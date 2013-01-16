#include "AMTask.h"
#include "AMThread.h"
#include "AMThreadMutex.h"
struct AMTaskMgrNode;

typedef struct AMTaskNode
{
    AMInt32                 mId; 
    struct AMTaskNode*      mNext;
    AMInt32                 mStatus;         //0, not start, 1, running, 2. finised.
    AMTaskProc              mProc;
	AMPVoid                 mProcArg;
	AMTaskArgFree			mProcFree;
    struct AMTaskMgrNode*   mTaskMgr;
	AMInt32					mThreadIndex;
}_AMTask;

typedef struct AMTaskMgrNode
{
    AMInt32                 mId;    
    AMInt32                 mConcurNum;         //可以运行最大任务数目
    _AMTask*                mTasks;             //task 列表 
    AMThreadMutex           mMutex;             //锁.
    AMInt32                 mNextTaskId;        //下一个任务要分配的Id
    AMThread                mThreads[AMASYNCTASK_MAX_EXECUTE_COUNT];
    AMInt32                 mThreadsFlag[AMASYNCTASK_MAX_EXECUTE_COUNT];    //0, unused. 1, finshed. 2, using.
}_AMTaskMgr;

AMPVoid _AMRunTaskThreadRun(_AMTask* task);

static  AMInt32 gTaskMgrCount = 0; 
static  AMThreadMutex gMutex = AMNULL;
static  _AMTaskMgr* gTaskMgr[AMASYNCTASK_SUPPORTED_MAXMGR] = { AMNULL };
#if !AMASYNCTASK_SUPPORTED_MUTI
static AMTaskMgr* AMTaskMgrCreate(AMInt32 concurNum);
static AMTask*    AMTaskMgrRun(AMTaskMgr* taskMgr, AMTaskProc proc, AMPVoid procArg, AMTaskArgFree procFree);
static AMInt32    AMTaskMgrRemove(AMTaskMgr* taskMgr, AMTask* task);
static AMInt32    AMTaskMgrDestory(AMTaskMgr* taskMgr);
#endif

static AMVoid _AMTaskMgrInit()
{
    if(gMutex != AMNULL)
        return;
     AMThreadMutexCreate(&gMutex);
     gTaskMgrCount = 0;
     AMMemset(gTaskMgr, 0, sizeof(gTaskMgr));
}
static AMVoid _AMTaskMgrUnint()
{
    if(gMutex == AMNULL)
        return;
    else
    {
        AMInt32 taskCount = 0;
        AMThreadMutexLock(&gMutex);
        taskCount = gTaskMgrCount;
        AMThreadMutexUnlock(&gMutex);
        if(taskCount == 0)
        {
            AMThreadMutexDestroy(&gMutex);
            gMutex = AMNULL;
        }
    }
}

static AMInt32 _AMRunTask(_AMTaskMgr* _taskMgr, AMBool isUseThisThread)
{
    if(_taskMgr == AMNULL)
        return -1;
    else
    {
        AMInt32 index = 0;
        _AMTask* task = AMNULL;
        _AMTask* nextRunTask = AMNULL;
        AMThreadMutexLock(&_taskMgr->mMutex);
        //find a unrun task.
        task = _taskMgr->mTasks;
        while(task != AMNULL)
        {
            if(task->mStatus == 0)
            {
                nextRunTask = task;
                break;
            }
            task = task->mNext;
        }
        if(nextRunTask != AMNULL && isUseThisThread == AMFALSE)
        {
            //find a empty thread.
            for(index = 0; index < _taskMgr->mConcurNum; index++)
            {
                if(_taskMgr->mThreadsFlag[index] == 1)
                {
                    AMThreadWait(_taskMgr->mThreads[index], AMNULL);
                    _taskMgr->mThreads[index] = AMNULL;
                    _taskMgr->mThreadsFlag[index] = 0;
                }

                if(_taskMgr->mThreadsFlag[index] == 0)
                {
                    nextRunTask->mStatus = 1;
                    _taskMgr->mThreadsFlag[index] = 2;
					nextRunTask->mThreadIndex = index;
                    AMPrintf("Create Thread\n");
                    AMThreadCreate(&_taskMgr->mThreads[index], AMNULL, _AMRunTaskThreadRun, nextRunTask);
                    break;
                }
            }
        }
        else if(nextRunTask != AMNULL && isUseThisThread == AMTRUE)
        {
            nextRunTask->mStatus = 1;
            AMThreadMutexUnlock(&_taskMgr->mMutex);
            AMPrintf("Re use Thread\n");
            task->mProc(task->mProcArg);
            AMThreadMutexLock(&_taskMgr->mMutex);
            task->mStatus = 2;
            AMThreadMutexUnlock(&_taskMgr->mMutex);
            AMTaskMgrRemove((AMTaskMgr*)_taskMgr, (AMTask*)task);
            return 1;
        }
        AMThreadMutexUnlock(&_taskMgr->mMutex);
        return 0;
    }
}
AMPVoid _AMRunTaskThreadRun(_AMTask* task)
{
    if(task == AMNULL)
        return AMNULL;
    else
    {
        //线程运行的第一个task.
        AMInt32 index = task->mThreadIndex;// get the index of the current thread from the first task that started it.

        _AMTaskMgr* taskMgr = task->mTaskMgr;
        task->mProc(task->mProcArg);
        AMThreadMutexLock(&taskMgr->mMutex);
        task->mStatus = 2;
        AMThreadMutexUnlock(&taskMgr->mMutex);
        AMTaskMgrRemove((AMTaskMgr*)taskMgr, (AMTask*)task);
       
        //如果还有Task, 继续运行.
        while(1)
        {
            AMInt32 retCode = _AMRunTask(taskMgr, AMTRUE);
            if(retCode != 1)
                break;
        }

		AMThreadMutexLock(&taskMgr->mMutex);
		taskMgr->mThreadsFlag[index] = 1;
		AMThreadMutexUnlock(&taskMgr->mMutex);
    }   
	
    return AMNULL;
}

AMTaskMgr* AMTaskMgrCreate(AMInt32 concurNum)
{
    AMInt32 index = 0;
    if(concurNum < 0)
        concurNum = AMASYNCTASK_DEFAULT_EXECUTE_COUNT;
    else if(concurNum > AMASYNCTASK_MAX_EXECUTE_COUNT)
        concurNum = AMASYNCTASK_MAX_EXECUTE_COUNT;

    _AMTaskMgrInit();
    AMThreadMutexLock(&gMutex);
    for(;index < AMASYNCTASK_SUPPORTED_MAXMGR; index++)
    {
        if(gTaskMgr[index] == AMNULL)
        {
            _AMTaskMgr* _taskMgr = (_AMTaskMgr*)AMMalloc(sizeof(_AMTaskMgr));
            if(_taskMgr == AMNULL)
            {
                AMThreadMutexUnlock(&gMutex);
                return AMNULL;
            }
			gTaskMgrCount++;
            AMMemset(_taskMgr, 0 , sizeof(_AMTaskMgr));
            _taskMgr->mId = index;
            _taskMgr->mConcurNum = concurNum;
            AMThreadMutexCreate(&_taskMgr->mMutex);
            AMThreadMutexUnlock(&gMutex);
            return (AMTaskMgr*)_taskMgr;
        }
    }
    AMThreadMutexUnlock(&gMutex);
    return AMNULL;
}
AMTask*  AMTaskMgrRun(AMTaskMgr* taskMgr, AMTaskProc proc, AMPVoid procArg, AMTaskArgFree procFree)
{
    _AMTaskMgr* _taskMgr = (_AMTaskMgr*)taskMgr;
    if(_taskMgr == AMNULL || proc == AMNULL)
        return AMNULL;
    else
    {
        _AMTask* newTask = AMNULL;
        AMThreadMutexLock(&_taskMgr->mMutex);
        //Create a new _AMTask.
        newTask = (_AMTask*)AMMalloc(sizeof(_AMTask));
        if(newTask == AMNULL)
        {
            AMThreadMutexUnlock(&_taskMgr->mMutex);
            return AMNULL;
        }
        AMMemset(newTask, 0, sizeof(_AMTask));
        newTask->mProc = proc;
        newTask->mProcArg = procArg;
		newTask->mProcFree = procFree;
        newTask->mId = _taskMgr->mNextTaskId++;
        newTask->mTaskMgr = _taskMgr;
        if(_taskMgr->mTasks == AMNULL)
            _taskMgr->mTasks = newTask;
        else
        {
            _AMTask* taskNode = _taskMgr->mTasks;
            while(taskNode->mNext != AMNULL)
            {
                taskNode = taskNode->mNext;
            }
            taskNode->mNext = newTask;
        }
        AMThreadMutexUnlock(&_taskMgr->mMutex);
        _AMRunTask(_taskMgr, AMFALSE);
        return (AMTask*)newTask;
    }
}

AMInt32  AMTaskMgrRemove(AMTaskMgr* taskMgr, AMTask* task)
{
    _AMTaskMgr* _taskMgr = (_AMTaskMgr*)taskMgr;
    _AMTask* _task = (_AMTask*)task;
    if(_taskMgr == AMNULL || _task == AMNULL)
        return -1;
    else
    {
        _AMTask* taskNode1 = AMNULL;
        _AMTask* taskNode2 = AMNULL;
        AMThreadMutexLock(&_taskMgr->mMutex);
        taskNode1 = _taskMgr->mTasks;
        while(taskNode1 != AMNULL)
        {
            if(taskNode1->mId == _task->mId && taskNode1->mTaskMgr->mId == _taskMgr->mId)
            {
                if(taskNode1->mStatus == 1)
                {
                    AMThreadMutexUnlock(&_taskMgr->mMutex);
                    return -1;
                }
                else
                {
                    if(taskNode2 == AMNULL)
                        _taskMgr->mTasks = taskNode1->mNext;
                    else
                        taskNode2->mNext = taskNode1->mNext;
                    
					if(taskNode1->mProcFree)
						taskNode1->mProcFree(taskNode1->mProcArg);// free ArgFree.
					
                    AMFree(taskNode1);
                    AMThreadMutexUnlock(&_taskMgr->mMutex);
                    return 0;
                }
            }
            taskNode2 = taskNode1;
            taskNode1 = taskNode2->mNext;
        }
        AMThreadMutexUnlock(&_taskMgr->mMutex);
        return -1;
    }
}
AMInt32   AMTaskMgrDestory(AMTaskMgr* taskMgr)
{   
    _AMTaskMgr* _taskMgr = (_AMTaskMgr*)taskMgr;
    if(_taskMgr == AMNULL)
        return -1;
    else
    {
        _AMTask* task = AMNULL;
        _AMTask* taskNext = AMNULL;
        AMInt32  index = 0;
        AMThreadMutexLock(&_taskMgr->mMutex);
        //Remove all finish and unstarded.
        task = _taskMgr->mTasks;
        while(task != AMNULL)
        {
            AMInt32 retCode = 0;
            taskNext = task->mNext;
            AMTaskMgrRemove((AMTaskMgr*)_taskMgr, (AMTask*)task);
            task = taskNext;
        }
        AMThreadMutexUnlock(&_taskMgr->mMutex);
        //WaitFor running thread.
        for(; index < _taskMgr->mConcurNum; index++)
        {
            if(_taskMgr->mThreads[index] != AMNULL)
            {
                AMThreadWait(_taskMgr->mThreads[index], AMNULL);
            }
        }
        //Remove Form  TaskManager.
        AMThreadMutexLock(&gMutex); 
		AMThreadMutexDestroy(&_taskMgr->mMutex);
        gTaskMgr[_taskMgr->mId] = AMNULL;
        gTaskMgrCount--;
        AMThreadMutexUnlock(&gMutex);
		_AMTaskMgrUnint();
        AMFree(_taskMgr);
        return 0;
    }
}

AMTask	*	AMTaskMgrGetTask(AMTaskMgr *taskMgr)
{
	_AMTaskMgr* _taskMgr = (_AMTaskMgr*)taskMgr;
	AMAssert(taskMgr);
	
	AMThreadMutexLock(&_taskMgr->mMutex);

	return _taskMgr->mTasks;
}

AMVoid		AMTaskMgrReleaseTask(AMTaskMgr *taskMgr)
{
	_AMTaskMgr* _taskMgr = (_AMTaskMgr*)taskMgr;
	AMAssert(taskMgr);

	AMThreadMutexUnlock(&_taskMgr->mMutex);
}

AMTaskProc	AMTaskGetProc(AMTask *task)
{
	_AMTask	*pTask = (_AMTask *)task;
	AMAssert(pTask);

	return pTask->mProc;
}

AMPVoid		AMTaskGetArg(AMTask	*task)
{
	_AMTask	*pTask = (_AMTask *)task;
	AMAssert(pTask);

	return pTask->mProcArg;
}

AMTask	*	AMTaskGetNext(AMTask *task)
{
	_AMTask	*pTask = (_AMTask *)task;
	AMAssert(pTask);

	return pTask->mNext;
}

#if AMASYNCTASK_SUPPORTED_MUTI
#else
static AMTaskMgr* gTaskMgrIn = AMNULL;
static AMInt32    gConcurNum = AMASYNCTASK_DEFAULT_EXECUTE_COUNT;

AMInt32  AMTaskSetConcurNum(AMInt32 num)
{
    _AMTaskMgrInit();
    AMThreadMutexLock(&gMutex);
    if(num < 0)
        num = AMASYNCTASK_DEFAULT_EXECUTE_COUNT;
    else if(num > AMASYNCTASK_MAX_EXECUTE_COUNT)
        num = AMASYNCTASK_MAX_EXECUTE_COUNT;
    if(gTaskMgrIn != AMNULL)
    {
        _AMTaskMgr* _taskMgr = (_AMTaskMgr*)gTaskMgrIn;
        AMThreadMutexLock(gTaskMgrIn);
        _taskMgr->mConcurNum = num;
        AMThreadMutexUnlock(gTaskMgrIn);
    }
    gConcurNum = num;
    AMThreadMutexUnlock(&gMutex);
    return 0;
}
AMTask* AMTaskRun(AMTaskProc proc, AMPVoid procArg)
{
    AMTask* task;
    _AMTaskMgrInit();
    AMThreadMutexLock(&gMutex);
    if(gTaskMgrIn == AMNULL)
    {
        gTaskMgrIn = AMTaskMgrCreate(gConcurNum);
        if(gTaskMgrIn == AMNULL)
        {
            AMThreadMutexUnlock(&gMutex);
            return AMNULL;
        }
    }
    task = AMTaskMgrRun(gTaskMgrIn, proc, procArg);
    AMThreadMutexUnlock(&gMutex);
    return task;
}
AMInt32 AMTaskRemove(AMTask* task)
{
    AMInt32 retCode = 0;
    _AMTaskMgrInit();
    AMThreadMutexLock(&gMutex);
    if(gTaskMgrIn == AMNULL)
    {
        AMThreadMutexUnlock(&gMutex);
        return -1;
    }
    AMThreadMutexUnlock(&gMutex);
    retCode = AMTaskMgrRemove(gTaskMgrIn, task);
    return retCode;
}
#endif

#ifndef  _AM_TASK_H_
#define  _AM_TASK_H_
#include <AMOS.h>

#define AMASYNCTASK_SUPPORTED_MAXMGR             16 //任务管理最大任务数目
#define AMASYNCTASK_MAX_EXECUTE_COUNT            16 //默认一个任务管理执行最大任务数目
#define AMASYNCTASK_DEFAULT_EXECUTE_COUNT        4  //默认一个任务管理执行任务数目
#define AMASYNCTASK_SUPPORTED_MUTI               1  //是否支持任务管理并发

typedef AMPVoid AMTaskMgr;
typedef AMPVoid AMTask;
typedef AMPVoid (*AMTaskProc)(AMPVoid procArg); 
typedef		AMVoid (*AMTaskArgFree)(AMPVoid pvArg);

#if AMASYNCTASK_SUPPORTED_MUTI
AMTaskMgr* AMTaskMgrCreate(AMInt32 concurNum);
AMTask*    AMTaskMgrRun(AMTaskMgr* taskMgr, AMTaskProc proc, AMPVoid procArg, AMTaskArgFree procFree);
AMInt32    AMTaskMgrRemove(AMTaskMgr* taskMgr, AMTask* task);
AMInt32    AMTaskMgrDestory(AMTaskMgr* taskMgr);

AMTask	*	AMTaskMgrGetTask(AMTaskMgr *taskMgr);
AMVoid		AMTaskMgrReleaseTask(AMTaskMgr *taskMgr);

AMTaskProc	AMTaskGetProc(AMTask *pTask);
AMPVoid		AMTaskGetArg(AMTask	*pTask);
AMTask	*	AMTaskGetNext(AMTask *pTask);
	
#else
AMInt32 AMTaskSetConcurNum(AMInt32 num);
AMTask* AMTaskRun(AMTaskProc proc, AMPVoid procArg);
AMInt32 AMTaskRemove(AMTask*  task);
#endif
#endif

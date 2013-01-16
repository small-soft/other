#ifndef  _AM_TASK_H_
#define  _AM_TASK_H_
#include <AMOS.h>

#define AMASYNCTASK_SUPPORTED_MAXMGR             16 //����������������Ŀ
#define AMASYNCTASK_MAX_EXECUTE_COUNT            16 //Ĭ��һ���������ִ�����������Ŀ
#define AMASYNCTASK_DEFAULT_EXECUTE_COUNT        4  //Ĭ��һ���������ִ��������Ŀ
#define AMASYNCTASK_SUPPORTED_MUTI               1  //�Ƿ�֧�����������

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

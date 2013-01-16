#include "AMLooperHandler.h"
#include "AMLooperMessage.h"
#include "AMLooper.h"
#include "AMTime.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMLog.h"

/** AMLooper 定义, 用户不可以直接操作里面的数据内容 */
typedef struct AMLooper
{
    List handler_queue;				     /**< Handler队列. */
    List message_queue;				     /**< 所有Handler消息的队列. */ 	
    AMThreadMutex   queue_mutex;	     /**< 队列同步的mutex. */ 
    AMInt32 end_run_flag;				 /**< 结束运行标志.	0表示继续运行, 1表示结束. */
    AMInt32 start_run_falg;				 /**< 标识这个looper是否已经开始运行. */
    AMThreadCond	loop_cond;			 /**< 用于通知loop可以开始运行了. */
    AMThreadMutex	loop_cond_mutex;	 /**< loop_cond配套使用的mutex. */

    List time_message_queue;			 /**< 这个是定时执行的消息队列 */
    AMInt32         isHasRecord;
}AMLooper;

#define LOOPER_END_TRUE				1
#define LOOPER_END_FALSE			0
#define LOOPER_RUNNING_TRUE			1
#define LOOPER_RUNNING_FALSE		0

/** AMHandler 定义, 用户不可以直接操作里面的数据内容 */
struct AMHandler
{
	struct AMLooper* looper;		    /**< 所在的looper */
	AMInt32 end_run_flag;				/**< 结束运行标志.	0表示继续运行, 1表示结束. */
	AMLooperHandlerCallback callback;   /**< handler的消息处理函数. */
    AMPVoid cbArgs;                     /**< 回调参数. */
};

#define HANDLE_END_TRUE				1
#define HANDLE_END_FALSE			0



//销毁整个looper.
static AMInt32 _AMLooperDestory(struct AMLooper* looper);
//添加一个Handler
AMInt32 AMLooperAddHandler(struct AMLooper* looper, struct AMHandler* handler);
//移除一个handler
AMInt32 AMLooperRemoveHandler(struct AMLooper* looper, struct AMHandler* handler);
//添加一个消息
AMInt32 AMLooperAddMessage(struct AMLooper* looper, struct AMMessage* message);
//添加一个时间消息
AMInt32 AMLooperAddTimeMessage(struct AMLooper* looper, struct AMMessage* message);
//得到一个消息
static AMInt32 _AMLooperGetMessage(struct AMLooper* looper, struct AMMessage* message);
static AMInt32 _AMLooperGetTimeMessage(struct AMLooper* looper, struct AMMessage* message, AMInt32* left_time);
//这个方法是AMLooperRemoveHandler的辅助方法, 其它不能调用.
void _AMLooperRemoveHandlerMsg(struct AMHandler* handler, List* list);
//移除所有消息.
void _AMLooperRemoveAllMsg(struct AMLooper* looper);
AMInt32 AMLooperRemoveTimerMessage(struct AMHandler* handler, AMUInt32 timer);


static AMInt32 _AMLooperMessageCmp(const AMVoid* ul1,const AMVoid* ul2, AMSize_t size)
{
    //AMLogForDebug("AMLooper", "_AMLooperMessageCmp");
	struct AMMessage* msg1 = (struct AMMessage*)ul1;
	struct AMMessage* msg2 = (struct AMMessage*)ul2;
	return -(msg1->run_tm.tv_sec - msg2->run_tm.tv_sec) * 1000000 - (msg1->run_tm.tv_usec - msg2->run_tm.tv_usec);
}

static AMVoid _AMLooperMessagePrint(const AMPVoid u)
{
    //AMLogForDebug("AMLooper", "_AMLooperMessagePrint");
	struct AMMessage* msg = (struct AMMessage*)u;
	AMPrintf("Msg: t = [%d, %d]\n", msg->run_tm.tv_sec, msg->run_tm.tv_usec);
}
// 
AMVoid _AMMessage_Destroy(AMVoid *pvMsg)
{
	struct AMMessage *pMsg = (struct AMMessage*)pvMsg;
	pMsg->cleanUp(pMsg);
	free(pMsg);
}

//建立looper
AMInt32 AMLooperCreate(struct AMLooper** looper)
{
    //AMLogForDebug("AMLooper", "AMLooperCreate");
	*looper = (struct AMLooper*)malloc(sizeof(struct AMLooper));
	if(NULL == *looper)
		return AME_LOOPER_ALLOC_MEMORY_ERROR;

	memset(*looper, 0, sizeof(struct AMLooper));

	if(construct_List(&((*looper)->handler_queue), sizeof(struct AMHandler), NOFREE) != 0)
	{
		free(*looper);
		*looper = NULL;
		return AME_LOOPER_OTHER_ERROR;
	}
	
	//内存测试.
	//set_alloc_List(&((*looper)->handler_queue), AMMalloc);
	//set_dealloc_List(&((*looper)->handler_queue), AMFree);
	if(construct_List(&((*looper)->message_queue), sizeof(struct AMMessage), FREEOBJ) != 0)
	{
		destruct_List(&((*looper)->handler_queue));
		free(*looper);
		*looper = NULL;
		return AME_LOOPER_OTHER_ERROR;
	}
	//内存测试.
	//set_alloc_List(&((*looper)->message_queue), AMMalloc);
	//set_dealloc_List(&((*looper)->message_queue), AMFree);
	if(construct_List(&((*looper)->time_message_queue), sizeof(struct AMMessage), FREEOBJ) != 0)
	{
		destruct_List(&((*looper)->handler_queue));
		destruct_List(&((*looper)->message_queue));
		free(*looper);
		*looper = NULL;
		return AME_LOOPER_OTHER_ERROR;
	}
	set_compare_List(&((*looper)->time_message_queue),  _AMLooperMessageCmp);
	//set_print_List(&((*looper)->time_message_queue), _AMLooperMessagePrint);
	//内存测试.
	//set_alloc_List(&((*looper)->message_queue), s_malloc);
	//set_dealloc_List(&((*looper)->message_queue), s_free);
	{
		AMInt32 err_code;
		err_code = AMThreadMutexCreate(&((*looper)->queue_mutex));
		err_code = AMThreadMutexCreate(&((*looper)->loop_cond_mutex));
		err_code = AMThreadCondCreate(&((*looper)->loop_cond));
	}

	(*looper)->end_run_flag = LOOPER_END_FALSE;
	(*looper)->start_run_falg = LOOPER_RUNNING_FALSE;
	return AME_LOOPER_SCUESS;
}
//关闭looper
AMInt32 AMLooperClose(struct AMLooper* looper)
{
    //AMLogForDebug("AMLooper", "AMLooperClose");
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	looper->end_run_flag = LOOPER_END_TRUE;
	if(LOOPER_RUNNING_FALSE == looper->start_run_falg)
	{
		return AME_LOOPER_LOOPER_NOT_STARTED;
	}
	else
	{
		//添加了一个消息, 条件变量通知
        AMThreadMutexLock(&looper->loop_cond_mutex);
        looper->isHasRecord = 1;
        AMThreadMutexUnlock(&looper->loop_cond_mutex);
		AMThreadCondSignal(&looper->loop_cond);
	}

	return AME_LOOPER_SCUESS;
}

//销毁整个looper.
AMInt32 _AMLooperDestory(struct AMLooper* looper)
{
    //AMLogForDebug("AMLooper", "_AMLooperDestory");
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
	{
		AMInt32 err_code;
		struct AMHandler* temp_handler;
		err_code = AMThreadMutexLock(&looper->queue_mutex);

		//消息销毁
		_AMLooperRemoveAllMsg(looper);
		//Handler销毁
		for(temp_handler = (struct AMHandler*)front_List(&looper->handler_queue); temp_handler != NULL;
			temp_handler = (struct AMHandler*)front_List(&looper->handler_queue))
		{
			pop_front_List(&looper->handler_queue);
			free(temp_handler);
		}

		err_code =AMThreadMutexUnlock(&looper->queue_mutex);

		err_code = AMThreadMutexDestroy(&looper->queue_mutex);
		err_code = AMThreadCondDestroy(&looper->loop_cond);
		err_code = AMThreadMutexDestroy(&looper->loop_cond_mutex);

		destruct_List(&looper->handler_queue);
		destruct_List(&looper->message_queue);
		destruct_List(&looper->time_message_queue);
	}
	free(looper);
	looper = NULL;
	return AME_LOOPER_SCUESS;
}
//执行looper

AMInt32 AMLooperLoop(struct AMLooper* looper)
{
    //AMLogForDebug("AMLooper", "AMLooperLoop");
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	looper->start_run_falg = LOOPER_RUNNING_TRUE;

	do
	{
		struct AMMessage message;
		AMInt32 left_time;
		AMInt32 err_code = 0;
		AMInt32 is_cond_time_set = 0;
		//处理完所有的一般消息
		do
		{
			if(LOOPER_END_TRUE == looper->end_run_flag)
			{
				looper->start_run_falg = LOOPER_RUNNING_FALSE;
				_AMLooperDestory(looper);
				return AME_LOOPER_SCUESS;
			}

			if(_AMLooperGetMessage(looper, &message) == AME_LOOPER_SCUESS)
			{
				message.handler->callback(&message, message.handler->cbArgs);
                if(message.cleanUp != NULL)
                    message.cleanUp(&message);
			}
			else
			{
				break;
			}
		}while(1);

		//处理所有定时消息
		do
		{
			if(LOOPER_END_TRUE == looper->end_run_flag)
			{
				looper->start_run_falg = LOOPER_RUNNING_FALSE;
				_AMLooperDestory(looper);
				return AME_LOOPER_SCUESS;
			}
			err_code = _AMLooperGetTimeMessage(looper, &message, &left_time);
			if(err_code == AME_LOOPER_SCUESS)
			{
				if(message.type == AM_MESSAGE_TIMER)
					((AMVoid(*)(AMPVoid* pArg))message.ref1.ptr)(message.ref2.ptr);
				else
                {
					message.handler->callback(&message, message.handler->cbArgs);
                    if(message.cleanUp != NULL)
                        message.cleanUp(&message);
                }
			}
			else if(left_time > 0)
			{
				is_cond_time_set = 1;
				break;
			}
			else 
			{
				is_cond_time_set = 0;
				break;
			}
		}while(1);
		//用athread_cond来处理.
        AMThreadMutexLock(&looper->loop_cond_mutex);
        while(looper->isHasRecord == 0)
        {
		    if(is_cond_time_set == 0)
		    {
                AMPrintf("AMThreadCondWait Start\n");
			    AMThreadCondWait(&looper->loop_cond, &looper->loop_cond_mutex); 
                AMPrintf("AMThreadCondWait End\n");
			    
		    }
		    else
		    {
			    //还要加上当前的时间
			    struct AMTimeval tm;
			    AMGetUTCTimeEx(&tm);
			    tm.tv_sec += (left_time + tm.tv_usec / 1000) / 1000;
			    tm.tv_usec = (((left_time + tm.tv_usec /1000)) % 1000) * 1000;
			    AMThreadCondTimewait(&looper->loop_cond, &looper->loop_cond_mutex, &tm);
		    }
        }
        looper->isHasRecord = 0;
        AMThreadMutexUnlock(&looper->loop_cond_mutex);
	}while(1);

	return AME_LOOPER_SCUESS;
}

//添加一个Handler
AMInt32 AMLooperAddHandler(struct AMLooper* looper, struct AMHandler* handler)
{
    //AMLogForDebug("AMLooper", "AMLooperAddHandler");
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
		
	if( NULL == handler)
		return AME_LOOPER_HANDLE_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if(HANDLE_END_TRUE == handler->end_run_flag)
		return AME_LOOPER_HANDLE_INVALID;

	/*
	if(looper->start_run_falg != LOOPER_RUNNING_TRUE)
		return AME_LOOPER_LOOPER_NOT_STARTED;
	*/
	
	//添加到队列尾部, 注意要保持列表线程安全.
	{
		AMInt32 err_code;
		err_code = AMThreadMutexLock(&looper->queue_mutex);
		err_code = push_back_List(&looper->handler_queue, handler, sizeof(struct AMHandler), DYNAMIC);
		err_code = AMThreadMutexUnlock(&looper->queue_mutex);
		
	}
	
	return AME_LOOPER_SCUESS;
}

// 移除一个handler
AMInt32 AMLooperRemoveHandler(struct AMLooper* looper, struct AMHandler* handler)
{
    //AMLogForDebug("AMLooper", "AMLooperRemoveHandler");
	AMInt32 ret_code = AME_LOOPER_SCUESS;
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
		
	if( NULL == handler)
		return AME_LOOPER_HANDLE_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if(HANDLE_END_TRUE == handler->end_run_flag)
		return AME_LOOPER_HANDLE_INVALID;

	if(looper->start_run_falg != LOOPER_RUNNING_TRUE)
		return AME_LOOPER_LOOPER_NOT_STARTED;

	//查找Handler
	{
		ListIter* iter;
		AMInt32 err_code;

		//在处理链表之前要锁住
		err_code = AMThreadMutexLock(&looper->queue_mutex);
		iter = create_ListIter(&looper->handler_queue);
		//链表头
		if(!head_ListIter(iter))											
		{
			struct AMHandler* removed_node = NULL;
			do
			{
				struct AMHandler* node = (struct AMHandler*)retrieve_ListIter(iter);
				if(node == handler)
				{
					extract_ListIter(iter);
					removed_node = node;
					break;
				}
			}while(!next_ListIter(iter));

			//找到了要移除的Handler
			if(NULL != removed_node)
			{
				//移除所有该Handler还没有处理的一般消息.
				_AMLooperRemoveHandlerMsg(removed_node, &looper->message_queue);
				//移除所有定时消息.
				_AMLooperRemoveHandlerMsg(removed_node, &looper->time_message_queue);
				//删除Handler对象.
				free(removed_node);
			}
			else
			{
				ret_code =  AME_LOOPER_HANDLE_NOT_EXIST;
				goto AM_REMOVE_LOOPER_HANDLE_END;
			}
		}

AM_REMOVE_LOOPER_HANDLE_END:
		destroy_ListIter(iter);
		err_code =AMThreadMutexUnlock(&looper->queue_mutex);
	}

	return ret_code;
}
//这个方法是AMLooperRemoveHandler的辅助方法, 其它不能调用.
void _AMLooperRemoveHandlerMsg(struct AMHandler* handler, List* list)
{
    //AMLogForDebug("AMLooper", "_AMLooperRemoveHandlerMsg");
	ListIter* message_iter;
	message_iter = create_ListIter(list);

	if(!head_ListIter(message_iter))											
	{
		do
		{
            struct AMMessage* msg = (struct AMMessage*)retrieve_ListIter(message_iter);
			if(msg->handler == handler || handler == NULL)
			{
				ListIter temp_message_iter;
				AMMemset(&temp_message_iter, 0, sizeof(ListIter));
				copy_ListIter(&temp_message_iter, message_iter);
				if(!next_ListIter(message_iter))
				{
					if(msg->cleanUp)
						msg->cleanUp(msg);
					//free(msg);
					extract_ListIter(&temp_message_iter);
					continue;
				}
				else
				{
					if(msg->cleanUp)
						msg->cleanUp(msg);
					//free(msg);
					extract_ListIter(&temp_message_iter);
					break;
				}
			}
		}while(!next_ListIter(message_iter));
	}
	destroy_ListIter(message_iter);
}
void _AMLooperRemoveAllMsg(struct AMLooper* looper)
{
    //AMLogForDebug("AMLooper", "_AMLooperRemoveAllMsg");
    _AMLooperRemoveHandlerMsg(NULL, &looper->message_queue);
    _AMLooperRemoveHandlerMsg(NULL, &looper->time_message_queue);
}

//添加一个消息
AMInt32 AMLooperAddMessage(struct AMLooper* looper, struct AMMessage* message)
{
    //
	AMInt32 ret_code = AME_LOOPER_SCUESS;
    //AMLogForDebug("AMLooper", "AMLooperAddMessage");
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
		
	if( NULL == message)
		return AME_LOOPER_MESSAGE_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if(looper->start_run_falg != LOOPER_RUNNING_TRUE)
		return AME_LOOPER_LOOPER_NOT_STARTED;

	//添加到消息队列尾部, 注意要保持列表线程安全.
	{
		AMInt32 err_code;
		err_code = AMThreadMutexLock(&looper->queue_mutex);
		err_code = push_back_List(&looper->message_queue, message, sizeof(struct AMMessage), STATIC);
		err_code = AMThreadMutexUnlock(&looper->queue_mutex);

		//添加了一个消息, 条件变量通知
        AMThreadMutexLock(&looper->loop_cond_mutex);
        looper->isHasRecord = 1;
        AMThreadMutexUnlock(&looper->loop_cond_mutex);
		AMThreadCondSignal(&looper->loop_cond);
	}

	return AME_LOOPER_SCUESS;
}

AMInt32 AMLooperAddTimeMessage(struct AMLooper* looper, struct AMMessage* message)
{
    //AMLogForDebug("AMLooper", "AMLooperAddTimeMessage");
	AMInt32 ret_code = AME_LOOPER_SCUESS;
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
		
	if( NULL == message)
		return AME_LOOPER_MESSAGE_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if(looper->start_run_falg != LOOPER_RUNNING_TRUE)
		return AME_LOOPER_LOOPER_NOT_STARTED;

	//添加到消息队列尾部, 注意要保持列表线程安全.
	{
		AMInt32 err_code;
		err_code = AMThreadMutexLock(&looper->queue_mutex);
		insert_List(&looper->time_message_queue, message, sizeof(struct AMMessage), STATIC);
		//print_List(&looper->time_message_queue);
		//AMPrintf("\n");
		err_code = AMThreadMutexUnlock(&looper->queue_mutex);
		//添加了一个消息, 条件变量通知
        AMThreadMutexLock(&looper->loop_cond_mutex);
        looper->isHasRecord = 1;
        AMThreadMutexUnlock(&looper->loop_cond_mutex);
		AMThreadCondSignal(&looper->loop_cond);
	}
	return AME_LOOPER_SCUESS;
}

//移除一个消息
AMInt32 _AMLooperGetMessage(struct AMLooper* looper, struct AMMessage* message)
{
    //AMLogForDebug("AMLooper", "_AMLooperGetMessage");
	AMInt32 ret_code = AME_LOOPER_SCUESS;
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
		
	if( NULL == message)
		return AME_LOOPER_MESSAGE_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if(looper->start_run_falg != LOOPER_RUNNING_TRUE)
		return AME_LOOPER_LOOPER_NOT_STARTED;

	//拿到第一条消息
	{
		AMInt32 err_code;
		struct AMMessage* front_message;
		err_code = AMThreadMutexLock(&looper->queue_mutex);
		if(empty_List(&looper->message_queue))
		{
			front_message = (struct AMMessage*)front_List(&looper->message_queue);
			memcpy(message, front_message, sizeof(struct AMMessage));
			err_code = pop_front_List(&looper->message_queue);
		}
		else
			ret_code = AME_LOOPER_MESSAGE_NOT_EXIST;
		err_code = AMThreadMutexUnlock(&looper->queue_mutex);
	}

	return ret_code;
}
AMInt32 _AMLooperGetTimeMessage(struct AMLooper* looper, struct AMMessage* message, AMInt32* left_time)
{
    //AMLogForDebug("AMLooper", "_AMLooperGetTimeMessage");
	AMInt32 ret_code = AME_LOOPER_SCUESS;
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;
		
	if( NULL == message)
		return AME_LOOPER_MESSAGE_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if(looper->start_run_falg != LOOPER_RUNNING_TRUE)
		return AME_LOOPER_LOOPER_NOT_STARTED;

	if(NULL == left_time)
		return AME_LOOPER_TIMEVAL_NULL;

	*left_time  = 0;
	//拿到第一条消息
	{
		AMInt32 err_code;
		struct AMMessage* front_message;
		err_code = AMThreadMutexLock(&looper->queue_mutex);
		
		if(empty_List(&looper->time_message_queue))
		{
			struct AMTimeval tp;
			front_message = (struct AMMessage*)back_List(&looper->time_message_queue);
			AMGetUTCTimeEx(&tp);
			*left_time = (front_message->run_tm.tv_sec - tp.tv_sec) * 1000;
			*left_time += (front_message->run_tm.tv_usec - tp.tv_usec) / 1000;
			if(*left_time  > 0)
			{
				ret_code = AME_LOOPER_MESSAGE_NOT_EXIST;
			}
			else 
			{
				*left_time  = 0;
				memcpy(message, front_message, sizeof(struct AMMessage));
				err_code = pop_back_List(&looper->time_message_queue);
			}
		}
		else
			ret_code = AME_LOOPER_MESSAGE_NOT_EXIST;
		err_code = AMThreadMutexUnlock(&looper->queue_mutex);
	}

	return ret_code;
}

void* AMLooperCallback(void* v)
{
    //AMLogForDebug("AMLooper", "AMLooperCallback");
	struct AMLooper* looper = (struct AMLooper*)v;
	if(NULL == v)
		return NULL;

	AMLooperLoop(looper);
	return NULL;
}

AMInt32 AMLooperRemoveTimerMessage(struct AMHandler* handler, AMUInt32 timer)
{
    //AMLogForDebug("AMLooper", "AMLooperRemoveTimerMessage");
	if( NULL == handler)
		return AME_LOOPER_HANDLE_NULL;

	if(NULL == handler->looper)
		return AME_LOOPER_LOOPER_NULL;

	if(LOOPER_END_TRUE == handler->looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if( HANDLE_END_TRUE == handler->end_run_flag)
		return AME_LOOPER_HANDLE_INVALID;

	//移除消息。 
	{
		AMInt32 err_code;
		ListIter* iter = NULL;
		err_code = AMThreadMutexLock(&handler->looper->queue_mutex);
		iter = create_ListIter(&handler->looper->time_message_queue);
		if(!head_ListIter(iter))											
		{
			do
			{
				struct AMMessage* node = (struct AMMessage*)retrieve_ListIter(iter);
				if(node->type == AM_MESSAGE_TIMER && node->v1.ui == timer)
				{
					extract_ListIter(iter);
				}
			}while(!next_ListIter(iter));
		}
		destroy_ListIter(iter);
		err_code = AMThreadMutexUnlock(&handler->looper->queue_mutex);
	}

	return AME_LOOPER_SCUESS;
}

//在looper上创建一个handler, 同时设置handler的AMLooperHandlerCallback方法
AMInt32 AMHandlerCreate(struct AMHandler** handler, struct AMLooper* looper, AMLooperHandlerCallback callback, AMPVoid cbArgs)
{
    //AMLogForDebug("AMLooper", "AMHandlerCreate");
	if(NULL == looper)
		return AME_LOOPER_LOOPER_NULL;

	if(NULL == callback)
		return AME_LOOPER_CALLBACK_NULL;

	if(LOOPER_END_TRUE == looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	*handler = (struct AMHandler*)malloc(sizeof(struct AMHandler));
	if(NULL == *handler)
		return AME_LOOPER_ALLOC_MEMORY_ERROR;
	memset(*handler, 0, sizeof(struct AMHandler));

	(*handler)->end_run_flag = HANDLE_END_FALSE;
	(*handler)->callback = callback;
    (*handler)->cbArgs = cbArgs;
	(*handler)->looper = looper;
	{
		AMInt32 err_code = AMLooperAddHandler(looper, *handler);
		if(err_code != AME_LOOPER_SCUESS)
		{
			free(*handler);
			*handler = NULL;
			return err_code;
		}
	}
	return AME_LOOPER_SCUESS;
}
//关闭handler
AMInt32 AMHandlerClose(struct AMHandler* handler)
{
    //AMLogForDebug("AMLooper", "AMHandlerClose");
	if( NULL == handler)
		return AME_LOOPER_HANDLE_NULL;

	if(NULL == handler->looper)
		return AME_LOOPER_LOOPER_NULL;

	if(LOOPER_END_TRUE == handler->looper->end_run_flag)
		return AME_LOOPER_LOOPER_INVALID;

	if( HANDLE_END_TRUE == handler->end_run_flag)
		return AME_LOOPER_HANDLE_INVALID;

	return AMLooperRemoveHandler(handler->looper, handler);
}
//发送一个消息到
AMInt32 AMHandlerSendMsg(struct AMHandler* handler, struct AMMessage* msg)
{
    //AMLogForDebug("AMLooper", "AMHandlerSendMsg");
	if(NULL == handler)
		return AME_LOOPER_HANDLE_NULL;

	if( NULL == msg)
		return AME_LOOPER_MESSAGE_NULL;

	if(HANDLE_END_TRUE == handler->end_run_flag)
		return AME_LOOPER_HANDLE_INVALID;

	msg->handler = handler;
	return AMLooperAddMessage(handler->looper,  msg);
}
//发送一个延时消息到handler
AMInt32 AMHandlerSendMsgAfterTime(struct AMHandler* handler, struct AMMessage* msg, struct AMTimeval* tm)
{
    //AMLogForDebug("AMLooper", "AMHandlerSendMsgAfterTime");
	if(NULL == handler)
		return AME_LOOPER_HANDLE_NULL;

	if( NULL == msg)
		return AME_LOOPER_MESSAGE_NULL;

	if(HANDLE_END_TRUE == handler->end_run_flag)
		return AME_LOOPER_HANDLE_INVALID;

	if(NULL == tm)
		return  AME_LOOPER_TIMEVAL_NULL;

	msg->handler = handler;
	if((tm->tv_sec > 0 && tm->tv_usec >= 0) || (tm->tv_usec > 0 && tm->tv_sec >= 0))
	{
		//得到当前时间.
		AMGetUTCTimeEx(&msg->run_tm);
		msg->run_tm.tv_sec += tm->tv_sec + (tm->tv_usec + msg->run_tm.tv_usec) / 1000000;
		msg->run_tm.tv_usec = (tm->tv_usec + msg->run_tm.tv_usec) % 1000000;
		return AMLooperAddTimeMessage(handler->looper, msg);
	}
	else
	{
		return AMHandlerSendMsg(handler, msg);
	}
}
AMInt32 AMHandlerRemoveTimerMessage(struct AMHandler* handler, AMUInt32 timer)
{
    //AMLogForDebug("AMLooper", "AMHandlerRemoveTimerMessage");
	if(NULL == handler)
		return AME_LOOPER_HANDLE_NULL;
	else
		return AMLooperRemoveTimerMessage(handler, timer);
}


#ifndef _AME_LOOPER_MESSAGE_
#define _AME_LOOPER_MESSAGE_
/*
 * @defgroup AMMessage模块
 * @{
 */
#include "AMLooperConfig.h"
#include "AMTime.h"

struct AMHandler;
struct AMMessage;

/** @brief 消息处理函数, 对发送给Handler的消息, 调用这个函数善后
 *  @param [in]  message 消息对象.
 *  @return 无.
*/
typedef AMVoid(*AMMessageCleanUp)(struct AMMessage* message);

/** 消息中用到的值类型 */
typedef union a_value
{
	AMInt8			c;
	AMUInt8     	uc; 
	AMInt16			s;
	AMUInt16	    us;
	AMInt32			i;
	AMUInt32	    ui;
	AMFloat			f;
	AMDouble		d;
}a_value;

/** 消息中用到的引用类型 */
typedef union a_ref
{
	AMPVoid	 ptr;
	AMInt8*	 sptr;

}a_ref;

typedef enum 
{
	AM_MESSAGE_NORMAL  =  0,	/** < 一般消息   */
	AM_MESSAGE_TIMER,			/** < 计时器消息  */
}AMMsgType;

/** 消息结构， 注意： v1， v2， ref1，ref2为用户可以直接使用的字段 其它字段用户不能使用*/
struct AMMessage
{
	//下面四个为用户使用字段
	a_value	v1;						/** < 值1 */
	a_value	v2;						/** < 值2 */
	a_value	v3;						/** < 值3 */
	a_value	v4;						/** < 值4*/
	a_ref		ref1;				/** < 引用1 */
	a_ref		ref2;				/** < 引用2 */

	//注意: 下面字段用户不能直接使用
	AMMsgType type;					/** < 消息类型,表示消息属于什么类型, 。	*/
	struct AMHandler* handler;		/** < 所在的Handler*/
    AMMessageCleanUp    cleanUp;    /** < 对没有处理的消息, 调用这个函数处理 */
	struct AMTimeval run_tm;		/** < 运行的时刻. */
};

#ifdef __cplusplus 
extern "C" {
#endif

    /** @brief 创建一个消息
     *  @param [in]  message 消息对象.
     *  @param [in]  cleanUp 善后函数, 传入空的时候, 表示忽略善后工作.
     *  @return: 成功: AME_LOOPER_SCUESS; 失败 (AME_LOOPER_MESSAGE_NULL : message无效;)
    */	
    ADAPTER_API AMInt32 AMMessageInit(struct AMMessage* message, AMMessageCleanUp cleanUp);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif

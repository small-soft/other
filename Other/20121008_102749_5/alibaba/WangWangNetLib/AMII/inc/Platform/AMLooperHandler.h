#ifndef _AME_LOOPER_HANDLER_
#define _AME_LOOPER_HANDLER_
/*
 * @defgroup AMHandler模块
 * @{
 */
#include "AMLooperConfig.h"

struct AMMessage;
struct AMLooper;
struct AMHandler;

/** @brief AMHandler的回调函数, 每一次回调, 就是处理一条消息.
 *  @param [in]  msg 消息对象.
 *  @param [in]  cbArgs.
 *  @return 0, 表示正常结束, 1 表示用户已经处理了消息的善后工作.
*/
typedef AMInt32 (*AMLooperHandlerCallback)(struct AMMessage* msg, AMPVoid cbArgs);

#ifdef __cplusplus 
extern "C" {
#endif
    /** @brief 在looper上创建一个handler, 同事设置callback函数.
     *  @param [out] handler  存放AMHandler句柄
     *  @param [in]  looper   AMLooper对象, 不能为空
     *  @param [in]  callback handler的处理消息函数.
     *  @param [in]  cbArgs
     *  @return 错误码
    */
    ADAPTER_API AMInt32 AMHandlerCreate(struct AMHandler** handler, 
        struct AMLooper* looper, AMLooperHandlerCallback callback, AMPVoid cbArgs);
    /** @brief 关闭handler, 同时释放所有没有处理的消息, 每个消息会调用放入消息时候的cleanup函数.
     *  @param [in] handler  存放AMHandler句柄
     *  @return 错误码
    */
    ADAPTER_API AMInt32 AMHandlerClose(struct AMHandler* handler);
    /** @brief 发送一条及时消息, 发送成功之后, 会回调callback函数, 处理这个消息.
     *  @param [in] handler  存放AMHandler句柄
     *  @param [in] msg  消息
     *  @return 错误码
    */
    ADAPTER_API AMInt32 AMHandlerSendMsg(struct AMHandler* handler, struct AMMessage* msg);
    /** @brief 发送一个延时消息到handler.
     *  @param [in] handler  存放AMHandler句柄
     *  @param [in] msg  消息
     *  @param [in] tm  延时时间, 到了这个时间, 会回调callback函数, 处理这个消息.
     *  @return 错误码
    */
    ADAPTER_API AMInt32 AMHandlerSendMsgAfterTime(struct AMHandler* handler, 
        struct AMMessage* msg, struct AMTimeval* tm);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif

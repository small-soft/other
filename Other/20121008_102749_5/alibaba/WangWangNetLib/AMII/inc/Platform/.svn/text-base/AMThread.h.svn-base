/*
* AMThread.h
*
*  Created on: 2009-11-17
*      Author: qinghua.liqh
*/

#ifndef _AM_THREAD_H_
#define _AM_THREAD_H_
/*
 * @defgroup 线程定义模块, AMII层只能使用本模块定义的线程
 * @{
 */
 
#include "AMThreadConfig.h"
/** 线程优先级, 目前只定义6个 */
enum 	
{
    AM_THREAD_NORMAL,			/**< 一般 */
    AM_THREAD_ABOVE_NORMAL,	    /**< 高 */
    AM_THREAD_BELOEW_NORMAL,    /**< 低 */
    AM_THREAD_HIGHEST,          /**< 最高 */
    AM_THREAD_LOWEST,           /**< 最低 */
    AM_THREAD_REALTIME,         /**< 实时 */
};

typedef AMPVoid AMThread;              /**< 线程句柄 */
typedef AMPVoid AMThreadAttr;          /**< 线程属性句柄 */

#ifdef __cplusplus 
extern "C" {
#endif
    //属性设置, 可分别设置堆栈大小, 堆栈地址, 和线程优先级
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrCreate (AMThreadAttr* attr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrDestroy (AMThreadAttr * attr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackAddr (const AMThreadAttr* attr, AMPVoid*  stackaddr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackSize (const AMThreadAttr* attr, AMUInt32* stacksize);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetPrority (const AMThreadAttr* attr, AMInt32* prority);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackAddr (AMThreadAttr * attr, AMPVoid stackaddr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackSize (AMThreadAttr * attr, AMUInt32 stacksize);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetPrority (AMThreadAttr* attr, AMInt32 prority);

	/**  @brief 创建线程, 创建的线程之后,  线程就会自动执行.
	  *  @param [out]  tid 线程句柄
	  *  @param [in]  attr 线程属性, 可以为空, 空则用默认.
	  *  @param [in]  start 线程执行函数, 不可以为空
	  *  @param [in]  arg 线程执行函数传入的参数.  可以为空
	  *  @return  错误码..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCreate (AMThread * tid, const AMThreadAttr * attr, 
        AMPVoid (*start) (AMPVoid), AMPVoid arg);
	/**  @brief 告诉线程结束的时候自己回收资源, 不建议使用
	  *  @param [in]  tid. 线程句柄
	  *  @return  错误码..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadDetach (AMThread tid);
    /**  @brief 等待该线程结束,并回收资源, 
	  *  @param [in]  thread线程句柄
	  *  @param [in]  value_ptr 参数value_ptr是该线程的返回结果, 目前不支持, 传入NULL.
	  *  @return  错误码..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadWait   (AMThread thread, AMPVoid* value_ptr);
    /**  @brief 关闭自己.
	  *  @param [in]  value_ptr 参数value_ptr是该线程的返回结果, 目前不支持, 传入NULL.
	  *  @return  错误码..
	*/
	AMTHREAD_DLL_EXPORT AMVoid  AMThreadExit (AMPVoid value_ptr);
    //关闭其它线程
    //AMTHREAD_DLL_EXPORT AMInt32 AMThreadKill  (AMThread thread);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif /* _AM_THREAD_H_ */

/*
 * AMThreadCond.h
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */

#ifndef _AM_THREAD_COND_H_
#define _AM_THREAD_COND_H_
/*
 * @defgroup 条件变量定义模块
 * @{
 */
#include "AMThreadConfig.h"
#include "AMThreadMutex.h"
#include "AMTime.h"

typedef AMPVoid AMThreadCond;       /**< 条件变量句柄 */

#ifdef __cplusplus 
extern "C" {
#endif
	/**  @brief 创建一个条件变量.
	  *  @param [out]  cond 存储cond句柄
	  *  @return  错误码..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondCreate (AMThreadCond * cond);
	/**  @brief 销毁一个条件变量.
	  *  @param [in]  cond 句柄
	  *  @return  错误码..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondDestroy (AMThreadCond * cond);
	/**  @brief 等待条件.
	  *  @param [in]  cond 句柄
	  *  @param [in]  mutex 对应的Mutex句柄
	  *  @return  错误码..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondWait (AMThreadCond * cond, AMThreadMutex * mutex);
#ifdef AMTHREAD_COND_SUPPORT_TIMEWAIT
	/**  @brief 超时等待条件.
	  *  @param [in]  cond 句柄
	  *  @param [in]  mutex 对应的Mutex句柄
	  *  @param [in]  abstime 等待的最大时间,.
	  *  @return  错误码, 如果AME_COND_TIMEOUT表示超时返回.
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondTimewait (AMThreadCond * cond,
        AMThreadMutex * mutex, const struct AMTimeval *abstime);
#endif
	/**  @brief 通知条件.
	  *  @param [in]  cond 句柄
	  *  @return  错误码
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondSignal (AMThreadCond * cond);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif /* ATHREAD_COND_H_ */

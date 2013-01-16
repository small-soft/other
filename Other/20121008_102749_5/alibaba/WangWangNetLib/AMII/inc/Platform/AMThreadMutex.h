/*
* AMThreadMutex.h
*
*  Created on: 2009-11-16
*      Author: qinghua.liqh
*/

#ifndef _AM_THREAD_MUTEX_H_
#define _AM_THREAD_MUTEX_H_
/*
 * @defgroup 同步锁模块, 不允许同线程多次加锁(这个是Team Review结果, 我的观点是可以多加加锁)
 * @{
 */
#include "AMThreadConfig.h"

typedef AMPVoid AMThreadMutex;     /**< mutex句柄 */

#ifdef __cplusplus 
extern "C" {
#endif
	/**  @brief 创建一个同步锁.
	  *  @param [out]  mutex 存储mutex句柄
	  *  @return  错误码..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexCreate (AMThreadMutex * mutex);
	/**  @brief 销毁一个同步锁.
	  *  @param [in]  mutex 存储mutex句柄
	  *  @return  错误码..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexDestroy (AMThreadMutex * mutex);
	/**  @brief 锁定同步锁.
	  *  @param [in]  mutex 存储mutex句柄
	  *  @return  错误码..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexLock (AMThreadMutex * mutex);

#ifdef AMTHREAD_MUTEX_SUPPORT_TRY_LOCK
	/**  @brief 尝试锁定同步锁.
	  *  @param [in]  mutex 存储mutex句柄
	  *  @return  错误码, AME_MUTEX_BUSY表示正在锁定.
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexTryLock (AMThreadMutex * mutex);
#endif
	/**  @brief 解锁同步锁.
	  *  @param [in]  mutex 存储mutex句柄
	  *  @return  错误码..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexUnlock (AMThreadMutex * mutex);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif /* _AM_THREAD_MUTEX_H_ */

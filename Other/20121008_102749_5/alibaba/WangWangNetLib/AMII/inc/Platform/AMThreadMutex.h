/*
* AMThreadMutex.h
*
*  Created on: 2009-11-16
*      Author: qinghua.liqh
*/

#ifndef _AM_THREAD_MUTEX_H_
#define _AM_THREAD_MUTEX_H_
/*
 * @defgroup ͬ����ģ��, ������ͬ�̶߳�μ���(�����Team Review���, �ҵĹ۵��ǿ��Զ�Ӽ���)
 * @{
 */
#include "AMThreadConfig.h"

typedef AMPVoid AMThreadMutex;     /**< mutex��� */

#ifdef __cplusplus 
extern "C" {
#endif
	/**  @brief ����һ��ͬ����.
	  *  @param [out]  mutex �洢mutex���
	  *  @return  ������..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexCreate (AMThreadMutex * mutex);
	/**  @brief ����һ��ͬ����.
	  *  @param [in]  mutex �洢mutex���
	  *  @return  ������..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexDestroy (AMThreadMutex * mutex);
	/**  @brief ����ͬ����.
	  *  @param [in]  mutex �洢mutex���
	  *  @return  ������..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexLock (AMThreadMutex * mutex);

#ifdef AMTHREAD_MUTEX_SUPPORT_TRY_LOCK
	/**  @brief ��������ͬ����.
	  *  @param [in]  mutex �洢mutex���
	  *  @return  ������, AME_MUTEX_BUSY��ʾ��������.
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexTryLock (AMThreadMutex * mutex);
#endif
	/**  @brief ����ͬ����.
	  *  @param [in]  mutex �洢mutex���
	  *  @return  ������..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexUnlock (AMThreadMutex * mutex);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif /* _AM_THREAD_MUTEX_H_ */

/*
 * AMThreadCond.h
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */

#ifndef _AM_THREAD_COND_H_
#define _AM_THREAD_COND_H_
/*
 * @defgroup ������������ģ��
 * @{
 */
#include "AMThreadConfig.h"
#include "AMThreadMutex.h"
#include "AMTime.h"

typedef AMPVoid AMThreadCond;       /**< ����������� */

#ifdef __cplusplus 
extern "C" {
#endif
	/**  @brief ����һ����������.
	  *  @param [out]  cond �洢cond���
	  *  @return  ������..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondCreate (AMThreadCond * cond);
	/**  @brief ����һ����������.
	  *  @param [in]  cond ���
	  *  @return  ������..
	*/	
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondDestroy (AMThreadCond * cond);
	/**  @brief �ȴ�����.
	  *  @param [in]  cond ���
	  *  @param [in]  mutex ��Ӧ��Mutex���
	  *  @return  ������..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondWait (AMThreadCond * cond, AMThreadMutex * mutex);
#ifdef AMTHREAD_COND_SUPPORT_TIMEWAIT
	/**  @brief ��ʱ�ȴ�����.
	  *  @param [in]  cond ���
	  *  @param [in]  mutex ��Ӧ��Mutex���
	  *  @param [in]  abstime �ȴ������ʱ��,.
	  *  @return  ������, ���AME_COND_TIMEOUT��ʾ��ʱ����.
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondTimewait (AMThreadCond * cond,
        AMThreadMutex * mutex, const struct AMTimeval *abstime);
#endif
	/**  @brief ֪ͨ����.
	  *  @param [in]  cond ���
	  *  @return  ������
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondSignal (AMThreadCond * cond);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif /* ATHREAD_COND_H_ */

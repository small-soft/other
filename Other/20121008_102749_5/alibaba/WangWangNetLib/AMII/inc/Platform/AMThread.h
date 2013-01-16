/*
* AMThread.h
*
*  Created on: 2009-11-17
*      Author: qinghua.liqh
*/

#ifndef _AM_THREAD_H_
#define _AM_THREAD_H_
/*
 * @defgroup �̶߳���ģ��, AMII��ֻ��ʹ�ñ�ģ�鶨����߳�
 * @{
 */
 
#include "AMThreadConfig.h"
/** �߳����ȼ�, Ŀǰֻ����6�� */
enum 	
{
    AM_THREAD_NORMAL,			/**< һ�� */
    AM_THREAD_ABOVE_NORMAL,	    /**< �� */
    AM_THREAD_BELOEW_NORMAL,    /**< �� */
    AM_THREAD_HIGHEST,          /**< ��� */
    AM_THREAD_LOWEST,           /**< ��� */
    AM_THREAD_REALTIME,         /**< ʵʱ */
};

typedef AMPVoid AMThread;              /**< �߳̾�� */
typedef AMPVoid AMThreadAttr;          /**< �߳����Ծ�� */

#ifdef __cplusplus 
extern "C" {
#endif
    //��������, �ɷֱ����ö�ջ��С, ��ջ��ַ, ���߳����ȼ�
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrCreate (AMThreadAttr* attr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrDestroy (AMThreadAttr * attr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackAddr (const AMThreadAttr* attr, AMPVoid*  stackaddr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackSize (const AMThreadAttr* attr, AMUInt32* stacksize);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetPrority (const AMThreadAttr* attr, AMInt32* prority);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackAddr (AMThreadAttr * attr, AMPVoid stackaddr);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackSize (AMThreadAttr * attr, AMUInt32 stacksize);
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetPrority (AMThreadAttr* attr, AMInt32 prority);

	/**  @brief �����߳�, �������߳�֮��,  �߳̾ͻ��Զ�ִ��.
	  *  @param [out]  tid �߳̾��
	  *  @param [in]  attr �߳�����, ����Ϊ��, ������Ĭ��.
	  *  @param [in]  start �߳�ִ�к���, ������Ϊ��
	  *  @param [in]  arg �߳�ִ�к�������Ĳ���.  ����Ϊ��
	  *  @return  ������..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadCreate (AMThread * tid, const AMThreadAttr * attr, 
        AMPVoid (*start) (AMPVoid), AMPVoid arg);
	/**  @brief �����߳̽�����ʱ���Լ�������Դ, ������ʹ��
	  *  @param [in]  tid. �߳̾��
	  *  @return  ������..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadDetach (AMThread tid);
    /**  @brief �ȴ����߳̽���,��������Դ, 
	  *  @param [in]  thread�߳̾��
	  *  @param [in]  value_ptr ����value_ptr�Ǹ��̵߳ķ��ؽ��, Ŀǰ��֧��, ����NULL.
	  *  @return  ������..
	*/
    AMTHREAD_DLL_EXPORT AMInt32 AMThreadWait   (AMThread thread, AMPVoid* value_ptr);
    /**  @brief �ر��Լ�.
	  *  @param [in]  value_ptr ����value_ptr�Ǹ��̵߳ķ��ؽ��, Ŀǰ��֧��, ����NULL.
	  *  @return  ������..
	*/
	AMTHREAD_DLL_EXPORT AMVoid  AMThreadExit (AMPVoid value_ptr);
    //�ر������߳�
    //AMTHREAD_DLL_EXPORT AMInt32 AMThreadKill  (AMThread thread);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif /* _AM_THREAD_H_ */

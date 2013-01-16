#ifndef _AME_LOOPER_MESSAGE_
#define _AME_LOOPER_MESSAGE_
/*
 * @defgroup AMMessageģ��
 * @{
 */
#include "AMLooperConfig.h"
#include "AMTime.h"

struct AMHandler;
struct AMMessage;

/** @brief ��Ϣ������, �Է��͸�Handler����Ϣ, ������������ƺ�
 *  @param [in]  message ��Ϣ����.
 *  @return ��.
*/
typedef AMVoid(*AMMessageCleanUp)(struct AMMessage* message);

/** ��Ϣ���õ���ֵ���� */
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

/** ��Ϣ���õ����������� */
typedef union a_ref
{
	AMPVoid	 ptr;
	AMInt8*	 sptr;

}a_ref;

typedef enum 
{
	AM_MESSAGE_NORMAL  =  0,	/** < һ����Ϣ   */
	AM_MESSAGE_TIMER,			/** < ��ʱ����Ϣ  */
}AMMsgType;

/** ��Ϣ�ṹ�� ע�⣺ v1�� v2�� ref1��ref2Ϊ�û�����ֱ��ʹ�õ��ֶ� �����ֶ��û�����ʹ��*/
struct AMMessage
{
	//�����ĸ�Ϊ�û�ʹ���ֶ�
	a_value	v1;						/** < ֵ1 */
	a_value	v2;						/** < ֵ2 */
	a_value	v3;						/** < ֵ3 */
	a_value	v4;						/** < ֵ4*/
	a_ref		ref1;				/** < ����1 */
	a_ref		ref2;				/** < ����2 */

	//ע��: �����ֶ��û�����ֱ��ʹ��
	AMMsgType type;					/** < ��Ϣ����,��ʾ��Ϣ����ʲô����, ��	*/
	struct AMHandler* handler;		/** < ���ڵ�Handler*/
    AMMessageCleanUp    cleanUp;    /** < ��û�д������Ϣ, ��������������� */
	struct AMTimeval run_tm;		/** < ���е�ʱ��. */
};

#ifdef __cplusplus 
extern "C" {
#endif

    /** @brief ����һ����Ϣ
     *  @param [in]  message ��Ϣ����.
     *  @param [in]  cleanUp �ƺ���, ����յ�ʱ��, ��ʾ�����ƺ���.
     *  @return: �ɹ�: AME_LOOPER_SCUESS; ʧ�� (AME_LOOPER_MESSAGE_NULL : message��Ч;)
    */	
    ADAPTER_API AMInt32 AMMessageInit(struct AMMessage* message, AMMessageCleanUp cleanUp);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif

#ifndef IM_NET_PACKET_H
#define IM_NET_PACKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "IMnetUtility.h"
#include "IMnetMain.h"

	/************************************************************************/
	// ��������: �ú��������Է��͵��������˵�������д��
	// ��������:
	//		Event* pEvt		: ��Ҫ�������Ϣ
	//		char** ppBuffer	: ��������Ϣ��ָ��,
	//						  �������贫��һ��ָ������¼��,�ռ�����ɸú������
	//		AMInt32* pLength	: ��¼��������Ϣ�峤��,�������贫��һ��ָ������¼��
	/************************************************************************/
	IMnetRetCode IMnetPack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength); 

	/************************************************************************/
	// ��������: �ú��������Դӷ��������յ�����Ϣ���н��
	// ��������:
	//		Event** ppEvt	: ��������Ϣ�ø�ָ���¼,
	//						  ��������Ҫ����һ��ָ������¼��,
	//						  �ռ�����ɸú������.
	//		EventId cmd		: ��Ϣ��ID
	//		char* pBuffer	: ���������Ϣ��
	//		AMInt32 Length		: ���������Ϣ�峤��
	/************************************************************************/
	IMnetRetCode IMnetUnpack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length); 


	/*
	 *	
	 */
	IMnetRetCode CheckCC(AMUInt8* byteBuffer, AMInt32 iPos, AMInt32 extLength, AMInt32 bodyLength);
	/*
	 *	
	 */

	IMnetRetCode FtsPackAllocate( FtsPacketHead* pHead, AMUInt8** ppBuffer, 
									AMInt32 *pLength, AMInt32 bodyLength);
	void		FtsHeadInit(FtsPacketHead *pHead);
	AMUInt8 *	FtsPackHead(AMUInt8 *pBufferTemp, FtsPacketHead *pHead);
	void		FtsResetHead(AMUInt8* pBuffer, AMInt32 bodyLength);

	IMnetRetCode FtsUnpackHeadAndCheck( AMUInt8* pBuffer, 
										AMUInt8** ppBufferTemp, 
										FtsPacketHead* pHead);

	AMUInt8* FtsUnpackHead(AMUInt8* pBufferTemp, FtsPacketHead* pHead);

#ifdef __cplusplus
} /* End of the 'extern "C"' block */
#endif

#endif


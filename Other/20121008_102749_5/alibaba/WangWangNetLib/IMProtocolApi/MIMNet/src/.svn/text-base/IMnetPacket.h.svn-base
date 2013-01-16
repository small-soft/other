#ifndef IM_NET_PACKET_H
#define IM_NET_PACKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "IMnetUtility.h"
#include "IMnetMain.h"

	/************************************************************************/
	// 功能描述: 该函数用来对发送到服务器端的命令进行打包
	// 参数描述:
	//		Event* pEvt		: 需要打包的消息
	//		char** ppBuffer	: 打包后的消息体指针,
	//						  调用者需传入一个指针来记录它,空间分配由该函数完成
	//		AMInt32* pLength	: 记录打包后的消息体长度,调用者需传入一个指针来记录它
	/************************************************************************/
	IMnetRetCode IMnetPack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength); 

	/************************************************************************/
	// 功能描述: 该函数用来对从服务器端收到的消息进行解包
	// 参数描述:
	//		Event** ppEvt	: 解包后的消息用该指针记录,
	//						  调用者需要传入一个指针来记录它,
	//						  空间分配由该函数完成.
	//		EventId cmd		: 消息的ID
	//		char* pBuffer	: 待解包的消息体
	//		AMInt32 Length		: 待解包的消息体长度
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


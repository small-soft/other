#ifndef IM_NET_UTILITY_H
#define IM_NET_UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "PCUtility.h"
#include "IMnetStruct.h"

	AMUInt8 GetLRC(AMUInt8* buf, AMInt32 pos, AMInt32 length) ;
	AMInt16 GetCC(AMUInt8* buf, AMInt32 pos, AMInt32 length); 

	void SkipPropertyNum(AMUInt8** ppbuffer, AMInt32 n);

	void MakeImMessageTextPacket(SecondProtocolId cmdID, 
		AMChar* pInMessage, 
		AMInt32 inMessageLen, 
		AMInt32 ackSeq);

	void XMLStringToMessageXML(AMChar* pSrc, AMInt32 srcLen, MessageXML* msgXML);
	void FreeMessageXml(MessageXML* pxml);

	void MakeXMLString(AMChar** ppDstStr, AMInt32* pDstStrLen, 
		AMChar* userName, AMInt32 userNameLen,
		AMChar* toID, AMInt32 toIDLen,
		AMInt32 groupIDHigh, AMInt32 groupIDLow,  
		AMChar* verifiMsg, AMInt32 verifyMsgLen,
		AMChar* displayName, AMInt32 displayNameLen,
		AMInt32 result);
	void FreeXMLString(AMChar** ppStr);

	
#ifdef __cplusplus
}
#endif


#endif

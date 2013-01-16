#include "IMnetPacket.h"
#include "IMnetMain.h"
#include "stdio.h"
#include "IMnetUtility.h"
#include "IMnetStruct.h"

#ifdef _GET_SIGNATURE_
#include "ghttp.h"
#include <string.h>
#include "AMOS.h"
#include "des.h"
#include <stdlib.h>
#endif // _GET_SIGNATURE_

/************************************************************************/
// struct declare
/************************************************************************/
//denx:不用做Property检查
#define IMnetCheckPropertyNum(a, b) 
/*
#define IMnetCheckPropertyNum(a, b) \
	if((a) != (b)) \
	{ \
		UncompressBodyEnd(pNewBuffer); \
		return eIMnetPropertyError;	   \
	}
*/
#define RSP_ADD_BIND_UID(header, rsp)\
	if(head.extData && head.extLength > 0)\
	{/*by pw 2011-7-19; binding account id;*/\
		rsp.bindIDLen = head.extLength;\
		rsp.bindID = (AMChar *)AMMalloc(rsp.bindIDLen + 1);\
		AMAssert(0 != rsp.bindID);\
		AMMemcpy(rsp.bindID, head.extData, rsp.bindIDLen);\
		rsp.bindID[rsp.bindIDLen] = 0;\
	}

#define PACKER_PARAM	IMnet* pIMnet, Event* pEvt, AMUInt8** pBuffer, AMInt32* pLength
#define UNPACKER_PARAM  IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length
typedef IMnetRetCode (*Packer)(PACKER_PARAM);
typedef IMnetRetCode (*Unpacker)(UNPACKER_PARAM);

typedef struct {
	EventId			id;
	Packer			packer;
#ifdef AMOS_DEBUG
	AMChar*			packerName;
#endif
}PackMap;

typedef struct {
	EventId			id;
	Unpacker		unpacker;
#ifdef AMOS_DEBUG
	AMChar*			unpackerName;
#endif
}UnpackMap;

/************************************************************************/
// static function declare
/************************************************************************/
#undef MACRO_DEF_SECOND_PROTOCOL
#define MACRO_DEF_SECOND_PROTOCOL(id, value)
#undef MACRO_DEF_EXTERN
#define MACRO_DEF_EXTERN(id, value, structDef)
#undef MACRO_DEF
#define MACRO_DEF(id,  value, structDef)

#undef MACRO_DEFS
#define MACRO_DEFS(id, value, structDef) static IMnetRetCode Pack##structDef(PACKER_PARAM);
#undef MACRO_DEFR
#define MACRO_DEFR(id, value, structDef) static IMnetRetCode Unpack##structDef(UNPACKER_PARAM);
#include "IMnetEventDef.h"

/************************************************************************/
// PackMap
/************************************************************************/
#define FUNC_STRING_DEF(str) #str
const static PackMap gPackMap[] = {
	#undef MACRO_DEFS
#ifdef AMOS_DEBUG
	#define MACRO_DEFS(id, value, structDef) {value, Pack##structDef, FUNC_STRING_DEF(Pack##structDef)},
#else
	#define MACRO_DEFS(id, value, structDef) {value, Pack##structDef},
#endif
	#undef MACRO_DEFR
	#define MACRO_DEFR(id, value, structDef)
	#include "IMnetEventDef.h"
};

/************************************************************************/
// UnpackMap
/************************************************************************/
const static UnpackMap gUnpackMap[] = {
	#undef MACRO_DEFS
	#define MACRO_DEFS(id, value, structDef)
	#undef MACRO_DEFR
#ifdef AMOS_DEBUG
	#define MACRO_DEFR(id, value, structDef) {value, Unpack##structDef, FUNC_STRING_DEF(Unpack##structDef)},
#else
	#define MACRO_DEFR(id, value, structDef) {value, Unpack##structDef},
#endif
	#include "IMnetEventDef.h"
};

/************************************************************************/
// local static function declare.
/************************************************************************/
//-------------------------------------------------------------------------------------------------
static IMnetRetCode UnpackHeadAndCheckProcedure( IMnet* pIMnet, 
										 AMUInt8* pBuffer, 
										 AMUInt8** ppBufferTemp, 
										 PacketHead* pHead);
static IMnetRetCode CheckStarterAndLrc(AMUInt8* byteBuffer);
static void HeadInit(PacketHead* pHead);
static IMnetRetCode PackAllocate( PacketHead* pHead, AMUInt8** ppBuffer, 
						  AMInt32 *pLength, short reserved, 
						  char* pExtData, AMInt32 extDataLen, 
						  AMInt32 bodyLength);
static AMUInt8* PackHead(AMUInt8* pBufferTemp, PacketHead* pHead);
static void ResetHead(AMUInt8* pBuffer, AMInt32 extLength, AMInt32 bodyLength);
static AMUInt8* UnpackHead(AMUInt8* pBuffer, PacketHead* pHead);
static IMnetRetCode UncompressBodyBegin(IMnet* pIMnet,
								 AMUInt8* pBufferRoot, 
								 AMUInt8** ppBuffer, 
								 PacketHead* pHead, 
								 AMUInt8** ppNewBuffer);
static void UncompressBodyEnd(AMUInt8* pbuffer);
//flag == 1: encrypt; flag == 0: decrypt;
static IMnetRetCode EncryptBody(IMnet* pIMnet, AMUInt8* pBuffer, AMInt32 extLength, 
						 AMInt32 bodyLength, AMInt32 encrypt, EncryptType flag);

IMnetRetCode CheckCC(AMUInt8* byteBuffer, AMInt32 iPos, AMInt32 extLength, AMInt32 bodyLength);
static IMnetRetCode UnpackImRspCommonContactList(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length);
static IMnetRetCode UnpackImMessageText(AMUInt8*  pBuffer, 
								 AMInt32   bufferLen,
								 ImMessageChildHead* pHead, 
								 AMUInt8** ppUnpackBuffer,
								 AMInt32*  pUnpackBufferLen);

static IMnetRetCode UnpackImMessageText_Sub(AMUInt8*  pBuffer, 
									 AMInt32   bufferLen,
									 AMUInt8** ppUnpackBuffer,
									 AMInt32*  pUnpackBufferLen);

//-------------------------------------------------------------------------------------------------

/************************************************************************/
// 功能描述: 该函数用来对发送到服务器端的命令进行打包
// 参数描述:
//		Event* pEvt		: 需要打包的消息
//		char** ppBuffer	: 打包后的消息体指针,
//						  调用者需传入一个指针来记录它,空间分配由该函数完成
//		AMInt32* pLength: 记录打包后的消息体长度,调用者需传入一个指针来记录它
/************************************************************************/
IMnetRetCode IMnetPack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	AMInt32 i;
	IMnetRetCode retCode;

	if(pIMnet == NULL || pEvt == NULL || ppBuffer == NULL || pLength == NULL)
		return eInvalidParam;

	for(i=0; i<sizeof(gPackMap)/sizeof(gPackMap[0]); i++)
	{
		if(gPackMap[i].id == pEvt->id)
		{
#ifdef AMOS_DEBUG
			AMPrintf("noble:packing Req: %s\n",gPackMap[i].packerName);
#endif
			retCode = gPackMap[i].packer(pIMnet, pEvt, ppBuffer, pLength);

#ifdef AMOS_DEBUG
			if(retCode == eIMnetUnsupportedFeature)
				AMPrintf( "noble:Request ID(unsupport, coming soon...): 0x%x\n", pEvt->id);
#endif
			return retCode;
		}
	}

#ifdef AMOS_DEBUG
	AMPrintf( "noble:Request ID is invalid: 0x%x\n",pEvt->id);
#endif
	return eIMnetInvalidCmd;
}

/************************************************************************/
// 功能描述: 该函数用来对从服务器端收到的消息进行解包
// 参数描述:
//		Event** ppEvt	: 解包后的消息用该指针记录,
//						  调用者需要传入一个指针来记录它,
//						  空间分配由该函数完成.
//		EventId cmd		: 消息的ID
//		char* pBuffer	: 待解包的消息体
//		AMInt32 Length	: 待解包的消息体长度
/************************************************************************/
IMnetRetCode IMnetUnpack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	AMInt32 i;
	IMnetRetCode retCode;

#ifdef AMOS_DEBUG
	AMPrintf( "IMnetUnpack: EventId = %d", cmd);
#endif

	if(pIMnet == NULL || ppEvt == NULL || pBuffer == NULL || Length == 0)
	{
		return eInvalidParam;
	}

	for(i=0; i<sizeof(gUnpackMap)/sizeof(gUnpackMap[0]); i++)
	{
		if(gUnpackMap[i].id == cmd)
		{
#ifdef AMOS_DEBUG
			AMPrintf( "noble:unpacking Rsp: %s\n",gUnpackMap[i].unpackerName);
#endif
			retCode = gUnpackMap[i].unpacker(pIMnet, ppEvt, cmd, pBuffer, Length);

#ifdef AMOS_DEBUG
			if(retCode == eIMnetUnsupportedFeature)
				AMPrintf( "noble:response ID(unsupport, coming soon...): 0x%x\n", cmd);
#endif
			return retCode;
		}
	}

#ifdef AMOS_DEBUG
	AMPrintf( "noble:Received ID is invalid: 0x%x\n",cmd);
#endif
	return eIMnetInvalidCmd;
}

/************************************************************************/
// IMnetPackRelease
/************************************************************************/
void IMnetPackRelease(AMUInt8* pBuffer)
{
	if(pBuffer)
	{
		AMFree(pBuffer);
	}
}

/************************************************************************/
//pack handlers
/************************************************************************/
IMnetRetCode PackImReqCommonSimple(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMUInt8* pBufferTemp = NULL;
	ImReqCommonSimple* pRequest = (ImReqCommonSimple*)(pEvt->pContent);

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 
	//ImReqHealthCheck not need Encrypt
	head.encrypt = PROTOCOL_HEAD_NO_ENCRYPT;  

	//
	//2. alloc buffer
	//
	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, 0);
	if( retCode != eOK )
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = PackHead(*ppBuffer, &head);

	//
	//4. pack body
	//
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqHealthCheck
/************************************************************************/
IMnetRetCode PackImReqHealthCheck(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return PackImReqCommonSimple(pIMnet, pEvt, ppBuffer, pLength);
}

/************************************************************************/
// PackImReqLogoff
/************************************************************************/
IMnetRetCode PackImReqLogoff(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return PackImReqCommonSimple(pIMnet, pEvt, ppBuffer, pLength);
}

/************************************************************************/
// PackImReqCheckVersion
/************************************************************************/
IMnetRetCode PackImReqCheckVersion(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	AMInt32 bodyLength = 0;
	PacketHead head;
	AMUInt8* pBufferTemp = NULL;
	ImReqCheckVersion* pReqCheckVersion = (ImReqCheckVersion*)(pEvt->pContent);

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 
	//CheckVersion not need Encrypt
	head.encrypt = PROTOCOL_HEAD_NO_ENCRYPT;  
	
	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength = 6 + strlen(pReqCheckVersion->version);
	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if( retCode != eOK )
    {
        return retCode;
    }

	//
	//3. pack head.
	//
	pBufferTemp = PackHead(*ppBuffer, &head);

	//
	//4. pack body
	//
	pReqCheckVersion->propertyNum = 1;
	if(pReqCheckVersion->propertyNum != 0)
		putByte(pBufferTemp, pReqCheckVersion->propertyNum);
	putSctString(pBufferTemp, pReqCheckVersion->version, strlen(pReqCheckVersion->version));
    
	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);
	
	//
	//6. EncryptBody
	//
	retCode =  EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
    return retCode;
}

/************************************************************************/
// PackImReqLogin
/************************************************************************/
IMnetRetCode PackImReqLogin(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	ImPackLoginInd indPackLogin;
	Event* pEvent = NULL;
	AMInt32 bodyLength = 0;
	PacketHead head;
	AMUInt8* pBufferTemp = NULL;
	ImReqLogin* pReqLogin = (ImReqLogin*)pEvt->pContent;
	AMInt32 i,size;

	pIMnet->pVarKeeper->bHasWorkKey = AMFALSE;
	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 50 + strlen(pReqLogin->password);
	bodyLength += strlen(pReqLogin->version);
	bodyLength += sizeof(pReqLogin->timestampList);
	// denx : hardcode,hardcheck 做什么用的,为什么都是0??
	bodyLength += 0; //hardcode
	bodyLength += 0; //hardcheck
	bodyLength += strlen(pReqLogin->rid);

	retCode = PackAllocate( &head, ppBuffer, pLength, pReqLogin->reserved, 
							pReqLogin->extData, strlen(pReqLogin->extData), 
                            bodyLength);
	if(retCode != eOK)
    {
        return retCode;
    }

	//
	//3. pack head.
	//
	pBufferTemp = PackHead(*ppBuffer, &head);

	//
	//4. pack body
	//
	pReqLogin->propertyNum = 10;
	if(pReqLogin->propertyNum != 0)
		putByte(pBufferTemp, pReqLogin->propertyNum);	
	putSctByte(pBufferTemp, pReqLogin->tokenFlag);
	putSctInt(pBufferTemp, pReqLogin->connectNo);
	putSctString(pBufferTemp, pReqLogin->password, strlen(pReqLogin->password));
	putSctString(pBufferTemp, pReqLogin->version, strlen(pReqLogin->version));
	putSctInt(pBufferTemp, pReqLogin->language);
	putSctInt(pBufferTemp, pReqLogin->timestampFlag);
	size = sizeof(pReqLogin->timestampList)/sizeof(AMInt32);
	putVectorInt(pBufferTemp, pReqLogin->timestampList, size);
	size = pReqLogin->hardCodeCount;
	putVectorStr(pBufferTemp, pReqLogin->hardcode, size);
	putSctString(pBufferTemp, pReqLogin->hardcheck, strlen(pReqLogin->hardcheck));
    putSctString(pBufferTemp, pReqLogin->rid, strlen(pReqLogin->rid));
	
	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	retCode = EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
	if(retCode == eOK)
	{
		// 构造ImPackLoginInd
		memset(&indPackLogin, 0, sizeof(indPackLogin));
		indPackLogin.connectNo = pReqLogin->connectNo;

        indPackLogin.loginBlock = (AMUInt8*)AMMalloc(*pLength);
        if(indPackLogin.loginBlock == 0)
        {
            AMAssert(0);
            retCode = eMallocError;
        }
        else
        {
            //此块内存会被重新带到协议层后释放掉,故用EventCreate,而不用EventCreateEx.
		    memcpy(indPackLogin.loginBlock, *ppBuffer, *pLength);
		    indPackLogin.loginBlockLen = *pLength;

		    //EventCreate(&pEvent, IM_PACK_LOGIN_IND, (void*)&indPackLogin, sizeof(indPackLogin));
		    //IMnetPostMessage(pIMnet, pEvent, IMnetCallbackQueue);

			EventCreate(pIMnet->hPCHandle, &pEvent, IM_PACK_LOGIN_IND, (void*)&indPackLogin, sizeof(indPackLogin));
			PacketConnectionSendtoCallback(pEvent);
        }
	}

	return retCode;
}

/************************************************************************/
// PackImReqPreLogin
/************************************************************************/
IMnetRetCode PackImReqPreLogin(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqPreLogin* pReqPreLogin = (ImReqPreLogin*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 
	head.encrypt = PROTOCOL_HEAD_NO_ENCRYPT;

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength += 16 + strlen((AMChar*)pReqPreLogin->workKey);
	bodyLength += pReqPreLogin->loginBlockLen;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
    {
        return retCode;
    }

	//
	//3. pack head.
	//
	pBufferTemp = PackHead(*ppBuffer, &head);

	//
	//4. pack body
	//
	pReqPreLogin->propertyNum = 3;
	if(pReqPreLogin->propertyNum != 0)
		putByte(pBufferTemp, pReqPreLogin->propertyNum);	
	putSctInt(pBufferTemp, pReqPreLogin->connectNo);
	putSctString(pBufferTemp, pReqPreLogin->workKey, strlen((AMChar*)pReqPreLogin->workKey));
	putStrByte(pBufferTemp, pReqPreLogin->loginBlock, pReqPreLogin->loginBlockLen);
	
	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqPreLogin
/************************************************************************/
IMnetRetCode PackImReqLogin2(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0, size = 0, i=0;
	AMUInt8* pBufferTemp = NULL;
	ImReqLogin2* pReqLogin2 = (ImReqLogin2*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 
	head.encrypt = PROTOCOL_HEAD_NO_ENCRYPT;

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength += 42 + strlen((AMChar*)pReqLogin2->remark);

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
	{
		return retCode;
	}

	//
	//3. pack head.
	//
	pBufferTemp = PackHead(*ppBuffer, &head);

	//
	//4. pack body
	//
	pReqLogin2->propertyNum = 3;
	if(pReqLogin2->propertyNum != 0)
		putByte(pBufferTemp, pReqLogin2->propertyNum);

	putSctInt(pBufferTemp, pReqLogin2->timestampFlag);
	size = sizeof(pReqLogin2->timestampList)/sizeof(AMInt32);
	putVectorInt(pBufferTemp, pReqLogin2->timestampList, size);

	putSctString(pBufferTemp, pReqLogin2->remark, strlen((AMChar*)pReqLogin2->remark));
	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

static void FreeImRspHelpChangeSrvMode(EventContent* pContent)
{
	ImRspHelpChangeSrvMode* pRspChangeSignature = (ImRspHelpChangeSrvMode*)pContent;
	AMFree(pRspChangeSignature->accountId);
	pRspChangeSignature->accountId = NULL;
}

/************************************************************************/
// UnpackImRspHelpChangeSrvMode
/************************************************************************/
// static IMnetRetCode _UnpackImRspHelpChangeSrvMode(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
// {
// 	return eIMnetUnsupportedFeature
// }


static void FreeImRspLogin2(EventContent* pContent)
{
	ImRspLogin2* pRspLogin2 = (ImRspLogin2*)pContent;

	AMFree(pRspLogin2->remark);
	pRspLogin2->remark = NULL;
}

IMnetRetCode UnpackImRspLogin2(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	if(2 == tempNum)
	{
		ImRspHelpChangeSrvMode rspHelpChangeSrvMode;

		// clear all
		memset(&rspHelpChangeSrvMode, 0, sizeof(rspHelpChangeSrvMode));	

		//
		//0. init propertyNum.
		//
		rspHelpChangeSrvMode.propertyNum = 2;

		IMnetCheckPropertyNum(rspHelpLogin.propertyNum, tempNum);

		getByte(pBufferTemp, tempNum);
		if(FT_STRING != tempNum)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		rspHelpChangeSrvMode.accountId = malloc(64);
		if(!rspHelpChangeSrvMode.accountId)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}
		getString(pBufferTemp, rspHelpChangeSrvMode.accountId, 64);
		rspHelpChangeSrvMode.accountIdLen = strlen(rspHelpChangeSrvMode.accountId);

		retCode = GetSctByte(&pBufferTemp, &rspHelpChangeSrvMode.retCode);
		if(retCode != eOK)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		UncompressBodyEnd(pNewBuffer);

		//4. create event.
		return EventCreateEx(pIMnet->hPCHandle, ppEvt, IM_EVENT_HELP_CHG_SRV_MODE, 
			(void*)&rspHelpChangeSrvMode, sizeof(rspHelpChangeSrvMode), FreeImRspHelpChangeSrvMode);
	}
	else
	{
		ImRspLogin2 rspLogin2;
		// clear all
		memset(&rspLogin2, 0, sizeof(rspLogin2));	
		//
		//0. init propertyNum.
		//
		rspLogin2.propertyNum = 11;

		retCode = GetSctInt(&pBufferTemp, &rspLogin2.retCode);
		if(retCode != eOK)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}
		retCode = GetSctInt(&pBufferTemp, &rspLogin2.timestampFlag);
		if(retCode != eOK)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		retCode = GetSctString(&pBufferTemp, &rspLogin2.remark, &rspLogin2.remarkLen);
		if(retCode != eOK)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}
		UncompressBodyEnd(pNewBuffer);

		//4. create event.
		return EventCreateEx(pIMnet->hPCHandle, ppEvt, IM_EVENT_LOGIN2, 
			(void*)&rspLogin2, sizeof(rspLogin2), FreeImRspLogin2);
	}
}

/************************************************************************/
// PackImReqPostLogin
/************************************************************************/
IMnetRetCode PackImReqPostLogin(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqPostLogin* pReqPostLogin = (ImReqPostLogin*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 5;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, pReqPostLogin->bindID, pReqPostLogin->bindIDLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pReqPostLogin->propertyNum = 2;
	if(pReqPostLogin->propertyNum != 0)
		putByte(pBufferTemp, pReqPostLogin->propertyNum);	
	putSctByte(pBufferTemp, pReqPostLogin->basicStatus);
	putSctByte(pBufferTemp, pReqPostLogin->predefStatus);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqAddBlack
/************************************************************************/
IMnetRetCode PackImReqAddBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqAddBlack* pReqAddBlack = (ImReqAddBlack*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6 + strlen(pReqAddBlack->contactID);

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pReqAddBlack->propertyNum = 1;
	if(pReqAddBlack->propertyNum != 0)
		putByte(pBufferTemp, pReqAddBlack->propertyNum);	
	putSctString(pBufferTemp, pReqAddBlack->contactID, strlen(pReqAddBlack->contactID));

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqGetUserUDBProfile
/************************************************************************/
IMnetRetCode PackImReqGetUserUDBProfile(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetUserUDBProfile* pRequest = (ImReqGetUserUDBProfile*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6 + strlen(pRequest->contactId);

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	
	putSctString(pBufferTemp, pRequest->contactId, strlen(pRequest->contactId));

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqSearchUser
/************************************************************************/
IMnetRetCode PackImReqSearchUser(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{

	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqSearchUser* pRequest = (ImReqSearchUser*)pEvt->pContent;

#ifdef AMOS_DEBUG
	AMPrintf("PackImReqSearchUser() start");
	AMPrintf("PackImReqSearchUser(): pRequest->timeStamp = %d", pRequest->timeStamp);
	AMPrintf("PackImReqSearchUser(): pRequest->searchType = %d", pRequest->searchType);
	AMPrintf("PackImReqSearchUser(): pRequest->keyWord = %s", pRequest->keyWord);
	AMPrintf("PackImReqSearchUser(): pRequest->syncAcc = %d", pRequest->syncAcc);
	AMPrintf("pRequest->reserve = %s", pRequest->reserve);
	AMPrintf("pRequest->reserveLen = %d", pRequest->reserveLen);
#endif

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 1  + 5 + 2 + 5 + strlen(pRequest->keyWord) + 2 + 5 + strlen(pRequest->reserve);

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
	{
		return retCode;
	}

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 5;
	if(pRequest->propertyNum != 0)
	{
		putByte(pBufferTemp, pRequest->propertyNum);	// 1
	}

	putSctInt(pBufferTemp, pRequest->timeStamp); // 1 + 4 = 5
	putSctByte(pBufferTemp, pRequest->searchType); // 1 + 1 = 2
	putSctString(pBufferTemp, pRequest->keyWord, strlen(pRequest->keyWord)); // 1 + 4 + len
	putSctByte(pBufferTemp, pRequest->syncAcc); // 1 + 1 = 2
	putSctString(pBufferTemp, pRequest->reserve, strlen(pRequest->reserve)); // 1 + 4 + len 

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//

	retCode = EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);

#ifdef AMOS_DEBUG
		AMPrintf("KKKK: PackImReqSearchUser() end %d", retCode);
#endif
	
	return retCode;
}


/************************************************************************/
// PackImReqGetBlack
/************************************************************************/
IMnetRetCode PackImReqGetBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// PackImReqChangeUserVerify
/************************************************************************/
IMnetRetCode PackImReqChangeUserVerify(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqChangeUserVerify* pRequest = (ImReqChangeUserVerify*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 7;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, pRequest->bindID, pRequest->bindIDLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 3;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	
	
	putSctByte(pBufferTemp, pRequest->addcontactFlag);
	putSctByte(pBufferTemp, pRequest->sendmsgFlag);
	putSctByte(pBufferTemp, pRequest->enableSearch);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqGetReverseBlack
/************************************************************************/
IMnetRetCode PackImReqGetReverseBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetPeerInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetPeerInfo* pRequest = (ImReqGetPeerInfo*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6 + pRequest->contactIdLen;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctString(pBufferTemp, pRequest->contactId, pRequest->contactIdLen);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqChangeSignature
/************************************************************************/
IMnetRetCode PackImReqChangeSignature(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqChangeSignature* pRequest = (ImReqChangeSignature*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6 + pRequest->signatureLen;
	
	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctString(pBufferTemp, pRequest->signature, pRequest->signatureLen);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqAddOfflineMsg(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetBinding(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqHelpGetShareCID(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqChangePortrait(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetUserInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqUpdateGeneralContact(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqHelpLogin(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqHelpLogin* pRequest = (ImReqHelpLogin*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 68;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 2;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putByte(pBufferTemp, FT_STRING);

	WriteData(&pBufferTemp, pRequest->accountId, pRequest->accountIdLen, 0, 64);

	putSctByte(pBufferTemp, pRequest->status);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqHelpGetOnlineChilds(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetPwdToken(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqCheckAuthCode(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqCheckAuthCode* pRequest = (ImReqCheckAuthCode*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 16 + 1 +  pRequest->uiSessionLen + pRequest->uiCodeLen + 10;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 3;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctString(pBufferTemp, pRequest->szSession, pRequest->uiSessionLen);
	putSctString(pBufferTemp, pRequest->szCode, pRequest->uiCodeLen);
	putSctByte(pBufferTemp, pRequest->uiMode);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImRawPacket(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	ImRawPacket* pRequest = (ImRawPacket*)pEvt->pContent;

	if(1 == pRequest->szPacket[4])
	{
		pRequest->szPacket[7] = 0;
		pRequest->szPacket[4] = 0;
		pRequest->szPacket[7] = GetLRC(pRequest->szPacket, 0, PROTOCOL_HEAD_LENGTH);
	}

	*ppBuffer = pRequest->szPacket;
	pRequest->szPacket = AMNULL;
	*pLength = pRequest->uiPacketLen;

	return eIMnetOK;
}

IMnetRetCode PackImReqChangeContact(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqHelpGetChildOnline(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqDeleteGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetPeerVerifyConfig(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetPeerVerifyConfig* pRequest = (ImReqGetPeerVerifyConfig*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 16 + 1 +  pRequest->contactIdLen;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 3;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctByte(pBufferTemp, pRequest->clientId);
	putSctString(pBufferTemp, pRequest->contactId, pRequest->contactIdLen);
	
	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqChangeGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// PackImReqDeleteBlack
/************************************************************************/
IMnetRetCode PackImReqDeleteBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqDeleteBlack* pRequest = (ImReqDeleteBlack*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 16 + pRequest->blackIdLen;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 3;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctInt(pBufferTemp, pRequest->retCode);
	putSctString(pBufferTemp, pRequest->blackId, pRequest->blackIdLen);
	putSctInt(pBufferTemp, pRequest->timestamp);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqChangeToolsProfile(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqChangeUserDetail(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetContactDetail(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqAddGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetUsersStatus(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// PackImReqAddContact
/************************************************************************/
IMnetRetCode PackImReqAddContact(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqAddContact* pImReqAddContact = (ImReqAddContact*)pEvt->pContent;

#ifdef AMOS_DEBUG
	AMPrintf( "noble:PackImReqAddContact: bindID:%s, cntID:%s\n", pImReqAddContact->bindID ? pImReqAddContact->bindID : "null", pImReqAddContact->contactInfo.contactID);
#endif
	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 4;
	bodyLength += 25; //25为ContactInfo的头size,类似于每个REQ的BodyLength上的第一个常量.
	bodyLength += pImReqAddContact->contactInfo.contactIDLen + 1;
	bodyLength += pImReqAddContact->contactInfo.nickNameLen + 1;
	bodyLength += pImReqAddContact->contactInfo.importanceLen + 1;
	bodyLength += pImReqAddContact->uiMsgLen + 1;
	
	retCode = PackAllocate(&head, ppBuffer, pLength, 0, pImReqAddContact->bindID, pImReqAddContact->bindIDLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pImReqAddContact->propertyNum = 3;
	if(pImReqAddContact->propertyNum != 0)
		putByte(pBufferTemp, pImReqAddContact->propertyNum);	

	putByte(pBufferTemp, FT_STRUCT);
	putByte(pBufferTemp, 4); //定义的propNum = 4并非pImReqAddContact->propertyNum中定义的2.
	putSctString(pBufferTemp, pImReqAddContact->contactInfo.contactID, pImReqAddContact->contactInfo.contactIDLen);
	putSctString(pBufferTemp, pImReqAddContact->contactInfo.nickName, pImReqAddContact->contactInfo.nickNameLen);
	putSctString(pBufferTemp, pImReqAddContact->contactInfo.importance, pImReqAddContact->contactInfo.importanceLen);
	putSctLong(pBufferTemp, pImReqAddContact->contactInfo.groupIDHigh, pImReqAddContact->contactInfo.groupIDLow);
	putSctByte(pBufferTemp, pImReqAddContact->type);
	putSctString(pBufferTemp, pImReqAddContact->szMessage, pImReqAddContact->uiMsgLen);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqHelpSetShareCID
/************************************************************************/
IMnetRetCode PackImReqHelpSetShareCID(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// PackImReqGetAppAddr
/************************************************************************/
IMnetRetCode PackImReqGetAppAddr(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetAppAddr* pRequest = (ImReqGetAppAddr*)pEvt->pContent;
	AMInt32 size = 0, up = ((AMInt32*)&pRequest->ulObjId)[1], low = ((AMInt32*)&pRequest->ulObjId)[0];

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 7;
	bodyLength += 5 + pRequest->iSessionIdLen;
	bodyLength += 3 + 3 + 9;


	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 4;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctString(pBufferTemp, pRequest->szSessionId, pRequest->iSessionIdLen);
	putSctShort(pBufferTemp, pRequest->uiAppType);
	putSctShort(pBufferTemp, pRequest->uiSubType);
	putSctULong(pBufferTemp, up, low);

	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackFtReqDelOffObj
/************************************************************************/
IMnetRetCode PackFtReqDelOffObj(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	FtReqDelOffObj *pRequest = (FtReqDelOffObj *)pEvt->pContent;
	AMInt32 size = 0, up = ((AMInt32*)&pRequest->ulObjId)[1], low = ((AMInt32*)&pRequest->ulObjId)[0];

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 7;
	bodyLength += 5 + pRequest->errorMsgLen;
	bodyLength += 5 + pRequest->sendUIDLen;
	bodyLength += 5 + pRequest->recevierUIDLen;
	bodyLength += 5 + pRequest->tokenLen;
	bodyLength += 5 + pRequest->downloadURLLen;
	bodyLength += 5 + pRequest->fileNameLen;
	bodyLength += 5 + pRequest->fileExtNameLen;
	bodyLength += 5 + pRequest->fileMD5Len;
	bodyLength += 5 + 3 + 9 + 5 + 5; // retcode, type, 离线贴图ID, file size, reserved.

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 13;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);

	putSctInt(pBufferTemp, pRequest->retCode);
	putSctString(pBufferTemp, pRequest->errorMsg, pRequest->errorMsgLen);
	putSctString(pBufferTemp, pRequest->sendUID, pRequest->sendUIDLen);
	putSctString(pBufferTemp, pRequest->recevierUID, pRequest->recevierUIDLen);
	putSctShort(pBufferTemp, pRequest->uiSubType);
	putSctULong(pBufferTemp, up, low);
	putSctString(pBufferTemp, pRequest->szToken, pRequest->tokenLen);
	putSctString(pBufferTemp, pRequest->szDownloadURL, pRequest->downloadURLLen);
	putSctString(pBufferTemp, pRequest->szFileName, pRequest->fileNameLen);
	putSctString(pBufferTemp, pRequest->szFileExtName, pRequest->fileExtNameLen);
	putSctString(pBufferTemp, pRequest->szFileMD5, pRequest->fileMD5Len);
	putSctInt(pBufferTemp, pRequest->fileSize);
	putSctInt(pBufferTemp, pRequest->reserved);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqCommonContactList
/************************************************************************/
IMnetRetCode PackImReqCommonContactList(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqCommonContactList* pRequest = (ImReqCommonContactList*)pEvt->pContent;
	AMInt32 size = 0;
	ContactList* pCurrentList = pRequest->pContactList;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 7;
	while(pCurrentList)
	{
		bodyLength += pCurrentList->userIDLen;
		size++;
		pCurrentList = pCurrentList->pNext;
	}
	bodyLength += size*4;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, pRequest->bindID, pRequest->bindIDLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putByte(pBufferTemp, FT_VECTOR);						
	putByte(pBufferTemp, FT_STRING);						
	putInt(pBufferTemp, size);			
	pCurrentList = pRequest->pContactList;
	while(pCurrentList)
	{					
		putString(pBufferTemp,pCurrentList->userID,pCurrentList->userIDLen);
		pCurrentList = pCurrentList->pNext;
	}

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqDeleteContact
/************************************************************************/
IMnetRetCode PackImReqDeleteContact(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return PackImReqCommonContactList(pIMnet, pEvt, ppBuffer, pLength);
}

/************************************************************************/
// PackImReqDisableSubscribeInfo
/************************************************************************/
IMnetRetCode PackImReqDisableSubscribeInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return PackImReqCommonContactList(pIMnet, pEvt, ppBuffer, pLength);
}

/************************************************************************/
// PackImReqSubscribeInfo
/************************************************************************/
IMnetRetCode PackImReqSubscribeInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return PackImReqCommonContactList(pIMnet, pEvt, ppBuffer, pLength);
}

/************************************************************************/
// PackImReqSendIMMessage
/************************************************************************/
IMnetRetCode PackImReqSendIMMessage(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
    IMnetRetCode retCode;
    PacketHead head;
    AMInt32 bodyLength = 0;
    AMUInt8* pBufferTemp = NULL;
    ImReqSendIMMessage* pReqSendIMMessage = (ImReqSendIMMessage*)pEvt->pContent;
    
    //0. 用二级协议打包原始信息(已经预留了8个字节的头部)
    MakeImMessageTextPacket(pReqSendIMMessage->secondCmd, pReqSendIMMessage->message, 
		pReqSendIMMessage->messageLen, pReqSendIMMessage->ackSeq);

    //
    //1. create head
    //
    HeadInit(&head);
    head.cmd	 = pEvt->id; 
    
    //
    //2. alloc buffer
    //
    //Protocol Length
    bodyLength += 13 + pReqSendIMMessage->contactIDLen;
	bodyLength += pReqSendIMMessage->messageLen;

    retCode = PackAllocate(&head, ppBuffer, pLength, 0, pReqSendIMMessage->bindID, pReqSendIMMessage->bindIDLen, bodyLength);
    if(retCode != eOK)
    {
        return retCode;
    }
    
    //
    //3. pack head.
    //
    pBufferTemp = *ppBuffer;
    pBufferTemp = PackHead(pBufferTemp, &head);
    
    //
    //4. pack body
    //
    pReqSendIMMessage->propertyNum = 3;
    if(pReqSendIMMessage->propertyNum != 0)
        putByte(pBufferTemp, pReqSendIMMessage->propertyNum);	
    putSctString(pBufferTemp, pReqSendIMMessage->contactID, pReqSendIMMessage->contactIDLen);
    putSctByte(pBufferTemp, pReqSendIMMessage->type);
    putStrByte(pBufferTemp, pReqSendIMMessage->message, pReqSendIMMessage->messageLen)
    
    //
    //5. reset head
    //
    ResetHead(*ppBuffer, head.extLength, head.bodyLength);
    
    //
    //6. EncryptBody
    //
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqChangeStatus
/************************************************************************/
IMnetRetCode PackImReqChangeStatus(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqChangeStatus* pRequest = (ImReqChangeStatus*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength += 5;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
	{
		return retCode;
	}

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 2;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	
	putSctByte(pBufferTemp, pRequest->basicStatus);
	putSctByte(pBufferTemp, pRequest->predefStatus);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

/************************************************************************/
// PackImReqReLogin
/************************************************************************/
IMnetRetCode PackImReqReLogin(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	AMInt32 bodyLength = 0;
	PacketHead head;
	AMUInt8* pBufferTemp = NULL;
	ImReqReLogin* pRequest = (ImReqReLogin*)pEvt->pContent;
	
	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 20 + strlen(pRequest->password);
	bodyLength += strlen(pRequest->version);

	retCode = PackAllocate( &head, ppBuffer, pLength, pRequest->reserved, 
		pRequest->extData, strlen(pRequest->extData), bodyLength);
	if(retCode != eOK)
	{
		return retCode;
	}

	//
	//3. pack head.
	//
	pBufferTemp = PackHead(*ppBuffer, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 5;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	
	
	putSctString(pBufferTemp, pRequest->password, strlen(pRequest->password));
	putSctString(pBufferTemp, pRequest->version, strlen(pRequest->version));
	putSctInt(pBufferTemp, pRequest->connectNo);
	putSctByte(pBufferTemp, pRequest->basicStatus);
	putSctByte(pBufferTemp, pRequest->predefStatus);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqHelpGetBindTo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetDegree(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetUserUDBProfile* pRequest = (ImReqGetUserUDBProfile*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6 + 64 /*strlen(pRequest->contactId)*/;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);
	putByte(pBufferTemp, FT_STRING);
	WriteData(&pBufferTemp, pRequest->contactId, pRequest->contactIdLen, 0, 64);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

void FreeImRspGetDegree(EventContent* pContent)
{
	ImRspGetDegree *pRsp = (ImRspGetDegree*)pContent;
	if(pRsp->contactId)
	{
		AMFree(pRsp->contactId);
		pRsp->contactId = NULL;
	}
}

IMnetRetCode UnpackImRspGetDegree(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetDegree rspDegree;


	// clear all
	memset(&rspDegree, 0, sizeof(rspDegree));	

	//
	//0. init propertyNum.
	//
	rspDegree.propertyNum = 4;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body

	getByte(pBufferTemp, tempNum);
	if(tempNum<6)
	{
		UncompressBodyEnd(pNewBuffer);
		return eInternalError;
	}

	retCode = GetSctString(&pBufferTemp, &rspDegree.contactId, &rspDegree.contactIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspDegree.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspDegree.userLevel);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspDegree.totalDegree);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspDegree.needDegree);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	getByte(pBufferTemp, tempNum);
	if(FT_VECTOR == tempNum)
	{
		//这里是一个Vector，谁用谁解析吧，没看懂...
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspDegree, sizeof(rspDegree), FreeImRspGetDegree);
}

IMnetRetCode PackImReqSendMultiUserMsg(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetOfflineMsg(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetContactStatus(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetSystemMsg(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}
IMnetRetCode PackImReqGetContact(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqAddBinding(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetWebSession(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 0;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//4. pack body
	//

	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqSendWatchInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqLoginAgain(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqPreLoginAgain(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetToolsProfile(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqHelpGetServices(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetSIPSessionID(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// PackImReqAddContactACK
/************************************************************************/
IMnetRetCode PackImReqAddContactACK(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqAddContactACK* pImReqAddContactACK = (ImReqAddContactACK*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 26 + pImReqAddContactACK->contactIDLen + pImReqAddContactACK->uiMsgLen;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, pImReqAddContactACK->bindID, pImReqAddContactACK->bindIDLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pImReqAddContactACK->propertyNum = 5;
	if(pImReqAddContactACK->propertyNum != 0)
		putByte(pBufferTemp, pImReqAddContactACK->propertyNum);	
	
	putSctByte(pBufferTemp, pImReqAddContactACK->opcode);
	putSctString(pBufferTemp, pImReqAddContactACK->contactID, pImReqAddContactACK->contactIDLen);
	putSctLong(pBufferTemp, pImReqAddContactACK->groupIDHigh, pImReqAddContactACK->groupIDLow);
	putSctString(pBufferTemp, "", 0);
	putSctString(pBufferTemp, pImReqAddContactACK->szMessage, pImReqAddContactACK->uiMsgLen);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqGetGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqCanKeySearch(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// PackImReqDeleteOfflineMsg
/************************************************************************/
IMnetRetCode PackImReqDeleteOfflineMsg(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqDeleteOfflineMsg* pRequest = (ImReqDeleteOfflineMsg*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, pRequest->bindID, pRequest->bindIDLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putSctInt(pBufferTemp, pRequest->lastTime);
	
	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqChangeBinding(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqChangeContactMemo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqHelpChangeSrvMode(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqHelpChangeSrvMode* pRequest = (ImReqHelpChangeSrvMode*)pEvt->pContent;
	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  =  68;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
 	pRequest->propertyNum = 2;
 	if(pRequest->propertyNum != 0)
 		putByte(pBufferTemp, pRequest->propertyNum);	

	putByte(pBufferTemp, FT_STRING);
	WriteData(&pBufferTemp, pRequest->accountId, pRequest->accountIdLen, 0, 64);

	putSctByte(pBufferTemp, pRequest->status);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqGetContactMemo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetContactMemo* pRequest = (ImReqGetContactMemo*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 6 + strlen(pRequest->contactID);

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 1;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	
	putSctString(pBufferTemp, pRequest->contactID, strlen(pRequest->contactID));

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqDeleteBinding(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
//unpack handlers
/************************************************************************/
/************************************************************************/
// UnpackImRspHelpGetOnlineChilds
/************************************************************************/
IMnetRetCode UnpackImRspHelpGetOnlineChilds(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspLoginAgain(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetPwdToken(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspAddBlack
/************************************************************************/
void FreeImRspAddBlack(EventContent* pContent)
{
    ImRspAddBlack* pRspAddBlack = (ImRspAddBlack*)pContent;
    AMFree(pRspAddBlack->blackId);
    pRspAddBlack->blackId = NULL;
}

IMnetRetCode UnpackImRspAddBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspAddBlack rspAddBlack;
    
    // clear all
    memset(&rspAddBlack, 0, sizeof(rspAddBlack));	
    
    //
    //0. init propertyNum.
    //
    rspAddBlack.propertyNum = 3;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspAddBlack.propertyNum, tempNum);

    retCode = GetSctInt(&pBufferTemp, &rspAddBlack.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}
    
    retCode = GetSctString(&pBufferTemp, &rspAddBlack.blackId, &rspAddBlack.blackIdLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}

    retCode = GetSctInt(&pBufferTemp, &rspAddBlack.timestamp);
    if(retCode != eOK)
    {
        FreeImRspAddBlack((EventContent*)&rspAddBlack);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}

    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspAddBlack, sizeof(rspAddBlack), FreeImRspAddBlack);
}

IMnetRetCode UnpackImRspGetUsersStatus(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

void FreeImRspGetUserUDBProfile(EventContent* pContent)
{
	ImRspGetUserUDBProfile* pRsp = (ImRspGetUserUDBProfile*)pContent;
	if(pRsp->pOhtData)
	{
		destruct(OHTable, pRsp->pOhtData);
		AMFree(pRsp->pOhtData);
	}
	if(pRsp->contactId)
	{
		AMFree(pRsp->contactId);
		pRsp->contactId = NULL;
	}
}

IMnetRetCode UnpackImRspGetUserUDBProfile(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetUserUDBProfile rspUserUDBProfile;

	// clear all
	memset(&rspUserUDBProfile, 0, sizeof(rspUserUDBProfile));	

	//
	//0. init propertyNum.
	//
	rspUserUDBProfile.propertyNum = 3;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspAddBlack.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspUserUDBProfile.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctStrStrMap(&pBufferTemp, &rspUserUDBProfile.pOhtData, &rspUserUDBProfile.iTotalLength);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspUserUDBProfile.contactId, &rspUserUDBProfile.contactIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	
	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspUserUDBProfile, sizeof(rspUserUDBProfile), FreeImRspGetUserUDBProfile);
}

IMnetRetCode UnpackImRspHelpGetServices(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspChangeContactMemo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfFeeds(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspChangeUserVerify
/************************************************************************/
IMnetRetCode UnpackImRspChangeUserVerify(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspChangeUserVerify rspChangeUserVerify;
    
    
    // clear all
    memset(&rspChangeUserVerify, 0, sizeof(rspChangeUserVerify));	
    
    //
    //0. init propertyNum.
    //
    rspChangeUserVerify.propertyNum = 4;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspChangeUserVerify.propertyNum, tempNum);
    
    retCode = GetSctInt(&pBufferTemp, &rspChangeUserVerify.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    retCode = GetSctByte(&pBufferTemp, &rspChangeUserVerify.addcontactFlag);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctByte(&pBufferTemp, &rspChangeUserVerify.sendmsgFlag);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

	retCode = GetSctByte(&pBufferTemp, &rspChangeUserVerify.enableSearch);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
	return EventCreate(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspChangeUserVerify, sizeof(rspChangeUserVerify));
}

IMnetRetCode UnpackImRspUpdateGeneralContact(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspGetOfflineMsg
/************************************************************************/
void FreeImRspGetOfflineMsg(EventContent* pContent)
{
    ImRspGetOfflineMsg* pRspGetOfflineMsg = (ImRspGetOfflineMsg*)pContent;
    OfflineMsgList* pList = NULL;
    OfflineMsgList* pCurrentList = NULL;
    
    //需要释放里面已经申请的内存
    pCurrentList = pRspGetOfflineMsg->offlineMsgList;
    while(pCurrentList != NULL)
    {
        pList		 = pCurrentList->pNext;
        AMFree(pCurrentList->offlineMsgInfo.text.content);
        pCurrentList->offlineMsgInfo.text.content = NULL;
        AMFree(pCurrentList->offlineMsgInfo.fromId);
        pCurrentList->offlineMsgInfo.fromId = NULL;
        AMFree(pCurrentList);
        pCurrentList = pList;
    }
    pRspGetOfflineMsg->offlineMsgList = NULL;
}

IMnetRetCode UnpackImRspGetOfflineMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetOfflineMsg rspGetOfflineMsg;
	AMInt32 i;
	OfflineMsgList* pList = NULL;
	OfflineMsgList* pCurrentList = NULL;
    AMUInt8* pChild = NULL;
    AMInt32 childLen = 0;

	// clear all
	memset(&rspGetOfflineMsg, 0, sizeof(rspGetOfflineMsg));	

	//
	//0. init propertyNum.
	//
	rspGetOfflineMsg.propertyNum = 4;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetOfflineMsg.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, &rspGetOfflineMsg.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetVectorStructLen(&pBufferTemp, &rspGetOfflineMsg.offlineMsgCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspGetOfflineMsg.offlineMsgCount; i++)
	{
		pList = NULL;
		pList = (OfflineMsgList*)AMMalloc(sizeof(OfflineMsgList));
		if(pList == NULL)
		{
            FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pList, 0, sizeof(OfflineMsgList));
		getByte(pBufferTemp, pList->num);
		
        retCode = GetSctString(&pBufferTemp, &pList->offlineMsgInfo.fromId, &pList->offlineMsgInfo.fromIdLen);
        if(retCode != eOK)
        {
            AMFree(pList);
            FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
			UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

        retCode = GetSctByte(&pBufferTemp, &pList->offlineMsgInfo.type);
        if(retCode != eOK)
        {
            AMFree(pList->offlineMsgInfo.fromId);
            AMFree(pList);
            FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
			UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

        retCode = GetSctInt(&pBufferTemp, &pList->offlineMsgInfo.sendTime);
        if(retCode != eOK)
        {
            AMFree(pList->offlineMsgInfo.fromId);
            AMFree(pList);
            FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

        pChild = NULL;
        retCode = GetSctString(&pBufferTemp, (AMInt8**)&pChild, &childLen);
        if(retCode != eOK)
        {
            AMFree(pList->offlineMsgInfo.fromId);
            AMFree(pList);
            FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

		if(pList->num > 4)
		{
			retCode = GetSctByte(&pBufferTemp, &pList->offlineMsgInfo.serverType);
			if(retCode != eOK)
			{
				AMFree(pList->offlineMsgInfo.fromId);
				AMFree(pList);
				AMFree(pChild);
				FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
				UncompressBodyEnd(pNewBuffer);
				return retCode;
			}

			SkipPropertyNum(&pBufferTemp, pList->num - 5); //denx: 4来自于Java版本的OfflineMsgHelper的propertyNum.
		}

		if(1 == pList->offlineMsgInfo.type)//订阅消息-------------该数值来自IMnetCallback.c
		{
			retCode = UnpackImMessageText_Sub( pChild, childLen,
											&pList->offlineMsgInfo.text.content, 
											&pList->offlineMsgInfo.text.contentLen );
		}
		else
		{
			retCode = UnpackImMessageText( pChild, childLen,
											&pList->offlineMsgInfo.text.childHead, 
											&pList->offlineMsgInfo.text.content, 
											&pList->offlineMsgInfo.text.contentLen );
		}
        AMFree(pChild);

        if(pList->offlineMsgInfo.type != 1 && pList->offlineMsgInfo.text.childHead.cmd == IMM_SP_CONTACT)
            pList->offlineMsgInfo.type = 2; //添加联系人通知消息

        if(retCode != eOK)
        {
            AMFree(pList->offlineMsgInfo.fromId);
            AMFree(pList->offlineMsgInfo.text.content);
            AMFree(pList);
            FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        if(rspGetOfflineMsg.offlineMsgList == NULL)
            rspGetOfflineMsg.offlineMsgList = pList;
        else
            pCurrentList->pNext = pList;
        pCurrentList = pList;
	}

	retCode = GetSctInt(&pBufferTemp, &rspGetOfflineMsg.timestamp);
	if(retCode != eOK)
	{
        FreeImRspGetOfflineMsg((EventContent*)&rspGetOfflineMsg);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
	RSP_ADD_BIND_UID(head, rspGetOfflineMsg);

    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetOfflineMsg, sizeof(rspGetOfflineMsg), FreeImRspGetOfflineMsg);
}

IMnetRetCode UnpackImRspGetSIPSessionID(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspChangeContact(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImNtfSubscribeMsg
/************************************************************************/
void FreeImNtfSubscribeMsg(EventContent* pContent)
{
    ImNtfSubscribeMsg* pNtfSubscribeMsg = (ImNtfSubscribeMsg*)pContent;
    AMFree(pNtfSubscribeMsg->message);
    pNtfSubscribeMsg->message = NULL;
}

IMnetRetCode UnpackImNtfSubscribeMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImNtfSubscribeMsg ntfSubscribeMsg;
    
    // clear all
    memset(&ntfSubscribeMsg, 0, sizeof(ntfSubscribeMsg));	
    
    //
    //0. init propertyNum.
    //
    ntfSubscribeMsg.propertyNum = 1;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(ntfSubscribeMsg.propertyNum, tempNum);
        
    retCode = GetSctString(&pBufferTemp, &ntfSubscribeMsg.message, &ntfSubscribeMsg.messageLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfSubscribeMsg, sizeof(ntfSubscribeMsg), FreeImNtfSubscribeMsg);
}

IMnetRetCode UnpackImRspHelpGetChildOnline(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetToolsProfile(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

void FreeImNtfUpdateUsrExtInfo(EventContent *pContent)
{
	ImNtfUpdateUsrExtInfo *pEvent = (ImNtfUpdateUsrExtInfo*)pContent,
							*pNext = NULL;
	AMInt32	i = 0;
	while(NULL != pEvent)
	{
		AMFree(pEvent->szContactID);
		pEvent->szContactID = NULL;

		AMFree(pEvent->szType);
		pEvent->szType = NULL;

		AMFree(pEvent->szValue);
		pEvent->szValue = NULL;

		pNext = pEvent->next;
		if(i++)
			AMFree(pEvent);
	
		pEvent = pNext;
	}
}

IMnetRetCode UnpackImNtfUpdateUsrExtInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImNtfUpdateUsrExtInfo ntfUpdataUsrExtInfo;

	// clear all
	memset(&ntfUpdataUsrExtInfo, 0, sizeof(ntfUpdataUsrExtInfo));	

	ntfUpdataUsrExtInfo.iCount = 1;
	ntfUpdataUsrExtInfo.iFlag = 1;
	//
	//0. init propertyNum.
	//
	ntfUpdataUsrExtInfo.propertyNum = 1;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfSubscribeMsg.propertyNum, tempNum);

	retCode = GetSctString(&pBufferTemp, &ntfUpdataUsrExtInfo.szContactID, &ntfUpdataUsrExtInfo.iContactIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &ntfUpdataUsrExtInfo.szType, &ntfUpdataUsrExtInfo.iTypeLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &ntfUpdataUsrExtInfo.szValue, &ntfUpdataUsrExtInfo.iValueLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfUpdataUsrExtInfo, sizeof(ntfUpdataUsrExtInfo), FreeImNtfUpdateUsrExtInfo);
	return eOK;
}

IMnetRetCode UnpackImRspChangeBinding(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eOK;
}

IMnetRetCode UnpackImRspAddBinding(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfUserSnsInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}
IMnetRetCode UnpackImRspGetBinding(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

void FreeImRspGetContactMemo(EventContent *pContent)
{
	ImRspGetContactMemo	*pMemo = (ImRspGetContactMemo*)pContent;
	if(pMemo->contactID)
	{
		AMFree(pMemo->contactID);
		pMemo->contactID = NULL;
	}
	if(pMemo->memo)
	{
		AMFree(pMemo->memo);
		pMemo->memo = NULL;
	}
}

IMnetRetCode UnpackImRspGetContactMemo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetContactMemo rspGetContactMemo;

	// clear all
	memset(&rspGetContactMemo, 0, sizeof(rspGetContactMemo));	

	//
	//0. init propertyNum.
	//
	rspGetContactMemo.propertyNum = 3;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspAddBlack.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspGetContactMemo.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspGetContactMemo.contactID, &rspGetContactMemo.contactIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspGetContactMemo.memo, &rspGetContactMemo.memoLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetContactMemo, sizeof(rspGetContactMemo), FreeImRspGetContactMemo);
}

IMnetRetCode UnpackImRspDeleteOfflineMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspChangeToolsProfile(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImNtfForceDisconnect
/************************************************************************/
void FreeImNtfForceDisconnect(EventContent* pContent)
{
    ImNtfForceDisconnect* pNtfForceDisconnect = (ImNtfForceDisconnect*)pContent;
    AMFree(pNtfForceDisconnect->remark);
    pNtfForceDisconnect->remark = NULL;
}

IMnetRetCode UnpackImNtfForceDisconnect(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImNtfForceDisconnect ntfForcedisconnect;
    
    // clear all
    memset(&ntfForcedisconnect, 0, sizeof(ntfForcedisconnect));	
    
    //
    //0. init propertyNum.
    //
    ntfForcedisconnect.propertyNum = 2;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(ntfForcedisconnect.propertyNum, tempNum);
    
    retCode = GetSctByte(&pBufferTemp, &ntfForcedisconnect.type);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    retCode = GetSctString(&pBufferTemp, &ntfForcedisconnect.remark, &ntfForcedisconnect.remarkLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfForcedisconnect, sizeof(ntfForcedisconnect), FreeImNtfForceDisconnect);
}

IMnetRetCode UnpackImNtfBindIDKicked(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImNtfBindIDKicked ntfForcedisconnect;

	// clear all
	memset(&ntfForcedisconnect, 0, sizeof(ntfForcedisconnect));	

	//
	//0. init propertyNum.
	//
	ntfForcedisconnect.propertyNum = 2;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfForcedisconnect.propertyNum, tempNum);

	retCode = GetSctByte(&pBufferTemp, &ntfForcedisconnect.type);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &ntfForcedisconnect.bindID, &ntfForcedisconnect.bindIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &ntfForcedisconnect.remark, &ntfForcedisconnect.remarkLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfForcedisconnect, sizeof(ntfForcedisconnect), FreeImNtfForceDisconnect);
}

/************************************************************************/
// UnpackImRspLogoff
/************************************************************************/
IMnetRetCode UnpackImRspLogoff(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	//denx:此消息上层不处理
	return eOK;
}

/************************************************************************/
// UnpackImRspAddGroup
/************************************************************************/
IMnetRetCode UnpackImRspAddGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspHelpGetShareCID
/************************************************************************/
IMnetRetCode UnpackImRspHelpGetShareCID(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspDeleteBinding
/************************************************************************/
IMnetRetCode UnpackImRspDeleteBinding(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspHelpGetBindTo
/************************************************************************/
IMnetRetCode UnpackImRspHelpGetBindTo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspDeleteBlack
/************************************************************************/
void FreeImRspDeleteBlack(EventContent* pContent)
{
    ImRspDeleteBlack* pRspDeleteBlack = (ImRspDeleteBlack*)pContent;
    AMFree(pRspDeleteBlack->blackId);
    pRspDeleteBlack->blackId = NULL;
}

IMnetRetCode UnpackImRspDeleteBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspDeleteBlack rspDeleteBlack;
    
    
    // clear all
    memset(&rspDeleteBlack, 0, sizeof(rspDeleteBlack));	
    
    //
    //0. init propertyNum.
    //
    rspDeleteBlack.propertyNum = 3;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspDeleteBlack.propertyNum, tempNum);
    
    retCode = GetSctInt(&pBufferTemp, &rspDeleteBlack.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    retCode = GetSctString(&pBufferTemp, &rspDeleteBlack.blackId, &rspDeleteBlack.blackIdLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctInt(&pBufferTemp, &rspDeleteBlack.timestamp);
    if(retCode != eOK)
    {
        FreeImRspDeleteBlack((EventContent*)&rspDeleteBlack);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspDeleteBlack, sizeof(rspDeleteBlack), FreeImRspDeleteBlack);
}

void FreeImNtfOperationTip(EventContent* pContent)
{
	ImNtfOperationTip* pNtfOperation = (ImNtfOperationTip*)pContent;
	AMFree(pNtfOperation->contactId);
	AMFree(pNtfOperation->messageType);
}
/************************************************************************/
// UnpackImNtfOperationTip
/************************************************************************/
IMnetRetCode UnpackImNtfOperationTip(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImNtfOperationTip ntfOperation;  
	AMInt32 tmpLen = 0;

	// clear all
	memset(&ntfOperation, 0, sizeof(ntfOperation));	

	//
	//0. init propertyNum.
	//
	ntfOperation.propertyNum = 3;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfOperation.propertyNum, tempNum);

	retCode = GetSctString(&pBufferTemp, &ntfOperation.contactId, &ntfOperation.contactIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &ntfOperation.messageType, &ntfOperation.msgTypeLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	
	retCode = GetSctInt(&pBufferTemp, &ntfOperation.ntfTime);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfOperation, sizeof(ntfOperation), FreeImNtfOperationTip);
}

IMnetRetCode UnpackImRspGetSystemMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspDeleteGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImNtfIMMessage
/************************************************************************/
void FreeImNtfIMMessage(EventContent* pContent)
{
    ImNtfIMMessage* pNtfIMMessage = (ImNtfIMMessage*)pContent;
    AMFree(pNtfIMMessage->text.content);
    pNtfIMMessage->text.content = NULL;
    AMFree(pNtfIMMessage->sendId);
    pNtfIMMessage->sendId = NULL;
}

IMnetRetCode UnpackImNtfIMMessage(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImNtfIMMessage ntfIMMessage;  
	AMUInt8* pMessage = NULL;
	AMInt32 MessageLen = 0;
    
    // clear all
    memset(&ntfIMMessage, 0, sizeof(ntfIMMessage));	
    
    //
    //0. init propertyNum.
    //
    ntfIMMessage.propertyNum = 4;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(ntfIMMessage.propertyNum, tempNum);
       
    retCode = GetSctString(&pBufferTemp, &ntfIMMessage.sendId, &ntfIMMessage.sendIdLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctInt(&pBufferTemp, &ntfIMMessage.sendTime);
    if(retCode != eOK)
    {
        AMFree(ntfIMMessage.sendId);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctString(&pBufferTemp, (AMInt8**)&pMessage, &MessageLen);
    if(retCode != eOK)
    {
        AMFree(ntfIMMessage.sendId);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

	retCode = GetSctByte(&pBufferTemp, &ntfIMMessage.serverType);
	if(retCode != eOK)
	{
		AMFree(ntfIMMessage.sendId);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	if(tempNum > 4)
	{
		retCode = GetSctByte(&pBufferTemp, &ntfIMMessage.shiftFlag);
		if(retCode != eOK)
		{
			AMFree(ntfIMMessage.sendId);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		SkipPropertyNum(&pBufferTemp, tempNum - 5);
	}

    UncompressBodyEnd(pNewBuffer);

	//解二级协议
	retCode = UnpackImMessageText( pMessage, MessageLen,
		&ntfIMMessage.text.childHead, 
		&ntfIMMessage.text.content, 
		&ntfIMMessage.text.contentLen);

	AMFree(pMessage);
	pMessage = NULL;
    
	RSP_ADD_BIND_UID(head, ntfIMMessage);

    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfIMMessage, sizeof(ntfIMMessage), FreeImNtfIMMessage);
}

IMnetRetCode UnpackImNtfWatchInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfRefreshContact(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfExitInfoMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

void FreeImRspChechAuthCode(EventContent* pContent)
{
	ImRspCheckAuthCode* pRspCheckAuthCode = (ImRspCheckAuthCode*)pContent;
	if(pRspCheckAuthCode->szSession)
		AMFree(pRspCheckAuthCode->szSession);
	if(pRspCheckAuthCode->szCode)
		AMFree(pRspCheckAuthCode->szCode);
}

IMnetRetCode UnpackImRspCheckAuthCode(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspCheckAuthCode rspCheckAuthCode;

	// clear all
	memset(&rspCheckAuthCode, 0, sizeof(rspCheckAuthCode));	

	//
	//0. init propertyNum.
	//
	rspCheckAuthCode.propertyNum = 3;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspReLogin.propertyNum, tempNum);

	retCode = GetSctByte(&pBufferTemp, &rspCheckAuthCode.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspCheckAuthCode.szSession, &rspCheckAuthCode.uiSessionLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspCheckAuthCode.szCode, &rspCheckAuthCode.uiCodeLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspCheckAuthCode, sizeof(rspCheckAuthCode), FreeImRspChechAuthCode);
}

/************************************************************************/
// UnpackImRspReLogin
/************************************************************************/
void FreeImRspReLogin(EventContent* pContent)
{
    ImRspReLogin* pRspReLogin = (ImRspReLogin*)pContent;
    AMFree(pRspReLogin->remark);
    pRspReLogin->remark = NULL;
}

IMnetRetCode UnpackImRspReLogin(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspReLogin rspReLogin;
    
    // clear all
    memset(&rspReLogin, 0, sizeof(rspReLogin));	
    
    //
    //0. init propertyNum.
    //
    rspReLogin.propertyNum = 3;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspReLogin.propertyNum, tempNum);
    
    retCode = GetSctInt(&pBufferTemp, &rspReLogin.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
	retCode = GetSctInt(&pBufferTemp, &rspReLogin.connectNo);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

    retCode = GetSctString(&pBufferTemp, &rspReLogin.remark, &rspReLogin.remarkLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspReLogin, sizeof(rspReLogin), FreeImRspReLogin);
}

void FreeImRspHelpLogin(EventContent* pContent)
{
	ImRspHelpLogin* pRspHelpLogin = (ImRspHelpLogin*)pContent;
	AMFree(pRspHelpLogin->parentId);
	pRspHelpLogin->parentId = NULL;
}
/************************************************************************/
// UnpackImRspHelpLogin
/************************************************************************/
IMnetRetCode UnpackImRspHelpLogin(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspHelpLogin rspHelpLogin;
    
    
    // clear all
    memset(&rspHelpLogin, 0, sizeof(rspHelpLogin));	
    
    //
    //0. init propertyNum.
    //
    rspHelpLogin.propertyNum = 2;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspHelpLogin.propertyNum, tempNum);

	retCode = GetSctByte(&pBufferTemp, &rspHelpLogin.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctByte(&pBufferTemp, &rspHelpLogin.mulStatus);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	getByte(pBufferTemp, tempNum);
	if(FT_STRING != tempNum	)
	{
		UncompressBodyEnd(pNewBuffer);
		return eTypeError;
	}

	rspHelpLogin.parentId = malloc(64);
	if(rspHelpLogin.parentId)
	{
		memcpy(rspHelpLogin.parentId, pBufferTemp, 64);
		rspHelpLogin.parentIdLen = strlen(rspHelpLogin.parentId);
		pBufferTemp += 64;
	}
	else
	{
		UncompressBodyEnd(pNewBuffer);
		return eMallocError;
	}
        
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspHelpLogin, sizeof(rspHelpLogin), FreeImRspHelpLogin);
}


/************************************************************************/
// UnpackImRspHelpSetShareCID
/************************************************************************/
IMnetRetCode UnpackImRspHelpSetShareCID(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfLoginAgain(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspSubscribeInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    // ImRspSubscribeInfo定义和ImRspGetContactStatus定义完全一样,使用之
	return UnpackImRspGetContactStatus(pIMnet, ppEvt, cmd, pBuffer, Length);
}

/************************************************************************/
// UnpackImRspChangeSignature
/************************************************************************/
void FreeImRspChangeSignature(EventContent* pContent)
{
    ImRspChangeSignature* pRspChangeSignature = (ImRspChangeSignature*)pContent;
    AMFree(pRspChangeSignature->signature);
    pRspChangeSignature->signature = NULL;
}

IMnetRetCode UnpackImRspChangeSignature(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspChangeSignature rspChangeSignature;
    
    
    // clear all
    memset(&rspChangeSignature, 0, sizeof(rspChangeSignature));	
    
    //
    //0. init propertyNum.
    //
    rspChangeSignature.propertyNum = 2;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspChangeSignature.propertyNum, tempNum);

	retCode = GetSctString(&pBufferTemp, &rspChangeSignature.signature, &rspChangeSignature.signatureLen);//先来string，后来retCode-----yanlong.shiyl
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

    retCode = GetSctInt(&pBufferTemp, &rspChangeSignature.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
        
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspChangeSignature, sizeof(rspChangeSignature), FreeImRspChangeSignature);
}

/************************************************************************/
// 
/************************************************************************/
IMnetRetCode UnpackImRspChangeUserDetail(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspAddContact
/************************************************************************/
void FreeImRspAddContact(EventContent* pContent)
{
    ImRspAddContact* pRspAddContact = (ImRspAddContact*)pContent;

	if(pRspAddContact->bContactInfoUsed == 0)
	{
		AMFree(pRspAddContact->contactInfo.contactID);
		pRspAddContact->contactInfo.contactID = NULL;
		AMFree(pRspAddContact->contactInfo.nickName);
		pRspAddContact->contactInfo.nickName = NULL;
		AMFree(pRspAddContact->contactInfo.importance);
		pRspAddContact->contactInfo.importance = NULL;
	}
}

IMnetRetCode UnpackImRspAddContact(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspAddContact rspAddContact;
    AMInt8 tempByte;

    // clear all
    memset(&rspAddContact, 0, sizeof(rspAddContact));
    
    //
    //0. init propertyNum.
    //
    rspAddContact.propertyNum = 4;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspAddContact.propertyNum, tempNum);
    
    retCode = GetSctInt(&pBufferTemp, &rspAddContact.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctByte(&pBufferTemp, &rspAddContact.type);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    getByte(pBufferTemp, tempByte);
    getByte(pBufferTemp, tempByte);
    retCode = GetSctString(&pBufferTemp, &rspAddContact.contactInfo.contactID, &rspAddContact.contactInfo.contactIDLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctString(&pBufferTemp, &rspAddContact.contactInfo.nickName, &rspAddContact.contactInfo.nickNameLen);
    if(retCode != eOK)
    {
        AMFree(rspAddContact.contactInfo.contactID);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    retCode = GetSctString(&pBufferTemp, &rspAddContact.contactInfo.importance, &rspAddContact.contactInfo.importanceLen);
    if(retCode != eOK)
    {
        AMFree(rspAddContact.contactInfo.contactID);
        AMFree(rspAddContact.contactInfo.nickName);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    retCode = GetSctLong(&pBufferTemp, &rspAddContact.contactInfo.groupIDHigh, &rspAddContact.contactInfo.groupIDLow);
    if(retCode != eOK)
    {
        FreeImRspAddContact((EventContent*)&rspAddContact);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    retCode = GetSctInt(&pBufferTemp, &rspAddContact.timestamp);
    if(retCode != eOK)
    {
        FreeImRspAddContact((EventContent*)&rspAddContact);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    UncompressBodyEnd(pNewBuffer);
    
	RSP_ADD_BIND_UID(head, rspAddContact);

    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspAddContact, sizeof(rspAddContact), FreeImRspAddContact);
}

void FreeImRspGetWebSession(EventContent* pContent)
{
	ImRspGetWebSession *pGetWebSession = (ImRspGetWebSession *)pContent;
	if(pGetWebSession->session)
	{
		AMFree(pGetWebSession->session);
		pGetWebSession->session = NULL;
	}
}

IMnetRetCode UnpackImRspGetWebSession(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetWebSession rspWebSession;

	// clear all
	memset(&rspWebSession, 0, sizeof(ImRspGetWebSession));	

	//
	//0. init propertyNum.
	//
	rspWebSession.propertyNum = 1;		//

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfStatus.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspWebSession.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspWebSession.expireTime);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspWebSession.session, &rspWebSession.sessionLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspWebSession, sizeof(rspWebSession), FreeImRspGetWebSession);
}

IMnetRetCode UnpackImRspDeleteContact(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    return UnpackImRspCommonContactList(pIMnet, ppEvt, cmd, pBuffer, Length);
}

/************************************************************************/
// UnpackImNtfStatus
/************************************************************************/
void FreeImNtfStatus(EventContent* pContent)
{
    ImNtfStatus* pStatus = (ImNtfStatus*)pContent;
    StatusList* pList = NULL;
    StatusList* pCurrentList = NULL;
    
    //需要释放里面已经申请的内存
    pCurrentList = pStatus->statusList;
    while(pCurrentList != NULL)
    {
        pList		  = pCurrentList->pNext;
        AMFree(pCurrentList->userID);
        AMFree(pCurrentList);
        pCurrentList = pList;
    }
    pStatus->statusList = NULL;
}

IMnetRetCode UnpackImNtfStatus(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImNtfStatus ntfStatus;
	AMInt32 i;
	StatusList* pList = NULL;
	StatusList* pCurrentList = NULL;

	// clear all
	memset(&ntfStatus, 0, sizeof(ntfStatus));	

	//
	//0. init propertyNum.
	//
	ntfStatus.propertyNum = 1;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfStatus.propertyNum, tempNum);
	
	retCode = GetVectorStructLen(&pBufferTemp, &ntfStatus.statusCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<ntfStatus.statusCount; i++)
	{
		pList = NULL;
		pList = (StatusList*)AMMalloc(sizeof(StatusList));
		if(pList == NULL)
		{
			FreeImNtfStatus((EventContent*)&ntfStatus);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pList, 0, sizeof(StatusList));
		getByte(pBufferTemp, pList->num);
        retCode = GetSctString(&pBufferTemp, &pList->userID, &pList->userIDLen);
        if(retCode != eOK)
        {
            FreeImNtfStatus((EventContent*)&ntfStatus);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

        retCode = GetSctByte(&pBufferTemp, &pList->basicStatus);
        if(retCode != eOK)
        {
            AMFree(pList->userID);
            AMFree(pList);
            FreeImNtfStatus((EventContent*)&ntfStatus);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctByte(&pBufferTemp, &pList->predefStatus);
        if(retCode != eOK)
        {
            AMFree(pList->userID);
            AMFree(pList);
            FreeImNtfStatus((EventContent*)&ntfStatus);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

        if(ntfStatus.statusList == NULL)
            ntfStatus.statusList = pList;
        else
			pCurrentList->pNext = pList;
		pCurrentList = pList;
	}
    
    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfStatus, sizeof(ntfStatus), FreeImNtfStatus);
}

void FreeImRspGetPeerInfo(EventContent* pContent)
{
	ImRspGetPeerInfo* pInfo = (ImRspGetPeerInfo*)pContent;
	if(pInfo->targetId)
	{
		AMFree(pInfo->targetId);
		pInfo->targetId = NULL;
	}
	if(pInfo->version)
	{
		AMFree(pInfo->version);
		pInfo->version = NULL;
	}
}

IMnetRetCode UnpackImRspGetPeerInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetPeerInfo rspPeerInfo;

	// clear all
	memset(&rspPeerInfo, 0, sizeof(rspPeerInfo));	

	//
	//0. init propertyNum.
	//
	rspPeerInfo.propertyNum = 1;		//

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfStatus.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspPeerInfo.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspPeerInfo.targetId, &rspPeerInfo.targetIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspPeerInfo.clinetip);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspPeerInfo.version, &rspPeerInfo.versionLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctByte(&pBufferTemp, &rspPeerInfo.basicStatus);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctByte(&pBufferTemp, &rspPeerInfo.predefStatus);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctByte(&pBufferTemp, &rspPeerInfo.addcontactFlag);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctByte(&pBufferTemp, &rspPeerInfo.sendmsgFlag);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctByte(&pBufferTemp, &rspPeerInfo.reverseContact);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);
	
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspPeerInfo, sizeof(rspPeerInfo), FreeImRspGetPeerInfo);
}

IMnetRetCode FreeImRspGetPeerVerifyConfig(EventContent* pContent)
{
	ImRspGetPeerVerifyConfig *pRsp = (ImRspGetPeerVerifyConfig*)pContent;
	if(pRsp->contactId)
	{
		AMFree(pRsp->contactId);
		pRsp->contactId = NULL;
	}

	if(pRsp->retLongId)
	{
		AMFree(pRsp->retLongId);
		pRsp->retLongId = NULL;
	}

	if(pRsp->retShowName)
	{
		AMFree(pRsp->retShowName);
		pRsp->retLongId = NULL;
	}
	return eOK;
}

IMnetRetCode UnpackImRspGetPeerVerifyConfig(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetPeerVerifyConfig rspPeerVerifyConfig;

	// clear all
	memset(&rspPeerVerifyConfig, 0, sizeof(rspPeerVerifyConfig));	

	//
	//0. init propertyNum.
	//
	rspPeerVerifyConfig.propertyNum = 1;		//

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfStatus.propertyNum, tempNum);

	retCode = GetSctByte(&pBufferTemp, &rspPeerVerifyConfig.clientId);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspPeerVerifyConfig.contactId, &rspPeerVerifyConfig.contactIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspPeerVerifyConfig.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspPeerVerifyConfig.retLongId, &rspPeerVerifyConfig.retLongIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspPeerVerifyConfig.retShowName, &rspPeerVerifyConfig.retShowNameLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspPeerVerifyConfig, sizeof(rspPeerVerifyConfig), FreeImRspGetPeerVerifyConfig);
}

IMnetRetCode UnpackImRspGetContactDetail(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspChangeGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

void FreeImNtfNeedAuthCode(EventContent* pContent)
{
	ImNtfNeedAuthCode* pNtfNeedAuthCode = (ImNtfNeedAuthCode*)pContent;
	if(pNtfNeedAuthCode && pNtfNeedAuthCode->szPacket)
	{
		AMFree(pNtfNeedAuthCode->szPacket);
		pNtfNeedAuthCode->szPacket = NULL;
	}
}

IMnetRetCode UnpackImNtfNeedAuthCode(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImNtfNeedAuthCode ntfNeedAuthCode;

	// clear all
	memset(&ntfNeedAuthCode, 0, sizeof(ImNtfNeedAuthCode));	

	//
	//0. init propertyNum.
	//
	ntfNeedAuthCode.propertyNum = 1;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(ntfNeedAuthCode.propertyNum, tempNum);

	retCode = GetSctString(&pBufferTemp, &ntfNeedAuthCode.szPacket, &ntfNeedAuthCode.uiPacketLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfNeedAuthCode, sizeof(ImNtfNeedAuthCode), FreeImNtfNeedAuthCode);
}

/************************************************************************/
// UnpackImRspAddContactACK
/************************************************************************/
void FreeImRspAddContactACK(EventContent* pContent)
{
    ImRspAddContactACK* pRspAddContactACK = (ImRspAddContactACK*)pContent;
    AMFree(pRspAddContactACK->contactID);
    pRspAddContactACK->contactID = NULL;
}

IMnetRetCode UnpackImRspAddContactACK(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImRspAddContactACK rspAddContactACK;
	
    // clear all
    memset(&rspAddContactACK, 0, sizeof(rspAddContactACK));	
    
    //
    //0. init propertyNum.
    //
    rspAddContactACK.propertyNum = 5;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(rspAddContactACK.propertyNum, tempNum);
    
    retCode = GetSctInt(&pBufferTemp, &rspAddContactACK.retCode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}
    retCode = GetSctByte(&pBufferTemp, &rspAddContactACK.opcode);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}
    retCode = GetSctLong(&pBufferTemp, &rspAddContactACK.groupIDHigh, &rspAddContactACK.groupIDLow);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}
    retCode = GetSctInt(&pBufferTemp, &rspAddContactACK.timestamp);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}
    retCode = GetSctString(&pBufferTemp, &rspAddContactACK.contactID, &rspAddContactACK.contactIDLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
	}

    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspAddContactACK, sizeof(rspAddContactACK), FreeImRspAddContactACK);
}

/************************************************************************/
// UnpackImNtfSystemMessage
/************************************************************************/
void FreeImNtfSystemMessage(EventContent* pContent)
{
    ImNtfSystemMessage* pNtfSystemMessage = (ImNtfSystemMessage*)pContent;
    AMFree(pNtfSystemMessage->message);
    pNtfSystemMessage->message = NULL;
    AMFree(pNtfSystemMessage->style);
    pNtfSystemMessage->style = NULL;
}

IMnetRetCode UnpackImNtfSystemMessage(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
    AMUInt8* pBufferTemp = NULL;
    AMUInt8* pNewBuffer = NULL;
    PacketHead head;
    AMUInt8 tempNum;
    ImNtfSystemMessage ntfSystemMessage;
    
    // clear all
    memset(&ntfSystemMessage, 0, sizeof(ntfSystemMessage));	
    
    //
    //0. init propertyNum.
    //
    ntfSystemMessage.propertyNum = 3;
    
    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;
    
    //2. uncompress body
    UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);
    
    //3. unpack body
    getByte(pBufferTemp, tempNum);
    IMnetCheckPropertyNum(ntfSystemMessage.propertyNum, tempNum);
    
    retCode = GetSctShort(&pBufferTemp, &ntfSystemMessage.cmdId);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    retCode = GetSctString(&pBufferTemp, &ntfSystemMessage.style, &ntfSystemMessage.styleLen);
    if(retCode != eOK)
    {
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    retCode = GetSctString(&pBufferTemp, &ntfSystemMessage.message, &ntfSystemMessage.messageLen);
    if(retCode != eOK)
    {
        AMFree(ntfSystemMessage.style);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }

    UncompressBodyEnd(pNewBuffer);
    
    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&ntfSystemMessage, sizeof(ntfSystemMessage), FreeImNtfSystemMessage);
}

/************************************************************************/
// UnpackImRspCheckVersion
/************************************************************************/
void FreeImRspCheckVersion(EventContent* pContent)
{
    ImRspCheckVersion* pRspCheckVersion = (ImRspCheckVersion*)pContent;
    AMFree(pRspCheckVersion->remark);
    pRspCheckVersion->remark = NULL;
}

IMnetRetCode UnpackImRspCheckVersion(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspCheckVersion rspCheckVersion;
	AMUInt8* pubKey = NULL;
    AMInt32 pubKeyLen = 0;

	// clear all
	memset(&rspCheckVersion, 0, sizeof(rspCheckVersion));	
	
	//
	//0. init propertyNum.
	//
	rspCheckVersion.propertyNum = 4;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	
	IMnetCheckPropertyNum(rspCheckVersion.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspCheckVersion.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspCheckVersion.remark, &rspCheckVersion.remarkLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, &rspCheckVersion.connectNo);
	if(retCode != eOK)
	{
        AMFree(rspCheckVersion.remark);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, (AMInt8**)&pubKey, &pubKeyLen);
	if(retCode != eOK)
	{
        AMFree(rspCheckVersion.remark);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	if(pubKeyLen > 2*IMNET_MAX_KEY_LEN)
		pubKeyLen = 2*IMNET_MAX_KEY_LEN;

    HexStringToByte(pubKey, pubKeyLen, rspCheckVersion.pubKey);
    AMFree(pubKey);

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspCheckVersion, sizeof(rspCheckVersion), FreeImRspCheckVersion);
}

/************************************************************************/
// UnpackImRspLogin
/************************************************************************/
void FreeImRspLogin(EventContent* pContent)
{
    ImRspLogin* pRspLogin = (ImRspLogin*)pContent;
    AMFree(pRspLogin->workKey);
    pRspLogin->workKey = NULL;
    AMFree(pRspLogin->pwtoken);
    pRspLogin->pwtoken = NULL;
    AMFree(pRspLogin->webmd5pw);
    pRspLogin->webmd5pw = NULL;
    AMFree(pRspLogin->bindid);
    pRspLogin->bindid = NULL;
    AMFree(pRspLogin->rid);
    pRspLogin->rid = NULL;
    AMFree(pRspLogin->remark);
    pRspLogin->remark = NULL;
}

IMnetRetCode UnpackImRspLogin(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspLogin rspLogin;
    
	// clear all
	memset(&rspLogin, 0, sizeof(rspLogin));	

	//
	//0. init propertyNum.
	//
	rspLogin.propertyNum = 11;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspLogin.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, &rspLogin.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, &rspLogin.timestampFlag);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, &rspLogin.clientIp);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, &rspLogin.serverTime);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	//retCode = getStrByte(&pBufferTemp, rspLogin.workKey);
	retCode = GetSctString(&pBufferTemp, &rspLogin.workKey, &rspLogin.workKeyLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspLogin.pwtoken, &rspLogin.pwtokenLen);
	if(retCode != eOK)
	{
        AMFree(rspLogin.workKey);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspLogin.remark, &rspLogin.remarkLen);
	if(retCode != eOK)
	{
        AMFree(rspLogin.workKey);
        AMFree(rspLogin.pwtoken);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspLogin.webmd5pw, &rspLogin.webmd5pwLen);
	if(retCode != eOK)
	{
        AMFree(rspLogin.workKey);
        AMFree(rspLogin.pwtoken);
        AMFree(rspLogin.remark);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, &rspLogin.lastClientip);
	if(retCode != eOK)
	{
        AMFree(rspLogin.workKey);
        AMFree(rspLogin.pwtoken);
        AMFree(rspLogin.remark);
        AMFree(rspLogin.webmd5pw);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspLogin.bindid, &rspLogin.bindidLen);
	if(retCode != eOK)
	{
        AMFree(rspLogin.workKey);
        AMFree(rspLogin.pwtoken);
        AMFree(rspLogin.remark);
        AMFree(rspLogin.webmd5pw);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspLogin.rid, &rspLogin.ridLen);
	if(retCode != eOK)
	{
        AMFree(rspLogin.workKey);
        AMFree(rspLogin.pwtoken);
        AMFree(rspLogin.remark);
        AMFree(rspLogin.webmd5pw);
        AMFree(rspLogin.bindid);
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);
	
	//get encrypt key. 我们在此只取前8位,后面8位不取。而且这个动作必须立刻做.
	if(pIMnet->pVarKeeper->bHasWorkKey == AMFALSE && rspLogin.workKey != NULL)
	{
		pIMnet->pVarKeeper->bHasWorkKey = AMTRUE;
		memcpy(pIMnet->pVarKeeper->encryptKey, rspLogin.workKey, IMNET_MAX_KEY_LEN);
	}

	RSP_ADD_BIND_UID(head, rspLogin);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspLogin, sizeof(rspLogin), FreeImRspLogin);
}

/************************************************************************/
// UnpackImAckHealthCheck
/************************************************************************/
IMnetRetCode UnpackImAckHealthCheck(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	// nothing to do.
	return eOK;
}

/************************************************************************/
// UnpackImRspGetUserInfo
/************************************************************************/
IMnetRetCode UnpackImRspGetUserInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetUserInfo rspGetUserInfo;

	// clear all
	memset(&rspGetUserInfo, 0, sizeof(rspGetUserInfo));	

	//
	//0. init propertyNum.
	//
	rspGetUserInfo.propertyNum = 8;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetUserInfo.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, (AMInt32*)&rspGetUserInfo.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctByte(&pBufferTemp, &rspGetUserInfo.addcontactFlag);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctByte(&pBufferTemp, &rspGetUserInfo.sendmsgFlag);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, (AMInt32*)&rspGetUserInfo.activity);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctByte(&pBufferTemp, &rspGetUserInfo.actLevel);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctInt(&pBufferTemp, (AMInt32*)&rspGetUserInfo.needNextlevel);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctByte(&pBufferTemp, &rspGetUserInfo.imlevel);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctByte(&pBufferTemp, &rspGetUserInfo.mulsendflag);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	
	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreate(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetUserInfo, sizeof(rspGetUserInfo));
}

/************************************************************************/
// UnpackImRspGetGroup
/************************************************************************/
void FreeImRspGetGroup(EventContent* pContent)
{
    ImRspGetGroup* pRspGetGroup = (ImRspGetGroup*)pContent;
    UserGroupList* pGroupList = NULL;
    UserGroupList* pCurrentGroupList = NULL;
    
	if(pRspGetGroup->bindID)
	{
		AMFree(pRspGetGroup->bindID);
		pRspGetGroup->bindID = AMNULL;
	}
    //需要释放rspGetGroup.groupList里面已经申请的内存
    pCurrentGroupList = pRspGetGroup->groupList;
    while(pCurrentGroupList != NULL)
    {
        pGroupList		  = pCurrentGroupList->pNext;
        AMFree(pCurrentGroupList->groupName);
        AMFree(pCurrentGroupList);
        pCurrentGroupList = pGroupList;
    }
    pRspGetGroup->groupList = NULL;
}

IMnetRetCode UnpackImRspGetGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetGroup rspGetGroup;
	AMInt32 i;
	UserGroupList* pGroupList = NULL;
	UserGroupList* pCurrentGroupList = NULL;

	// clear all
	memset(&rspGetGroup, 0, sizeof(rspGetGroup));	

	//
	//0. init propertyNum.
	//
	rspGetGroup.propertyNum = 3;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetGroup.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, &rspGetGroup.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetVectorStructLen(&pBufferTemp, &rspGetGroup.groupCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspGetGroup.groupCount; i++)
	{
		pGroupList = NULL;
		pGroupList = (UserGroupList*)AMMalloc(sizeof(UserGroupList));
		if(pGroupList == NULL)
		{
			FreeImRspGetGroup((EventContent*)&rspGetGroup);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pGroupList, 0, sizeof(UserGroupList));
		getByte(pBufferTemp, pGroupList->num);

		retCode = GetSctLong(&pBufferTemp, &pGroupList->groupIDHigh, &pGroupList->groupIDLow);
        if(retCode != eOK)
        {
            AMFree(pGroupList);
            FreeImRspGetGroup((EventContent*)&rspGetGroup);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctLong(&pBufferTemp, &pGroupList->parentIDup, &pGroupList->parentIDlw);
        if(retCode != eOK)
        {
            AMFree(pGroupList);
            FreeImRspGetGroup((EventContent*)&rspGetGroup);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctString(&pBufferTemp, &pGroupList->groupName, &pGroupList->groupNameLen);
        if(retCode != eOK)
        {
            AMFree(pGroupList);
            FreeImRspGetGroup((EventContent*)&rspGetGroup);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        if(rspGetGroup.groupList == NULL)
            rspGetGroup.groupList = pGroupList;
        else
			pCurrentGroupList->pNext = pGroupList;
		pCurrentGroupList = pGroupList;
	}

	retCode = GetSctInt(&pBufferTemp, &rspGetGroup.timestamp);
	if(retCode != eOK)
	{
        FreeImRspGetGroup((EventContent*)&rspGetGroup);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
	RSP_ADD_BIND_UID(head, rspGetGroup);

    //4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetGroup, sizeof(rspGetGroup), FreeImRspGetGroup);
}

/************************************************************************/
// UnpackImRspGetContact
/************************************************************************/
void FreeImRspGetContact(EventContent* pContent)
{
    ImRspGetContact* pRspGetContact = (ImRspGetContact*)pContent;
    UserContactList* pContactList = NULL;
	UserContactList* pCurrentContactList = NULL;

	if(pRspGetContact->bindID)
	{
		AMFree(pRspGetContact->bindID);
		pRspGetContact->bindID = NULL;
	}
    //需要释放rspGetContact.contactList里面已经申请的内存
    pCurrentContactList = pRspGetContact->contactList;
    while(pCurrentContactList != NULL)
    {
        pContactList		= pCurrentContactList->pNext;
        AMFree(pCurrentContactList->contactInfo.contactID);
        AMFree(pCurrentContactList->contactInfo.importance);
        AMFree(pCurrentContactList->contactInfo.nickName);
        AMFree(pCurrentContactList);
        pCurrentContactList = pContactList;
    }
    pRspGetContact->contactList = NULL;
}

IMnetRetCode UnpackImRspGetContact(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetContact rspGetContact;
	AMInt32 i;
	UserContactList* pContactList = NULL;
	UserContactList* pCurrentContactList = NULL;

	// clear all
	memset(&rspGetContact, 0, sizeof(rspGetContact));	

	//
	//0. init propertyNum.
	//
	rspGetContact.propertyNum = 3;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetContact.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, &rspGetContact.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetVectorStructLen(&pBufferTemp, &rspGetContact.contactCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspGetContact.contactCount; i++)
	{
		pContactList = NULL;
		pContactList = (UserContactList*)AMMalloc(sizeof(UserContactList));
		if(pContactList == NULL)
		{
            FreeImRspGetContact((EventContent*)&rspGetContact);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pContactList, 0, sizeof(UserContactList));
		getByte(pBufferTemp, pContactList->num);
		
        retCode = GetSctString(&pBufferTemp, &pContactList->contactInfo.contactID, &pContactList->contactInfo.contactIDLen);
        if(retCode != eOK)
        {
            AMFree(pContactList);
            FreeImRspGetContact((EventContent*)&rspGetContact);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctString(&pBufferTemp, &pContactList->contactInfo.nickName, &pContactList->contactInfo.nickNameLen);
        if(retCode != eOK)
        {
            AMFree(pContactList->contactInfo.contactID);
            AMFree(pContactList);
            FreeImRspGetContact((EventContent*)&rspGetContact);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctString(&pBufferTemp, &pContactList->contactInfo.importance, &pContactList->contactInfo.importanceLen);
        if(retCode != eOK)
        {
            AMFree(pContactList->contactInfo.contactID);
            AMFree(pContactList->contactInfo.nickName);
            AMFree(pContactList);
            FreeImRspGetContact((EventContent*)&rspGetContact);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctLong(&pBufferTemp, &pContactList->contactInfo.groupIDHigh, &pContactList->contactInfo.groupIDLow);
        if(retCode != eOK)
        {
            AMFree(pContactList->contactInfo.contactID);
            AMFree(pContactList->contactInfo.nickName);
            AMFree(pContactList->contactInfo.importance);
            AMFree(pContactList);
            FreeImRspGetContact((EventContent*)&rspGetContact);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        if(rspGetContact.contactList == NULL)
            rspGetContact.contactList = pContactList;
        else
            pCurrentContactList->pNext = pContactList;
        pCurrentContactList = pContactList;
	}

	retCode = GetSctInt(&pBufferTemp, &rspGetContact.timestamp);
	if(retCode != eOK)
	{
        FreeImRspGetContact((EventContent*)&rspGetContact);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
	RSP_ADD_BIND_UID(head, rspGetContact);

    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetContact, sizeof(rspGetContact), FreeImRspGetContact);
}

void FreeImRspSearchUser(EventContent* pContent)
{
	ImRspSearchUser* pRspGetContact = (ImRspSearchUser*)pContent;
    SearchUserInfoList* pContactList = NULL;
	SearchUserInfoList* pCurrentContactList = NULL;

    //需要释放rspGetContact.contactList里面已经申请的内存
    pCurrentContactList = pRspGetContact->userList;
    while(pCurrentContactList != NULL)
    {
        pContactList		= pCurrentContactList->pNext;
        AMFree(pCurrentContactList->userInfo.contactID);
        AMFree(pCurrentContactList->userInfo.nickName);
        AMFree(pCurrentContactList->userInfo.city);
        AMFree(pCurrentContactList);
        pCurrentContactList = pContactList;
    }
    pRspGetContact->userList= NULL;

}

IMnetRetCode UnpackImRspSearchUser(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{

#ifdef AMOS_DEBUG
		AMPrintf("KKKK: UnpackImRspSearchUser() start");
#endif

	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspSearchUser rspSearchUser;
	AMInt32 i;
	SearchUserInfoList* pContactList = NULL;
	SearchUserInfoList* pCurrentContactList = NULL;

	// clear all
	memset(&rspSearchUser, 0, sizeof(rspSearchUser));	

	//
	//0. init propertyNum.
	//
	rspSearchUser.propertyNum = 3;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
	{
        return retCode;
   	}

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspSearchUser.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, &rspSearchUser.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	
	retCode = GetVectorStructLen(&pBufferTemp, &rspSearchUser.userCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	
	for(i=0; i<rspSearchUser.userCount; i++)
	{
		pContactList = NULL;
		pContactList = (SearchUserInfoList*)AMMalloc(sizeof(SearchUserInfoList));
		if(pContactList == NULL)
		{
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pContactList, 0, sizeof(SearchUserInfoList));
		getByte(pBufferTemp, pContactList->num);
		
        retCode = GetSctString(&pBufferTemp, &pContactList->userInfo.contactID, &pContactList->userInfo.contactIDLen);
        if(retCode != eOK)
        {
            AMFree(pContactList);
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctString(&pBufferTemp, &pContactList->userInfo.nickName, &pContactList->userInfo.nickNameLen);
        if(retCode != eOK)
        {
            AMFree(pContactList->userInfo.contactID);
            AMFree(pContactList);
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

		retCode = GetSctByte(&pBufferTemp, &pContactList->userInfo.age);
        if(retCode != eOK)
        {
            AMFree(pContactList->userInfo.contactID);
            AMFree(pContactList->userInfo.nickName);
            AMFree(pContactList);
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

		retCode = GetSctByte(&pBufferTemp, &pContactList->userInfo.gender);
        if(retCode != eOK)
        {
            AMFree(pContactList->userInfo.contactID);
            AMFree(pContactList->userInfo.nickName);
            AMFree(pContactList);
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

		
        retCode = GetSctString(&pBufferTemp, &pContactList->userInfo.city, &pContactList->userInfo.cityLen);
        if(retCode != eOK)
        {
            AMFree(pContactList->userInfo.contactID);
            AMFree(pContactList->userInfo.nickName);
            AMFree(pContactList);
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }

		retCode = GetSctByte(&pBufferTemp, &pContactList->userInfo.basicStatus);
        if(retCode != eOK)
        {
            AMFree(pContactList->userInfo.contactID);
            AMFree(pContactList->userInfo.nickName);
            AMFree(pContactList->userInfo.city);
            AMFree(pContactList);
            FreeImRspSearchUser((EventContent*)&rspSearchUser);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
	    if(rspSearchUser.userList== NULL)
    	{
	        rspSearchUser.userList = pContactList;
    	}
	    else
    	{
	        pCurrentContactList->pNext = pContactList;
    	}
        pCurrentContactList = pContactList;
	}

	retCode = GetSctInt(&pBufferTemp, &rspSearchUser.timestamp);
	if(retCode != eOK)
	{
        FreeImRspSearchUser((EventContent*)&rspSearchUser);
        UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);

	
#ifdef AMOS_DEBUG
	AMPrintf("UnpackImRspSearchUser() end ");
#endif
    
    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspSearchUser, sizeof(rspSearchUser), FreeImRspSearchUser);
}


/************************************************************************/
// UnpackGetBlack
/************************************************************************/
void FreeImRspCommonContactList(EventContent* pContent)
{
    ImRspCommonContactList* pCommonContactList = (ImRspCommonContactList*)pContent;
    ContactList* pList = NULL;
	ContactList* pCurrentList = NULL;

	if(pCommonContactList->bindID)
	{
		AMFree(pCommonContactList->bindID);
		pCommonContactList->bindID = AMNULL;
	}
    //需要释放pCommonContactList->contactList里面已经申请的内存
    pCurrentList = pCommonContactList->contactList;
    while(pCurrentList != NULL)
    {
        pList		 = pCurrentList->pNext;
        AMFree(pCurrentList->userID);
        AMFree(pCurrentList);
        pCurrentList = pList;
	}
    pCommonContactList->contactList = NULL;
}

IMnetRetCode UnpackImRspCommonContactList(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspCommonContactList rspCommonContactList;
	ContactList* pList = NULL;
	ContactList* pCurrentList = NULL;
	AMInt32 i;

	// clear all
	memset(&rspCommonContactList, 0, sizeof(rspCommonContactList));	

	//
	//0. init propertyNum.
	//
	rspCommonContactList.propertyNum = 3;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspCommonContactList.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspCommonContactList.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetVectorStrLen(&pBufferTemp, &rspCommonContactList.contactCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspCommonContactList.contactCount; i++)
	{
		pList = NULL;
		pList = (ContactList*)AMMalloc(sizeof(ContactList));
		if(pList == NULL)
		{
            FreeImRspCommonContactList((EventContent*)&rspCommonContactList);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pList, 0, sizeof(ContactList));

        retCode = GetStringAlloc(&pBufferTemp, &pList->userID, &pList->userIDLen);
        if(retCode != eOK)
        {
            FreeImRspCommonContactList((EventContent*)&rspCommonContactList);
			UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
		
		if(!pList->userID) {
			--rspCommonContactList.contactCount;
			continue;
		}
        
        if(rspCommonContactList.contactList == NULL)
            rspCommonContactList.contactList = pList;
        else
			pCurrentList->pNext = pList;
		pCurrentList = pList;
	}

	retCode = GetSctInt(&pBufferTemp, &rspCommonContactList.timestamp);
	if(retCode != eOK)
	{
        FreeImRspCommonContactList((EventContent*)&rspCommonContactList);
		UncompressBodyEnd(pNewBuffer);
        return retCode;
    }
    
    UncompressBodyEnd(pNewBuffer);
    
	RSP_ADD_BIND_UID(head, rspCommonContactList);

    //4. create event.
    return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspCommonContactList, sizeof(rspCommonContactList), FreeImRspCommonContactList);
}

/************************************************************************/
// UnpackImRspGetBlack
/************************************************************************/
IMnetRetCode UnpackImRspGetBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
    return UnpackImRspCommonContactList(pIMnet, ppEvt, cmd, pBuffer, Length);
}

/************************************************************************/
// UnpackImRspGetReverseBlack
/************************************************************************/
IMnetRetCode UnpackImRspGetReverseBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return UnpackImRspCommonContactList(pIMnet, ppEvt, cmd, pBuffer, Length);
}


void FreeImRspGetAppAddr(EventContent* pContent)
{
	ImRspGetAppAddr* pRspGetAddr = (ImRspGetAppAddr*)pContent;
	AMFree(pRspGetAddr->szSessionId);
	AMFree(pRspGetAddr->szServerIp);
}
/************************************************************************/
// UnpackImRspGetAppAddr
/************************************************************************/
IMnetRetCode UnpackImRspGetAppAddr(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetAppAddr rspGetAppAddr;

	// clear all
	memset(&rspGetAppAddr, 0, sizeof(rspGetAppAddr));	

	//
	//0. init propertyNum.
	//
	rspGetAppAddr.propertyNum = 7;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetAppAddr.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspGetAppAddr.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspGetAppAddr.szServerIp, &rspGetAppAddr.iServerIpLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctShort(&pBufferTemp, &rspGetAppAddr.uiServerPort);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctString(&pBufferTemp, &rspGetAppAddr.szSessionId, &rspGetAppAddr.iSessionIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctShort(&pBufferTemp, &rspGetAppAddr.uiAppType);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctShort(&pBufferTemp, &rspGetAppAddr.uiSubType);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetSctULong(&pBufferTemp, ((AMInt32*)&rspGetAppAddr.ulObjId)+1, (AMInt32*)&rspGetAppAddr.ulObjId);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	
	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetAppAddr, sizeof(rspGetAppAddr), FreeImRspGetAppAddr);
}

/************************************************************************/
// UnpackImRspGetContactStatus
/************************************************************************/
void FreeImRspGetContactStatus(EventContent* pContent)
{
    ImRspGetContactStatus* pRspGetContactStatus = (ImRspGetContactStatus*)pContent;
    ContactStatusList* pContactStatusList = NULL;
	ContactStatusList* pCurrentContactStatusList = NULL;
    //需要释放里面已经申请的内存
    pCurrentContactStatusList = pRspGetContactStatus->contactStatusList;
    while(pCurrentContactStatusList != NULL)
    {
        pContactStatusList		  = pCurrentContactStatusList->pNext;
        AMFree(pCurrentContactStatusList->userID);
        AMFree(pCurrentContactStatusList);
        pCurrentContactStatusList = pContactStatusList;
	}
    pRspGetContactStatus->contactStatusList = NULL;
}

IMnetRetCode UnpackImRspGetContactStatus(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetContactStatus rspGetContactStatus;
	AMInt32 i;
	ContactStatusList* pContactStatusList = NULL;
	ContactStatusList* pCurrentContactStatusList = NULL;

	// clear all
	memset(&rspGetContactStatus, 0, sizeof(rspGetContactStatus));	

	//
	//0. init propertyNum.
	//
	rspGetContactStatus.propertyNum = 2;

    //1. unpack head, decrypt body and check body.
    retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
    if(retCode != eOK)
        return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetContactStatus.propertyNum, tempNum);
	
	retCode = GetSctInt(&pBufferTemp, &rspGetContactStatus.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	retCode = GetVectorStructLen(&pBufferTemp, &rspGetContactStatus.contactStatusCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspGetContactStatus.contactStatusCount; i++)
	{
		pContactStatusList = NULL;
		pContactStatusList = (ContactStatusList*)AMMalloc(sizeof(ContactStatusList));
		if(pContactStatusList == NULL)
		{
            FreeImRspGetContactStatus((EventContent*)&rspGetContactStatus);
            UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pContactStatusList, 0, sizeof(ContactStatusList));
		getByte(pBufferTemp, pContactStatusList->num);
		
        retCode = GetSctString(&pBufferTemp, &pContactStatusList->userID, &pContactStatusList->userIDLen);
        if(retCode != eOK)
        {
            FreeImRspGetContactStatus((EventContent*)&rspGetContactStatus);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctByte(&pBufferTemp, &pContactStatusList->basicStatus);
        if(retCode != eOK)
        {
            AMFree(pContactStatusList->userID);
            FreeImRspGetContactStatus((EventContent*)&rspGetContactStatus);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        retCode = GetSctByte(&pBufferTemp, &pContactStatusList->predefStatus);
        if(retCode != eOK)
        {
            AMFree(pContactStatusList->userID);
            FreeImRspGetContactStatus((EventContent*)&rspGetContactStatus);
            UncompressBodyEnd(pNewBuffer);
            return retCode;
        }
        
        if(rspGetContactStatus.contactStatusList == NULL)
            rspGetContactStatus.contactStatusList = pContactStatusList;
        else
			pCurrentContactStatusList->pNext = pContactStatusList;
		pCurrentContactStatusList = pContactStatusList;
	}
	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspGetContactStatus, sizeof(rspGetContactStatus), FreeImRspGetContactStatus);
}

/************************************************************************/
// common components
/************************************************************************/
/************************************************************************/
// 二级协议的封包
/************************************************************************/
void MakeImMessageTextPacket(SecondProtocolId cmdID, 
                             AMChar* pInMessage, 
                             AMInt32 inMessageLen, 
                             AMInt32 ackSeq)
{
    //pack head.
    putByte(pInMessage, PROTOCOL_SECOND_HEAD_LENGTH);   //head length
    putByte(pInMessage, 0);                             //compress
    putShort(pInMessage, cmdID);                        //cmd id
    putInt(pInMessage, ackSeq);                         //ack seq

    //pack body.
    //nothing to do.
}

/************************************************************************/
// 二级协议的解包
/************************************************************************/
IMnetRetCode UnpackImMessageText(AMUInt8*  pBuffer, 
                                 AMInt32   bufferLen,
                                 ImMessageChildHead* pHead, 
                                 AMUInt8** ppUnpackBuffer,
                                 AMInt32*  pUnpackBufferLen)
{
    //unpack head.
    getByte(pBuffer, pHead->headLen);
    getByte(pBuffer, pHead->compress);
    getShort(pBuffer, pHead->cmd);
    getInt(pBuffer, pHead->ackSeq);

    //unpack body.
    *pUnpackBufferLen = bufferLen - pHead->headLen;
    if(*pUnpackBufferLen != 0)
    {
        *ppUnpackBuffer = (AMUInt8*)AMMalloc(*pUnpackBufferLen);
        if(*ppUnpackBuffer == NULL)
            return eMallocError;
        
        getString(pBuffer, (*ppUnpackBuffer), (*pUnpackBufferLen));
    }
    else
    {
        *ppUnpackBuffer = NULL;
    }
    return eOK;
}

/************************************************************************/
// 订阅消息相对于上面的普通消息，它没有消息头...
/************************************************************************/
IMnetRetCode UnpackImMessageText_Sub(AMUInt8*  pBuffer, 
								 AMInt32   bufferLen,
								 AMUInt8** ppUnpackBuffer,
								 AMInt32*  pUnpackBufferLen)
{
	//unpack body.
	*pUnpackBufferLen = bufferLen;
	if(*pUnpackBufferLen != 0)
	{
		*ppUnpackBuffer = (AMUInt8*)AMMalloc(*pUnpackBufferLen);
		if(*ppUnpackBuffer == NULL)
			return eMallocError;

		getString(pBuffer, (*ppUnpackBuffer), (*pUnpackBufferLen));
	}
	else
	{
		*ppUnpackBuffer = NULL;
	}
	return eOK;
}



/************************************************************************/
// unpack head, decrypt body and check body.
/************************************************************************/
IMnetRetCode UnpackHeadAndCheckProcedure(IMnet* pIMnet, 
                                         AMUInt8* pBuffer, 
                                         AMUInt8** ppBufferTemp, 
                                         PacketHead* pHead)
{
    IMnetRetCode retCode = eOK;
    //1. check Starter & LRC
    retCode = CheckStarterAndLrc(pBuffer);
    if(retCode!=eOK)
        return retCode;
    
    //2. unpack header
    memset(pHead, 0, sizeof(PacketHead));
    (*ppBufferTemp) = UnpackHead(pBuffer, pHead);
    
    //3. decrypt body
	if (pIMnet != AMNULL)
	{
		retCode = EncryptBody(pIMnet, pBuffer, pHead->extLength, pHead->bodyLength, pHead->encrypt, eDecrypt);
		if(retCode != eOK)
		    return retCode;
	}

    //4. check body.
    return CheckCC(pBuffer, 20, pHead->extLength, pHead->bodyLength);
}


IMnetRetCode FtsUnpackHeadAndCheck( AMUInt8* pBuffer, 
								   AMUInt8** ppBufferTemp, 
								   FtsPacketHead* pHead)
{
	IMnetRetCode retCode = eOK;

	if ((AMInt8)0x8f != (AMInt8)pBuffer[0]) 
	{
#ifdef AMOS_DEBUG
		AMPrintf( "invalid starter = 0x%02x.\n", pBuffer[0]);
#endif
		return eIMnetInvalidStarter;
	}

	//2. unpack header
	memset(pHead, 0, sizeof(FtsPacketHead));
	(*ppBufferTemp) = FtsUnpackHead(pBuffer, pHead);

	//4. check body.
	return CheckCC(pBuffer, 13, 0, pHead->uiLen);
}

/************************************************************************/
// HeadInit
/************************************************************************/
void HeadInit(PacketHead* pHead)
{
	if(pHead)
	{
		memset(pHead, 0, sizeof(PacketHead));
		pHead->starter = PROTOCOL_HEAD_STARTER;	
		pHead->major   = PROTOCOL_HEAD_MAJOR;		
		pHead->encrypt = PROTOCOL_HEAD_ENCRYPT;  //默认加密
	}
}

void FtsHeadInit( FtsPacketHead *pHead)
{
	AMAssert(pHead);
	memset(pHead, 0, sizeof(FtsPacketHead));
	pHead->uiStarter = 0x8f;
	pHead->uiVersion = 0x0101;
}

/************************************************************************/
// PackAllocate
/************************************************************************/
IMnetRetCode PackAllocate(PacketHead* pHead, AMUInt8** ppBuffer, 
						  AMInt32 *pLength, short reserved, 
						  char* pExtData, AMInt32 extDataLen, 
                          AMInt32 bodyLength)
{
	AMInt32 length = 0;

	pHead->bodyLength = getProtocolBodyLength(bodyLength);
	if(/*reserved != 0 && */pExtData != NULL)
	{
		pHead->reserved = 1;
		pHead->extLength = 4 + extDataLen; // add 4 first.
		memcpy(pHead->extData, pExtData, extDataLen);
	}

	//Head Length
	length += PROTOCOL_HEAD_LENGTH;
	//ext Length
	length += pHead->extLength;
	//body
	length += pHead->bodyLength;

	//return value
	*pLength = length;
	//malloc buffer
	*ppBuffer = (AMUInt8*)AMMalloc(length);

	if(*ppBuffer == NULL)
	{
		return eMallocError;
	}
	else
	{
		memset(*ppBuffer, 0, length);
	}

	return eOK;
}


IMnetRetCode FtsPackAllocate( FtsPacketHead* pHead, AMUInt8** ppBuffer, 
							 AMInt32 *pLength, AMInt32 bodyLength)
{
	AMInt32 length = 0;

	length = getProtocolBodyLength(bodyLength);
	//Head Length
	length += PROTOCOL_HEAD_LENGTH;	
	//body
	*pLength += length;

	//return value
	*pLength = length;
	//malloc buffer
	*ppBuffer = (AMUInt8*)AMMalloc(length);

	if(*ppBuffer == NULL)
		return eMallocError;
	else
		memset(*ppBuffer, 0, length);

	pHead->uiLen = length-PROTOCOL_HEAD_LENGTH;

	return eOK;
}

/************************************************************************/
// PackHead
/************************************************************************/
AMUInt8* PackHead(AMUInt8* pBufferTemp, PacketHead* pHead)
{
	AMInt32 length = 0;
	putByte(pBufferTemp, pHead->starter);
	putByte(pBufferTemp, pHead->major);
	putByte(pBufferTemp, pHead->minor);
	putByte(pBufferTemp, pHead->msgtype);
	putByte(pBufferTemp, pHead->encrypt);
	putByte(pBufferTemp, pHead->compress);
	putByte(pBufferTemp, pHead->encode);
	putByte(pBufferTemp, pHead->lrc);
	putInt(pBufferTemp, pHead->seq);
	putInt(pBufferTemp, (pHead->extLength+pHead->bodyLength));
	putInt(pBufferTemp, pHead->cmd);
	putShort(pBufferTemp, pHead->cc);
	putShort(pBufferTemp, pHead->reserved);
	if (1 == pHead->reserved) 
	{
		putInt(pBufferTemp, strlen(pHead->extData));
		//denx : 不要使用sprintf,在某些平台会导致内存异常
		//pBufferTemp += sprintf((AMChar*)pBufferTemp, "%s", pHead->extData);
		length = strlen(pHead->extData);
		memcpy((AMChar*)pBufferTemp, pHead->extData, length);
		pBufferTemp += length;
	}

	return pBufferTemp;
}

AMUInt8 *FtsPackHead(AMUInt8 *pBufferTemp, FtsPacketHead *pHead)
{
	putByte(pBufferTemp, pHead->uiStarter);
	putShort(pBufferTemp, pHead->uiVersion);
	putShort(pBufferTemp, pHead->uiCmd);
	putInt(pBufferTemp, pHead->uiSessionNo);
	putInt(pBufferTemp, pHead->uiSeq);
	putShort(pBufferTemp, pHead->uiCC);
	putInt(pBufferTemp, pHead->uiLen);
	putByte(pBufferTemp, pHead->uiFlag);
	putInt(pBufferTemp, pHead->uiReserved);
	return pBufferTemp;
}

void FtsResetHead(AMUInt8* pBuffer, AMInt32 bodyLength)
{
	short cc = 0;
	AMUInt8 lrc = 0;
	AMUInt8* pBufferTemp2 = NULL;

	cc = GetCC(pBuffer, PROTOCOL_HEAD_LENGTH, bodyLength);
	pBufferTemp2 = pBuffer + 13;
	putShort(pBufferTemp2, cc);
	pBufferTemp2 = pBuffer +15;
	putInt(pBufferTemp2, bodyLength);
}

/************************************************************************/
// ResetHead
/************************************************************************/
void ResetHead(AMUInt8* pBuffer, AMInt32 extLength, AMInt32 bodyLength)
{
	short cc = 0;
	AMUInt8 lrc = 0;
	AMUInt8* pBufferTemp2 = NULL;

	cc = GetCC(pBuffer, PROTOCOL_HEAD_LENGTH + extLength, bodyLength);
	pBufferTemp2 = pBuffer;
	pBufferTemp2 += 20;
	putShort(pBufferTemp2, cc);

	lrc = GetLRC(pBuffer, 0, PROTOCOL_HEAD_LENGTH);
	pBufferTemp2 = pBuffer;
	pBufferTemp2 += 7;
	putByte(pBufferTemp2, lrc);
}

/************************************************************************/
// UnpackHead
/************************************************************************/
AMUInt8* UnpackHead(AMUInt8* pBuffer, PacketHead* pHead)
{
	getByte(pBuffer, pHead->starter);
	getByte(pBuffer, pHead->major);
	getByte(pBuffer, pHead->minor);
	getByte(pBuffer, pHead->msgtype);
	getByte(pBuffer, pHead->encrypt);
	getByte(pBuffer, pHead->compress);
	getByte(pBuffer, pHead->encode);
	getByte(pBuffer, pHead->lrc);
	getInt(pBuffer, pHead->seq);
	getInt(pBuffer, pHead->bodyLength);
	getInt(pBuffer, pHead->cmd);
	getShort(pBuffer, pHead->cc);
	getShort(pBuffer, pHead->reserved);
	if(1 == pHead->reserved)
	{
		getInt(pBuffer, pHead->extLength);
		getString(pBuffer, pHead->extData, pHead->extLength);
		pHead->extLength += 4;
		pHead->bodyLength -= pHead->extLength;
	}
	
	return pBuffer;
}


AMUInt8* FtsUnpackHead(AMUInt8* pBufferTemp, FtsPacketHead* pHead)
{
	getByte(pBufferTemp, pHead->uiStarter);
	getShort(pBufferTemp, pHead->uiVersion);
	getShort(pBufferTemp, pHead->uiCmd);
	getInt(pBufferTemp, pHead->uiSessionNo);
	getInt(pBufferTemp, pHead->uiSeq);
	getShort(pBufferTemp, pHead->uiCC);
	getInt(pBufferTemp, pHead->uiLen);
	getByte(pBufferTemp, pHead->uiFlag);
	getInt(pBufferTemp, pHead->uiReserved);
	return pBufferTemp;
}
/************************************************************************/
//UncompressBodyBegin and UncompressBodyEnd 需成对使用
/************************************************************************/
IMnetRetCode UncompressBodyBegin(IMnet* pIMnet,
								 AMUInt8* pBufferRoot, 
								 AMUInt8** ppBuffer, 
								 PacketHead* pHead, 
								 AMUInt8** ppNewBuffer)
{
	AMInt32 bodyLen = 0;
	AMInt32 compLen = 0;
	AMUInt8* pZipBuffer = NULL;
	
	*ppNewBuffer = NULL;

	if(1==pHead->compress)
	{
		bodyLen = pHead->bodyLength;
		
		getInt((*ppBuffer), compLen);

		pZipBuffer = (AMUInt8*)AMMalloc(compLen);
		memset(pZipBuffer, 0, compLen);
		if(ZipInflate(*ppBuffer, (bodyLen - 4), pZipBuffer, compLen) != compLen)
		{
			//uncompress error.
			AMFree(pZipBuffer);
			return eIMnetInflateError;
		}
		
		*ppNewBuffer = (AMUInt8*)AMMalloc(PROTOCOL_HEAD_LENGTH+compLen);
		memcpy(*ppNewBuffer, pBufferRoot, PROTOCOL_HEAD_LENGTH);
		memcpy((*ppNewBuffer)+PROTOCOL_HEAD_LENGTH, pZipBuffer, compLen);
		*ppBuffer = (*ppNewBuffer)+PROTOCOL_HEAD_LENGTH;

		AMFree(pZipBuffer);
	}

	return eOK;
}

void UncompressBodyEnd(AMUInt8* pbuffer)
{
	AMFree(pbuffer);
}

/************************************************************************/
// EncryptBody
/************************************************************************/
IMnetRetCode EncryptBody(IMnet* pIMnet, AMUInt8* pBuffer, AMInt32 extLength, 
						 AMInt32 bodyLength, AMInt32 encrypt, EncryptType flag)
{
	AMUInt8* pBodyData = NULL;
	AMChar tmpdata[IMNET_MAX_KEY_LEN];
	AMChar cmp[IMNET_MAX_KEY_LEN];

	AMInt32 i;
	if(PROTOCOL_HEAD_NO_ENCRYPT == encrypt)
		return eOK;
	
#ifdef AMOS_DEBUG
	if(bodyLength%8 != 0)
    {
        AMPrintf( "xxxxxxxx EncryptBody error !! xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        AMAssert(0);
    }
#endif

	pBodyData = (AMUInt8*)AMMalloc(bodyLength);
	if(pBodyData == NULL)
	{
	#ifdef AMOS_DEBUG
		AMPrintf( "EncryptBody:body data zero.\n");
	#endif
		return eIMnetBodyDataZero;
	}

	memcpy(pBodyData, pBuffer + PROTOCOL_HEAD_LENGTH + extLength, bodyLength);
	
	//denx: compare encrypt key.
	memset(cmp, 0, sizeof(cmp));
	if(memcmp(pIMnet->pVarKeeper->encryptKey, cmp, sizeof(cmp)) == 0)
	{
	#ifdef AMOS_DEBUG
		AMPrintf( "EncryptBody:encryptKey isn't ready.\n");
	#endif
		AMFree(pBodyData);
		return eIMnetEncryptKeyLost;
	}
	else
	{
		for (i = 0; i < bodyLength / 8; i++) 
		{
			memcpy(tmpdata, pBodyData+i*8, 8);
			DesEncrypt(
				(AMUInt8*)pIMnet->pVarKeeper->encryptKey,
				(AMUInt8*)tmpdata,
				flag);

			memcpy(pBodyData+i*8, tmpdata, 8);
		}
	}

	memcpy(pBuffer + PROTOCOL_HEAD_LENGTH + extLength, pBodyData, bodyLength);

	AMFree(pBodyData);
	return eOK;
}

/************************************************************************/
// CheckStarterAndLrc
/************************************************************************/
IMnetRetCode CheckStarterAndLrc(AMUInt8* byteBuffer) 
{
	if ((AMInt8)PROTOCOL_HEAD_STARTER != (AMInt8)byteBuffer[0]) 
	{
		#ifdef AMOS_DEBUG
		AMPrintf( "invalid starter = 0x%02x.\n", byteBuffer[0]);
		#endif
		return eIMnetInvalidStarter;
	}

	if (0 != GetLRC(byteBuffer, 0, PROTOCOL_HEAD_LENGTH)) 
	{
		#ifdef AMOS_DEBUG
		AMPrintf( "invalid packet,check LRC error.\n");
		#endif
		return eIMnetInvalidLRC;
	}

	return eOK;
}

/************************************************************************/
// CheckCC
/************************************************************************/
IMnetRetCode CheckCC(AMUInt8* byteBuffer, AMInt32 iPos, AMInt32 extLength, AMInt32 bodyLength)
{
	short value = getShortValue(byteBuffer, iPos);
	
	if(value != GetCC(byteBuffer, PROTOCOL_HEAD_LENGTH+extLength, bodyLength))
	{
	#ifdef AMOS_DEBUG
		AMPrintf( "CheckCC:error.\n");
	#endif	
		return eIMnetInvalidCC;
	}

	return eOK;
}

//以下为群的协议的Packet

IMnetRetCode PackImReqGetTribeGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetAddTribeGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqUpdateTribeGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqDelTribeGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqShallowLoginTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return PackImReqCommonSimple(pIMnet, pEvt, ppBuffer, pLength);
}

IMnetRetCode PackImReqDeepLoginTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqDeepLoginTribe	*pRequest = (ImReqDeepLoginTribe *)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = pRequest->tribeIdLen + 6;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 2;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	
	putSctString(pBufferTemp, pRequest->tribeId, pRequest->tribeIdLen);

	//
	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode PackImReqInviteTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqOnInviteJoinTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqAskJoinTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqExamAskJoinTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqChgLevelTribeMember(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqChgTribeGroup(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqAddStarMember(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqDelStarMember(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqDelTribeMember(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetTribeBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqAddTribeBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqDelTribeBlack(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqQuitTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqCloseTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetTribeInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqModifyTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetTribeMemberInfo(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqSendTribeMsg(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqGetTribeConfig(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqSetTribeConfig(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqSetOpenTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqVisitTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqClearVisitor(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqStartTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqRecommendTribe(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqAuthRecommend(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode PackImReqUpdateTribeCard(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetTribeGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetAddTribeGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspUpdateTribeGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspDelTribeGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

void	DestroyImTribeId(IMTribeId *pTribeId)
{
	IMTribeId	*pCurrentImTribeId = pTribeId;
	while(pCurrentImTribeId)
	{
		if(pCurrentImTribeId->id)
			AMFree(pCurrentImTribeId->id);
		if(pCurrentImTribeId->name)
			AMFree(pCurrentImTribeId->name);
		if(pCurrentImTribeId->extSign)
			AMFree(pCurrentImTribeId->extSign);
		pTribeId = pCurrentImTribeId->pNext;
		AMFree(pCurrentImTribeId);
		pCurrentImTribeId = pTribeId;
	}
}

void	FreeImRspShallowLoginTribe(EventContent* pContent)
{
	ImRspShallowLoginTribe* pRspShallowLoginTribe = (ImRspShallowLoginTribe*)pContent;
	DestroyImTribeId(pRspShallowLoginTribe->pImTribeIds);
	pRspShallowLoginTribe->pImTribeIds = NULL;
}

PCRetCode	GetSctTribeId(AMUInt8 **ppBuffer, IMTribeId	**ppId)
{
	IMnetRetCode retCode = eOK;
	IMTribeId	*	pNewTribeId = NULL;
	AMUInt8		tmp = 0;

	getByte(*ppBuffer, tmp);//一个'\07'不知道是什么意思，就当是padding了...

	pNewTribeId = (IMTribeId*)AMMalloc(sizeof(IMTribeId));
	if(!pNewTribeId)
		return eMallocError;

	AMMemset(pNewTribeId, 0, sizeof(IMTribeId));
	do 
	{
		if(eOK != (retCode = GetSctString(ppBuffer, (AMInt8**)&pNewTribeId->id, &pNewTribeId->idLen))
			|| eOK != (retCode = GetSctString(ppBuffer, (AMInt8**)&pNewTribeId->name, &pNewTribeId->nameLen))
			|| eOK != (retCode = GetSctByte(ppBuffer, &pNewTribeId->level))
			|| eOK != (retCode = GetSctByte(ppBuffer, &pNewTribeId->status))
			|| eOK != (retCode = GetSctString(ppBuffer, (AMInt8**)&pNewTribeId->extSign, &pNewTribeId->extSignLen))
			|| eOK != (retCode = GetSctInt(ppBuffer, &pNewTribeId->stamp))
			|| eOK != (retCode = GetSctByte(ppBuffer, &pNewTribeId->open)))
			break;

		*ppId = pNewTribeId;
		return eOK;
	} while (0);
	
	DestroyImTribeId(pNewTribeId);
	return retCode;
}

IMnetRetCode UnpackImRspShallowLoginTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspShallowLoginTribe rspShallowLoginTribe;
	AMInt32 i;
	IMTribeId* pTailImTribeIdList = NULL, * pNewTribeId = NULL;

	// clear all
	memset(&rspShallowLoginTribe, 0, sizeof(rspShallowLoginTribe));	

	//
	//0. init propertyNum.
	//
	rspShallowLoginTribe.propertyNum = 2;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetContactStatus.propertyNum, tempNum);

	retCode = GetSctByte(&pBufferTemp, &rspShallowLoginTribe.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetVectorStructLen(&pBufferTemp, &rspShallowLoginTribe.tribeInfoCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	for(i=0; i<rspShallowLoginTribe.tribeInfoCount; i++)
	{
		retCode = GetSctTribeId(&pBufferTemp, &pNewTribeId);

		if(retCode != eOK)
		{
			FreeImRspShallowLoginTribe((EventContent*)&rspShallowLoginTribe);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		if(!pTailImTribeIdList)
			rspShallowLoginTribe.pImTribeIds = pNewTribeId;
		else
			pTailImTribeIdList->pNext = pNewTribeId;

		pTailImTribeIdList = pNewTribeId;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspShallowLoginTribe, sizeof(rspShallowLoginTribe), FreeImRspShallowLoginTribe);
}

void	DestroyImTribeMemStatus(IMTribeMemStatus *pMemStatus)
{
	IMTribeMemStatus	*pCurrentStatus = pMemStatus;
	while(pCurrentStatus)
	{
		if(pCurrentStatus->id)
			AMFree(pCurrentStatus->id);
		if(pCurrentStatus->name)
			AMFree(pCurrentStatus->name);

		pMemStatus = pCurrentStatus->pNext;
		AMFree(pCurrentStatus);
		pCurrentStatus = pMemStatus;
	}
}

void	FreeImRspDeepLoginTribe(EventContent* pContent)
{
	ImRspDeepLoginTribe* pRspDeepLoginTribe = (ImRspDeepLoginTribe*)pContent;
	DestroyImTribeMemStatus(pRspDeepLoginTribe->pMemStatus);
	AMFree(pRspDeepLoginTribe->tribeId);
	pRspDeepLoginTribe->pMemStatus = NULL;
}

void	FreeIMTribeInfo(IMTribeInfo *pInfo)
{

}

IMnetRetCode	GetSctTribeInfo(AMUInt8** ppbuffer, IMTribeInfo *pInfo)
{
	IMnetRetCode	retCode = 0;
	
	do 
	{
		if(eOK != (retCode = GetSctString(ppbuffer, &pInfo->id, &pInfo->idLen))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->name, &pInfo->nameLen))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->masterId, &pInfo->masterIdLen))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->category, &pInfo->categoryLen))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->describe, &pInfo->describeLen))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->bulletin, &pInfo->bulletinLen))
			|| eOK != (retCode = GetSctByte(ppbuffer, &pInfo->check_mode))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->password, &pInfo->passwordLen))
			|| eOK != (retCode = GetSctString(ppbuffer, &pInfo->keyword, &pInfo->keywordLen))
			/**/)
			break;

	} while (0);

	return retCode;
}

IMnetRetCode UnpackImRspDeepLoginTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspDeepLoginTribe rspDeepLoginTribe;
	IMTribeMemStatus	* pTailMemStatus = NULL, * pNewMemStatus = NULL;

	// clear all
	memset(&rspDeepLoginTribe, 0, sizeof(rspDeepLoginTribe));	

	//
	//0. init propertyNum.
	//
	rspDeepLoginTribe.propertyNum = 2;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspGetContactStatus.propertyNum, tempNum);

	retCode = GetSctByte(&pBufferTemp, &rspDeepLoginTribe.retCode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspDeepLoginTribe.tribeId, &rspDeepLoginTribe.tribeIdLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}




	UncompressBodyEnd(pNewBuffer);
	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspDeepLoginTribe, sizeof(rspDeepLoginTribe), FreeImRspDeepLoginTribe);
}

IMnetRetCode UnpackImRspInviteTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspOnInviteJoinTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspAskJoinTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspExamAskJoinTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspChgLevelTribeMember(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspChgTribeGroup(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspAddStarMember(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspDelStarMember(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspDelTribeMember(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetTribeBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspAddTribeBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspDelTribeBlack(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspQuitTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspCloseTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetTribeInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspModifyTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetTribeMemberInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspSendTribeMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspGetTribeConfig(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspSetTribeConfig(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspSetOpenTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspVisitTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspClearVisitor(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspStartTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspRecommendTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspAuthRecommend(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImRspUpdateTribeCard(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}


IMnetRetCode UnpackImNtfInviteTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfAskJoinTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNetTribeMsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfTribeSysmsg(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

IMnetRetCode UnpackImNtfRecommendTribe(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	return eIMnetUnsupportedFeature;
}

/************************************************************************/
// UnpackImRspGetCNExtraInfo
/************************************************************************/
void FreeImRspCNExtraInfo(EventContent* pContent)
{
	ImRspGetCNExtraInfo* pCNExtraInfo = (ImRspGetCNExtraInfo*)pContent;
	Contact_ExtraInfo* pList = NULL;
	Contact_ExtraInfo* pCurrentList = NULL;

	//需要释放pCommonContactList->contactList里面已经申请的内存
	pCurrentList = pCNExtraInfo->contactExtraInfos;
	while(pCurrentList != NULL)
	{
		pList		 = pCurrentList->pNext;
		if(pCurrentList->userID)
			AMFree(pCurrentList->userID);
		if(pCurrentList->phone)
			AMFree(pCurrentList->phone);
		AMFree(pCurrentList);
		pCurrentList = pList;
	}
	pCNExtraInfo->contactExtraInfos = NULL;
}

IMnetRetCode UnpackImRspGetCNExtraInfo(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetCNExtraInfo rspCNExtraInfo;
	Contact_ExtraInfo* pList = NULL;
	Contact_ExtraInfo* pCurrentList = NULL;
	AMInt32 i;

	// clear all
	memset(&rspCNExtraInfo, 0, sizeof(rspCNExtraInfo));	

	//
	//0. init propertyNum.
	//
	rspCNExtraInfo.propertyNum = 3;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspCNExtraInfo.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspCNExtraInfo.retcode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rspCNExtraInfo.timestamp);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetVectorStructLen(&pBufferTemp, &rspCNExtraInfo.contactCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspCNExtraInfo.contactCount; i++)
	{
		pList = NULL;
		pList = (Contact_ExtraInfo*)AMMalloc(sizeof(Contact_ExtraInfo));
		if(pList == NULL)
		{
			FreeImRspCNExtraInfo((EventContent*)&rspCNExtraInfo);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pList, 0, sizeof(Contact_ExtraInfo));
		getByte(pBufferTemp, pList->propertyNum);

		retCode = GetSctString(&pBufferTemp, &pList->userID, &pList->userIDLen);
		if(retCode != eOK)
		{
			FreeImRspCNExtraInfo((EventContent*)&rspCNExtraInfo);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		retCode = GetSctInt(&pBufferTemp, &pList->result);
		if(retCode != eOK)
		{
			FreeImRspCNExtraInfo((EventContent*)&rspCNExtraInfo);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}


		retCode = GetSctString(&pBufferTemp, &pList->phone, &pList->phoneLen);
		if(retCode != eOK)
		{
			FreeImRspCNExtraInfo((EventContent*)&rspCNExtraInfo);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		if(!pList->userID) {
			--rspCNExtraInfo.contactCount;
			continue;
		}

		if(rspCNExtraInfo.contactExtraInfos == NULL)
			rspCNExtraInfo.contactExtraInfos = pList;
		else
			pCurrentList->pNext = pList;
		pCurrentList = pList;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspCNExtraInfo, sizeof(rspCNExtraInfo), FreeImRspCNExtraInfo);
}

/************************************************************************/
// UnpackImRspGetWebBinding
/************************************************************************/
void FreeImRspGetWebBinding(EventContent* pContent)
{
	ImRspGetWebBinding* pWebBinding = (ImRspGetWebBinding*)pContent;
	Bind_Service* pList = NULL;
	Bind_Service* pCurrentList = NULL;
	String_List* pStrList = NULL;
	String_List* pCurrentStrList = NULL;

	if(pWebBinding->aliUID)
		AMFree(pWebBinding->aliUID);
	if(pWebBinding->aliUIDToken)
		AMFree(pWebBinding->aliUIDToken);

	pCurrentList = pWebBinding->bindList;
	while(pCurrentList != NULL)
	{
		pList = pCurrentList->pNext;
		if(pCurrentList->serviceID)
			AMFree(pCurrentList->serviceID);
		if(pCurrentList->siteID)
			AMFree(pCurrentList->siteID);
		if(pCurrentList->webID)
			AMFree(pCurrentList->webID);
		if(pCurrentList->webUid)
			AMFree(pCurrentList->webUid);

		pCurrentStrList = pCurrentList->webUrl;
		while(pCurrentStrList != NULL)
		{
			pStrList = pCurrentStrList->pNext;
			if(pCurrentStrList->str)
				AMFree(pCurrentStrList->str);
			AMFree(pCurrentStrList);
			pCurrentStrList = pStrList;
		}

		AMFree(pCurrentList);
		pCurrentList = pList;
	}
	pWebBinding->bindList = NULL;
}

IMnetRetCode PackImReqGetWebBinding(IMnet* pIMnet, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength)
{
	IMnetRetCode retCode;
	PacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	ImReqGetWebBinding* pRequest = (ImReqGetWebBinding*)pEvt->pContent;

	//
	//1. create head
	//
	HeadInit(&head);
	head.cmd	 = pEvt->id; 

	//
	//2. alloc buffer
	//
	//Protocol Length
	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 1+2+4+2+4;

	retCode = PackAllocate(&head, ppBuffer, pLength, 0, 0, 0, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = PackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	pRequest->propertyNum = 2;
	if(pRequest->propertyNum != 0)
		putByte(pBufferTemp, pRequest->propertyNum);	

	putByte(pBufferTemp, FT_VECTOR);						
	putByte(pBufferTemp, FT_STRUCT);						
	putInt(pBufferTemp, 0);							

	putByte(pBufferTemp, FT_VECTOR);						
	putByte(pBufferTemp, FT_STRING);						
	putInt(pBufferTemp, 0);							

	//5. reset head
	//
	ResetHead(*ppBuffer, head.extLength, head.bodyLength);

	//
	//6. EncryptBody
	//
	return EncryptBody(pIMnet, *ppBuffer, head.extLength, head.bodyLength, head.encrypt, eEncrypt);
}

IMnetRetCode UnpackImRspGetWebBinding(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImRspGetWebBinding rspWebBinding;
	Bind_Service* pBindServiceList = NULL;
	Bind_Service* pCurBindServiceList = NULL;
	String_List* pStrList = NULL;
	String_List* pCurStrList = NULL;
	AMInt32 i;

	// clear all
	memset(&rspWebBinding, 0, sizeof(rspWebBinding));	

	//
	//0. init propertyNum.
	//
	rspWebBinding.propertyNum = 3;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspWebBinding.propertyNum, tempNum);

	retCode = GetSctInt(&pBufferTemp, &rspWebBinding.retcode);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspWebBinding.aliUID, &rspWebBinding.aliUIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rspWebBinding.aliUIDToken, &rspWebBinding.aliUIDTokenLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetVectorStructLen(&pBufferTemp, &rspWebBinding.bindListCount);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}
	for(i=0; i<rspWebBinding.bindListCount; i++)
	{
		pBindServiceList = NULL;
		pBindServiceList = (Bind_Service*)AMMalloc(sizeof(Bind_Service));
		if(pBindServiceList == NULL)
		{
			FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
			UncompressBodyEnd(pNewBuffer);
			return eMallocError;
		}
		memset(pBindServiceList, 0, sizeof(Bind_Service));
		getByte(pBufferTemp, pBindServiceList->propertyNum);

		retCode = GetSctString(&pBufferTemp, &pBindServiceList->serviceID, &pBindServiceList->serviceIDLen);
		if(retCode != eOK)
		{
			FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		retCode = GetSctString(&pBufferTemp, &pBindServiceList->siteID, &pBindServiceList->siteIDLen);
		if(retCode != eOK)
		{
			FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		retCode = GetSctString(&pBufferTemp, &pBindServiceList->webID, &pBindServiceList->webIDLen);
		if(retCode != eOK)
		{
			FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		retCode = GetSctString(&pBufferTemp, &pBindServiceList->webUid, &pBindServiceList->webUidLen);
		if(retCode != eOK)
		{
			FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}

		//TODO web_url parse
		retCode = GetVectorStrLen(&pBufferTemp, &pBindServiceList->webUrlCount);
		if(retCode != eOK)
		{
			UncompressBodyEnd(pNewBuffer);
			return retCode;
		}
		for(i=0; i<pBindServiceList->webUrlCount; i++)
		{
			pStrList = NULL;
			pStrList = (String_List*)AMMalloc(sizeof(*pStrList));
			if(pStrList == NULL)
			{
				FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
				UncompressBodyEnd(pNewBuffer);
				return eMallocError;
			}
			memset(pStrList, 0, sizeof(*pStrList));

			retCode = GetStringAlloc(&pBufferTemp, &pStrList->str, &pStrList->strLen);
			if(retCode != eOK)
			{
				FreeImRspGetWebBinding((EventContent*)&rspWebBinding);
				UncompressBodyEnd(pNewBuffer);
				return retCode;
			}

			if(!pStrList->str) {
				--pBindServiceList->webUrlCount;
				continue;
			}

			if(pBindServiceList->webUrl == NULL)
				pBindServiceList->webUrl = pStrList;
			else
				pCurStrList->pNext = pStrList;
			pCurStrList = pStrList;
		}

		if(rspWebBinding.bindList == NULL)
			rspWebBinding.bindList = pBindServiceList;
		else
			pCurBindServiceList->pNext = pBindServiceList;
		pCurBindServiceList = pBindServiceList;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rspWebBinding, sizeof(rspWebBinding), FreeImRspGetWebBinding);
}

void FreeImNtfWebUserMessage(EventContent* pContent)
{
	ImNtfWebUserMessage* pRsp = (ImNtfWebUserMessage*)pContent;
	if(pRsp->pOhtData)
	{
		destruct(OHTable, pRsp->pOhtData);
		AMFree(pRsp->pOhtData);
	}
	if(pRsp->fromID)
	{
		AMFree(pRsp->fromID);
		pRsp->fromID = NULL;
	}
	if(pRsp->serviceID)
	{
		AMFree(pRsp->serviceID);
		pRsp->serviceID = NULL;
	}
	if(pRsp->webID)
	{
		AMFree(pRsp->webID);
		pRsp->webID = NULL;
	}
}


IMnetRetCode UnpackImNtfWebUserMessage(IMnet* pIMnet, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	PacketHead head;
	AMUInt8 tempNum;
	ImNtfWebUserMessage rsp;

	// clear all
	memset(&rsp, 0, sizeof(rsp));	

	//
	//0. init propertyNum.
	//
	rsp.propertyNum = 5;

	//1. unpack head, decrypt body and check body.
	retCode = UnpackHeadAndCheckProcedure(pIMnet, pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//2. uncompress body
	UncompressBodyBegin(pIMnet, pBuffer, &pBufferTemp, &head, &pNewBuffer);

	//3. unpack body
	getByte(pBufferTemp, tempNum);
	IMnetCheckPropertyNum(rspAddBlack.propertyNum, tempNum);

	retCode = GetSctString(&pBufferTemp, &rsp.fromID, &rsp.fromIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rsp.serviceID, &rsp.serviceIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctString(&pBufferTemp, &rsp.webID, &rsp.webIDLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctInt(&pBufferTemp, &rsp.cmdId);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	retCode = GetSctStrStrMap(&pBufferTemp, &rsp.pOhtData, &rsp.iOhtDataLen);
	if(retCode != eOK)
	{
		UncompressBodyEnd(pNewBuffer);
		return retCode;
	}

	UncompressBodyEnd(pNewBuffer);

	//4. create event.
	return EventCreateEx(pIMnet->hPCHandle, ppEvt, cmd, (void*)&rsp, sizeof(rsp), FreeImNtfWebUserMessage);
}


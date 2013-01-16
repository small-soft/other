#include "IMnetMain.h"

#include "IMnetUtility.h"
#include "IMnetPacket.h"
/************************************************************************/
//IMnet Subsystem
/************************************************************************/
void VarKeeperCreate(VarKeeper** ppObject)
{
	const AMUInt8 key[] = {
		0xc5, 0x96, 0xbb, 0x17, 0xc9, 0x1f, 0x41, 0x3a
	};
	
	if(ppObject == NULL)
		return;
	
	(*ppObject) = (VarKeeper*)AMMalloc(sizeof(VarKeeper));
	if(*ppObject)
		memset(*ppObject, 0, sizeof(VarKeeper));
    else
    {
        AMAssert(0);
        return;
    }
	
	memcpy((*ppObject)->constDesKey, key, sizeof(key));
	memcpy((*ppObject)->constVersion, IM_PROTOCOL_VERSION, sizeof(IM_PROTOCOL_VERSION));
}

void VarKeeperDestory(VarKeeper** ppObject)
{
	if(ppObject != NULL)
	{
		AMFree(*ppObject);
		*ppObject = NULL;
	}
}

PCRetCode IMnetReceiver(PCHandle hHandle, Event* pEvent, PCReference ref)
{
	IMnetRetCode retCode;
	IMnet* pIMNet = (IMnet*)ref;

	PCContextGetInstance()->mutexLock(&pIMNet->regCritical);
	retCode = IMnetCallbackHandle(pIMNet, pEvent);
	PCContextGetInstance()->mutexUnlock(&pIMNet->regCritical);
	return retCode;
}

PCRetCode IMnetPacker(PCHandle hHandle, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength, PCReference ref)
{
	return IMnetPack((IMnet*)ref, pEvt, ppBuffer, pLength);
}

void IMnetPackerFree(AMInt8* pBuffer, PCReference ref)
{
	IMnetPackRelease(pBuffer);
}

PCRetCode IMnetUnpacker(PCHandle hHandle, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length, PCReference ref)
{
	return IMnetUnpack((IMnet*)ref, ppEvt, cmd, pBuffer, Length);
}

IMnetRetCode IMnetMainCreate(IMnetHandle* phIMnetHanlde, IMnetReference pReference)
{
	IMnet* pIMnet = NULL;	
	IMnetCallback* pCallback = NULL;
	VarKeeper* pVarKeeper = NULL;

	if(phIMnetHanlde == NULL)
		return eInvalidParam;


	pIMnet = (IMnet*)AMMalloc(sizeof(IMnet));
	memset(pIMnet, 0, sizeof(IMnet));
	if(pIMnet)
	{
		//IMnetCallbackCreate
		pCallback = IMnetCallbackCreate();
		pIMnet->pIMnetCallback = pCallback;

		VarKeeperCreate(&pVarKeeper);
		pIMnet->pVarKeeper = pVarKeeper;
		pIMnet->pReference = pReference;

		PCContextGetInstance()->mutexCreate(&pIMnet->regCritical);

		PacketConnectionCreate(&pIMnet->hPCHandle, (PCServiceID)0, (PCReference)pIMnet);
		PacketConnectionSetPacker(pIMnet->hPCHandle, IMnetPacker, IMnetPackerFree);
		PacketConnectionSetUnpacker(pIMnet->hPCHandle, IMnetUnpacker);
		PacketConnectionSetReceiver(pIMnet->hPCHandle, IMnetReceiver);

		*phIMnetHanlde = pIMnet;
	}
	else
		return eMallocError;

	return eOK;
}

IMnetRetCode IMnetConnectOpen(IMnetHandle hIMnetHandle, AMChar* ip, AMUInt16 port, AMInt32 sync)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	IMnetRetCode retCode; 

#ifdef AMOS_DEBUG
	AMPrintf("IMnetConnectOpen.........................%s, %d\n", ip, port);
#endif // AMOS_DEBUG

	if(pIMnet && ip)
	{
		PacketConnectionClose(pIMnet->hPCHandle);

		retCode = PacketConnectionOpen(pIMnet->hPCHandle, ip, port, sync);
	}
	else
		retCode = eInvalidParam;

	return retCode;
}

IMnetRetCode IMnetConnectClose(IMnetHandle hIMnetHandle)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	IMnetRetCode retCode; 

	if(pIMnet)
	{
		//close network
		retCode = PacketConnectionClose(pIMnet->hPCHandle);
	}
	else
		retCode = eInvalidParam;

	return retCode;
}
#if IM_NET_SHUT_SOCKET
IMnetRetCode IMnetConnectShut(IMnetHandle hIMnetHandle)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	IMnetRetCode retCode; 

	if(pIMnet)
	{
		//close network
		retCode = PacketConnectionShut(pIMnet->hPCHandle);
	}
	else
		retCode = eInvalidParam;

	return retCode;
}
#endif

void IMnetMainDestory(IMnetHandle hIMnetHandle)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

#ifdef AMOS_DEBUG
	AMPrintf( "IMnetMainDestory.............Entering!\n");
#endif
	if(pIMnet)
	{
#ifdef AMOS_DEBUG
		AMPrintf( "IMnetMainDestory.............Before IMnetConnectClose!\n");
#endif
		//1: imnet close.
		IMnetConnectClose(hIMnetHandle);
#ifdef AMOS_DEBUG
		AMPrintf( "IMnetMainDestory.............After IMnetConnectClose\n");
#endif
		
		//3: destory engine
		PacketConnectionDestory(pIMnet->hPCHandle);
#ifdef AMOS_DEBUG
		AMPrintf( "IMnetMainDestory.............After PacketConnectionDestory\n");
#endif

		//4. destroy component.
		IMnetCallbackDestory(pIMnet->pIMnetCallback);;
#ifdef AMOS_DEBUG
		AMPrintf( "IMnetMainDestory.............After IMnetCallbackDestory\n");
#endif
		VarKeeperDestory(&pIMnet->pVarKeeper);

		PCContextGetInstance()->mutexDestory(&pIMnet->regCritical);

		AMFree((void*)pIMnet);
		pIMnet = NULL;
	}
}

IMnetRetCode IMnetMainRegister(IMnetHandle hIMnetHandle, EventId id, CallbackFunc pCallback)
{
	IMnetRetCode retCode;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	if(pIMnet)
	{
		PCContextGetInstance()->mutexLock(&pIMnet->regCritical);
		retCode = IMnetCallbackRegister(&pIMnet->pIMnetCallback, id, pCallback);
		PCContextGetInstance()->mutexUnlock(&pIMnet->regCritical);
	}
	else
		retCode = eIMnetRegisterError;

	return retCode;
}

IMnetRetCode IMnetMainUnregister(IMnetHandle hIMnetHandle, EventId id, CallbackFunc pCallback)
{
	IMnetRetCode retCode;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	if(pIMnet)
	{
		PCContextGetInstance()->mutexLock(&pIMnet->regCritical);
		retCode = IMnetCallbackUnregister(&pIMnet->pIMnetCallback, id, pCallback);
		PCContextGetInstance()->mutexUnlock(&pIMnet->regCritical);
	}
	else
		retCode = eIMnetUnRegisterError;
	return retCode;
}


IMnetReference IMnetGetReference(IMnetHandle hIMnetHandle)
{
	AMAssert(NULL != ((IMnet*)hIMnetHandle)->pReference);

	if(hIMnetHandle == NULL)
		return 0;
	else
		return ((IMnet*)hIMnetHandle)->pReference;
}

IMnetRetCode IMnetPackGetOffObj(const FtReqGetOffObj *pGetOffObj,
								AMChar **pszBuff, AMInt32 *piBuffLen)
{
	IMnetRetCode retCode;
	FtsPacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;

	AMInt32 size = 0, up = ((AMInt32*)&pGetOffObj->ulObjId)[1], low = ((AMInt32*)&pGetOffObj->ulObjId)[0];

	//
	//1. create head
	//
	FtsHeadInit(&head);
	head.uiCmd	 = 0x1653; // to do 

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 514;

	retCode = FtsPackAllocate(&head, pszBuff, piBuffLen, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *pszBuff;
	pBufferTemp = FtsPackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	//if(pGetOffObj->propertyNum != 0)
	//	putByte(pBufferTemp, pGetOffObj->propertyNum);

	WriteData(&pBufferTemp, pGetOffObj->sendUID, pGetOffObj->sendUIDLen, 0, 64);
	WriteData(&pBufferTemp, pGetOffObj->recevierUID, pGetOffObj->recevierUIDLen, 0, 64);
	putShort(pBufferTemp, pGetOffObj->uiSubType);
	WriteData(&pBufferTemp, pGetOffObj->szToken, pGetOffObj->tokenLen, 0, 64);
	putLong(pBufferTemp, up, low);
	WriteData(&pBufferTemp, pGetOffObj->szDownloadURL, pGetOffObj->downloadURLLen, 0, 128);
	WriteData(&pBufferTemp, pGetOffObj->szFileName, pGetOffObj->fileNameLen, 0, 128);
	WriteData(&pBufferTemp, pGetOffObj->szFileExtName, pGetOffObj->fileExtNameLen, 0, 16);
	WriteData(&pBufferTemp, pGetOffObj->szFileMD5, pGetOffObj->fileMD5Len, 0, 32);
	putInt(pBufferTemp, pGetOffObj->fileSize);
	putInt(pBufferTemp, pGetOffObj->reserved);

	//
	//5. reset head
	//
	FtsResetHead(*pszBuff, head.uiLen);
	return eOK;
}

void FreeFtRspGetOffObj(FtRspGetOffObj* pGetOffObj)
{
	AMAssert(pGetOffObj);

	if (pGetOffObj->errorMsg != AMNULL)
	{
		AMFree(pGetOffObj->errorMsg);
		pGetOffObj->errorMsg = AMNULL;
	}

	if (pGetOffObj->sendUID != AMNULL)
	{
		AMFree(pGetOffObj->sendUID);
		pGetOffObj->sendUID = AMNULL;
	}

	if (pGetOffObj->recevierUID != AMNULL)
	{
		AMFree(pGetOffObj->recevierUID);
		pGetOffObj->recevierUID = AMNULL;
	}

	AMFree(pGetOffObj);
}

IMnetRetCode IMnetUnpackGetOffObj(FtRspGetOffObj **ppGetOffObj,
								  AMChar *pszBuff, AMInt32 piBuffLen)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBuffTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	FtsPacketHead head;
	FtRspGetOffObj *pGetOffObj = (FtRspGetOffObj *)AMMalloc(sizeof(FtRspGetOffObj));
	// clear all
	memset(pGetOffObj, 0, sizeof(FtRspGetOffObj));

	//
	//0. init propertyNum.
	//
	pGetOffObj->propertyNum = 12;

	//1. unpack head and check body.
	retCode = FtsUnpackHeadAndCheck(pszBuff, &pBuffTemp, &head);
	if(retCode != eOK)
		return retCode;

	//3. unpack body
	
	getInt(pBuffTemp, pGetOffObj->retCode);
	if ((eOK == (retCode = ReadData(&pBuffTemp, &pGetOffObj->errorMsg, &pGetOffObj->errorMsgLen, 32)))
		&& (eOK == (retCode = ReadData(&pBuffTemp, &pGetOffObj->sendUID, &pGetOffObj->sendUIDLen, 64)))
		&& (eOK == (retCode = ReadData(&pBuffTemp, &pGetOffObj->recevierUID, &pGetOffObj->recevierUIDLen, 64))))
	{
		getShort(pBuffTemp, pGetOffObj->uiSubType);
		getLong(pBuffTemp, *(((AMInt32*)&pGetOffObj->ulObjId)+1), *(((AMInt32*)&pGetOffObj->ulObjId)));
		getInt(pBuffTemp, pGetOffObj->reserved);
		getShort(pBuffTemp, pGetOffObj->totalNum);
		getShort(pBuffTemp, pGetOffObj->leftNum);
		getShort(pBuffTemp, pGetOffObj->totalSize);
		getShort(pBuffTemp, pGetOffObj->leftSize);
		getByte(pBuffTemp, pGetOffObj->keepDay);
		*ppGetOffObj = pGetOffObj;
	}

	if (retCode != eOK)
	{
		FreeFtRspGetOffObj(pGetOffObj);
		*ppGetOffObj = AMNULL;
	}

	return retCode;
}

IMnetRetCode IMnetPackGetOffObjFin(const FtReqGetOffObjFin *pRequest,
								   AMChar **ppBuffer, AMInt32 *pLength)
{
	IMnetRetCode retCode;
	FtsPacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	AMInt32 size = 0, up = ((AMInt32*)&pRequest->ulObjId)[1], low = ((AMInt32*)&pRequest->ulObjId)[0];

	//
	//1. create head
	//
	FtsHeadInit(&head);
	head.uiCmd	 = 0x1655; // to do

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 550;

	retCode = FtsPackAllocate(&head, ppBuffer, pLength, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = FtsPackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	putInt(pBufferTemp, pRequest->retCode);
	WriteData(&pBufferTemp, pRequest->errorMsg, pRequest->errorMsgLen, 0, 32);
	WriteData(&pBufferTemp, pRequest->sendUID, pRequest->sendUIDLen, 0, 64);
	WriteData(&pBufferTemp, pRequest->recevierUID, pRequest->recevierUIDLen, 0 ,64);
	putShort(pBufferTemp, pRequest->uiSubType);
	putLong(pBufferTemp, up, low);
	WriteData(&pBufferTemp, pRequest->szToken, pRequest->tokenLen, 0, 64);
	WriteData(&pBufferTemp, pRequest->szDownloadURL, pRequest->downloadURLLen, 0,128);
	WriteData(&pBufferTemp, pRequest->szFileName, pRequest->fileNameLen, 0, 128);
	WriteData(&pBufferTemp, pRequest->szFileExtName, pRequest->fileExtNameLen, 0, 16);
	WriteData(&pBufferTemp, pRequest->szFileMD5, pRequest->fileMD5Len, 0, 32);
	putInt(pBufferTemp, pRequest->fileSize);
	putInt(pBufferTemp, pRequest->reserved);

	//
	//5. reset head
	//
	FtsResetHead(*ppBuffer, head.uiLen);
	return eOK;
}

void FreeFtRspGetOffObjFin(FtRspGetOffObjFin* pGetOffObjFin)
{
	if (!pGetOffObjFin)
		return;

	if (!pGetOffObjFin->errorMsg)
	{
		AMFree(pGetOffObjFin->errorMsg);
		pGetOffObjFin->errorMsg = AMNULL;
	}

	if (!pGetOffObjFin->sendUID)
	{
		AMFree(pGetOffObjFin->sendUID);
		pGetOffObjFin->sendUID = AMNULL;
	}

	if (!pGetOffObjFin->recevierUID)
	{
		AMFree(pGetOffObjFin->recevierUID);
		pGetOffObjFin->recevierUID = AMNULL;
	}

	if (!pGetOffObjFin->szToken)
	{
		AMFree(pGetOffObjFin->szToken);
		pGetOffObjFin->szToken = AMNULL;
	}

	AMFree(pGetOffObjFin);
}

IMnetRetCode IMnetUnpackGetOffObjFin(FtRspGetOffObjFin **ppGetOffObjFin, AMChar *pszBuff, AMInt32 piBuffLen)
{
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	FtsPacketHead head;
	FtRspGetOffObjFin *pRspGetOffObjFin = AMNULL;

	pRspGetOffObjFin = (FtRspGetOffObjFin *)AMMalloc(sizeof(FtRspGetOffObjFin));
	memset(pRspGetOffObjFin, 0, sizeof(FtRspGetOffObjFin));

	//
	//0. init propertyNum.
	//
	pRspGetOffObjFin->propertyNum = 8;

	//1. unpack head and check body.
	retCode = FtsUnpackHeadAndCheck(pszBuff, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//3. unpack body
	//getByte(pBufferTemp, tempNum);
	//IMnetCheckPropertyNum(*pGetOffObj.propertyNum, tempNum);

	getInt(pBufferTemp, pRspGetOffObjFin->retCode);
	if (eOK == (retCode = ReadData(&pBufferTemp, &pRspGetOffObjFin->errorMsg, &pRspGetOffObjFin->errorMsgLen, 32))
		&& eOK == (retCode = ReadData(&pBufferTemp, &pRspGetOffObjFin->sendUID, &pRspGetOffObjFin->sendUIDLen, 64)) 
		&& eOK == (retCode = ReadData(&pBufferTemp, &pRspGetOffObjFin->recevierUID, &pRspGetOffObjFin->recevierUIDLen, 64))
		&& eOK == (retCode = GetSctShort(&pBufferTemp, &pRspGetOffObjFin->uiSubType))
		&& eOK == (retCode = ReadData(&pBufferTemp,  &pRspGetOffObjFin->szToken, &pRspGetOffObjFin->tokenLen, 64))
		&& eOK == (retCode = GetSctULong(&pBufferTemp, ((AMInt32 *)&pRspGetOffObjFin->ulObjId) + 1, (AMInt32*)&pRspGetOffObjFin->ulObjId)))
	{
		getInt(pBufferTemp, pRspGetOffObjFin->reserved);
		retCode = eOK;
	}

	if (retCode != eOK)
	{
		FreeFtRspGetOffObjFin(pRspGetOffObjFin);
		*ppGetOffObjFin = AMNULL;
	}
	else
		*ppGetOffObjFin = pRspGetOffObjFin;

	return retCode;
}

IMnetRetCode IMnetPackPutOffObj(const FtReqPutOffObj *pPutOffObj, AMChar **ppBuffer, AMInt32 *pLength)
{
	IMnetRetCode retCode;
	FtsPacketHead head;
	AMInt32 bodyLength = 0;
	AMUInt8* pBufferTemp = NULL;
	AMInt32 size = 0, up = ((AMInt32*)&pPutOffObj->ulObjId)[1], low = ((AMInt32*)&pPutOffObj->ulObjId)[0];

	//
	//1. create head
	//
	FtsHeadInit(&head);
	head.uiCmd	 = 0x00001650; // to do

	//
	//2. alloc buffer
	//
	//Protocol Length
	bodyLength  = 514;

	retCode = FtsPackAllocate(&head, ppBuffer, pLength, bodyLength);
	if(retCode != eOK)
		return retCode;

	//
	//3. pack head.
	//
	pBufferTemp = *ppBuffer;
	pBufferTemp = FtsPackHead(pBufferTemp, &head);

	//
	//4. pack body
	//
	//pPutOffObj->propertyNum = 11;
	//if(pPutOffObj->propertyNum != 0)
	//	putByte(pBufferTemp, pPutOffObj->propertyNum);

	WriteData(&pBufferTemp, pPutOffObj->sendUID, pPutOffObj->sendUIDLen, 0, 64);
	WriteData(&pBufferTemp, pPutOffObj->recevierUID, pPutOffObj->recevierUIDLen, 0, 64);
	putShort(pBufferTemp, pPutOffObj->uiSubType);
	putLong(pBufferTemp, up, low);
	WriteData(&pBufferTemp, pPutOffObj->szToken, pPutOffObj->tokenLen, 0, 64);
	WriteData(&pBufferTemp, pPutOffObj->szDownloadURL, pPutOffObj->downloadURLLen, 0, 128);
	WriteData(&pBufferTemp, pPutOffObj->szFileName, pPutOffObj->fileNameLen, 0, 128);
	WriteData(&pBufferTemp, pPutOffObj->szFileExtName, pPutOffObj->fileExtNameLen, 0, 16);
	WriteData(&pBufferTemp, pPutOffObj->szFileMD5, pPutOffObj->fileMD5Len, 0, 32);
	putInt(pBufferTemp, pPutOffObj->fileSize);
	putInt(pBufferTemp, pPutOffObj->reserved);

	//
	//5. reset head
	//
	FtsResetHead(*ppBuffer, head.uiLen);
	return eOK;
}

void FreeFtRspPutOffObj(FtRspPutOffObj* pRspPutOffObj)
{
	if (pRspPutOffObj)
	{
		if (pRspPutOffObj->errorMsg)
		{
			AMFree(pRspPutOffObj->errorMsg);
			pRspPutOffObj->errorMsg = AMNULL;
		}

		if (pRspPutOffObj->sendUID)
		{
			AMFree(pRspPutOffObj->sendUID);
			pRspPutOffObj->sendUID = AMNULL;
		}

		if (pRspPutOffObj->recevierUID)
		{
			AMFree(pRspPutOffObj->recevierUID);
			pRspPutOffObj->recevierUID = AMNULL;
		}
		AMFree(pRspPutOffObj);
	}
}

IMnetRetCode IMnetUnpackPutOffObj(FtRspPutOffObj **ppPutOffObj, AMChar *szBuff, AMInt32 piBuffLen)
{	
	IMnetRetCode retCode = eOK;
	AMUInt8* pBuffTemp = NULL, pNewBuffer = NULL;
	FtsPacketHead head;
	FtRspPutOffObj * pPutOffObj = AMNULL;

	pPutOffObj = (FtRspPutOffObj *)AMMalloc(sizeof(FtRspPutOffObj));
	memset(pPutOffObj, 0, sizeof(FtRspPutOffObj));

	//
	//0. init propertyNum.
	//
	pPutOffObj->propertyNum = 12;

	//1. unpack head, decrypt body and check body.
	retCode = FtsUnpackHeadAndCheck(szBuff, &pBuffTemp, &head);
	if(retCode != eOK)
		return retCode;

	//3. unpack body
	getInt(pBuffTemp, pPutOffObj->retCode);
	if ((eOK == (retCode = ReadData(&pBuffTemp, &pPutOffObj->errorMsg, &pPutOffObj->errorMsgLen, 32)))
		&& (eOK == (retCode = ReadData(&pBuffTemp, &pPutOffObj->sendUID, &pPutOffObj->sendUIDLen, 64)))
		&& (eOK == (retCode = ReadData(&pBuffTemp, &pPutOffObj->recevierUID, &pPutOffObj->recevierUIDLen, 64))))
	{
		getShort(pBuffTemp, pPutOffObj->uiSubType);
		getLong(pBuffTemp, *(((AMInt32*)&pPutOffObj->ulObjId)+1), *(((AMInt32*)&pPutOffObj->ulObjId)));
		getInt(pBuffTemp, pPutOffObj->reserved);
		getShort(pBuffTemp, pPutOffObj->totalNum);
		getShort(pBuffTemp, pPutOffObj->leftNum);
		getShort(pBuffTemp, pPutOffObj->totalSize);
		getShort(pBuffTemp, pPutOffObj->leftSize);
		getShort(pBuffTemp, pPutOffObj->keepDay);
		*ppPutOffObj = pPutOffObj;
	}

	if (retCode != eOK)
	{
		FreeFtRspPutOffObj(pPutOffObj);
		*ppPutOffObj = AMNULL;
	}

	return retCode;
}

void FreeFtRspPutOffObjFin(FtRspPutOffObjFin* pRspPutOffObjFin)
{
	if (pRspPutOffObjFin)
	{
		if (pRspPutOffObjFin->errorMsg)
		{
			AMFree(pRspPutOffObjFin->errorMsg);
			pRspPutOffObjFin->errorMsg = AMNULL;
		}

		if (pRspPutOffObjFin->sendUID)
		{
			AMFree(pRspPutOffObjFin->sendUID);
			pRspPutOffObjFin->sendUID = AMNULL;
		}

		if (pRspPutOffObjFin->recevierUID)
		{
			AMFree(pRspPutOffObjFin->recevierUID);
			pRspPutOffObjFin->recevierUID = AMNULL;
		}

		if(pRspPutOffObjFin->szDownloadURL)
			AMFree(pRspPutOffObjFin->szDownloadURL);

		if(pRspPutOffObjFin->szToken)
			AMFree(pRspPutOffObjFin->szToken);

		AMFree(pRspPutOffObjFin);
	}
}

IMnetRetCode IMnetUnpackPutOffObjFin(FtRspPutOffObjFin** ppRspPutOffObjFin, AMUInt8* pBuffer, AMInt32 Length)
{
	
	IMnetRetCode retCode = eOK;
	AMUInt8* pBufferTemp = NULL;
	AMUInt8* pNewBuffer = NULL;
	FtsPacketHead head;
	FtRspPutOffObjFin *pPutOffObjFin = (FtRspPutOffObjFin *)AMMalloc(sizeof(FtRspPutOffObjFin));
	memset(pPutOffObjFin, 0, sizeof(FtRspPutOffObjFin));	

	//
	//0. init propertyNum.
	//
	pPutOffObjFin->propertyNum = 7;

	//1. unpack head, decrypt body and check body.
	retCode = FtsUnpackHeadAndCheck(pBuffer, &pBufferTemp, &head);
	if(retCode != eOK)
		return retCode;

	//3. unpack body

	getInt(pBufferTemp, pPutOffObjFin->retCode);

	if ((eOK == (retCode = ReadData(&pBufferTemp, &pPutOffObjFin->errorMsg, &pPutOffObjFin->errorMsgLen, 32)))
		&& (eOK == (retCode = ReadData(&pBufferTemp, &pPutOffObjFin->sendUID, &pPutOffObjFin->sendUIDLen, 64)))
		&& (eOK == (retCode = ReadData(&pBufferTemp, &pPutOffObjFin->recevierUID, &pPutOffObjFin->recevierUIDLen, 64))))
	{
		getShort(pBufferTemp, pPutOffObjFin->uiSubType);
		if( eOK == (retCode = ReadData(&pBufferTemp, &pPutOffObjFin->szToken, &pPutOffObjFin->tokenLen, 64)))
			retCode = ReadData(&pBufferTemp, &pPutOffObjFin->szDownloadURL, &pPutOffObjFin->downloadURLLen, 128);
	}

	*ppRspPutOffObjFin = pPutOffObjFin;

	if (eOK != retCode)
	{
		FreeFtRspPutOffObjFin(pPutOffObjFin);
		*ppRspPutOffObjFin = AMNULL;
	}

	return retCode;
}


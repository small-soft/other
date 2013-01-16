#include "AIMTrans.h"
#include "AIMTransModule.h"
#include "AMString.h"
#include "AMStdlib.h"
#include "IMnet.h"
#include "md5.h"


static AMChar* _hex2Dsp(AMChar *szDest, AMChar* data, AMInt32 len)
{
	AMChar base;
	AMUChar ch;
	AMInt32 i;

	base = 'a' - 10;

	for(i = 0; i < len; i++)
	{
		ch = (AMUChar)data[i] >> 4;
		szDest[2*i] = (AMChar)(ch >= 10 ? ch + base : ch + '0');
		ch = (AMUChar)data[i] & 0x0f;
		szDest[2*i+1] = (AMChar)(ch >= 10 ? ch + base : ch + '0');
	}
	szDest[2*len] = 0;
	return szDest;
}
/*
 *	szDigest的长度由调用者保证。
 */

#define		SIZE_BUFFER		4096
AMInt32 _AIM_md5File(AMChar *szDigest, AMFILE *pFile)
{
	AMChar szBuffer[SIZE_BUFFER] = {0}, szHash[16] = {0};
	MD5_CTX md5Context;
	AMInt32 iReadLen = 0, iPos = 0;
	//md5
	MD5Init(&md5Context);

	iPos = AMFseek(pFile, 0, AM_SEEK_SET);

	while((iReadLen = AMFread(szBuffer, 1, SIZE_BUFFER, pFile)) > 0)
	{
		MD5Update(&md5Context, szBuffer, iReadLen);
	}

	MD5Final(szHash, &md5Context);

	AMFseek(pFile, 0, AM_SEEK_SET);

	if(iReadLen<0)
		return eAIM_RESULT_FILE_READ;
	else
	{
		_hex2Dsp(szDigest, szHash, 16);
	}

	return eAIM_RESULT_OK;
}

#define FILE_DELIMITER	'/'
static const AMChar	* _AIM_getNameFromPath(const AMChar *szPathName)
{
	const AMChar *szFileName = AMNULL, *szDelimiter = AMNULL;
	AMAssert(szPathName);
	
	szFileName = szDelimiter = szPathName;

	while(szDelimiter = AMStrchr(szFileName, FILE_DELIMITER))
		szFileName = szDelimiter+1;

	DPRINT("%s >>>>>> fileName: %s\n", __FUNCTION__, szFileName);

	return szFileName;
}

static const AMChar	* _AIM_getExtend(const AMChar *szFileName)
{
	const AMChar *szExtend = AMNULL, *szDot = AMNULL;

	AMAssert(szFileName);

	szDot = szExtend = AMStrchr(szFileName, '.');

	while(szDot && (szDot = AMStrchr(szDot+1, '.')))
		szExtend = szDot;

	DPRINT("%s >>>>>> fileExtend: %s\n", __FUNCTION__, szExtend);
	return szExtend;
}

AMInt32	_AIM_getFileSize(AMFILE *pFile)
{
	AMUInt32 uiSize = 0, uiPos = 0;
	uiPos = AMFtell(pFile);

	uiPos = AMFseek(pFile, 0, AM_SEEK_END);
	uiSize = AMFtell(pFile);
	AMFseek(pFile, uiPos, AM_SEEK_SET);

	return uiSize;
}

AMInt32	AIMTrans_createSend(const AMChar *szContactId, const AMChar *szPathName, AIMTrans **ppTrans)
{
	AIMTrans *pTrans = AMNULL;
	AMInt32 iRetCode = eAIM_RESULT_OK;
	AMChar *szDigest = AMNULL, *szFileName = AMNULL, *szExtend = AMNULL;
	AMAssert(szPathName && ppTrans);

	*ppTrans = AMNULL;

	pTrans = (AIMTrans *)AMMalloc(sizeof(AIMTrans));
	if(!pTrans)
		return eAIM_RESULT_MALLOC_ERROR;

	AMMemset(pTrans, 0, sizeof(AIMTrans));
	
	pTrans->eType = eAIM_TYPE_SEND;

	do 
	{
		pTrans->pFile = AMFopen(szPathName, "rb");
		if(!pTrans->pFile)
		{
			iRetCode = eAIM_RESULT_FILE_OPEN;
			break;
		}

		pTrans->uiFileSize = _AIM_getFileSize(pTrans->pFile);
		DPRINT("%s >>>>>> fileSize: %d\n", __FUNCTION__, pTrans->uiFileSize);

		if(iRetCode = _AIM_md5File(pTrans->szDigest, pTrans->pFile))
			break;

		if(!(pTrans->szContactId = _StrDupLen(szContactId, AMStrlen(szContactId))))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}

		if(!(pTrans->szFilePath = _StrDupLen(szPathName, AMStrlen(szPathName))))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}

		szFileName = _AIM_getNameFromPath(szPathName);
		AMAssert(szFileName);
		if(!(pTrans->szFileName = _StrDupLen(szFileName, AMStrlen(szFileName))))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}

		szExtend = _AIM_getExtend(pTrans->szFileName);
		if(!(pTrans->szExtend = _StrDupLen(szExtend, szExtend?AMStrlen(szExtend):0)))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}

	} while (0);

	if(!iRetCode)
		*ppTrans = pTrans;
	else
		AIMTrans_destroy(pTrans);

	return iRetCode;
}

#define XML_TRANS_SIZE		"<dwImageSize>"
#define XML_TRANS_SIZE_END	"</dwImageSize>"
#define	XML_TRANS_MD5BGN	"<strImageHash>"
#define	XML_TRANS_MD5END	"</strImageHash>"
#define	XML_TRANS_ID		"<llSID>"
#define XML_TRANS_ID_END	"</llSID>"
#define XML_TRANS_EXTBGN	"<strImageExtend>"
#define XML_TRANS_EXTEND	"</strImageExtend>"
AMInt32		AIMTrans_createReceive(const AMChar *szContactId, const AMChar *szXML, const AMChar *szDestFile, AIMTrans **ppTrans)
{
	AMChar *szObjId = AMNULL, *szSize = AMNULL, *szMd5Bgn = AMNULL, 
		*szMd5End = AMNULL, *szExtendBgn = AMNULL, *szExtendEnd = AMNULL;
	AMChar *szDigest = AMNULL, *szFileName = AMNULL;
	AIMTrans *pTrans = AMNULL;
	AMInt32 iRetCode = eAIM_RESULT_OK;

	AMAssert(szDestFile && ppTrans && szXML);

	*ppTrans = AMNULL;

	if( !(szSize = AMStrstr(szXML, XML_TRANS_SIZE))
		|| !(szMd5Bgn = AMStrstr(szSize + 2*sizeof(XML_TRANS_SIZE)-2, XML_TRANS_MD5BGN))
		|| !(szMd5End = AMStrstr(szMd5Bgn + sizeof(XML_TRANS_MD5BGN)-1, XML_TRANS_MD5END))
		|| !(szObjId = AMStrstr(szMd5End + sizeof(XML_TRANS_MD5END)-1, XML_TRANS_ID))
		|| !(szExtendBgn = AMStrstr(szObjId + 2*sizeof(XML_TRANS_ID)-2, XML_TRANS_EXTBGN))
		|| !(szExtendEnd = AMStrstr(szExtendBgn + sizeof(XML_TRANS_EXTBGN)-1, XML_TRANS_EXTEND)) )
		return eAIM_RESULT_PARAM_ERROR;

	pTrans = (AIMTrans *)AMMalloc(sizeof(AIMTrans));
	if(!pTrans)
		return eAIM_RESULT_MALLOC_ERROR;

	AMMemset(pTrans, 0, sizeof(AIMTrans));

	pTrans->eType = eAIM_TYPE_RECV;

	do 
	{
		szObjId += sizeof(XML_TRANS_ID) - 1;
		pTrans->ulObjId = AMAtoi64(szObjId);

		pTrans->pFile = AMFopen(szDestFile, "wb");
		if(!pTrans->pFile)
		{
			iRetCode = eAIM_RESULT_FILE_OPEN;
			break;
		}

		szSize += sizeof(XML_TRANS_SIZE) -1;
		pTrans->uiFileSize = AMAtoi(szSize);
		DPRINT("%s >>>>>> fileSize: %d\n", __FUNCTION__, pTrans->uiFileSize);

		szMd5Bgn += sizeof(XML_TRANS_MD5BGN)-1;
		AMMemcpy(pTrans->szDigest, szMd5Bgn, szMd5End - szMd5Bgn);

		if(!(pTrans->szContactId = _StrDupLen(szContactId, AMStrlen(szContactId))))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}

		szFileName = _AIM_getNameFromPath(szDestFile);
		AMAssert(szFileName);
		if(!(pTrans->szFileName = _StrDupLen(szFileName, AMStrlen(szFileName))))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}
		
		szExtendBgn += sizeof(XML_TRANS_EXTBGN)-1;
		if(!(pTrans->szExtend = _StrDupLen(szExtendBgn, szExtendEnd-szExtendBgn)))
		{
			iRetCode = eAIM_RESULT_MALLOC_ERROR;
			break;
		}

	} while (0);

	if(!iRetCode)
		*ppTrans = pTrans;
	else
		AIMTrans_destroy(pTrans);

	return iRetCode;
}

AMInt32		AIMTrans_createId(AMInt32 iId, AIMTrans **ppTrans)
{
	AIMTrans *pTrans = AMNULL;
	pTrans = (AIMTrans *)AMMalloc(sizeof(AIMTrans));
	if(!pTrans)
		return eAIM_RESULT_MALLOC_ERROR;

	AMMemset(pTrans, 0, sizeof(AIMTrans));
	pTrans->iTransId = iId;

	*ppTrans = pTrans;

	return eAIM_RESULT_OK;
}

AMVoid		AIMTrans_destroy(AIMTrans *pTrans)
{
	AMAssert(pTrans);
	if(pTrans->pFile)
		AMFclose(pTrans->pFile);
	if(pTrans->szFilePath)
		AMFree(pTrans->szFilePath);
	if(pTrans->szFileName)
		AMFree(pTrans->szFileName);
	if(pTrans->szExtend)
		AMFree(pTrans->szExtend);
	if(pTrans->szContactId)
		AMFree(pTrans->szContactId);
	
	AMFree(pTrans);
}

static AMInt32	_AIMTrans_cmpSend(const AIMTrans *pATrans, const AIMTrans*pBTrans)
{
	AMInt32 iResult = 0;
	AMAssert(pATrans && pBTrans);

	iResult = AMStrcmp(pATrans->szContactId, pBTrans->szContactId);

	if(!iResult)
		iResult = AMStrcmp(pATrans->szFilePath, pBTrans->szFilePath);

	return iResult;
}

static AMInt32	_AIMTrans_cmpRecv(const AIMTrans *pATrans, const AIMTrans*pBTrans)
{
	AMAssert(pATrans && pBTrans);
	AMAssert(pATrans->ulObjId && pBTrans->ulObjId);
	return (AMInt32)(pATrans->ulObjId - pBTrans->ulObjId);
}

AMInt32		AIMTrans_cmpContent(const AMVoid *pvA, const AMVoid *pvB, AMUInt32 uiSize)
{
	AIMTrans *pATrans = (AIMTrans*)pvA, *pBTrans = (AIMTrans *)pvB;
	AMAssert(pATrans && pBTrans);

	if(pATrans->eType == pBTrans->eType)
	{
		if(eAIM_TYPE_SEND == pATrans->eType)
			return _AIMTrans_cmpSend(pATrans, pBTrans);
		else if(eAIM_TYPE_RECV == pATrans->eType)
			return _AIMTrans_cmpRecv(pATrans, pBTrans);
		else
			AMAssert(0);
	}
	else
		return pATrans->eType - pBTrans->eType;
}

AMInt32		AIMTrans_cmpId(const AMVoid *pvA, const AMVoid *pvB, AMUInt32 uiSize)
{
	AIMTrans *pATrans = (AIMTrans*)pvA, *pBTrans = (AIMTrans *)pvB;
	AMAssert(pATrans && pBTrans);
	
	return pATrans->iTransId - pBTrans->iTransId;
}

AMInt32		AIMTrans_cmpPtr(const AMVoid *pvA, const AMVoid *pvB, AMUInt32 uiSize)
{
	AMAssert(pvA && pvB);
	return (AMInt32)pvA-(AMInt32)pvB;
}

static AMInt32	_AIMTrans_recv(AIMTrans *pTrans, AMInt32 sockFd);

static AMInt32	_AIMTrans_send(AIMTrans *pTrans, AMInt32 sockFd);

AMInt32		AIMTrans_work(AIMTrans *pTrans, const AMChar *szIp, AMUInt32 uiPort)
{
	AIM_RESULT retCode;
	AMInt32 socketFD = -1;

	if(AIMTransModule_update(pTrans->pTransModule, pTrans, ePROGRESS_NET))
		return 0;

	socketFD = PCContextGetInstance()->socketCreate(szIp, uiPort);

	DPRINT("%s >>>>>>> socket create. ip:%s, port:%d, sockFd:%d\n", __FUNCTION__, szIp, uiPort, socketFD);


	if(AIMTransModule_update(pTrans->pTransModule, pTrans, ePROGRESS_SERV))
	{
		PCContextGetInstance()->socketClose(&socketFD);
		return 0;
	}

	if (socketFD <= 0)
	{
		AIMTransModule_result(pTrans->pTransModule, pTrans, eAIM_TRANS_SOCKET);
		retCode = eAIM_RESULT_FAIL;
	}
	else
	{
		if (pTrans->eType == eAIM_TYPE_SEND)
			retCode = _AIMTrans_send(pTrans, socketFD);
		else
			retCode = _AIMTrans_recv(pTrans, socketFD);

		PCContextGetInstance()->socketClose(&socketFD);
	}

	DPRINT("%s >>>>>>> end. retCode: %d \n", __FUNCTION__, retCode);

	return retCode;
}

/*
 *	发送定长二进制流
 */
 AMInt32 _AIMTrans_sendBuffer(AMInt32 sockFd, const AMChar *szBuff, AMInt32 iBuffLen)
{
	AMInt32 iSendDataLen = 0;
	AMAssert(sockFd > 0 && szBuff);

	iSendDataLen = PCContextGetInstance()->send(sockFd, szBuff, iBuffLen);
	DPRINT("%s >>>>>> send buffer ok!\n", __FUNCTION__);

	return (iSendDataLen == iBuffLen) ? 0 : -1;
}
/*
 *	先读24字节，然后判断二进制流长度，再读取相应长度的流。合并。
 */
 #define _AIMTrans_getIntValue(b, off) \
 ( ((b[off + 3] & 0xFF) << 0)\
 + ((b[off + 2] & 0xFF) << 8)\
 + ((b[off + 1] & 0xFF) << 16)\
 + ((b[off + 0] & 0xFF) << 24) )

 AMInt32 _AIMTrans_recvBuffer(AMInt32 sockFd, AMChar **pszBuff, AMInt32 *piBufferLen)
 {
	 AMInt32 length = 0;
	 AMUInt8 szHeadBuff[24] = {0};
	 AMInt32 iHeadLen = 24;
	 AMInt32 iBodyLen = 0;

	 DPRINT("%s >>>>>> begin!\n", __FUNCTION__);

	 //recv szHeadBuff.
	 if ((length = PCContextGetInstance()->recv(sockFd, szHeadBuff, iHeadLen)) != iHeadLen)
	 {
		 DPRINT("%s >>>>>> recv szHeadBuff: recv = %d != HeadLength = %d\n", __FUNCTION__, length, iHeadLen);
		 return -1;
	 }

	 // recv body.
	 if ( ((iBodyLen = _AIMTrans_getIntValue(szHeadBuff, 15)) <= 0) 
		 || !(*pszBuff = (AMChar *)AMMalloc(iBodyLen + iHeadLen)) )
		 return -1;
	 memset(*pszBuff, 0, iBodyLen + iHeadLen);
	 if ((length = PCContextGetInstance()->recv(sockFd, *pszBuff + iHeadLen, iBodyLen)) != iBodyLen)
	 {
		 DPRINT("%s >>>>>> recv body: recv = %d != BodyLength = %d\n", __FUNCTION__, length, iBodyLen);
		 AMFree(*pszBuff);
		 *pszBuff = AMNULL;
		 return -1;
	 }

	 // merge.
	 memcpy(*pszBuff, szHeadBuff, iHeadLen);
	 *piBufferLen = iHeadLen + iBodyLen;

	 DPRINT("%s >>>>>> end!\n", __FUNCTION__);
	 return 0;
 }
/*
 *	分段读取文件，发送，并更新进度。
 */
AMInt32 _AIMTrans_sendFile(AIMTrans *pTrans, AMInt32 sockFd)
{
	AMChar szBuffer[SIZE_BUFFER] = {0};
	AMInt32 iReadLen = 0, iSendLen = 0, iNow = 0, iRetCode = eAIM_TRANS_OK;

	AMAssert(pTrans && sockFd);

	while((iReadLen = AMFread(szBuffer, 1, SIZE_BUFFER, pTrans->pFile)) > 0 
		&& !iRetCode)
	{
		if(!_AIMTrans_sendBuffer(sockFd, szBuffer, iReadLen))
		{
			iNow += iReadLen*100;
			iRetCode = AIMTransModule_update(pTrans->pTransModule, pTrans, iNow/pTrans->uiFileSize);
		}
		else
		{
			iRetCode = eAIM_TRANS_SEND;
		}
	}

	AMFclose(pTrans->pFile);

	if(iReadLen<0)
		return eAIM_RESULT_FILE_READ;

	return iRetCode;
}

/*
 *	分段接收定长文件，存盘，并更新进度。
 */
AMInt32 _AIMTrans_recvFile(AIMTrans *pTrans, AMInt32 sockFd)
{
	AMChar szBuffer[SIZE_BUFFER] = {0};
	AMInt32 iRecvLen = 0, iWriteLen = 0, iNow = 0, iRetCode = eAIM_TRANS_OK, iRemain = 0;
	
	AMAssert(pTrans && sockFd);

	iRemain = pTrans->uiFileSize;
	while((iRecvLen = PCContextGetInstance()->recv(sockFd, szBuffer, iRemain<SIZE_BUFFER?iRemain:SIZE_BUFFER)) > 0 
		&& !iRetCode && iRemain)
	{
		iRemain -= iRecvLen;
		if(iRecvLen == (iWriteLen = AMFwrite(szBuffer, 1, iRecvLen, pTrans->pFile)))
		{
			iNow += iWriteLen*100;
			iRetCode = AIMTransModule_update(pTrans->pTransModule, pTrans, iNow/pTrans->uiFileSize);
		}
		else
		{
			iRetCode = eAIM_TRANS_FILE_WRITE;
		}
	}

	AMFclose(pTrans->pFile);

	if(iRecvLen<0)
		return eAIM_TRANS_RECV;

	return iRetCode;
}

AMInt32 _AIMTrans_fillPutOffObj(const AIMTrans *pTrans, FtReqPutOffObj *pReq)
{
	AMInt32 strLen = 0;

	AIMTransModule * pTransModule = AMNULL;
	AMAssert(pTrans && pReq);

	pTransModule = (AIMTransModule *)pTrans->pTransModule;

	memset(pReq, 0, sizeof(pReq));
	pReq->propertyNum = 11;

	pReq->sendUID = pTransModule->pIM->pAcnt->szID;
	pReq->sendUIDLen = AMStrlen(pReq->sendUID);

	pReq->recevierUID = pTrans->szContactId;
	pReq->recevierUIDLen = AMStrlen(pReq->recevierUID);

	pReq->uiSubType = 3;

	pReq->ulObjId = pTrans->ulObjId;

	pReq->szToken = pTransModule->pIM->pAcnt->szToken;
	pReq->tokenLen = pTransModule->pIM->pAcnt->uiTokenLen;

	pReq->szDownloadURL = AMNULL;
	pReq->downloadURLLen = 0;

	pReq->szFileName = pTrans->szFileName;
	pReq->fileNameLen = AMStrlen(pReq->szFileName);

	pReq->szFileExtName = pTrans->szExtend;
	pReq->fileExtNameLen = AMStrlen(pReq->szFileExtName);

	pReq->szFileMD5 = pTrans->szDigest;
	pReq->fileMD5Len = AMStrlen(pReq->szFileMD5);

	pReq->fileSize = pTrans->uiFileSize;

	pReq->reserved = 0;

	return eAIM_RESULT_OK;
}

 AMInt32 _AIMTrans_reqPutOffObj(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 FtReqPutOffObj reqPutOffObj;
	 AMChar *szBuffer = AMNULL;
	 AMInt32 iBuffLen = 0, iRetCode = eAIM_TRANS_OK;
	 AMAssert(pTrans && sockFd);

	 DPRINT("%s >>>>>> fuck here!\n", __FUNCTION__);
	 if(!(iRetCode = _AIMTrans_fillPutOffObj(pTrans, &reqPutOffObj))
		 && eIMnetOK == (iRetCode = IMnetPackPutOffObj(&reqPutOffObj, &szBuffer, &iBuffLen)))
	 {
		 iRetCode = _AIMTrans_sendBuffer(sockFd, szBuffer, iBuffLen);
		 IMnetPackRelease(szBuffer);
	 }

	 return iRetCode;
 }

AMInt32 _AIMTrans_pickPutOffObj(AIMTrans *pTrans, FtRspPutOffObj *pRspPutOffObj)
{
	AMAssert(pTrans && pRspPutOffObj);
	DPRINT("%s >>>>> I'm here!\n", __FUNCTION__);
	return pRspPutOffObj->retCode;
}

 AMInt32 _AIMTrans_rspPutOffObj(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 FtRspPutOffObj *pRspPutOffObj = AMNULL;
	 AMChar *szBuffer = AMNULL;
	 AMInt32 iBuffLen = 0, iRetCode = eAIM_TRANS_OK;
	 AMAssert(pTrans && sockFd);

	 DPRINT("%s >>>>>> here!\n", __FUNCTION__);
	 if (!(iRetCode = _AIMTrans_recvBuffer(sockFd, &szBuffer, &iBuffLen))
		 && eIMnetOK == (iRetCode = IMnetUnpackPutOffObj(&pRspPutOffObj, szBuffer, iBuffLen)))
	 {
		 iRetCode = _AIMTrans_pickPutOffObj(pTrans, pRspPutOffObj);	 
	 }

	 if(pRspPutOffObj)
		 FreeFtRspPutOffObj(pRspPutOffObj);
	 if(szBuffer)
		 IMnetPackRelease(szBuffer);
	 return iRetCode;
 }

 AMInt32 _AIMTrans_pickPutOffObjFin(AIMTrans *pTrans, FtRspPutOffObjFin *pRspPutOffObjFin)
 {
	 DPRINT("%s >>>>>> I'm here.\n",  __FUNCTION__);
	 return pRspPutOffObjFin->retCode;
 }

 AMInt32 _AIMTrans_rspPutOffObjFin(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 FtRspPutOffObjFin *pRspPutOffObjFin = AMNULL;
	 AMChar *szBuffer = AMNULL;
	 AMInt32 iBuffLen = 0, iRetCode = eAIM_TRANS_OK;
	 AMAssert(pTrans && sockFd);

	 DPRINT("%s >>>>>> here!\n", __FUNCTION__);
	 if (!(iRetCode = _AIMTrans_recvBuffer(sockFd, &szBuffer, &iBuffLen))
		 && eIMnetOK == (iRetCode = IMnetUnpackPutOffObjFin(&pRspPutOffObjFin, szBuffer, iBuffLen)))
	 {
		 iRetCode = _AIMTrans_pickPutOffObjFin(pTrans, pRspPutOffObjFin);	 
	 }

	 if(pRspPutOffObjFin)
		 FreeFtRspPutOffObjFin(pRspPutOffObjFin);
	 if(szBuffer)
		 IMnetPackRelease(szBuffer);
	 return iRetCode;
 }

AMInt32 _AIMTrans_fillGetOffObj(const AIMTrans *pTrans, FtReqGetOffObj *pReq)
{
	AMInt32 strLen = 0;

	AIMTransModule * pTransModule = AMNULL;
	AMAssert(pTrans && pReq);

	pTransModule = (AIMTransModule *)pTrans->pTransModule;

	memset(pReq, 0, sizeof(pReq));
	pReq->propertyNum = 11;
	pReq->uiSubType = 3;
	pReq->ulObjId = pTrans->ulObjId;
	pReq->fileSize = pTrans->uiFileSize;
	pReq->reserved = 0;

	pReq->sendUID = pTransModule->pIM->pAcnt->szID;
	pReq->sendUIDLen = AMStrlen(pReq->sendUID);

	pReq->szToken = pTransModule->pIM->pAcnt->szWebMD5;
	pReq->tokenLen = pTransModule->pIM->pAcnt->uiWebMD5Len;
	
	pReq->szDownloadURL = AMNULL;
	pReq->downloadURLLen = 0;

	pReq->recevierUID = pTrans->szContactId;
	pReq->recevierUIDLen = AMStrlen(pReq->recevierUID);

	pReq->szFileName = pTrans->szFileName;
	pReq->fileNameLen = AMStrlen(pReq->szFileName);

	pReq->szFileExtName = pTrans->szExtend;
	pReq->fileExtNameLen = AMStrlen(pReq->szFileExtName);

	pReq->szFileMD5 = pTrans->szDigest;
	pReq->fileMD5Len = AMStrlen(pReq->szFileMD5);

	return eAIM_RESULT_OK;
}

AMInt32 _AIMTrans_reqGetOffObj(AIMTrans *pTrans, AMInt32 sockFd)
{
	FtReqGetOffObj reqGetOffObj;
	AMChar *szBuffer = AMNULL;
	AMInt32 iBuffLen = 0, iRetCode = eAIM_RESULT_OK;
	AMAssert(pTrans && sockFd);

	DPRINT("%s >>>>>> here!\n", __FUNCTION__);
	if(!(iRetCode = _AIMTrans_fillGetOffObj(pTrans, &reqGetOffObj))
		&& eIMnetOK == (iRetCode = IMnetPackGetOffObj(&reqGetOffObj, &szBuffer, &iBuffLen)))
		{
			iRetCode = _AIMTrans_sendBuffer(sockFd, szBuffer, iBuffLen);
			IMnetPackRelease(szBuffer);
		}
	
	return iRetCode;
}

AMInt32 _AIMTrans_pickGetOffObj(AIMTrans *pTrans,  FtRspGetOffObj *pRspGetOffObj)
{
	pTrans->ulObjId =  pRspGetOffObj->ulObjId;
	DPRINT("%s >>>>>>err code: %d, error msg: %s.\n",  __FUNCTION__, pRspGetOffObj->retCode, pRspGetOffObj->errorMsg);
	return pRspGetOffObj->retCode;
}

 AMInt32 _AIMTrans_rspGetOffObj(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 FtRspGetOffObj *pRspGetOffObj = AMNULL;
	 AMChar *szBuffer = AMNULL;
	 AMInt32 iBuffLen = 0, iRetCode = eAIM_TRANS_OK;
	 AMAssert(pTrans && sockFd);

	 DPRINT("%s >>>>>> here!\n", __FUNCTION__);
	 if (!(iRetCode = _AIMTrans_recvBuffer(sockFd, &szBuffer, &iBuffLen))
		 && eIMnetOK == (iRetCode = IMnetUnpackGetOffObj(&pRspGetOffObj, szBuffer, iBuffLen)))
	 {
		 iRetCode = _AIMTrans_pickGetOffObj(pTrans, pRspGetOffObj);	 
	 }
	 
	 if(pRspGetOffObj)
		 FreeFtRspGetOffObj(pRspGetOffObj);
	 if(szBuffer)
		 IMnetPackRelease(szBuffer);

	 return iRetCode;
 }

 AMInt32 _AIMTrans_fillGetOffObjFin(const AIMTrans *pTrans, FtReqGetOffObjFin *pReq)
 {
	 AMInt32 strLen = 0;

	 AIMTransModule * pTransModule = AMNULL;
	 AMAssert(pTrans && pReq);

	 pTransModule = (AIMTransModule *)pTrans->pTransModule;

	 memset(pReq, 0, sizeof(FtReqGetOffObjFin));
	 pReq->propertyNum = 13;
	 pReq->uiSubType = 3;
	 pReq->ulObjId = pTrans->ulObjId;
	 pReq->fileSize = pTrans->uiFileSize;
	 pReq->reserved = 0;
	 pReq->retCode = 0;

	 pReq->errorMsg = AMNULL;
	 pReq->errorMsgLen = 0;

	 pReq->sendUID = pTransModule->pIM->pAcnt->szID;
	 pReq->sendUIDLen = AMStrlen(pReq->sendUID);

	 pReq->szToken = pTransModule->pIM->pAcnt->szToken;
	 pReq->tokenLen = pTransModule->pIM->pAcnt->uiTokenLen;

	 pReq->szDownloadURL = AMNULL;
	 pReq->downloadURLLen = 0;

	 pReq->recevierUID = pTrans->szContactId;
	 pReq->recevierUIDLen = AMStrlen(pReq->recevierUID);

	 pReq->szFileName = pTrans->szFileName;
	 pReq->fileNameLen = AMStrlen(pReq->szFileName);

	 pReq->szFileExtName = pTrans->szExtend;
	 pReq->fileExtNameLen = AMStrlen(pReq->szFileExtName);

	 pReq->szFileMD5 = pTrans->szDigest;
	 pReq->fileMD5Len = AMStrlen(pReq->szFileMD5);

	 return eAIM_RESULT_OK;
 }

 AMInt32 _AIMTrans_reqGetOffObjFin(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 FtReqGetOffObjFin reqGetOffObjFin;
	 AMChar *szBuffer = AMNULL;
	 AMInt32 iBuffLen = 0, iRetCode = eAIM_RESULT_OK;
	 AMAssert(pTrans && sockFd);

	 DPRINT("%s >>>>>> here!\n", __FUNCTION__);
	 if(!(iRetCode = _AIMTrans_fillGetOffObjFin(pTrans, &reqGetOffObjFin))
		 && eIMnetOK == (iRetCode = IMnetPackGetOffObjFin(&reqGetOffObjFin, &szBuffer, &iBuffLen)))
	 {
		 iRetCode = _AIMTrans_sendBuffer(sockFd, szBuffer, iBuffLen);
		 IMnetPackRelease(szBuffer);
	 }

	 return iRetCode;
 }

 AMInt32 _AIMTrans_pickGetOffObjFin(AIMTrans *pTrans, FtRspGetOffObjFin *pRspGetOffObjFin)
 {
	 pTrans->ulObjId = pRspGetOffObjFin->ulObjId;
	 DPRINT("%s >>>>>>err code: %d, error msg: %s.\n",  __FUNCTION__, pRspGetOffObjFin->retCode, pRspGetOffObjFin->errorMsg);
	 return pRspGetOffObjFin->retCode;
 }

 AMInt32 _AIMTrans_rspGetOffObjFin(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 FtRspGetOffObjFin *pRspGetOffObjFin = AMNULL;
	 AMChar *szBuffer = AMNULL;
	 AMInt32 iBuffLen = 0, iRetCode = eAIM_RESULT_OK;
	 AMAssert(pTrans && sockFd);

	 DPRINT("%s >>>>>> here!\n", __FUNCTION__);
	 if (!(iRetCode = _AIMTrans_recvBuffer(sockFd, &szBuffer, &iBuffLen))
		 && eIMnetOK == (iRetCode = IMnetUnpackGetOffObjFin(&pRspGetOffObjFin, szBuffer, iBuffLen)))
	 {
		 iRetCode = _AIMTrans_pickGetOffObjFin(pTrans, pRspGetOffObjFin);	 
	 }

	 if(pRspGetOffObjFin)
		 FreeFtRspGetOffObjFin(pRspGetOffObjFin);
	 if(szBuffer)
		 IMnetPackRelease(szBuffer);

	 return iRetCode;
 }

 AMInt32	_AIMTrans_recv(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 AMInt32 iRetCode = eAIM_RESULT_OK;
	 AMAssert(pTrans && sockFd);

	 if(!(iRetCode = _AIMTrans_reqGetOffObj(pTrans, sockFd))
		 && !(iRetCode = _AIMTrans_rspGetOffObj(pTrans, sockFd))
		 && !(iRetCode = _AIMTrans_recvFile(pTrans, sockFd)) )
	 {
		 if(!_AIMTrans_reqGetOffObjFin(pTrans, sockFd))
			 _AIMTrans_rspGetOffObjFin(pTrans, sockFd);
	 }

	 if(eAIM_RESULT_CANCEL != iRetCode)
		 AIMTransModule_result(pTrans->pTransModule, pTrans, iRetCode);

	 return iRetCode;
 }

#define		XML_TRANS_NOTIFY	"<xparam><dwImageSize>%d</dwImageSize>"\
	"<strImageHash>%s</strImageHash><llSID>"I64FORMAT"</llSID>"\
	"<strImageExtend>%s</strImageExtend></xparam>"

 AMInt32	_AIMTrans_send(AIMTrans *pTrans, AMInt32 sockFd)
 {
	 AMInt32 iRetCode = eAIM_RESULT_OK;
	 AMAssert(pTrans && sockFd);

	 if (!(iRetCode = _AIMTrans_reqPutOffObj(pTrans, sockFd))
		 && !(iRetCode = _AIMTrans_rspPutOffObj(pTrans, sockFd))
		 && !(iRetCode = _AIMTrans_sendFile(pTrans, sockFd)))
	 {
		 iRetCode = _AIMTrans_rspPutOffObjFin(pTrans, sockFd);
	 }

	 if(eAIM_RESULT_CANCEL != iRetCode)
	 {
		 if(!iRetCode)
		 {
			 //todo: 发送二级协议
			 AIMTransModule *pTransModule = (AIMTransModule *)pTrans->pTransModule;
			 IAIM *pIm = pTransModule->pIM;
			 AMChar szXML[256] = {0};
			 if(pIm && pIm->pAcnt)
			 {
				 AMSprintf(szXML, XML_TRANS_NOTIFY, pTrans->uiFileSize, pTrans->szDigest, pTrans->ulObjId, pTrans->szExtend?pTrans->szExtend:"");

				 IMnetSendFileMessage(pIm->pNetModel, pTrans->szContactId, szXML, AMStrlen(szXML), 1);
			
				 szXML[0] = 0;
				 AMStrcat(szXML, "\\P");
				 AMStrcat(szXML, pTrans->szDigest);
				 AMStrcat(szXML + 32, ".jpg<");
				 IMnetSendMessage(pIm->pNetModel, pTrans->szContactId, szXML, AMStrlen(szXML), 1);
			 				 
			 }
		 }
		 AIMTransModule_result(pTrans->pTransModule, pTrans, iRetCode);
	 }
	 return iRetCode;
 }


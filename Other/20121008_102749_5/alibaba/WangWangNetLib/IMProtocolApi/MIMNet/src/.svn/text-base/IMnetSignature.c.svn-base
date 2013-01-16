// #ifdef _WIN32
// #include <stdio.h>
// #include "IMnetMain.h"
// #include "ghttp.h"
// #include <string.h>
// #include "AMOS.h"
// #include "des.h"
// #include <stdlib.h>
// 
// #define AUIDDOMAIN "http://profile.im.alisoft.com/userprofile/getsignature"
// 
// typedef struct _UrlParam{
// 	unsigned char* key;
// 	unsigned char* value;
// }UrlParam;
// 
// static AMChar* generateHttpBody(UrlParam* param, AMUInt32 size)
// {
// 	AMUInt32 i,len = 0;
// 	AMChar* p = NULL;
// 
// 	if(param == NULL){
// 		return NULL;
// 	}
// 
// 	for(i=0; i<size; i++){
// 		len += (AMUInt32)AMStrlen(param[i].key);
// 		len += (AMUInt32)AMStrlen(param[i].value);
// 		len += 2; //key=value&
// 	}
// 
// 	p = (AMChar*)AMMalloc(len);
// 	AMAssert(p != NULL);
// 	if(p == NULL){
// 		return NULL;
// 	}
// 	AMMemset(p, 0, len);
// 
// 	for(i=0; i<size; i++){
// 		if(i>0){
// 			AMStrcat(p, "&");
// 		}
// 		AMStrcat(p, param[i].key);
// 		AMStrcat(p, "=");
// 		AMStrcat(p, param[i].value);
// 	}
// 
// 	return p;
// }
// 
// 
// static AMChar* urlPost(AMChar *url, AMChar *body){
// 	AMChar *p = NULL;
// 	AMChar *response = NULL;
// 	int status;
// 	AMChar *content = NULL;
// 	int len = 0;
// 	ghttp_request *request = NULL;
// 
// 
// 	request = ghttp_request_new();
// 	ghttp_set_uri(request, url);
// 	ghttp_set_header(request, http_hdr_Connection, "close");
// 	ghttp_set_header(request, http_hdr_Content_Type, "application/x-www-form-urlencoded");
// 	ghttp_set_sync(request, ghttp_sync);
// 	ghttp_set_type(request, ghttp_type_post);
// 	ghttp_set_body(request, body, AMStrlen(body));
// 	ghttp_prepare(request);
// 
// 	status = ghttp_process(request);
// 	if(status == ghttp_done){
// 		content = ghttp_get_body(request);
// 		len = ghttp_get_body_len(request);
// 	}else{
// 		return NULL;
// 	}
// 
// 	if(content == NULL) return NULL;
// 	len = AMStrlen(content)+1;
// 	response = (AMChar*)AMMalloc(len);
// 	AMMemset(response, 0, len);
// 	AMStrcpy(response, content);
// 	ghttp_request_destroy(request);
// 	return response;
// }
// char* _AMItoa(int value, char* string, int radix)
// {
// 	char tmp[33];
// 	char* tp = tmp;
// 	int i;
// 	unsigned v;
// 	int sign;
// 	char* sp;
// 
// 	if (radix > 36 || radix <= 1)
// 	{
// 		return 0;
// 	}
// 
// 	sign = (radix == 10 && value < 0);
// 	if (sign)
// 		v = -value;
// 	else
// 		v = (unsigned)value;
// 	while (v || tp == tmp)
// 	{
// 		i = v % radix;
// 		v = v / radix;
// 		if (i < 10)
// 			*tp++ = i+'0';
// 		else
// 			*tp++ = i + 'a' - 10;
// 	}
// 
// 	if (string == 0)
// 		string = (char*)malloc((tp-tmp)+sign+1);
// 	sp = string;
// 
// 	if (sign)
// 		*sp++ = '-';
// 	while (tp > tmp)
// 		*sp++ = *--tp;
// 	*sp = 0;
// 	return string;
// }
// 
// AMVoid* _getSigXml(AMChar *accountId, AMChar *token,  AMChar *toids, AMInt32 count){
// 	UrlParam param[5];
// 	AMInt32 tmpLen = 0, valueLen = 0;
// 	AMChar *pTmp = NULL;
// 	AMChar *pBody = NULL, *xml = NULL;
// 
// 	param[0].key = "uid";
// 	param[1].key = "toids";
// 	param[2].key = "num";
// 	param[3].key = "v";
// 	param[4].key = "token";
// 
// 	//uid= base64(des(¡°flgflg32¡±, longid))
// 
// 	tmpLen = AMStrlen(accountId);
// 	tmpLen = tmpLen + (tmpLen%8 == 0?0:8-(tmpLen%8));
// 	pTmp = AMMalloc(tmpLen);
// 	AMMemset(pTmp, 0 , tmpLen);
// 	AMStrncpy(pTmp, accountId, AMStrlen(accountId));
// 
// 
// 	param[0].value = des_encrypt("flgflg32", pTmp, tmpLen);
// 	valueLen  = tmpLen;
// 
// 	//base64
// 	tmpLen = (valueLen/3 + ((valueLen%3) == 0 ? 0 : 1)) * 4 + 1;
// 	pTmp = (AMChar*)AMMalloc(tmpLen);
// 	if(base64_encode(param[0].value, valueLen, pTmp, tmpLen) <= 0){
// 		return NULL;
// 	}
// 
// 
// 	AMFree(param[0].value);
// 	param[0].value = pTmp;
// 	param[1].value = toids;
// 	param[2].value = _AMItoa(count, NULL, 10);
// 	param[3].value = "1";
// 	param[4].value = token;
// 
// 
// 	pBody = generateHttpBody(param, sizeof(param)/sizeof(UrlParam));
// 
// 	AMFree(param[0].value);
// 	AMFree(param[2].value);
// 
// 
// 	if(pBody == NULL) return NULL;
// 
// 	xml = urlPost(AUIDDOMAIN, pBody);
// 	AMFree(pBody);
// 	return xml;
// }
// 
// typedef struct {
// 	IMnetHandle	hIMnetHandle;
// 	AMChar	*	szContactIDs;
// 	AMInt32		iCount;
// 	AMChar	*	szToken;
// 	AMChar	*	szAccount;
// }GetSigParam;
// 
// AMVoid	FreeGetSigParam(EventContent *pContent)
// {
// 	GetSigParam* pRequest = (GetSigParam*)pContent;
// 	AMFree(pRequest->szContactIDs);
// }
// 
// void FreeImNtfUpdateUsrExtInfo(EventContent *pContent);
// 
// #define		XML_SIGOP_HEAD	"<SigOp>"
// #define		XML_SIGOP_TAIL	"</SigOp>"
// #define		XML_UPDATE_TYPE	"signature"
// AMPVoid _GetSignatureXML(AMPVoid pvArg)
// {
// 	Event *pEvent = (Event *)pvArg;
// 	GetSigParam *pRequest = (GetSigParam*)((Event*)pvArg)->pContent;
// 	IMnet* pIMnet = (IMnet* )pRequest->hIMnetHandle;
// 	ImNtfUpdateUsrExtInfo	*pFirst = NULL, *pTail = NULL, *pTmp = NULL;
// 	PacketConnection	*pPCHandle = NULL;
// 	
// 	AMChar  *	szXml = 0;
// 	AMChar	*	szSigBegin = NULL, *szSigEnd = NULL, * szPos = NULL;
// 	AMChar	*	szContactBegin = NULL, *szContactEnd = NULL;
// 
// 	szXml = _getSigXml(pRequest->szAccount, pRequest->szToken, pRequest->szContactIDs, pRequest->iCount);
// 	EventDestory(&pEvent);
// 
// 	if(NULL == szXml)
// 		return NULL;
// 
// 	szSigEnd = szXml;
// 	szSigBegin = AMStrstr(szSigEnd, XML_SIGOP_HEAD);
// 	while(szSigBegin)
// 	{
// 		szContactBegin = AMStrstr(szSigEnd, "\1\2") + 2;
// 		szContactEnd = AMStrstr(szContactBegin, "\1");
// 
// 		szSigEnd = AMStrstr(szSigBegin, XML_SIGOP_TAIL);
// 
// 		pTmp = (ImNtfUpdateUsrExtInfo*)AMMalloc(sizeof(ImNtfUpdateUsrExtInfo));
// 		AMMemset(pTmp, 0, sizeof(ImNtfUpdateUsrExtInfo));
// 		
// 		pTmp->iContactIDLen = szContactEnd-szContactBegin-2;
// 		pTmp->szContactID = (AMChar *)AMMalloc(pTmp->iContactIDLen);
// 		AMAssert(NULL != pTmp->szContactID);
// 		AMMemcpy(pTmp->szContactID, szContactBegin+2, pTmp->iContactIDLen);
// 
// 		pTmp->iValueLen = szSigEnd - szSigBegin + sizeof(XML_SIGOP_TAIL);
// 		pTmp->szValue = (AMChar *)AMMalloc(pTmp->iValueLen);
// 		AMAssert(NULL != pTmp->szValue);
// 		AMMemcpy(pTmp->szValue, szSigBegin, pTmp->iValueLen);
// 
// 		pTmp->iTypeLen = sizeof(XML_UPDATE_TYPE);
// 		pTmp->szType = (AMChar *)AMMalloc(pTmp->iTypeLen);
// 		AMStrcpy(pTmp->szType, XML_UPDATE_TYPE);
// 
// 		if(NULL == pFirst)
// 		{
// 			pFirst = pTmp;
// 			pTail = pTmp;
// 		}
// 		else
// 		{
// 			pTail->next = pTmp;
// 			pTail = pTmp;
// 		}
// 	}	
// 
// 	EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_NTF_UPDATE_USREXTINFO, (void*)pFirst, sizeof(ImNtfUpdateUsrExtInfo) FreeImNtfUpdateUsrExtInfo); 
// 
// 	pFirst->next = NULL;
// 	
// 	FreeImNtfUpdateUsrExtInfo(pFirst);
// 	
// 	pPCHandle = (PacketConnection*)pIMnet->hPCHandle;
// 	
// 	PCPostMessage(pPCHandle->pProtocolEngine->pPCContext, pEvent, pPCHandle->pProtocolEngine->pPCCore->pCallbackQueue);
// 
// 	AMFree(szXml);
// 	return NULL;
// }
// 
// //************************************
// // Method:    IMnetGetSignature
// // Access:    public 
// // Author:    yanlong.shiyl
// // Returns:   IMnetRetCode
// // Parameter: IMnetHandle hIMnetHandle
// // Parameter: ContactList * pContactList
// //************************************
// IMnetRetCode IMnetGetSignature(IMnetHandle hIMnetHandle, const AMChar *szAccountID, const AMChar *szToken, const AMChar * szContactIDs, AMInt32 iCount)
// {
// 	IMnetRetCode retCode;
// 	Event* pEvent = NULL;
// 	IMnet* pIMnet = (IMnet*)hIMnetHandle;
// 	AMThread	hThread = NULL;
// 	GetSigParam	request;
// 	AMInt32 iLen = 0;
// 
// 	if(NULL == szAccountID || NULL == szToken || NULL == szContactIDs)
// 		return eInvalidParam;
// 
// 	if(pIMnet != NULL && iCount > 0)
// 	{
// 		memset(&request, 0, sizeof(request));
// 		iLen = AMStrlen(szContactIDs);
// 		request.szContactIDs = (AMChar *)AMMalloc(iLen+1);
// 		if(NULL == request.szContactIDs)
// 		{
// 			return eMallocError;
// 		}
// 		AMStrcpy(request.szContactIDs, szContactIDs);
// 
// 		request.iCount= iCount;
// 		request.hIMnetHandle = hIMnetHandle;
// 		request.szAccount = szAccountID;
// 		request.szToken = szToken;
// 
// 		//·¢ËÍÏûÏ¢
// 		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, 0, (void*)&request, sizeof(request), FreeGetSigParam);
// 		if(retCode == eOK)
// 		{
// 			AMThreadCreate(&hThread, NULL, _GetSignatureXML, pEvent);
// 			AMThreadDetach(hThread);
// 		}
// 	}
// 	else
// 	{
// 		retCode = eNotReady;
// 	}
// 
// 	return retCode;
// }
// 
// #endif // _WIN32
#include "AIMContactModel.h"
#include "AIMGroup.h"
#include "AIM.h"
#include "AIMAccount.h"
#include "AIMessage.h"
#include "AIMSessionModel.h"
#include "AIMUtil.h"

#include "AIMSignature.h"//....

#include "ghttp.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMFS.h"
#include "AMStdlib.h"

#include <stdio.h>
//GBK encoding.
#define		IM_GRPNAME_BIND		"\xCD\xFA\xCD\xFA\xBA\xC3\xD3\xD1"
#define		IM_GRPNAME_BLACK	"\xBA\xDA\xC3\xFB\xB5\xA5"
#define		IM_GRPNAME_STRANGER	"\xC4\xB0\xC9\xFA\xC8\xCB"
#define		IM_GRPNAME_RECENT	"\xD7\xEE\xBD\xFC\xC1\xAA\xCF\xB5\xC8\xCB"
#define		IM_GRPNAME_DEFAULT	"\xCE\xB4\xB7\xD6\xD7\xE9\xBA\xC3\xD3\xD1"

static AMChar _szGroupName_Default[] = {0};

IAContactModel	*	IAContactModel_Create(IAIM	*pReference)
{
	IAContactModel *pRet = AMMalloc(sizeof(IAContactModel));
	AMAssert(0 != pRet);
	AMMemset(pRet, 0, sizeof(IAContactModel));
	
	construct(OHTable, &pRet->ohtFriends, sizeof(IAContact), FREEOBJ);
	set_compare(OHTable, &pRet->ohtFriends, IAContact_CmpID);
	set_dealloc(OHTable, &pRet->ohtFriends, IAContact_Destroy);
	set_hash_OHTable(&pRet->ohtFriends, IAContact_Hash);

	construct(OHTable, &pRet->ohtTmps, sizeof(IAContact), FREEOBJ);
	set_compare(OHTable, &pRet->ohtTmps, IAContact_CmpID);
	set_dealloc(OHTable, &pRet->ohtTmps, IAContact_Destroy);
	set_hash_OHTable(&pRet->ohtTmps, IAContact_Hash);

	construct(OHTable, &pRet->ohtOthers, sizeof(IAContact), FREEOBJ);
	set_compare(OHTable, &pRet->ohtOthers, IAContact_CmpID);
	set_dealloc(OHTable, &pRet->ohtOthers, IAContact_Destroy);
	set_hash_OHTable(&pRet->ohtOthers, IAContact_Hash);

	construct(OHTable, &pRet->ohtRevBlk, sizeof(IAContact), NOFREE);
	set_compare(OHTable, &pRet->ohtRevBlk, IAContact_CmpID);
	set_hash_OHTable(&pRet->ohtRevBlk, IAContact_Hash);

	construct(OHTable, &pRet->ohtGroups, sizeof(IAContact), FREEOBJ);
	set_compare(OHTable, &pRet->ohtGroups, IAGroup_CmpID);
	set_dealloc(OHTable, &pRet->ohtGroups, IAGroup_Destroy);
	set_hash_OHTable(&pRet->ohtGroups, IAGroup_Hash);

	construct(List, &pRet->lTopGrp, sizeof(IAGroup), NOFREE);
	set_compare(List, &pRet->lTopGrp, IAGroup_CmpPinyin);//每个insert的时候，需要CmpPinyin以完成按拼音排序

	pRet->pBindGrp = IAGroup_Create();
	pRet->pBlkGrp = IAGroup_Create();
	pRet->pStrangerGrp = IAGroup_Create();

	pRet->pRecentGrp = IAGroup_Create();
	set_compare(List, &pRet->pRecentGrp->lChildCnt, IAContact_CmpID);

	pRet->pBindGrp->iGroupID = BIND_ACCOUNT_GRP_ID;
	IAGroup_SetName(pRet->pBindGrp, IM_GRPNAME_BIND, sizeof(IM_GRPNAME_BIND));
	pRet->pBlkGrp->iGroupID = BLACK_GRP_ID;
	IAGroup_SetName(pRet->pBlkGrp, IM_GRPNAME_BLACK, sizeof(IM_GRPNAME_BLACK));
	pRet->pStrangerGrp->iGroupID = STRANG_GRP_ID;
	IAGroup_SetName(pRet->pStrangerGrp, IM_GRPNAME_STRANGER, sizeof(IM_GRPNAME_STRANGER));
	pRet->pRecentGrp->iGroupID = RECENT_GRP_ID;
	IAGroup_SetName(pRet->pRecentGrp,IM_GRPNAME_RECENT, sizeof(IM_GRPNAME_RECENT));

	pRet->pReference = pReference;

	return pRet;
}

#define AIMContactModel_Callback(pCntModel, funcName,  ...)	\
	do \
	{\
		if((pCntModel)->pReference->callback && (pCntModel)->pReference->callback->funcName)\
			(pCntModel)->pReference->callback->funcName((pCntModel)->pReference->callback->pvArg, ## __VA_ARGS__);\
	} while (0)


AMInt32		IAContactModel_Notify(IAContactModel *pCntModel, AIM_UPDATE_GROUP_TYPE eType, IAGroup *pGroup, IAContact *pContact)
{
	ContactList	cntList;
	AIM_NTF_UPDATE_GROUP ntfUpdateGroup;
	AMAssert(0 != pCntModel);

	DPRINT("IAContactModel_Notify...........%d, "I64FORMAT", %s\n", eType, pGroup->iGroupID, pContact->szID?pContact->szID:"0");

	if(STRANG_GRP_ID == pGroup->iGroupID && eAIM_GROUP_ADD == eType)
	{
		AMMemset(&cntList, 0, sizeof(cntList));

		cntList.userID = pContact->szID;
		cntList.userIDLen = AMStrlen(pContact->szID);

		IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, &cntList, 1);
	}

	ntfUpdateGroup.eType = eType;
	ntfUpdateGroup.hGroup = pGroup;
	ntfUpdateGroup.hContact = pContact;
	AIMContactModel_Callback(pCntModel, OnNtfUpdateGroup, &ntfUpdateGroup);
	
	return 0;
}

AMInt32		IAContactModel_NotifyCallback(IAContactModel *pCntModel, AIM_UPDATE_GROUP_TYPE eType, IAGroup	*pGroup, IAContact *pContact)
{
	AIM_PRIVATE_EVENT notify;
	IAIM *pIm = (IAIM *)pCntModel->pReference;
	AMInt32 iLen = 0;
	AMAssert(0 != pCntModel);
	DPRINT("IAContactModel_Notify...........%d, "I64FORMAT", %s\n", eType, pGroup->iGroupID, pContact->szID?pContact->szID:"0");

	notify.iEventType = eAIM_PRIVATE_EVENT_CNTDATA;

	notify.iParam1 = eType;
	notify.szParam3 = (AMChar*)pContact;
	notify.i64Param2 = (AMInt32)pGroup;	

	IMnetSendMsg2Callback(pIm->pNetModel, IM_EVENT_PRIVATE, &notify, sizeof(notify), NULL);
	
	return 0;
}

static AMVoid _AIMContact_hideFriend(IAContactModel *pCntModel, IAContact *pCnt)
{
	IAGroup *pGrpFind = AMNULL, *pGrpTmp = IAGroup_Create();
	AMAssert(pCntModel && pCnt);
	AMAssert(AIMContact_isFriend(pCntModel, pCnt));

	//remove from parent groups
	if(pCnt->pParentGrp)
	{
		int iCount = pCnt->pParentGrp->lChildCnt.size;
		set_compare(List, &pCnt->pParentGrp->lChildCnt, IAContact_CmpID);
		delete_List(&pCnt->pParentGrp->lChildCnt, pCnt, sizeof(IAContact));
		if(iCount != pCnt->pParentGrp->lChildCnt.size)
		{
			pCnt->pParentGrp->iUnreadMsgCnt -= pCnt->iUnreadCnt;
			IAContactModel_Notify(pCntModel, eAIM_GROUP_REMOVE, pCnt->pParentGrp, pCnt);
		}
	}
	
	//remove from ohtgroups
	pGrpTmp->iGroupID = pCnt->iParentGid;
	pGrpFind = (IAGroup *)find_OHTable(&pCntModel->ohtGroups, pGrpTmp, sizeof(IAGroup));
	IAGroup_Destroy(pGrpTmp);
	if(pGrpFind)
	{
		int iCount = pGrpFind->lChildCnt.size;
		set_compare(List, &pGrpFind->lChildCnt, IAContact_CmpID);
		delete_List(&pGrpFind->lChildCnt, pCnt, sizeof(IAContact));
		if(iCount != pGrpFind->lChildCnt.size)
		{
			pGrpFind->iUnreadMsgCnt -= pCnt->iUnreadCnt;
			IAContactModel_Notify(pCntModel, eAIM_GROUP_REMOVE, pGrpFind, pCnt);
		}
	}
}

static AMVoid _AIMContact_showFriend(IAContactModel *pCntModel, IAContact *pCnt)
{
	IAGroup *pGrpFind = AMNULL, *pGrpTmp = IAGroup_Create();
	AMAssert(pCntModel && pCnt);
	AMAssert(AIMContact_isFriend(pCntModel, pCnt));
	
	//show from parent groups
	if(pCnt->pParentGrp)
	{
		IAContact *pCntFind = AMNULL;
		pGrpFind = pCnt->pParentGrp;
		set_compare(List, &pGrpFind->lChildCnt, IAContact_CmpID);
		pCntFind = find_List(&pGrpFind->lChildCnt, pCnt, sizeof(IAContact));
		if(!pCntFind)
		{
			set_compare(List, &pGrpFind->lChildCnt, IAContact_CmpPinyin);
			insert_List(&pGrpFind->lChildCnt, pCnt, sizeof(IAContact), STATIC);
			pGrpFind->iUnreadMsgCnt += pCnt->iUnreadCnt;
			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pGrpFind, pCnt);
		}
	}

	pGrpTmp->iGroupID = pCnt->iParentGid;
	pGrpFind = (IAGroup *)find_OHTable(&pCntModel->ohtGroups, pGrpTmp, sizeof(IAGroup));
	IAGroup_Destroy(pGrpTmp);
	if(pGrpFind)
	{
		IAContact *pCntFind = AMNULL;
		set_compare(List, &pGrpFind->lChildCnt, IAContact_CmpID);
		pCntFind = find_List(&pGrpFind->lChildCnt, pCnt, sizeof(IAContact));
		if(!pCntFind)
		{
			set_compare(List, &pGrpFind->lChildCnt, IAContact_CmpPinyin);
			insert_List(&pGrpFind->lChildCnt, pCnt, sizeof(IAContact), STATIC);
			pGrpFind->iUnreadMsgCnt += pCnt->iUnreadCnt;
			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pGrpFind, pCnt);
		}
	}
}

AMVoid IAContactModel_ClearBindData(IAIM *pIM, IAContactModel *pCntModel, AMChar *szBindID)
{
	ListIter	*pListItr = 0;
	OHTableIter	*pItr = 0;
	IAContact * pCnt = NULL;

	if(szBindID == AMNULL) 
		return;

	//clear bind group
	clear(List, &pIM->pCntModel->pBindGrp->lChildCnt);
	//clear revblack
	pCnt = NULL;
	if(pCntModel->ohtRevBlk.num_elem > 0)
	{
		pItr = create(OHTableIter, &pCntModel->ohtRevBlk);
		head(OHTableIter, pItr);
		do 
		{
			if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
				delete_OHTable(&pCntModel->ohtRevBlk, pCnt, sizeof(IAContact));
			pCnt = (IAContact *)retrieve(OHTableIter, pItr);
		} while (!next(OHTableIter, pItr));	
		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
			delete_OHTable(&pCntModel->ohtRevBlk, pCnt, sizeof(IAContact));
		destroy(OHTableIter, pItr);	
	}
	//clear group
	pCnt = NULL;
	if(pCntModel->pRecentGrp)
	{
		pListItr = create(ListIter, (List*)&pCntModel->pRecentGrp->lChildCnt);
		head(ListIter, pListItr);
		do 
		{
			if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
				delete_List(&pCntModel->pRecentGrp->lChildCnt, pCnt, sizeof(IAContact));
			pCnt = (IAContact*)retrieve(ListIter, pListItr);
		} while (!next(ListIter, pListItr));
		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
			delete_List(&pCntModel->pRecentGrp->lChildCnt, pCnt, sizeof(IAContact));
		destroy(ListIter, pListItr);
	}
	pCnt = NULL;
	if(pCntModel->pBlkGrp)
	{
		pListItr = create(ListIter, (List*)&pCntModel->pBlkGrp->lChildCnt);
		head(ListIter, pListItr);
		do 
		{
			if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
				delete_List(&pCntModel->pBlkGrp->lChildCnt, pCnt, sizeof(IAContact));
			pCnt = (IAContact*)retrieve(ListIter, pListItr);
		} while (!next(ListIter, pListItr));
		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
			delete_List(&pCntModel->pBlkGrp->lChildCnt, pCnt, sizeof(IAContact));
		destroy(ListIter, pListItr);
	}
	pCnt = NULL;
	if(pCntModel->pStrangerGrp)
	{
		pListItr = create(ListIter, (List*)&pCntModel->pStrangerGrp->lChildCnt);
		head(ListIter, pListItr);
		do 
		{
			if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
				delete_List(&pCntModel->pStrangerGrp->lChildCnt, pCnt, sizeof(IAContact));
			pCnt = (IAContact*)retrieve(ListIter, pListItr);
		} while (!next(ListIter, pListItr));
		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
			delete_List(&pCntModel->pStrangerGrp->lChildCnt, pCnt, sizeof(IAContact));
		destroy(ListIter, pListItr);
	}
	//pCnt = NULL;
	//if(pCntModel->pRecentGrp)
	//{
	//	pListItr = create(ListIter, (List*)&pCntModel->pRecentGrp->lChildCnt);
	//	head(ListIter, pListItr);
	//	do 
	//	{
	//		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
	//			delete_List(&pCntModel->pRecentGrp->lChildCnt, pCnt, sizeof(IAContact));
	//		pCnt = (IAContact*)retrieve(ListIter, pListItr);
	//	} while (!next(ListIter, pListItr));
	//	if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
	//		delete_List(&pCntModel->pRecentGrp->lChildCnt, pCnt, sizeof(IAContact));
	//	destroy(ListIter, pListItr);
	//}

	//clear bind friend
	pCnt = NULL;
	if(pCntModel->ohtFriends.num_elem > 0)
	{
		pItr = create(OHTableIter, &pCntModel->ohtFriends);
		head(OHTableIter, pItr);
		do 
		{
			if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
				delete_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
			pCnt = (IAContact *)retrieve(OHTableIter, pItr);
		} while (!next(OHTableIter, pItr));	
		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
			delete_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
		destroy(OHTableIter, pItr);	
	}
	//clear strange
	pCnt = NULL;
	if(pCntModel->ohtOthers.num_elem > 0)
	{
		pItr = create(OHTableIter, &pCntModel->ohtOthers);
		head(OHTableIter, pItr);
		do 
		{
			if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
				delete_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));
			pCnt = (IAContact *)retrieve(OHTableIter, pItr);
		} while (!next(OHTableIter, pItr));	
		if(pCnt && pCnt->szBindUID && 0 == AMStrcmp(pCnt->szBindUID, szBindID))
			delete_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));
		destroy(OHTableIter, pItr);	
	}
}



/**
 * 以下是获取头像的功能代码
 */

static AMChar * _PORTRAITURL[] = {	
	"http://jianghu.taobao.com/wangwang/headshow.htm?longId=",		//淘宝帐号，加上longId
	"http://img.china.alibaba.com/club/upload/pic/user/",			//中文站帐号, 加上shortId(shortId的前四个字母后都加"/"), 尾是".tom?random=1"
	"http://call.koubei.com/export/wangwang/getuserlogo.html?size=100&amp;username=",	//口碑帐号
	"",		//旺旺
	"http://www2.im.alisoft.com/webim/personv6/getLogo.htm?signmode=im&amp;wangid=",	//雅虎帐号
	"",		//ALIINT
	"",		//ANONYM
	"",		//ALIMAMA
};

#define		_PORTRAITURL_TAIL		".tom?random=1"

AMChar* _PORTRAIT_GenerateDestUrl(const AMChar* szContactID)
{
	AMUInt32 iIdType = 0, iUrlLen = 0, uiIdLen = 0, i = 0, j = 0;
	AMChar* szUrlRet = AMNULL;

	AMAssert(AMNULL != szContactID);

	uiIdLen = AMStrlen(szContactID);

	switch (iIdType = IAccount_TellType(szContactID, uiIdLen))
	{
	case eAIM_ACNTYPE_TAOBAO:
	case eAIM_ACNTYPE_YAHOO:
	case eAIM_ACNTYPE_KOUBEI:
		iUrlLen = AMStrlen(_PORTRAITURL[iIdType]) + uiIdLen;
		szUrlRet = (AMChar*)AMMalloc(iUrlLen + 1);
		if(szUrlRet)
		{
			AMStrcpy(szUrlRet, _PORTRAITURL[iIdType]);
			AMStrcat(szUrlRet, szContactID);
		}
		break;
	case eAIM_ACNTYPE_ALICHN:
		i = AMStrlen(_PORTRAITURL[iIdType]);
		iUrlLen = i + uiIdLen + sizeof(_PORTRAITURL_TAIL) + 8;
		szUrlRet = (AMChar*)AMMalloc(iUrlLen + 1);
		if(szUrlRet)
		{
			AMMemset(szUrlRet, 0, iUrlLen + 1);
			AMStrcpy(szUrlRet, _PORTRAITURL[iIdType]);
			for(j=0; j<4; j++)
			{
				szUrlRet[i + j*2] = szContactID[ID_HEAD_LEN + j];
				szUrlRet[i + j*2 + 1]  = '/';
			}
			AMStrcat(szUrlRet + i, szContactID + ID_HEAD_LEN);
			AMStrcat(szUrlRet + i, _PORTRAITURL_TAIL);			//+i可以提高效率吧...
		}
		break;
	default:
		return AMNULL;
	}

	return szUrlRet;
}

extern DataBasePath gDatabasePath;
#define		PORTRAIT_FILE_EXT	".aim"
#define		MAX_FILE_EXT_LEN		5
#define		PORTRAIT_FILE_TYPE		"image"
static AMChar* _PortraitGet(AMChar *szContactId)
{
	AMInt32	iPos = 0;
	AMInt32 iGhttpRetCode;
	AMChar *szPortrait = AMNULL;
	int iPortraitLen = 0;
	AMChar	*szUrl = AMNULL;
	const AMChar *szRedirectUrl = AMNULL, *szContentType = AMNULL;
	ghttp_request *request = AMNULL;
	FILE *pFile = AMNULL;
	static AMChar	szFilePath[256] = {0};

	szUrl = _PORTRAIT_GenerateDestUrl(szContactId);
	if(!szUrl)
		return AMNULL;

	request = ghttp_request_new();
	ghttp_set_uri(request, szUrl);
	ghttp_set_header(request, http_hdr_Connection, "close");
	ghttp_set_sync(request, ghttp_sync);
	ghttp_set_type(request, ghttp_type_get);
	ghttp_prepare(request);

	iGhttpRetCode = ghttp_process(request);
	if(ghttp_done == iGhttpRetCode)
	{
		szRedirectUrl = ghttp_get_header(request, http_hdr_Location);
		if(szRedirectUrl)
		{
			ghttp_set_uri(request, (AMChar*)szRedirectUrl);
			ghttp_prepare(request);
			iGhttpRetCode = ghttp_process(request);
		}
	}

	if(ghttp_done == iGhttpRetCode)
	{
		szContentType = ghttp_get_header(request, http_hdr_Content_Type);
		szPortrait = ghttp_get_body(request);
		iPortraitLen = ghttp_get_body_len(request);
	}

	AMFree(szUrl);

	if(szPortrait == AMNULL || AMMemcmp(szContentType, PORTRAIT_FILE_TYPE, sizeof(PORTRAIT_FILE_TYPE)-1))
	{
		ghttp_request_destroy(request);
		return AMNULL;
	}

	AMMemset(szFilePath, 0, sizeof(szFilePath));
	AMStrcpy(szFilePath, gDatabasePath.databasePath);
	iPos = AMStrlen(szFilePath);
	while(*szContactId)
	{
		iPos += _AIMItoa(*((AMUChar *)(szContactId++)), szFilePath+iPos);
	}
	AMStrcat(szFilePath, PORTRAIT_FILE_EXT);

	pFile = fopen(szFilePath, "wb");
	fwrite(szPortrait, iPortraitLen, 1, pFile);
	fclose(pFile);

	ghttp_request_destroy(request);
	return szFilePath;

#if 0
	AMInt32 iGhttpRetCode;
	AMChar *szPortrait = AMNULL;
	int iPortraitLen = 0;
	AMChar	*szUrl = AMNULL;
	const AMChar *szRedirectUrl = AMNULL, *szContentType = AMNULL;
	ghttp_request *request = AMNULL;
	FILE *pFile = AMNULL;
	static AMChar	szFilePath[sizeof(PORTRAIT_PATH) + MAX_ID_LEN + MAX_FILE_EXT_LEN] = {0};

	szUrl = _PORTRAIT_GenerateDestUrl(szContactId);
	if(!szUrl)
		return AMNULL;

	request = ghttp_request_new();
	ghttp_set_uri(request, szUrl);
	ghttp_set_header(request, http_hdr_Connection, "close");
	ghttp_set_sync(request, ghttp_sync); 
	ghttp_set_type(request, ghttp_type_get);
	ghttp_prepare(request);

	iGhttpRetCode = ghttp_process(request);
	if(ghttp_done == iGhttpRetCode)
	{
		szRedirectUrl = ghttp_get_header(request, http_hdr_Location);//第一次是否重定向
		if(szRedirectUrl)
		{
			ghttp_set_uri(request, (AMChar*)szRedirectUrl);
			ghttp_prepare(request);
			iGhttpRetCode = ghttp_process(request);
		}
	}

	if(ghttp_done == iGhttpRetCode)
	{
		szContentType = ghttp_get_header(request, http_hdr_Content_Type);//得到文件的类型
		szPortrait = ghttp_get_body(request);
		iPortraitLen = ghttp_get_body_len(request);
	}

	AMFree(szUrl);

	if(szPortrait == AMNULL || AMMemcmp(szContentType, PORTRAIT_FILE_TYPE, sizeof(PORTRAIT_FILE_TYPE)-1))
	{
		ghttp_request_destroy(request);
		return AMNULL;
	}

	AMMemset(szFilePath, 0, sizeof(PORTRAIT_PATH) + MAX_ID_LEN + MAX_FILE_EXT_LEN);
	AMStrcpy(szFilePath, PORTRAIT_PATH);
	AMStrcat(szFilePath, szContactId);
	AMStrcat(szFilePath, PORTRAIT_FILE_EXT);

	pFile = fopen(szFilePath, "wb");
	fwrite(szPortrait, iPortraitLen, 1, pFile);
	fclose(pFile);

	ghttp_request_destroy(request);
	return szFilePath;
#endif
}

static AMChar* _IAIM_GetPortrait(const AMChar* szContactId)
{
	AMChar *szFilePath = AMNULL;

	szFilePath = _PortraitGet((AMChar*)szContactId);

	return szFilePath;
}

/**
 * 以上是获取头像的功能代码
 */

/**
 * 以下是获取签名的功能代码
 */

#define AUIDDOMAIN_REAL "http://profile.im.alisoft.com/userprofile/getsignature"
#define AUIDDOMAIN_TEST "http://10.250.3.46/userprofile/getsignature"

static AMChar* generateHttpBody(UrlParam* param, AMUInt32 size)
{
	AMUInt32 i,len = 0;
	AMChar* p = NULL;

	if(param == NULL){
		return NULL;
	}

	for(i=0; i<size; i++){
		len += (AMUInt32)AMStrlen(param[i].key);
		len += (AMUInt32)AMStrlen(param[i].value);
		len += 2; //key=value&
	}

	p = (AMChar*)AMMalloc(len);
	AMAssert(p != NULL);
	if(p == NULL){
		return NULL;
	}
	AMMemset(p, 0, len);

	for(i=0; i<size; i++){
		if(i>0){
			AMStrcat(p, "&");
		}
		AMStrcat(p, param[i].key);
		AMStrcat(p, "=");
		AMStrcat(p, param[i].value);
	}

	return p;
}

#define  MAX_WAIT_TIME	2000

//返回的AMChar*需要调用者释放
AMInt32 urlPost(AMChar *url, AMChar *body, AMChar **pszSignature){
	AMChar *p = NULL;
	AMChar *response = NULL;
	AMInt32 status, len = 0, iTime = 0;
	AMChar *content = NULL;
	ghttp_request *request = NULL;

	request = ghttp_request_new();
	ghttp_set_uri(request, url);
	ghttp_set_header(request, http_hdr_Connection, "close");
	ghttp_set_header(request, http_hdr_Content_Type, "application/x-www-form-urlencoded");
	ghttp_set_sync(request, ghttp_async);
	ghttp_set_type(request, ghttp_type_post);
	ghttp_set_body(request, body, AMStrlen(body));
	ghttp_prepare(request);

	DPRINT("urlPost.................url:%s, body:%s\n", url, body);

	while(1)
	{
		status = ghttp_process(request);

		DPRINT("urlPost.....................After ghttp_process %x,status: %d\n", request, status);

		if(ghttp_done == status)
		{
			content = ghttp_get_body(request);
			len = ghttp_get_body_len(request);
			break;
		}
		else if(ghttp_not_done == status)
		{
			AMSleep(200);
			iTime += 200;
			if(iTime > MAX_WAIT_TIME)
			{
				ghttp_close(request);
				ghttp_request_destroy(request);
				return -1;
			}
		}
		else
		{
			ghttp_request_destroy(request);
			return -1;
		}
	}
	
	if(content == NULL)
	{
		*pszSignature = NULL;
		ghttp_request_destroy(request);
		return 0;
	}
	
	len = AMStrlen(content)+1;
	response = (AMChar*)AMMalloc(len);
	AMMemset(response, 0, len);
	AMStrcpy(response, content);
	ghttp_request_destroy(request);

	*pszSignature = response;

	return 0;
}
char* _AMItoa(int value, char* string, int radix)
{
	char tmp[33];
	char* tp = tmp;
	int i;
	unsigned v;
	int sign;
	char* sp;

	if (radix > 36 || radix <= 1)
	{
		return 0;
	}

	sign = (radix == 10 && value < 0);
	if (sign)
		v = -value;
	else
		v = (unsigned)value;
	while (v || tp == tmp)
	{
		i = v % radix;
		v = v / radix;
		if (i < 10)
			*tp++ = i+'0';
		else
			*tp++ = i + 'a' - 10;
	}

	if (string == 0)
		string = (char*)malloc((tp-tmp)+sign+1);
	sp = string;

	if (sign)
		*sp++ = '-';
	while (tp > tmp)
		*sp++ = *--tp;
	*sp = 0;
	return string;
}

AMChar origin[11] = "\x59\x53\x5E\x59\x53\x5E\x19\x18\x2A\x2A";

static AMChar* _AIM_Orz(void)
{	
	static AMInt32 key = 0;
	static AMChar szRet[11] = {0};
	AMInt32 i = 0;
	
	if(!szRet[0])
		return szRet;

	key = rand()%129+1;	

	for(i=0 ; i<10; i++)
	{
		origin[i] ^= key;
	}

	for (i=0; i<10; i++)
	{
		int k = (AMInt32)origin[i];

		if (k >= 97 && k <= 109)
		{
			k = k + 13;
		}
		else if( k >= 110 && k <= 122 )
		{
			k = k - 13;
		}
		else if (k >= 65 && k <= 77)
		{
			k = k + 13 ;
		}
		else if( k >= 78 && k <= 90 )
		{
			k = k - 13;
		}
		szRet[i] = k;
	}

	return szRet;
}

IMnetRetCode _getSigXml(AMChar *accountId, AMChar *token, AMUChar ucTest, AMChar *toids, AMInt32 count, AMChar **pszXML)
{
	UrlParam param[5];
	AMInt32 tmpLen = 0, valueLen = 0, iRetCode = 0;
	AMChar *pTmp = NULL;
	AMChar *pBody = NULL, *xml = NULL;
	static AMChar *pTmp2[20] = {0};

	AMAssert(NULL != pszXML);

	param[0].key = "uid";
	param[1].key = "toids";
	param[2].key = "num";
	param[3].key = "v";
	param[4].key = "token";

	tmpLen = AMStrlen(accountId);
	tmpLen = tmpLen + (tmpLen%8 == 0?0:8-(tmpLen%8));
	pTmp = AMMalloc(tmpLen);
	AMMemset(pTmp, 0 , tmpLen);
	AMStrncpy(pTmp, accountId, AMStrlen(accountId));

	param[0].value = des_encrypt(_AIM_Orz(), pTmp, tmpLen);
	valueLen  = tmpLen;

    
	tmpLen = (valueLen/3 + ((valueLen%3) == 0 ? 0 : 1)) * 4 + 1; 
    pTmp = NULL;
	pTmp = (AMChar*)AMMalloc(tmpLen);
        
    if(ali_base64_encode(param[0].value, (size_t)valueLen, pTmp, (size_t)tmpLen) <= 0) {
        return eIMnetNotReady;
    }
    
	AMFree(param[0].value);
	param[0].value = pTmp;
	param[1].value = toids;
	param[2].value = _AMItoa(count, NULL, 10);
	param[3].value = "1";
	param[4].value = token;

	pBody = generateHttpBody(param, sizeof(param)/sizeof(UrlParam));

	AMFree(param[0].value);
    param[0].value=NULL;
	AMFree(param[2].value);
    param[2].value=NULL;
    
	if(pBody == NULL) return eIMnetNotReady;

	if(ucTest){
        iRetCode = urlPost(AUIDDOMAIN_TEST, pBody, &xml);
    }
	else{
        iRetCode = urlPost(AUIDDOMAIN_REAL, pBody, &xml);
    }
	AMFree(pBody);

	*pszXML = xml;

	if(!iRetCode)
		return eIMnetOK;
	else
		return eIMnetNotReady;
}


extern void FreeImNtfUpdateUsrExtInfo(EventContent *pContent);

#define		XML_SIGOP_HEAD		"<SigOp>"
#define		XML_SIGOP_TAIL		"</SigOp>"
#define		XML_UPDATE_TYPE_SIG	"signature"
AMPVoid _GetSignatureXML(IAContactModel *pCntModel, AMUChar ucTest, const AMChar *szCntIds, AMInt32 iCount)
{
	IMnetHandle* pIMnet = pCntModel->pReference->pNetModel;
	ImNtfUpdateUsrExtInfo	*pFirst = NULL, *pTail = NULL, *pTmp = NULL;
	AMInt32		iSignatureCount = 0;

	AMChar  *	szXml = 0;
	AMChar	*	szSigBegin = NULL, *szSigEnd = NULL, * szPos = NULL;
	AMChar	*	szContactBegin = NULL, *szContactEnd = NULL;
	IMnetRetCode retCode = eIMnetOK;
	AIM_RSP_GET_SIGNATURE rspGetSignature;

	AMAssert(pCntModel && pCntModel->pReference && pCntModel->pReference->pAcnt);
	AMAssert(pCntModel->pReference->pAcnt->szToken);

#ifdef AMOS_DEBUG
	AMPrintf("_GetSignatureXML...............Before _getSigXml!\n");
#endif // AMOS_DEBUG

	retCode = _getSigXml(pCntModel->pReference->pAcnt->szID, pCntModel->pReference->pAcnt->szToken,
							ucTest, szCntIds, iCount, &szXml);

	DPRINT("_GetSignatureXML................._getSigXml return %d\n", retCode);

	AMMemset(&rspGetSignature, 0, sizeof(rspGetSignature));

	if(eIMnetOK != retCode || !szXml)
	{
		rspGetSignature.iRetCode = -1;
		rspGetSignature.pszContactIds = &szCntIds;
		AIMContactModel_Callback(pCntModel, OnRspGetSignature, &rspGetSignature);
		return NULL;
	}

	szSigEnd = szXml;
	szSigBegin = AMStrstr(szSigEnd, XML_SIGOP_HEAD);
	while(szSigBegin)
	{
		szContactBegin = AMStrstr(szSigEnd, "\1\2") + 2;
		if(NULL == szContactBegin)
			break;

		szContactEnd = AMStrstr(szContactBegin, "\1");
		if(NULL == szContactEnd)
			break;

		szSigEnd = AMStrstr(szSigBegin, XML_SIGOP_TAIL);
		if(NULL == szSigEnd)
			break;

		pTmp = (ImNtfUpdateUsrExtInfo*)AMMalloc(sizeof(ImNtfUpdateUsrExtInfo));
		if(NULL == pTmp)
			break;

		AMMemset(pTmp, 0, sizeof(ImNtfUpdateUsrExtInfo));

		pTmp->iValueLen = szSigEnd - szSigBegin + sizeof(XML_SIGOP_TAIL);
		pTmp->szValue = (AMChar *)AMMalloc(pTmp->iValueLen);
		if(NULL == pTmp->szValue)
		{
			AMFree(pTmp);
			break;
		}
		AMMemcpy(pTmp->szValue, szSigBegin, pTmp->iValueLen);

		pTmp->iContactIDLen = szContactEnd-szContactBegin;
		pTmp->szContactID = (AMChar *)AMMalloc(pTmp->iContactIDLen);
		if(NULL == pTmp->szContactID)
		{
			AMFree(pTmp->szValue);
			AMFree(pTmp);
			break;
		}
		AMMemcpy(pTmp->szContactID, szContactBegin, pTmp->iContactIDLen);		

		pTmp->iTypeLen = sizeof(XML_UPDATE_TYPE_SIG);
		pTmp->szType = (AMChar *)AMMalloc(pTmp->iTypeLen);
		if(NULL == pTmp->szType)
		{
			AMFree(pTmp->szContactID);
			AMFree(pTmp->szValue);
			AMFree(pTmp);
			break;
		}
		AMStrcpy(pTmp->szType, XML_UPDATE_TYPE_SIG);

		if(NULL == pFirst)
		{
			pFirst = pTmp;
			pTail = pTmp;
		}
		else
		{
			pTail->next = pTmp;
			pTail = pTmp;
		}

		iSignatureCount++;

		szSigBegin = AMStrstr(szSigEnd, XML_SIGOP_HEAD);
	}

	AMFree(szXml);

	if(iSignatureCount>0)
	{
		pFirst->iCount = iSignatureCount;
		IMnetSendMsg2Callback(pCntModel->pReference->pNetModel, IM_NTF_UPDATE_USREXTINFO, 
						(void*)pFirst, sizeof(ImNtfUpdateUsrExtInfo), FreeImNtfUpdateUsrExtInfo); 
		AMFree(pFirst);
	}
	else
	{
		rspGetSignature.iRetCode = retCode;
		rspGetSignature.pszContactIds = &szCntIds;
		AIMContactModel_Callback(pCntModel, OnRspGetSignature, &rspGetSignature);
	}

	return NULL;
}

/**
 * 以上是获取签名的功能代码
 */


IMnetRetCode	IAContactModel_OnIMEvent(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	AIM_PRIVATE_EVENT	*pEvent = (AIM_PRIVATE_EVENT*)pEventContent;
	IAIM*	pIM = (IAIM *)IMnetGetReference(hIMnetHandle);

	AMAssert(AMNULL != pIM && AMNULL != pEvent);
	
	if(eAIM_PRIVATE_EVENT_CNTDATA == pEvent->iEventType)
	{
		IAContactModel_Notify(pIM->pCntModel, pEvent->iParam1, (AMHandle)pEvent->i64Param2, (AMHandle)pEvent->szParam3);
		
		return eIMnetSkip;
	}
	else if(eAIM_PRIVATE_EVENT_PORTRAIT == pEvent->iEventType)
	{
		AIM_RSP_GET_PROTRAIT ntfGetPortrait;
		AMChar * szFilePath = _IAIM_GetPortrait(pEvent->szParam3);
		if(szFilePath)
		{
			ntfGetPortrait.iRetCode = 0;
		}
		else
		{
			ntfGetPortrait.iRetCode = -1;
		}
		ntfGetPortrait.szContactId = pEvent->szParam3;//退出的时候会被销毁
		ntfGetPortrait.szValue = szFilePath;

		AIMContactModel_Callback(pIM->pCntModel, OnRspGetPortrait, &ntfGetPortrait);

		return eIMnetSkip;
	}
	else if(eAIM_PRIVATE_EVENT_SIGNATURE == pEvent->iEventType)
	{
		_GetSignatureXML(pIM->pCntModel, pIM->bTest, pEvent->szParam3, pEvent->iParam1);

		return eIMnetSkip;
	}
	return eIMnetOK;
}

AMVoid			IAContactModel_UpdateRecent(IAContactModel *pCntModel, const AMChar *szCntID
											, const AMChar *szMsg, AMInt32 iMsgLen, AMBool bDirect)
{
	IAContact *pTmpCnt = 0, *pCntFind = 0;
	AMBool bIsFriend = AMFALSE, bIsStranger = AMFALSE;
	ContactList		cntList;

	AMAssert(0 != pCntModel && 0 != szCntID);

	AMMemset(&cntList, 0, sizeof(ContactList));

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szCntID, AMStrlen(szCntID));

	pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
	{
		bIsFriend = AMFALSE;
		pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	}
	else
	{
		bIsFriend = AMTRUE;
	}

	if(0 != pCntFind)
	{
		IAContact_Destroy(pTmpCnt);

		IAContact_MarkRecent(pCntFind);
		delete_List(&pCntModel->pRecentGrp->lChildCnt, pCntFind, sizeof(IAContact));

		if(pCntModel->pRecentGrp->lChildCnt.size >= MAX_RECENT_NUM)
		{
			pop_back_List(&pCntModel->pRecentGrp->lChildCnt);
		}

		push_front_List(&pCntModel->pRecentGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);

		if(szMsg)
			IAContact_SetLastMsg(pCntFind, szMsg, iMsgLen);

		IAIMContact_IsStrange(pCntFind, &bIsStranger);
		if(AMFALSE == bIsFriend && AMFALSE == bIsStranger)
		{
			IAContact_MarkStrang(pCntFind);
			pCntFind->pParentGrp = pCntModel->pStrangerGrp;

			if(pCntModel->pStrangerGrp->lChildCnt.size >= MAX_STRANGE_NUM)
			{
				pop_back_List(&pCntModel->pStrangerGrp->lChildCnt);
			}

			insert_List(&pCntModel->pStrangerGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);
			pCntModel->uiDirtFlag |= 0x20;

			cntList.userID = pCntFind->szID;
			cntList.userIDLen = AMStrlen(pCntFind->szID);
			IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, &cntList, 1);

			DPRINT("IAContactModel_UpdateRecent...................Stranger!");

			if(bDirect)
				IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pCntModel->pStrangerGrp, pCntFind);
			else
				IAContactModel_NotifyCallback(pCntModel, eAIM_GROUP_ADD, pCntModel->pStrangerGrp, pCntFind);
		}
	}
	else
	{
		IAContact_MarkRecent(pTmpCnt);
		IAContact_SetNickName(pTmpCnt, pTmpCnt->szID + 8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_SetPinyin(pTmpCnt, pTmpCnt->szID + 8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_AutoSetBindUid(pCntModel->pReference, pTmpCnt);
		insert_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);
		
		if(pCntModel->pRecentGrp->lChildCnt.size >= MAX_RECENT_NUM)
		{
			pop_back_List(&pCntModel->pRecentGrp->lChildCnt);
		}
		
		push_front_List(&pCntModel->pRecentGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);
		
		//加到陌生人，dirt陌生人
		IAContact_MarkStrang(pTmpCnt);
		pTmpCnt->pParentGrp = pCntModel->pStrangerGrp;

		if(pCntModel->pStrangerGrp->lChildCnt.size >= MAX_STRANGE_NUM)
		{
			pop_back_List(&pCntModel->pStrangerGrp->lChildCnt);
		}

		insert_List(&pCntModel->pStrangerGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);
		pCntModel->uiDirtFlag |= 0x20;
		
		if(szMsg)
			IAContact_SetLastMsg(pTmpCnt, szMsg, iMsgLen);

		cntList.userID = pTmpCnt->szID;
		cntList.userIDLen = AMStrlen(pTmpCnt->szID);
		IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, &cntList, 1);
		//通知添加联系人到陌生人。

		DPRINT("IAContactModel_UpdateRecent...................Stranger!");

		if(bDirect)
			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pCntModel->pStrangerGrp, pTmpCnt);
		else
			IAContactModel_NotifyCallback(pCntModel, eAIM_GROUP_ADD, pCntModel->pStrangerGrp, pTmpCnt);
	}

	pCntModel->uiDirtFlag |= 0x40;
}

AMVoid				IAContactModel_ClearData(IAContactModel *pCntModle)
{
	AMAssert(0 != pCntModle);

	DPRINT("IAContactModel_ClearData....................Entering\n");

	clear(List, &pCntModle->pBlkGrp->lChildCnt);
	clear(List, &pCntModle->pRecentGrp->lChildCnt);
	clear(List, &pCntModle->pStrangerGrp->lChildCnt);
	clear(List, &pCntModle->pBindGrp->lChildCnt);

	clear(List, &pCntModle->lTopGrp);
	
	clear(OHTable, &pCntModle->ohtGroups);
	clear(OHTable, &pCntModle->ohtRevBlk);
	clear(OHTable, &pCntModle->ohtOthers);
	clear(OHTable, &pCntModle->ohtFriends);


	DPRINT("IAContactModel_ClearData....................OK\n");
}

AMVoid				IAContactModel_Destroy(IAContactModel *pCntModel)
{
	AMAssert(0 != pCntModel);

	destruct(OHTable, &pCntModel->ohtFriends);
	destruct(OHTable, &pCntModel->ohtOthers);
	destruct(OHTable, &pCntModel->ohtTmps);

	destruct(OHTable, &pCntModel->ohtRevBlk);

	destruct(OHTable, &pCntModel->ohtGroups);

	destruct(List, &pCntModel->lTopGrp);

	IAGroup_Destroy(pCntModel->pBindGrp);
	IAGroup_Destroy(pCntModel->pBlkGrp);
	IAGroup_Destroy(pCntModel->pRecentGrp);
	IAGroup_Destroy(pCntModel->pStrangerGrp);

	AMFree(pCntModel);
}

IAIM  *	IAContactModel_GetReference(const IAContactModel *pCntModel)
{
	AMAssert(0 != pCntModel);
	return pCntModel->pReference;
}

AIM_RESULT IAIMContactModel_GetGroupList( AMHandle hContactModel, const List **ppList )
{
	IAContactModel *pCntModel = (IAContactModel*)hContactModel;
	AMAssert(AMNULL != pCntModel && AMNULL != ppList);

	*ppList = &pCntModel->lTopGrp;

	return eAIM_RESULT_OK;
}



IAContact	*	IAContactModel_FindContact(const IAContactModel *pCntModel, const IAContact *pCnt)
{
	IAContact *pRet = 0;
	pRet = (IAContact*)find_OHTable((OHTable *)&pCntModel->ohtFriends, (void*)pCnt, sizeof(IAContact));
	if(0 == pRet)
		pRet = (IAContact*)find_OHTable((OHTable *)&pCntModel->ohtOthers, (void*)pCnt, sizeof(IAContact));
	return pRet;
}

AIM_RESULT IAIMContactModel_GetContactByID( AMHandle hContactModel, const AMChar *szCntID, AMHandle *phContact )
{
	IAContactModel *pCntModel = (IAContactModel *)hContactModel;
	IAContact *pTmp = AMNULL;
	AMAssert(AMNULL != pCntModel && AMNULL != szCntID && AMNULL != phContact);

	pTmp = IAContact_Create();
	IAContact_SetCntID(pTmp, szCntID, AMStrlen(szCntID));

	*phContact = (AMHandle)IAContactModel_FindContact(hContactModel, pTmp);
	IAContact_Destroy(pTmp);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContactModel_GetGroupByID( AMHandle hContactModel, AMInt64 i64GrpID, AMHandle *phGroup )
{
	IAContactModel *pCntModel = (IAContactModel *)hContactModel;
	IAGroup *pRet = 0, *pTmp = 0;

	AMAssert(AMNULL != pCntModel && AMNULL != phGroup);

	if(BLACK_GRP_ID == i64GrpID)
	{
		*phGroup = pCntModel->pBlkGrp;
	}
	else if(RECENT_GRP_ID == i64GrpID)
	{
		*phGroup = pCntModel->pRecentGrp;
	}
	else if(STRANG_GRP_ID == i64GrpID)
	{
		*phGroup = pCntModel->pStrangerGrp;
	}
	else if(BIND_ACCOUNT_GRP_ID == i64GrpID)
	{
		*phGroup = pCntModel->pBindGrp;
	}
	else
	{
		pTmp = IAGroup_CreateProc(AMTRUE);
		pTmp->iGroupID = i64GrpID;
		*phGroup = (IAGroup*)find_OHTable(&pCntModel->ohtGroups, pTmp, sizeof(IAGroup));
		IAGroup_Destroy(pTmp);
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContactModel_RemoveRecent( AMHandle hContactModel, const AMChar *szCntID )
{
	IAContactModel *pCntModel = (IAContactModel *)hContactModel;
	IAContact *pCntFind = AMNULL;
	AMBool	bIsRecent = AMFALSE;
	ListIter *pIter = AMNULL;
	AMAssert(AMNULL != pCntModel);

	DPRINT("IAIMContactModel_RemoveRecent................%s\n", szCntID?szCntID:"0");

	if(AMNULL == szCntID)		//清除所有
	{
		if(0 < pCntModel->pRecentGrp->lChildCnt.size)
		{
			pIter = create(ListIter, &pCntModel->pRecentGrp->lChildCnt);
			head(ListIter, pIter);
			do 
			{
				pCntFind = (IAContact*)retrieve(ListIter, pIter);
				pCntFind->uiFlag &= ~0x08;							//去除最近联系人人标记
			} while (!next(ListIter, pIter));
			destroy(ListIter, pIter);

			pCntModel->uiDirtFlag |= 0x40;
			clear(List, &pCntModel->pRecentGrp->lChildCnt);	
		}
		return eAIM_RESULT_OK;		//同步清除，需要回调么？
	}

	IAIMContactModel_GetContactByID(hContactModel, szCntID, &pCntFind);
	if(AMNULL == pCntFind)
	{
		DPRINT("IAIMContactModel_RemoveRecent................%s not found!\n", szCntID?szCntID:"0");
		return eAIM_RESULT_OK;
	}

	IAIMContact_IsRecent(pCntFind, &bIsRecent);
	if(AMTRUE == bIsRecent)
	{
		DPRINT("IAIMContactModel_RemoveRecent................%s is removing!\n", szCntID?szCntID:"0");
		set_compare(List, &pCntModel->pRecentGrp->lChildCnt, IAContact_CmpID);
		delete_List(&pCntModel->pRecentGrp->lChildCnt, pCntFind, sizeof(IAContact));
		pCntFind->uiFlag &= ~0x08;

		pCntModel->uiDirtFlag |= 0x40;
		IAContactModel_NotifyCallback(pCntModel, eAIM_GROUP_REMOVE, pCntModel->pRecentGrp, pCntFind);//同步事件要不要回调？
	}
	else
	{
		DPRINT("IAIMContactModel_RemoveRecent................%s is not recent!\n", szCntID?szCntID:"0");
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContactModel_RemoveStranger( AMHandle hContactModel, const AMChar *szCntID )
{
	IAContactModel *pCntModel = (IAContactModel *)hContactModel;
	IAContact *pCntFind = AMNULL;
	AMBool	bIsStrange = AMFALSE;
	ListIter *pIter = AMNULL;
	AMAssert(AMNULL != pCntModel);

	DPRINT("IAIMContactModel_RemoveStranger..................%s\n", szCntID);

	if(AMNULL == szCntID)		//清除所有
	{
		if(0 < pCntModel->pStrangerGrp->lChildCnt.size)
		{
			pIter = create(ListIter, &pCntModel->pStrangerGrp->lChildCnt);
			head(ListIter, pIter);
			do 
			{
				pCntFind = (IAContact*)retrieve(ListIter, pIter);		//移除自陌生人组
				pCntFind->uiFlag &= ~0x04;								//去除陌生人标记
			} while (!next(ListIter, pIter));
			destroy(ListIter, pIter);

			pCntModel->uiDirtFlag |= 0x20;
			clear(List, &pCntModel->pStrangerGrp->lChildCnt);
		}
		return eAIM_RESULT_OK;		//同步清除，需要回调么？
	}

	IAIMContactModel_GetContactByID(pCntModel, szCntID, &pCntFind);
	if(AMNULL == pCntFind)
		return eAIM_RESULT_OK;

	IAIMContact_IsStrange(pCntFind, &bIsStrange);
	if(AMTRUE == bIsStrange)
	{
		set_compare(List, &pCntModel->pStrangerGrp->lChildCnt, IAContact_CmpID);
		delete_List(&pCntModel->pStrangerGrp->lChildCnt, pCntFind, sizeof(IAContact));
		set_compare(List, &pCntModel->pStrangerGrp->lChildCnt, IAContact_CmpPinyin);

		pCntFind->uiFlag &= ~0x04;//清除陌生人标记

		pCntModel->uiDirtFlag |= 0x20;
		IAContactModel_NotifyCallback(pCntModel, eAIM_GROUP_REMOVE, pCntModel->pStrangerGrp, pCntFind);
	}
	else
	{
		DPRINT("IAIMContactModel_RemoveStranger..................%s is Not Stranger!\n", szCntID);
	}

	DPRINT("IAIMContactModel_RemoveStranger..................%s OK!\n", szCntID);

	return eAIM_RESULT_OK;
}

/************************************************************************/
/* callbacks for IMnet                                                  */
/************************************************************************/

IMnetRetCode	IAContactModel_OnGetGroup(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetGroup	*pGetGroup = (ImEventGetGroup*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	UserGroupList	*pGrpList = 0;
	IAGroup	*pGrp = 0;
	AMInt64	i64Tmp = 0;
	AMBool bNeedDefault = AMTRUE;
	AMBool bBindContacts = AMFALSE;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm);
	pCntModel = pIm->pCntModel;

	if(pGetGroup->bindID && 0 != AMStrcmp(pIm->pAcnt->szID, pGetGroup->bindID))
	{
		bBindContacts = AMTRUE;
		//TODO;
		return eIMnetOK; 
	}

	AMAssert(eIM_STATUS_LOGINOKRECVED == pIm->ucImStatus);

	AMAssert(0 != pIm->pAcnt);

	pGrpList = pGetGroup->groupList;

	clear(List, &pCntModel->lTopGrp); 
	clear(OHTable, &pCntModel->ohtGroups);
	while(0 != pGrpList)
	{
		pGrp = IAGroup_Create();
		i64Tmp = pGrpList->groupIDHigh;
		pGrp->iGroupID = (i64Tmp<<32)+pGrpList->groupIDLow;
		i64Tmp = pGrpList->parentIDup;
		pGrp->iParentGid = (i64Tmp<<32) + pGrpList->parentIDlw;
		
		if(0 == pGrp->iGroupID)
		{
			IAGroup_SetName(pGrp, IM_GRPNAME_DEFAULT, sizeof(IM_GRPNAME_DEFAULT)-1);
			//这里需要做向拼音的转换
			IAGroup_SetPinyin(pGrp, IM_GRPNAME_DEFAULT, sizeof(IM_GRPNAME_DEFAULT)-1);
			bNeedDefault = AMFALSE;
		}
		else
		{
			IAGroup_SetName(pGrp, pGrpList->groupName, pGrpList->groupNameLen);
			//这里需要做向拼音的转换
			IAGroup_SetPinyin(pGrp, pGrpList->groupName, pGrpList->groupNameLen);
		}

		insert(OHTable, &pCntModel->ohtGroups, pGrp, DYNAMIC);
		pGrpList = pGrpList->pNext;
	}

	if(AMTRUE == bNeedDefault)
	{
		DPRINT("IAContactModel_OnGetGroup..................Need to creat default group!\n");
		pGrp = IAGroup_Create();
		IAGroup_SetName(pGrp, IM_GRPNAME_DEFAULT, sizeof(IM_GRPNAME_DEFAULT)-1);
		IAGroup_SetPinyin(pGrp, IM_GRPNAME_DEFAULT, sizeof(IM_GRPNAME_DEFAULT)-1);
		pGrp->iGroupID = 0;
		pGrp->iParentGid = -1;
		insert(OHTable, &pCntModel->ohtGroups, pGrp, DYNAMIC);
	}

	DPRINT("IAContactModel_OnGetGroup..........OK\n");

	IAContactModel_BuildGroupTree(pCntModel);

	if(0 == (pCntModel->uiDirtFlag & 0x02))
	{
		IAContactModel_SetAllContact(pCntModel, bBindContacts);
	}

	pCntModel->uiDirtFlag |= 0x01;
	pIm->pAcnt->iGroupStamp	= pGetGroup->timestamp;

	return eIMnetOK; 
}

AMInt32		IAContactModel_RestoreBlack(IAContactModel *pCntModel, sqlite3 *pDB);
AMInt32		IAContactModel_RestoreRevBlk(IAContactModel *pCntModel, sqlite3 *pDB);
AMInt32		IAContactModel_RestoreStranger(IAContactModel *pCntModel, sqlite3 *pDB);
AMInt32		IAContactModel_RestoreRecent(IAContactModel *pCntModel, sqlite3 *pDB);

IMnetRetCode	IAContactModel_OnGetContact(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	AMInt32 iRcSqlite	= 0;
	sqlite3		*pDB	= 0;
	ImEventGetContact	*pEvent = (ImEventGetContact*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	UserContactList *pCntList = 0;
	ContactInfo	*pCntInfo = 0;
	IAContact	*pCnt;
	AMInt64 i64Tmp = 0;
	AMBool bBindContacts = AMFALSE;

	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm && 0 != pIm->pAcnt);
	pCntModel = pIm->pCntModel;

	if(pEvent->bindID && 0 != AMStrcmp(pIm->pAcnt->szID, pEvent->bindID))
	{
		bBindContacts = AMTRUE;
	}

	DPRINT("IAContactModel_OnGetContact..........Begin\n");
	//AMAssert(eIM_STATUS_GROUPRECVED == pIm->ucImStatus);

	if(!bBindContacts)
		clear(OHTable, &pCntModel->ohtFriends);

	pCntList = pEvent->contactList;
	while (0 != pCntList)
	{
		pCnt = IAContact_Create();
		IAContact_SetCntID(pCnt, pCntList->contactInfo.contactID, pCntList->contactInfo.contactIDLen);
		//这里需要做向拼音的转换
		if(0 == pCntList->contactInfo.nickName)
		{
			IAContact_SetNickName(pCnt, pCntList->contactInfo.contactID+8, pCntList->contactInfo.contactIDLen-8);
			IAContact_SetPinyin(pCnt, pCntList->contactInfo.contactID+8, pCntList->contactInfo.contactIDLen-8);
		}
		else
		{
			IAContact_SetNickName(pCnt, pCntList->contactInfo.nickName, pCntList->contactInfo.nickNameLen);
			IAContact_SetPinyin(pCnt, pCntList->contactInfo.nickName, pCntList->contactInfo.nickNameLen);
		}

		if(bBindContacts)
		{
			pCnt->iParentGid = BIND_ACCOUNT_GRP_ID;
			IAContact_SetBindUid(pCnt, pEvent->bindID, pEvent->bindIDLen);
		}
		else
		{
			IAContact_AutoSetBindUid(pIm, pCnt);
			i64Tmp = pCntList->contactInfo.groupIDHigh;
			pCnt->iParentGid = (i64Tmp<<32) + pCntList->contactInfo.groupIDLow;
		}
		DPRINT("IAContactModel_OnGetContact..........Add: %s\n", pCntList->contactInfo.contactID);
		insert_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact), DYNAMIC);

		pCntList = pCntList->pNext;
	}

	DPRINT("IAContactModel_OnGetContact..........OK\n");
	
	pCntModel->uiDirtFlag |= 0x02;

	if(bBindContacts)
	{
		IAContactModel_BuildBindContactList(pCntModel);
	}
	else
	{
		pIm->pAcnt->iContactStamp = pEvent->timestamp;

		iRcSqlite = myADB_Open(pCntModel->pReference->pAcnt->szID, &pDB, AMFALSE);

		if(iRcSqlite)
		{
			DPRINT("IAContactModel_OnGetContact:.......Can't sqlite3_open: %s\n", sqlite3_errmsg(pDB));
			sqlite3_close(pDB);
			return eIMnetOK;
		}

		IAContactModel_RestoreStranger(pCntModel, pDB);		//这里的顺序要跟Restore中的顺序一致
		IAContactModel_RestoreRecent(pCntModel, pDB);

		if((pCntModel->uiDirtFlag & 0x04) != 0x04)
			IAContactModel_RestoreBlack(pCntModel, pDB);	////以下几个必须在ohtFriends和ohtOthers建立之后，他们的数据都在这两个之中。

		if((pCntModel->uiDirtFlag & 0x08) != 0x08)
			IAContactModel_RestoreRevBlk(pCntModel, pDB);

		sqlite3_close(pDB);

		IAContactModel_SetAllContact(pCntModel, bBindContacts);
	}

	return eIMnetOK; 
}

IMnetRetCode	IAContactModel_OnGetCNExtraInfo(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetCNExtraInfo	*pEvent = (ImEventGetCNExtraInfo*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	Contact_ExtraInfo *pInfoList = 0;
	IAContact	*pCnt = 0, *pCntFind = 0;
	//AIM_NTF_UPDATE_CONTACT ntfUpdateContact;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm);
	pCntModel = pIm->pCntModel;

	pIm->phoneNumRetCode = pEvent->retcode;

	pIm->phoneNumStatus = 1;

	if(pEvent->contactExtraInfos == NULL || pEvent->contactCount == 0)
		return eIMnetOK;

	pIm->phoneNumStatus = 2;
	
	//AMMemset(&ntfUpdateContact, 0, sizeof(ntfUpdateContact));

	//ntfUpdateContact.phContacts = (AMHandle*) AMMalloc (sizeof(AMHandle)*(pEvent->statusCount));
	//AMMemset(ntfUpdateContact.phContacts, 0, sizeof(AMHandle)*pEvent->statusCount);
	//ntfUpdateContact.eType = eAIM_CONTACT_PRESENCE;

	pInfoList = pEvent->contactExtraInfos;
	pCnt = IAContact_Create();
	while(0 != pInfoList)
	{
		if(!AMStrcmp(pIm->pAcnt->szID, pInfoList->userID))
		{
			AMAssert(0 != pCnt);
			if(pIm->szPhoneNum)
			{
				AMFree(pIm->szPhoneNum);
				pIm->szPhoneNum = 0;
			}

			pIm->phoneNumStatus = 3;
			if(pInfoList->phone && pInfoList->phoneLen > 0)
			{
				pIm->szPhoneNum = (AMChar *)AMMalloc(pInfoList->phoneLen + 1);
				AMAssert(AMNULL != pIm->szPhoneNum);
				AMMemcpy(pIm->szPhoneNum, pInfoList->phone, pInfoList->phoneLen);
				pIm->szPhoneNum[pInfoList->phoneLen] = 0;
				pIm->phoneNumStatus = 4;
			}
		}
		else
		{
			IAContact_SetCntID(pCnt, pInfoList->userID, pInfoList->userIDLen);
			pCntFind = (IAContact *)find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
			if(0 == pCntFind)
				pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));;

			if(0 != pCntFind)
			{
				IAContact_SetPhone(pCnt, pInfoList->phone, pInfoList->phoneLen);
				DPRINT("IAContactModel_OnGetCNExtraInfo..........%s, phone: %s\n", pInfoList->userID, pInfoList->phone);
			}
			else
			{
				DPRINT("IAContactModel_OnGetCNExtraInfo..........cnt %s not find in this IM\n", pCnt->szID);
			}
		}
		pInfoList = pInfoList->pNext;
	}

	IAContact_Destroy(pCnt);

	//if(ntfUpdateContact.iCount>0)//通知状态变化~
	//	AIMContactModel_Callback(pCntModel, OnNtfUpdateContact, &ntfUpdateContact);

	//AMFree(ntfUpdateContact.phContacts);

	return eIMnetOK;
}

IMnetRetCode	IAContactModel_OnGetWebBinding(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetWebBinding	*pEvent = (ImEventGetWebBinding*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	Bind_Service *pList = 0;
	IAContact	*pCnt = 0, *pCntFind = 0;
	AMChar*	szBindID = NULL;
	AMInt32 nBindIDLen = 0;
	AIM_NTF_DATA_READY ntfDataReady;
	//AIM_NTF_UPDATE_CONTACT ntfUpdateContact;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm);
	pCntModel = pIm->pCntModel;

	if(pEvent->retcode != 0)
	{
		pIm->pAcnt->eBindStatus = eAIM_BIND_GET_BINDED_FAIL;
	}
	else if(pEvent->bindList == NULL || pEvent->bindListCount == 0)
	{
		pIm->pAcnt->eBindStatus = eAIM_BIND_NO_BIND;
	}
	else
	{//取第一个bind的id，目前仅支持bind一个
		nBindIDLen = pEvent->bindList->serviceIDLen + pEvent->bindList->webUidLen;
		szBindID = (AMChar *)AMMalloc(nBindIDLen+1);
		AMAssert(0 != szBindID);
		if(pEvent->bindList->serviceIDLen > 0)
			AMMemcpy(szBindID, pEvent->bindList->serviceID, pEvent->bindList->serviceIDLen);
		if(pEvent->bindList->webUidLen > 0)
			AMMemcpy(szBindID + pEvent->bindList->serviceIDLen, pEvent->bindList->webUid, pEvent->bindList->webUidLen);
		szBindID[nBindIDLen] = 0;
		IAccount_SetBindID(pIm->pAcnt, szBindID, nBindIDLen);
		AMFree(szBindID);
		pIm->pAcnt->eBindStatus = eAIM_BIND_BINDED;
	}

	if(pIm->pAcnt->eBindStatus != eAIM_BIND_BINDED)
	{
		ntfDataReady.eInfo = eDATA_BINDID_ALLREADY;
		AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);
	}

	return eIMnetOK;
}


IMnetRetCode	IAContactModel_OnNtfWebUserMessage(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventNtfWebUserMessage	*pEvent = (ImEventNtfWebUserMessage*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	IAContact	*pCnt = 0, *pCntFind = 0;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm);
	pCntModel = pIm->pCntModel;

	DPRINT("IAContactModel_OnNtfWebUserMessage..........Start\n");

	if(pEvent->cmdId == 2463
		&& pEvent->pOhtData->num_elem > 0)
	{
		OHTableIter *pIter = AMNULL;
		StrStrPair	*pPair = AMNULL;
		AMInt32 phoneNumLen = 0;

		pIter = create(OHTableIter, pEvent->pOhtData);
		head(OHTableIter, pIter);
		do 
		{
			pPair = (StrStrPair*)retrieve(OHTableIter, pIter);
			if(AMNULL != pPair->szKey && AMNULL != pPair->szValue)
			{
				DPRINT("IAContactModel_OnNtfWebUserMessage..........%s, phone: %s\n", pPair->szKey, pPair->szValue);
				phoneNumLen = AMStrlen(pPair->szValue);
				if(!AMStrcmp(pIm->pAcnt->szID, pPair->szKey))
				{
					if(pIm->szPhoneNum)
					{
						AMFree(pIm->szPhoneNum);
						pIm->szPhoneNum = 0;
					}

					pIm->szPhoneNum = (AMChar *)AMMalloc(phoneNumLen + 1);
					AMAssert(AMNULL != pIm->szPhoneNum);
					AMMemcpy(pIm->szPhoneNum, pPair->szValue, phoneNumLen);
					pIm->szPhoneNum[phoneNumLen] = 0;
				}
				else
				{
					pCnt = IAContact_Create();
					IAContact_SetCntID(pCnt, pPair->szKey, AMStrlen(pPair->szKey));
					pCntFind = (IAContact *)find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
					if(0 == pCntFind)
						pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));;

					if(pCntFind)
					{
						IAContact_SetPhone(pCnt, pPair->szValue, phoneNumLen);
					}
					else
					{
						DPRINT("IAContactModel_OnNtfWebUserMessage..........cnt %s not find in this IM\n", pCnt->szID);
					}
				}			
			}
		} while (!next(OHTableIter, pIter));
		destroy(OHTableIter, pIter);
	}

	return eIMnetOK;
}


IMnetRetCode	IAContactModel_OnGetBlack(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetBlack	*pEvent = (ImEventGetBlack*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	ContactList *pCntList = 0;
	IAContact	*pCnt = 0, *pCntFind = 0, *pBlackCntFind = 0;
	AIM_NTF_DATA_READY ntfDataReady;
	AMBool bBindContacts = AMFALSE;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm && 0 != pIm->pAcnt);
	pCntModel = pIm->pCntModel;

	pCntList = pEvent->contactList;

	if(pEvent->bindID && 0 != AMStrcmp(pIm->pAcnt->szID, pEvent->bindID))
	{
		bBindContacts = AMTRUE;
	}

	if(!bBindContacts)
		clear(List, &pCntModel->pBlkGrp->lChildCnt);

	pCnt = IAContact_Create();

	while (0 != pCntList)
	{
		IAContact_SetCntID(pCnt, pCntList->userID, pCntList->userIDLen);
		DPRINT("IAContactModel_OnGetBlack......ID: %s \n", pCntList->userID);
		pCntFind = find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
		if(pCntFind)
		{
			if(pCntFind->pParentGrp)
			{
				set_compare(List, &pCntFind->pParentGrp->lChildCnt, IAContact_CmpID);
				delete_List(&pCntFind->pParentGrp->lChildCnt, pCntFind, sizeof(IAContact));
			}
		}
		else
			pCntFind = find_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));

		if(pCntFind)
		{
			IAContact_MarkBlack(pCntFind);
			if(pEvent->bindID)
				IAContact_SetBindUid(pCntFind, pEvent->bindID, pEvent->bindIDLen);
			else
				IAContact_AutoSetBindUid(pIm, pCntFind);
			set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
			insert_List(&pCntModel->pBlkGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);
		}
		else
		{
			IAContact_MarkBlack(pCnt);
			IAContact_SetNickName(pCnt, pCntList->userID+8, pCntList->userIDLen-8);
			IAContact_SetPinyin(pCnt, pCntList->userID+8, pCntList->userIDLen-8);
			if(pEvent->bindID)
				IAContact_SetBindUid(pCnt, pEvent->bindID, pEvent->bindIDLen);
			else
				IAContact_AutoSetBindUid(pIm, pCnt);
			insert_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact), DYNAMIC);
			set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
			insert_List(&pCntModel->pBlkGrp->lChildCnt, pCnt, sizeof(IAContact), DYNAMIC);
			pCnt = IAContact_Create();
		}
		pCntList = pCntList->pNext;
	}

	IAContact_Destroy(pCnt);

	pCntModel->uiDirtFlag |= 0X04;
	pIm->pAcnt->iBlackStamp	= pEvent->timestamp;

	DPRINT("IAContactModel_OnGetBlack...............OK\n");

	IMnetPutBindInfo(pCntModel->pReference->pNetModel, pEvent->bindID, pEvent->bindIDLen);
	IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, pEvent->contactList, 1);

	if((pCntModel->uiDirtFlag & 0x08) == 0x00)
	{
		IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_ALLREADY);
		ntfDataReady.eInfo = bBindContacts ? eDATA_BINDID_ALLREADY : eDATA_ALLREADY;
	}
	else
	{
		ntfDataReady.eInfo = eDATA_BLACK_READY;
		IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_BLACKRECVED);
	}
	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);
	
	return eIMnetOK; 
}
IMnetRetCode	IAContactModel_OnGetRevBlack(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetBlack	*pEvent = (ImEventGetBlack*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	ContactList *pCntList = 0;
	IAContact	*pCnt = 0, *pCntFind = 0;
	AIM_NTF_DATA_READY ntfDataReady;
	AMBool bBindContacts = AMFALSE;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm && 0 != pIm->pAcnt);
	pCntModel = pIm->pCntModel;

	if(pEvent->bindID && 0 != AMStrcmp(pIm->pAcnt->szID, pEvent->bindID))
	{
		bBindContacts = AMTRUE;
	}

	if(!bBindContacts)
		clear(OHTable, &pCntModel->ohtRevBlk);

	pCntList = pEvent->contactList;
	pCnt = IAContact_Create();
	while (0 != pCntList)
	{	
		IAContact_SetCntID(pCnt, pCntList->userID, pCntList->userIDLen);
		DPRINT("IAContactModel_OnGetRevBlack......ID: %s \n", pCntList->userID);
		pCntFind = find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
		if(0 == pCntFind)
			pCntFind = find_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));

		if(0 != pCntFind)
		{
			(pCntFind->uiFlag) |= 0x02;
			if(pEvent->bindID)
				IAContact_SetBindUid(pCntFind, pEvent->bindID, pEvent->bindIDLen);
			else
				IAContact_AutoSetBindUid(pIm, pCntFind);
			insert_OHTable(&pCntModel->ohtRevBlk, pCntFind, sizeof(IAContact), DYNAMIC);
		}
		else
		{
			(pCnt->uiFlag) |= 0x02;
			IAContact_SetNickName(pCnt, pCntList->userID+8, pCntList->userIDLen-8);
			IAContact_SetPinyin(pCnt, pCntList->userID+8, pCntList->userIDLen - 8);
			if(pEvent->bindID)
				IAContact_SetBindUid(pCnt, pEvent->bindID, pEvent->bindIDLen);
			else
				IAContact_AutoSetBindUid(pIm, pCnt);
			insert_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact), DYNAMIC);
			set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
			insert_OHTable(&pCntModel->ohtRevBlk, pCnt, sizeof(IAContact), DYNAMIC);
			pCnt = IAContact_Create();
		}
		pCntList = pCntList->pNext;
	}
	IAContact_Destroy(pCnt);

	pIm->pCntModel->uiDirtFlag |= 0x08;
	pIm->pAcnt->iRevBlackStamp	= pEvent->timestamp;

	DPRINT("IAContactModel_OnGetRevBlack......OK\n");
	IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_ALLREADY);

	ntfDataReady.eInfo = bBindContacts ? eDATA_BINDID_ALLREADY : eDATA_ALLREADY;
	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	return eIMnetOK; 
}

//bind id has been kicked
IMnetRetCode IAContactModel_OnBindIDForceDisconnect(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventNtfForceDisconnect *pEvt = (ImEventNtfForceDisconnect *)pEventContent;
	IAContactModel *pCntModel = pIM->pCntModel;
	IAContact * pCnt = NULL;
	AIM_NTF_DATA_READY ntfDataReady;

	AMAssert(0 != pIM && 0 != pCntModel);

	AMAssert(eIM_STATUS_ALLREADY >= pIM->ucImStatus && eIM_STATUS_LOGINOKRECVED <= pIM->ucImStatus);

	DPRINT("IAIM_OnBindIDForceDisconnect......................begin!\n");
	if(pEvt->bindID && pEvt->bindIDLen > 0 && 0 != AMStrcmp(pIM->pAcnt->szID, pEvt->bindID))
	{//绑定帐号被踢，通知上层
		DPRINT("IAIM_OnBindIDForceDisconnect......................delete from friends!\n");
		//TODO删除好友列表
		pIM->pAcnt->eBindStatus = eAIM_BIND_BIND_KICK;
		IAContactModel_ClearBindData(pIM, pCntModel, pEvt->bindID);

		ntfDataReady.eInfo = eDATA_BINDID_KICKED;
		AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	}

	//DPRINT("IAIM_OnBindIDForceDisconnect.........................Entering!\n");
	////AMAssert(pIM->ucImStatus >= IM_STATUS_LOGINOKRECVED);//应该是这个，先调整一下状态值大小关系
	//if(eIM_STATUS_ALLREADY == pIM->ucImStatus)
	//{
	//	IAIM_StoreClear(pIM, AMFALSE);	//被踢下线的时候，不清空数据
	//}

	//IMnetConnectClose(pIM->pNetModel);

	//IAIM_TransStatus(pIM, eIM_STATUS_FORCEDISC);

	//IAIM_Callback(pIM, OnNtfForceDisconnected);

	DPRINT("IAIM_OnBindIDForceDisconnect......................OK!\n");
	return eIMnetOK;
}





IMnetRetCode	IAContactModel_OnGetCntStatus(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetContactStatus	*pEvent = (ImEventGetContactStatus*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	IAContact *pCnt = 0, *pCntFind = 0;
	ContactStatusList	*pStatusList = 0;
	AIM_NTF_UPDATE_CONTACT ntfUpdateContact;
	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm);
	pCntModel = pIm->pCntModel;

	pStatusList = pEvent->contactStatusList;

	ntfUpdateContact.phContacts = (AMHandle*) AMMalloc (sizeof(AMHandle)*(pEvent->contactStatusCount));
	AMMemset(ntfUpdateContact.phContacts, 0, sizeof(AMHandle)*pEvent->contactStatusCount);
	ntfUpdateContact.iCount = 0;
	ntfUpdateContact.eType = eAIM_CONTACT_PRESENCE_FIRST;

	pCnt = IAContact_Create();
	while(0 != pStatusList)
	{
		IAContact_SetCntID(pCnt, pStatusList->userID, pStatusList->userIDLen);
		
		pCntFind = find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
		if(0 == pCntFind)
			pCntFind = find_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));
		
		if(0 != pCntFind)
		{
			pCntFind->ePresence = convert2Status(pStatusList->basicStatus, pStatusList->predefStatus);
			ntfUpdateContact.phContacts[ntfUpdateContact.iCount++] = pCntFind;
		}
		else
		{
			IAContact *pCntDup = IAContact_Duplicate(pCnt);
			IAContact_SetNickName(pCntDup, pCntDup->szID + 8, AMStrlen(pCntDup->szID)-8);
			IAContact_SetPinyin(pCntDup, pCntDup->szID + 8, AMStrlen(pCntDup->szID)-8);
			IAContact_AutoSetBindUid(pIm, pCntDup);
			insert_OHTable(&pCntModel->ohtOthers, pCntDup, sizeof(IAContact), DYNAMIC);

			IAContact_MarkStrang(pCntDup);
			pCntDup->pParentGrp = pCntModel->pStrangerGrp;

			if(pCntModel->pStrangerGrp->lChildCnt.size >= MAX_STRANGE_NUM)
			{
				pop_back_List(&pCntModel->pStrangerGrp->lChildCnt);
			}

			insert_List(&pCntModel->pStrangerGrp->lChildCnt, pCntDup, sizeof(IAContact), DYNAMIC);
			pCntModel->uiDirtFlag |= 0x20;

			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pCntModel->pStrangerGrp, pCntDup);
			DPRINT("IAContactModel_OnGetCntStatus.........没有这个人， 加入到陌生人%s\n", pCntDup->szID);
		}
		pStatusList = pStatusList->pNext;
	}
	IAContact_Destroy(pCnt);

	if(ntfUpdateContact.iCount>0)//通知状态变化~
		AIMContactModel_Callback(pCntModel, OnNtfUpdateContact, &ntfUpdateContact);

	AMFree(ntfUpdateContact.phContacts);
	
	DPRINT("IAContactModel_OnGetCntStatus......OK\n");
	return eIMnetOK; 
}

IMnetRetCode	IAContactModel_OnAddContact(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventAddContact *pEvnt = (ImEventAddContact*)pEventContent;
	IAIM	*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IAContactModel		*pCntModel = pIM->pCntModel;
	IAContact	*pTmpCnt = 0, *pCntFind = 0;
	AMInt64	i64Tmp = 0;
	IAGroup	*pTmpGrp = 0, *pGrpFind = 0;
	AMBool	bTmp = AMFALSE, bBlack = AMFALSE;
	AMUInt32	uiStrangeNum = 0;
	
	AIM_RSP_ADD_CONTACT rspAddContact;

	AMAssert(0 != pIM && 0 != pIM->pAcnt);
	AMAssert(0 != pCntModel && 0 != pEvnt);

	rspAddContact.eRetCode = pEvnt->retCode;
	rspAddContact.szContactId = AMMalloc(pEvnt->contactInfo.contactIDLen + 1);
	AMMemcpy(rspAddContact.szContactId, pEvnt->contactInfo.contactID, pEvnt->contactInfo.contactIDLen);
	rspAddContact.szContactId[pEvnt->contactInfo.contactIDLen] = 0;

	DPRINT("%s >>>>>> contactId:%s, retCode:%d, info:%d\n", __FUNCTION__, 
		rspAddContact.szContactId, pEvnt->retCode, pEvnt->info);
	
	if(0 == pEvnt->retCode)
	{
		pTmpCnt = IAContact_Create();

		IAContact_SetCntID(pTmpCnt, pEvnt->contactInfo.contactID, pEvnt->contactInfo.contactIDLen);
		AMAssert(0 == find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact)));//这个人不在好友中。
		insert_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact), DYNAMIC);//加入好友列表

		IAContact_SetNickName(pTmpCnt, pEvnt->contactInfo.nickName, pEvnt->contactInfo.nickNameLen);
		IAContact_SetPinyin(pTmpCnt, pEvnt->contactInfo.nickName, pEvnt->contactInfo.nickNameLen);
		if(pEvnt->bindID)
			IAContact_SetBindUid(pTmpCnt, pEvnt->bindID, pEvnt->bindIDLen);
		else
			IAContact_AutoSetBindUid(pIM, pTmpCnt);

		if(pTmpCnt->szBindUID && 0 != AMStrcmp(pIM->pAcnt->szID, pTmpCnt->szBindUID))
			pTmpCnt->iParentGid = BIND_ACCOUNT_GRP_ID;
		else
		{
			i64Tmp = pEvnt->contactInfo.groupIDHigh;
			pTmpCnt->iParentGid = (i64Tmp<<32) + pEvnt->contactInfo.groupIDLow;
		}
		
		pTmpGrp = IAGroup_CreateProc(AMTRUE);
		pTmpGrp->iGroupID = pTmpCnt->iParentGid;

		pGrpFind = (IAGroup	*)find_OHTable(&pCntModel->ohtGroups, pTmpGrp, sizeof(IAGroup));
		if(AMNULL == pGrpFind && pTmpGrp->iGroupID == BIND_ACCOUNT_GRP_ID)
			pGrpFind = pCntModel->pBindGrp;
		AMAssert(0 != pGrpFind);//所加联系人必须有父亲组。
		IAGroup_Destroy(pTmpGrp);		
		pTmpCnt->pParentGrp = pGrpFind;
		insert_List(&pGrpFind->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);//加入到对应组

		{
			ContactList cntList;
			cntList.pNext = AMNULL;
			cntList.userID = pEvnt->contactInfo.contactID;
			cntList.userIDLen = pEvnt->contactInfo.contactIDLen;
			IMnetPutBindInfo(pIM->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID) : 0);
			IMnetSubscribeContactInfo(pIM->pNetModel, &cntList, 1);			
		}

		//将others中数据的引用，转到friends的数据上。
		pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
		if(0 != pCntFind)
		{
			pTmpCnt->uiFlag = pCntFind->uiFlag;
			pTmpCnt->ePresence = pCntFind->ePresence;

			if(pCntFind->szLastMsg)
				IAContact_SetLastMsg(pTmpCnt, pCntFind->szLastMsg, AMStrlen(pCntFind->szLastMsg));

			IAIMContact_IsStrange(pCntFind, &bTmp);
			if(bTmp)		//与uiStrangeNum的作用，可以二选一...，bTmp更有逻辑，但uiStrangeNum更...霸道...
			{
				pTmpCnt->uiFlag &= ~0x04;//去除陌生人标记

				uiStrangeNum = pCntModel->pStrangerGrp->lChildCnt.size;

				set_compare(List, &pCntModel->pStrangerGrp->lChildCnt, IAContact_CmpID);
				delete_List(&pCntModel->pStrangerGrp->lChildCnt, pCntFind, sizeof(IAContact));
				set_compare(List, &pCntModel->pStrangerGrp->lChildCnt, IAContact_CmpPinyin);

				if(uiStrangeNum > pCntModel->pStrangerGrp->lChildCnt.size)
				{					
					pCntModel->uiDirtFlag |= 0x20;
					
					pCntModel->pStrangerGrp->iUnreadMsgCnt -= pCntFind->iUnreadCnt;	//修正组的未读消息个数
					AMAssert(0 <= pCntModel->pStrangerGrp->iUnreadMsgCnt);
					pTmpCnt->pParentGrp->iUnreadMsgCnt += pCntFind->iUnreadCnt;

					IAContactModel_Notify(pCntModel, eAIM_GROUP_REMOVE, pCntModel->pStrangerGrp, pCntFind);	
				}
			}

			IAIMContact_IsBlack(pCntFind, &bBlack);
			if(bBlack)
			{
				set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
				delete_List(&pCntModel->pBlkGrp->lChildCnt, pCntFind, sizeof(IAContact));
				set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpPinyin);
				insert_List(&pCntModel->pBlkGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);

				IMnetDeleteBlack(pCntModel->pReference->pNetModel, pCntFind->szID);
			}

			IAIMContact_IsRecent(pCntFind, &bTmp);
			if(bTmp)
			{
				delete_List(&pCntModel->pRecentGrp->lChildCnt, pCntFind, sizeof(IAContact));
				push_front_List(&pCntModel->pRecentGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);
				pCntModel->uiDirtFlag |= 0x40;
			}
			
			if(IAContact_IsRevBlack(pCntFind))
			{
				delete_OHTable(&pCntModel->ohtRevBlk, pCntFind, sizeof(IAContact));
				insert_OHTable(&pCntModel->ohtRevBlk, pTmpCnt, sizeof(IAContact), DYNAMIC);
			}

			delete_OHTable(&pCntModel->ohtOthers, pCntFind, sizeof(IAContact));
		}
		else
		{
			DPRINT("IAContactModel_OnAddContact...............contact %s not find in others\n", pEvnt->contactInfo.contactID);
		}

		DPRINT("IAContactModel_OnAddContact.........contact %s added.\n", pEvnt->contactInfo.contactID);

		//修订当前账户的联系人时间戳，并将该联系人数据标记为dirt.
		pIM->pAcnt->iContactStamp = pEvnt->timestamp;
		pCntModel->uiDirtFlag	|= 0x02;

		//if(!bBlack)
			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pGrpFind, pTmpCnt);	
	}
	else if(1 == pEvnt->retCode)//需要验证
	{
		rspAddContact.eInfo = eADDCONTACT_INFO_NEEDAUTH;
	}
	else if(2 == pEvnt->retCode)//已经发过验证了，等待对方回复。
	{
		rspAddContact.eInfo = eADDCONTACT_INFO_WAITAUTH;
	}
	else if(-1 == pEvnt->retCode)//失败
	{
		rspAddContact.eInfo = (pEvnt->info>eADDCONTACT_INFO_OTHERERROR)?eADDCONTACT_INFO_OTHERERROR:
			(pEvnt->info<=0?eADDCONTACT_INFO_OTHERERROR:pEvnt->info);
	}
	else
	{
		AMAssert(0);//pEvnt->retCode不应该有其他的值~
	}

	DPRINT("%s >>>>>> retCode: %d, info: %d, contact: %s\n", 
		__FUNCTION__, pEvnt->retCode, pEvnt->info, pEvnt->contactInfo.contactID);

	if(!bBlack)
	{
		AIMContactModel_Callback(pCntModel, OnRspAddContact, &rspAddContact);
	}

	if(rspAddContact.szContactId)
		AMFree(rspAddContact.szContactId);

	return eIMnetOK;
}

IMnetRetCode	IAContactModel_OnAddBlack(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventAddBlack *pEvnt = (ImEventAddBlack*)pEventContent;
	IAIM		*pIM	= (IAIM*)IMnetGetReference(hIMnetHandle);
	IAContactModel		*pCntModel = pIM->pCntModel;
	IAContact	*pTmpCnt = 0, *pCntFind = 0;
	AMInt64	i64Tmp = 0;
	IAGroup	*pTmpGrp = 0, *pGrpFind = 0;
	AMUInt32	uiStrangeCount = 0;
	AMBool		bIsStrange = AMFALSE;
	ContactList		cntList;
	AIM_RSP_ADD_BLACK rspAddBlack;
	
	AMAssert(0 != pIM && 0 != pIM->pAcnt);
	AMAssert(0 != pCntModel && 0 != pEvnt);

	AMMemset(&cntList, 0, sizeof(cntList));
	AMMemset(&rspAddBlack, 0, sizeof(rspAddBlack));
	
	if(0 == pEvnt->retCode)//ok
	{
		pTmpCnt = IAContact_Create();
		IAContact_SetCntID(pTmpCnt, pEvnt->blackId, pEvnt->blackIdLen);

		pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
		if(pCntFind)
			bIsStrange = AMFALSE;
		else
		{
			bIsStrange = AMTRUE;
			pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
		}

		if(pCntFind)
		{
			IAContact_Destroy(pTmpCnt);
			AMAssert((pCntFind->uiFlag & 0x01) == 0);//确认此人不在黑名单列表中
			IAContact_MarkBlack(pCntFind);
			insert_List(&pCntModel->pBlkGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);

			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pCntModel->pBlkGrp, pCntFind);

			if(!bIsStrange)
				_AIMContact_hideFriend(pCntModel, pCntFind);
		}
		else
		{
			IAContact_MarkBlack(pTmpCnt);
			IAContact_SetNickName(pTmpCnt, pEvnt->blackId+8, pEvnt->blackIdLen-8);
			IAContact_SetPinyin(pTmpCnt, pEvnt->blackId+8, pEvnt->blackIdLen-8);
			IAContact_AutoSetBindUid(pIM, pTmpCnt);
			insert_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);
			set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
			insert_List(&pCntModel->pBlkGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);

			IAContactModel_Notify(pCntModel, eAIM_GROUP_ADD, pCntModel->pBlkGrp, pTmpCnt);
		}

		//修订时间戳，并将black数据标记为dirt.
		pIM->pAcnt->iBlackStamp = pEvnt->timestamp;
		pCntModel->uiDirtFlag |= 0x04;

		cntList.userID = pEvnt->blackId;			//订阅状态
		cntList.userIDLen = pEvnt->blackIdLen;
		IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, &cntList, 1);
		//通知列表更新

		DPRINT("IAContactModel_OnAddBlack.............black  added.\n");
	}
	else
	{
		DPRINT("IAContactModel_OnAddBlack.............add black failed.\n");
	}	
	
	rspAddBlack.iRetCode = pEvnt->retCode;
	rspAddBlack.szBlackId = (AMChar *)AMMalloc(pEvnt->blackIdLen + 1);
	AMMemcpy(rspAddBlack.szBlackId, pEvnt->blackId, pEvnt->blackIdLen);
	rspAddBlack.szBlackId[pEvnt->blackIdLen] = 0;
	AIMContactModel_Callback(pIM->pCntModel, OnRspAddBlack, &rspAddBlack);
	AMFree(rspAddBlack.szBlackId);

	return eIMnetOK;
}

IMnetRetCode	IAContactModel_OnDelBlack(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventDeleteBlack	*pEvent = (ImEventDeleteBlack*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	IAContact	*pTmpCnt = 0, *pCntFind = 0;
	AIM_RSP_DEL_BLACK rspDelBlack;
	AIM_RSP_ADD_CONTACT rspAddContact;
	AMBool bIsFriend = AMFALSE;
	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm && 0 != pIm->pAcnt);
	pCntModel = pIm->pCntModel;

	pTmpCnt	= IAContact_Create();
	IAContact_SetCntID(pTmpCnt, pEvent->blackId, pEvent->blackIdLen);

	pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(AMNULL == pCntFind)
	{
		bIsFriend = AMFALSE;
		pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	}
	else
	{
		bIsFriend = AMTRUE;
	}

	IAContact_Destroy(pTmpCnt);

	if(0 == pEvent->retCode)
	{
		if(pCntFind)
		{
			int iBlackCount = pCntModel->pBlkGrp->lChildCnt.size;
			pCntFind->uiFlag &= ~0x01;	//清除黑名单标记
			set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
			delete_List(&pCntModel->pBlkGrp->lChildCnt, pCntFind, sizeof(IAContact));
			set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpPinyin);
			
			//通知列表更新
			if(iBlackCount > pCntModel->pBlkGrp->lChildCnt.size)
			{
				IAContactModel_Notify(pIm->pCntModel, eAIM_GROUP_REMOVE, pCntModel->pBlkGrp, pCntFind);
			
				pCntModel->uiDirtFlag |= 0x04;//标记blackList 为dirty
			}

			DPRINT("IAContactModel_OnDelBlack...................black removed.\n");
		}
		else
		{
			DPRINT("IAContactModel_OnDelBlack...............no such black .\n");
		}
	}
	else
	{
		DPRINT("IAContactModel_OnDelBlack...................faile .\n");
	}

	//修正时间戳
	pIm->pAcnt->iBlackStamp = pEvent->timestamp;

	if(bIsFriend)
	{
		_AIMContact_showFriend(pCntModel, pCntFind);

		AMMemset(&rspAddContact, 0, sizeof(rspAddContact));
		rspAddContact.eRetCode = pEvent->retCode==0 ? 0 : -1;
		rspAddContact.eInfo = pEvent->retCode?eADDCONTACT_INFO_OTHERERROR:0;
		rspAddContact.szContactId = pCntFind->szID;
		AIMContactModel_Callback(pIm->pCntModel, OnRspAddContact, &rspAddContact);
	}
	else
	{
		AMMemset(&rspDelBlack, 0, sizeof(rspDelBlack));
		rspDelBlack.szBlackId = pEvent->blackId;
		AIMContactModel_Callback(pIm->pCntModel, OnRspDelBlack, &rspDelBlack);
	}

	DPRINT("IAContactModel_OnDelBlack...................OK.\n");
	return eIMnetOK; 
}

IMnetRetCode	IAContactModel_OnDelContact(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventDeleteContact	*pEvent = (ImEventDeleteContact*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	ContactList *pCntList = 0;
	IAContact	*pCnt = 0, *pCntFind = 0, *pCntOther = 0;
	IAGroup		*pGrp = 0;
	AMBool	bTmp = AMFALSE, bBlack = AMFALSE;

	AIM_RSP_DEL_CONTACT rspDelContact;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm && 0 != pIm->pAcnt);

	pCntModel = pIm->pCntModel;

	pCntList = pEvent->contactList;

	pCnt = IAContact_Create();

	AMMemset(&rspDelContact, 0, sizeof(rspDelContact));
	rspDelContact.iRetCode = pEvent->retCode;

	AMAssert(!pEvent->retCode);
	while (pCntList)
	{
		IAContact_SetCntID(pCnt, pCntList->userID, pCntList->userIDLen);
		pCntFind = find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
		if(0 != pCntFind)
		{
			//从组中删除
			IAIMContact_IsBlack(pCntFind, &bBlack);
			if(!bBlack)
			{
				AMAssert(0 != pCntFind->pParentGrp);
				delete_List(&pCntFind->pParentGrp->lChildCnt, pCntFind, sizeof(IAContact));

				pCntFind->pParentGrp->iUnreadMsgCnt -= pCntFind->iUnreadCnt;
				AMAssert(0 <= pCntFind->pParentGrp->iUnreadMsgCnt);
			}

			//换属性组中的引用
			if(0 != pCntFind->uiFlag)
			{
				pCntOther = IAContact_Duplicate(pCntFind);
				insert_OHTable(&pCntModel->ohtOthers, pCntOther, sizeof(IAContact), DYNAMIC);

				if(bBlack)
				{
					set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
					delete_List(&pCntModel->pBlkGrp->lChildCnt, pCntFind, sizeof(IAContact));
					set_compare(List, &pCntModel->pBlkGrp->lChildCnt, IAContact_CmpPinyin);
					insert_List(&pCntModel->pBlkGrp->lChildCnt, pCntOther, sizeof(IAContact), DYNAMIC);
					
					IMnetDeleteBlack(pIm->pNetModel, pCntFind->szID);
				}
				else
				{
					IAContactModel_Notify(pIm->pCntModel, eAIM_GROUP_REMOVE, pCntFind->pParentGrp, pCntFind);
				}

				IAIMContact_IsRecent(pCntFind, &bTmp);
				if(AMTRUE == bTmp)
				{
					delete_List(&pCntModel->pRecentGrp->lChildCnt, pCntFind, sizeof(IAContact));
					push_front_List(&pCntModel->pRecentGrp->lChildCnt, pCntOther, sizeof(IAContact), DYNAMIC);
					pCntModel->uiDirtFlag |= 0x40;			
				}

				if(AMTRUE == IAContact_IsRevBlack(pCntOther))
				{
					delete_OHTable(&pCntModel->ohtRevBlk, pCntFind, sizeof(IAContact));
					insert_OHTable(&pCntModel->ohtRevBlk, pCntOther, sizeof(IAContact), DYNAMIC);
				}				
			}
			else
			{
				IAContactModel_Notify(pIm->pCntModel, eAIM_GROUP_REMOVE, pCntFind->pParentGrp, pCntFind);
			}

			pCntFind->pParentGrp = AMNULL;

			delete_OHTable(&pCntModel->ohtFriends, pCntFind, sizeof(IAContact));

			//标记联系人数据为dirt
			pIm->pCntModel->uiDirtFlag |= 0x02;

			DPRINT("IAContactModel_OnDelContact............contact %s removed!\n", pCnt->szID);
		}
		else
		{
			DPRINT("IAContactModel_OnDelContact............no contact %s to remove!\n", pCnt->szID);
		}
		
		rspDelContact.szContactId = pCnt->szID;

		AMAssert(!pCntList->pNext);
		pCntList = pCntList->pNext;
	}
	
	if(!bBlack)
		AIMContactModel_Callback(pIm->pCntModel, OnRspDelContact, &rspDelContact);

	IAContact_Destroy(pCnt);

	if(pEvent->contactList)
	{
		pIm->pAcntModel->uiDirtFlag |= 0x01;
		pIm->pAcnt->iContactStamp = pEvent->timestamp;
	}

	DPRINT("IAContactModel_OnDelContact............OK\n");
	return eIMnetOK; 
}

#define			USR_EXT_SIGNATURE	"signature"
#define			USR_EXT_PORTRAIT	"portrait"
#define			USR_EXT_CI_HEAD		"<CI>"
#define			USR_EXT_SIG_HEAD	"<Sig>"
#define			USR_EXT_SIG_TAIL	"</Sig>"
IMnetRetCode	IAContactModel_OnUpdateUsrExtInfo(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventNtfUpdateUsrExtInfo	*pEvent = (ImEventNtfUpdateUsrExtInfo*)pEventContent;
	IAIM *pIM = AMNULL;
	IAContact	*pCntTmp = AMNULL, *pCntFind = AMNULL;
	AIM_SIGNATURE signature;
	AIM_NTF_UPDATE_CONTACT ntfUpdateContact;
	AIM_RSP_GET_SIGNATURE rspGetSignature;
	AMInt32	iCount = 0;
	
	AMAssert(AMNULL != hIMnetHandle);

	pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	AMAssert(AMNULL != pIM);

	AMMemset(&ntfUpdateContact, 0, sizeof(ntfUpdateContact));
	AMMemset(&rspGetSignature, 0, sizeof(rspGetSignature));

	pCntTmp	= IAContact_Create();
	iCount = 0;

	if(!pEvent->iFlag)//RspGetSignature
	{
		rspGetSignature.pszContactIds = (AMChar**)AMMalloc(sizeof(AMChar *) * pEvent->iCount);
		AMMemset(rspGetSignature.pszContactIds, 0, sizeof(sizeof(AMChar *) * pEvent->iCount));
		rspGetSignature.pszValues = (AMChar**)AMMalloc(sizeof(AMChar *) * pEvent->iCount);
		AMMemset(rspGetSignature.pszValues, 0, sizeof(sizeof(AMChar *) * pEvent->iCount));
	}
	else//ntf
	{
		ntfUpdateContact.phContacts = (AMHandle*)AMMalloc(sizeof(AMHandle) * pEvent->iCount);
		AMMemset(ntfUpdateContact.phContacts, 0, sizeof(AMHandle) * pEvent->iCount);
	}

	while(pEvent)
	{
		IAContact_SetCntID(pCntTmp, pEvent->szContactID, pEvent->iContactIDLen);
		if(!pEvent->iFlag && !AMStrcmp(pIM->pAcnt->szID, pCntTmp->szID))//得到的是当前帐号的签名，应该只有一个，break就行了
		{
			if(0 == AMMemcmp(pEvent->szType, USR_EXT_SIGNATURE, sizeof(USR_EXT_SIGNATURE)-1))
			{
				SigXML2SigStruct(pEvent->szValue, &signature);

				IAccount_SetSignature(pIM->pAcnt, signature.szSignature[signature.iCI],  AMStrlen(signature.szSignature[signature.iCI]));
				IAccount_SetSigXML(pIM->pAcnt, pEvent->szValue, pEvent->iValueLen);
				IAccountModel_UpdateSigXML(pIM->pAcntModel, pIM->pAcnt->szID, pEvent->szValue, pEvent->iValueLen);		
				
				rspGetSignature.pszContactIds[rspGetSignature.iCount] = pIM->pAcnt->szID;
				rspGetSignature.pszValues[rspGetSignature.iCount++] = pIM->pAcnt->szSignature;
			}
			else if( 0 == AMMemcmp(pEvent->szType, USR_EXT_PORTRAIT, sizeof(USR_EXT_PORTRAIT)-1))
			{
				DPRINT("IAContactModel_OnUpdateUsrExtInfo.....................%s\n", pEvent->szType);
			}

			pEvent = pEvent->next;
			continue;
		}

		pCntFind = IAContactModel_FindContact(pIM->pCntModel, pCntTmp);	//如果没有这个人，则直接退出
		if(AMNULL == pCntFind)
		{
			pEvent = pEvent->next;
			continue;
		}

		if(0 == AMMemcmp(pEvent->szType, USR_EXT_SIGNATURE, sizeof(USR_EXT_SIGNATURE)-1))
		{
			//更新签名数据库
			SigXML2SigStruct(pEvent->szValue, &signature);

			if(0 == IAContact_SetSignature(pCntFind, signature.szSignature[signature.iCI]
											, AMStrlen(signature.szSignature[signature.iCI])))
			{
				if(!pEvent->iFlag)
				{
					rspGetSignature.pszContactIds[rspGetSignature.iCount] = pCntFind->szID;
					rspGetSignature.pszValues[rspGetSignature.iCount++] = pCntFind->szSignature;
				}
				else
				{
					ntfUpdateContact.eType = eAIM_CONTACT_SIGNATURE;
					ntfUpdateContact.phContacts[ntfUpdateContact.iCount++] = pCntFind;
				}
			}
		}
		else if( 0 == AMMemcmp(pEvent->szType, USR_EXT_PORTRAIT, sizeof(USR_EXT_PORTRAIT)-1))
		{
			ntfUpdateContact.eType = eAIM_CONTACT_PORTRAIT;
			ntfUpdateContact.phContacts[ntfUpdateContact.iCount++] = pCntFind;
			DPRINT("IAContactModel_OnUpdateUsrExtInfo.....................%s\n", pEvent->szType);
		}
		else
		{
			DPRINT("IAContactModel_OnUpdateUsrExtInfo.....................%s\n", pEvent->szType);
		}
		pEvent = pEvent->next;
	}
	IAContact_Destroy(pCntTmp);

	DPRINT("IAContactModel_OnUpdateUsrExtInfo..............................OK!\n");

	pEvent = (ImEventNtfUpdateUsrExtInfo*)pEventContent;

	if(!pEvent->iFlag)
	{
		AIMContactModel_Callback(pIM->pCntModel, OnRspGetSignature, &rspGetSignature);
		AMFree(rspGetSignature.pszContactIds);
		AMFree(rspGetSignature.pszValues);
	}
	else
	{
		AIMContactModel_Callback(pIM->pCntModel, OnNtfUpdateContact, &ntfUpdateContact);
		AMFree(ntfUpdateContact.phContacts);
	}

	return eIMnetOK;
}

IMnetRetCode	IAContactModel_OnStatus(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventNtfStatus	*pEvent = (ImEventNtfStatus*)pEventContent;
	IAIM	*pIm = 0;
	IAContactModel	*pCntModel = 0;
	StatusList *pStatusList = 0;
	IAContact	*pCnt = 0, *pCntFind = 0;
	AIM_NTF_UPDATE_CONTACT ntfUpdateContact;

	AMAssert(0 != hIMnetHandle);
	pIm = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIm);
	pCntModel = pIm->pCntModel;

	if(pEvent->statusCount == 0)
		return eIMnetOK;

	AMMemset(&ntfUpdateContact, 0, sizeof(ntfUpdateContact));

	ntfUpdateContact.phContacts = (AMHandle*) AMMalloc (sizeof(AMHandle)*(pEvent->statusCount));
	AMMemset(ntfUpdateContact.phContacts, 0, sizeof(AMHandle)*pEvent->statusCount);
	ntfUpdateContact.eType = eAIM_CONTACT_PRESENCE;

	pStatusList = pEvent->statusList;
	pCnt = IAContact_Create();
	while(0 != pStatusList)
	{
		IAContact_SetCntID(pCnt, pStatusList->userID, pStatusList->userIDLen);
		pCntFind = (IAContact *)find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact));
		if(0 == pCntFind)
			pCntFind = (IAContact*)find_OHTable(&pCntModel->ohtOthers, pCnt, sizeof(IAContact));;

		if(0 != pCntFind)
		{
			//修改状态，通知哪个实体组的哪个人状态改变。
			pCntFind->ePresence = convert2Status(pStatusList->basicStatus, pStatusList->predefStatus);
			ntfUpdateContact.phContacts[ntfUpdateContact.iCount++] = pCntFind;
			DPRINT("IAContactModel_OnStatus..........%s, status: %d\n", pCntFind->szID, pCntFind->ePresence);
		}
		else
		{
			DPRINT("IAContactModel_OnStatus..........cnt %s not find in this IM\n", pCnt->szID);
		}

		pStatusList = pStatusList->pNext;
	}

	IAContact_Destroy(pCnt);

	if(ntfUpdateContact.iCount>0)//通知状态变化~
		AIMContactModel_Callback(pCntModel, OnNtfUpdateContact, &ntfUpdateContact);

	AMFree(ntfUpdateContact.phContacts);

	return eIMnetOK;
}

AMVoid				IAContactModel_DecreaseReadCnt(IAContactModel *pCntModel, const AMChar *szCntId, AMInt32 iNum)
{
	IAContact *pCntFind = AMNULL;
	AMAssert(0 != pCntModel && 0 != szCntId);
	IAIMContactModel_GetContactByID(pCntModel, szCntId, &pCntFind);
	if(AMNULL != pCntFind)
	{
		pCntFind->iUnreadCnt -= iNum;
		if(pCntFind->iUnreadCnt < 0)
			pCntFind->iUnreadCnt = 0;
		if(AMNULL != pCntFind->pParentGrp)
		{
			pCntFind->pParentGrp->iUnreadMsgCnt -= iNum;
			if(pCntFind->pParentGrp->iUnreadMsgCnt < 0)
				pCntFind->pParentGrp->iUnreadMsgCnt = 0;
		}
		else
		{
			//更新属性组消息未读数目
		}
	}
}

AMVoid	IAContactModel_BuildGroupTree(IAContactModel *pCntModel)
{
	IAGroup *pGrp = 0, *pFindGrp = 0, *pTmpGrp = 0;
	OHTableIter *pItrGroup = 0;
	AIM_NTF_DATA_READY ntfDataReady;
	AMAssert(0 != pCntModel);

	if(pCntModel->ohtGroups.num_elem > 0)
	{
		pItrGroup = create(OHTableIter, &pCntModel->ohtGroups);
		head(OHTableIter, pItrGroup);

		pTmpGrp = IAGroup_CreateProc(AMTRUE);

		do 
		{
			pGrp = (IAGroup *)retrieve(OHTableIter, pItrGroup);		
			if(pGrp->iParentGid < 0)
			{
				//if(1 != pGrp->iGroupID)//E客服“我的团队”，要隐藏...
				{
					insert_List(&pCntModel->lTopGrp, pGrp, sizeof(IAGroup), DYNAMIC);//需要 IAGroup_CmpPinyin.		
				}				
				continue;
			}

			pTmpGrp->iGroupID = pGrp->iParentGid;
			pFindGrp = find_OHTable(&pCntModel->ohtGroups, pTmpGrp, sizeof(IAGroup));
			if(0 != pFindGrp)
			{
				pGrp->pParentGrp = pFindGrp;
				insert_List(&pFindGrp->lChildGrp, pGrp, sizeof(IAGroup), DYNAMIC);
				insert_List(&pCntModel->lTopGrp, pGrp, sizeof(IAGroup), DYNAMIC);//将每个组都加到lTopGrp中！
			}
			else
			{
				DPRINT("IAContactModel_BuildGroupTree.........组"I64FORMAT"的父组"I64FORMAT"不存在?\n", pGrp->iGroupID, pGrp->iParentGid);
				insert_List(&pCntModel->lTopGrp, pGrp, sizeof(IAGroup), DYNAMIC);//需要 IAGroup_CmpPinyin.
			}

		} while (!next(OHTableIter, pItrGroup));

		IAGroup_Destroy(pTmpGrp);

		destroy(OHTableIter, pItrGroup);

	}
										//////////////////////////////////////////////顺序需要调整
	push_back_List(&pCntModel->lTopGrp, pCntModel->pBindGrp, sizeof(IAGroup), DYNAMIC);
	push_back_List(&pCntModel->lTopGrp, pCntModel->pStrangerGrp, sizeof(IAGroup), DYNAMIC);
	push_back_List(&pCntModel->lTopGrp, pCntModel->pBlkGrp, sizeof(IAGroup), DYNAMIC);
	
	IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_GROUPRECVED);
	ntfDataReady.eInfo = eDATA_GROUP_READY;
	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	DPRINT("IAContactModel_BuildGroupTree.............OK\n");
}

AMVoid IAContactModel_BuildBindContactList(IAContactModel *pCntModel)
{
	IAContact *pCnt = 0;
	OHTableIter *pItrCnt = 0;
	AIM_NTF_DATA_READY ntfDataReady;
	AMAssert(0 != pCntModel);

	DPRINT("IAContactModel_BuildBindContactList....................Entering!\n");

	if(pCntModel->ohtFriends.num_elem > 0)
	{
		pItrCnt = create(OHTableIter, &pCntModel->ohtFriends);
		head(OHTableIter, pItrCnt);

		if(pCntModel->pBindGrp == NULL)
			pCntModel->pBindGrp = IAGroup_CreateProc(AMTRUE);
		pCntModel->pBindGrp->iGroupID = BIND_ACCOUNT_GRP_ID;
		do 
		{
			pCnt = (IAContact*)retrieve(OHTableIter, pItrCnt);
			if(pCnt->iParentGid == BIND_ACCOUNT_GRP_ID)
			{
				pCnt->pParentGrp = pCntModel->pBindGrp;
				insert(List, &pCntModel->pBindGrp->lChildCnt, pCnt, DYNAMIC);
			}
		} while (!next(OHTableIter, pItrCnt));

		destroy(OHTableIter, pItrCnt);
	}

	if(pCntModel->pReference->pAcnt->ePresence == eAIM_PRESENCE_OFFLINE || (pCntModel->uiDirtFlag & 0x0C) == 0x00)
	{
		IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_ALLREADY);

		ntfDataReady.eInfo = eDATA_BINDID_ALLREADY;
	}
	else
	{
		ntfDataReady.eInfo = eDATA_FRIEND_READY;
		IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_CONTACTRECVED);
	}

	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	if(pCntModel->pReference->pAcnt->szBindID)
		IMnetPutBindInfo(pCntModel->pReference->pNetModel, pCntModel->pReference->pAcnt->szBindID, AMStrlen(pCntModel->pReference->pAcnt->szBindID));
	IMnetPostLogin(pCntModel->pReference->pNetModel, getBasicStatus(pCntModel->pReference->pAcnt->ePresence), getPredefStatus(pCntModel->pReference->pAcnt->ePresence));
	DPRINT("IAContactModel_BuildBindContactList............OK\n");
}

AMVoid IAContactModel_SetAllContact(IAContactModel *pCntModel, AMBool bBindID)
{
	IAContact *pCnt = 0;
	IAGroup *pGrp = 0, *pGrpFind = 0;
	OHTableIter *pItrCnt = 0;
	AIM_NTF_DATA_READY ntfDataReady;
	AMBool bBlack = AMFALSE;
	AMAssert(0 != pCntModel);

	DPRINT("IAContactModel_SetAllContact....................Entering!\n");

	if(pCntModel->ohtFriends.num_elem > 0)
	{
		pItrCnt = create(OHTableIter, &pCntModel->ohtFriends);
		head(OHTableIter, pItrCnt);

		pGrp = IAGroup_CreateProc(AMTRUE);
		do 
		{
			pCnt = (IAContact*)retrieve(OHTableIter, pItrCnt);
			IAIMContact_IsBlack(pCnt, &bBlack);
			if(bBlack)
				continue;

			switch (pCnt->iParentGid)
			{
			case BLACK_GRP_ID:
				pCnt->pParentGrp = pCntModel->pBlkGrp;
				insert(List, &pCnt->pParentGrp->lChildCnt, pCnt, DYNAMIC);
				break;
			case RECENT_GRP_ID:
				pCnt->pParentGrp = pCntModel->pRecentGrp;
				insert(List, &pCnt->pParentGrp->lChildCnt, pCnt, DYNAMIC);
				break;
			case BIND_ACCOUNT_GRP_ID:
				pCnt->pParentGrp = pCntModel->pBindGrp;
				insert(List, &pCnt->pParentGrp->lChildCnt, pCnt, DYNAMIC);
				break;
			case DEFAULT_GRP_ID:
			case STRANG_GRP_ID:
			default:
				pGrp->iGroupID = pCnt->iParentGid;
				pGrpFind = find(OHTable,&pCntModel->ohtGroups, pGrp);
				if(0 != pGrpFind)
				{
					pCnt->pParentGrp = pGrpFind;
					insert(List, &pGrpFind->lChildCnt, pCnt, DYNAMIC);
				}
				else
				{
					pCntModel->pReference->pAcnt->iGroupStamp = 0;
					DPRINT("IAContactModel_SetAllContact...........联系人%s的组"I64FORMAT"不存在，放到陌生人？\n", pCnt->szID, pCnt->iParentGid);
					insert(List, &pCntModel->pStrangerGrp->lChildCnt, pCnt, DYNAMIC);
				}
				break;
			}


			//pGrp->iGroupID = pCnt->iParentGid;
			//pGrpFind = find(OHTable,&pCntModel->ohtGroups, pGrp);
			//if(0 != pGrpFind)
			//{
			//	pCnt->pParentGrp = pGrpFind;
			//	insert(List, &pGrpFind->lChildCnt, pCnt, DYNAMIC);
			//}
			//else
			//{
			//	pCntModel->pReference->pAcnt->iGroupStamp = 0;
			//	DPRINT("IAContactModel_SetAllContact...........联系人%s的组"I64FORMAT"不存在，放到陌生人？\n", pCnt->szID, pCnt->iParentGid);
			//	insert(List, &pCntModel->pStrangerGrp->lChildCnt, pCnt, DYNAMIC);
			//}
		} while (!next(OHTableIter, pItrCnt));
		IAGroup_Destroy(pGrp);

		destroy(OHTableIter, pItrCnt);
	}


	IMnetPostLogin(pCntModel->pReference->pNetModel, getBasicStatus(pCntModel->pReference->pAcnt->ePresence), getPredefStatus(pCntModel->pReference->pAcnt->ePresence));

	if(pCntModel->pReference->pAcnt->ePresence == eAIM_PRESENCE_OFFLINE || (pCntModel->uiDirtFlag & 0x0C) == 0x00)
	{
		IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_ALLREADY);

		ntfDataReady.eInfo = bBindID? eDATA_BINDID_ALLREADY : eDATA_ALLREADY;
	}
	else
	{
		ntfDataReady.eInfo = eDATA_FRIEND_READY;
		IAIM_TransStatus(pCntModel->pReference, eIM_STATUS_CONTACTRECVED);
	}

	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	DPRINT("IAContactModel_SetAllContact............OK\n");
}


AMInt32		IAContactModel_StoreGrp(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite = 0;
	AMChar	*szErrMsg = 0;
	OHTableIter	*pItr = 0;
	IAGroup		*pGrp = 0;
	AMChar	*	szSql = AMNULL;

	iRcSqlite = sqlite3_exec(pDB, "DELETE FROM _grouplist;", 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreGrp:.......can not \"DELETE FROM _grouplist;\":%s\n" ,szErrMsg);
		sqlite3_free(szErrMsg);
	}

	iRcSqlite = sqlite3_exec(pDB, "CREATE TABLE IF NOT EXISTS _grouplist(\
								  _rid		INTEGER PRIMARY KEY AUTOINCREMENT,\
								  _gid		INTEGER UNIQUE,\
								  _pgid		INTEGER,\
								  _name		VARCHAR(32));",
								  0, 0, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreGrp:.......can not \"CREATE TABLE _grouplist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->ohtGroups.num_elem > 0)
	{
		pItr = create(OHTableIter, &pCntModel->ohtGroups);
		head(OHTableIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreGrp:.......can not \"BEGIN TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			destroy(OHTableIter, pItr);
			return -1;
		}

		do 
		{
			pGrp = (IAGroup *)retrieve(OHTableIter, pItr);
			szSql =sqlite3_mprintf(SQL_INSERT_GRP, pGrp->iGroupID, pGrp->iParentGid, pGrp->szName);

			if(AMNULL != szSql)
			{
				iRcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
				sqlite3_free(szSql);

				if(SQLITE_OK != iRcSqlite)
				{
					DPRINT("IAContactModel_StoreGrp:.......can not INSERT %s\n", szErrMsg);
					sqlite3_free(szErrMsg);
					destroy(OHTableIter, pItr);
					return -1;
				}
			}
			else
			{
				destroy(OHTableIter, pItr);
				return -1;
			}
		} while (!next(OHTableIter, pItr));
		destroy(OHTableIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreGrp:.......can not \"COMMIT TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			return -1;
		}
	}
	DPRINT("IAContactModel_StoreGrp...................OK\n");
	return 0;
}

static AMInt32 IAContactModel_OnSelGrp(void* pvCntModel, int iCnt, char **pszValue, char**pszName)
{
	IAContactModel	*pCntModel		= (IAContactModel *)pvCntModel;
	IAGroup			*pTmpGrp		= 0;

	AMAssert(0 !=  pCntModel);

	pTmpGrp = IAGroup_Create();

	IAGroup_SetName(pTmpGrp, pszValue[3], AMStrlen(pszValue[3]));
	//转化到拼音
	IAGroup_SetPinyin(pTmpGrp, pszValue[3], AMStrlen(pszValue[3]));
	pTmpGrp->_iRid = AMAtoi(pszValue[0]);
	pTmpGrp->iGroupID = AMAtoi64(pszValue[1]);
	pTmpGrp->iParentGid = AMAtoi64(pszValue[2]);

	insert_OHTable(&pCntModel->ohtGroups, pTmpGrp, sizeof(IAGroup), DYNAMIC);

	return 0;
}


AMInt32		IAContactModel_RestoreGrp(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite	= 0;
	AMChar	*szErrMsg	= 0;

	clear(List, &pCntModel->lTopGrp); 

	clear(OHTable, &pCntModel->ohtGroups);

	iRcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _grouplist;",
		IAContactModel_OnSelGrp, pCntModel, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_RestoreGrp:.......Can't SELECT * FROM _grouplist;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}
	DPRINT("IAContactModel_RestoreGrp................OK\n");
	return 0;
}

AMInt32		IAContactModel_StoreFriends(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite = 0;
	AMChar	*szErrMsg = 0;
	OHTableIter	*pItr = 0;
	IAContact	*pCnt = 0;
	AMChar	*szSql = AMNULL;

	iRcSqlite = sqlite3_exec(pDB, "DELETE FROM _contactlist;", 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreFriends:.......can not \"DELETE FROM _contactlist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
	}

	iRcSqlite = sqlite3_exec(pDB, "CREATE TABLE IF NOT EXISTS _contactlist(\
								  _rid		INTEGER PRIMARY KEY AUTOINCREMENT,\
								  _gid			INTEGER,\
								  _cntid		VARCHAR(64),\
								  _nickname		VARCHAR(64),\
								  _pinyin		VARCHAR(64));",
								  0,0,&szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreFriends:.......can not \"CREATE TABLE _contactlist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->ohtFriends.num_elem > 0)
	{
		pItr = create(OHTableIter, &pCntModel->ohtFriends);
		head(OHTableIter, pItr);
		
		iRcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreFriends:.......can not \"BEGIN TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			destroy(OHTableIter, pItr);
			return -1;
		}

		do 
		{
			pCnt = (IAContact *)retrieve(OHTableIter, pItr);
			if(AMNULL != pCnt->szBindUID && 0 != AMStrcmp(pCnt->szBindUID, pCntModel->pReference->pAcnt->szID))
				continue;
			szSql = sqlite3_mprintf(SQL_INSERT_CNT, pCnt->iParentGid, pCnt->szID, pCnt->szName, pCnt->szPinyin);
			if(AMNULL != szSql)
			{
				iRcSqlite = sqlite3_exec(pDB, szSql,0,0,&szErrMsg);
				sqlite3_free(szSql);
				if(SQLITE_OK != iRcSqlite)
				{
					DPRINT("IAContactModel_StoreFriends:.......can not INSERT, %s\n" ,szErrMsg);
					sqlite3_free(szErrMsg);
					destroy(OHTableIter, pItr);
					return -1;
				}
			}
			else
			{
				destroy(OHTableIter, pItr);
				return -1;
			}
		} while (!next(OHTableIter, pItr));	
		destroy(OHTableIter, pItr);	

		iRcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreFriends:.......can not \"COMMIT TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			return -1;
		}

	}
	DPRINT("IAContactModel_StoreFriends....................OK\n");

	return 0;
}

static AMInt32 IAContactModel_OnSelFriends(void* pvCntor, int iCnt, char **pszValue, char**pszName)
{
	IAContactModel	*pCntor		= (IAContactModel *)pvCntor;
	IAContact		*pTmpCnt	= 0;
	AMAssert(0 !=  pCntor);

	pTmpCnt = IAContact_Create();
	
	pTmpCnt->_iRid = AMAtoi(pszValue[0]);
	pTmpCnt->iParentGid = AMAtoi64(pszValue[1]);

	IAContact_SetCntID(pTmpCnt, pszValue[2], AMStrlen(pszValue[2]));
	IAContact_SetNickName(pTmpCnt, pszValue[3], AMStrlen(pszValue[3]));
	IAContact_SetPinyin(pTmpCnt, pszValue[4], AMStrlen(pszValue[4]));
	IAContact_AutoSetBindUid(pCntor->pReference, pTmpCnt);

	insert_OHTable(&pCntor->ohtFriends, pTmpCnt, sizeof(IAContact), DYNAMIC);

	return 0;
}

AMInt32		IAContactModel_RestoreFriends(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite	= 0;
	AMChar	*szErrMsg	= 0;

	clear(OHTable, &pCntModel->ohtFriends);

	DPRINT("IAContactModel_RestoreFriends..................Before Select!\n");

	iRcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _contactlist;",
							IAContactModel_OnSelFriends, pCntModel, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_RestoreFriends:.......Can't SELECT * FROM _contactlist;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}
	DPRINT("IAContactModel_RestoreFriends.................OK\n");

	IAContactModel_RestoreStranger(pCntModel, pDB);
	IAContactModel_RestoreRecent(pCntModel, pDB);	

	return 0;
}
#define		SQL_CREATE_TABLE_BLACK	"CREATE TABLE IF NOT EXISTS _blacklist(_rid INTEGER PRIMARY KEY AUTOINCREMENT, _cntid	VARCHAR(64));"
AMInt32		IAContactModel_StoreBlack(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite = 0;
	AMChar	*szErrMsg = 0;
	ListIter	*pItr = 0;
	IAContact	*pCnt = 0;
	AMChar	*szSql = AMNULL;

	iRcSqlite = sqlite3_exec(pDB, "DELETE FROM _blacklist;", 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreBlack:.......can not \"DELETE FROM _blacklist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
	}

	iRcSqlite = sqlite3_exec(pDB, SQL_CREATE_TABLE_BLACK, 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreBlack:.......can not \"CREATE TABLE _blacklist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->pBlkGrp->lChildCnt.size > 0)
	{
		pItr = create(ListIter, &pCntModel->pBlkGrp->lChildCnt);
		head(ListIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreBlack:.......can not \"BEGIN TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			destroy(ListIter, pItr);
			return -1;
		}

		do 
		{
			pCnt = (IAContact *)retrieve(ListIter, pItr);
			if(AMNULL != pCnt->szBindUID && 0 != AMStrcmp(pCnt->szBindUID, pCntModel->pReference->pAcnt->szID))
				continue;
			szSql = sqlite3_mprintf("INSERT INTO _blacklist VALUES(NULL, '%q');",pCnt->szID);
			if(AMNULL != szSql)
			{
				iRcSqlite = sqlite3_exec(pDB, szSql,0,0,&szErrMsg);
				sqlite3_free(szSql);			
				if(SQLITE_OK != iRcSqlite)
				{
					DPRINT("IAContactModel_StoreBlack:.......can not INSERT for %s\n" ,szErrMsg);
					sqlite3_free(szErrMsg);
					destroy(ListIter, pItr);
					return -1;
				}
			}
			else
			{
				destroy(ListIter, pItr);
				return -1;
			}
		} while (!next(ListIter, pItr));
		destroy(ListIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreBlack:.......can not \"COMMIT TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			return -1;
		}
	}
	DPRINT("IAContactModel_StoreBlack.......................OK\n");
	return 0;
}

static AMInt32 IAContactModel_OnSelBlack(void* pvCntor, int iCnt, char **pszValue, char**pszName)
{
	IAContactModel	*pCntModel		= (IAContactModel *)pvCntor;
	IAContact		*pTmpCnt = 0, *pCntFind = 0;
	AMBool		bIsFriend = AMFALSE, bIsStrange = AMFALSE;
	AMAssert(0 !=  pCntModel);

	pTmpCnt = IAContact_Create();

	IAContact_SetCntID(pTmpCnt, pszValue[1], AMStrlen(pszValue[1]));
	
	pCntFind = find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
	{
		bIsFriend = AMFALSE;
		pCntFind = find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	}
	else
	{
		bIsFriend = AMTRUE;
	}

	if(0 != pCntFind)
	{
		IAContact_Destroy(pTmpCnt);

		IAContact_MarkBlack(pCntFind);
		insert_List(&pCntModel->pBlkGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);
	}
	else
	{
		insert_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);

		IAContact_MarkBlack(pTmpCnt);
		IAContact_SetNickName(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_SetPinyin(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_AutoSetBindUid(pCntModel->pReference, pTmpCnt);
		insert_List(&pCntModel->pBlkGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);
	}

	return 0;
}

AMInt32		IAContactModel_RestoreBlack(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite	= 0;
	AMChar	*szErrMsg	= 0;
	ContactList	*pBlackList = AMNULL;
	ListIter *pIter = AMNULL;
	IAContact *pTmpCnt = AMNULL, *pCntFind = AMNULL;
	AIM_NTF_DATA_READY ntfDataReay;

	clear(List, &pCntModel->pBlkGrp->lChildCnt);

	DPRINT("IAContactModel_RestoreBlack.......... when ohtFriends is %d\n", pCntModel->ohtFriends.num_elem);

	iRcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _blacklist;",
							IAContactModel_OnSelBlack, pCntModel, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_RestoreBlack:.......Can't SELECT * FROM _blacklist;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->pBlkGrp->lChildCnt.size)
	{
		pBlackList = AMMalloc(sizeof(ContactList) * pCntModel->pBlkGrp->lChildCnt.size);
		if(pBlackList)
		{
			int i = 0;
			AMMemset(pBlackList, 0, sizeof(ContactList) * pCntModel->pBlkGrp->lChildCnt.size);
			pIter = create(ListIter, &pCntModel->pBlkGrp->lChildCnt);
			head(ListIter, pIter);
			do 
			{
				pTmpCnt = (IAContact*)retrieve(ListIter, pIter);
				pBlackList[i].userID = pTmpCnt->szID;
				pBlackList[i].userIDLen = AMStrlen(pTmpCnt->szID);
				pBlackList[i].pNext = &pBlackList[i+1];
				i++;
				
				pCntFind = (IAContact *)find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
				if(pCntFind && pCntFind->pParentGrp)
				{
					set_compare(List, &pCntFind->pParentGrp->lChildCnt, IAGroup_CmpID);
					delete_List(&pCntFind->pParentGrp->lChildCnt, pCntFind, sizeof(IAContact));
				}

			} while (!next(ListIter, pIter));
			destroy(ListIter, pIter);
			pBlackList[i-1].pNext = AMNULL;

			IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, pBlackList, 1);

			AMFree(pBlackList);
		}
	}

	ntfDataReay.eInfo = eDATA_BLACK_READY;
	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReay);

	DPRINT("IAContactModel_RestoreBlack........................OK\n");

	return 0;
}

AMInt32		IAContactModel_StoreRevBlack(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite = 0;
	AMChar	*szErrMsg = 0;
	OHTableIter	*pItr = 0;
	IAContact	*pCnt = 0;
	AMChar	*szSql = AMNULL;

	iRcSqlite = sqlite3_exec(pDB, "DELETE FROM _revblklist;", 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreRevBlack:.......can not \"DELETE FROM _revblklist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
	}

	iRcSqlite = sqlite3_exec(pDB, "CREATE TABLE IF NOT EXISTS _revblklist(_rid INTEGER PRIMARY KEY AUTOINCREMENT, _cntid	VARCHAR(64));",
		0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreRevBlack:.......can not \"CREATE TABLE _revblklist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->ohtRevBlk.num_elem > 0)
	{
		pItr = create(OHTableIter, &pCntModel->ohtRevBlk);
		head(OHTableIter, pItr);
		do 
		{
			pCnt = (IAContact *)retrieve(OHTableIter, pItr);
			if(AMNULL != pCnt->szBindUID && 0 != AMStrcmp(pCnt->szBindUID, pCntModel->pReference->pAcnt->szID))
				continue;
			szSql = sqlite3_mprintf("INSERT INTO _revblklist VALUES(NULL, '%q');",pCnt->szID);
			if(AMNULL != szSql)
			{
				iRcSqlite = sqlite3_exec(pDB, szSql,0,0,&szErrMsg);
				sqlite3_free(szSql);
				if(SQLITE_OK != iRcSqlite)
				{
					DPRINT("IAContactModel_StoreRevBlack:.......can not INSERT, %s\n", szErrMsg);
					sqlite3_free(szErrMsg);
					destroy(OHTableIter, pItr);
					return -1;
				}
			}
			else
			{
				destroy(OHTableIter, pItr);
				return -1;
			}
		} while (!next(OHTableIter, pItr));
		destroy(OHTableIter, pItr);
	}

	DPRINT("IAContactModel_StoreRevBlack.......................Ok\n");

	return 0;
}

static AMInt32 IAContactModel_OnSelRevBlk(void* pvCntor, int iCnt, char **pszValue, char**pszName)
{
	IAContactModel	*pCntModel		= (IAContactModel *)pvCntor;
	IAContact		*pTmpCnt = 0, *pCntFind = 0;
	AMAssert(0 !=  pCntModel);

	pTmpCnt = IAContact_Create();

	pTmpCnt->_iRid = AMAtoi(pszValue[0]);
	IAContact_SetCntID(pTmpCnt, pszValue[1], AMStrlen(pszValue[1]));

	pCntFind = find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
		pCntFind = find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	
	if(0 != pCntFind)
	{
		IAContact_Destroy(pTmpCnt);

		IAContact_MarkRevBlk(pCntFind);
		insert_OHTable(&pCntModel->ohtRevBlk, pCntFind, sizeof(IAContact), DYNAMIC);
	}
	else
	{		
		IAContact_MarkRevBlk(pTmpCnt);
		IAContact_SetNickName(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_SetPinyin(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_AutoSetBindUid(pCntModel->pReference, pTmpCnt);
		insert_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);
		insert_OHTable(&pCntModel->ohtRevBlk, pTmpCnt, sizeof(IAContact), DYNAMIC);
	}

	return 0;
}

AMInt32		IAContactModel_RestoreRevBlk(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite	= 0;
	AMChar	*szErrMsg	= 0;

	clear(OHTable, &pCntModel->ohtRevBlk);

	DPRINT("IAContactModel_RestoreRevBlk.......... when ohtFriends is %d\n", pCntModel->ohtFriends.num_elem);

	iRcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _revblklist;",
							IAContactModel_OnSelRevBlk, pCntModel, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		AMPrintf("AMImCntModel: ", "Can't SELECT * FROM _revblklist;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	DPRINT("IAContactModel_RestoreRevBlk........................OK\n");

	return 0;
}


AMInt32		IAContactModel_StoreStrangers(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite = 0;
	AMChar	*szErrMsg = 0;
	ListIter	*pItr = 0;
	IAContact	*pCnt = 0;
	AMChar	*szSql = AMNULL;

	iRcSqlite = sqlite3_exec(pDB, "DELETE FROM _strangerlist;", 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreStrangers:", "can not \"DELETE FROM _strangerlist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
	}

	iRcSqlite = sqlite3_exec(pDB, "CREATE TABLE IF NOT EXISTS _strangerlist(_rid INTEGER PRIMARY KEY AUTOINCREMENT, _cntid	VARCHAR(64));",
		0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreStrangers:", "can not \"CREATE TABLE _strangerlist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->pStrangerGrp->lChildCnt.size > 0)
	{
		pItr = create(ListIter, &pCntModel->pStrangerGrp->lChildCnt);
		head(ListIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreStrangers:.......can not \"BEGIN TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			destroy(ListIter, pItr);
			return -1;
		}

		do 
		{
			pCnt = (IAContact *)retrieve(ListIter, pItr);
			if(AMNULL != pCnt->szBindUID && 0 != AMStrcmp(pCnt->szBindUID, pCntModel->pReference->pAcnt->szID))
				continue;
			szSql = sqlite3_mprintf("INSERT INTO _strangerlist VALUES(NULL, '%q');",pCnt->szID);
			if(szSql)
			{
				iRcSqlite = sqlite3_exec(pDB, szSql,0,0,&szErrMsg);
				sqlite3_free(szSql);
				if(SQLITE_OK != iRcSqlite)
				{
					DPRINT("IAContactModel_StoreStrangers:", "can not INSERT, %s\n", szErrMsg);
					sqlite3_free(szErrMsg);
					destroy(ListIter, pItr);
					return -1;
				}
			}
			else
			{
				destroy(ListIter, pItr);
				return -1;
			}			
		} while (!next(ListIter, pItr));
		destroy(ListIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreStrangers:.......can not \"COMMIT TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			return -1;
		}

	}

	DPRINT("IAContactModel_StoreStrangers......................OK\n");
	return 0;
}

static AMInt32 IAContactModel_OnSelStrangers(void* pvCntor, int iCnt, char **pszValue, char**pszName)
{
	IAContactModel	*pCntModel		= (IAContactModel *)pvCntor;
	IAContact		*pTmpCnt = 0, *pCntFind = 0;
	AMAssert(0 !=  pCntModel);

	pTmpCnt = IAContact_Create();

	pTmpCnt->_iRid = AMAtoi(pszValue[0]);

	IAContact_SetCntID(pTmpCnt, pszValue[1], AMStrlen(pszValue[1]));

	pCntFind = find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	//陌生人不需要去find_Other了，陌生人是Other中最早恢复的
	
	if(0 != pCntFind)//如果已经是好友了
	{
		IAContact_Destroy(pTmpCnt);
		pCntModel->uiDirtFlag	|= 0x20;//将strange数据标黑
	}
	else
	{
		IAContact_MarkStrang(pTmpCnt);
		pTmpCnt->pParentGrp = pCntModel->pStrangerGrp;
		IAContact_SetNickName(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID) - 8);
		IAContact_SetPinyin(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID) - 8);
		IAContact_AutoSetBindUid(pCntModel->pReference, pTmpCnt);
		insert_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);
		insert_List(&pCntModel->pStrangerGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);
	}

	return 0;
}

AMInt32		IAContactModel_RestoreStranger(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite	= 0;
	AMChar	*szErrMsg	= 0;
	ContactList	*pStrangers = AMNULL;
	ListIter *pIter = AMNULL;
	IAContact *pTmpCnt = AMNULL;
	AIM_NTF_DATA_READY ntfDataReady;

	clear(List, &pCntModel->pStrangerGrp->lChildCnt);

	DPRINT("IAContactModel_RestoreStranger..........when ohtFriends.size =  %d\n", pCntModel->ohtFriends.num_elem);

	iRcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _strangerlist;",
								IAContactModel_OnSelStrangers, pCntModel, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_RestoreStranger.......Can't SELECT * FROM _strangerlist;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->pStrangerGrp->lChildCnt.size)
	{
		pStrangers = AMMalloc(sizeof(ContactList) * pCntModel->pStrangerGrp->lChildCnt.size);
		if(pStrangers)
		{
			int i = 0;
			AMMemset(pStrangers, 0, sizeof(ContactList) * pCntModel->pStrangerGrp->lChildCnt.size);
			pIter = create(ListIter, &pCntModel->pStrangerGrp->lChildCnt);
			head(ListIter, pIter);
			do 
			{
				pTmpCnt = (IAContact*)retrieve(ListIter, pIter);
				pStrangers[i].userID = pTmpCnt->szID;
				pStrangers[i].userIDLen = AMStrlen(pTmpCnt->szID);
				pStrangers[i].pNext = &pStrangers[i+1];
				i++;
			} while (!next(ListIter, pIter));
			destroy(ListIter, pIter);
			pStrangers[i-1].pNext = AMNULL;

			IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, pStrangers, 1);

			AMFree(pStrangers);
		}
	}

	ntfDataReady.eInfo = eDATA_STRANGER_READY;
	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	DPRINT("IAContactModel_RestoreStrangers..................OK\n");

	return 0;
}


AMInt32		IAContactModel_StoreRecent(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite = 0;
	AMChar	*szErrMsg = 0;
	ListIter	*pItr = 0;
	IAContact	*pCnt = 0;
	AMChar	*szSql = AMNULL;

	iRcSqlite = sqlite3_exec(pDB, "DELETE FROM _recentlist;", 0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreRecent:.......can not \"DELETE FROM _recentlist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
	}

	iRcSqlite = sqlite3_exec(pDB, "CREATE TABLE IF NOT EXISTS _recentlist(_rid INTEGER PRIMARY KEY AUTOINCREMENT, _cntid	VARCHAR(64));",
		0, 0, &szErrMsg);
	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreRecent:.......can not \"CREATE TABLE _recentlist;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->pRecentGrp->lChildCnt.size > 0)
	{
		pItr = create(ListIter, &pCntModel->pRecentGrp->lChildCnt);
		head(ListIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreRecent:.......can not \"BEGIN TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			destroy(ListIter, pItr);
			return -1;
		}

		do 
		{
			pCnt = (IAContact *)retrieve(ListIter, pItr);
			szSql = sqlite3_mprintf("INSERT INTO _recentlist VALUES(NULL, '%q');",pCnt->szID);
			if(szSql)
			{
				iRcSqlite = sqlite3_exec(pDB, szSql,0,0,&szErrMsg);
				sqlite3_free(szSql);
				if(SQLITE_OK != iRcSqlite)
				{
					DPRINT("IAContactModel_StoreRecent:.......can not INSERT for %s\n", szErrMsg);
					sqlite3_free(szErrMsg);
					destroy(ListIter, pItr);
					return -1;
				}
			}
			else
			{
				destroy(ListIter, pItr);
				return -1;
			}
			
		} while (!next(ListIter, pItr));
		destroy(ListIter, pItr);

		iRcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != iRcSqlite)
		{
			DPRINT("IAContactModel_StoreRecent:.......can not \"COMMIT TRANSACTION;\":%s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			destroy(ListIter, pItr);
			return -1;
		}
	}

	DPRINT("IAContactModel_StoreRecent....................OK\n");

	return 0;
}

static AMInt32 IAContactModel_OnSelRecent(void* pvCntor, int iCnt, char **pszValue, char**pszName)
{
	IAContactModel	*pCntModel		= (IAContactModel *)pvCntor;
	IAContact		*pTmpCnt = 0, *pCntFind = 0;
	AMBool		bIsFriend = AMFALSE, bIsStrange = AMFALSE;

	AMAssert(0 !=  pCntModel);

	pTmpCnt = IAContact_Create();

	pTmpCnt->_iRid = AMAtoi(pszValue[0]);

	IAContact_SetCntID(pTmpCnt, pszValue[1], AMStrlen(pszValue[1]));

	pCntFind = find_OHTable(&pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
	{
		bIsFriend = AMFALSE;
		pCntFind = find_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	}
	else
	{
		bIsFriend = AMTRUE;
	}

	if(0 != pCntFind)
	{
		IAContact_Destroy(pTmpCnt);

		IAContact_MarkRecent(pCntFind);
		push_back_List(&pCntModel->pRecentGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);

#ifdef _NOFRIEND_IS_STRANGE_
		if(AMFALSE == bIsFriend)
		{
			IAIMContact_IsStrange(pCntFind, &bIsStrange);
			if(AMFALSE == bIsStrange)
			{
				IAContact_MarkStrang(pCntFind);	//最近联系人不是好友的时候，需要加入陌生人么？
				pCntFind->pParentGrp = pCntModel->pStrangerGrp;
				insert_List(&pCntModel->pStrangerGrp->lChildCnt, pCntFind, sizeof(IAContact), DYNAMIC);
				pCntModel->uiDirtFlag |= 0x20;	//标黑陌生人数据
			}
		}
#endif // _NOFRIEND_IS_STRANGE_
	}
	else
	{
		IAContact_MarkRecent(pTmpCnt);
		IAContact_SetNickName(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_SetPinyin(pTmpCnt, pTmpCnt->szID+8, AMStrlen(pTmpCnt->szID)-8);
		IAContact_AutoSetBindUid(pCntModel->pReference, pTmpCnt);
		insert_OHTable(&pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);
		push_back_List(&pCntModel->pRecentGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);

#ifdef _NOFRIEND_IS_STRANGE_
		IAContact_MarkStrang(pTmpCnt);		//最近联系人不是好友的时候，需要加入陌生人么？
		pTmpCnt->pParentGrp = pCntModel->pStrangerGrp;
		insert_List(&pCntModel->pStrangerGrp->lChildCnt, pTmpCnt, sizeof(IAContact), DYNAMIC);
		pCntModel->uiDirtFlag |= 0x20;	//标黑陌生人数据
#endif //_NOFRIEND_IS_STRANGE_
	}
	return 0;
}

AMInt32		IAContactModel_RestoreRecent(IAContactModel *pCntModel, sqlite3 *pDB)
{
	AMInt32	iRcSqlite	= 0;
	AMChar	*szErrMsg	= 0;
	ContactList	*pRecents = AMNULL;
	ListIter *pIter = AMNULL;
	IAContact *pTmpCnt = AMNULL;
	AIM_NTF_DATA_READY ntfDataReady;


	clear(List, &pCntModel->pRecentGrp->lChildCnt);

	DPRINT("IAContactModel_OnSelRecent..........when ohtFriends.size =  %d\n", pCntModel->ohtFriends.num_elem);

	iRcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _recentlist;",
							IAContactModel_OnSelRecent, pCntModel, &szErrMsg);

	if(SQLITE_OK != iRcSqlite)
	{
		DPRINT("IAContactModel_StoreRecent:.......Can't SELECT * FROM _recentlist;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	if(pCntModel->pRecentGrp->lChildCnt.size)
	{
		pRecents = AMMalloc(sizeof(ContactList) * pCntModel->pRecentGrp->lChildCnt.size);
		if(pRecents)
		{
			int i = 0;
			AMMemset(pRecents, 0, sizeof(ContactList) * pCntModel->pRecentGrp->lChildCnt.size);
			pIter = create(ListIter, &pCntModel->pRecentGrp->lChildCnt);
			head(ListIter, pIter);
			do 
			{
				pTmpCnt = (IAContact*)retrieve(ListIter, pIter);
				pRecents[i].userID = pTmpCnt->szID;
				pRecents[i].userIDLen = AMStrlen(pTmpCnt->szID);
				pRecents[i].pNext = &pRecents[i+1];
				i++;
			} while (!next(ListIter, pIter));
			destroy(ListIter, pIter);
			pRecents[i-1].pNext = AMNULL;

			IMnetSubscribeContactInfo(pCntModel->pReference->pNetModel, pRecents, 1);

			AMFree(pRecents);
		}
	}

	ntfDataReady.eInfo = eDATA_RECENT_READY;
	AIMContactModel_Callback(pCntModel, OnNtfDataReady, &ntfDataReady);

	DPRINT("IAContactModel_RestoreRecent..................OK\n");

	return 0;
}

AMInt32		IAContactModel_Store(IAContactModel *pCntModel, AMBool	bClear)
{
	sqlite3		*pDB		= 0;
	AMInt32		iRcSqlite	= 0;
	AMAssert(0 != pCntModel && 0 != pCntModel->pReference->pAcnt);
	
	if(0 != pCntModel->uiDirtFlag)
	{
		iRcSqlite = myADB_Open(pCntModel->pReference->pAcnt->szID, &pDB, AMFALSE);

		if(iRcSqlite)
		{
			DPRINT("IAContactModel_Store:.......Can't sqlite3_open: %s\n", sqlite3_errmsg(pDB));
			sqlite3_close(pDB);
			return -1;
		}

		if((pCntModel->uiDirtFlag & 0x01) == 0x01)//Group data is dirty.
		{
			if(0 == IAContactModel_StoreGrp(pCntModel, pDB))
				pCntModel->uiDirtFlag &= ~0x01;
		}

		if((pCntModel->uiDirtFlag & 0x02) == 0x02)//contact data is dirty.
		{
			if(0 == IAContactModel_StoreFriends(pCntModel, pDB))
				pCntModel->uiDirtFlag &= ~0x02;
		}

		if((pCntModel->uiDirtFlag & 0x04) == 0x04)//black data is dirty
		{	
			if(0 == IAContactModel_StoreBlack(pCntModel, pDB))
				pCntModel->uiDirtFlag &= ~0x04;
		}

		if((pCntModel->uiDirtFlag & 0x08) == 0x08)//reverse black data is dirty
		{
			if(0 == IAContactModel_StoreRevBlack(pCntModel, pDB))
				pCntModel->uiDirtFlag &= ~0x08;
		}

		if((pCntModel->uiDirtFlag & 0x20) == 0x20)//stranger flags is dirty
		{
			if(0 == IAContactModel_StoreStrangers(pCntModel, pDB))
				pCntModel->uiDirtFlag &= ~0x20;
		}

		if((pCntModel->uiDirtFlag & 0x40) == 0x40)//recent flags is dirty
		{
			if(0 == IAContactModel_StoreRecent(pCntModel, pDB))
				pCntModel->uiDirtFlag &= ~0x40;
		}

		sqlite3_close(pDB);
	}

	if(AMTRUE == bClear)
	{
		IAContactModel_ClearData(pCntModel);
	}

	return pCntModel->uiDirtFlag;
}

AMInt32		IAContactModel_Restore(IAContactModel *pCntModel, AMUInt32 iDirtFlag, AMBool bTry)
{
	AMInt32 iRcSqlite	= 0;
	sqlite3		*pDB	= 0;
	AMInt32		iRetCode = 0;

	AMAssert(0 != pCntModel && 0 != pCntModel->pReference->pAcnt);

	iRcSqlite = myADB_Open(pCntModel->pReference->pAcnt->szID, &pDB, bTry);

	pCntModel->uiDirtFlag = iDirtFlag & 0x0F;//Restore时，数据库中的数据中，只有网络数据可能是脏的~

	if(iRcSqlite)
	{
		DPRINT("IAContactModel_Restore:Can't sqlite3_open: %s(Maybe first time<noError>.)\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		return -1;
	}

	if(AMTRUE == bTry)
	{
		sqlite3_close(pDB);
		return 0;
	}

	clear(OHTable, &pCntModel->ohtOthers);

	if((iDirtFlag & 0x01) != 0x01)
	{
		if(0 == IAContactModel_RestoreGrp(pCntModel, pDB))
			IAContactModel_BuildGroupTree(pCntModel);
		else
			iRetCode |= 0x01;
	}

	if((iDirtFlag & 0x02) != 0x02)
	{
		if(0 != IAContactModel_RestoreFriends(pCntModel, pDB))
			iRetCode |= 0x02;
		
		if((iDirtFlag & 0x04) != 0x04)
		{
			if(0 != IAContactModel_RestoreBlack(pCntModel, pDB))	//以下几个必须在ohtFriends和ohtOthers建立之后，他们的数据都在这两个之中。
				iRetCode |= 0x04;
		}			

		if((iDirtFlag & 0x08) != 0x08)
		{
			if( 0 != IAContactModel_RestoreRevBlk(pCntModel, pDB))
				iRetCode |= 0x08;
		}

		if((iDirtFlag & 0x01) != 0x01)
		{
			IAContactModel_SetAllContact(pCntModel, AMFALSE);		//必须在ohtGrps建立之后！！！
		}
	}

	sqlite3_close(pDB);

	return iRetCode;
}

AMVoid				IAContactModel_ListenIMnet(IAContactModel *pCntModel, IMnetHandle pNetModel)
{
	AMAssert(0 != pCntModel && 0 != pNetModel);
	IMnetMainRegister(pNetModel, IM_EVENT_GETGROUP, IAContactModel_OnGetGroup);
	IMnetMainRegister(pNetModel, IM_EVENT_GETCONTACT, IAContactModel_OnGetContact);
	IMnetMainRegister(pNetModel, IM_EVENT_GETBLACK, IAContactModel_OnGetBlack);
	IMnetMainRegister(pNetModel, IM_EVENT_GETREVBLACK, IAContactModel_OnGetRevBlack);
	IMnetMainRegister(pNetModel, IM_EVENT_GETCNTSTATUS, IAContactModel_OnGetCntStatus);
	IMnetMainRegister(pNetModel, IM_EVENT_SUBSCRIBE_INFO, IAContactModel_OnGetCntStatus);
	IMnetMainRegister(pNetModel, IM_EVENT_GET_CN_EXTRAINFO, IAContactModel_OnGetCNExtraInfo);
	IMnetMainRegister(pNetModel, IM_EVENT_GETWEBBINDING, IAContactModel_OnGetWebBinding);
	IMnetMainRegister(pNetModel, IM_EVENT_WEBUSERMESSAGE, IAContactModel_OnNtfWebUserMessage);

	IMnetMainRegister(pNetModel, IM_NTF_BINDID_KICKED, IAContactModel_OnBindIDForceDisconnect);


	IMnetMainRegister(pNetModel, IM_EVENT_ADDCONTACT, IAContactModel_OnAddContact);
	IMnetMainRegister(pNetModel, IM_EVENT_ADDBLACK, IAContactModel_OnAddBlack);
	IMnetMainRegister(pNetModel, IM_EVENT_DELCONTACT, IAContactModel_OnDelContact);
	IMnetMainRegister(pNetModel, IM_EVENT_DELBLACK, IAContactModel_OnDelBlack);

	IMnetMainRegister(pNetModel, IM_EVENT_STATUS, IAContactModel_OnStatus);
	IMnetMainRegister(pNetModel, IM_EVENT_UPDATEUSREXTINFO, IAContactModel_OnUpdateUsrExtInfo);

	IMnetMainRegister(pNetModel, IM_EVENT_PRIVATE, IAContactModel_OnIMEvent);
}

AMVoid				IAContactModel_UnlistenIMnet(IAContactModel *pCntModel, IMnetHandle pNetModel)
{
	AMAssert(0 != pCntModel && 0 != pNetModel);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETGROUP, IAContactModel_OnGetGroup);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETCONTACT, IAContactModel_OnGetContact);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETBLACK, IAContactModel_OnGetBlack);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETREVBLACK, IAContactModel_OnGetRevBlack);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETCNTSTATUS, IAContactModel_OnGetCntStatus);
	IMnetMainUnregister(pNetModel, IM_EVENT_SUBSCRIBE_INFO, IAContactModel_OnGetCntStatus);
	IMnetMainUnregister(pNetModel, IM_EVENT_GET_CN_EXTRAINFO, IAContactModel_OnGetCNExtraInfo);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETWEBBINDING, IAContactModel_OnGetWebBinding);
	IMnetMainUnregister(pNetModel, IM_EVENT_WEBUSERMESSAGE, IAContactModel_OnNtfWebUserMessage);

	IMnetMainUnregister(pNetModel, IM_NTF_BINDID_KICKED, IAContactModel_OnBindIDForceDisconnect);

	IMnetMainUnregister(pNetModel, IM_EVENT_ADDCONTACT, IAContactModel_OnAddContact);
	IMnetMainUnregister(pNetModel, IM_EVENT_ADDBLACK, IAContactModel_OnAddBlack);
	IMnetMainUnregister(pNetModel, IM_EVENT_DELCONTACT, IAContactModel_OnDelContact);
	IMnetMainUnregister(pNetModel, IM_EVENT_DELBLACK, IAContactModel_OnDelBlack);

	IMnetMainUnregister(pNetModel, IM_EVENT_STATUS, IAContactModel_OnStatus);
	IMnetMainUnregister(pNetModel, IM_EVENT_UPDATEUSREXTINFO, IAContactModel_OnUpdateUsrExtInfo);


	IMnetMainUnregister(pNetModel, IM_EVENT_PRIVATE, IAContactModel_OnIMEvent);
}
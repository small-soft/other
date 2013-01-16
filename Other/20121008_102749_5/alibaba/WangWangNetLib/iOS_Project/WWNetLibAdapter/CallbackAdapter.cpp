
/*
 *  CallbackAdapter.cpp
 * 
 *  Created on  : 2012-06-11
 *  Author      : tom.lih
 */

#include "LoginDataStructDefs.h"
#include "ErrorCodeDefs.h"
#include "IWangWangNetCallback.h"
#include "OldMsgType.h"

#include "CallbackAdapter.h"
#include "AIM.h"
#include "AMString.h"
#include "ContactDetailInfo.h"

extern std::string Change2PlainText(const std::string& strFormattedText);

#define		CONTACT_LIST_LOADED         100

#define		CONTACT_ADDED               101

#define		CONTACT_REMOVED             102

#define		CONTACT_BINDID_LIST_LOADED 	109

#define		CONTACT_BINDID_KICKED       110

#define     UID_KEYWROD_ID              "uid"

#ifdef push_back(TYPE,STRUCT,OBJ,FLAG)
#undef push_back(TYPE,STRUCT,OBJ,FLAG)
#endif


#ifdef insert(TYPE,STRUCT,OBJ,FLAG)
#undef insert(TYPE,STRUCT,OBJ,FLAG)
#endif


/*
 extern AMInt32 JavaCntListener(AMVoid *pArg, AMInt32 iType, AMInt64 i64GrpID,  const AMChar *szCntID);
 
 
 static AMInt32 Adapter_OnIncomingSysMsg(IASessionModel *pSesModel, IAIMessage *pMsg, AMVoid *pvArg)
 {
 
 IASession *pSysSes = AMNULL;
 AMAssert(0 != pSesModel && 0 != pMsg);
 
 IASessionModel_StoreMsg(pSesModel, pMsg, AMTRUE);
 
 if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pSesModel, SYS_SES_NAME, (AMPVoid*)&pSysSes))
 {
 DPRINT("IASessionModel_OnIncomingSysMsg..................Error!\n");
 AMAssert(0);
 }
 
 return JavaMsgListener(pvArg, pSysSes, pMsg);
 }
 */

extern void *	g_hIM;
extern IWangWangNetCallback	  * g_pCallback;
extern CContactsInfoTimestamp	g_timestamp;

AIM_RESULT	OnRspLogin(AMVoid *pvArg, AIM_RSP_LOGIN * pRspLogin)
{
    
    IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
    
    CLoginFinalResult finalResult;
    
    finalResult.m_bGroupListUpdated=AMFALSE;
    finalResult.m_bContactListUpdated=AMFALSE;
    finalResult.m_bBlackListUpdated=AMFALSE;
    
    if (NULL != pIM)
    {
        if (NULL != pIM->pAcnt)
        {
            if (NULL != pIM->pAcnt->szToken)
            {
                finalResult.m_strTokenPassword = pIM->pAcnt->szToken;
            }
            
            if (g_timestamp.m_groupListTimestamp !=0 && g_timestamp.m_groupListTimestamp ==pIM->pAcnt->iGroupStamp)
            {
                finalResult.m_bGroupListUpdated=AMTRUE;
            }
            if (g_timestamp.m_contactListTimestamp !=0 && g_timestamp.m_contactListTimestamp==pIM->pAcnt->iContactStamp)
            {
                finalResult.m_bContactListUpdated=AMTRUE;
            }
            if (g_timestamp.m_blackListTimestamp !=0 &&  g_timestamp.m_blackListTimestamp==pIM->pAcnt->iBlackStamp)
            {
                finalResult.m_bBlackListUpdated=AMTRUE;
            }
        }else
        {
            pRspLogin->iRetCode=RESULT_FAILED;
        }
        
        if (NULL !=pIM->szRemarkMsg)
        {
            finalResult.m_strRemark = pIM->szRemarkMsg;
        }
    }
    
    if (g_pCallback)
    {
        if (!pRspLogin->iRetCode) 
        {
            g_pCallback->OnLoginResult(RESULT_OKEY, STEP_AUTH, finalResult);
        }else 
        {
            g_pCallback->OnLoginResult(pRspLogin->eInfo, STEP_AUTH, finalResult);
        }
    }
    
}

AIM_RESULT	OnNtfUpdateGroup(AMVoid *pvArg, AIM_NTF_UPDATE_GROUP *pNtfUpdateGroup)
{
    
	AMInt64 i64GrpId = 0;
	AMChar *szContactId = AMNULL;
	AMInt32 iType = 0;
    
	if(eAIM_GROUP_ADD == pNtfUpdateGroup->eType)
		iType = CONTACT_ADDED;
	else if(eAIM_GROUP_REMOVE == pNtfUpdateGroup->eType)
		iType = CONTACT_REMOVED;
    
	IAIMGroup_GetID(pNtfUpdateGroup->hGroup, &i64GrpId);
	IAIMContact_GetID(pNtfUpdateGroup->hContact, (const AMChar **)&szContactId);
	//by tom.lih
    /*
     appCntListener();
     */
    
    return eAIM_RESULT_OK;
    
}

AIM_RESULT	OnNtfUpdateContact(AMVoid *pArg, AIM_NTF_UPDATE_CONTACT *pNtfUpdateContact)
{
 	AIM_CONTACT_UPDATE_DATA	*pPresent = 0;
	AMInt32 i=0;
	IAIM *pIM = (IAIM*)(((AMPVoid*)pArg)[1]);
    ContactStatusList_t contactStatusList;
	pPresent = (AIM_CONTACT_UPDATE_DATA*)AMMalloc(sizeof(AIM_CONTACT_UPDATE_DATA) * pNtfUpdateContact->iCount);
	AMMemset(pPresent, 0, sizeof(AIM_CONTACT_UPDATE_DATA) * pNtfUpdateContact->iCount);
    
	switch(pNtfUpdateContact->eType)
	{
        case eAIM_CONTACT_PRESENCE_FIRST:
            DPRINT("OnNtfUpdateContact..........................Presence First!\n");
            for(i=0; i<pNtfUpdateContact->iCount; i++)
            {
                pPresent[i].ucType = eAIM_CONTACT_PRESENCE;
                IAIMContact_GetPresence(pNtfUpdateContact->phContacts[i], (AIM_PRESENCE*)&pPresent[i].ucStatus);
                IAIMContact_GetID(pNtfUpdateContact->phContacts	[i], (const AMChar **)&pPresent[i].szID);
                
                CContactStatus contactStatus;
                contactStatus.m_strUid = pPresent[i].szID;
                
                contactStatus.m_defaultPresence =(EnLoginStatus)pPresent[i].ucStatus;
                contactStatusList.push_back(contactStatus);
                
            }                             
            if (g_pCallback && (pNtfUpdateContact->iCount>0) )
            {
                g_pCallback->OnContactStatusChanged(contactStatusList); 
            }
            
            break;
        case eAIM_CONTACT_PRESENCE:
            DPRINT("OnNtfUpdateContact..........................Presence!\n");
            
            for(i=0; i<pNtfUpdateContact->iCount; i++)
            {
                pPresent[i].iFlag = 1;
                pPresent[i].ucType = eAIM_CONTACT_PRESENCE;
                IAIMContact_GetPresence(pNtfUpdateContact->phContacts[i], (AIM_PRESENCE*)&pPresent[i].ucStatus);
                IAIMContact_GetID(pNtfUpdateContact->phContacts	[i], (const AMChar **)&pPresent[i].szID);
                
                CContactStatus contactStatus;
                contactStatus.m_strUid = pPresent[i].szID;
                
                contactStatus.m_defaultPresence =(EnLoginStatus)pPresent[i].ucStatus;
                contactStatusList.push_back(contactStatus);
                
            }                             
            
            if (g_pCallback && (pNtfUpdateContact->iCount>0) )
            {
                g_pCallback->OnContactStatusChanged(contactStatusList); 
            }
            
            break;
        case eAIM_CONTACT_SIGNATURE:
            DPRINT("OnNtfUpdateContact..........................Signature!\n");
            for(i=0; i<pNtfUpdateContact->iCount; i++)
            {
                pPresent[i].iFlag = 1;
                pPresent[i].ucType = eAIM_CONTACT_SIGNATURE;
                IAIMContact_GetSignature(pNtfUpdateContact->phContacts[i], (const AMChar **)&pPresent[i].szSignature);
                IAIMContact_GetID(pNtfUpdateContact->phContacts	[i], (const AMChar **)&pPresent[i].szID);
                
                if (g_pCallback)
                {
                    g_pCallback->OnContactSignatureChanged(pPresent[i].szID, pPresent[i].szSignature); 
                }
            }
            
            break;
        case eAIM_CONTACT_PORTRAIT:
            DPRINT("OnNtfUpdateContact..........................Portrait!\n");
#ifdef ALIM_SUPPORT_PORTRAIT_NOTIFY	// notify the event
            for(i=0; i<pNtfUpdateContact->iCount; i++)
            {
                pPresent[i].iFlag = 1;
                pPresent[i].ucType = eAIM_CONTACT_PORTRAIT;
            }
#else // get the portrait data. 
            IAIMContact_GetID(pNtfUpdateContact->phContacts	[0], (const AMChar **)&pPresent[0].szID);
            IAIM_GetPortrait(pIM, pPresent[0].szID);
            
            pNtfUpdateContact->iCount = 0;//»Áπ˚ «Õ∑œÒ ¬º˛£¨‘Ú≤ªœÚ…œ∑¢ÀÕ¡À
#endif
        default:
            pNtfUpdateContact->iCount = 0;
	}
    
	AMFree(pPresent);
    
    return eAIM_RESULT_OK;
}

AMInt32 sysMsgListener(AMVoid *pArg, IASession *pSes, IAIMessage *pMsg)
{
    DPRINT("sysMsgListener.........Called with 0x%x, 0x%x, 0x%x\n", pArg, pSes, pMsg);
    CTextMsg sysMsg;
    
    sysMsg.m_type =(EnTextMsgType) pMsg->eType; 
    if (pMsg->eType != CHG_SIGNATURE_OK) 
    {
        sysMsg.m_strPeerContactId =pMsg->szContactID;
    }
    
    //sysMsg.bUnread = pMsg->bUnread;
    //sysMsg.m_nTime = pMsg->iServerTime; 
    //sysMsg.m_nTextSequence = pMsg->_iRid ;
    
    if (g_pCallback) 
    {
        g_pCallback->OnRecvSysMsg(sysMsg);
        
    }
    
    return 0;
}

AIM_RESULT	OnNtfMesage(AMVoid *pvArg, AIM_NTF_MSG *pNtfMsg)
{    
    //receive text message ,101 
    if (((IAIMessage *)(pNtfMsg->hMessage))->eType == eMSG_TYPE_CHAT_RECV) 
    {
        
        CTextMsg textMsg;
        
        textMsg.m_strPeerContactId =((IAIMessage *)(pNtfMsg->hMessage))->szContactID; 
        textMsg.m_type = TEXT_MSG_NORMAL_TEXT; 
        //textMsg.m_strTextContent =((IAIMessage *)(pNtfMsg->hMessage))->szContent ;
        //transfer message content in library.
        textMsg.m_strTextContent =Change2PlainText(((IAIMessage *)(pNtfMsg->hMessage))->szContent);
        
        textMsg.m_nTextSequence = ((IAIMessage *)(pNtfMsg->hMessage))->_iRid ;
        textMsg.m_nTime = ((IAIMessage *)(pNtfMsg->hMessage))->iServerTime;  
        
        if (g_pCallback) 
        {
            g_pCallback->OnRecvTextMsg(textMsg);
        }
    }
    
    //added by friend ,10E 
    if (((IAIMessage *)(pNtfMsg->hMessage))->eType == eMSG_TYPE_CONTACT_ADDED_BY) 
    {
        
        if (g_pCallback) 
        {
            g_pCallback->OnMyselfAdded(((IAIMessage *)(pNtfMsg->hMessage))->szContactID);
        }
    }
    
    //receive  add request by friend ,  
    if (((IAIMessage *)(pNtfMsg->hMessage))->eType == eMSG_TYPE_CONTACT_REQ_FROM) 
    {
        
        if (g_pCallback) 
        {
            g_pCallback->OnRequestAddMyself(((IAIMessage *)(pNtfMsg->hMessage))->szContactID, "" );
        }
    }
    
}


AIM_RESULT	OnRspGetSignature(AMVoid *pvArg, AIM_RSP_GET_SIGNATURE *rspGetSignature)
{	
	AIM_CONTACT_UPDATE_DATA	*pPresent = 0;
	AMInt32 i=0;
    
    UidSignatures_t uidSigs;
    
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	if(!rspGetSignature->iRetCode)
	{
		pPresent = (AIM_CONTACT_UPDATE_DATA	*)AMMalloc(sizeof(AIM_CONTACT_UPDATE_DATA) * rspGetSignature->iCount);
		AMMemset(pPresent, 0, sizeof(AIM_CONTACT_UPDATE_DATA) * rspGetSignature->iCount);
		for(i=0; i<rspGetSignature->iCount; i++)
		{
			pPresent[i].iFlag = 0;
			pPresent[i].szID = rspGetSignature->pszContactIds[i];
			pPresent[i].szSignature = rspGetSignature->pszValues[i];
			pPresent[i].ucType = eAIM_CONTACT_SIGNATURE;
            
            
			CUidSignature uidSignature;
			uidSignature.m_strUid = rspGetSignature->pszContactIds[i];
			uidSignature.m_strSignature = rspGetSignature->pszValues[i];
            uidSigs.push_back(uidSignature);
            
		}
        
		//JavaPreListener(pvArg, pPresent, rspGetSignature->iCount);
        if (g_pCallback)
        { 
            g_pCallback->OnGetSignature(uidSigs);     
        }
        
		AMFree(pPresent);
	}
	else
	{
		AMAssert(pIM && pIM->pAcnt);
		AMAssert(rspGetSignature->pszContactIds);
		DPRINT("OnRspGetSignature................Fail: %s\n", *(rspGetSignature->pszContactIds));
		if(0 == AMStrcmp(pIM->pAcnt->szID, *(rspGetSignature->pszContactIds)))
		{
			DPRINT("OnRspGetSignature................Fail: %s\n", *(rspGetSignature->pszContactIds));
			//pIM->pAcnt->bGetSigFail = AMTRUE;
		}
		else
		{
			DPRINT("OnRspGetSignature.....................Acnt %s\n", pIM->pAcnt->szID);
		}
	}
    
	return eAIM_RESULT_OK;
}


static AMInt32 Adapter_OnIncomingSysMsg(IASessionModel *pSesModel, IAIMessage *pMsg, AMVoid *pvArg)
{
	IASession *pSysSes = AMNULL;
	AMAssert(0 != pSesModel && 0 != pMsg);
    
	IASessionModel_StoreMsg(pSesModel, pMsg, AMTRUE);
    
	if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pSesModel, SYS_SES_NAME, (AMPVoid*)&pSysSes))
	{
		DPRINT("IASessionModel_OnIncomingSysMsg..................Error!\n");
		AMAssert(0);
	}
    
	return sysMsgListener(pvArg, pSysSes, pMsg);
}

AIM_RESULT	OnRspGetProfile(AMVoid *pvArg, AIM_RSP_GET_PROFILE *pRspGetProfile)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = 0;
	AMInt32 iContentLen = 0, i = 0, iPos = 0, iLen = 0;;
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	pMsg->eType = (AIM_MSG_TYPE)GET_PEER_UDB_PROFILE;
	IAIMessage_SetCntID(pMsg, pRspGetProfile->szContactId, AMStrlen(pRspGetProfile->szContactId));
    
	iContentLen = pRspGetProfile->iTotalLen + 4 + AMStrlen(pRspGetProfile->szContactId) + sizeof(UID_KEYWROD_ID);
	iContentLen +=  pRspGetProfile->iCount*2;
    
	pMsg->szContent = (AMChar *)AMMalloc(iContentLen);
	if(AMNULL == pMsg->szContent)
	{
		IAIMessage_Destroy(pMsg);
		return eAIM_RESULT_NOT_READY;
	}
	AMMemset(pMsg->szContent, 0, iContentLen);
    //add by tom.lih
    KeyValueMap_t  profileMap;
    
	for(i=0; i<pRspGetProfile->iCount; i++)
	{
		if(AMNULL != pRspGetProfile->pszValues[i])
		{
			iLen = AMStrlen(pRspGetProfile->pszKeys[i]);
			AMMemcpy(pMsg->szContent+iPos, pRspGetProfile->pszKeys[i], iLen);
            
			iPos += iLen;
            
			pMsg->szContent[iPos++] = '\1';
			iLen = AMStrlen(pRspGetProfile->pszValues[i]);
			AMMemcpy(pMsg->szContent+iPos, pRspGetProfile->pszValues[i], iLen);
            
			iPos += iLen;
			pMsg->szContent[iPos++] = '\1';
            
            profileMap.insert(KeyValueMap_t::value_type((pRspGetProfile->pszKeys[i]), (pRspGetProfile->pszValues[i])));
            
		}
	}
    
	AMMemcpy(pMsg->szContent+iPos, UID_KEYWROD_ID, sizeof(UID_KEYWROD_ID)-1);//º”…œ"uid\1'contactId'"
	iPos += sizeof(UID_KEYWROD_ID)-1;
	pMsg->szContent[iPos++] = '\1';
    
	AMStrcat(pMsg->szContent+iPos, pRspGetProfile->szContactId);//≤ª–Ë“™Œ≤∞Õ¡À
    
    profileMap.insert(KeyValueMap_t::value_type((UID_KEYWROD_ID), (pRspGetProfile->szContactId)));
    
	DPRINT("IASessionModel_OnPeerVerifyConfig.................%s\n", pMsg->szContent);	
    
    //by tom.lih    
    //	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
    
    CContactPersonalDetailInfo detailInfo;
    CContactDetailInfoUtils detailInfoUtils;
    
    detailInfoUtils.MakeDetailInfo(profileMap ,&detailInfo);
    if (g_pCallback) 
    {
        g_pCallback->OnReturnContactPersonalDetailInfo(detailInfo);
    }
    
	IAIMessage_Destroy(pMsg);
    
	return eAIM_RESULT_OK;
}


AIM_RESULT	OnRspAddBlack(AMVoid *pvArg, AIM_RSP_ADD_BLACK *pRspAddBlack)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage *pMsg = AMNULL;
    
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	IAIMessage_SetCntID(pMsg, pRspAddBlack->szBlackId, AMStrlen(pRspAddBlack->szBlackId));
    
	if(!pRspAddBlack->iRetCode)
	{
		pMsg->eType = (AIM_MSG_TYPE)ADD_BLK_SUCCESS;
	}
	else
	{
		pMsg->eType = (AIM_MSG_TYPE)ADD_BLK_FAILED;
	}
    
	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
    
	IAIMessage_Destroy(pMsg);
    
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspChgSignature(AMVoid *pvArg, AIM_RSP_CHG_SIGNATURE *pRspChgSignature)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = 0;
    
	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);
    
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	if(!pRspChgSignature->iRetCode)
	{
		pMsg->eType	= (AIM_MSG_TYPE)CHG_SIGNATURE_OK;
		IAIMessage_SetContent(pMsg, pIM->pAcnt->szSignature, AMStrlen(pIM->pAcnt->szSignature));
		DPRINT("IAIM_OnChgSignature..............%s\n", pIM->pAcnt->szSignature);
	}
	else
	{
		pMsg->eType	= (AIM_MSG_TYPE)CHG_SIGNATURE_FAIL;
		DPRINT("IAIM_OnChgSignature...................Faile!\n");
	}
    
	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
    
	IAIMessage_Destroy(pMsg);
    
	return eAIM_RESULT_OK;
}



AIM_RESULT	OnNtfForceDisconnected(AMVoid *pArg)
{
    if (g_pCallback) 
    {
        g_pCallback->OnForceDisconnect();
    }  
}


AIM_RESULT	OnNtfNetInfo(AMVoid *pArg, AIM_NTF_NET_STATUS * pNtfNetStatus)
{
	switch (pNtfNetStatus->eStatus)
	{
        case eNET_OK:
            //return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_NETOK, 0);
            break;
        case eNET_PUZZLE:
            //return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_NETPUZZLE, 0);
            if (g_pCallback) 
            {
                g_pCallback->OnNetworkError();
            }
            break;
        case eNET_CUT:
            //return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_NETCUT, 0);           
            if (g_pCallback) 
            {
                g_pCallback->OnNetworkError();
            } 
            break;
	}
	return eAIM_RESULT_OK;
}

AIM_RESULT    OnRspDelContact(AMVoid *pvArg, AIM_RSP_DEL_CONTACT *pRspDelContact)
{
    IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
    IAIMessage *pMsg = AMNULL;
    if(!pRspDelContact->iRetCode && pRspDelContact->szContactId)
    {
        pMsg = IAIMessage_Create();
        pMsg->bUnread = AMTRUE;
        pMsg->eType = (AIM_MSG_TYPE)REMOVE_CNT_SUCESS;
        
        IAIMessage_SetCntID(pMsg, pRspDelContact->szContactId, AMStrlen(pRspDelContact->szContactId));
        
        Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
        IAIMessage_Destroy(pMsg);
    }
    return eAIM_RESULT_OK;
}

AIM_RESULT    OnRspDelBlack(AMVoid *pvArg, AIM_RSP_DEL_BLACK *pRspDelBlack)
{
    IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
    IAIMessage *pMsg = AMNULL;
    
    pMsg = IAIMessage_Create();
    pMsg->bUnread = AMTRUE;
    IAIMessage_SetCntID(pMsg, pRspDelBlack->szBlackId, AMStrlen(pRspDelBlack->szBlackId));
    
    if(!pRspDelBlack->iRetCode)
    {
        pMsg->eType = (AIM_MSG_TYPE)REMOVE_BLK_SUCESS;
    }
    else
    {
        pMsg->eType = (AIM_MSG_TYPE)REMOVE_BLK_FAILED;
    }
    
    Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
    
    IAIMessage_Destroy(pMsg);
    
    return eAIM_RESULT_OK;
}    

AIM_RESULT    OnRspAddContact(AMVoid *pvArg, AIM_RSP_ADD_CONTACT *pRspAddContact)
{
    IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
    IAIMessage *pMsg = AMNULL;
    if(pRspAddContact->szContactId)
    {
        pMsg = IAIMessage_Create();
        pMsg->bUnread = AMTRUE;
        
        if(eADDCONTACT_SUCCESS == pRspAddContact->eRetCode)
        {
            pMsg->eType = eMSG_TYPE_CONTACT_ADD_OK;
            pMsg->bUnread = AMFALSE;   
            //remove the short time appearence of '1' in status bar: chunyuan.wuchy
        } 
        else if( eADDCONTACT_FAILED == pRspAddContact->eRetCode)
        {
            AMChar szBuf[MAX_INT_NUMBER_LEN] = {0};
            
            pMsg->eType = eMSG_TYPE_CONTACT_ADD_FAIL;
            _AIMItoa(pRspAddContact->eInfo, szBuf);
            DPRINT("%s >>>>>> info: %d, %s\n", __FUNCTION__, pRspAddContact->eInfo, szBuf);
            IAIMessage_SetContent(pMsg, szBuf, AMStrlen(szBuf));        
        } 
        else if(eADDCONTACT_NEEDVERIFY == pRspAddContact->eRetCode)
        {
            pMsg->eType = eMSG_TYPE_CONTACT_NEED_REQ;
        }
        else if(eADDCONTACT_WAITAUTH == pRspAddContact->eRetCode)
        {
            pMsg->eType = eMSG_TYPE_CONTACT_WAIT_VERIFY;
        }
        else
            AMAssert(0);
        
        IAIMessage_SetCntID(pMsg, pRspAddContact->szContactId, AMStrlen(pRspAddContact->szContactId));
        
        //Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
        if (g_pCallback)
        {
            CAddedContact addedContact;
            addedContact.m_strUid = pMsg->szContactID;
            addedContact.m_strDispName = "";
            addedContact.m_nGroupId = 0;
            
            if (eADDCONTACT_SUCCESS == pRspAddContact->eRetCode) 
            {
                g_pCallback->OnAddContactResult(addedContact, RESULT_OKEY, "");
            }
            else 
            {
                g_pCallback->OnAddContactResult(addedContact, pRspAddContact->eInfo, "");
            }
            
        }
        
        IAIMessage_Destroy(pMsg);
    }
    return eAIM_RESULT_OK;
}


AIM_RESULT  OnRspSearchUser(AMVoid *pvArg, AIM_RSP_SEARCH_USER *pRspGetProfile)
{
    DPRINT("OnRspSearchUser start");
    
    AIM_CONTACT_UPDATE_DATA    *pPresent = 0;
    AMInt32 i=0;
    
    IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
    
    if(!pRspGetProfile->iRetCode)
    {
        
        SearchContactList_t searchContactList;
        
        for (int i=0; i< pRspGetProfile->iUserCount; i++) 
        {
            
            CSearchContact searchContact;
            
            if (pRspGetProfile->pszContactIds[i] !=NULL) 
            {
                searchContact.m_strUid = pRspGetProfile->pszContactIds[i]; 
            }
            else 
            {
                searchContact.m_strUid = ""; 
            }
            
            if (pRspGetProfile->pszNickNames[i] !=NULL) 
            {
                searchContact.m_stNickName = pRspGetProfile->pszNickNames[i]; 
            }
            else 
            {
                searchContact.m_stNickName = ""; 
            }
            
            if (pRspGetProfile->pszCitys[i] !=NULL) 
            {
                searchContact.m_strCity = pRspGetProfile->pszCitys[i];
            }
            else 
            {
                searchContact.m_strCity = "";
            }
            
            searchContact.m_strAge = pRspGetProfile->pAges[i]; 
            searchContact.m_strGender = pRspGetProfile->pGenders[i];
            
            //? 这里服务器返回的和enBasicStatus的定义恰好是反的
            if (pRspGetProfile->pBasicStatus[i] == 0)
            {
                searchContact.m_basiCStatus = (EnBasicStatus)1;
            }
            else
            {
                searchContact.m_basiCStatus = (EnBasicStatus)0;
            }
            
            searchContactList.push_back(searchContact);
        }
        
        if (g_pCallback)
        {
            g_pCallback->OnReturnSearchContacts(searchContactList, 0);
        }
        
    }
    else
    {
        AMAssert(pIM && pIM->pAcnt);
    }
    DPRINT("OnRspSearchUser end");
    return eAIM_RESULT_OK;
}

AIM_RESULT    OnNtfAddedBy(AMVoid *pvArg, AIM_NTF_ADDED_BY *pNtfAddedBy)
{
    if (g_pCallback)
    {
        g_pCallback->OnMyselfAdded(pNtfAddedBy->szContactId);
    }
    return eAIM_RESULT_OK;
}

AIM_RESULT    OnNtfAcceptedBy(AMVoid *pvArg, AIM_NTF_ACCEPTED_BY * pNtfAcceptedBy)
{
    return eAIM_RESULT_OK;
}

AIM_RESULT    OnNtfRejectedBy(AMVoid *pvArg, AIM_NTF_REJECTED_BY * pNtfRejectedBy)
{
    return eAIM_RESULT_OK;
}

AIM_RESULT    OnNtfRequestFrom(AMVoid *pvArg, AIM_NTF_REQUEST_FROM *pNtfRequestFrom)
{
    return eAIM_RESULT_OK;
}

AIM_RESULT    OnNtfDataReady(AMVoid *pArg, AIM_NTF_DATA_READY *ntfDataReady)
{
    switch (ntfDataReady->eInfo)
    {
        case eDATA_GROUP_READY:
            break;
        case eDATA_FRIEND_READY:
            break;
        case eDATA_STRANGER_READY:
            break;
        case eDATA_RECENT_READY:
            break;
        case eDATA_BLACK_READY:
            break;
            
        case eDATA_ALLREADY:
            DPRINT("%s >>>>>> Data Ready, CONTACT_LIST_LOADED\n", __FUNCTION__);
        case eDATA_BINDID_ALLREADY:
            DPRINT("%s >>>>>> Data Ready, CONTACT_BINDID_LIST_LOADED\n", __FUNCTION__);
        case eDATA_BINDID_KICKED:
            DPRINT("%s >>>>>> eDATA_BINDID_KICKED , CONTACT_BINDID_KICKED \n", __FUNCTION__);            
            if (g_pCallback)
            {
                g_pCallback->OnNtfDataReady(ntfDataReady->eInfo);
            }
            break;
    }
    return eAIM_RESULT_OK;
}




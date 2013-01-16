
/*
 *  WangWangNetLib.cpp
 * 
 *  Created on  : 2012-06-11
 *  Author      : tom.lih
 */
 
#include "WangWangNetLib.h"
#include "CallbackAdapter.h"
#include "AIM.h"
#include "IAIM.h"

#ifdef push_back(TYPE,STRUCT,OBJ,FLAG)
#undef push_back(TYPE,STRUCT,OBJ,FLAG)
#endif

#ifdef find(TYPE,STRUCT,OBJ)
#undef find(TYPE,STRUCT,OBJ)
#endif

#ifdef empty(TYPE,STRUCT)
#undef empty(TYPE,STRUCT)
#endif

#ifdef clear(TYPE,STRUCT)
#undef clear(TYPE,STRUCT)
#endif

#define   ALIBABA_CLIENT_MESSAGE    "【该消息来自手机旺旺 iPhone 客户端，体验客户端请访问 http://3g.china.alibaba.com/iphone 】"

#define   ALIBABA_TTID_MESSAGE      "215200@aliww_app_1_1.2.4"
#define   ALIBABA_OM_VERSION        "0005"

IWangWangNetCallback	* g_pCallback; 
void *	g_hIM;
CContactsInfoTimestamp	g_timestamp;

AMPVoid pvArg[2] = {AMNULL, AMNULL};
AIM_CALLBACK	CallBack_Template = {
	pvArg,
	OnNtfForceDisconnected,
	NULL,//OnNtfCheckVersion,
	OnNtfDataReady,
	OnNtfNetInfo,
	OnNtfUpdateGroup,
	OnNtfUpdateContact,
	OnNtfMesage,
	OnNtfAddedBy,
	OnNtfAcceptedBy,
	OnNtfRejectedBy,
	OnNtfRequestFrom,
	NULL,//OnNtfHelpLogin ,
	NULL,//OnNtfUserInfo ,
	NULL,
	NULL,//OnNtfNeedAuth ,
	OnRspLogin,//17
	NULL,//OnRspChgVerify ,
	NULL,//OnRspChgSrvMode ,
	OnRspChgSignature,
	OnRspAddContact,//NULL
	OnRspDelContact,//NULL
	NULL,//OnRspAccept ,
	OnRspAddBlack,
	OnRspDelBlack,//NULL
	NULL,//OnRspGetVerify ,
	OnRspGetProfile,
	NULL,//OnRspGetDegree ,
	NULL,//OnRspGetMemo ,
	OnRspGetSignature,
	NULL,//OnRspGetPortrait ,
	NULL,//OnRspSendMsg,
	AMNULL,//OnRspChgPresence ,
	NULL,
	NULL,//OnRspCheckCode
    OnRspSearchUser,
};


CWangWangNetLib::CWangWangNetLib()
{   
	hIM = AMNULL;  
}

CWangWangNetLib::~CWangWangNetLib()
{
   
}

void CWangWangNetLib::Start(IWangWangNetCallback* pCallback, const std::string& dbPath)
{	
   
    IASessionModel_SetMobileImMessage(ALIBABA_CLIENT_MESSAGE);
    
    IAIM_SetTtid(ALIBABA_TTID_MESSAGE);
    
    IAIM_SetGlobalDatabasePath((AMChar*)dbPath.c_str());

	if(AMNULL == hIM)
	{
		IAIM_Create((AMHandle*)&hIM);
        pvArg[1] = hIM;
		IAIM_RegisterListener((AMHandle*)hIM, &CallBack_Template);
        g_pCallback=pCallback; 
        
	} 
    
}


void CWangWangNetLib::Stop()
{
    
}


void CWangWangNetLib::LogOff()
{     
    g_pCallback=AMNULL; 
    
    if(NULL == hIM)
        return ;
    
    if ( NULL != ((IAIM *)hIM)->callback) 
    {
        IAIM_UnregisterListener(hIM, ((IAIM *)hIM)->callback);
    }
    ((IAIM *)hIM)->callback=AMNULL;
    
    if ( NULL != hIM) 
    {
        IAIM_Destroy(hIM);
        hIM=AMNULL;
    }
    
    pvArg[1] = AMNULL;
    
}

void CWangWangNetLib::Login(IWangWangNetCallback* pCallback, const std::string& dbPath, 
           const CWangWangEnviroment& wangwangEnviroment,
           const CLoginUserLoginInfo& loginUserLoginInfo)
{
    if(AMNULL == hIM)
	{
		Start(pCallback, dbPath);
	}
    
    AMAssert(hIM !=AMNULL);
  
    
    AIM_ACCOUNT_SETTING setting;
    //基本状态(0-在线,1-离线,2-隐身)
    setting.eDefaultPresence = (AIM_PRESENCE) loginUserLoginInfo.m_loginStatus.m_defaultPresence;
	setting.bSavePwd = 1;
	setting.bMute = 0;
	setting.bViberate = 0;
    
    AMBool bTest =AMFALSE;
    AMBool bNotPlain =AMFALSE;
    
    g_timestamp= loginUserLoginInfo.m_timestamp;
   
    IAIM_LoginEx(hIM, loginUserLoginInfo.m_loginStatus.m_strUid.c_str(), loginUserLoginInfo.m_password.m_strPassword.c_str(), bNotPlain, setting, bTest,ALIBABA_OM_VERSION);

}

void CWangWangNetLib::RequestGetGroupList()
{ 
    AMHandle *pGrps = AMNULL;
    AMInt32 iCount = 0;
    AMInt64 iGrpId = 0;
    
    const AMChar    *szGrpName = AMNULL;
    
    IAIM *pIM = (IAIM *)hIM;  
    
    int times=0;
	int retryCount=1000;
    
    while ((!pIM || !pIM->pCntModel) && (times < retryCount))
    {
        AMSleep(1);
        times++;
    }
    if (times >= retryCount) 
    {
        return;
    }
    
    times=0;
	retryCount=500;
    while (((pIM->pCntModel)->lTopGrp.size  == 0) && (times < retryCount))
    {
        AMSleep(1);
        times++;
    } 
    if (times >= retryCount) 
    {
        return;
    }

    if (eAIM_RESULT_OK  != IAIM_GetTopGroups(pIM, &pGrps, &iCount)
        || (pGrps == AMNULL) ) 
    {
        return;
    }
    
    GroupList_t retGroupList;
    
    for(int i=iCount-1; i>=0; i--)
    {
        IAIMGroup_GetID(pGrps[i], &iGrpId);
        IAIMGroup_GetName(pGrps[i], &szGrpName);
        //旺旺好友grpid -6666
        if (iGrpId != -6666) 
        {
            
            CGroupInfo groupInfo;
            groupInfo.m_groupId = iGrpId; 
            
            groupInfo.m_parentId = 0;
            groupInfo.m_groupName = szGrpName;
            
            retGroupList.push_back(groupInfo);
        }
        
    }
    
    IAIM_ReleaseTopGroups(hIM, pGrps, iCount);
    
    if (g_pCallback)
    { 
        g_pCallback->OnReturnGroupList(retGroupList,pIM->pAcnt->iGroupStamp);
    }
    
    return ;
    
}

//请求得到联系人列表
void CWangWangNetLib::RequestGetContactList()
{   
    
    AMHandle *pGrps = AMNULL;
    AMInt32 iCount = 0;
    AMInt64 iGrpId = 0;   
    
    ContactList_t retContactList;
    
    IAIM *pIM = (IAIM *)hIM;
    IAContact * pCnt=AMNULL;
    
    int times=0;
	int retryCount=1000;

    while ((!pIM || !pIM->pCntModel) && (times < retryCount))
    {
        AMSleep(1);
        times++;
    }
    if (times >= retryCount) 
    {
        return;
    }
     
    times=0;
	retryCount=500;
    while (((pIM->pCntModel)->lTopGrp.size  == 0) && (times < retryCount))
    {
        AMSleep(1);
        times++;
    } 
    if (times >= retryCount) 
    {
        return;
    }
    
    if (eAIM_RESULT_OK  != IAIM_GetTopGroups(pIM, &pGrps, &iCount)
        || (pGrps == AMNULL) ) 
    {
            return;
    }
   
    for(int i=0; i<iCount; i++)
    {
        
        IAIMGroup_GetID(pGrps[i], &iGrpId);
            
        AMHandle *phCnts = AMNULL;
        AMInt32 iCount_contacts = 0;
        const AMChar    *szCntName = AMNULL;
            
        IAIMGroup_GetContacts(pGrps[i], AMFALSE, &phCnts, &iCount_contacts);
        
        for(int i=0; i<iCount_contacts; i++) 
        {
            
            IAIMContact_GetID(phCnts[i], &szCntName);
            IAIM_GetContactByID(pIM, szCntName, (AMHandle *)&pCnt);
            
            CContactInfo contactInfo;
            contactInfo.m_strUid = szCntName;
            contactInfo.m_groupId = iGrpId;
            contactInfo.m_strNickName = pCnt->szName;
            retContactList.push_back(contactInfo);
            
        }
        
    }
    
    IAIM_ReleaseTopGroups(pIM, pGrps, iCount);
    
    if (g_pCallback)
    {
        g_pCallback->OnReturnContactList(retContactList,pIM->pAcnt->iContactStamp);
    }
    
	return ;
    
}

void CWangWangNetLib::RequestGetContactStatusList()
{
    
}

void CWangWangNetLib::GetContactStatus(const std::string& strContactId)
{
    IAIM *pIM = (IAIM *)hIM;
    IAContact *pCnt = AMNULL;

    AMAssert(0 != pIM && 0 != strContactId.c_str());
    
    IAIM_GetContactByID(pIM, strContactId.c_str(), (AMHandle *)&pCnt);

    if(0 != pCnt) 
    {

        CContactStatus contactStatus;
		contactStatus.m_strUid = strContactId;
        contactStatus.m_defaultPresence=(EnLoginStatus)pCnt->ePresence;

        if (g_pCallback)
        {
            g_pCallback->OnReturnGetContactStatus(contactStatus);  
        
        }
    }
}

//发送文本消息给好友
void CWangWangNetLib::SendTextMsg(const CTextMsg& textMsg)
{
    //IAIM_SendMessage(hIM, (textMsg.m_strPeerContactId).c_str(), (textMsg.m_strTextContent).c_str());
    IAIM_SendMessageEx(hIM, (textMsg.m_strPeerContactId).c_str(), (textMsg.m_strTextContent).c_str(), 0);
}


void CWangWangNetLib::GetContactDetailInfo(const std::string& strUid)
{
    IAIM_GetProfile(hIM, strUid.c_str());
}

void CWangWangNetLib::SetSelfDetailInfo(const CContactPersonalDetailInfo& detailInfo)
{
	//return m_spNetLibImpl->SetSelfDetailInfo(detailInfo);
}


void CWangWangNetLib::ChangeSelfSignature(const std::string& strSignature)
{
    if(strSignature == "clear")
        IAIM_ChangeSignature(hIM, "");
    else
        IAIM_ChangeSignature(hIM, strSignature.c_str());
}


void CWangWangNetLib:: GetSignature(const std::string& strUid, unsigned int count)
{
    IAIM_GetSignature(hIM, strUid.c_str(), count);
    return;
}

void CWangWangNetLib::ParseSignatures(const std::string& strSignature, UidSignatures_t& uidSigs)
{
	//return m_spNetLibImpl->ParseSignatures(strSignature, uidSigs);
}

void CWangWangNetLib::DeleteBlackListContact(const std::string& strUid)
{
    IAIM_RemoveBlack(hIM, strUid.c_str());
}

void CWangWangNetLib::AddContact2BlackList(const std::string& strUid)
{
    AIM_RESULT ret;
    ret= IAIM_AddBlack(hIM, strUid.c_str());  
}

////请求得到黑名单列表
//void CWangWangNetLib::RequestGetBlackList()
//{
//	//m_spNetLibImpl->RequestGetBlackList();
//}

//搜索关键字相关的联系人
void CWangWangNetLib::SearchConacts(const std::string& strKeyword, uint32_t nTimestamp)
{
	IAIM_SearchUser(hIM, strKeyword.c_str());
}

//添加联系人
void CWangWangNetLib::AddContact(const std::string& strContactId)
{
    IAIM_AddContact(hIM, strContactId.c_str());
}

void CWangWangNetLib::CheckAuthCode(const std::string& strUserInputAuthCode)
{
	//return m_spNetLibImpl->CheckAuthCode(strUserInputAuthCode);
}

//如果对方设置为“加我为好友，需要我的验证“，这个接口则用来设置想对对方说的话，如表明自己的身份等等
void CWangWangNetLib::SendAddContactAuthenticationWords(const std::string& strContactId, const std::string& strAuthenticationWords)
{
	IAIM_SendVerify(hIM, strContactId.c_str(), strAuthenticationWords.c_str());
}

void CWangWangNetLib::acceptAddContact(const std::string& strCnt)
{
    IAIM_AcceptAddContact(hIM, (const AMChar *)strCnt.c_str());
}

void CWangWangNetLib::rejectAddContact(const std::string& strCnt, const std::string& strContent)
{
    IAIM_RejectAddContact(hIM, (const AMChar *)strCnt.c_str(),  (const AMChar *)strContent.c_str());
}

void CWangWangNetLib::ChangeAddedAuthFlag(EnAddedAuthFlag enNewAddedAuthFlag)
{
	IAIM_ChangeVerify(hIM, enNewAddedAuthFlag);
}


void CWangWangNetLib::DeleteContact(const std::string& strUid)
{
    IAIM_RemoveContact(hIM, strUid.c_str());
}

void CWangWangNetLib::ChangeSelfStatus(EnDetailStatus status)
{
	IAIM_ChangePresence(hIM,  (AIM_PRESENCE)status);
}

//发送文件
//strPicFileName是iphone app里自己bundle里的全路径，非局部路径
void CWangWangNetLib::SendFile(const std::string& strPeerId, const std::string& strFileFullName)
{
    IAIM_SendFile(hIM, strPeerId.c_str(), strFileFullName.c_str(), 0);
}

//接收文件
void CWangWangNetLib::recvFile(const std::string& strPeerId, const std::string& strFileNameToRecv , const std::string& strSaveFileName)
{
    IAIM_ReceiveFile(hIM, strPeerId.c_str(), strFileNameToRecv.c_str(), strSaveFileName.c_str(), 0);
}

//for test
void CWangWangNetLib::wwtest(const std::string uid)
{
  
    
}



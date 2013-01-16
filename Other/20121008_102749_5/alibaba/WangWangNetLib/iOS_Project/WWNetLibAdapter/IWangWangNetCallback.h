
/*
 *  IWangWangNetCallback.h
 * 
 *  Created on  : 2012-06-11
 *  Author      : tom.lih
 */

#ifndef IWANGWANG_NET_CALLBACK_H
#define IWANGWANG_NET_CALLBACK_H

#include "IAIMCallback.h"
#include "ErrorCodeDefs.h"
#include "LoginDataStructDefs.h"

#define RESULT_OKEY         0
#define RESULT_FAILED       -1 

//please implement this callback interface
//the framwork will notify the client through this interface
class IWangWangNetCallback
{
public:
	IWangWangNetCallback()
	{}
	
	virtual ~IWangWangNetCallback()
	{}
    
public:
	//notify the login result
	//login result has been seperated into two steps:checkversion && auth
	//when the loginStep == auth, you can use the loginFinalResult to get some extra result
	virtual void OnLoginResult(int errCode,								
							   EnLoginStep loginStep,							
							   const CLoginFinalResult& loginFinalResult) = 0;	
    
    
    //return the grouplist && the group timestamp
	virtual void OnReturnGroupList(const GroupList_t& groupList, uint32_t nGroupListTimestamp) = 0;
    
	//return the contactlist && the contact list timestamp
	virtual void OnReturnContactList(const ContactList_t& contactList, uint32_t nContactListTimestamp) = 0;
    
    //登录的时候，返回联系人的状态
    virtual void OnReturnContactStatus(const ContactStatusList_t& contactStatusList) = 0;
    
    //返回联系人的状态
	virtual void OnReturnGetContactStatus(const CContactStatus& contactStatus) = 0;
    
    //收到对方的文本消息
	virtual void OnRecvTextMsg(const CTextMsg& textMsg) = 0;
    
    virtual void OnRecvSysMsg(const CTextMsg& sysMsg) = 0;

    
    virtual void OnReturnLoginUserPersonalDetailInfo(const CContactPersonalDetailInfo& personalDetailInfo) = 0;
    
   	//返回联系人或自己的详细信息，如生肖，星座等等
	virtual void OnReturnContactPersonalDetailInfo(CContactPersonalDetailInfo& detailInfo) = 0; 
    
    //更改签名的返回值  NO_ERROR表示成功
	virtual void OnChangeSelfSignature(int enErrCode) = 0;
	
	//联系人的签名发生了变化
	//strContactId,签名发生变化的联系人id
	//strNewSignature, 新的签名
	virtual void OnContactSignatureChanged(const std::string& strContactId, const std::string& strNewSignature) = 0;
     
	//得到离线消息
	virtual void OnRecvOffLineMsgs(const TextMsgList_t&  offLineMsgs) = 0;
	
	//得到离线添加好友请求
	virtual void OnRecvOfflineContactMsg(const std::string& strUid, const std::string& strMessage) = 0;
	
	//收到离线系统消息
	virtual void OnRecvOfflineSystemMsg(const std::string& strMessage) = 0;

    virtual void OnReturnAddBlack(int enErrCode, const std::string& strUid) = 0;
	
    //删除黑名单里的用户的回调接口
    virtual void OnDeleteBlackListContact(const std::string& strUid, int enErrCode) = 0;
    
    virtual void OnGetSignature(UidSignatures_t & uidSigs) = 0;
    
    //发生了网络错误，譬如网络断线等等，必须切换界面到登录界面上去
	virtual void OnNetworkError() = 0;
	
	//被踢下线,相同的帐号在其他地方登录了
	virtual void OnForceDisconnect() = 0;
    
    //一些联系人状态发生变化的通知
	//typedef std::vector<CContactStatus>			ContactStatusList_t;
    virtual void OnContactStatusChanged(const ContactStatusList_t& contactStatusList)= 0;
    
    //删除联系人的返回结果
	//enErrCode = NO_ERROR表示删除成功，其他值都表示失败
	//只有操作成功，其他参数（strUid)才有意义
	virtual void OnReturnDeleteContact(int enErrCode, const std::string& strUid) = 0;
    
    virtual void OnAddContactResult(const CAddedContact& addedContact, int enErrCode, const std::string& strDenyWords) = 0;
    
    virtual void OnReturnSearchContacts(const SearchContactList_t& searchContactList, uint32_t nTimestamp) =0;
    
    //被好友添加成功了
	virtual void OnMyselfAdded(const std::string& strPeerId) = 0;
	
	//好友请求添加我为好友
	//strAuthenticationWords为好友发送的验证的话
	virtual void OnRequestAddMyself(const std::string& strPeerId, const std::string& strAuthenticationWords) = 0;
    
	virtual void OnNtfDataReady(int iType) = 0;
    
    virtual void OnCallBackTest() = 0; 
    
};   


#endif //IWANGWANG_NET_CALLBACK_H
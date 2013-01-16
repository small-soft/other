/*
 *  WangWangNetLib.h
 * 
 *  Created on  : 2012-06-11
 *  Author      : tom.lih
 */

#ifndef WANGWANG_NET_LIB_H
#define WANGWANG_NET_LIB_H


#include "LoginDataStructDefs.h"
#include "IWangWangNetCallback.h"
#include "AccountUtils.h"

class CWangWangNetLibImpl;

//该类是客户端底层库的框架类，必须保证全局只有唯一一个该对象
//todo use singleton design pattern
class CWangWangNetLib
{
public:
	CWangWangNetLib();
	~CWangWangNetLib();
    
public:
	//启动框架,全局在程序开始的时候调用一次
	//void Start(IWangWangNetCallback* pCallback);
    void Start(IWangWangNetCallback* pCallback, const std::string& dbPath);
    
	//关闭框架运行，全局在程序结束的时候调用一次
	void Stop();
    
	//开始登陆，登陆的两个参数请看参数的具体定义
	void Login(IWangWangNetCallback* pCallback, const std::string& dbPath,
               const CWangWangEnviroment& wangwangEnviroment,
			   const CLoginUserLoginInfo& loginUserLoginInfo);
	
	//注销，直接认为成功，不会有回调通知
	void LogOff();
    
    
    //请求得到组列表，返回值在IWangWangNetCallback的OnReturnGroupList中得到,不再主动推送给客户端
	void RequestGetGroupList();
	
	//请求得到联系人列表
	void RequestGetContactList();
    //登录的时候请求得到联系人的状态
	void RequestGetContactStatusList();
    
    //获取指定联系人的状态
	void GetContactStatus(const std::string& strContactId);

    //发送文本消息给好友
	void SendTextMsg(const CTextMsg& textMsg);

    
    //获取联系人的详细信息，如果是获取自己的详细信息，strUid填写自己的Uid
	void GetContactDetailInfo(const std::string& strUid);
    
	//设置自己的详细信息
	void SetSelfDetailInfo(const CContactPersonalDetailInfo& detailInfo);
    
    
    //获取联系人的签名的
	void GetSignature(const std::string& strUid, unsigned int count);
    
	//解析从web服务器上得到的签名信息,从而得到与联系人uid对应的签名信息
	void ParseSignatures(const std::string& strSignature, UidSignatures_t& uidSigs);
	
	//修改自己的签名
	void ChangeSelfSignature(const std::string& strSignature);
    
    void DeleteBlackListContact(const std::string& strUid); 
    
    void AddContact2BlackList(const std::string& strUid);    
    //请求得到黑名单列表
    //void RequestGetBlackList(); 

    //搜索关键字相关的联系人
    void SearchConacts(const std::string& strKeyword, uint32_t nTimestamp);
    
    //添加联系人
    void AddContact(const std::string& strContactId);
    
    void CheckAuthCode(const std::string& strUserInputAuthCode);
 
    void acceptAddContact(const std::string& strCnt);
    
    void rejectAddContact(const std::string& strCnt, const std::string& strContent);
    
    //如果对方设置为“加我为好友，需要我的验证“，这个接口则用来设置想对对方说的话，如表明自己的身份等等
    void SendAddContactAuthenticationWords(const std::string& strContactId, const std::string& strAuthenticationWords);
    
    //更改自己好友添加的验证方式
	void ChangeAddedAuthFlag(EnAddedAuthFlag enNewAddedAuthFlag);
    
    void DeleteContact(const std::string& strUid);
    
    void ChangeSelfStatus(EnDetailStatus status);
    
    //发送文件
    //strPicFileName是iphone app里自己bundle里的全路径，非局部路径
    void SendFile(const std::string& strPeerId, const std::string& strFileFullName);
    
    //接收文件
    void recvFile(const std::string& strPeerId, const std::string& strFileNameToRecv , const std::string& strSaveFileName);
    
    void wwtest(const std::string uid);
    
private:
    void *	hIM; 

};


#endif //WANGWANG_NET_LIB_H
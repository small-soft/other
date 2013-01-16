#ifndef XUMINGGANG_IM_LOGINUTILS_H
#define XUMINGGANG_IM_LOGINUTILS_H

#include "IPacketHandler.h"
#include "LoginDataStructDefs.h"

class CImRspLogin;

class CLoginUtils: public IPacketHandler
{
public:
	void Login(const CWangWangEnviroment& wwEnv, const CLoginUserLoginInfo& loginInfo, 
			   IPacketMgr* pPackMgr);
	
//	void SecurityLogin(int iLoginType, int iLoginStep, string strToken);	
//	virtual void OnPacket(uint32_t nCmd, const CScHead& header, std::string& pack);
	
	std::string GetMsgEncKey() const;
	
	std::string GetSessionNo() const;
	
	std::string GetLoginUid() const;
	
	void LogOff();
	
private:
	bool CheckVersion();
	
	int ConvertClientStatus2ServerStatus(int nClientState);
	void NeedSecurityLogin(const CImRspLogin& rsp);
	void InitFromLoginrsp(const CImRspLogin& rsp, CLoginFinalResult& finalResult);
	
private:
	CWangWangEnviroment								m_wwEnv;
	CLoginUserLoginInfo								m_loginInfo;
	std::string m_strKey;
	uint32_t m_wConnectNo;
	std::string m_pubKey;
	std::string m_uid;
	std::string m_rid;
	uint32_t m_dwTimeStampsFlag;
	std::string m_pass;	
	int m_passtype;
	std::string m_strSessionNo;
};

#endif //XUMINGGANG_IM_LOGINUTILS_H



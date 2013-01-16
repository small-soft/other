/*---------------------------------------------------------------------------
// Filename:        imsc_pack.h
// Date:            2009-08-25 09:18:13
// Author:          autogen 
// Note:            this is a auto-generated file, DON'T MODIFY IT!
//---------------------------------------------------------------------------*/
#ifndef __IMSC_PACK_H__
#define __IMSC_PACK_H__

#include <string>
#include <vector>
#include <map>
#include "packdata.h"
#include "des.h"
#include "zlib.h"
#include "sc_head.h"
#include "const_macro.h"
#include "imsc_cmd.h"

#define PROTOCOL_LIB
using namespace std;

#ifndef STATUSDEF_LENGTH
#define STATUSDEF_LENGTH 64
#endif 

//#define USER_OLD_UDB_PROFILE_PROTOCOL

class PROTOCOL_LIB CImHelthCheck : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_HELTH_CHECK
    };
    CImHelthCheck()
    {
    }

    ~CImHelthCheck() { }
public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImHelthCheck::Size() const
{
    return 1;
}
class PROTOCOL_LIB CImReqCheckversion : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHECKVERSION
    };
    CImReqCheckversion()
    {
    }

    ~CImReqCheckversion() { }
    CImReqCheckversion(const string&  strVersion)
    {
        m_version = strVersion;
    }
    CImReqCheckversion&  operator=( const CImReqCheckversion&  cImReqCheckversion )
    {
        m_version = cImReqCheckversion.m_version;
        return *this;
    }

    const string&  GetVersion () const { return m_version; }
    bool SetVersion ( const string&  strVersion )
    {
        if(strVersion.size() > 128)
            return false;
        m_version = strVersion;
        return true;
    }
private:
    string m_version;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqCheckversion::Size() const
{
    uint32_t nSize = 6;
    nSize += m_version.length();
    return nSize;
}

class PROTOCOL_LIB CImRspCheckversion : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHECKVERSION
    };
    CImRspCheckversion()
    {
    }

    ~CImRspCheckversion() { }
    CImRspCheckversion(const uint32_t&  dwRetcode, const string&  strRemark, const uint32_t&  dwConnectNo, const string&  strPubkey)
    {
        m_retcode = dwRetcode;
        m_remark = strRemark;
        m_connectNo = dwConnectNo;
        m_pubkey = strPubkey;
    }
    CImRspCheckversion&  operator=( const CImRspCheckversion&  cImRspCheckversion )
    {
        m_retcode = cImRspCheckversion.m_retcode;
        m_remark = cImRspCheckversion.m_remark;
        m_connectNo = cImRspCheckversion.m_connectNo;
        m_pubkey = cImRspCheckversion.m_pubkey;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetRemark () const { return m_remark; }
    bool SetRemark ( const string&  strRemark )
    {
        if(strRemark.size() > 256)
            return false;
        m_remark = strRemark;
        return true;
    }
    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetPubkey () const { return m_pubkey; }
    bool SetPubkey ( const string&  strPubkey )
    {
        m_pubkey = strPubkey;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_remark;
    uint32_t m_connectNo;
    string m_pubkey;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspCheckversion::Size() const
{
    uint32_t nSize = 21;
    nSize += m_remark.length();
    nSize += m_pubkey.length();
    return nSize;
}

class PROTOCOL_LIB CImReqPrelogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_PRELOGIN
    };
    CImReqPrelogin()
    {
    }

    ~CImReqPrelogin() { }
    CImReqPrelogin(const uint32_t&  dwConnectNo, const string&  strWorkKey, const string&  strStrlogin)
    {
        m_connectNo = dwConnectNo;
        m_workKey = strWorkKey;
        m_strlogin = strStrlogin;
    }
    CImReqPrelogin&  operator=( const CImReqPrelogin&  cImReqPrelogin )
    {
        m_connectNo = cImReqPrelogin.m_connectNo;
        m_workKey = cImReqPrelogin.m_workKey;
        m_strlogin = cImReqPrelogin.m_strlogin;
        return *this;
    }

    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetWorkKey () const { return m_workKey; }
    bool SetWorkKey ( const string&  strWorkKey )
    {
        if(strWorkKey.size() > 128)
            return false;
        m_workKey = strWorkKey;
        return true;
    }
    const string&  GetStrlogin () const { return m_strlogin; }
    bool SetStrlogin ( const string&  strStrlogin )
    {
        m_strlogin = strStrlogin;
        return true;
    }
private:
    uint32_t m_connectNo;
    string m_workKey;
    string m_strlogin;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqPrelogin::Size() const
{
    uint32_t nSize = 16;
    nSize += m_workKey.length();
    nSize += m_strlogin.length();
    return nSize;
}

class PROTOCOL_LIB CImReqLogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_LOGIN
    };
    CImReqLogin() : m_rid("magic")
    {
    }

    ~CImReqLogin() { }
    CImReqLogin(const uint8_t&  chTokenFlag, const uint32_t&  dwConnectNo, const string&  strPassword, const string&  strVersion, const uint32_t&  dwLanguage, const uint32_t&  dwTimestampFlag, const VECTOR< uint32_t >&  vecTimestampList, const VECTOR< string >&  vecHardcode, const string&  strHardcheck, const string&  strRid)
    {
        m_tokenFlag = chTokenFlag;
        m_connectNo = dwConnectNo;
        m_password = strPassword;
        m_version = strVersion;
        m_language = dwLanguage;
        m_timestampFlag = dwTimestampFlag;
        m_timestampList = vecTimestampList;
        m_hardcode = vecHardcode;
        m_hardcheck = strHardcheck;
        m_rid = strRid;
    }
    CImReqLogin&  operator=( const CImReqLogin&  cImReqLogin )
    {
        m_tokenFlag = cImReqLogin.m_tokenFlag;
        m_connectNo = cImReqLogin.m_connectNo;
        m_password = cImReqLogin.m_password;
        m_version = cImReqLogin.m_version;
        m_language = cImReqLogin.m_language;
        m_timestampFlag = cImReqLogin.m_timestampFlag;
        m_timestampList = cImReqLogin.m_timestampList;
        m_hardcode = cImReqLogin.m_hardcode;
        m_hardcheck = cImReqLogin.m_hardcheck;
        m_rid = cImReqLogin.m_rid;
        return *this;
    }

    const uint8_t&  GetTokenFlag () const { return m_tokenFlag; }
    bool SetTokenFlag ( const uint8_t&  chTokenFlag )
    {
        m_tokenFlag = chTokenFlag;
        return true;
    }
    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetPassword () const { return m_password; }
    bool SetPassword ( const string&  strPassword )
    {
        if(strPassword.size() > 48)
            return false;
        m_password = strPassword;
        return true;
    }
    const string&  GetVersion () const { return m_version; }
    bool SetVersion ( const string&  strVersion )
    {
        if(strVersion.size() > 128)
            return false;
        m_version = strVersion;
        return true;
    }
    const uint32_t&  GetLanguage () const { return m_language; }
    bool SetLanguage ( const uint32_t&  dwLanguage )
    {
        m_language = dwLanguage;
        return true;
    }
    const uint32_t&  GetTimestampFlag () const { return m_timestampFlag; }
    bool SetTimestampFlag ( const uint32_t&  dwTimestampFlag )
    {
        m_timestampFlag = dwTimestampFlag;
        return true;
    }
    const VECTOR< uint32_t >&  GetTimestampList () const { return m_timestampList; }
    bool SetTimestampList ( const VECTOR< uint32_t >&  vecTimestampList )
    {
        m_timestampList = vecTimestampList;
        return true;
    }
    const VECTOR< string >&  GetHardcode () const { return m_hardcode; }
    bool SetHardcode ( const VECTOR< string >&  vecHardcode )
    {
        m_hardcode = vecHardcode;
        return true;
    }
    const string&  GetHardcheck () const { return m_hardcheck; }
    bool SetHardcheck ( const string&  strHardcheck )
    {
        m_hardcheck = strHardcheck;
        return true;
    }
    const string&  GetRid () const { return m_rid; }
    bool SetRid ( const string&  strRid )
    {
        m_rid = strRid;
        return true;
    }
private:
    uint8_t m_tokenFlag;
    uint32_t m_connectNo;
    string m_password;
    string m_version;
    uint32_t m_language;
    uint32_t m_timestampFlag;
    VECTOR< uint32_t > m_timestampList;
    VECTOR< string > m_hardcode;
    string m_hardcheck;
    string m_rid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqLogin::Size() const
{
    uint32_t nSize = 50;
    nSize += m_password.length();
    nSize += m_version.length();
    nSize += m_timestampList.size() * 4;
    nSize += m_hardcode.size() * 4;
    for(uint32_t i = 0; i < m_hardcode.size(); i++)
    {
        nSize += m_hardcode[i].length();
    }
    nSize += m_hardcheck.length();
    nSize += m_rid.length();
    return nSize;
}

class PROTOCOL_LIB CImReqPrelogin1 : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_PRELOGIN1
    };
    CImReqPrelogin1()
    {
    }

    ~CImReqPrelogin1() { }
    CImReqPrelogin1(const uint32_t&  dwConnectNo, const string&  strWorkKey, const string&  strStrlogin)
    {
        m_connectNo = dwConnectNo;
        m_workKey = strWorkKey;
        m_strlogin = strStrlogin;
    }
    CImReqPrelogin1&  operator=( const CImReqPrelogin1&  cImReqPrelogin1 )
    {
        m_connectNo = cImReqPrelogin1.m_connectNo;
        m_workKey = cImReqPrelogin1.m_workKey;
        m_strlogin = cImReqPrelogin1.m_strlogin;
        return *this;
    }

    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetWorkKey () const { return m_workKey; }
    bool SetWorkKey ( const string&  strWorkKey )
    {
        if(strWorkKey.size() > 128)
            return false;
        m_workKey = strWorkKey;
        return true;
    }
    const string&  GetStrlogin () const { return m_strlogin; }
    bool SetStrlogin ( const string&  strStrlogin )
    {
        m_strlogin = strStrlogin;
        return true;
    }
private:
    uint32_t m_connectNo;
    string m_workKey;
    string m_strlogin;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqPrelogin1::Size() const
{
    uint32_t nSize = 16;
    nSize += m_workKey.length();
    nSize += m_strlogin.length();
    return nSize;
}

class PROTOCOL_LIB CImRspLogin : public CPackData
{
public:
	enum
	{
		CMD_ID = IM_RSP_LOGIN
	};
	CImRspLogin() : m_lastLogintime(0)
	{
	}

	~CImRspLogin() { }
	CImRspLogin(const uint32_t&  dwRetcode, const uint32_t&  dwTimestampFlag, const uint32_t&  dwClientIp, const uint32_t&  dwServerTime, const string&  strWorkKey, const string&  strPwtoken, const string&  strRemark, const string&  strWebmd5pw, const uint32_t&  dwLastClientip, const string&  strBindid, const string&  strRid,const uint32_t&  dwLastLogintime)
	{
		m_retcode = dwRetcode;
		m_timestampFlag = dwTimestampFlag;
		m_clientIp = dwClientIp;
		m_serverTime = dwServerTime;
		m_workKey = strWorkKey;
		m_pwtoken = strPwtoken;
		m_remark = strRemark;
		m_webmd5pw = strWebmd5pw;
		m_lastClientip = dwLastClientip;
		m_bindid = strBindid;
		m_rid = strRid;
		m_lastLogintime = dwLastLogintime;
	}
	CImRspLogin&  operator=( const CImRspLogin&  cImRspLogin )
	{
		m_retcode = cImRspLogin.m_retcode;
		m_timestampFlag = cImRspLogin.m_timestampFlag;
		m_clientIp = cImRspLogin.m_clientIp;
		m_serverTime = cImRspLogin.m_serverTime;
		m_workKey = cImRspLogin.m_workKey;
		m_pwtoken = cImRspLogin.m_pwtoken;
		m_remark = cImRspLogin.m_remark;
		m_webmd5pw = cImRspLogin.m_webmd5pw;
		m_lastClientip = cImRspLogin.m_lastClientip;
		m_bindid = cImRspLogin.m_bindid;
		m_rid = cImRspLogin.m_rid;
		m_lastLogintime = cImRspLogin.m_lastLogintime;
		return *this;
	}

	const uint32_t&  GetRetcode () const { return m_retcode; }
	bool SetRetcode ( const uint32_t&  dwRetcode )
	{
		m_retcode = dwRetcode;
		return true;
	}
	const uint32_t&  GetTimestampFlag () const { return m_timestampFlag; }
	bool SetTimestampFlag ( const uint32_t&  dwTimestampFlag )
	{
		m_timestampFlag = dwTimestampFlag;
		return true;
	}
	const uint32_t&  GetClientIp () const { return m_clientIp; }
	bool SetClientIp ( const uint32_t&  dwClientIp )
	{
		m_clientIp = dwClientIp;
		return true;
	}
	const uint32_t&  GetServerTime () const { return m_serverTime; }
	bool SetServerTime ( const uint32_t&  dwServerTime )
	{
		m_serverTime = dwServerTime;
		return true;
	}
	const string&  GetWorkKey () const { return m_workKey; }
	bool SetWorkKey ( const string&  strWorkKey )
	{
		m_workKey = strWorkKey;
		return true;
	}
	const string&  GetPwtoken () const { return m_pwtoken; }
	bool SetPwtoken ( const string&  strPwtoken )
	{
		m_pwtoken = strPwtoken;
		return true;
	}
	const string&  GetRemark () const { return m_remark; }
	bool SetRemark ( const string&  strRemark )
	{
		if(strRemark.size() > 256)
			return false;
		m_remark = strRemark;
		return true;
	}
	const string&  GetWebmd5pw () const { return m_webmd5pw; }
	bool SetWebmd5pw ( const string&  strWebmd5pw )
	{
		m_webmd5pw = strWebmd5pw;
		return true;
	}
	const uint32_t&  GetLastClientip () const { return m_lastClientip; }
	bool SetLastClientip ( const uint32_t&  dwLastClientip )
	{
		m_lastClientip = dwLastClientip;
		return true;
	}
	const string&  GetBindid () const { return m_bindid; }
	bool SetBindid ( const string&  strBindid )
	{
		m_bindid = strBindid;
		return true;
	}
	const string&  GetRid () const { return m_rid; }
	bool SetRid ( const string&  strRid )
	{
		m_rid = strRid;
		return true;
	}
	const uint32_t&  GetLastLogintime () const { return m_lastLogintime; }
	bool SetLastLogintime ( const uint32_t&  dwLastLogintime )
	{
		m_lastLogintime = dwLastLogintime;
		return true;
	}
private:
	uint32_t m_retcode;
	uint32_t m_timestampFlag;
	uint32_t m_clientIp;
	uint32_t m_serverTime;
	string m_workKey;
	string m_pwtoken;
	string m_remark;
	string m_webmd5pw;
	uint32_t m_lastClientip;
	string m_bindid;
	string m_rid;
	uint32_t m_lastLogintime;

public:
	CScHead m_scHead;
	void PackHead(string& strData);
	void PackBody(string& strData);
	void PackData(string& strData, const string& strKey = "");
	PACKRETCODE UnpackBody(string& strData);
	PACKRETCODE UnpackData(string& strData, const string& strKey = "");
	uint32_t Size() const;
};

inline uint32_t CImRspLogin::Size() const
{
	uint32_t nSize = 61;
	nSize += m_workKey.length();
	nSize += m_pwtoken.length();
	nSize += m_remark.length();
	nSize += m_webmd5pw.length();
	nSize += m_bindid.length();
	nSize += m_rid.length();
	return nSize;
}

class PROTOCOL_LIB CImReqLogin2 : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_LOGIN2
    };
    CImReqLogin2()
    {
    }

    ~CImReqLogin2() { }
    CImReqLogin2(const uint32_t&  dwTimestampFlag, const VECTOR< uint32_t >&  vecTimestampList, const string&  strLoginToken)
    {
        m_timestampFlag = dwTimestampFlag;
        m_timestampList = vecTimestampList;
        m_loginToken = strLoginToken;
    }
    CImReqLogin2&  operator=( const CImReqLogin2&  cImReqLogin2 )
    {
        m_timestampFlag = cImReqLogin2.m_timestampFlag;
        m_timestampList = cImReqLogin2.m_timestampList;
        m_loginToken = cImReqLogin2.m_loginToken;
        return *this;
    }

    const uint32_t&  GetTimestampFlag () const { return m_timestampFlag; }
    bool SetTimestampFlag ( const uint32_t&  dwTimestampFlag )
    {
        m_timestampFlag = dwTimestampFlag;
        return true;
    }
    const VECTOR< uint32_t >&  GetTimestampList () const { return m_timestampList; }
    bool SetTimestampList ( const VECTOR< uint32_t >&  vecTimestampList )
    {
        m_timestampList = vecTimestampList;
        return true;
    }
    const string&  GetLoginToken () const { return m_loginToken; }
    bool SetLoginToken ( const string&  strLoginToken )
    {
        m_loginToken = strLoginToken;
        return true;
    }
private:
    uint32_t m_timestampFlag;
    VECTOR< uint32_t > m_timestampList;
    string m_loginToken;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqLogin2::Size() const
{
    uint32_t nSize = 17;
    nSize += m_timestampList.size() * 4;
    nSize += m_loginToken.length();
    return nSize;
}

class PROTOCOL_LIB CImRspLogin2 : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_LOGIN2
    };
    CImRspLogin2()
    {
    }

    ~CImRspLogin2() { }
    CImRspLogin2(const uint32_t&  dwRetcode, const uint32_t&  dwTimestampFlag, const string&  strRemark)
    {
        m_retcode = dwRetcode;
        m_timestampFlag = dwTimestampFlag;
        m_remark = strRemark;
    }
    CImRspLogin2&  operator=( const CImRspLogin2&  cImRspLogin2 )
    {
        m_retcode = cImRspLogin2.m_retcode;
        m_timestampFlag = cImRspLogin2.m_timestampFlag;
        m_remark = cImRspLogin2.m_remark;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint32_t&  GetTimestampFlag () const { return m_timestampFlag; }
    bool SetTimestampFlag ( const uint32_t&  dwTimestampFlag )
    {
        m_timestampFlag = dwTimestampFlag;
        return true;
    }
    const string&  GetRemark () const { return m_remark; }
    bool SetRemark ( const string&  strRemark )
    {
        if(strRemark.size() > 256)
            return false;
        m_remark = strRemark;
        return true;
    }
private:
    uint32_t m_retcode;
    uint32_t m_timestampFlag;
    string m_remark;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspLogin2::Size() const
{
    uint32_t nSize = 16;
    nSize += m_remark.length();
    return nSize;
}

class PROTOCOL_LIB CImReqPreloginAgain : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_PRELOGIN_AGAIN
    };
    CImReqPreloginAgain()
    {
    }

    ~CImReqPreloginAgain() { }
    CImReqPreloginAgain(const uint32_t&  dwConnectNo, const string&  strWorkKey, const string&  strStrloginagin)
    {
        m_connectNo = dwConnectNo;
        m_workKey = strWorkKey;
        m_strloginagin = strStrloginagin;
    }
    CImReqPreloginAgain&  operator=( const CImReqPreloginAgain&  cImReqPreloginAgain )
    {
        m_connectNo = cImReqPreloginAgain.m_connectNo;
        m_workKey = cImReqPreloginAgain.m_workKey;
        m_strloginagin = cImReqPreloginAgain.m_strloginagin;
        return *this;
    }

    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetWorkKey () const { return m_workKey; }
    bool SetWorkKey ( const string&  strWorkKey )
    {
        if(strWorkKey.size() > 128)
            return false;
        m_workKey = strWorkKey;
        return true;
    }
    const string&  GetStrloginagin () const { return m_strloginagin; }
    bool SetStrloginagin ( const string&  strStrloginagin )
    {
        m_strloginagin = strStrloginagin;
        return true;
    }
private:
    uint32_t m_connectNo;
    string m_workKey;
    string m_strloginagin;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqPreloginAgain::Size() const
{
    uint32_t nSize = 16;
    nSize += m_workKey.length();
    nSize += m_strloginagin.length();
    return nSize;
}

class PROTOCOL_LIB CImReqLoginAgain : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_LOGIN_AGAIN
    };
    CImReqLoginAgain()
    {
    }

    ~CImReqLoginAgain() { }
    CImReqLoginAgain(const uint8_t&  chTokenFlag, const uint32_t&  dwConnectNo, const string&  strPassword, const string&  strVersion, const uint32_t&  dwLanguage, const VECTOR< string >&  vecHardcode, const string&  strHardcheck, const uint8_t&  chBasicStatus, const uint8_t&  chPredefStatus, const string&  strPwcode)
    {
        m_tokenFlag = chTokenFlag;
        m_connectNo = dwConnectNo;
        m_password = strPassword;
        m_version = strVersion;
        m_language = dwLanguage;
        m_hardcode = vecHardcode;
        m_hardcheck = strHardcheck;
        m_basicStatus = chBasicStatus;
        m_predefStatus = chPredefStatus;
        m_pwcode = strPwcode;
    }
    CImReqLoginAgain&  operator=( const CImReqLoginAgain&  cImReqLoginAgain )
    {
        m_tokenFlag = cImReqLoginAgain.m_tokenFlag;
        m_connectNo = cImReqLoginAgain.m_connectNo;
        m_password = cImReqLoginAgain.m_password;
        m_version = cImReqLoginAgain.m_version;
        m_language = cImReqLoginAgain.m_language;
        m_hardcode = cImReqLoginAgain.m_hardcode;
        m_hardcheck = cImReqLoginAgain.m_hardcheck;
        m_basicStatus = cImReqLoginAgain.m_basicStatus;
        m_predefStatus = cImReqLoginAgain.m_predefStatus;
        m_pwcode = cImReqLoginAgain.m_pwcode;
        return *this;
    }

    const uint8_t&  GetTokenFlag () const { return m_tokenFlag; }
    bool SetTokenFlag ( const uint8_t&  chTokenFlag )
    {
        m_tokenFlag = chTokenFlag;
        return true;
    }
    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetPassword () const { return m_password; }
    bool SetPassword ( const string&  strPassword )
    {
        if(strPassword.size() > 48)
            return false;
        m_password = strPassword;
        return true;
    }
    const string&  GetVersion () const { return m_version; }
    bool SetVersion ( const string&  strVersion )
    {
        if(strVersion.size() > 128)
            return false;
        m_version = strVersion;
        return true;
    }
    const uint32_t&  GetLanguage () const { return m_language; }
    bool SetLanguage ( const uint32_t&  dwLanguage )
    {
        m_language = dwLanguage;
        return true;
    }
    const VECTOR< string >&  GetHardcode () const { return m_hardcode; }
    bool SetHardcode ( const VECTOR< string >&  vecHardcode )
    {
        m_hardcode = vecHardcode;
        return true;
    }
    const string&  GetHardcheck () const { return m_hardcheck; }
    bool SetHardcheck ( const string&  strHardcheck )
    {
        m_hardcheck = strHardcheck;
        return true;
    }
    const uint8_t&  GetBasicStatus () const { return m_basicStatus; }
    bool SetBasicStatus ( const uint8_t&  chBasicStatus )
    {
        m_basicStatus = chBasicStatus;
        return true;
    }
    const uint8_t&  GetPredefStatus () const { return m_predefStatus; }
    bool SetPredefStatus ( const uint8_t&  chPredefStatus )
    {
        m_predefStatus = chPredefStatus;
        return true;
    }
    const string&  GetPwcode () const { return m_pwcode; }
    bool SetPwcode ( const string&  strPwcode )
    {
        m_pwcode = strPwcode;
        return true;
    }
private:
    uint8_t m_tokenFlag;
    uint32_t m_connectNo;
    string m_password;
    string m_version;
    uint32_t m_language;
    VECTOR< string > m_hardcode;
    string m_hardcheck;
    uint8_t m_basicStatus;
    uint8_t m_predefStatus;
    string m_pwcode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqLoginAgain::Size() const
{
    uint32_t nSize = 43;
    nSize += m_password.length();
    nSize += m_version.length();
    nSize += m_hardcode.size() * 4;
    for(uint32_t i = 0; i < m_hardcode.size(); i++)
    {
        nSize += m_hardcode[i].length();
    }
    nSize += m_hardcheck.length();
    nSize += m_pwcode.length();
    return nSize;
}

class PROTOCOL_LIB CImRspLoginAgain : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_LOGIN_AGAIN
    };
    CImRspLoginAgain()
    {
    }

    ~CImRspLoginAgain() { }
    CImRspLoginAgain(const uint32_t&  dwRetcode, const string&  strWorkKey, const string&  strRemark)
    {
        m_retcode = dwRetcode;
        m_workKey = strWorkKey;
        m_remark = strRemark;
    }
    CImRspLoginAgain&  operator=( const CImRspLoginAgain&  cImRspLoginAgain )
    {
        m_retcode = cImRspLoginAgain.m_retcode;
        m_workKey = cImRspLoginAgain.m_workKey;
        m_remark = cImRspLoginAgain.m_remark;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetWorkKey () const { return m_workKey; }
    bool SetWorkKey ( const string&  strWorkKey )
    {
        m_workKey = strWorkKey;
        return true;
    }
    const string&  GetRemark () const { return m_remark; }
    bool SetRemark ( const string&  strRemark )
    {
        if(strRemark.size() > 256)
            return false;
        m_remark = strRemark;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_workKey;
    string m_remark;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspLoginAgain::Size() const
{
    uint32_t nSize = 16;
    nSize += m_workKey.length();
    nSize += m_remark.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfLoginAgain : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_LOGIN_AGAIN
    };
    CImNtfLoginAgain()
    {
    }

    ~CImNtfLoginAgain() { }
    CImNtfLoginAgain(const string&  strPwcode)
    {
        m_pwcode = strPwcode;
    }
    CImNtfLoginAgain&  operator=( const CImNtfLoginAgain&  cImNtfLoginAgain )
    {
        m_pwcode = cImNtfLoginAgain.m_pwcode;
        return *this;
    }

    const string&  GetPwcode () const { return m_pwcode; }
    bool SetPwcode ( const string&  strPwcode )
    {
        m_pwcode = strPwcode;
        return true;
    }
private:
    string m_pwcode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfLoginAgain::Size() const
{
    uint32_t nSize = 6;
    nSize += m_pwcode.length();
    return nSize;
}

class PROTOCOL_LIB CImReqPostlogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_POSTLOGIN
    };
    CImReqPostlogin()
    {
    }

    ~CImReqPostlogin() { }
    CImReqPostlogin(const uint8_t&  chBasicStatus, const uint8_t&  chPredefStatus)
    {
        m_basicStatus = chBasicStatus;
        m_predefStatus = chPredefStatus;
    }
    CImReqPostlogin&  operator=( const CImReqPostlogin&  cImReqPostlogin )
    {
        m_basicStatus = cImReqPostlogin.m_basicStatus;
        m_predefStatus = cImReqPostlogin.m_predefStatus;
        return *this;
    }

    const uint8_t&  GetBasicStatus () const { return m_basicStatus; }
    bool SetBasicStatus ( const uint8_t&  chBasicStatus )
    {
        m_basicStatus = chBasicStatus;
        return true;
    }
    const uint8_t&  GetPredefStatus () const { return m_predefStatus; }
    bool SetPredefStatus ( const uint8_t&  chPredefStatus )
    {
        m_predefStatus = chPredefStatus;
        return true;
    }
private:
    uint8_t m_basicStatus;
    uint8_t m_predefStatus;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqPostlogin::Size() const
{
    return 5;
}
class PROTOCOL_LIB CImReqRelogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_RELOGIN
    };
    CImReqRelogin()
    {
    }

    ~CImReqRelogin() { }
    CImReqRelogin(const string&  strPassword, const string&  strVersion, const uint32_t&  dwConnectNo, const uint8_t&  chBasicStatus, const uint8_t&  chPredefStatus)
    {
        m_password = strPassword;
        m_version = strVersion;
        m_connectNo = dwConnectNo;
        m_basicStatus = chBasicStatus;
        m_predefStatus = chPredefStatus;
    }
    CImReqRelogin&  operator=( const CImReqRelogin&  cImReqRelogin )
    {
        m_password = cImReqRelogin.m_password;
        m_version = cImReqRelogin.m_version;
        m_connectNo = cImReqRelogin.m_connectNo;
        m_basicStatus = cImReqRelogin.m_basicStatus;
        m_predefStatus = cImReqRelogin.m_predefStatus;
        return *this;
    }

    const string&  GetPassword () const { return m_password; }
    bool SetPassword ( const string&  strPassword )
    {
        if(strPassword.size() > 48)
            return false;
        m_password = strPassword;
        return true;
    }
    const string&  GetVersion () const { return m_version; }
    bool SetVersion ( const string&  strVersion )
    {
        if(strVersion.size() > 128)
            return false;
        m_version = strVersion;
        return true;
    }
    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const uint8_t&  GetBasicStatus () const { return m_basicStatus; }
    bool SetBasicStatus ( const uint8_t&  chBasicStatus )
    {
        m_basicStatus = chBasicStatus;
        return true;
    }
    const uint8_t&  GetPredefStatus () const { return m_predefStatus; }
    bool SetPredefStatus ( const uint8_t&  chPredefStatus )
    {
        m_predefStatus = chPredefStatus;
        return true;
    }
private:
    string m_password;
    string m_version;
    uint32_t m_connectNo;
    uint8_t m_basicStatus;
    uint8_t m_predefStatus;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqRelogin::Size() const
{
    uint32_t nSize = 20;
    nSize += m_password.length();
    nSize += m_version.length();
    return nSize;
}

class PROTOCOL_LIB CImRspRelogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_RELOGIN
    };
    CImRspRelogin()
    {
    }

    ~CImRspRelogin() { }
    CImRspRelogin(const uint32_t&  dwRetcode, const uint32_t&  dwConnectNo, const string&  strRemark)
    {
        m_retcode = dwRetcode;
        m_connectNo = dwConnectNo;
        m_remark = strRemark;
    }
    CImRspRelogin&  operator=( const CImRspRelogin&  cImRspRelogin )
    {
        m_retcode = cImRspRelogin.m_retcode;
        m_connectNo = cImRspRelogin.m_connectNo;
        m_remark = cImRspRelogin.m_remark;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint32_t&  GetConnectNo () const { return m_connectNo; }
    bool SetConnectNo ( const uint32_t&  dwConnectNo )
    {
        m_connectNo = dwConnectNo;
        return true;
    }
    const string&  GetRemark () const { return m_remark; }
    bool SetRemark ( const string&  strRemark )
    {
        if(strRemark.size() > 256)
            return false;
        m_remark = strRemark;
        return true;
    }
private:
    uint32_t m_retcode;
    uint32_t m_connectNo;
    string m_remark;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspRelogin::Size() const
{
    uint32_t nSize = 16;
    nSize += m_remark.length();
    return nSize;
}

class PROTOCOL_LIB CImReqLogoff : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_LOGOFF
    };
    CImReqLogoff()
    {
    }

    ~CImReqLogoff() { }
public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqLogoff::Size() const
{
    return 1;
}
class PROTOCOL_LIB CImRspLogoff : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_LOGOFF
    };
    CImRspLogoff()
    {
    }

    ~CImRspLogoff() { }
    CImRspLogoff(const uint32_t&  dwRetcode, const string&  strRemark)
    {
        m_retcode = dwRetcode;
        m_remark = strRemark;
    }
    CImRspLogoff&  operator=( const CImRspLogoff&  cImRspLogoff )
    {
        m_retcode = cImRspLogoff.m_retcode;
        m_remark = cImRspLogoff.m_remark;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetRemark () const { return m_remark; }
    bool SetRemark ( const string&  strRemark )
    {
        if(strRemark.size() > 256)
            return false;
        m_remark = strRemark;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_remark;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspLogoff::Size() const
{
    uint32_t nSize = 11;
    nSize += m_remark.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfForcedisconnect : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_FORCEDISCONNECT
    };
    CImNtfForcedisconnect()
    {
    }

    ~CImNtfForcedisconnect() { }
    CImNtfForcedisconnect(const uint8_t&  chType, const string&  strRemark)
    {
        m_type = chType;
        m_remark = strRemark;
    }
    CImNtfForcedisconnect&  operator=( const CImNtfForcedisconnect&  cImNtfForcedisconnect )
    {
        m_type = cImNtfForcedisconnect.m_type;
        m_remark = cImNtfForcedisconnect.m_remark;
        return *this;
    }

    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetRemark () const { return m_remark; }
    bool SetRemark ( const string&  strRemark )
    {
        if(strRemark.size() > 256)
            return false;
        m_remark = strRemark;
        return true;
    }
private:
    uint8_t m_type;
    string m_remark;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfForcedisconnect::Size() const
{
    uint32_t nSize = 8;
    nSize += m_remark.length();
    return nSize;
}

struct SUserGroup
{
public:
    SUserGroup()
    {
    }

    ~SUserGroup() { }
    SUserGroup(const int64_t&  llGroupId, const int64_t&  llParentId, const string&  strGroupName)
    {
        m_groupId = llGroupId;
        m_parentId = llParentId;
        m_groupName = strGroupName;
    }
    SUserGroup&  operator=( const SUserGroup&  sUserGroup )
    {
        m_groupId = sUserGroup.m_groupId;
        m_parentId = sUserGroup.m_parentId;
        m_groupName = sUserGroup.m_groupName;
        return *this;
    }

    int64_t m_groupId;
    int64_t m_parentId;
    string m_groupName;

public:
    uint32_t Size() const;
};

inline uint32_t SUserGroup::Size() const
{
    uint32_t nSize = 24;
    nSize += m_groupName.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SUserGroup&  sUserGroup );
CPackData& operator>> ( CPackData& cPackData, SUserGroup&  sUserGroup );

class PROTOCOL_LIB CImReqGetgroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETGROUP
    };
    CImReqGetgroup()
    {
    }

    ~CImReqGetgroup() { }
    CImReqGetgroup(const uint32_t&  dwTimestamp)
    {
        m_timestamp = dwTimestamp;
    }
    CImReqGetgroup&  operator=( const CImReqGetgroup&  cImReqGetgroup )
    {
        m_timestamp = cImReqGetgroup.m_timestamp;
        return *this;
    }

    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetgroup::Size() const
{
    return 6;
}
class PROTOCOL_LIB CImRspGetgroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETGROUP
    };
    CImRspGetgroup()
    {
    }

    ~CImRspGetgroup() { }
    CImRspGetgroup(const uint32_t&  dwRetcode, const VECTOR< SUserGroup >&  vecGroupList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_groupList = vecGroupList;
        m_timestamp = dwTimestamp;
    }
    CImRspGetgroup&  operator=( const CImRspGetgroup&  cImRspGetgroup )
    {
        m_retcode = cImRspGetgroup.m_retcode;
        m_groupList = cImRspGetgroup.m_groupList;
        m_timestamp = cImRspGetgroup.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SUserGroup >&  GetGroupList () const { return m_groupList; }
    bool SetGroupList ( const VECTOR< SUserGroup >&  vecGroupList )
    {
        m_groupList = vecGroupList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SUserGroup > m_groupList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetgroup::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_groupList.size(); i++)
    {
        nSize += m_groupList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqAddgroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDGROUP
    };
    CImReqAddgroup()
    {
    }

    ~CImReqAddgroup() { }
    CImReqAddgroup(const string&  strGroupName, const int64_t&  llParentId)
    {
        m_groupName = strGroupName;
        m_parentId = llParentId;
    }
    CImReqAddgroup&  operator=( const CImReqAddgroup&  cImReqAddgroup )
    {
        m_groupName = cImReqAddgroup.m_groupName;
        m_parentId = cImReqAddgroup.m_parentId;
        return *this;
    }

    const string&  GetGroupName () const { return m_groupName; }
    bool SetGroupName ( const string&  strGroupName )
    {
        m_groupName = strGroupName;
        return true;
    }
    const int64_t&  GetParentId () const { return m_parentId; }
    bool SetParentId ( const int64_t&  llParentId )
    {
        m_parentId = llParentId;
        return true;
    }
private:
    string m_groupName;
    int64_t m_parentId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddgroup::Size() const
{
    uint32_t nSize = 15;
    nSize += m_groupName.length();
    return nSize;
}

class PROTOCOL_LIB CImRspAddgroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDGROUP
    };
    CImRspAddgroup()
    {
    }

    ~CImRspAddgroup() { }
    CImRspAddgroup(const uint32_t&  dwRetcode, const SUserGroup&  sGroupInfo, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_groupInfo = sGroupInfo;
        m_timestamp = dwTimestamp;
    }
    CImRspAddgroup&  operator=( const CImRspAddgroup&  cImRspAddgroup )
    {
        m_retcode = cImRspAddgroup.m_retcode;
        m_groupInfo = cImRspAddgroup.m_groupInfo;
        m_timestamp = cImRspAddgroup.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const SUserGroup&  GetGroupInfo () const { return m_groupInfo; }
    bool SetGroupInfo ( const SUserGroup&  sGroupInfo )
    {
        m_groupInfo = sGroupInfo;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    SUserGroup m_groupInfo;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddgroup::Size() const
{
    uint32_t nSize = 12;
    nSize += m_groupInfo.Size();
    return nSize;
}

enum GROUP_OPERATE
{
    CHGGROUP_NAME               = 0x1,
    MOVE_GROUP                  = 0x2,

};

struct SUserChggroup
{
public:
    SUserChggroup()
    {
    }

    ~SUserChggroup() { }
    SUserChggroup(const uint64_t&  ullMask, const int64_t&  llGroupId, const int64_t&  llParentId, const string&  strGroupName)
    {
        m_mask = ullMask;
        m_groupId = llGroupId;
        m_parentId = llParentId;
        m_groupName = strGroupName;
    }
    SUserChggroup&  operator=( const SUserChggroup&  sUserChggroup )
    {
        m_mask = sUserChggroup.m_mask;
        m_groupId = sUserChggroup.m_groupId;
        m_parentId = sUserChggroup.m_parentId;
        m_groupName = sUserChggroup.m_groupName;
        return *this;
    }

    uint64_t m_mask;
    int64_t m_groupId;
    int64_t m_parentId;
    string m_groupName;

public:
    uint32_t Size() const;
};

inline uint32_t SUserChggroup::Size() const
{
    uint32_t nSize = 33;
    nSize += m_groupName.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SUserChggroup&  sUserChggroup );
CPackData& operator>> ( CPackData& cPackData, SUserChggroup&  sUserChggroup );

class PROTOCOL_LIB CImReqChggroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGGROUP
    };
    CImReqChggroup()
    {
    }

    ~CImReqChggroup() { }
    CImReqChggroup(const VECTOR< SUserChggroup >&  vecGroupInfo)
    {
        m_groupInfo = vecGroupInfo;
    }
    CImReqChggroup&  operator=( const CImReqChggroup&  cImReqChggroup )
    {
        m_groupInfo = cImReqChggroup.m_groupInfo;
        return *this;
    }

    const VECTOR< SUserChggroup >&  GetGroupInfo () const { return m_groupInfo; }
    bool SetGroupInfo ( const VECTOR< SUserChggroup >&  vecGroupInfo )
    {
        m_groupInfo = vecGroupInfo;
        return true;
    }
private:
    VECTOR< SUserChggroup > m_groupInfo;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChggroup::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_groupInfo.size(); i++)
    {
        nSize += m_groupInfo[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImRspChggroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGGROUP
    };
    CImRspChggroup()
    {
    }

    ~CImRspChggroup() { }
    CImRspChggroup(const uint32_t&  dwRetcode, const VECTOR< SUserChggroup >&  vecGroupInfo, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_groupInfo = vecGroupInfo;
        m_timestamp = dwTimestamp;
    }
    CImRspChggroup&  operator=( const CImRspChggroup&  cImRspChggroup )
    {
        m_retcode = cImRspChggroup.m_retcode;
        m_groupInfo = cImRspChggroup.m_groupInfo;
        m_timestamp = cImRspChggroup.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SUserChggroup >&  GetGroupInfo () const { return m_groupInfo; }
    bool SetGroupInfo ( const VECTOR< SUserChggroup >&  vecGroupInfo )
    {
        m_groupInfo = vecGroupInfo;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SUserChggroup > m_groupInfo;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChggroup::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_groupInfo.size(); i++)
    {
        nSize += m_groupInfo[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqDelgroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_DELGROUP
    };
    CImReqDelgroup()
    {
    }

    ~CImReqDelgroup() { }
    CImReqDelgroup(const VECTOR< int64_t >&  vecGroupId)
    {
        m_groupId = vecGroupId;
    }
    CImReqDelgroup&  operator=( const CImReqDelgroup&  cImReqDelgroup )
    {
        m_groupId = cImReqDelgroup.m_groupId;
        return *this;
    }

    const VECTOR< int64_t >&  GetGroupId () const { return m_groupId; }
    bool SetGroupId ( const VECTOR< int64_t >&  vecGroupId )
    {
        m_groupId = vecGroupId;
        return true;
    }
private:
    VECTOR< int64_t > m_groupId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqDelgroup::Size() const
{
    uint32_t nSize = 7;
    nSize += m_groupId.size() * 8;
    return nSize;
}

struct SDelGroup
{
public:
    SDelGroup()
    {
    }

    ~SDelGroup() { }
    SDelGroup(const uint32_t&  dwRetcode, const int64_t&  llGroupId)
    {
        m_retcode = dwRetcode;
        m_groupId = llGroupId;
    }
    SDelGroup&  operator=( const SDelGroup&  sDelGroup )
    {
        m_retcode = sDelGroup.m_retcode;
        m_groupId = sDelGroup.m_groupId;
        return *this;
    }

    uint32_t m_retcode;
    int64_t m_groupId;

public:
    uint32_t Size() const;
};

inline uint32_t SDelGroup::Size() const
{
    return 15;
}
CPackData& operator<< ( CPackData& cPackData, const SDelGroup&  sDelGroup );
CPackData& operator>> ( CPackData& cPackData, SDelGroup&  sDelGroup );

class PROTOCOL_LIB CImRspDelgroup : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_DELGROUP
    };
    CImRspDelgroup()
    {
    }

    ~CImRspDelgroup() { }
    CImRspDelgroup(const uint32_t&  dwRetcode, const VECTOR< SDelGroup >&  vecGroupInfo, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_groupInfo = vecGroupInfo;
        m_timestamp = dwTimestamp;
    }
    CImRspDelgroup&  operator=( const CImRspDelgroup&  cImRspDelgroup )
    {
        m_retcode = cImRspDelgroup.m_retcode;
        m_groupInfo = cImRspDelgroup.m_groupInfo;
        m_timestamp = cImRspDelgroup.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SDelGroup >&  GetGroupInfo () const { return m_groupInfo; }
    bool SetGroupInfo ( const VECTOR< SDelGroup >&  vecGroupInfo )
    {
        m_groupInfo = vecGroupInfo;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SDelGroup > m_groupInfo;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspDelgroup::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_groupInfo.size(); i++)
    {
        nSize += m_groupInfo[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqChguserverify : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGUSERVERIFY
    };
    CImReqChguserverify()
    {
    }

    ~CImReqChguserverify() { }
    CImReqChguserverify(const uint8_t&  chAddcontactFlag, const uint8_t&  chSendmsgFlag, const uint8_t&  chEnableSearch)
    {
        m_addcontactFlag = chAddcontactFlag;
        m_sendmsgFlag = chSendmsgFlag;
        m_enableSearch = chEnableSearch;
    }
    CImReqChguserverify&  operator=( const CImReqChguserverify&  cImReqChguserverify )
    {
        m_addcontactFlag = cImReqChguserverify.m_addcontactFlag;
        m_sendmsgFlag = cImReqChguserverify.m_sendmsgFlag;
        m_enableSearch = cImReqChguserverify.m_enableSearch;
        return *this;
    }

    const uint8_t&  GetAddcontactFlag () const { return m_addcontactFlag; }
    bool SetAddcontactFlag ( const uint8_t&  chAddcontactFlag )
    {
        m_addcontactFlag = chAddcontactFlag;
        return true;
    }
    const uint8_t&  GetSendmsgFlag () const { return m_sendmsgFlag; }
    bool SetSendmsgFlag ( const uint8_t&  chSendmsgFlag )
    {
        m_sendmsgFlag = chSendmsgFlag;
        return true;
    }
    const uint8_t&  GetEnableSearch () const { return m_enableSearch; }
    bool SetEnableSearch ( const uint8_t&  chEnableSearch )
    {
        m_enableSearch = chEnableSearch;
        return true;
    }
private:
    uint8_t m_addcontactFlag;
    uint8_t m_sendmsgFlag;
    uint8_t m_enableSearch;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChguserverify::Size() const
{
    return 7;
}
class PROTOCOL_LIB CImRspChguserverify : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGUSERVERIFY
    };
    CImRspChguserverify()
    {
    }

    ~CImRspChguserverify() { }
    CImRspChguserverify(const uint32_t&  dwRetcode, const uint8_t&  chAddcontactFlag, const uint8_t&  chSendmsgFlag, const uint8_t&  chEnableSearch)
    {
        m_retcode = dwRetcode;
        m_addcontactFlag = chAddcontactFlag;
        m_sendmsgFlag = chSendmsgFlag;
        m_enableSearch = chEnableSearch;
    }
    CImRspChguserverify&  operator=( const CImRspChguserverify&  cImRspChguserverify )
    {
        m_retcode = cImRspChguserverify.m_retcode;
        m_addcontactFlag = cImRspChguserverify.m_addcontactFlag;
        m_sendmsgFlag = cImRspChguserverify.m_sendmsgFlag;
        m_enableSearch = cImRspChguserverify.m_enableSearch;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint8_t&  GetAddcontactFlag () const { return m_addcontactFlag; }
    bool SetAddcontactFlag ( const uint8_t&  chAddcontactFlag )
    {
        m_addcontactFlag = chAddcontactFlag;
        return true;
    }
    const uint8_t&  GetSendmsgFlag () const { return m_sendmsgFlag; }
    bool SetSendmsgFlag ( const uint8_t&  chSendmsgFlag )
    {
        m_sendmsgFlag = chSendmsgFlag;
        return true;
    }
    const uint8_t&  GetEnableSearch () const { return m_enableSearch; }
    bool SetEnableSearch ( const uint8_t&  chEnableSearch )
    {
        m_enableSearch = chEnableSearch;
        return true;
    }
private:
    uint32_t m_retcode;
    uint8_t m_addcontactFlag;
    uint8_t m_sendmsgFlag;
    uint8_t m_enableSearch;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChguserverify::Size() const
{
    return 12;
}
enum CONTACT_OPERATE
{
    CHGNICK_NAME                = 0x1,
    MOVE_CONTACT                = 0x2,
    CHG_IMPORTANCE              = 0x4,

};

struct SChgContactInfo
{
public:
    SChgContactInfo()
    {
    }

    ~SChgContactInfo() { }
    SChgContactInfo(const int64_t&  llMask, const string&  strContactId, const string&  strNickName, const string&  strImportance, const int64_t&  llGroupId)
    {
        m_mask = llMask;
        m_contactId = strContactId;
        m_nickName = strNickName;
        m_importance = strImportance;
        m_groupId = llGroupId;
    }
    SChgContactInfo&  operator=( const SChgContactInfo&  sChgContactInfo )
    {
        m_mask = sChgContactInfo.m_mask;
        m_contactId = sChgContactInfo.m_contactId;
        m_nickName = sChgContactInfo.m_nickName;
        m_importance = sChgContactInfo.m_importance;
        m_groupId = sChgContactInfo.m_groupId;
        return *this;
    }

    int64_t m_mask;
    string m_contactId;
    string m_nickName;
    string m_importance;
    int64_t m_groupId;

public:
    uint32_t Size() const;
};

inline uint32_t SChgContactInfo::Size() const
{
    uint32_t nSize = 34;
    nSize += m_contactId.length();
    nSize += m_nickName.length();
    nSize += m_importance.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SChgContactInfo&  sChgContactInfo );
CPackData& operator>> ( CPackData& cPackData, SChgContactInfo&  sChgContactInfo );

struct SContactInfo
{
public:
    SContactInfo()
    {
    }

    ~SContactInfo() { }
    SContactInfo(const string&  strContactId, const string&  strNickName, const string&  strImportance, const int64_t&  llGroupId)
    {
        m_contactId = strContactId;
        m_nickName = strNickName;
        m_importance = strImportance;
        m_groupId = llGroupId;
    }
    SContactInfo&  operator=( const SContactInfo&  sContactInfo )
    {
        m_contactId = sContactInfo.m_contactId;
        m_nickName = sContactInfo.m_nickName;
        m_importance = sContactInfo.m_importance;
        m_groupId = sContactInfo.m_groupId;
        return *this;
    }

    string m_contactId;
    string m_nickName;
    string m_importance;
    int64_t m_groupId;

public:
    uint32_t Size() const;
};

inline uint32_t SContactInfo::Size() const
{
    uint32_t nSize = 25;
    nSize += m_contactId.length();
    nSize += m_nickName.length();
    nSize += m_importance.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SContactInfo&  sContactInfo );
CPackData& operator>> ( CPackData& cPackData, SContactInfo&  sContactInfo );

class PROTOCOL_LIB CImReqGetcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETCONTACT
    };
    CImReqGetcontact()
    {
    }

    ~CImReqGetcontact() { }
    CImReqGetcontact(const uint32_t&  dwTimestamp)
    {
        m_timestamp = dwTimestamp;
    }
    CImReqGetcontact&  operator=( const CImReqGetcontact&  cImReqGetcontact )
    {
        m_timestamp = cImReqGetcontact.m_timestamp;
        return *this;
    }

    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetcontact::Size() const
{
    return 6;
}
class PROTOCOL_LIB CImRspGetcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETCONTACT
    };
    CImRspGetcontact()
    {
    }

    ~CImRspGetcontact() { }
    CImRspGetcontact(const uint32_t&  dwRetcode, const VECTOR< SContactInfo >&  vecContactList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_contactList = vecContactList;
        m_timestamp = dwTimestamp;
    }
    CImRspGetcontact&  operator=( const CImRspGetcontact&  cImRspGetcontact )
    {
        m_retcode = cImRspGetcontact.m_retcode;
        m_contactList = cImRspGetcontact.m_contactList;
        m_timestamp = cImRspGetcontact.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SContactInfo >&  GetContactList () const { return m_contactList; }
    bool SetContactList ( const VECTOR< SContactInfo >&  vecContactList )
    {
        m_contactList = vecContactList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SContactInfo > m_contactList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetcontact::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_contactList.size(); i++)
    {
        nSize += m_contactList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqAddcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDCONTACT
    };
    CImReqAddcontact()
    {
    }

    ~CImReqAddcontact() { }
    CImReqAddcontact(const SContactInfo&  sContact, const uint8_t&  chType)
    {
        m_contact = sContact;
        m_type = chType;
    }
    CImReqAddcontact&  operator=( const CImReqAddcontact&  cImReqAddcontact )
    {
        m_contact = cImReqAddcontact.m_contact;
        m_type = cImReqAddcontact.m_type;
        return *this;
    }

    const SContactInfo&  GetContact () const { return m_contact; }
    bool SetContact ( const SContactInfo&  sContact )
    {
        m_contact = sContact;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
private:
    SContactInfo m_contact;
    uint8_t m_type;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddcontact::Size() const
{
    uint32_t nSize = 4;
    nSize += m_contact.Size();
    return nSize;
}

class PROTOCOL_LIB CImRspAddcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDCONTACT
    };
    CImRspAddcontact()
    {
    }

    ~CImRspAddcontact() { }
    CImRspAddcontact(const uint32_t&  dwRetcode, const uint8_t&  chType, const SContactInfo&  sContact, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_type = chType;
        m_contact = sContact;
        m_timestamp = dwTimestamp;
    }
    CImRspAddcontact&  operator=( const CImRspAddcontact&  cImRspAddcontact )
    {
        m_retcode = cImRspAddcontact.m_retcode;
        m_type = cImRspAddcontact.m_type;
        m_contact = cImRspAddcontact.m_contact;
        m_timestamp = cImRspAddcontact.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const SContactInfo&  GetContact () const { return m_contact; }
    bool SetContact ( const SContactInfo&  sContact )
    {
        m_contact = sContact;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    uint8_t m_type;
    SContactInfo m_contact;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddcontact::Size() const
{
    uint32_t nSize = 14;
    nSize += m_contact.Size();
    return nSize;
}

class PROTOCOL_LIB CImReqChgcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGCONTACT
    };
    CImReqChgcontact()
    {
    }

    ~CImReqChgcontact() { }
    CImReqChgcontact(const VECTOR< SChgContactInfo >&  vecContactList)
    {
        m_contactList = vecContactList;
    }
    CImReqChgcontact&  operator=( const CImReqChgcontact&  cImReqChgcontact )
    {
        m_contactList = cImReqChgcontact.m_contactList;
        return *this;
    }

    const VECTOR< SChgContactInfo >&  GetContactList () const { return m_contactList; }
    bool SetContactList ( const VECTOR< SChgContactInfo >&  vecContactList )
    {
        m_contactList = vecContactList;
        return true;
    }
private:
    VECTOR< SChgContactInfo > m_contactList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgcontact::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_contactList.size(); i++)
    {
        nSize += m_contactList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImRspChgcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGCONTACT
    };
    CImRspChgcontact()
    {
    }

    ~CImRspChgcontact() { }
    CImRspChgcontact(const uint32_t&  dwRetcode, const VECTOR< SChgContactInfo >&  vecContactList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_contactList = vecContactList;
        m_timestamp = dwTimestamp;
    }
    CImRspChgcontact&  operator=( const CImRspChgcontact&  cImRspChgcontact )
    {
        m_retcode = cImRspChgcontact.m_retcode;
        m_contactList = cImRspChgcontact.m_contactList;
        m_timestamp = cImRspChgcontact.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SChgContactInfo >&  GetContactList () const { return m_contactList; }
    bool SetContactList ( const VECTOR< SChgContactInfo >&  vecContactList )
    {
        m_contactList = vecContactList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SChgContactInfo > m_contactList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChgcontact::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_contactList.size(); i++)
    {
        nSize += m_contactList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqDelcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_DELCONTACT
    };
    CImReqDelcontact()
    {
    }

    ~CImReqDelcontact() { }
    CImReqDelcontact(const VECTOR< string >&  vecContactList)
    {
        m_contactList = vecContactList;
    }
    CImReqDelcontact&  operator=( const CImReqDelcontact&  cImReqDelcontact )
    {
        m_contactList = cImReqDelcontact.m_contactList;
        return *this;
    }

    const VECTOR< string >&  GetContactList () const { return m_contactList; }
    bool SetContactList ( const VECTOR< string >&  vecContactList )
    {
        m_contactList = vecContactList;
        return true;
    }
private:
    VECTOR< string > m_contactList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqDelcontact::Size() const
{
    uint32_t nSize = 7;
    nSize += m_contactList.size() * 4;
    for(uint32_t i = 0; i < m_contactList.size(); i++)
    {
        nSize += m_contactList[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImRspDelcontact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_DELCONTACT
    };
    CImRspDelcontact()
    {
    }

    ~CImRspDelcontact() { }
    CImRspDelcontact(const uint32_t&  dwRetcode, const VECTOR< string >&  vecContactList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_contactList = vecContactList;
        m_timestamp = dwTimestamp;
    }
    CImRspDelcontact&  operator=( const CImRspDelcontact&  cImRspDelcontact )
    {
        m_retcode = cImRspDelcontact.m_retcode;
        m_contactList = cImRspDelcontact.m_contactList;
        m_timestamp = cImRspDelcontact.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< string >&  GetContactList () const { return m_contactList; }
    bool SetContactList ( const VECTOR< string >&  vecContactList )
    {
        m_contactList = vecContactList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< string > m_contactList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspDelcontact::Size() const
{
    uint32_t nSize = 17;
    nSize += m_contactList.size() * 4;
    for(uint32_t i = 0; i < m_contactList.size(); i++)
    {
        nSize += m_contactList[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqAddcntack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDCNTACK
    };
    CImReqAddcntack()
    {
    }

    ~CImReqAddcntack() { }
    CImReqAddcntack(const uint8_t&  chOpcode, const string&  strContactId, const int64_t&  llGroupId)
    {
        m_opcode = chOpcode;
        m_contactId = strContactId;
        m_groupId = llGroupId;
    }
    CImReqAddcntack&  operator=( const CImReqAddcntack&  cImReqAddcntack )
    {
        m_opcode = cImReqAddcntack.m_opcode;
        m_contactId = cImReqAddcntack.m_contactId;
        m_groupId = cImReqAddcntack.m_groupId;
        return *this;
    }

    const uint8_t&  GetOpcode () const { return m_opcode; }
    bool SetOpcode ( const uint8_t&  chOpcode )
    {
        m_opcode = chOpcode;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const int64_t&  GetGroupId () const { return m_groupId; }
    bool SetGroupId ( const int64_t&  llGroupId )
    {
        m_groupId = llGroupId;
        return true;
    }
private:
    uint8_t m_opcode;
    string m_contactId;
    int64_t m_groupId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddcntack::Size() const
{
    uint32_t nSize = 17;
    nSize += m_contactId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspAddcntack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDCNTACK
    };
    CImRspAddcntack()
    {
    }

    ~CImRspAddcntack() { }
    CImRspAddcntack(const uint32_t&  dwRetcode, const uint8_t&  chOpcode, const int64_t&  llGroupId, const uint32_t&  dwTimestamp, const string&  strContactId)
    {
        m_retcode = dwRetcode;
        m_opcode = chOpcode;
        m_groupId = llGroupId;
        m_timestamp = dwTimestamp;
        m_contactId = strContactId;
    }
    CImRspAddcntack&  operator=( const CImRspAddcntack&  cImRspAddcntack )
    {
        m_retcode = cImRspAddcntack.m_retcode;
        m_opcode = cImRspAddcntack.m_opcode;
        m_groupId = cImRspAddcntack.m_groupId;
        m_timestamp = cImRspAddcntack.m_timestamp;
        m_contactId = cImRspAddcntack.m_contactId;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint8_t&  GetOpcode () const { return m_opcode; }
    bool SetOpcode ( const uint8_t&  chOpcode )
    {
        m_opcode = chOpcode;
        return true;
    }
    const int64_t&  GetGroupId () const { return m_groupId; }
    bool SetGroupId ( const int64_t&  llGroupId )
    {
        m_groupId = llGroupId;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
private:
    uint32_t m_retcode;
    uint8_t m_opcode;
    int64_t m_groupId;
    uint32_t m_timestamp;
    string m_contactId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddcntack::Size() const
{
    uint32_t nSize = 27;
    nSize += m_contactId.length();
    return nSize;
}

struct SContactDetailGetter
{
public:
    SContactDetailGetter()
    {
    }

    ~SContactDetailGetter() { }
    SContactDetailGetter(const string&  strContactId, const uint32_t&  dwTimestamp)
    {
        m_contactId = strContactId;
        m_timestamp = dwTimestamp;
    }
    SContactDetailGetter&  operator=( const SContactDetailGetter&  sContactDetailGetter )
    {
        m_contactId = sContactDetailGetter.m_contactId;
        m_timestamp = sContactDetailGetter.m_timestamp;
        return *this;
    }

    string m_contactId;
    uint32_t m_timestamp;

public:
    uint32_t Size() const;
};

inline uint32_t SContactDetailGetter::Size() const
{
    uint32_t nSize = 11;
    nSize += m_contactId.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SContactDetailGetter&  sContactDetailGetter );
CPackData& operator>> ( CPackData& cPackData, SContactDetailGetter&  sContactDetailGetter );

class PROTOCOL_LIB CImReqGetcntdetail : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETCNTDETAIL
    };
    CImReqGetcntdetail()
    {
    }

    ~CImReqGetcntdetail() { }
    CImReqGetcntdetail(const VECTOR< SContactDetailGetter >&  vecContacts)
    {
        m_contacts = vecContacts;
    }
    CImReqGetcntdetail&  operator=( const CImReqGetcntdetail&  cImReqGetcntdetail )
    {
        m_contacts = cImReqGetcntdetail.m_contacts;
        return *this;
    }

    const VECTOR< SContactDetailGetter >&  GetContacts () const { return m_contacts; }
    bool SetContacts ( const VECTOR< SContactDetailGetter >&  vecContacts )
    {
        m_contacts = vecContacts;
        return true;
    }
private:
    VECTOR< SContactDetailGetter > m_contacts;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetcntdetail::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_contacts.size(); i++)
    {
        nSize += m_contacts[i].Size();
    }
    return nSize;
}

struct SContactDetail
{
public:
    SContactDetail()
    {
    }

    ~SContactDetail() { }
    SContactDetail(const map< string,string >&  mapContactDetail, const uint32_t&  dwTimestamp)
    {
        m_contactDetail = mapContactDetail;
        m_timestamp = dwTimestamp;
    }
    SContactDetail&  operator=( const SContactDetail&  sContactDetail )
    {
        m_contactDetail = sContactDetail.m_contactDetail;
        m_timestamp = sContactDetail.m_timestamp;
        return *this;
    }

    map< string,string > m_contactDetail;
    uint32_t m_timestamp;

public:
    uint32_t Size() const;
};

inline uint32_t SContactDetail::Size() const
{
    uint32_t nSize = 10;
    nSize += m_contactDetail.size() * 8;
    {
        map< string,string >::const_iterator itr;
        for(itr = m_contactDetail.begin(); itr != m_contactDetail.end(); ++itr)
        {
            nSize += itr->first.length();
            nSize += itr->second.length();
        }
    }
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SContactDetail&  sContactDetail );
CPackData& operator>> ( CPackData& cPackData, SContactDetail&  sContactDetail );

class PROTOCOL_LIB CImRspGetcntdetail : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETCNTDETAIL
    };
    CImRspGetcntdetail()
    {
    }

    ~CImRspGetcntdetail() { }
    CImRspGetcntdetail(const uint32_t&  dwRetcode, const VECTOR< SContactDetail >&  vecDetailList)
    {
        m_retcode = dwRetcode;
        m_detailList = vecDetailList;
    }
    CImRspGetcntdetail&  operator=( const CImRspGetcntdetail&  cImRspGetcntdetail )
    {
        m_retcode = cImRspGetcntdetail.m_retcode;
        m_detailList = cImRspGetcntdetail.m_detailList;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SContactDetail >&  GetDetailList () const { return m_detailList; }
    bool SetDetailList ( const VECTOR< SContactDetail >&  vecDetailList )
    {
        m_detailList = vecDetailList;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SContactDetail > m_detailList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetcntdetail::Size() const
{
    uint32_t nSize = 12;
    for(uint32_t i = 0; i < m_detailList.size(); i++)
    {
        nSize += m_detailList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqChguserdetail : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGUSERDETAIL
    };
    CImReqChguserdetail()
    {
    }

    ~CImReqChguserdetail() { }
    CImReqChguserdetail(const map< string,string >&  mapUserDetail)
    {
        m_userDetail = mapUserDetail;
    }
    CImReqChguserdetail&  operator=( const CImReqChguserdetail&  cImReqChguserdetail )
    {
        m_userDetail = cImReqChguserdetail.m_userDetail;
        return *this;
    }

    const map< string,string >&  GetUserDetail () const { return m_userDetail; }
    bool SetUserDetail ( const map< string,string >&  mapUserDetail )
    {
        m_userDetail = mapUserDetail;
        return true;
    }
private:
    map< string,string > m_userDetail;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChguserdetail::Size() const
{
    uint32_t nSize = 5;
    nSize += m_userDetail.size() * 8;
    {
        map< string,string >::const_iterator itr;
        for(itr = m_userDetail.begin(); itr != m_userDetail.end(); ++itr)
        {
            nSize += itr->first.length();
            nSize += itr->second.length();
        }
    }
    return nSize;
}

class PROTOCOL_LIB CImRspChguserdetail : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGUSERDETAIL
    };
    CImRspChguserdetail()
    {
    }

    ~CImRspChguserdetail() { }
    CImRspChguserdetail(const uint32_t&  dwRetcode, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_timestamp = dwTimestamp;
    }
    CImRspChguserdetail&  operator=( const CImRspChguserdetail&  cImRspChguserdetail )
    {
        m_retcode = cImRspChguserdetail.m_retcode;
        m_timestamp = cImRspChguserdetail.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChguserdetail::Size() const
{
    return 11;
}
class PROTOCOL_LIB CImReqGetcntmemo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETCNTMEMO
    };
    CImReqGetcntmemo()
    {
    }

    ~CImReqGetcntmemo() { }
    CImReqGetcntmemo(const string&  strContactId)
    {
        m_contactId = strContactId;
    }
    CImReqGetcntmemo&  operator=( const CImReqGetcntmemo&  cImReqGetcntmemo )
    {
        m_contactId = cImReqGetcntmemo.m_contactId;
        return *this;
    }

    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
private:
    string m_contactId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetcntmemo::Size() const
{
    uint32_t nSize = 6;
    nSize += m_contactId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspGetcntmemo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETCNTMEMO
    };
    CImRspGetcntmemo()
    {
    }

    ~CImRspGetcntmemo() { }
    CImRspGetcntmemo(const uint32_t&  dwRetcode, const string&  strContactId, const string&  strMemo)
    {
        m_retcode = dwRetcode;
        m_contactId = strContactId;
        m_memo = strMemo;
    }
    CImRspGetcntmemo&  operator=( const CImRspGetcntmemo&  cImRspGetcntmemo )
    {
        m_retcode = cImRspGetcntmemo.m_retcode;
        m_contactId = cImRspGetcntmemo.m_contactId;
        m_memo = cImRspGetcntmemo.m_memo;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const string&  GetMemo () const { return m_memo; }
    bool SetMemo ( const string&  strMemo )
    {
        m_memo = strMemo;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_contactId;
    string m_memo;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetcntmemo::Size() const
{
    uint32_t nSize = 16;
    nSize += m_contactId.length();
    nSize += m_memo.length();
    return nSize;
}

class PROTOCOL_LIB CImReqChgcntmemo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGCNTMEMO
    };
    CImReqChgcntmemo()
    {
    }

    ~CImReqChgcntmemo() { }
    CImReqChgcntmemo(const string&  strContactId, const string&  strMemo)
    {
        m_contactId = strContactId;
        m_memo = strMemo;
    }
    CImReqChgcntmemo&  operator=( const CImReqChgcntmemo&  cImReqChgcntmemo )
    {
        m_contactId = cImReqChgcntmemo.m_contactId;
        m_memo = cImReqChgcntmemo.m_memo;
        return *this;
    }

    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const string&  GetMemo () const { return m_memo; }
    bool SetMemo ( const string&  strMemo )
    {
        m_memo = strMemo;
        return true;
    }
private:
    string m_contactId;
    string m_memo;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgcntmemo::Size() const
{
    uint32_t nSize = 11;
    nSize += m_contactId.length();
    nSize += m_memo.length();
    return nSize;
}

class PROTOCOL_LIB CImRspChgcntmemo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGCNTMEMO
    };
    CImRspChgcntmemo()
    {
    }

    ~CImRspChgcntmemo() { }
    CImRspChgcntmemo(const uint32_t&  dwRetcode, const string&  strContactId, const string&  strMemo)
    {
        m_retcode = dwRetcode;
        m_contactId = strContactId;
        m_memo = strMemo;
    }
    CImRspChgcntmemo&  operator=( const CImRspChgcntmemo&  cImRspChgcntmemo )
    {
        m_retcode = cImRspChgcntmemo.m_retcode;
        m_contactId = cImRspChgcntmemo.m_contactId;
        m_memo = cImRspChgcntmemo.m_memo;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const string&  GetMemo () const { return m_memo; }
    bool SetMemo ( const string&  strMemo )
    {
        m_memo = strMemo;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_contactId;
    string m_memo;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChgcntmemo::Size() const
{
    uint32_t nSize = 16;
    nSize += m_contactId.length();
    nSize += m_memo.length();
    return nSize;
}

class PROTOCOL_LIB CImRspGetblack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETBLACK
    };
    CImRspGetblack()
    {
    }

    ~CImRspGetblack() { }
    CImRspGetblack(const uint32_t&  dwRetcode, const VECTOR< string >&  vecBlackList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_blackList = vecBlackList;
        m_timestamp = dwTimestamp;
    }
    CImRspGetblack&  operator=( const CImRspGetblack&  cImRspGetblack )
    {
        m_retcode = cImRspGetblack.m_retcode;
        m_blackList = cImRspGetblack.m_blackList;
        m_timestamp = cImRspGetblack.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< string >&  GetBlackList () const { return m_blackList; }
    bool SetBlackList ( const VECTOR< string >&  vecBlackList )
    {
        m_blackList = vecBlackList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< string > m_blackList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetblack::Size() const
{
    uint32_t nSize = 17;
    nSize += m_blackList.size() * 4;
    for(uint32_t i = 0; i < m_blackList.size(); i++)
    {
        nSize += m_blackList[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqAddblack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDBLACK
    };
    CImReqAddblack()
    {
    }

    ~CImReqAddblack() { }
    CImReqAddblack(const string&  strBlackId)
    {
        m_blackId = strBlackId;
    }
    CImReqAddblack&  operator=( const CImReqAddblack&  cImReqAddblack )
    {
        m_blackId = cImReqAddblack.m_blackId;
        return *this;
    }

    const string&  GetBlackId () const { return m_blackId; }
    bool SetBlackId ( const string&  strBlackId )
    {
        if(strBlackId.size() > 64)
            return false;
        m_blackId = strBlackId;
        return true;
    }
private:
    string m_blackId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddblack::Size() const
{
    uint32_t nSize = 6;
    nSize += m_blackId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspAddblack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDBLACK
    };
    CImRspAddblack()
    {
    }

    ~CImRspAddblack() { }
    CImRspAddblack(const uint32_t&  dwRetcode, const string&  strBlackId, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_blackId = strBlackId;
        m_timestamp = dwTimestamp;
    }
    CImRspAddblack&  operator=( const CImRspAddblack&  cImRspAddblack )
    {
        m_retcode = cImRspAddblack.m_retcode;
        m_blackId = cImRspAddblack.m_blackId;
        m_timestamp = cImRspAddblack.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetBlackId () const { return m_blackId; }
    bool SetBlackId ( const string&  strBlackId )
    {
        if(strBlackId.size() > 64)
            return false;
        m_blackId = strBlackId;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_blackId;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddblack::Size() const
{
    uint32_t nSize = 16;
    nSize += m_blackId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspDelblack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_DELBLACK
    };
    CImRspDelblack()
    {
    }

    ~CImRspDelblack() { }
    CImRspDelblack(const uint32_t&  dwRetcode, const string&  strBlackId, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_blackId = strBlackId;
        m_timestamp = dwTimestamp;
    }
    CImRspDelblack&  operator=( const CImRspDelblack&  cImRspDelblack )
    {
        m_retcode = cImRspDelblack.m_retcode;
        m_blackId = cImRspDelblack.m_blackId;
        m_timestamp = cImRspDelblack.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetBlackId () const { return m_blackId; }
    bool SetBlackId ( const string&  strBlackId )
    {
        if(strBlackId.size() > 64)
            return false;
        m_blackId = strBlackId;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_blackId;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspDelblack::Size() const
{
    uint32_t nSize = 16;
    nSize += m_blackId.length();
    return nSize;
}

class PROTOCOL_LIB CImReqDelblack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_DELBLACK
    };
    CImReqDelblack()
    {
    }

    ~CImReqDelblack() { }
    CImReqDelblack(const uint32_t&  dwRetcode, const string&  strBlackId, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_blackId = strBlackId;
        m_timestamp = dwTimestamp;
    }
    CImReqDelblack&  operator=( const CImReqDelblack&  cImReqDelblack )
    {
        m_retcode = cImReqDelblack.m_retcode;
        m_blackId = cImReqDelblack.m_blackId;
        m_timestamp = cImReqDelblack.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetBlackId () const { return m_blackId; }
    bool SetBlackId ( const string&  strBlackId )
    {
        if(strBlackId.size() > 64)
            return false;
        m_blackId = strBlackId;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_blackId;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqDelblack::Size() const
{
    uint32_t nSize = 16;
    nSize += m_blackId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspGetrevblack : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETREVBLACK
    };
    CImRspGetrevblack()
    {
    }

    ~CImRspGetrevblack() { }
    CImRspGetrevblack(const uint32_t&  dwRetcode, const VECTOR< string >&  vecBlackList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_blackList = vecBlackList;
        m_timestamp = dwTimestamp;
    }
    CImRspGetrevblack&  operator=( const CImRspGetrevblack&  cImRspGetrevblack )
    {
        m_retcode = cImRspGetrevblack.m_retcode;
        m_blackList = cImRspGetrevblack.m_blackList;
        m_timestamp = cImRspGetrevblack.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< string >&  GetBlackList () const { return m_blackList; }
    bool SetBlackList ( const VECTOR< string >&  vecBlackList )
    {
        m_blackList = vecBlackList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< string > m_blackList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetrevblack::Size() const
{
    uint32_t nSize = 17;
    nSize += m_blackList.size() * 4;
    for(uint32_t i = 0; i < m_blackList.size(); i++)
    {
        nSize += m_blackList[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImRspGetuserinfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETUSERINFO
    };
    CImRspGetuserinfo()
    {
    }

    ~CImRspGetuserinfo() { }
    CImRspGetuserinfo(const uint32_t&  dwRetcode, const uint8_t&  chAddcontactFlag, const uint8_t&  chSendmsgFlag, const uint32_t&  dwActivity, const uint8_t&  chActLevel, const uint32_t&  dwNeedNextlevel, const uint8_t&  chImlevel, const uint8_t&  chMulsendflag)
    {
        m_retcode = dwRetcode;
        m_addcontactFlag = chAddcontactFlag;
        m_sendmsgFlag = chSendmsgFlag;
        m_activity = dwActivity;
        m_actLevel = chActLevel;
        m_needNextlevel = dwNeedNextlevel;
        m_imlevel = chImlevel;
        m_mulsendflag = chMulsendflag;
    }
    CImRspGetuserinfo&  operator=( const CImRspGetuserinfo&  cImRspGetuserinfo )
    {
        m_retcode = cImRspGetuserinfo.m_retcode;
        m_addcontactFlag = cImRspGetuserinfo.m_addcontactFlag;
        m_sendmsgFlag = cImRspGetuserinfo.m_sendmsgFlag;
        m_activity = cImRspGetuserinfo.m_activity;
        m_actLevel = cImRspGetuserinfo.m_actLevel;
        m_needNextlevel = cImRspGetuserinfo.m_needNextlevel;
        m_imlevel = cImRspGetuserinfo.m_imlevel;
        m_mulsendflag = cImRspGetuserinfo.m_mulsendflag;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint8_t&  GetAddcontactFlag () const { return m_addcontactFlag; }
    bool SetAddcontactFlag ( const uint8_t&  chAddcontactFlag )
    {
        m_addcontactFlag = chAddcontactFlag;
        return true;
    }
    const uint8_t&  GetSendmsgFlag () const { return m_sendmsgFlag; }
    bool SetSendmsgFlag ( const uint8_t&  chSendmsgFlag )
    {
        m_sendmsgFlag = chSendmsgFlag;
        return true;
    }
    const uint32_t&  GetActivity () const { return m_activity; }
    bool SetActivity ( const uint32_t&  dwActivity )
    {
        m_activity = dwActivity;
        return true;
    }
    const uint8_t&  GetActLevel () const { return m_actLevel; }
    bool SetActLevel ( const uint8_t&  chActLevel )
    {
        m_actLevel = chActLevel;
        return true;
    }
    const uint32_t&  GetNeedNextlevel () const { return m_needNextlevel; }
    bool SetNeedNextlevel ( const uint32_t&  dwNeedNextlevel )
    {
        m_needNextlevel = dwNeedNextlevel;
        return true;
    }
    const uint8_t&  GetImlevel () const { return m_imlevel; }
    bool SetImlevel ( const uint8_t&  chImlevel )
    {
        m_imlevel = chImlevel;
        return true;
    }
    const uint8_t&  GetMulsendflag () const { return m_mulsendflag; }
    bool SetMulsendflag ( const uint8_t&  chMulsendflag )
    {
        m_mulsendflag = chMulsendflag;
        return true;
    }
private:
    uint32_t m_retcode;
    uint8_t m_addcontactFlag;
    uint8_t m_sendmsgFlag;
    uint32_t m_activity;
    uint8_t m_actLevel;
    uint32_t m_needNextlevel;
    uint8_t m_imlevel;
    uint8_t m_mulsendflag;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetuserinfo::Size() const
{
    return 26;
}
struct SUserStatus
{
public:
    SUserStatus()
    {
    }

    ~SUserStatus() { }
    SUserStatus(const string&  strUserId, const uint8_t&  chBasicStatus, const uint8_t&  chPredefStatus)
    {
        m_userId = strUserId;
        m_basicStatus = chBasicStatus;
        m_predefStatus = chPredefStatus;
    }
    SUserStatus&  operator=( const SUserStatus&  sUserStatus )
    {
        m_userId = sUserStatus.m_userId;
        m_basicStatus = sUserStatus.m_basicStatus;
        m_predefStatus = sUserStatus.m_predefStatus;
        return *this;
    }

    string m_userId;
    uint8_t m_basicStatus;
    uint8_t m_predefStatus;

public:
    uint32_t Size() const;
};

inline uint32_t SUserStatus::Size() const
{
    uint32_t nSize = 10;
    nSize += m_userId.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SUserStatus&  sUserStatus );
CPackData& operator>> ( CPackData& cPackData, SUserStatus&  sUserStatus );

class PROTOCOL_LIB CImRspGetcntstatus : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETCNTSTATUS
    };
    CImRspGetcntstatus()
    {
    }

    ~CImRspGetcntstatus() { }
    CImRspGetcntstatus(const uint32_t&  dwRetcode, const VECTOR< SUserStatus >&  vecContactStatus)
    {
        m_retcode = dwRetcode;
        m_contactStatus = vecContactStatus;
    }
    CImRspGetcntstatus&  operator=( const CImRspGetcntstatus&  cImRspGetcntstatus )
    {
        m_retcode = cImRspGetcntstatus.m_retcode;
        m_contactStatus = cImRspGetcntstatus.m_contactStatus;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SUserStatus >&  GetContactStatus () const { return m_contactStatus; }
    bool SetContactStatus ( const VECTOR< SUserStatus >&  vecContactStatus )
    {
        m_contactStatus = vecContactStatus;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SUserStatus > m_contactStatus;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetcntstatus::Size() const
{
    uint32_t nSize = 12;
    for(uint32_t i = 0; i < m_contactStatus.size(); i++)
    {
        nSize += m_contactStatus[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqChgstatus : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGSTATUS
    };
    CImReqChgstatus()
    {
    }

    ~CImReqChgstatus() { }
    CImReqChgstatus(const uint8_t&  chBasicStatus, const uint8_t&  chPredefStatus)
    {
        m_basicStatus = chBasicStatus;
        m_predefStatus = chPredefStatus;
    }
    CImReqChgstatus&  operator=( const CImReqChgstatus&  cImReqChgstatus )
    {
        m_basicStatus = cImReqChgstatus.m_basicStatus;
        m_predefStatus = cImReqChgstatus.m_predefStatus;
        return *this;
    }

    const uint8_t&  GetBasicStatus () const { return m_basicStatus; }
    bool SetBasicStatus ( const uint8_t&  chBasicStatus )
    {
        m_basicStatus = chBasicStatus;
        return true;
    }
    const uint8_t&  GetPredefStatus () const { return m_predefStatus; }
    bool SetPredefStatus ( const uint8_t&  chPredefStatus )
    {
        m_predefStatus = chPredefStatus;
        return true;
    }
private:
    uint8_t m_basicStatus;
    uint8_t m_predefStatus;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgstatus::Size() const
{
    return 5;
}
class PROTOCOL_LIB CImNtfStatus : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_STATUS
    };
    CImNtfStatus()
    {
    }

    ~CImNtfStatus() { }
    CImNtfStatus(const VECTOR< SUserStatus >&  vecUserStatusList)
    {
        m_userStatusList = vecUserStatusList;
    }
    CImNtfStatus&  operator=( const CImNtfStatus&  cImNtfStatus )
    {
        m_userStatusList = cImNtfStatus.m_userStatusList;
        return *this;
    }

    const VECTOR< SUserStatus >&  GetUserStatusList () const { return m_userStatusList; }
    bool SetUserStatusList ( const VECTOR< SUserStatus >&  vecUserStatusList )
    {
        m_userStatusList = vecUserStatusList;
        return true;
    }
private:
    VECTOR< SUserStatus > m_userStatusList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfStatus::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_userStatusList.size(); i++)
    {
        nSize += m_userStatusList[i].Size();
    }
    return nSize;
}

struct SOfflineMessage
{
public:
    SOfflineMessage() : m_serverType(0)
    {
    }

    ~SOfflineMessage() { }
    SOfflineMessage(const string&  strFromId, const uint8_t&  chType, const uint32_t&  dwSendTime, const string&  strMessage, const uint8_t&  chServerType)
    {
        m_fromId = strFromId;
        m_type = chType;
        m_sendTime = dwSendTime;
        m_message = strMessage;
        m_serverType = chServerType;
    }
    SOfflineMessage&  operator=( const SOfflineMessage&  sOfflineMessage )
    {
        m_fromId = sOfflineMessage.m_fromId;
        m_type = sOfflineMessage.m_type;
        m_sendTime = sOfflineMessage.m_sendTime;
        m_message = sOfflineMessage.m_message;
        m_serverType = sOfflineMessage.m_serverType;
        return *this;
    }

    string m_fromId;
    uint8_t m_type;
    uint32_t m_sendTime;
    string m_message;
    uint8_t m_serverType;

public:
    uint32_t Size() const;
};

inline uint32_t SOfflineMessage::Size() const
{
    uint32_t nSize = 20;
    nSize += m_fromId.length();
    nSize += m_message.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SOfflineMessage&  sOfflineMessage );
CPackData& operator>> ( CPackData& cPackData, SOfflineMessage&  sOfflineMessage );

class PROTOCOL_LIB CImRspGetofflinemsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETOFFLINEMSG
    };
    CImRspGetofflinemsg()
    {
    }

    ~CImRspGetofflinemsg() { }
    CImRspGetofflinemsg(const uint32_t&  dwRetcode, const VECTOR< SOfflineMessage >&  vecMessageList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_messageList = vecMessageList;
        m_timestamp = dwTimestamp;
    }
    CImRspGetofflinemsg&  operator=( const CImRspGetofflinemsg&  cImRspGetofflinemsg )
    {
        m_retcode = cImRspGetofflinemsg.m_retcode;
        m_messageList = cImRspGetofflinemsg.m_messageList;
        m_timestamp = cImRspGetofflinemsg.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SOfflineMessage >&  GetMessageList () const { return m_messageList; }
    bool SetMessageList ( const VECTOR< SOfflineMessage >&  vecMessageList )
    {
        m_messageList = vecMessageList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SOfflineMessage > m_messageList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetofflinemsg::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_messageList.size(); i++)
    {
        nSize += m_messageList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqAddofflinemsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDOFFLINEMSG
    };
    CImReqAddofflinemsg()
    {
    }

    ~CImReqAddofflinemsg() { }
    CImReqAddofflinemsg(const VECTOR< SOfflineMessage >&  vecMessageList)
    {
        m_messageList = vecMessageList;
    }
    CImReqAddofflinemsg&  operator=( const CImReqAddofflinemsg&  cImReqAddofflinemsg )
    {
        m_messageList = cImReqAddofflinemsg.m_messageList;
        return *this;
    }

    const VECTOR< SOfflineMessage >&  GetMessageList () const { return m_messageList; }
    bool SetMessageList ( const VECTOR< SOfflineMessage >&  vecMessageList )
    {
        m_messageList = vecMessageList;
        return true;
    }
private:
    VECTOR< SOfflineMessage > m_messageList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddofflinemsg::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_messageList.size(); i++)
    {
        nSize += m_messageList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqDelofflinemsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_DELOFFLINEMSG
    };
    CImReqDelofflinemsg()
    {
    }

    ~CImReqDelofflinemsg() { }
    CImReqDelofflinemsg(const uint32_t&  dwLastTime)
    {
        m_lastTime = dwLastTime;
    }
    CImReqDelofflinemsg&  operator=( const CImReqDelofflinemsg&  cImReqDelofflinemsg )
    {
        m_lastTime = cImReqDelofflinemsg.m_lastTime;
        return *this;
    }

    const uint32_t&  GetLastTime () const { return m_lastTime; }
    bool SetLastTime ( const uint32_t&  dwLastTime )
    {
        m_lastTime = dwLastTime;
        return true;
    }
private:
    uint32_t m_lastTime;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqDelofflinemsg::Size() const
{
    return 6;
}
class PROTOCOL_LIB CImRspGetsystemmsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETSYSTEMMSG
    };
    CImRspGetsystemmsg()
    {
    }

    ~CImRspGetsystemmsg() { }
    CImRspGetsystemmsg(const VECTOR< string >&  vecMessageList)
    {
        m_messageList = vecMessageList;
    }
    CImRspGetsystemmsg&  operator=( const CImRspGetsystemmsg&  cImRspGetsystemmsg )
    {
        m_messageList = cImRspGetsystemmsg.m_messageList;
        return *this;
    }

    const VECTOR< string >&  GetMessageList () const { return m_messageList; }
    bool SetMessageList ( const VECTOR< string >&  vecMessageList )
    {
        m_messageList = vecMessageList;
        return true;
    }
private:
    VECTOR< string > m_messageList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetsystemmsg::Size() const
{
    uint32_t nSize = 7;
    nSize += m_messageList.size() * 4;
    for(uint32_t i = 0; i < m_messageList.size(); i++)
    {
        nSize += m_messageList[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqSendimmessage : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_SENDIMMESSAGE
    };
    CImReqSendimmessage()
    {
    }

    ~CImReqSendimmessage() { }
    CImReqSendimmessage(const string&  strTargetId, const uint8_t&  chType, const string&  strMessage)
    {
        m_targetId = strTargetId;
        m_type = chType;
        m_message = strMessage;
    }
    CImReqSendimmessage&  operator=( const CImReqSendimmessage&  cImReqSendimmessage )
    {
        m_targetId = cImReqSendimmessage.m_targetId;
        m_type = cImReqSendimmessage.m_type;
        m_message = cImReqSendimmessage.m_message;
        return *this;
    }

    const string&  GetTargetId () const { return m_targetId; }
    bool SetTargetId ( const string&  strTargetId )
    {
        if(strTargetId.size() > 64)
            return false;
        m_targetId = strTargetId;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    string m_targetId;
    uint8_t m_type;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqSendimmessage::Size() const
{
    uint32_t nSize = 13;
    nSize += m_targetId.length();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImReqSendmultiusermsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_SENDMULTIUSERMSG
    };
    CImReqSendmultiusermsg()
    {
    }

    ~CImReqSendmultiusermsg() { }
    CImReqSendmultiusermsg(const VECTOR< string >&  vecTargetList, const uint8_t&  chType, const string&  strMessage)
    {
        m_targetList = vecTargetList;
        m_type = chType;
        m_message = strMessage;
    }
    CImReqSendmultiusermsg&  operator=( const CImReqSendmultiusermsg&  cImReqSendmultiusermsg )
    {
        m_targetList = cImReqSendmultiusermsg.m_targetList;
        m_type = cImReqSendmultiusermsg.m_type;
        m_message = cImReqSendmultiusermsg.m_message;
        return *this;
    }

    const VECTOR< string >&  GetTargetList () const { return m_targetList; }
    bool SetTargetList ( const VECTOR< string >&  vecTargetList )
    {
        m_targetList = vecTargetList;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    VECTOR< string > m_targetList;
    uint8_t m_type;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqSendmultiusermsg::Size() const
{
    uint32_t nSize = 14;
    nSize += m_targetList.size() * 4;
    for(uint32_t i = 0; i < m_targetList.size(); i++)
    {
        nSize += m_targetList[i].length();
    }
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfImmessage : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_IMMESSAGE
    };
    CImNtfImmessage() : m_serverType(0)
    {
    }

    ~CImNtfImmessage() { }
    CImNtfImmessage(const string&  strSendId, const uint32_t&  dwSendTime, const string&  strMessage, const uint8_t&  chServerType)
    {
        m_sendId = strSendId;
        m_sendTime = dwSendTime;
        m_message = strMessage;
        m_serverType = chServerType;
    }
    CImNtfImmessage&  operator=( const CImNtfImmessage&  cImNtfImmessage )
    {
        m_sendId = cImNtfImmessage.m_sendId;
        m_sendTime = cImNtfImmessage.m_sendTime;
        m_message = cImNtfImmessage.m_message;
        m_serverType = cImNtfImmessage.m_serverType;
        return *this;
    }

    const string&  GetSendId () const { return m_sendId; }
    bool SetSendId ( const string&  strSendId )
    {
        if(strSendId.size() > 64)
            return false;
        m_sendId = strSendId;
        return true;
    }
    const uint32_t&  GetSendTime () const { return m_sendTime; }
    bool SetSendTime ( const uint32_t&  dwSendTime )
    {
        m_sendTime = dwSendTime;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
    const uint8_t&  GetServerType () const { return m_serverType; }
    bool SetServerType ( const uint8_t&  chServerType )
    {
        m_serverType = chServerType;
        return true;
    }
private:
    string m_sendId;
    uint32_t m_sendTime;
    string m_message;
    uint8_t m_serverType;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfImmessage::Size() const
{
    uint32_t nSize = 18;
    nSize += m_sendId.length();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfSystemmessage : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_SYSTEMMESSAGE
    };
    CImNtfSystemmessage()
    {
    }

    ~CImNtfSystemmessage() { }
    CImNtfSystemmessage(const uint16_t&  wCmdId, const string&  strStyle, const string&  strMessage)
    {
        m_cmdId = wCmdId;
        m_style = strStyle;
        m_message = strMessage;
    }
    CImNtfSystemmessage&  operator=( const CImNtfSystemmessage&  cImNtfSystemmessage )
    {
        m_cmdId = cImNtfSystemmessage.m_cmdId;
        m_style = cImNtfSystemmessage.m_style;
        m_message = cImNtfSystemmessage.m_message;
        return *this;
    }

    const uint16_t&  GetCmdId () const { return m_cmdId; }
    bool SetCmdId ( const uint16_t&  wCmdId )
    {
        m_cmdId = wCmdId;
        return true;
    }
    const string&  GetStyle () const { return m_style; }
    bool SetStyle ( const string&  strStyle )
    {
        m_style = strStyle;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    uint16_t m_cmdId;
    string m_style;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfSystemmessage::Size() const
{
    uint32_t nSize = 14;
    nSize += m_style.length();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfSubcribeMsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_SUBCRIBE_MSG
    };
    CImNtfSubcribeMsg()
    {
    }

    ~CImNtfSubcribeMsg() { }
    CImNtfSubcribeMsg(const string&  strMessage, const map< string,string >&  mapHtmlMsg)
    {
        m_message = strMessage;
        m_htmlMsg = mapHtmlMsg;
    }
    CImNtfSubcribeMsg&  operator=( const CImNtfSubcribeMsg&  cImNtfSubcribeMsg )
    {
        m_message = cImNtfSubcribeMsg.m_message;
        m_htmlMsg = cImNtfSubcribeMsg.m_htmlMsg;
        return *this;
    }

    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
    const map< string,string >&  GetHtmlMsg () const { return m_htmlMsg; }
    bool SetHtmlMsg ( const map< string,string >&  mapHtmlMsg )
    {
        m_htmlMsg = mapHtmlMsg;
        return true;
    }
private:
    string m_message;
    map< string,string > m_htmlMsg;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfSubcribeMsg::Size() const
{
    uint32_t nSize = 10;
    nSize += m_message.length();
    nSize += m_htmlMsg.size() * 8;
    {
        map< string,string >::const_iterator itr;
        for(itr = m_htmlMsg.begin(); itr != m_htmlMsg.end(); ++itr)
        {
            nSize += itr->first.length();
            nSize += itr->second.length();
        }
    }
    return nSize;
}

class PROTOCOL_LIB CImNtfExtinfoMsg : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_EXTINFO_MSG
    };
    CImNtfExtinfoMsg()
    {
    }

    ~CImNtfExtinfoMsg() { }
    CImNtfExtinfoMsg(const uint16_t&  wType, const string&  strContactId, const string&  strMessage)
    {
        m_type = wType;
        m_contactId = strContactId;
        m_message = strMessage;
    }
    CImNtfExtinfoMsg&  operator=( const CImNtfExtinfoMsg&  cImNtfExtinfoMsg )
    {
        m_type = cImNtfExtinfoMsg.m_type;
        m_contactId = cImNtfExtinfoMsg.m_contactId;
        m_message = cImNtfExtinfoMsg.m_message;
        return *this;
    }

    const uint16_t&  GetType () const { return m_type; }
    bool SetType ( const uint16_t&  wType )
    {
        m_type = wType;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    uint16_t m_type;
    string m_contactId;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfExtinfoMsg::Size() const
{
    uint32_t nSize = 14;
    nSize += m_contactId.length();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImReqGettoolsprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETTOOLSPROFILE
    };
    CImReqGettoolsprofile()
    {
    }

    ~CImReqGettoolsprofile() { }
    CImReqGettoolsprofile(const VECTOR< uint8_t >&  vecToolTypes, const uint32_t&  dwTimestamp)
    {
        m_toolTypes = vecToolTypes;
        m_timestamp = dwTimestamp;
    }
    CImReqGettoolsprofile&  operator=( const CImReqGettoolsprofile&  cImReqGettoolsprofile )
    {
        m_toolTypes = cImReqGettoolsprofile.m_toolTypes;
        m_timestamp = cImReqGettoolsprofile.m_timestamp;
        return *this;
    }

    const VECTOR< uint8_t >&  GetToolTypes () const { return m_toolTypes; }
    bool SetToolTypes ( const VECTOR< uint8_t >&  vecToolTypes )
    {
        m_toolTypes = vecToolTypes;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    VECTOR< uint8_t > m_toolTypes;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGettoolsprofile::Size() const
{
    uint32_t nSize = 12;
    nSize += m_toolTypes.size() * 1;
    return nSize;
}

struct SToolProfile
{
public:
    SToolProfile()
    {
    }

    ~SToolProfile() { }
    SToolProfile(const uint8_t&  chToolType, const string&  strProfile)
    {
        m_toolType = chToolType;
        m_profile = strProfile;
    }
    SToolProfile&  operator=( const SToolProfile&  sToolProfile )
    {
        m_toolType = sToolProfile.m_toolType;
        m_profile = sToolProfile.m_profile;
        return *this;
    }

    uint8_t m_toolType;
    string m_profile;

public:
    uint32_t Size() const;
};

inline uint32_t SToolProfile::Size() const
{
    uint32_t nSize = 8;
    nSize += m_profile.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SToolProfile&  sToolProfile );
CPackData& operator>> ( CPackData& cPackData, SToolProfile&  sToolProfile );

class PROTOCOL_LIB CImRspGettoolsprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETTOOLSPROFILE
    };
    CImRspGettoolsprofile()
    {
    }

    ~CImRspGettoolsprofile() { }
    CImRspGettoolsprofile(const uint32_t&  dwRetcode, const VECTOR< SToolProfile >&  vecProfileList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_profileList = vecProfileList;
        m_timestamp = dwTimestamp;
    }
    CImRspGettoolsprofile&  operator=( const CImRspGettoolsprofile&  cImRspGettoolsprofile )
    {
        m_retcode = cImRspGettoolsprofile.m_retcode;
        m_profileList = cImRspGettoolsprofile.m_profileList;
        m_timestamp = cImRspGettoolsprofile.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SToolProfile >&  GetProfileList () const { return m_profileList; }
    bool SetProfileList ( const VECTOR< SToolProfile >&  vecProfileList )
    {
        m_profileList = vecProfileList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SToolProfile > m_profileList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGettoolsprofile::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_profileList.size(); i++)
    {
        nSize += m_profileList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqChgtoolsprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGTOOLSPROFILE
    };
    CImReqChgtoolsprofile()
    {
    }

    ~CImReqChgtoolsprofile() { }
    CImReqChgtoolsprofile(const VECTOR< SToolProfile >&  vecProfileList)
    {
        m_profileList = vecProfileList;
    }
    CImReqChgtoolsprofile&  operator=( const CImReqChgtoolsprofile&  cImReqChgtoolsprofile )
    {
        m_profileList = cImReqChgtoolsprofile.m_profileList;
        return *this;
    }

    const VECTOR< SToolProfile >&  GetProfileList () const { return m_profileList; }
    bool SetProfileList ( const VECTOR< SToolProfile >&  vecProfileList )
    {
        m_profileList = vecProfileList;
        return true;
    }
private:
    VECTOR< SToolProfile > m_profileList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgtoolsprofile::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_profileList.size(); i++)
    {
        nSize += m_profileList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImRspChgtoolsprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGTOOLSPROFILE
    };
    CImRspChgtoolsprofile()
    {
    }

    ~CImRspChgtoolsprofile() { }
    CImRspChgtoolsprofile(const uint32_t&  dwRetcode, const VECTOR< uint8_t >&  vecToolTypes, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_toolTypes = vecToolTypes;
        m_timestamp = dwTimestamp;
    }
    CImRspChgtoolsprofile&  operator=( const CImRspChgtoolsprofile&  cImRspChgtoolsprofile )
    {
        m_retcode = cImRspChgtoolsprofile.m_retcode;
        m_toolTypes = cImRspChgtoolsprofile.m_toolTypes;
        m_timestamp = cImRspChgtoolsprofile.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< uint8_t >&  GetToolTypes () const { return m_toolTypes; }
    bool SetToolTypes ( const VECTOR< uint8_t >&  vecToolTypes )
    {
        m_toolTypes = vecToolTypes;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< uint8_t > m_toolTypes;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChgtoolsprofile::Size() const
{
    uint32_t nSize = 17;
    nSize += m_toolTypes.size() * 1;
    return nSize;
}

class PROTOCOL_LIB CImReqPeerinfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_PEERINFO
    };
    CImReqPeerinfo()
    {
    }

    ~CImReqPeerinfo() { }
    CImReqPeerinfo(const string&  strTargetId)
    {
        m_targetId = strTargetId;
    }
    CImReqPeerinfo&  operator=( const CImReqPeerinfo&  cImReqPeerinfo )
    {
        m_targetId = cImReqPeerinfo.m_targetId;
        return *this;
    }

    const string&  GetTargetId () const { return m_targetId; }
    bool SetTargetId ( const string&  strTargetId )
    {
        if(strTargetId.size() > 64)
            return false;
        m_targetId = strTargetId;
        return true;
    }
private:
    string m_targetId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqPeerinfo::Size() const
{
    uint32_t nSize = 6;
    nSize += m_targetId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspPeerinfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_PEERINFO
    };
    CImRspPeerinfo()
    {
    }

    ~CImRspPeerinfo() { }
    CImRspPeerinfo(const uint32_t&  dwRetcode, const string&  strTargetId, const uint32_t&  dwClinetip, const string&  strVersion, const uint8_t&  chBasicStatus, const uint8_t&  chPredefStatus, const uint8_t&  chAddcontactFlag, const uint8_t&  chSendmsgFlag, const uint8_t&  chReverseContact)
    {
        m_retcode = dwRetcode;
        m_targetId = strTargetId;
        m_clinetip = dwClinetip;
        m_version = strVersion;
        m_basicStatus = chBasicStatus;
        m_predefStatus = chPredefStatus;
        m_addcontactFlag = chAddcontactFlag;
        m_sendmsgFlag = chSendmsgFlag;
        m_reverseContact = chReverseContact;
    }
    CImRspPeerinfo&  operator=( const CImRspPeerinfo&  cImRspPeerinfo )
    {
        m_retcode = cImRspPeerinfo.m_retcode;
        m_targetId = cImRspPeerinfo.m_targetId;
        m_clinetip = cImRspPeerinfo.m_clinetip;
        m_version = cImRspPeerinfo.m_version;
        m_basicStatus = cImRspPeerinfo.m_basicStatus;
        m_predefStatus = cImRspPeerinfo.m_predefStatus;
        m_addcontactFlag = cImRspPeerinfo.m_addcontactFlag;
        m_sendmsgFlag = cImRspPeerinfo.m_sendmsgFlag;
        m_reverseContact = cImRspPeerinfo.m_reverseContact;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetTargetId () const { return m_targetId; }
    bool SetTargetId ( const string&  strTargetId )
    {
        if(strTargetId.size() > 64)
            return false;
        m_targetId = strTargetId;
        return true;
    }
    const uint32_t&  GetClinetip () const { return m_clinetip; }
    bool SetClinetip ( const uint32_t&  dwClinetip )
    {
        m_clinetip = dwClinetip;
        return true;
    }
    const string&  GetVersion () const { return m_version; }
    bool SetVersion ( const string&  strVersion )
    {
        if(strVersion.size() > 128)
            return false;
        m_version = strVersion;
        return true;
    }
    const uint8_t&  GetBasicStatus () const { return m_basicStatus; }
    bool SetBasicStatus ( const uint8_t&  chBasicStatus )
    {
        m_basicStatus = chBasicStatus;
        return true;
    }
    const uint8_t&  GetPredefStatus () const { return m_predefStatus; }
    bool SetPredefStatus ( const uint8_t&  chPredefStatus )
    {
        m_predefStatus = chPredefStatus;
        return true;
    }
    const uint8_t&  GetAddcontactFlag () const { return m_addcontactFlag; }
    bool SetAddcontactFlag ( const uint8_t&  chAddcontactFlag )
    {
        m_addcontactFlag = chAddcontactFlag;
        return true;
    }
    const uint8_t&  GetSendmsgFlag () const { return m_sendmsgFlag; }
    bool SetSendmsgFlag ( const uint8_t&  chSendmsgFlag )
    {
        m_sendmsgFlag = chSendmsgFlag;
        return true;
    }
    const uint8_t&  GetReverseContact () const { return m_reverseContact; }
    bool SetReverseContact ( const uint8_t&  chReverseContact )
    {
        m_reverseContact = chReverseContact;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_targetId;
    uint32_t m_clinetip;
    string m_version;
    uint8_t m_basicStatus;
    uint8_t m_predefStatus;
    uint8_t m_addcontactFlag;
    uint8_t m_sendmsgFlag;
    uint8_t m_reverseContact;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspPeerinfo::Size() const
{
    uint32_t nSize = 31;
    nSize += m_targetId.length();
    nSize += m_version.length();
    return nSize;
}

class PROTOCOL_LIB CImReqSubscribeInfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_SUBSCRIBE_INFO
    };
    CImReqSubscribeInfo()
    {
    }

    ~CImReqSubscribeInfo() { }
    CImReqSubscribeInfo(const VECTOR< string >&  vecTargetList)
    {
        m_targetList = vecTargetList;
    }
    CImReqSubscribeInfo&  operator=( const CImReqSubscribeInfo&  cImReqSubscribeInfo )
    {
        m_targetList = cImReqSubscribeInfo.m_targetList;
        return *this;
    }

    const VECTOR< string >&  GetTargetList () const { return m_targetList; }
    bool SetTargetList ( const VECTOR< string >&  vecTargetList )
    {
        m_targetList = vecTargetList;
        return true;
    }
private:
    VECTOR< string > m_targetList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqSubscribeInfo::Size() const
{
    uint32_t nSize = 7;
    nSize += m_targetList.size() * 4;
    for(uint32_t i = 0; i < m_targetList.size(); i++)
    {
        nSize += m_targetList[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImRspSubscribeInfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_SUBSCRIBE_INFO
    };
    CImRspSubscribeInfo()
    {
    }

    ~CImRspSubscribeInfo() { }
    CImRspSubscribeInfo(const uint32_t&  dwRetcode, const VECTOR< SUserStatus >&  vecStatusList)
    {
        m_retcode = dwRetcode;
        m_statusList = vecStatusList;
    }
    CImRspSubscribeInfo&  operator=( const CImRspSubscribeInfo&  cImRspSubscribeInfo )
    {
        m_retcode = cImRspSubscribeInfo.m_retcode;
        m_statusList = cImRspSubscribeInfo.m_statusList;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SUserStatus >&  GetStatusList () const { return m_statusList; }
    bool SetStatusList ( const VECTOR< SUserStatus >&  vecStatusList )
    {
        m_statusList = vecStatusList;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SUserStatus > m_statusList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspSubscribeInfo::Size() const
{
    uint32_t nSize = 12;
    for(uint32_t i = 0; i < m_statusList.size(); i++)
    {
        nSize += m_statusList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqDisubscribeInfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_DISUBSCRIBE_INFO
    };
    CImReqDisubscribeInfo()
    {
    }

    ~CImReqDisubscribeInfo() { }
    CImReqDisubscribeInfo(const VECTOR< string >&  vecTargets)
    {
        m_targets = vecTargets;
    }
    CImReqDisubscribeInfo&  operator=( const CImReqDisubscribeInfo&  cImReqDisubscribeInfo )
    {
        m_targets = cImReqDisubscribeInfo.m_targets;
        return *this;
    }

    const VECTOR< string >&  GetTargets () const { return m_targets; }
    bool SetTargets ( const VECTOR< string >&  vecTargets )
    {
        m_targets = vecTargets;
        return true;
    }
private:
    VECTOR< string > m_targets;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqDisubscribeInfo::Size() const
{
    uint32_t nSize = 7;
    nSize += m_targets.size() * 4;
    for(uint32_t i = 0; i < m_targets.size(); i++)
    {
        nSize += m_targets[i].length();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqGetftsaddr : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETFTSADDR
    };
    CImReqGetftsaddr()
    {
    }

    ~CImReqGetftsaddr() { }
    CImReqGetftsaddr(const string&  strSessionId, const uint16_t&  wType)
    {
        m_sessionId = strSessionId;
        m_type = wType;
    }
    CImReqGetftsaddr&  operator=( const CImReqGetftsaddr&  cImReqGetftsaddr )
    {
        m_sessionId = cImReqGetftsaddr.m_sessionId;
        m_type = cImReqGetftsaddr.m_type;
        return *this;
    }

    const string&  GetSessionId () const { return m_sessionId; }
    bool SetSessionId ( const string&  strSessionId )
    {
        if(strSessionId.size() > 64)
            return false;
        m_sessionId = strSessionId;
        return true;
    }
    const uint16_t&  GetType () const { return m_type; }
    bool SetType ( const uint16_t&  wType )
    {
        m_type = wType;
        return true;
    }
private:
    string m_sessionId;
    uint16_t m_type;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetftsaddr::Size() const
{
    uint32_t nSize = 9;
    nSize += m_sessionId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspGetftsaddr : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETFTSADDR
    };
    CImRspGetftsaddr()
    {
    }

    ~CImRspGetftsaddr() { }
    CImRspGetftsaddr(const uint32_t&  dwRetcode, const string&  strServerIp, const uint16_t&  wServerPort, const string&  strSessionId, const uint16_t&  wType, const uint32_t&  dwSessionsum)
    {
        m_retcode = dwRetcode;
        m_serverIp = strServerIp;
        m_serverPort = wServerPort;
        m_sessionId = strSessionId;
        m_type = wType;
        m_sessionsum = dwSessionsum;
    }
    CImRspGetftsaddr&  operator=( const CImRspGetftsaddr&  cImRspGetftsaddr )
    {
        m_retcode = cImRspGetftsaddr.m_retcode;
        m_serverIp = cImRspGetftsaddr.m_serverIp;
        m_serverPort = cImRspGetftsaddr.m_serverPort;
        m_sessionId = cImRspGetftsaddr.m_sessionId;
        m_type = cImRspGetftsaddr.m_type;
        m_sessionsum = cImRspGetftsaddr.m_sessionsum;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetServerIp () const { return m_serverIp; }
    bool SetServerIp ( const string&  strServerIp )
    {
        if(strServerIp.size() > 15)
            return false;
        m_serverIp = strServerIp;
        return true;
    }
    const uint16_t&  GetServerPort () const { return m_serverPort; }
    bool SetServerPort ( const uint16_t&  wServerPort )
    {
        m_serverPort = wServerPort;
        return true;
    }
    const string&  GetSessionId () const { return m_sessionId; }
    bool SetSessionId ( const string&  strSessionId )
    {
        if(strSessionId.size() > 64)
            return false;
        m_sessionId = strSessionId;
        return true;
    }
    const uint16_t&  GetType () const { return m_type; }
    bool SetType ( const uint16_t&  wType )
    {
        m_type = wType;
        return true;
    }
    const uint32_t&  GetSessionsum () const { return m_sessionsum; }
    bool SetSessionsum ( const uint32_t&  dwSessionsum )
    {
        m_sessionsum = dwSessionsum;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_serverIp;
    uint16_t m_serverPort;
    string m_sessionId;
    uint16_t m_type;
    uint32_t m_sessionsum;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetftsaddr::Size() const
{
    uint32_t nSize = 27;
    nSize += m_serverIp.length();
    nSize += m_sessionId.length();
    return nSize;
}

class PROTOCOL_LIB CImReqChgportrait : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGPORTRAIT
    };
    CImReqChgportrait()
    {
    }

    ~CImReqChgportrait() { }
    CImReqChgportrait(const string&  strPortraitid)
    {
        m_portraitid = strPortraitid;
    }
    CImReqChgportrait&  operator=( const CImReqChgportrait&  cImReqChgportrait )
    {
        m_portraitid = cImReqChgportrait.m_portraitid;
        return *this;
    }

    const string&  GetPortraitid () const { return m_portraitid; }
    bool SetPortraitid ( const string&  strPortraitid )
    {
        m_portraitid = strPortraitid;
        return true;
    }
private:
    string m_portraitid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgportrait::Size() const
{
    uint32_t nSize = 6;
    nSize += m_portraitid.length();
    return nSize;
}

class PROTOCOL_LIB CImReqChgsignature : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGSIGNATURE
    };
    CImReqChgsignature()
    {
    }

    ~CImReqChgsignature() { }
    CImReqChgsignature(const string&  strSignature)
    {
        m_signature = strSignature;
    }
    CImReqChgsignature&  operator=( const CImReqChgsignature&  cImReqChgsignature )
    {
        m_signature = cImReqChgsignature.m_signature;
        return *this;
    }

    const string&  GetSignature () const { return m_signature; }
    bool SetSignature ( const string&  strSignature )
    {
        if(strSignature.size() > 1024)
            return false;
        m_signature = strSignature;
        return true;
    }
private:
    string m_signature;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgsignature::Size() const
{
    uint32_t nSize = 6;
    nSize += m_signature.length();
    return nSize;
}

class PROTOCOL_LIB CImRspChgsignature : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGSIGNATURE
    };
    CImRspChgsignature()
    {
    }

    ~CImRspChgsignature() { }
    CImRspChgsignature(const string&  strSignature, const uint32_t&  dwRetcode)
    {
        m_signature = strSignature;
        m_retcode = dwRetcode;
    }
    CImRspChgsignature&  operator=( const CImRspChgsignature&  cImRspChgsignature )
    {
        m_signature = cImRspChgsignature.m_signature;
        m_retcode = cImRspChgsignature.m_retcode;
        return *this;
    }

    const string&  GetSignature () const { return m_signature; }
    bool SetSignature ( const string&  strSignature )
    {
        if(strSignature.size() > 1024)
            return false;
        m_signature = strSignature;
        return true;
    }
    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
private:
    string m_signature;
    uint32_t m_retcode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChgsignature::Size() const
{
    uint32_t nSize = 11;
    nSize += m_signature.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfOperationtip : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_OPERATIONTIP
    };
    CImNtfOperationtip()
    {
    }

    ~CImNtfOperationtip() { }
    CImNtfOperationtip(const string&  strContactId, const string&  strNtfmessage, const uint32_t&  dwNtftime)
    {
        m_contactId = strContactId;
        m_ntfmessage = strNtfmessage;
        m_ntftime = dwNtftime;
    }
    CImNtfOperationtip&  operator=( const CImNtfOperationtip&  cImNtfOperationtip )
    {
        m_contactId = cImNtfOperationtip.m_contactId;
        m_ntfmessage = cImNtfOperationtip.m_ntfmessage;
        m_ntftime = cImNtfOperationtip.m_ntftime;
        return *this;
    }

    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        m_contactId = strContactId;
        return true;
    }
    const string&  GetNtfmessage () const { return m_ntfmessage; }
    bool SetNtfmessage ( const string&  strNtfmessage )
    {
        m_ntfmessage = strNtfmessage;
        return true;
    }
    const uint32_t&  GetNtftime () const { return m_ntftime; }
    bool SetNtftime ( const uint32_t&  dwNtftime )
    {
        m_ntftime = dwNtftime;
        return true;
    }
private:
    string m_contactId;
    string m_ntfmessage;
    uint32_t m_ntftime;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfOperationtip::Size() const
{
    uint32_t nSize = 16;
    nSize += m_contactId.length();
    nSize += m_ntfmessage.length();
    return nSize;
}

struct SBindingInfo
{
public:
    SBindingInfo()
    {
    }

    ~SBindingInfo() { }
    SBindingInfo(const string&  strUserId, const string&  strPassword)
    {
        m_userId = strUserId;
        m_password = strPassword;
    }
    SBindingInfo&  operator=( const SBindingInfo&  sBindingInfo )
    {
        m_userId = sBindingInfo.m_userId;
        m_password = sBindingInfo.m_password;
        return *this;
    }

    string m_userId;
    string m_password;

public:
    uint32_t Size() const;
};

inline uint32_t SBindingInfo::Size() const
{
    uint32_t nSize = 11;
    nSize += m_userId.length();
    nSize += m_password.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SBindingInfo&  sBindingInfo );
CPackData& operator>> ( CPackData& cPackData, SBindingInfo&  sBindingInfo );

class PROTOCOL_LIB CImReqAddbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDBINDING
    };
    CImReqAddbinding()
    {
    }

    ~CImReqAddbinding() { }
    CImReqAddbinding(const uint32_t&  dwAddflag, const SBindingInfo&  sBinding)
    {
        m_addflag = dwAddflag;
        m_binding = sBinding;
    }
    CImReqAddbinding&  operator=( const CImReqAddbinding&  cImReqAddbinding )
    {
        m_addflag = cImReqAddbinding.m_addflag;
        m_binding = cImReqAddbinding.m_binding;
        return *this;
    }

    const uint32_t&  GetAddflag () const { return m_addflag; }
    bool SetAddflag ( const uint32_t&  dwAddflag )
    {
        m_addflag = dwAddflag;
        return true;
    }
    const SBindingInfo&  GetBinding () const { return m_binding; }
    bool SetBinding ( const SBindingInfo&  sBinding )
    {
        m_binding = sBinding;
        return true;
    }
private:
    uint32_t m_addflag;
    SBindingInfo m_binding;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddbinding::Size() const
{
    uint32_t nSize = 7;
    nSize += m_binding.Size();
    return nSize;
}

class PROTOCOL_LIB CImRspAddbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDBINDING
    };
    CImRspAddbinding()
    {
    }

    ~CImRspAddbinding() { }
    CImRspAddbinding(const uint32_t&  dwRetcode, const string&  strUid, const string&  strWebmd5pw)
    {
        m_retcode = dwRetcode;
        m_uid = strUid;
        m_webmd5pw = strWebmd5pw;
    }
    CImRspAddbinding&  operator=( const CImRspAddbinding&  cImRspAddbinding )
    {
        m_retcode = cImRspAddbinding.m_retcode;
        m_uid = cImRspAddbinding.m_uid;
        m_webmd5pw = cImRspAddbinding.m_webmd5pw;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        m_uid = strUid;
        return true;
    }
    const string&  GetWebmd5pw () const { return m_webmd5pw; }
    bool SetWebmd5pw ( const string&  strWebmd5pw )
    {
        if(strWebmd5pw.size() > 48)
            return false;
        m_webmd5pw = strWebmd5pw;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_uid;
    string m_webmd5pw;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddbinding::Size() const
{
    uint32_t nSize = 16;
    nSize += m_uid.length();
    nSize += m_webmd5pw.length();
    return nSize;
}

class PROTOCOL_LIB CImReqChgbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHGBINDING
    };
    CImReqChgbinding()
    {
    }

    ~CImReqChgbinding() { }
    CImReqChgbinding(const SBindingInfo&  sBinding)
    {
        m_binding = sBinding;
    }
    CImReqChgbinding&  operator=( const CImReqChgbinding&  cImReqChgbinding )
    {
        m_binding = cImReqChgbinding.m_binding;
        return *this;
    }

    const SBindingInfo&  GetBinding () const { return m_binding; }
    bool SetBinding ( const SBindingInfo&  sBinding )
    {
        m_binding = sBinding;
        return true;
    }
private:
    SBindingInfo m_binding;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqChgbinding::Size() const
{
    uint32_t nSize = 2;
    nSize += m_binding.Size();
    return nSize;
}

class PROTOCOL_LIB CImRspChgbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHGBINDING
    };
    CImRspChgbinding()
    {
    }

    ~CImRspChgbinding() { }
    CImRspChgbinding(const uint32_t&  dwRetcode, const string&  strWebmd5pw)
    {
        m_retcode = dwRetcode;
        m_webmd5pw = strWebmd5pw;
    }
    CImRspChgbinding&  operator=( const CImRspChgbinding&  cImRspChgbinding )
    {
        m_retcode = cImRspChgbinding.m_retcode;
        m_webmd5pw = cImRspChgbinding.m_webmd5pw;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetWebmd5pw () const { return m_webmd5pw; }
    bool SetWebmd5pw ( const string&  strWebmd5pw )
    {
        if(strWebmd5pw.size() > 48)
            return false;
        m_webmd5pw = strWebmd5pw;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_webmd5pw;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspChgbinding::Size() const
{
    uint32_t nSize = 11;
    nSize += m_webmd5pw.length();
    return nSize;
}

class PROTOCOL_LIB CImReqDelbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_DELBINDING
    };
    CImReqDelbinding()
    {
    }

    ~CImReqDelbinding() { }
    CImReqDelbinding(const string&  strUserId)
    {
        m_userId = strUserId;
    }
    CImReqDelbinding&  operator=( const CImReqDelbinding&  cImReqDelbinding )
    {
        m_userId = cImReqDelbinding.m_userId;
        return *this;
    }

    const string&  GetUserId () const { return m_userId; }
    bool SetUserId ( const string&  strUserId )
    {
        if(strUserId.size() > 64)
            return false;
        m_userId = strUserId;
        return true;
    }
private:
    string m_userId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqDelbinding::Size() const
{
    uint32_t nSize = 6;
    nSize += m_userId.length();
    return nSize;
}

class PROTOCOL_LIB CImRspDelbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_DELBINDING
    };
    CImRspDelbinding()
    {
    }

    ~CImRspDelbinding() { }
    CImRspDelbinding(const uint32_t&  dwRetcode)
    {
        m_retcode = dwRetcode;
    }
    CImRspDelbinding&  operator=( const CImRspDelbinding&  cImRspDelbinding )
    {
        m_retcode = cImRspDelbinding.m_retcode;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
private:
    uint32_t m_retcode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspDelbinding::Size() const
{
    return 6;
}
class PROTOCOL_LIB CImReqGetbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETBINDING
    };
    CImReqGetbinding()
    {
    }

    ~CImReqGetbinding() { }
public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetbinding::Size() const
{
    return 1;
}
class PROTOCOL_LIB CImRspGetbinding : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETBINDING
    };
    CImRspGetbinding()
    {
    }

    ~CImRspGetbinding() { }
    CImRspGetbinding(const uint32_t&  dwRetcode, const VECTOR< SBindingInfo >&  vecBindingList)
    {
        m_retcode = dwRetcode;
        m_bindingList = vecBindingList;
    }
    CImRspGetbinding&  operator=( const CImRspGetbinding&  cImRspGetbinding )
    {
        m_retcode = cImRspGetbinding.m_retcode;
        m_bindingList = cImRspGetbinding.m_bindingList;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SBindingInfo >&  GetBindingList () const { return m_bindingList; }
    bool SetBindingList ( const VECTOR< SBindingInfo >&  vecBindingList )
    {
        m_bindingList = vecBindingList;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SBindingInfo > m_bindingList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetbinding::Size() const
{
    uint32_t nSize = 12;
    for(uint32_t i = 0; i < m_bindingList.size(); i++)
    {
        nSize += m_bindingList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqGetPwdtoken : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GET_PWDTOKEN
    };
    CImReqGetPwdtoken()
    {
    }

    ~CImReqGetPwdtoken() { }
    CImReqGetPwdtoken(const string&  strUid)
    {
        m_uid = strUid;
    }
    CImReqGetPwdtoken&  operator=( const CImReqGetPwdtoken&  cImReqGetPwdtoken )
    {
        m_uid = cImReqGetPwdtoken.m_uid;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        m_uid = strUid;
        return true;
    }
private:
    string m_uid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetPwdtoken::Size() const
{
    uint32_t nSize = 6;
    nSize += m_uid.length();
    return nSize;
}

class PROTOCOL_LIB CImRspGetPwdtoken : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GET_PWDTOKEN
    };
    CImRspGetPwdtoken()
    {
    }

    ~CImRspGetPwdtoken() { }
    CImRspGetPwdtoken(const uint32_t&  dwRetcode, const string&  strUid, const string&  strToken)
    {
        m_retcode = dwRetcode;
        m_uid = strUid;
        m_token = strToken;
    }
    CImRspGetPwdtoken&  operator=( const CImRspGetPwdtoken&  cImRspGetPwdtoken )
    {
        m_retcode = cImRspGetPwdtoken.m_retcode;
        m_uid = cImRspGetPwdtoken.m_uid;
        m_token = cImRspGetPwdtoken.m_token;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        m_uid = strUid;
        return true;
    }
    const string&  GetToken () const { return m_token; }
    bool SetToken ( const string&  strToken )
    {
        m_token = strToken;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_uid;
    string m_token;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetPwdtoken::Size() const
{
    uint32_t nSize = 16;
    nSize += m_uid.length();
    nSize += m_token.length();
    return nSize;
}

class PROTOCOL_LIB CImReqCankeysearch : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CANKEYSEARCH
    };
    CImReqCankeysearch()
    {
    }

    ~CImReqCankeysearch() { }
    CImReqCankeysearch(const uint8_t&  chEnabled)
    {
        m_enabled = chEnabled;
    }
    CImReqCankeysearch&  operator=( const CImReqCankeysearch&  cImReqCankeysearch )
    {
        m_enabled = cImReqCankeysearch.m_enabled;
        return *this;
    }

    const uint8_t&  GetEnabled () const { return m_enabled; }
    bool SetEnabled ( const uint8_t&  chEnabled )
    {
        m_enabled = chEnabled;
        return true;
    }
private:
    uint8_t m_enabled;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqCankeysearch::Size() const
{
    return 3;
}
class PROTOCOL_LIB CImReqGetwebSession : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GETWEB_SESSION
    };
    CImReqGetwebSession()
    {
    }

    ~CImReqGetwebSession() { }
public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetwebSession::Size() const
{
    return 1;
}
class PROTOCOL_LIB CImRspGetwebSession : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GETWEB_SESSION
    };
    CImRspGetwebSession()
    {
    }

    ~CImRspGetwebSession() { }
    CImRspGetwebSession(const uint32_t&  dwRetcode, const uint32_t&  dwExpiretime, const string&  strSessionNo)
    {
        m_retcode = dwRetcode;
        m_expiretime = dwExpiretime;
        m_sessionNo = strSessionNo;
    }
    CImRspGetwebSession&  operator=( const CImRspGetwebSession&  cImRspGetwebSession )
    {
        m_retcode = cImRspGetwebSession.m_retcode;
        m_expiretime = cImRspGetwebSession.m_expiretime;
        m_sessionNo = cImRspGetwebSession.m_sessionNo;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint32_t&  GetExpiretime () const { return m_expiretime; }
    bool SetExpiretime ( const uint32_t&  dwExpiretime )
    {
        m_expiretime = dwExpiretime;
        return true;
    }
    const string&  GetSessionNo () const { return m_sessionNo; }
    bool SetSessionNo ( const string&  strSessionNo )
    {
        m_sessionNo = strSessionNo;
        return true;
    }
private:
    uint32_t m_retcode;
    uint32_t m_expiretime;
    string m_sessionNo;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetwebSession::Size() const
{
    uint32_t nSize = 16;
    nSize += m_sessionNo.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfUpdateUsrextinfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_UPDATE_USREXTINFO
    };
    CImNtfUpdateUsrextinfo()
    {
    }

    ~CImNtfUpdateUsrextinfo() { }
    CImNtfUpdateUsrextinfo(const string&  strContactId, const string&  strType, const string&  strValue)
    {
        m_contactId = strContactId;
        m_type = strType;
        m_value = strValue;
    }
    CImNtfUpdateUsrextinfo&  operator=( const CImNtfUpdateUsrextinfo&  cImNtfUpdateUsrextinfo )
    {
        m_contactId = cImNtfUpdateUsrextinfo.m_contactId;
        m_type = cImNtfUpdateUsrextinfo.m_type;
        m_value = cImNtfUpdateUsrextinfo.m_value;
        return *this;
    }

    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        m_contactId = strContactId;
        return true;
    }
    const string&  GetType () const { return m_type; }
    bool SetType ( const string&  strType )
    {
        m_type = strType;
        return true;
    }
    const string&  GetValue () const { return m_value; }
    bool SetValue ( const string&  strValue )
    {
        m_value = strValue;
        return true;
    }
private:
    string m_contactId;
    string m_type;
    string m_value;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfUpdateUsrextinfo::Size() const
{
    uint32_t nSize = 16;
    nSize += m_contactId.length();
    nSize += m_type.length();
    nSize += m_value.length();
    return nSize;
}

#ifdef USER_OLD_UDB_PROFILE_PROTOCOL
class PROTOCOL_LIB CImReqUserudbprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_USERUDBPROFILE
    };
    CImReqUserudbprofile()
    {
    }

    ~CImReqUserudbprofile() { }
public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqUserudbprofile::Size() const
{
    return 1;
}
class PROTOCOL_LIB CImRspUserudbprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_USERUDBPROFILE
    };
    CImRspUserudbprofile()
    {
    }

    ~CImRspUserudbprofile() { }
    CImRspUserudbprofile(const uint32_t&  dwRetcode, const map< string,string >&  mapProfilelist)
    {
        m_retcode = dwRetcode;
        m_profilelist = mapProfilelist;
    }
    CImRspUserudbprofile&  operator=( const CImRspUserudbprofile&  cImRspUserudbprofile )
    {
        m_retcode = cImRspUserudbprofile.m_retcode;
        m_profilelist = cImRspUserudbprofile.m_profilelist;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const map< string,string >&  GetProfilelist () const { return m_profilelist; }
    bool SetProfilelist ( const map< string,string >&  mapProfilelist )
    {
        m_profilelist = mapProfilelist;
        return true;
    }
private:
    uint32_t m_retcode;
    map< string,string > m_profilelist;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspUserudbprofile::Size() const
{
    uint32_t nSize = 10;
    nSize += m_profilelist.size() * 8;
    {
        map< string,string >::const_iterator itr;
        for(itr = m_profilelist.begin(); itr != m_profilelist.end(); ++itr)
        {
            nSize += itr->first.length();
            nSize += itr->second.length();
        }
    }
    return nSize;
}
#else
class PROTOCOL_LIB CImReqUserudbprofile : public CPackData
{
public:
	enum
	{
		CMD_ID = IM_REQ_USERUDBPROFILE
	};
	CImReqUserudbprofile() : m_uid("magic")
	{
	}

	~CImReqUserudbprofile() { }
	CImReqUserudbprofile(const string&  strUid)
	{
		m_uid = strUid;
	}
	CImReqUserudbprofile&  operator=( const CImReqUserudbprofile&  cImReqUserudbprofile )
	{
		m_uid = cImReqUserudbprofile.m_uid;
		return *this;
	}

	const string&  GetUid () const { return m_uid; }
	bool SetUid ( const string&  strUid )
	{
		m_uid = strUid;
		return true;
	}
private:
	string m_uid;

public:
	CScHead m_scHead;
	void PackHead(string& strData);
	void PackBody(string& strData);
	void PackData(string& strData, const string& strKey = "");
	PACKRETCODE UnpackBody(string& strData);
	PACKRETCODE UnpackData(string& strData, const string& strKey = "");
	uint32_t Size() const;
};

inline uint32_t CImReqUserudbprofile::Size() const
{
	uint32_t nSize = 6;
	nSize += m_uid.length();
	return nSize;
}

class PROTOCOL_LIB CImRspUserudbprofile : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_USERUDBPROFILE
    };
    CImRspUserudbprofile()
    {
    }

    ~CImRspUserudbprofile() { }
    CImRspUserudbprofile(const uint32_t&  dwRetcode, const map< string,string >&  mapProfilelist, const string&  strUid)
    {
        m_retcode = dwRetcode;
        m_profilelist = mapProfilelist;
        m_uid = strUid;
    }
    CImRspUserudbprofile&  operator=( const CImRspUserudbprofile&  cImRspUserudbprofile )
    {
        m_retcode = cImRspUserudbprofile.m_retcode;
        m_profilelist = cImRspUserudbprofile.m_profilelist;
        m_uid = cImRspUserudbprofile.m_uid;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const map< string,string >&  GetProfilelist () const { return m_profilelist; }
    bool SetProfilelist ( const map< string,string >&  mapProfilelist )
    {
        m_profilelist = mapProfilelist;
        return true;
    }
    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        m_uid = strUid;
        return true;
    }
private:
    uint32_t m_retcode;
    map< string,string > m_profilelist;
    string m_uid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspUserudbprofile::Size() const
{
    uint32_t nSize = 15;
    nSize += m_profilelist.size() * 8;
    {
        map< string,string >::const_iterator itr;
        for(itr = m_profilelist.begin(); itr != m_profilelist.end(); ++itr)
        {
            nSize += itr->first.length();
            nSize += itr->second.length();
        }
    }
    nSize += m_uid.length();
    return nSize;
}
#endif //USER_OLD_UDB_PROFILE_PROTOCOL

class PROTOCOL_LIB CImReqPeerVerifyConfig : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_PEER_VERIFY_CONFIG
    };
    CImReqPeerVerifyConfig()
    {
    }

    ~CImReqPeerVerifyConfig() { }
    CImReqPeerVerifyConfig(const uint8_t&  chClientid, const string&  strContactId)
    {
        m_clientid = chClientid;
        m_contactId = strContactId;
    }
    CImReqPeerVerifyConfig&  operator=( const CImReqPeerVerifyConfig&  cImReqPeerVerifyConfig )
    {
        m_clientid = cImReqPeerVerifyConfig.m_clientid;
        m_contactId = cImReqPeerVerifyConfig.m_contactId;
        return *this;
    }

    const uint8_t&  GetClientid () const { return m_clientid; }
    bool SetClientid ( const uint8_t&  chClientid )
    {
        m_clientid = chClientid;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        m_contactId = strContactId;
        return true;
    }
private:
    uint8_t m_clientid;
    string m_contactId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqPeerVerifyConfig::Size() const
{
    uint32_t nSize = 8;
    nSize += m_contactId.length();
    return nSize;
}

enum VERIFY_FLAG
{
    OK                          = 0,
    VERIFY                      = 0x1,
    DENY                        = 0x2,

};

class PROTOCOL_LIB CImRspPeerVerifyConfig : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_PEER_VERIFY_CONFIG
    };
    CImRspPeerVerifyConfig()
    {
    }

    ~CImRspPeerVerifyConfig() { }
    CImRspPeerVerifyConfig(const uint8_t&  chClientid, const string&  strContactId, const uint32_t&  dwRetcode, const string&  strRetlongid, const string&  strRetshowname)
    {
        m_clientid = chClientid;
        m_contactId = strContactId;
        m_retcode = dwRetcode;
        m_retlongid = strRetlongid;
        m_retshowname = strRetshowname;
    }
    CImRspPeerVerifyConfig&  operator=( const CImRspPeerVerifyConfig&  cImRspPeerVerifyConfig )
    {
        m_clientid = cImRspPeerVerifyConfig.m_clientid;
        m_contactId = cImRspPeerVerifyConfig.m_contactId;
        m_retcode = cImRspPeerVerifyConfig.m_retcode;
        m_retlongid = cImRspPeerVerifyConfig.m_retlongid;
        m_retshowname = cImRspPeerVerifyConfig.m_retshowname;
        return *this;
    }

    const uint8_t&  GetClientid () const { return m_clientid; }
    bool SetClientid ( const uint8_t&  chClientid )
    {
        m_clientid = chClientid;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        m_contactId = strContactId;
        return true;
    }
    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetRetlongid () const { return m_retlongid; }
    bool SetRetlongid ( const string&  strRetlongid )
    {
        m_retlongid = strRetlongid;
        return true;
    }
    const string&  GetRetshowname () const { return m_retshowname; }
    bool SetRetshowname ( const string&  strRetshowname )
    {
        m_retshowname = strRetshowname;
        return true;
    }
private:
    uint8_t m_clientid;
    string m_contactId;
    uint32_t m_retcode;
    string m_retlongid;
    string m_retshowname;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspPeerVerifyConfig::Size() const
{
    uint32_t nSize = 23;
    nSize += m_contactId.length();
    nSize += m_retlongid.length();
    nSize += m_retshowname.length();
    return nSize;
}

class PROTOCOL_LIB CImReqCheckAuthcode : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_CHECK_AUTHCODE
    };
    CImReqCheckAuthcode() : m_mode(0)
    {
    }

    ~CImReqCheckAuthcode() { }
    CImReqCheckAuthcode(const string&  strSessionId, const string&  strAuthCode, const uint8_t&  chMode)
    {
        m_sessionId = strSessionId;
        m_authCode = strAuthCode;
        m_mode = chMode;
    }
    CImReqCheckAuthcode&  operator=( const CImReqCheckAuthcode&  cImReqCheckAuthcode )
    {
        m_sessionId = cImReqCheckAuthcode.m_sessionId;
        m_authCode = cImReqCheckAuthcode.m_authCode;
        m_mode = cImReqCheckAuthcode.m_mode;
        return *this;
    }

    const string&  GetSessionId () const { return m_sessionId; }
    bool SetSessionId ( const string&  strSessionId )
    {
        m_sessionId = strSessionId;
        return true;
    }
    const string&  GetAuthCode () const { return m_authCode; }
    bool SetAuthCode ( const string&  strAuthCode )
    {
        m_authCode = strAuthCode;
        return true;
    }
    const uint8_t&  GetMode () const { return m_mode; }
    bool SetMode ( const uint8_t&  chMode )
    {
        m_mode = chMode;
        return true;
    }
private:
    string m_sessionId;
    string m_authCode;
    uint8_t m_mode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqCheckAuthcode::Size() const
{
    uint32_t nSize = 13;
    nSize += m_sessionId.length();
    nSize += m_authCode.length();
    return nSize;
}

class PROTOCOL_LIB CImRspCheckAuthcode : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_CHECK_AUTHCODE
    };
    CImRspCheckAuthcode()
    {
    }

    ~CImRspCheckAuthcode() { }
    CImRspCheckAuthcode(const uint8_t&  chRetcode, const string&  strSessionId, const string&  strAuthCode)
    {
        m_retcode = chRetcode;
        m_sessionId = strSessionId;
        m_authCode = strAuthCode;
    }
    CImRspCheckAuthcode&  operator=( const CImRspCheckAuthcode&  cImRspCheckAuthcode )
    {
        m_retcode = cImRspCheckAuthcode.m_retcode;
        m_sessionId = cImRspCheckAuthcode.m_sessionId;
        m_authCode = cImRspCheckAuthcode.m_authCode;
        return *this;
    }

    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const string&  GetSessionId () const { return m_sessionId; }
    bool SetSessionId ( const string&  strSessionId )
    {
        m_sessionId = strSessionId;
        return true;
    }
    const string&  GetAuthCode () const { return m_authCode; }
    bool SetAuthCode ( const string&  strAuthCode )
    {
        m_authCode = strAuthCode;
        return true;
    }
private:
    uint8_t m_retcode;
    string m_sessionId;
    string m_authCode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspCheckAuthcode::Size() const
{
    uint32_t nSize = 13;
    nSize += m_sessionId.length();
    nSize += m_authCode.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfNeedAuthcode : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_NEED_AUTHCODE
    };
    CImNtfNeedAuthcode()
    {
    }

    ~CImNtfNeedAuthcode() { }
    CImNtfNeedAuthcode(const string&  strOrigPacket)
    {
        m_origPacket = strOrigPacket;
    }
    CImNtfNeedAuthcode&  operator=( const CImNtfNeedAuthcode&  cImNtfNeedAuthcode )
    {
        m_origPacket = cImNtfNeedAuthcode.m_origPacket;
        return *this;
    }

    const string&  GetOrigPacket () const { return m_origPacket; }
    bool SetOrigPacket ( const string&  strOrigPacket )
    {
        m_origPacket = strOrigPacket;
        return true;
    }
private:
    string m_origPacket;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfNeedAuthcode::Size() const
{
    uint32_t nSize = 6;
    nSize += m_origPacket.length();
    return nSize;
}

class PROTOCOL_LIB CImReqHelpLogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_LOGIN
    };
    CImReqHelpLogin()
    {
    }

    ~CImReqHelpLogin() { }
    CImReqHelpLogin(const string&  strUid, const uint8_t&  chStatus)
    {
        m_uid = strUid;
        m_status = chStatus;
    }
    CImReqHelpLogin&  operator=( const CImReqHelpLogin&  cImReqHelpLogin )
    {
        m_uid = cImReqHelpLogin.m_uid;
        m_status = cImReqHelpLogin.m_status;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetStatus () const { return m_status; }
    bool SetStatus ( const uint8_t&  chStatus )
    {
        m_status = chStatus;
        return true;
    }
private:
    string m_uid;
    uint8_t m_status;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpLogin::Size() const
{
    return 68;
}
struct SRecChildId
{
public:
    SRecChildId()
    {
    }

    ~SRecChildId() { }
    SRecChildId(const string&  strChildId, const string&  strChildNick)
    {
        m_childId = strChildId;
        m_childNick = strChildNick;
    }
    SRecChildId&  operator=( const SRecChildId&  sRecChildId )
    {
        m_childId = sRecChildId.m_childId;
        m_childNick = sRecChildId.m_childNick;
        return *this;
    }

    string m_childId;
    string m_childNick;

public:
    uint32_t Size() const;
};

inline uint32_t SRecChildId::Size() const
{
    return 99;
}
CPackData& operator<< ( CPackData& cPackData, const SRecChildId&  sRecChildId );
CPackData& operator>> ( CPackData& cPackData, SRecChildId&  sRecChildId );

class PROTOCOL_LIB CImRspHelpLogin : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_LOGIN
    };
    CImRspHelpLogin()
    {
    }

    ~CImRspHelpLogin() { }
    CImRspHelpLogin(const uint8_t&  chRetcode, const uint8_t&  chMulStatus, const string&  strParentUid, const VECTOR< SRecChildId >&  vecChildList)
    {
        m_retcode = chRetcode;
        m_mulStatus = chMulStatus;
        m_parentUid = strParentUid;
        m_childList = vecChildList;
    }
    CImRspHelpLogin&  operator=( const CImRspHelpLogin&  cImRspHelpLogin )
    {
        m_retcode = cImRspHelpLogin.m_retcode;
        m_mulStatus = cImRspHelpLogin.m_mulStatus;
        m_parentUid = cImRspHelpLogin.m_parentUid;
        m_childList = cImRspHelpLogin.m_childList;
        return *this;
    }

    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const uint8_t&  GetMulStatus () const { return m_mulStatus; }
    bool SetMulStatus ( const uint8_t&  chMulStatus )
    {
        m_mulStatus = chMulStatus;
        return true;
    }
    const string&  GetParentUid () const { return m_parentUid; }
    bool SetParentUid ( const string&  strParentUid )
    {
        if(strParentUid.size() > 64)
            return false;
        m_parentUid = strParentUid;
        return true;
    }
    const VECTOR< SRecChildId >&  GetChildList () const { return m_childList; }
    bool SetChildList ( const VECTOR< SRecChildId >&  vecChildList )
    {
        m_childList = vecChildList;
        return true;
    }
private:
    uint8_t m_retcode;
    uint8_t m_mulStatus;
    string m_parentUid;
    VECTOR< SRecChildId > m_childList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpLogin::Size() const
{
    uint32_t nSize = 74;
    for(uint32_t i = 0; i < m_childList.size(); i++)
    {
        nSize += m_childList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqHelpChgSrvMode : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_CHG_SRV_MODE
    };
    CImReqHelpChgSrvMode()
    {
    }

    ~CImReqHelpChgSrvMode() { }
    CImReqHelpChgSrvMode(const string&  strUid, const uint8_t&  chStatus)
    {
        m_uid = strUid;
        m_status = chStatus;
    }
    CImReqHelpChgSrvMode&  operator=( const CImReqHelpChgSrvMode&  cImReqHelpChgSrvMode )
    {
        m_uid = cImReqHelpChgSrvMode.m_uid;
        m_status = cImReqHelpChgSrvMode.m_status;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetStatus () const { return m_status; }
    bool SetStatus ( const uint8_t&  chStatus )
    {
        m_status = chStatus;
        return true;
    }
private:
    string m_uid;
    uint8_t m_status;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpChgSrvMode::Size() const
{
    return 68;
}
class PROTOCOL_LIB CImRspHelpChgSrvMode : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_CHG_SRV_MODE
    };
    CImRspHelpChgSrvMode()
    {
    }

    ~CImRspHelpChgSrvMode() { }
    CImRspHelpChgSrvMode(const string&  strUid, const uint8_t&  chRetcode)
    {
        m_uid = strUid;
        m_retcode = chRetcode;
    }
    CImRspHelpChgSrvMode&  operator=( const CImRspHelpChgSrvMode&  cImRspHelpChgSrvMode )
    {
        m_uid = cImRspHelpChgSrvMode.m_uid;
        m_retcode = cImRspHelpChgSrvMode.m_retcode;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
private:
    string m_uid;
    uint8_t m_retcode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpChgSrvMode::Size() const
{
    return 68;
}
class PROTOCOL_LIB CImReqHelpSetShareCid : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_SET_SHARE_CID
    };
    CImReqHelpSetShareCid()
    {
    }

    ~CImReqHelpSetShareCid() { }
    CImReqHelpSetShareCid(const string&  strUid, const string&  strCid, const uint8_t&  chType)
    {
        m_uid = strUid;
        m_cid = strCid;
        m_type = chType;
    }
    CImReqHelpSetShareCid&  operator=( const CImReqHelpSetShareCid&  cImReqHelpSetShareCid )
    {
        m_uid = cImReqHelpSetShareCid.m_uid;
        m_cid = cImReqHelpSetShareCid.m_cid;
        m_type = cImReqHelpSetShareCid.m_type;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetCid () const { return m_cid; }
    bool SetCid ( const string&  strCid )
    {
        if(strCid.size() > 64)
            return false;
        m_cid = strCid;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
private:
    string m_uid;
    string m_cid;
    uint8_t m_type;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpSetShareCid::Size() const
{
    return 133;
}
class PROTOCOL_LIB CImRspHelpSetShareCid : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_SET_SHARE_CID
    };
    CImRspHelpSetShareCid()
    {
    }

    ~CImRspHelpSetShareCid() { }
    CImRspHelpSetShareCid(const string&  strUid, const uint8_t&  chRetcode)
    {
        m_uid = strUid;
        m_retcode = chRetcode;
    }
    CImRspHelpSetShareCid&  operator=( const CImRspHelpSetShareCid&  cImRspHelpSetShareCid )
    {
        m_uid = cImRspHelpSetShareCid.m_uid;
        m_retcode = cImRspHelpSetShareCid.m_retcode;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
private:
    string m_uid;
    uint8_t m_retcode;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpSetShareCid::Size() const
{
    return 68;
}
class PROTOCOL_LIB CImReqHelpGetShareCid : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_GET_SHARE_CID
    };
    CImReqHelpGetShareCid()
    {
    }

    ~CImReqHelpGetShareCid() { }
    CImReqHelpGetShareCid(const string&  strUid, const string&  strCid, const uint8_t&  chType)
    {
        m_uid = strUid;
        m_cid = strCid;
        m_type = chType;
    }
    CImReqHelpGetShareCid&  operator=( const CImReqHelpGetShareCid&  cImReqHelpGetShareCid )
    {
        m_uid = cImReqHelpGetShareCid.m_uid;
        m_cid = cImReqHelpGetShareCid.m_cid;
        m_type = cImReqHelpGetShareCid.m_type;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetCid () const { return m_cid; }
    bool SetCid ( const string&  strCid )
    {
        if(strCid.size() > 64)
            return false;
        m_cid = strCid;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
private:
    string m_uid;
    string m_cid;
    uint8_t m_type;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpGetShareCid::Size() const
{
    return 133;
}
class PROTOCOL_LIB CImRspHelpGetShareCid : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_GET_SHARE_CID
    };
    CImRspHelpGetShareCid()
    {
    }

    ~CImRspHelpGetShareCid() { }
    CImRspHelpGetShareCid(const string&  strUid, const string&  strCid, const uint8_t&  chRetcode, const uint8_t&  chShared)
    {
        m_uid = strUid;
        m_cid = strCid;
        m_retcode = chRetcode;
        m_shared = chShared;
    }
    CImRspHelpGetShareCid&  operator=( const CImRspHelpGetShareCid&  cImRspHelpGetShareCid )
    {
        m_uid = cImRspHelpGetShareCid.m_uid;
        m_cid = cImRspHelpGetShareCid.m_cid;
        m_retcode = cImRspHelpGetShareCid.m_retcode;
        m_shared = cImRspHelpGetShareCid.m_shared;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetCid () const { return m_cid; }
    bool SetCid ( const string&  strCid )
    {
        if(strCid.size() > 64)
            return false;
        m_cid = strCid;
        return true;
    }
    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const uint8_t&  GetShared () const { return m_shared; }
    bool SetShared ( const uint8_t&  chShared )
    {
        m_shared = chShared;
        return true;
    }
private:
    string m_uid;
    string m_cid;
    uint8_t m_retcode;
    uint8_t m_shared;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpGetShareCid::Size() const
{
    return 135;
}
class PROTOCOL_LIB CImReqHelpGetChildOnline : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_GET_CHILD_ONLINE
    };
    CImReqHelpGetChildOnline()
    {
    }

    ~CImReqHelpGetChildOnline() { }
    CImReqHelpGetChildOnline(const string&  strUid, const string&  strCid)
    {
        m_uid = strUid;
        m_cid = strCid;
    }
    CImReqHelpGetChildOnline&  operator=( const CImReqHelpGetChildOnline&  cImReqHelpGetChildOnline )
    {
        m_uid = cImReqHelpGetChildOnline.m_uid;
        m_cid = cImReqHelpGetChildOnline.m_cid;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetCid () const { return m_cid; }
    bool SetCid ( const string&  strCid )
    {
        if(strCid.size() > 64)
            return false;
        m_cid = strCid;
        return true;
    }
private:
    string m_uid;
    string m_cid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpGetChildOnline::Size() const
{
    return 131;
}
class PROTOCOL_LIB CImRspHelpGetChildOnline : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_GET_CHILD_ONLINE
    };
    CImRspHelpGetChildOnline()
    {
    }

    ~CImRspHelpGetChildOnline() { }
    CImRspHelpGetChildOnline(const string&  strUid, const string&  strCid, const uint8_t&  chRetcode, const uint8_t&  chBasic, const string&  strStatusdef)
    {
        m_uid = strUid;
        m_cid = strCid;
        m_retcode = chRetcode;
        m_basic = chBasic;
        m_statusdef = strStatusdef;
    }
    CImRspHelpGetChildOnline&  operator=( const CImRspHelpGetChildOnline&  cImRspHelpGetChildOnline )
    {
        m_uid = cImRspHelpGetChildOnline.m_uid;
        m_cid = cImRspHelpGetChildOnline.m_cid;
        m_retcode = cImRspHelpGetChildOnline.m_retcode;
        m_basic = cImRspHelpGetChildOnline.m_basic;
        m_statusdef = cImRspHelpGetChildOnline.m_statusdef;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetCid () const { return m_cid; }
    bool SetCid ( const string&  strCid )
    {
        if(strCid.size() > 64)
            return false;
        m_cid = strCid;
        return true;
    }
    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const uint8_t&  GetBasic () const { return m_basic; }
    bool SetBasic ( const uint8_t&  chBasic )
    {
        m_basic = chBasic;
        return true;
    }
    const string&  GetStatusdef () const { return m_statusdef; }
    bool SetStatusdef ( const string&  strStatusdef )
    {
        if(strStatusdef.size() > 64)
            return false;
        m_statusdef = strStatusdef;
        return true;
    }
private:
    string m_uid;
    string m_cid;
    uint8_t m_retcode;
    uint8_t m_basic;
    string m_statusdef;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpGetChildOnline::Size() const
{
    return 200;
}
class PROTOCOL_LIB CImReqHelpGetOnlinechilds : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_GET_ONLINECHILDS
    };
    CImReqHelpGetOnlinechilds()
    {
    }

    ~CImReqHelpGetOnlinechilds() { }
    CImReqHelpGetOnlinechilds(const string&  strUid, const uint8_t&  chStatus)
    {
        m_uid = strUid;
        m_status = chStatus;
    }
    CImReqHelpGetOnlinechilds&  operator=( const CImReqHelpGetOnlinechilds&  cImReqHelpGetOnlinechilds )
    {
        m_uid = cImReqHelpGetOnlinechilds.m_uid;
        m_status = cImReqHelpGetOnlinechilds.m_status;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetStatus () const { return m_status; }
    bool SetStatus ( const uint8_t&  chStatus )
    {
        m_status = chStatus;
        return true;
    }
private:
    string m_uid;
    uint8_t m_status;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpGetOnlinechilds::Size() const
{
    return 68;
}
class PROTOCOL_LIB CImRspHelpGetOnlinechilds : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_GET_ONLINECHILDS
    };
    CImRspHelpGetOnlinechilds()
    {
    }

    ~CImRspHelpGetOnlinechilds() { }
    CImRspHelpGetOnlinechilds(const uint8_t&  chRetcode, const VECTOR< SRecChildId >&  vecChildList)
    {
        m_retcode = chRetcode;
        m_childList = vecChildList;
    }
    CImRspHelpGetOnlinechilds&  operator=( const CImRspHelpGetOnlinechilds&  cImRspHelpGetOnlinechilds )
    {
        m_retcode = cImRspHelpGetOnlinechilds.m_retcode;
        m_childList = cImRspHelpGetOnlinechilds.m_childList;
        return *this;
    }

    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const VECTOR< SRecChildId >&  GetChildList () const { return m_childList; }
    bool SetChildList ( const VECTOR< SRecChildId >&  vecChildList )
    {
        m_childList = vecChildList;
        return true;
    }
private:
    uint8_t m_retcode;
    VECTOR< SRecChildId > m_childList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpGetOnlinechilds::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_childList.size(); i++)
    {
        nSize += m_childList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqHelpGetServices : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_GET_SERVICES
    };
    CImReqHelpGetServices()
    {
    }

    ~CImReqHelpGetServices() { }
    CImReqHelpGetServices(const string&  strUid, const string&  strFid)
    {
        m_uid = strUid;
        m_fid = strFid;
    }
    CImReqHelpGetServices&  operator=( const CImReqHelpGetServices&  cImReqHelpGetServices )
    {
        m_uid = cImReqHelpGetServices.m_uid;
        m_fid = cImReqHelpGetServices.m_fid;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetFid () const { return m_fid; }
    bool SetFid ( const string&  strFid )
    {
        if(strFid.size() > 64)
            return false;
        m_fid = strFid;
        return true;
    }
private:
    string m_uid;
    string m_fid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpGetServices::Size() const
{
    return 131;
}
class PROTOCOL_LIB CImRspHelpGetServices : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_GET_SERVICES
    };
    CImRspHelpGetServices()
    {
    }

    ~CImRspHelpGetServices() { }
    CImRspHelpGetServices(const uint8_t&  chRetcode, const VECTOR< uint32_t >&  vecServiceList)
    {
        m_retcode = chRetcode;
        m_serviceList = vecServiceList;
    }
    CImRspHelpGetServices&  operator=( const CImRspHelpGetServices&  cImRspHelpGetServices )
    {
        m_retcode = cImRspHelpGetServices.m_retcode;
        m_serviceList = cImRspHelpGetServices.m_serviceList;
        return *this;
    }

    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const VECTOR< uint32_t >&  GetServiceList () const { return m_serviceList; }
    bool SetServiceList ( const VECTOR< uint32_t >&  vecServiceList )
    {
        m_serviceList = vecServiceList;
        return true;
    }
private:
    uint8_t m_retcode;
    VECTOR< uint32_t > m_serviceList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpGetServices::Size() const
{
    uint32_t nSize = 9;
    nSize += m_serviceList.size() * 4;
    return nSize;
}

class PROTOCOL_LIB CImReqHelpGetBindTo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_GET_BIND_TO
    };
    CImReqHelpGetBindTo()
    {
    }

    ~CImReqHelpGetBindTo() { }
    CImReqHelpGetBindTo(const string&  strUid)
    {
        m_uid = strUid;
    }
    CImReqHelpGetBindTo&  operator=( const CImReqHelpGetBindTo&  cImReqHelpGetBindTo )
    {
        m_uid = cImReqHelpGetBindTo.m_uid;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
private:
    string m_uid;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpGetBindTo::Size() const
{
    return 66;
}
class PROTOCOL_LIB CImRspHelpGetBindTo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_GET_BIND_TO
    };
    CImRspHelpGetBindTo()
    {
    }

    ~CImRspHelpGetBindTo() { }
    CImRspHelpGetBindTo(const uint8_t&  chRetcode, const string&  strUidBinded)
    {
        m_retcode = chRetcode;
        m_uidBinded = strUidBinded;
    }
    CImRspHelpGetBindTo&  operator=( const CImRspHelpGetBindTo&  cImRspHelpGetBindTo )
    {
        m_retcode = cImRspHelpGetBindTo.m_retcode;
        m_uidBinded = cImRspHelpGetBindTo.m_uidBinded;
        return *this;
    }

    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const string&  GetUidBinded () const { return m_uidBinded; }
    bool SetUidBinded ( const string&  strUidBinded )
    {
        if(strUidBinded.size() > 64)
            return false;
        m_uidBinded = strUidBinded;
        return true;
    }
private:
    uint8_t m_retcode;
    string m_uidBinded;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpGetBindTo::Size() const
{
    return 68;
}
class PROTOCOL_LIB CImReqHelpChgServiceNum : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_CHG_SERVICE_NUM
    };
    CImReqHelpChgServiceNum()
    {
    }

    ~CImReqHelpChgServiceNum() { }
    CImReqHelpChgServiceNum(const string&  strUid, const string&  strChildId, const string&  strContactId, const uint8_t&  chType, const uint8_t&  chLocalNum, const uint32_t&  dwLocalTime)
    {
        m_uid = strUid;
        m_childId = strChildId;
        m_contactId = strContactId;
        m_type = chType;
        m_localNum = chLocalNum;
        m_localTime = dwLocalTime;
    }
    CImReqHelpChgServiceNum&  operator=( const CImReqHelpChgServiceNum&  cImReqHelpChgServiceNum )
    {
        m_uid = cImReqHelpChgServiceNum.m_uid;
        m_childId = cImReqHelpChgServiceNum.m_childId;
        m_contactId = cImReqHelpChgServiceNum.m_contactId;
        m_type = cImReqHelpChgServiceNum.m_type;
        m_localNum = cImReqHelpChgServiceNum.m_localNum;
        m_localTime = cImReqHelpChgServiceNum.m_localTime;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetChildId () const { return m_childId; }
    bool SetChildId ( const string&  strChildId )
    {
        if(strChildId.size() > 64)
            return false;
        m_childId = strChildId;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const uint8_t&  GetLocalNum () const { return m_localNum; }
    bool SetLocalNum ( const uint8_t&  chLocalNum )
    {
        m_localNum = chLocalNum;
        return true;
    }
    const uint32_t&  GetLocalTime () const { return m_localTime; }
    bool SetLocalTime ( const uint32_t&  dwLocalTime )
    {
        m_localTime = dwLocalTime;
        return true;
    }
private:
    string m_uid;
    string m_childId;
    string m_contactId;
    uint8_t m_type;
    uint8_t m_localNum;
    uint32_t m_localTime;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpChgServiceNum::Size() const
{
    return 205;
}
class PROTOCOL_LIB CImRspHelpChgServiceNum : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_CHG_SERVICE_NUM
    };
    CImRspHelpChgServiceNum()
    {
    }

    ~CImRspHelpChgServiceNum() { }
    CImRspHelpChgServiceNum(const uint8_t&  chStatus, const string&  strMessage, const string&  strUid, const string&  strChildId, const string&  strContactId, const uint8_t&  chServiceNum, const uint32_t&  dwServiceTime)
    {
        m_status = chStatus;
        m_message = strMessage;
        m_uid = strUid;
        m_childId = strChildId;
        m_contactId = strContactId;
        m_serviceNum = chServiceNum;
        m_serviceTime = dwServiceTime;
    }
    CImRspHelpChgServiceNum&  operator=( const CImRspHelpChgServiceNum&  cImRspHelpChgServiceNum )
    {
        m_status = cImRspHelpChgServiceNum.m_status;
        m_message = cImRspHelpChgServiceNum.m_message;
        m_uid = cImRspHelpChgServiceNum.m_uid;
        m_childId = cImRspHelpChgServiceNum.m_childId;
        m_contactId = cImRspHelpChgServiceNum.m_contactId;
        m_serviceNum = cImRspHelpChgServiceNum.m_serviceNum;
        m_serviceTime = cImRspHelpChgServiceNum.m_serviceTime;
        return *this;
    }

    const uint8_t&  GetStatus () const { return m_status; }
    bool SetStatus ( const uint8_t&  chStatus )
    {
        m_status = chStatus;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const string&  GetChildId () const { return m_childId; }
    bool SetChildId ( const string&  strChildId )
    {
        if(strChildId.size() > 64)
            return false;
        m_childId = strChildId;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const uint8_t&  GetServiceNum () const { return m_serviceNum; }
    bool SetServiceNum ( const uint8_t&  chServiceNum )
    {
        m_serviceNum = chServiceNum;
        return true;
    }
    const uint32_t&  GetServiceTime () const { return m_serviceTime; }
    bool SetServiceTime ( const uint32_t&  dwServiceTime )
    {
        m_serviceTime = dwServiceTime;
        return true;
    }
private:
    uint8_t m_status;
    string m_message;
    string m_uid;
    string m_childId;
    string m_contactId;
    uint8_t m_serviceNum;
    uint32_t m_serviceTime;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpChgServiceNum::Size() const
{
    uint32_t nSize = 210;
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImReqSendWatchInfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_SEND_WATCH_INFO
    };
    CImReqSendWatchInfo()
    {
    }

    ~CImReqSendWatchInfo() { }
    CImReqSendWatchInfo(const uint8_t&  chType, const string&  strMessage)
    {
        m_type = chType;
        m_message = strMessage;
    }
    CImReqSendWatchInfo&  operator=( const CImReqSendWatchInfo&  cImReqSendWatchInfo )
    {
        m_type = cImReqSendWatchInfo.m_type;
        m_message = cImReqSendWatchInfo.m_message;
        return *this;
    }

    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    uint8_t m_type;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqSendWatchInfo::Size() const
{
    uint32_t nSize = 8;
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfWatchInfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_WATCH_INFO
    };
    CImNtfWatchInfo()
    {
    }

    ~CImNtfWatchInfo() { }
    CImNtfWatchInfo(const string&  strUserId, const uint8_t&  chType, const string&  strMessage)
    {
        m_userId = strUserId;
        m_type = chType;
        m_message = strMessage;
    }
    CImNtfWatchInfo&  operator=( const CImNtfWatchInfo&  cImNtfWatchInfo )
    {
        m_userId = cImNtfWatchInfo.m_userId;
        m_type = cImNtfWatchInfo.m_type;
        m_message = cImNtfWatchInfo.m_message;
        return *this;
    }

    const string&  GetUserId () const { return m_userId; }
    bool SetUserId ( const string&  strUserId )
    {
        m_userId = strUserId;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    string m_userId;
    uint8_t m_type;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfWatchInfo::Size() const
{
    uint32_t nSize = 13;
    nSize += m_userId.length();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfRefreshContact : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_REFRESH_CONTACT
    };
    CImNtfRefreshContact() : m_groupId(0)
    {
    }

    ~CImNtfRefreshContact() { }
    CImNtfRefreshContact(const uint8_t&  chType, const string&  strContactId, const string&  strNickName, const int64_t&  llGroupId)
    {
        m_type = chType;
        m_contactId = strContactId;
        m_nickName = strNickName;
        m_groupId = llGroupId;
    }
    CImNtfRefreshContact&  operator=( const CImNtfRefreshContact&  cImNtfRefreshContact )
    {
        m_type = cImNtfRefreshContact.m_type;
        m_contactId = cImNtfRefreshContact.m_contactId;
        m_nickName = cImNtfRefreshContact.m_nickName;
        m_groupId = cImNtfRefreshContact.m_groupId;
        return *this;
    }

    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const string&  GetNickName () const { return m_nickName; }
    bool SetNickName ( const string&  strNickName )
    {
        if(strNickName.size() > 32)
            return false;
        m_nickName = strNickName;
        return true;
    }
    const int64_t&  GetGroupId () const { return m_groupId; }
    bool SetGroupId ( const int64_t&  llGroupId )
    {
        m_groupId = llGroupId;
        return true;
    }
private:
    uint8_t m_type;
    string m_contactId;
    string m_nickName;
    int64_t m_groupId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfRefreshContact::Size() const
{
    uint32_t nSize = 22;
    nSize += m_contactId.length();
    nSize += m_nickName.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfFeeds : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_FEEDS
    };
    CImNtfFeeds()
    {
    }

    ~CImNtfFeeds() { }
    CImNtfFeeds(const string&  strSite, const string&  strFromId, const uint32_t&  dwCreateTime, const string&  strContent)
    {
        m_site = strSite;
        m_fromId = strFromId;
        m_createTime = dwCreateTime;
        m_content = strContent;
    }
    CImNtfFeeds&  operator=( const CImNtfFeeds&  cImNtfFeeds )
    {
        m_site = cImNtfFeeds.m_site;
        m_fromId = cImNtfFeeds.m_fromId;
        m_createTime = cImNtfFeeds.m_createTime;
        m_content = cImNtfFeeds.m_content;
        return *this;
    }

    const string&  GetSite () const { return m_site; }
    bool SetSite ( const string&  strSite )
    {
        if(strSite.size() > 8)
            return false;
        m_site = strSite;
        return true;
    }
    const string&  GetFromId () const { return m_fromId; }
    bool SetFromId ( const string&  strFromId )
    {
        if(strFromId.size() > 64)
            return false;
        m_fromId = strFromId;
        return true;
    }
    const uint32_t&  GetCreateTime () const { return m_createTime; }
    bool SetCreateTime ( const uint32_t&  dwCreateTime )
    {
        m_createTime = dwCreateTime;
        return true;
    }
    const string&  GetContent () const { return m_content; }
    bool SetContent ( const string&  strContent )
    {
        m_content = strContent;
        return true;
    }
private:
    string m_site;
    string m_fromId;
    uint32_t m_createTime;
    string m_content;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfFeeds::Size() const
{
    uint32_t nSize = 25;
    nSize += m_fromId.length();
    nSize += m_content.length();
    return nSize;
}

class PROTOCOL_LIB CImNtfUserSnsinfo : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_USER_SNSINFO
    };
    CImNtfUserSnsinfo()
    {
    }

    ~CImNtfUserSnsinfo() { }
    CImNtfUserSnsinfo(const string&  strFromId, const uint8_t&  chType, const map< string,string >&  mapInfo)
    {
        m_fromId = strFromId;
        m_type = chType;
        m_info = mapInfo;
    }
    CImNtfUserSnsinfo&  operator=( const CImNtfUserSnsinfo&  cImNtfUserSnsinfo )
    {
        m_fromId = cImNtfUserSnsinfo.m_fromId;
        m_type = cImNtfUserSnsinfo.m_type;
        m_info = cImNtfUserSnsinfo.m_info;
        return *this;
    }

    const string&  GetFromId () const { return m_fromId; }
    bool SetFromId ( const string&  strFromId )
    {
        if(strFromId.size() > 64)
            return false;
        m_fromId = strFromId;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const map< string,string >&  GetInfo () const { return m_info; }
    bool SetInfo ( const map< string,string >&  mapInfo )
    {
        m_info = mapInfo;
        return true;
    }
private:
    string m_fromId;
    uint8_t m_type;
    map< string,string > m_info;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfUserSnsinfo::Size() const
{
    uint32_t nSize = 12;
    nSize += m_fromId.length();
    nSize += m_info.size() * 8;
    {
        map< string,string >::const_iterator itr;
        for(itr = m_info.begin(); itr != m_info.end(); ++itr)
        {
            nSize += itr->first.length();
            nSize += itr->second.length();
        }
    }
    return nSize;
}

class PROTOCOL_LIB CImReqGetSipSessionid : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_GET_SIP_SESSIONID
    };
    CImReqGetSipSessionid()
    {
    }

    ~CImReqGetSipSessionid() { }
    CImReqGetSipSessionid(const string&  strAppId, const string&  strType)
    {
        m_appId = strAppId;
        m_type = strType;
    }
    CImReqGetSipSessionid&  operator=( const CImReqGetSipSessionid&  cImReqGetSipSessionid )
    {
        m_appId = cImReqGetSipSessionid.m_appId;
        m_type = cImReqGetSipSessionid.m_type;
        return *this;
    }

    const string&  GetAppId () const { return m_appId; }
    bool SetAppId ( const string&  strAppId )
    {
        m_appId = strAppId;
        return true;
    }
    const string&  GetType () const { return m_type; }
    bool SetType ( const string&  strType )
    {
        m_type = strType;
        return true;
    }
private:
    string m_appId;
    string m_type;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqGetSipSessionid::Size() const
{
    uint32_t nSize = 11;
    nSize += m_appId.length();
    nSize += m_type.length();
    return nSize;
}

class PROTOCOL_LIB CImRspGetSipSessionid : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GET_SIP_SESSIONID
    };
    CImRspGetSipSessionid()
    {
    }

    ~CImRspGetSipSessionid() { }
    CImRspGetSipSessionid(const uint32_t&  dwRetcode, const string&  strAppId, const string&  strType, const string&  strUserId, const string&  strSessionId)
    {
        m_retcode = dwRetcode;
        m_appId = strAppId;
        m_type = strType;
        m_userId = strUserId;
        m_sessionId = strSessionId;
    }
    CImRspGetSipSessionid&  operator=( const CImRspGetSipSessionid&  cImRspGetSipSessionid )
    {
        m_retcode = cImRspGetSipSessionid.m_retcode;
        m_appId = cImRspGetSipSessionid.m_appId;
        m_type = cImRspGetSipSessionid.m_type;
        m_userId = cImRspGetSipSessionid.m_userId;
        m_sessionId = cImRspGetSipSessionid.m_sessionId;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const string&  GetAppId () const { return m_appId; }
    bool SetAppId ( const string&  strAppId )
    {
        m_appId = strAppId;
        return true;
    }
    const string&  GetType () const { return m_type; }
    bool SetType ( const string&  strType )
    {
        m_type = strType;
        return true;
    }
    const string&  GetUserId () const { return m_userId; }
    bool SetUserId ( const string&  strUserId )
    {
        if(strUserId.size() > 64)
            return false;
        m_userId = strUserId;
        return true;
    }
    const string&  GetSessionId () const { return m_sessionId; }
    bool SetSessionId ( const string&  strSessionId )
    {
        m_sessionId = strSessionId;
        return true;
    }
private:
    uint32_t m_retcode;
    string m_appId;
    string m_type;
    string m_userId;
    string m_sessionId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetSipSessionid::Size() const
{
    uint32_t nSize = 26;
    nSize += m_appId.length();
    nSize += m_type.length();
    nSize += m_userId.length();
    nSize += m_sessionId.length();
    return nSize;
}
class PROTOCOL_LIB CImReqHelpGetBuddyStatus : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_HELP_GET_BUDDY_STATUS
    };
    CImReqHelpGetBuddyStatus()
    {
    }

    ~CImReqHelpGetBuddyStatus() { }
    CImReqHelpGetBuddyStatus(const string&  strUid, const uint8_t&  chStatus)
    {
        m_uid = strUid;
        m_status = chStatus;
    }
    CImReqHelpGetBuddyStatus&  operator=( const CImReqHelpGetBuddyStatus&  cImReqHelpGetBuddyStatus )
    {
        m_uid = cImReqHelpGetBuddyStatus.m_uid;
        m_status = cImReqHelpGetBuddyStatus.m_status;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetStatus () const { return m_status; }
    bool SetStatus ( const uint8_t&  chStatus )
    {
        m_status = chStatus;
        return true;
    }
private:
    string m_uid;
    uint8_t m_status;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqHelpGetBuddyStatus::Size() const
{
    return 68;
}
struct SRecChildIdStatus
{
public:
    SRecChildIdStatus()
    {
    }

    ~SRecChildIdStatus() { }
    SRecChildIdStatus(const string&  strChildId, const uint8_t&  chOnlineStatus, const uint8_t&  chServiceStatus, const uint16_t&  wReserved1, const uint16_t&  wReserved2, const uint16_t&  wReserved3)
    {
        m_childId = strChildId;
        m_onlineStatus = chOnlineStatus;
        m_serviceStatus = chServiceStatus;
        m_reserved1 = wReserved1;
        m_reserved2 = wReserved2;
        m_reserved3 = wReserved3;
    }
    SRecChildIdStatus&  operator=( const SRecChildIdStatus&  sRecChildIdStatus )
    {
        m_childId = sRecChildIdStatus.m_childId;
        m_onlineStatus = sRecChildIdStatus.m_onlineStatus;
        m_serviceStatus = sRecChildIdStatus.m_serviceStatus;
        m_reserved1 = sRecChildIdStatus.m_reserved1;
        m_reserved2 = sRecChildIdStatus.m_reserved2;
        m_reserved3 = sRecChildIdStatus.m_reserved3;
        return *this;
    }

    string m_childId;
    uint8_t m_onlineStatus;
    uint8_t m_serviceStatus;
    uint16_t m_reserved1;
    uint16_t m_reserved2;
    uint16_t m_reserved3;

public:
    uint32_t Size() const;
};

inline uint32_t SRecChildIdStatus::Size() const
{
    return 79;
}
CPackData& operator<< ( CPackData& cPackData, const SRecChildIdStatus&  sRecChildIdStatus );
CPackData& operator>> ( CPackData& cPackData, SRecChildIdStatus&  sRecChildIdStatus );

class PROTOCOL_LIB CImRspHelpGetBuddyStatus : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_HELP_GET_BUDDY_STATUS
    };
    CImRspHelpGetBuddyStatus()
    {
    }

    ~CImRspHelpGetBuddyStatus() { }
    CImRspHelpGetBuddyStatus(const uint8_t&  chRetcode, const VECTOR< SRecChildIdStatus >&  vecChildList)
    {
        m_retcode = chRetcode;
        m_childList = vecChildList;
    }
    CImRspHelpGetBuddyStatus&  operator=( const CImRspHelpGetBuddyStatus&  cImRspHelpGetBuddyStatus )
    {
        m_retcode = cImRspHelpGetBuddyStatus.m_retcode;
        m_childList = cImRspHelpGetBuddyStatus.m_childList;
        return *this;
    }

    const uint8_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint8_t&  chRetcode )
    {
        m_retcode = chRetcode;
        return true;
    }
    const VECTOR< SRecChildIdStatus >&  GetChildList () const { return m_childList; }
    bool SetChildList ( const VECTOR< SRecChildIdStatus >&  vecChildList )
    {
        m_childList = vecChildList;
        return true;
    }
private:
    uint8_t m_retcode;
    VECTOR< SRecChildIdStatus > m_childList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspHelpGetBuddyStatus::Size() const
{
    uint32_t nSize = 7;
    for(uint32_t i = 0; i < m_childList.size(); i++)
    {
        nSize += m_childList[i].Size();
    }
    return nSize;
}

struct SRecentNode
{
public:
    SRecentNode()
    {
    }

    ~SRecentNode() { }
    SRecentNode(const string&  strContactId, const uint32_t&  dwSendTime, const uint32_t&  dwRecvTime, const uint32_t&  dwRecvFlag, const uint32_t&  dwSendFlag)
    {
        m_contactId = strContactId;
        m_sendTime = dwSendTime;
        m_recvTime = dwRecvTime;
        m_recvFlag = dwRecvFlag;
        m_sendFlag = dwSendFlag;
    }
    SRecentNode&  operator=( const SRecentNode&  sRecentNode )
    {
        m_contactId = sRecentNode.m_contactId;
        m_sendTime = sRecentNode.m_sendTime;
        m_recvTime = sRecentNode.m_recvTime;
        m_recvFlag = sRecentNode.m_recvFlag;
        m_sendFlag = sRecentNode.m_sendFlag;
        return *this;
    }

    string m_contactId;
    uint32_t m_sendTime;
    uint32_t m_recvTime;
    uint32_t m_recvFlag;
    uint32_t m_sendFlag;

public:
    uint32_t Size() const;
};

inline uint32_t SRecentNode::Size() const
{
    uint32_t nSize = 26;
    nSize += m_contactId.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SRecentNode&  sRecentNode );
CPackData& operator>> ( CPackData& cPackData, SRecentNode&  sRecentNode );

class PROTOCOL_LIB CImNtfRecent : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_NTF_RECENT
    };
    CImNtfRecent()
    {
    }

    ~CImNtfRecent() { }
    CImNtfRecent(const uint32_t&  dwTimeStamp, const uint32_t&  dwOpType, const VECTOR< SRecentNode >&  vecRecentList)
    {
        m_timeStamp = dwTimeStamp;
        m_opType = dwOpType;
        m_recentList = vecRecentList;
    }
    CImNtfRecent&  operator=( const CImNtfRecent&  cImNtfRecent )
    {
        m_timeStamp = cImNtfRecent.m_timeStamp;
        m_opType = cImNtfRecent.m_opType;
        m_recentList = cImNtfRecent.m_recentList;
        return *this;
    }

    const uint32_t&  GetTimeStamp () const { return m_timeStamp; }
    bool SetTimeStamp ( const uint32_t&  dwTimeStamp )
    {
        m_timeStamp = dwTimeStamp;
        return true;
    }
    const uint32_t&  GetOpType () const { return m_opType; }
    bool SetOpType ( const uint32_t&  dwOpType )
    {
        m_opType = dwOpType;
        return true;
    }
    const VECTOR< SRecentNode >&  GetRecentList () const { return m_recentList; }
    bool SetRecentList ( const VECTOR< SRecentNode >&  vecRecentList )
    {
        m_recentList = vecRecentList;
        return true;
    }
private:
    uint32_t m_timeStamp;
    uint32_t m_opType;
    VECTOR< SRecentNode > m_recentList;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImNtfRecent::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_recentList.size(); i++)
    {
        nSize += m_recentList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqAddcontactNew : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDCONTACT_NEW
    };
    CImReqAddcontactNew()
    {
    }

    ~CImReqAddcontactNew() { }
    CImReqAddcontactNew(const SContactInfo&  sContact, const uint8_t&  chType, const string&  strMessage)
    {
        m_contact = sContact;
        m_type = chType;
        m_message = strMessage;
    }
    CImReqAddcontactNew&  operator=( const CImReqAddcontactNew&  cImReqAddcontactNew )
    {
        m_contact = cImReqAddcontactNew.m_contact;
        m_type = cImReqAddcontactNew.m_type;
        m_message = cImReqAddcontactNew.m_message;
        return *this;
    }

    const SContactInfo&  GetContact () const { return m_contact; }
    bool SetContact ( const SContactInfo&  sContact )
    {
        m_contact = sContact;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    SContactInfo m_contact;
    uint8_t m_type;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddcontactNew::Size() const
{
    uint32_t nSize = 9;
    nSize += m_contact.Size();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImRspAddcontactNew : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDCONTACT_NEW
    };
    CImRspAddcontactNew()
    {
    }

    ~CImRspAddcontactNew() { }
    CImRspAddcontactNew(const uint32_t&  dwRetcode, const uint8_t&  chType, const SContactInfo&  sContact, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_type = chType;
        m_contact = sContact;
        m_timestamp = dwTimestamp;
    }
    CImRspAddcontactNew&  operator=( const CImRspAddcontactNew&  cImRspAddcontactNew )
    {
        m_retcode = cImRspAddcontactNew.m_retcode;
        m_type = cImRspAddcontactNew.m_type;
        m_contact = cImRspAddcontactNew.m_contact;
        m_timestamp = cImRspAddcontactNew.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const SContactInfo&  GetContact () const { return m_contact; }
    bool SetContact ( const SContactInfo&  sContact )
    {
        m_contact = sContact;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    uint8_t m_type;
    SContactInfo m_contact;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddcontactNew::Size() const
{
    uint32_t nSize = 14;
    nSize += m_contact.Size();
    return nSize;
}

class PROTOCOL_LIB CImReqAddcntackNew : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_ADDCNTACK_NEW
    };
    CImReqAddcntackNew()
    {
    }

    ~CImReqAddcntackNew() { }
    CImReqAddcntackNew(const uint8_t&  chOpcode, const string&  strContactId, const int64_t&  llGroupId, const string&  strNickName, const string&  strMessage)
    {
        m_opcode = chOpcode;
        m_contactId = strContactId;
        m_groupId = llGroupId;
        m_nickName = strNickName;
        m_message = strMessage;
    }
    CImReqAddcntackNew&  operator=( const CImReqAddcntackNew&  cImReqAddcntackNew )
    {
        m_opcode = cImReqAddcntackNew.m_opcode;
        m_contactId = cImReqAddcntackNew.m_contactId;
        m_groupId = cImReqAddcntackNew.m_groupId;
        m_nickName = cImReqAddcntackNew.m_nickName;
        m_message = cImReqAddcntackNew.m_message;
        return *this;
    }

    const uint8_t&  GetOpcode () const { return m_opcode; }
    bool SetOpcode ( const uint8_t&  chOpcode )
    {
        m_opcode = chOpcode;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
    const int64_t&  GetGroupId () const { return m_groupId; }
    bool SetGroupId ( const int64_t&  llGroupId )
    {
        m_groupId = llGroupId;
        return true;
    }
    const string&  GetNickName () const { return m_nickName; }
    bool SetNickName ( const string&  strNickName )
    {
        m_nickName = strNickName;
        return true;
    }
    const string&  GetMessage () const { return m_message; }
    bool SetMessage ( const string&  strMessage )
    {
        m_message = strMessage;
        return true;
    }
private:
    uint8_t m_opcode;
    string m_contactId;
    int64_t m_groupId;
    string m_nickName;
    string m_message;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqAddcntackNew::Size() const
{
    uint32_t nSize = 27;
    nSize += m_contactId.length();
    nSize += m_nickName.length();
    nSize += m_message.length();
    return nSize;
}

class PROTOCOL_LIB CImRspAddcntackNew : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_ADDCNTACK_NEW
    };
    CImRspAddcntackNew()
    {
    }

    ~CImRspAddcntackNew() { }
    CImRspAddcntackNew(const uint32_t&  dwRetcode, const uint8_t&  chOpcode, const int64_t&  llGroupId, const uint32_t&  dwTimestamp, const string&  strContactId)
    {
        m_retcode = dwRetcode;
        m_opcode = chOpcode;
        m_groupId = llGroupId;
        m_timestamp = dwTimestamp;
        m_contactId = strContactId;
    }
    CImRspAddcntackNew&  operator=( const CImRspAddcntackNew&  cImRspAddcntackNew )
    {
        m_retcode = cImRspAddcntackNew.m_retcode;
        m_opcode = cImRspAddcntackNew.m_opcode;
        m_groupId = cImRspAddcntackNew.m_groupId;
        m_timestamp = cImRspAddcntackNew.m_timestamp;
        m_contactId = cImRspAddcntackNew.m_contactId;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint8_t&  GetOpcode () const { return m_opcode; }
    bool SetOpcode ( const uint8_t&  chOpcode )
    {
        m_opcode = chOpcode;
        return true;
    }
    const int64_t&  GetGroupId () const { return m_groupId; }
    bool SetGroupId ( const int64_t&  llGroupId )
    {
        m_groupId = llGroupId;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
    const string&  GetContactId () const { return m_contactId; }
    bool SetContactId ( const string&  strContactId )
    {
        if(strContactId.size() > 64)
            return false;
        m_contactId = strContactId;
        return true;
    }
private:
    uint32_t m_retcode;
    uint8_t m_opcode;
    int64_t m_groupId;
    uint32_t m_timestamp;
    string m_contactId;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspAddcntackNew::Size() const
{
    uint32_t nSize = 27;
    nSize += m_contactId.length();
    return nSize;
}



//todo
class PROTOCOL_LIB CImReqGetDegree : public CPackData
{
public:
	enum
	{
		CMD_ID = IM_REQ_GET_DEGREE
	};
	CImReqGetDegree()
	{
	}

	~CImReqGetDegree() { }
	CImReqGetDegree(const string&  strUid)
	{
		m_uid = strUid;
	}
	CImReqGetDegree&  operator=( const CImReqGetDegree&  cImReqGetDegree )
	{
		m_uid = cImReqGetDegree.m_uid;
		return *this;
	}

	const string&  GetUid () const { return m_uid; }
	bool SetUid ( const string&  strUid )
	{
		if(strUid.size() > 64)
			return false;
		m_uid = strUid;
		return true;
	}
private:
	string m_uid;

public:
	CScHead m_scHead;
	void PackHead(string& strData);
	void PackBody(string& strData);
	void PackData(string& strData, const string& strKey = "");
	PACKRETCODE UnpackBody(string& strData);
	PACKRETCODE UnpackData(string& strData, const string& strKey = "");
	uint32_t Size() const;
};

inline uint32_t CImReqGetDegree::Size() const
{
	return 66;
}
class PROTOCOL_LIB CImRspGetDegree : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_GET_DEGREE
    };
    CImRspGetDegree()
    {
    }

    ~CImRspGetDegree() { }
    CImRspGetDegree(const string&  strUid, const uint32_t&  dwRetcode, const uint32_t&  dwUserLevel, const uint32_t&  dwTotalDegree, const uint32_t&  dwNeedDegree, const VECTOR< uint8_t >&  vecShowCount)
    {
        m_uid = strUid;
        m_retcode = dwRetcode;
        m_userLevel = dwUserLevel;
        m_totalDegree = dwTotalDegree;
        m_needDegree = dwNeedDegree;
        m_showCount = vecShowCount;
    }
    CImRspGetDegree&  operator=( const CImRspGetDegree&  cImRspGetDegree )
    {
        m_uid = cImRspGetDegree.m_uid;
        m_retcode = cImRspGetDegree.m_retcode;
        m_userLevel = cImRspGetDegree.m_userLevel;
        m_totalDegree = cImRspGetDegree.m_totalDegree;
        m_needDegree = cImRspGetDegree.m_needDegree;
        m_showCount = cImRspGetDegree.m_showCount;
        return *this;
    }

    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        m_uid = strUid;
        return true;
    }
    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const uint32_t&  GetUserLevel () const { return m_userLevel; }
    bool SetUserLevel ( const uint32_t&  dwUserLevel )
    {
        m_userLevel = dwUserLevel;
        return true;
    }
    const uint32_t&  GetTotalDegree () const { return m_totalDegree; }
    bool SetTotalDegree ( const uint32_t&  dwTotalDegree )
    {
        m_totalDegree = dwTotalDegree;
        return true;
    }
    const uint32_t&  GetNeedDegree () const { return m_needDegree; }
    bool SetNeedDegree ( const uint32_t&  dwNeedDegree )
    {
        m_needDegree = dwNeedDegree;
        return true;
    }
    const VECTOR< uint8_t >&  GetShowCount () const { return m_showCount; }
    bool SetShowCount ( const VECTOR< uint8_t >&  vecShowCount )
    {
        m_showCount = vecShowCount;
        return true;
    }
private:
    string m_uid;
    uint32_t m_retcode;
    uint32_t m_userLevel;
    uint32_t m_totalDegree;
    uint32_t m_needDegree;
    VECTOR< uint8_t > m_showCount;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspGetDegree::Size() const
{
    uint32_t nSize = 32;
    nSize += m_uid.length();
    nSize += m_showCount.size() * 1;
    return nSize;
}

//updateudbprofile
class PROTOCOL_LIB CImReqUpdateUdbprofile : public CPackData
{
public:
	enum
	{
		CMD_ID = IM_REQ_UPDATE_UDBPROFILE
	};
	CImReqUpdateUdbprofile()
	{
	}

	~CImReqUpdateUdbprofile() { }
	CImReqUpdateUdbprofile(const map< string,string >&  mapProfilelist)
	{
		m_profilelist = mapProfilelist;
	}
	CImReqUpdateUdbprofile&  operator=( const CImReqUpdateUdbprofile&  cImReqUpdateUdbprofile )
	{
		m_profilelist = cImReqUpdateUdbprofile.m_profilelist;
		return *this;
	}

	const map< string,string >&  GetProfilelist () const { return m_profilelist; }
	bool SetProfilelist ( const map< string,string >&  mapProfilelist )
	{
		m_profilelist = mapProfilelist;
		return true;
	}
private:
	map< string,string > m_profilelist;

public:
	CScHead m_scHead;
	void PackHead(string& strData);
	void PackBody(string& strData);
	void PackData(string& strData, const string& strKey = "");
	PACKRETCODE UnpackBody(string& strData);
	PACKRETCODE UnpackData(string& strData, const string& strKey = "");
	uint32_t Size() const;
};

inline uint32_t CImReqUpdateUdbprofile::Size() const
{
	uint32_t nSize = 5;
	nSize += m_profilelist.size() * 8;
	{
		map< string,string >::const_iterator itr;
		for(itr = m_profilelist.begin(); itr != m_profilelist.end(); ++itr)
		{
			nSize += itr->first.length();
			nSize += itr->second.length();
		}
	}
	return nSize;
}

class PROTOCOL_LIB CImRspUpdateUdbprofile : public CPackData
{
public:
	enum
	{
		CMD_ID = IM_RSP_UPDATE_UDBPROFILE
	};
	CImRspUpdateUdbprofile()
	{
	}

	~CImRspUpdateUdbprofile() { }
	CImRspUpdateUdbprofile(const uint32_t&  dwRetcode, const string&  strUid)
	{
		m_retcode = dwRetcode;
		m_uid = strUid;
	}
	CImRspUpdateUdbprofile&  operator=( const CImRspUpdateUdbprofile&  cImRspUpdateUdbprofile )
	{
		m_retcode = cImRspUpdateUdbprofile.m_retcode;
		m_uid = cImRspUpdateUdbprofile.m_uid;
		return *this;
	}

	const uint32_t&  GetRetcode () const { return m_retcode; }
	bool SetRetcode ( const uint32_t&  dwRetcode )
	{
		m_retcode = dwRetcode;
		return true;
	}
	const string&  GetUid () const { return m_uid; }
	bool SetUid ( const string&  strUid )
	{
		m_uid = strUid;
		return true;
	}
private:
	uint32_t m_retcode;
	string m_uid;

public:
	CScHead m_scHead;
	void PackHead(string& strData);
	void PackBody(string& strData);
	void PackData(string& strData, const string& strKey = "");
	PACKRETCODE UnpackBody(string& strData);
	PACKRETCODE UnpackData(string& strData, const string& strKey = "");
	uint32_t Size() const;
};

inline uint32_t CImRspUpdateUdbprofile::Size() const
{
	uint32_t nSize = 11;
	nSize += m_uid.length();
	return nSize;
}


class PROTOCOL_LIB CImReqSearchuser : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_SEARCHUSER
    };
    CImReqSearchuser()
    {
    }

    ~CImReqSearchuser() { }
    CImReqSearchuser(const uint32_t&  dwTimestamp, const uint8_t&  chType, const string&  strUid, const uint8_t&  chSyncacc)
    {
        m_timestamp = dwTimestamp;
        m_type = chType;
        m_uid = strUid;
        m_syncacc = chSyncacc;
    }
    CImReqSearchuser&  operator=( const CImReqSearchuser&  cImReqSearchuser )
    {
        m_timestamp = cImReqSearchuser.m_timestamp;
        m_type = cImReqSearchuser.m_type;
        m_uid = cImReqSearchuser.m_uid;
        m_syncacc = cImReqSearchuser.m_syncacc;
        return *this;
    }

    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
    const uint8_t&  GetType () const { return m_type; }
    bool SetType ( const uint8_t&  chType )
    {
        m_type = chType;
        return true;
    }
    const string&  GetUid () const { return m_uid; }
    bool SetUid ( const string&  strUid )
    {
        if(strUid.size() > 64)
            return false;
        m_uid = strUid;
        return true;
    }
    const uint8_t&  GetSyncacc () const { return m_syncacc; }
    bool SetSyncacc ( const uint8_t&  chSyncacc )
    {
        m_syncacc = chSyncacc;
        return true;
    }
private:
    uint32_t m_timestamp;
    uint8_t m_type;
    string m_uid;
    uint8_t m_syncacc;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqSearchuser::Size() const
{
    uint32_t nSize = 15;
    nSize += m_uid.length();
    return nSize;
}

struct SSearchUserinfo
{
public:
    SSearchUserinfo()
    {
    }

    ~SSearchUserinfo() { }
    SSearchUserinfo(const string&  strContactId, const string&  strNickName, const uint8_t&  chAge, const uint8_t&  chGender, const string&  strCity, const uint8_t&  chBasicStatus)
    {
        m_contactId = strContactId;
        m_nickName = strNickName;
        m_age = chAge;
        m_gender = chGender;
        m_city = strCity;
        m_basicStatus = chBasicStatus;
    }
    SSearchUserinfo&  operator=( const SSearchUserinfo&  sSearchUserinfo )
    {
        m_contactId = sSearchUserinfo.m_contactId;
        m_nickName = sSearchUserinfo.m_nickName;
        m_age = sSearchUserinfo.m_age;
        m_gender = sSearchUserinfo.m_gender;
        m_city = sSearchUserinfo.m_city;
        m_basicStatus = sSearchUserinfo.m_basicStatus;
        return *this;
    }

    string m_contactId;
    string m_nickName;
    uint8_t m_age;
    uint8_t m_gender;
    string m_city;
    uint8_t m_basicStatus;

public:
    uint32_t Size() const;
};

inline uint32_t SSearchUserinfo::Size() const
{
    uint32_t nSize = 22;
    nSize += m_contactId.length();
    nSize += m_nickName.length();
    nSize += m_city.length();
    return nSize;
}

CPackData& operator<< ( CPackData& cPackData, const SSearchUserinfo&  sSearchUserinfo );
CPackData& operator>> ( CPackData& cPackData, SSearchUserinfo&  sSearchUserinfo );

class PROTOCOL_LIB CImRspSearchuser : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_RSP_SEARCHUSER
    };
    CImRspSearchuser()
    {
    }

    ~CImRspSearchuser() { }
    CImRspSearchuser(const uint32_t&  dwRetcode, const VECTOR< SSearchUserinfo >&  vecUserList, const uint32_t&  dwTimestamp)
    {
        m_retcode = dwRetcode;
        m_userList = vecUserList;
        m_timestamp = dwTimestamp;
    }
    CImRspSearchuser&  operator=( const CImRspSearchuser&  cImRspSearchuser )
    {
        m_retcode = cImRspSearchuser.m_retcode;
        m_userList = cImRspSearchuser.m_userList;
        m_timestamp = cImRspSearchuser.m_timestamp;
        return *this;
    }

    const uint32_t&  GetRetcode () const { return m_retcode; }
    bool SetRetcode ( const uint32_t&  dwRetcode )
    {
        m_retcode = dwRetcode;
        return true;
    }
    const VECTOR< SSearchUserinfo >&  GetUserList () const { return m_userList; }
    bool SetUserList ( const VECTOR< SSearchUserinfo >&  vecUserList )
    {
        m_userList = vecUserList;
        return true;
    }
    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
private:
    uint32_t m_retcode;
    VECTOR< SSearchUserinfo > m_userList;
    uint32_t m_timestamp;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImRspSearchuser::Size() const
{
    uint32_t nSize = 17;
    for(uint32_t i = 0; i < m_userList.size(); i++)
    {
        nSize += m_userList[i].Size();
    }
    return nSize;
}

class PROTOCOL_LIB CImReqSearchuserex : public CPackData
{
public:
    enum
    {
        CMD_ID = IM_REQ_SEARCHUSEREX
    };
    CImReqSearchuserex()
    {
    }

    ~CImReqSearchuserex() { }
    CImReqSearchuserex(const uint32_t&  dwTimestamp, const string&  strSite, const string&  strCountry, const string&  strProvince, const string&  strCity, const uint8_t&  chGender, const uint32_t&  dwAge, const string&  strJob)
    {
        m_timestamp = dwTimestamp;
        m_site = strSite;
        m_country = strCountry;
        m_province = strProvince;
        m_city = strCity;
        m_gender = chGender;
        m_age = dwAge;
        m_job = strJob;
    }
    CImReqSearchuserex&  operator=( const CImReqSearchuserex&  cImReqSearchuserex )
    {
        m_timestamp = cImReqSearchuserex.m_timestamp;
        m_site = cImReqSearchuserex.m_site;
        m_country = cImReqSearchuserex.m_country;
        m_province = cImReqSearchuserex.m_province;
        m_city = cImReqSearchuserex.m_city;
        m_gender = cImReqSearchuserex.m_gender;
        m_age = cImReqSearchuserex.m_age;
        m_job = cImReqSearchuserex.m_job;
        return *this;
    }

    const uint32_t&  GetTimestamp () const { return m_timestamp; }
    bool SetTimestamp ( const uint32_t&  dwTimestamp )
    {
        m_timestamp = dwTimestamp;
        return true;
    }
    const string&  GetSite () const { return m_site; }
    bool SetSite ( const string&  strSite )
    {
        if(strSite.size() > 64)
            return false;
        m_site = strSite;
        return true;
    }
    const string&  GetCountry () const { return m_country; }
    bool SetCountry ( const string&  strCountry )
    {
        m_country = strCountry;
        return true;
    }
    const string&  GetProvince () const { return m_province; }
    bool SetProvince ( const string&  strProvince )
    {
        m_province = strProvince;
        return true;
    }
    const string&  GetCity () const { return m_city; }
    bool SetCity ( const string&  strCity )
    {
        m_city = strCity;
        return true;
    }
    const uint8_t&  GetGender () const { return m_gender; }
    bool SetGender ( const uint8_t&  chGender )
    {
        m_gender = chGender;
        return true;
    }
    const uint32_t&  GetAge () const { return m_age; }
    bool SetAge ( const uint32_t&  dwAge )
    {
        m_age = dwAge;
        return true;
    }
    const string&  GetJob () const { return m_job; }
    bool SetJob ( const string&  strJob )
    {
        m_job = strJob;
        return true;
    }
private:
    uint32_t m_timestamp;
    string m_site;
    string m_country;
    string m_province;
    string m_city;
    uint8_t m_gender;
    uint32_t m_age;
    string m_job;

public:
    CScHead m_scHead;
    void PackHead(string& strData);
    void PackBody(string& strData);
    void PackData(string& strData, const string& strKey = "");
    PACKRETCODE UnpackBody(string& strData);
    PACKRETCODE UnpackData(string& strData, const string& strKey = "");
    uint32_t Size() const;
};

inline uint32_t CImReqSearchuserex::Size() const
{
    uint32_t nSize = 38;
    nSize += m_site.length();
    nSize += m_country.length();
    nSize += m_province.length();
    nSize += m_city.length();
    nSize += m_job.length();
    return nSize;
}

#endif



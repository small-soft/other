
#include "AccountUtils.h"


static const int ACCOUNT_PREFIX_LEN = 8;

bool CAccountUtils::Init(const std::string& strUid)
{
	m_strUid = strUid;
	
	if (strUid.length() <= ACCOUNT_PREFIX_LEN)
		return false;
	
	const std::string& strPrefix = strUid.substr(0, ACCOUNT_PREFIX_LEN);
	m_strSiteName = GetSiteNameImpl(strPrefix);
	
	m_strShortUid = strUid.substr(ACCOUNT_PREFIX_LEN);
	
	
	return true;
}

std::string CAccountUtils::GetSiteName() const
{
	return m_strSiteName;
}

std::string CAccountUtils::GetShortUid() const
{
	return m_strShortUid;
}

std::string CAccountUtils::GetLongUid() const
{
	return m_strUid;
}

std::string CAccountUtils::GetSiteNameImpl(const std::string& strSitePrefix)
{
	if (strSitePrefix == "cntaobao")
		return "淘宝网";
	else if (strSitePrefix == "cnalichn")
		return "阿里巴巴中文站";
	else if (strSitePrefix == "cnaliyun")
		return "阿里云";
	else
		return "";
}

//void CAccountUtils::test()
//{
//	bool bInit = Init("cntaobaodikatour");
//	
//	MU_ASSERT(bInit);
//	
//	MU_ASSERT(GetSiteName() == "淘宝网");
//	
//	MU_ASSERT(GetShortUid() == "dikatour");
//	
//	MU_ASSERT(GetLongUid() == "cntaobaodikatour");
//	
//	MU_OK();
//}

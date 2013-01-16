#ifndef XUMINGGANG_IM_ACCOUNT_UTILS_H
#define XUMINGGANG_IM_ACCOUNT_UTILS_H

#include <string>

class CAccountUtils
{
public:
	bool Init(const std::string& strUid);
	std::string GetSiteName() const;
	std::string GetShortUid() const;
	std::string GetLongUid() const;
	
	
#define MY_UNIT_TEST
#ifdef MY_UNIT_TEST
	void test();
#endif
	
private:
	std::string GetSiteNameImpl(const std::string& strSitePrefix);
	
private:
	std::string										m_strUid;
	std::string										m_strSiteName;
	std::string										m_strShortUid;
};

#endif //XUMINGGANG_IM_ACCOUNT_UTILS_H





#include "LoginDataStructDefs.h"
#include "ContactInfoKeywordDefs.h"

#ifdef find(TYPE,STRUCT,OBJ)
#undef find(TYPE,STRUCT,OBJ)
#endif

#ifdef empty(TYPE,STRUCT)
#undef empty(TYPE,STRUCT)
#endif


#ifdef insert(TYPE,STRUCT,OBJ,FLAG)
#undef insert(TYPE,STRUCT,OBJ,FLAG)
#endif


const CContactPersonalDetailInfo::KeyValueMap_t& CContactPersonalDetailInfo::GetKeyValueMap() const
{
	return m_keyValueMap;
}


bool CContactPersonalDetailInfo::SetInfo(EnInfoType enInfoType, const std::string& strNewValue)
{
	std::string strKey = GetInfoTypeKey(enInfoType);
	if (strKey.empty())
		return false;
	
	SetKeyValue(strKey, strNewValue);
	
	return true;
}


void CContactPersonalDetailInfo::SetKeyValue(const std::string& strKey, const std::string& strValue)
{
	m_keyValueMap[strKey] = strValue;
}


bool CContactPersonalDetailInfo::SetAreaInfo(const std::string& strCountryValue, const std::string& strProvinceValue, const std::string& strCityValue)
{
	return (SetInfo(COUNTRY_INFO, strCountryValue) && SetInfo(PROVINCE_INFO, strProvinceValue) && SetInfo(CITY_INFO, strCityValue));
}

CContactPersonalDetailInfo::CContactPersonalDetailInfo()
{
	InitInfoTypeKeyMap();
}


std::string CContactPersonalDetailInfo::GetKeyValue(const std::string& strKey) const
{
	std::string strRet = "";
	KeyValueMap_t::const_iterator p2 = m_keyValueMap.find(strKey);
	if (p2 == m_keyValueMap.end())
		return strRet;
	
	const std::string& strValue = p2->second;
	return strValue;
}

std::string CContactPersonalDetailInfo::GetInfoTypeKey(EnInfoType enInfoType) const
{
	std::string strRet = "";
	InfoTypeKeyMap_t::const_iterator p = m_infoTypeKeyMap.find(enInfoType);
	if (p == m_infoTypeKeyMap.end())
		return strRet;
	
	const std::string& strKey = p->second;
	
	return strKey;
}

std::string CContactPersonalDetailInfo::GetInfo(EnInfoType enInfoType) const
{
	std::string strKey = GetInfoTypeKey(enInfoType);
	if (strKey.empty())
		return strKey;
	
	return GetKeyValue(strKey);
}


const CContactPersonalDetailInfo::InfoTypeKeyMap_t& CContactPersonalDetailInfo::GetInfoTypeKeyMap() const
{
	return m_infoTypeKeyMap;
}

bool CContactPersonalDetailInfo::InitInfoTypeKeyMap()
{
#define INSERT_ITEM(key, value) \
m_infoTypeKeyMap.insert(InfoTypeKeyMap_t::value_type((key), (value)))
	
	INSERT_ITEM(UID_INFO,	UID_KEYWROD_ID);							//用户id
	INSERT_ITEM(DISPNAME_INFO, NAME_KEYWORD_ID);						//姓名
	INSERT_ITEM(GENDER_INFO, GENDER_KEYWORD_ID);						//性别
	INSERT_ITEM(BIRTHDAY_INFO,	BIRTH_KEYWORD_ID);						//生日
	INSERT_ITEM(CONSTELLATION_INFO,	CONSTELLATION_KEYWORD_ID);			//星座
	INSERT_ITEM(SHENGXIAO_INFO,	SHENGXIAO_KEYWORD_ID);					//生肖
	INSERT_ITEM(COUNTRY_INFO, COUNTRY_KEYWORD_ID);						//国家
	INSERT_ITEM(PROVINCE_INFO, PROVINCE_KEYWORD_ID);					//省份
	INSERT_ITEM(CITY_INFO, CITY_KEYWORD_ID);							//城市
	INSERT_ITEM(MOBILEPHONE_INFO, MOBILE_KEYWORD_ID);					//手机
	INSERT_ITEM(TELEPHONE_INFO,	PHONE_KEYWORD_ID);						//电话
	INSERT_ITEM(EMAIL_INFO,	EMAIL_KEYWORD_ID);							//邮箱
	INSERT_ITEM(CAREER_INFO, CAREER_KEYWORD_ID);						//职业
	INSERT_ITEM(GRADSCHOOL_INFO, SCHOOL_KEYWORD_ID);					//毕业院校
	INSERT_ITEM(PERSONALWEBSITE_INFO, PERSONALWEBSITE_KEYWORD_ID);		//个人主页
	
	return true;
}


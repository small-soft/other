#include <string>

#include "ContactDetailInfo.h"
#include "ContactInfoKeywordDefs.h"

//#include "../Protocol/imsc_pack.h"
//#include "../Utils/md5hash.h"
//#include "../Utils/rsa/rsa.h"
//#include "../Utils/DreamUnitTest.h"
//#include "../Protocol/des.h"
//#include "../Utils/RSAWrapper.h"

#ifdef insert(KeyValueMap_t::value_type((key), (value)))
#undef insert(KeyValueMap_t::value_type((key), (value)))
#endif

void CContactDetailInfoUtils::GetAreaName(const KeyValueMap_t& profileMap, std::string& strCountryName, std::string& strProvinceName, std::string& strCityName)
{
	//地域字段由于存储方式的特别，所以这里特殊处理一下
	std::string strCountryCode = GetKeyValue(profileMap, COUNTRY_KEYWORD_ID);
	std::string strProvinceCode = GetKeyValue(profileMap, PROVINCE_KEYWORD_ID);
	std::string strCityCode = GetKeyValue(profileMap, CITY_KEYWORD_ID);
	
	//country的parent code是0
	strCountryName = m_contactInfoCollectionUtils.GetNameByCodeInAreaMap("0", strCountryCode);
	if (strCountryName.empty())
		return;
	
	strProvinceName = m_contactInfoCollectionUtils.GetNameByCodeInAreaMap(strCountryCode, strProvinceCode);
	if (strProvinceName.empty())
		return;
	
	strCityName = m_contactInfoCollectionUtils.GetNameByCodeInAreaMap(strProvinceCode, strCityCode);
}


std::string CContactDetailInfoUtils::GetKeyValue(const KeyValueMap_t& keyValueMap, const std::string& strKey)
{
	std::string strRet = "";
	KeyValueMap_t::const_iterator p = keyValueMap.find(strKey);
	if (p == keyValueMap.end())
		return strRet;
	else {
		return p->second;
	}
    
}

void CContactDetailInfoUtils::MakeContactDetailInfo(const KeyValueMap_t& profileMap, CContactPersonalDetailInfo& detailInfo)
{
	//递归detailinfo的InfoType map,根据key得到profileMap里的值
	//这个profileMap里的值可能是code也可能是直接是值
	//如果key是area相关的，则特殊处理
	//先到contactInfoCollections里去寻找值
	//如果找不到值,则就是值
	//如果找到，则设置为值
	
	const CContactPersonalDetailInfo::InfoTypeKeyMap_t& infoTypeKeyMap = detailInfo.GetInfoTypeKeyMap();
	
	do
	{
		CContactPersonalDetailInfo::InfoTypeKeyMap_t::const_iterator b = infoTypeKeyMap.begin();
		CContactPersonalDetailInfo::InfoTypeKeyMap_t::const_iterator e = infoTypeKeyMap.end();
		for (; b != e; ++b)
		{
			CContactPersonalDetailInfo::EnInfoType infoType = b->first;
			const std::string& strKey = b->second;
			
			std::string strProfileMapValue = GetKeyValue(profileMap, strKey);
			
			if (infoType == CContactPersonalDetailInfo::GENDER_INFO && strProfileMapValue.empty())
			{
				strProfileMapValue = "0"; //性别为保密
			}
			
			std::string strValue = strProfileMapValue;
			
			
			//strProfileMapValue可能就是值（譬如生日字段），也可能是个code(譬如性别字段），如果是code则需要二次查询对应的值
			//去contactinfocollections里去查询
			
			if (strKey != COUNTRY_KEYWORD_ID && strKey != PROVINCE_KEYWORD_ID && strKey != CITY_KEYWORD_ID)
			{
				std::string strNameByCode = m_contactInfoCollectionUtils.GetNameByCodeInNormalInfoMap(strKey, strProfileMapValue);
				if (!strNameByCode.empty())
					strValue = strNameByCode; //如果非空，则表示strProfileMapValue真的是个code，而不是个值
			}
			
			detailInfo.SetInfo(infoType, strValue);
		}
		
		
		std::string strCountryName, strProvinceName, strCityName;
		GetAreaName(profileMap, strCountryName, strProvinceName, strCityName);
		
		detailInfo.SetAreaInfo(strCountryName, strProvinceName, strCityName);
		
	} while (0);
	
}

void CContactDetailInfoUtils::MakeDetailInfo(KeyValueMap_t  profileMap, CContactPersonalDetailInfo * detailInfo)
{
#if 0
	KeyValueMap_t profileMap;
   
#define INSERT_ITEM(key, value) profileMap.insert(KeyValueMap_t::value_type((key), (value)))
	
	INSERT_ITEM(UID_KEYWROD_ID, "cnalichnwirelesstest");							//用户id
	INSERT_ITEM(NAME_KEYWORD_ID, "徐明刚");						//姓名
	INSERT_ITEM(GENDER_KEYWORD_ID, "0");//保密						//性别
	INSERT_ITEM(BIRTH_KEYWORD_ID, "1983/1/1");						//生日
	INSERT_ITEM(CONSTELLATION_KEYWORD_ID, "3");	//双子座		//星座
	INSERT_ITEM(SHENGXIAO_KEYWORD_ID, "3");	//虎"				//生肖
	INSERT_ITEM(COUNTRY_KEYWORD_ID, "100000000");	//中国					//国家
	INSERT_ITEM(PROVINCE_KEYWORD_ID, "100330000");	//浙江省				//省份
	INSERT_ITEM(CITY_KEYWORD_ID, "100330800"); //衢州市							//城市
	INSERT_ITEM(MOBILE_KEYWORD_ID, "13666611111");					//手机
	INSERT_ITEM(PHONE_KEYWORD_ID, "0571-741741741");						//电话
	INSERT_ITEM(EMAIL_KEYWORD_ID, "a@b.com");							//邮箱
	INSERT_ITEM(CAREER_KEYWORD_ID, "drillmaster");	//培训师					//职业
	INSERT_ITEM(SCHOOL_KEYWORD_ID, "浙江名牌大学");					//毕业院校
	INSERT_ITEM(PERSONALWEBSITE_KEYWORD_ID, "www.sina.com.cn");		//个人主页
#endif	
	 
	MakeContactDetailInfo(profileMap, *detailInfo);
	
}


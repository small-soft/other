#ifndef XUMINGGANG_IM_CONTACTDETAILINFOUTILS_H
#define XUMINGGANG_IM_CONTACTDETAILINFOUTILS_H

#include <map>

#include "IPacketHandler.h"
//#include "LoginDataStructDefs.h"
#include "LoginUtils.h"
#include "ContactInfoCollectionUtils.h"

typedef std::map<std::string, std::string>									KeyValueMap_t;

class CContactDetailInfoUtils: public IPacketHandler
{
public:
	void Init(IPacketMgr* pPackMgr, CLoginUtils *pLoginUtils);
	
//	virtual void OnPacket(uint32_t nCmd, const CScHead& header, std::string& pack);
	
	void GetContactDetailInfo(const std::string& strUid);
	void SetSelfDetailInfo(const CContactPersonalDetailInfo& detailInfo);
	
	std::string GetCityName(const std::string& strCityCode);
	std::string GetGenderName(const std::string& strGenderCode);
    
    void MakeDetailInfo(KeyValueMap_t  profileMap, CContactPersonalDetailInfo * detailInfo);
    
private:
	
    
	void MakeProfileMap(const CContactPersonalDetailInfo& detailInfo, KeyValueMap_t& profileMap);
	void MakeContactDetailInfo(const KeyValueMap_t& profileMap, CContactPersonalDetailInfo& detailInfo);
	std::string GetKeyValue(const KeyValueMap_t& keyValueMap, const std::string& strKey);
	
	void GetAreaName(const KeyValueMap_t& profileMap, std::string& strCountryName, std::string& strProvinceName, std::string& strCityName);
	void GetAreaCode(const CContactPersonalDetailInfo& detailInfo, std::string& strCountryCode, std::string& strProvinceCode, std::string& strCityCode);
	
private:
	CLoginUtils							*m_pLoginUtils;
	CContactInfoCollectionUtils			m_contactInfoCollectionUtils;
};

#endif //XUMINGGANG_IM_CONTACTDETAILINFOUTILS_H



#ifndef XUMINGGANG_IM_CONTACTINFO_COLLECTION_UTILS_H
#define XUMINGGANG_IM_CONTACTINFO_COLLECTION_UTILS_H

#include <map>
#include <string>
#include <vector>
//#include "../Utils/DreamUnitTest.h"
#include "LoginDataStructDefs.h"

class CContactInfoCollectionUtils
{
public:	
	CContactInfoCollectionUtils();
	~CContactInfoCollectionUtils();
	
	std::string GetNameByCodeInNormalInfoMap(const std::string& strKey, const std::string& strCode);
	std::string GetNameByCodeInAreaMap(const std::string& strParentCode, const std::string& strCode);
	
	std::string GetCodeByNameInNormalInfoMap(const std::string& strKey, const std::string& strName);
	std::string GetCodeByNameInAreaMap(const std::string& strKey, const std::string& strName);
	
    InfoItemList_t GetAreaInfoItemList(const std::string& strKey);


private:
	struct Item
	{
		std::string								m_strCode;
		std::string								m_strName;
	};
	
	typedef std::vector<Item> ItemVec_t;
	
	typedef std::map<std::string, ItemVec_t> ItemMap_t;

	bool LoadInfoCollections();
	bool UnloadInfoCollections();

	InfoItemList_t GetInfoItemListImpl(const std::string& strKey, ItemMap_t& itemMap);
	bool MakeCommaPartItemVec(const std::string& commaPart, ItemVec_t& itemVec);
	
	//insert the data(title:c1,n1,c2,n2,c3,n3) to the item map 
	bool InsertData2ItemMap(const std::string& strData, ItemMap_t& itemMap);
	
	bool InitItemMap(const std::string& strData, ItemMap_t& itemMap);
	
	bool InitAreaMap();
	
	bool InitOtherInfoMap();
	
	//strTitle means gender, constellation, shengxiao etc. category
	//if error or not find, return empty string
	std::string GetNameByCode(const std::string& strTitle, const std::string& strCode, const ItemMap_t& itemMap);
	
	//strTitle means gender, constellation, shengxiao etc. category
	//if error or not find, return empty string
	std::string GetCodeByName(const std::string& strTitle, const std::string& strName, const ItemMap_t& itemMap);
	

	ItemMap_t		m_areaMap; //handle country, province, city stuff
	ItemMap_t		m_infoMap; //handle constellation, shengxiao, career etc. stuff
	

};
#endif //XUMINGGANG_IM_CONTACTINFO_COLLECTION_UTILS_H
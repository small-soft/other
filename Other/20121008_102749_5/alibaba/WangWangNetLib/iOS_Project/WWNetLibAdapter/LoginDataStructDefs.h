#ifndef LOGIN_USER_LOGIN_INFO_H
#define LOGIN_USER_LOGIN_INFO_H

#include <string>
#include <map>
#include <vector>

//#include "CommonDefs.h"
#include "AIMEnum.h"

typedef AIM_PRESENCE EnLoginStatus;

struct CWangWangEnviroment
{
	//旺旺的客户端版本，服务器将来可能需要这个版本号用来做升级之类的事情
	std::string								m_strWangWangVersion;
};



enum EnPasswordType
{
	//真实密码类型
	REAL_PASSWORD = 0, 

	//用于本地保存的密码，非真实的密码，而是第一个登陆成功后服务器返回的一个伪密码，用于客户端自动登陆，并且不泄露真实的密码
	TOKEN_PASSWORD = 1, 
};



struct CPassword
{	
	std::string								m_strPassword;

	EnPasswordType							m_passwordType;
};



//根据时间戳，服务器会决定是否联系人关系有更新，第一次登陆后，在回调接口里有以下3个对应的时间戳
//客户端本地应该保存起来，下次登陆的时候传递进来
struct CContactsInfoTimestamp
{	
	uint32_t								m_groupListTimestamp;

	uint32_t								m_contactListTimestamp;

	uint32_t								m_blackListTimestamp;
};


enum EnBasicStatus
{
	BASICSTATUS_OFFLINE = 0,
	BASICSTATUS_ONLINE = 1,
	BASICSTATUS_INVISIBLE = 2
};

enum EnDetailStatus
{
	IMPREDEFSTATUS_OFFLINE	= 0,// 离线
	IMPREDEFSTATUS_FREE	= 1,// 在线
	IMPREDEFSTATUS_BUSY	= 2,//忙碌中
	IMPREDEFSTATUS_AWAY	= 3,//不在电脑旁
	IMPREDEFSTATUS_INCALL	= 4,//接听电话中
	IMPREDEFSTATUS_OUTFORDINNER	= 5,//外出就餐
	IMPREDEFSTATUS_WAIT	= 6,//稍候
	IMPREDEFSTATUS_INVISIBLE	= 7,// 隐身
	IMPREDEFSTATUS_OFFLINELOGON	= 8,//离线登陆
	IMPREDEFSTATUS_UNKNOW	= 9,//未知
	IMPREDEFSTATUS_FAKEONLINE	= 10,//假在线，E客服使用
	IMPREDEFSTATUS_MOBILEONLINE	= 12, //手机在线
	IMPREDEFSTATUS_MOBILE_FREE_1	= 30,
	IMPREDEFSTATUS_MOBILE_FREE_2	= 33,
	IMPREDEFSTATUS_MOBILE_BUSY	= 34,
	IMPREDEFSTATUS_MOBILE_AWAY	= 35,
	IMPREDEFSTATUS_MOBILE_INCALL	= 36,
	IMPREDEFSTATUS_MOBILE_OUTFORDINNER	= 37,
	IMPREDEFSTATUS_MOBILE_WAIT	= 38,
	IMPREDEFSTATUS_MOBILE_INVISIBLE	= 39,
	IMPREDEFSTATUS_MOBILE_OFFLINELOGON	= 40,
	IMPREDEFSTATUS_MOBILE_SELFDEF	= 41,
	IMPREDEFSTATUS_NUM	= IMPREDEFSTATUS_MOBILE_SELFDEF + 1
};


//联系人的状态
struct CContactStatus
{
	//联系人的id
	std::string								m_strUid;
/*
	//基本状态(0-在线,1-离线,2-隐身)
    EnBasicStatus							m_basicStatus;

	//详细状态,参看EnDetailStatus枚举值
    EnDetailStatus							m_detailStatus;
*/    
    EnLoginStatus                           m_defaultPresence;
};

typedef std::vector<CContactStatus>			ContactStatusList_t;

//登录用户开始登录时的信息
struct CLoginUserLoginInfo
{
	//登录的id,譬如cntaobao徐明刚
	std::string								m_strUid; 

	//登录的密码
	CPassword								m_password;

	//时间戳
	CContactsInfoTimestamp					m_timestamp;

	//登陆时选择的状态
	CContactStatus							m_loginStatus;
};

//登录的步骤
//目前分为2个步骤,检查版本号，验证
//只有最后一个步骤走完，才认为是登录真正成功了
//之所以提供详细的多个步骤，是提供给外部库一个机会，登录的时候向用户显示
//当前登录正在做些什么事情,如果不需要此功能，直接处理最后一个步骤
enum EnLoginStep
{
	STEP_CHECK_VERSION = 0,
	STEP_AUTH,
	//STEP_GET_CONTACTS_INFO
};

//登录最后一个步骤执行成功后，返回的值
//注意：只有最后一个步骤执行成功后，才能查看该值的内容
struct CLoginFinalResult
{
	CLoginFinalResult() : m_bGroupListUpdated(false)
	, m_bContactListUpdated(false)
	, m_bBlackListUpdated(false)
	{}
	bool								m_bGroupListUpdated;   //组是否有更新，参看CContactsInfoTimeStamp的说明
	bool								m_bContactListUpdated; //联系人是否有更新
	bool								m_bBlackListUpdated;   //黑名单列表是否有更新
	
	std::string							m_strRemark;			// 登陆返回错误时带的说明文案，客户端用来显示
	std::string							m_strTokenPassword; //the token type password returned by the server, check out CPassword structure
};

//登录用户拥有的一些能力
//低级别用户（如刚注册的用户），有些能力无法拥有
struct CLoginUserCapability
{
	bool								m_bCanSendMsg; //能否发送消息
	bool								m_bCanAddContact; //能否添加联系人
	bool								m_bCanSendGroupMsg; //能否群发消息
	bool								m_bActivated;	//是否激活
};

//组信息
struct CGroupInfo
{
	int64_t								m_groupId; //组id
    int64_t								m_parentId; //父组id
	std::string							m_groupName; //组名
};


typedef std::vector<CGroupInfo>			GroupList_t;

//联系人信息
struct CContactInfo
{
	std::string								m_strUid; //联系人id
	std::string								m_strNickName; //联系人昵称
	int64_t									m_groupId;//联系人所在组的id
};

typedef std::vector<CContactInfo>		ContactList_t;
typedef std::vector<std::string>		BlackList_t;

//联系人的详细信息
class CContactPersonalDetailInfo
{
public:
	enum EnInfoType
	{
		UID_INFO,							//用户id
		DISPNAME_INFO,						//姓名
		GENDER_INFO,						//性别
		BIRTHDAY_INFO,						//生日
		CONSTELLATION_INFO,					//星座
		SHENGXIAO_INFO,						//生肖
		COUNTRY_INFO,						//国家
		PROVINCE_INFO,						//省份
		CITY_INFO,							//城市
		MOBILEPHONE_INFO,					//手机
		TELEPHONE_INFO,						//电话
		EMAIL_INFO,							//邮箱
		CAREER_INFO,						//职业
		GRADSCHOOL_INFO,					//毕业院校
		PERSONALWEBSITE_INFO,				//个人主页
	};
	
	typedef std::map<EnInfoType, std::string>						InfoTypeKeyMap_t;
	typedef std::map<std::string, std::string>						KeyValueMap_t;
	
	CContactPersonalDetailInfo();
	
	
	//获取对应字段的值
	std::string GetInfo(EnInfoType enInfoType) const;
	
	//更新对应字段的值
	bool SetInfo(EnInfoType enInfoType, const std::string& strNewValue);
	
	
	//地域字段要特殊处理，因为内部字段的保存方式都是通过国家找到对应的省份列表，通过省份找到对应的城市列表
	//因此这里特殊处理
	bool SetAreaInfo(const std::string& strCountryValue, const std::string& strProvinceValue, const std::string& strCityValue);
	
	const InfoTypeKeyMap_t& GetInfoTypeKeyMap() const;
	
	const KeyValueMap_t& GetKeyValueMap() const;

	
//#define MY_UNIT_TEST
#ifdef MY_UNIT_TEST
	void test_InitInfoTypeKeyMap();
	void test_GetInfoTypeKey();
	void test_SetKeyValue();
	void test_GetInfo();
	void test_SetAreaInfo();
	
#endif //MY_UNIT_TEST
private:

	std::string GetInfoTypeKey(EnInfoType enInfoType) const;
	std::string GetKeyValue(const std::string& strKey) const;
	void SetKeyValue(const std::string& strKey, const std::string& strValue);
	bool InitInfoTypeKeyMap();
	
private:
	
	InfoTypeKeyMap_t												m_infoTypeKeyMap;
	KeyValueMap_t													m_keyValueMap;
};

enum EnSpecialGroups
{
	TOPMOST_GROUP_ID = -1,
	RECENT_CONTACTS_GROUP_ID = -2,
	UNKNOWN_CONTACTS_GROUP_ID = -5,
	BLACKLIST_CONTACTS_GROUP_ID = -6
};

struct CSearchContact
{
	std::string									m_strUid;
	std::string									m_stNickName;
	std::string									m_strAge;
	std::string									m_strGender;
	std::string									m_strCity;
	EnBasicStatus								m_basiCStatus;
};

typedef std::vector<CSearchContact>				SearchContactList_t;


enum EnTextMsgType
{
	TEXT_MSG_NORMAL_TEXT = 0, //正常文本 
	TEXT_MSG_AUTO_REPLY, //自动回复
	TEXT_MSG_GROUP_SEND, //群发的消息
	TEXT_MSG_PICTURE,	//这条文本消息是贴图
	TEXT_MSG_CONTACT	//添加好友请求
};
struct CTextMsg
{
	std::string									m_strPeerContactId; //对方的uid
	std::string									m_strTextContent; //文本消息内容
	uint32_t									m_nTextSequence; //消息的序列号，从0开始递增
	EnTextMsgType								m_type;			//消息的类型，根据消息的类型可以提示譬如（［自动回复]我正在吃饭，稍候联系！ [群发]下午3点小组半亩地吃饭！ etc.)
	
	uint32_t									m_nTime; //格林尼治时间？
};

//个人详细资料里一个字段的所有可能列表，如星座的所有列表
typedef std::vector<std::string>				InfoItemList_t;

struct CAddedContact
{
	std::string									m_strUid;
	std::string									m_strDispName; //显示名
	int64_t										m_nGroupId; //所在的组id
};

typedef std::vector<std::string> StrVec_t;

struct CUidSignature
{
	std::string									m_strUid; //联系人id
	std::string									m_strSignature;//id对应的签名
};

typedef std::vector<CUidSignature> UidSignatures_t;



typedef std::vector<CTextMsg> TextMsgList_t;

//被好友添加的验证设置的选项 
enum EnAddedAuthFlag
{
	ADDED_AUTH_NONE = 0, //不用我验证就能加我为好友
	ADDED_AUTH_REQUIRE_MYSELF_AUTH = 1, //需要我验证，才能加我为好友
	ADDED_AUTH_DENY_ALL = 2 //拒绝任何人加我为好友
};

enum EnMySelfAddedResult
{
	MY_SELF_ADDED_OK = 0, //允许对方添加
	MY_SELF_ADDED_DENY, //拒绝对方添加
	MY_SELF_ADDED_IGNORE, //忽略对方的添加请求
};

enum EnPeerRequestSendPicResult
{
	ACCEPT_PEER_SEND_PIC = 0, //接受
	DENY_PEER_SEND_PIC, //拒绝
	PIC_ALREADY_EXIST //图片已经存在
};
#endif //LOGIN_USER_LOGIN_INFO_H
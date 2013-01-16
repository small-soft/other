#ifndef IM_NET_H
#define IM_NET_H



#ifdef __cplusplus
extern "C" {
#endif
	/************************************************************************/
	// prototype define
	/************************************************************************/

#include "string.h"
#include "PacketConnection.h"
#include "PCEvent.h"
#include "hashtable.h"
	typedef AMInt32 IMnetRetCode;

//#define	IM_PROTOCOL_VERSION			"6.5.0.Mobile_J2ME_Common_Buyer"
//#define 	IM_PROTOCOL_VERSION			"6.0.0.Mobile_J2ME_N73"
//#define 	IM_PROTOCOL_VERSION			"6.5.0.Mobile_J2ME_I61"
//#define	IM_PROTOCOL_VERSION			"6.5.0.Mobile_J2ME_Common"

//正式使用的编号

#ifdef ANDROID_BUILD
	//v1.0.0
	//#define	IM_PROTOCOL_VERSION			"6.5.0.Mobile_Android_N2_Buyer" 
	//v1.2.0
	#define	IM_PROTOCOL_VERSION			"6.6.0.Mobile_Android_N2_Buyer"
	//v1.2.4
	//#define	IM_PROTOCOL_VERSION			"6.06.04.Mobile_Android_N2_Buyer"

#elif defined(IOS_BUILD)

	#define	IM_PROTOCOL_VERSION			"6.6.0.Mobile_Android_N2_Buyer"

#else
	//ww_alios版本号
	//#define	IM_PROTOCOL_VERSION			"1.00.01_ww_alios_na_w700"
	//云聊版本号
	#define	IM_PROTOCOL_VERSION			"1.00.01_yunliao_alios_na_w700"
#endif

#define CHECK_VERSION_SUCESS			0
#define CHECK_VERSION_COMPATIBLE		1
#define CHECK_VERSION_NONCOMPATIBLE		2
#define CHECK_VERSION_UNKNOWN			0xFF

	/************************************************************************/
	// macro, enum, union, structure declare
	/************************************************************************/
#undef MACRO_DEF_SECOND_PROTOCOL
#define MACRO_DEF_SECOND_PROTOCOL(id, value)

	enum{
#undef MACRO_DEF
#define MACRO_DEF(id, value, structDef)				id=value,
#undef MACRO_DEFS
#define MACRO_DEFS(id, value, structDef)			id=value,
#undef MACRO_DEFR
#define MACRO_DEFR(id, value, structDef)			id=value,
#undef MACRO_DEF_EXTERN
#define MACRO_DEF_EXTERN(id, value, structDef)		id=value,
#include "IMnetEventDef.h"
	};

#define		eIMnetOK						eOK
#define		eIMnetNotReady					eNotReady
#define		eIMnetAlreadyExist				eAlreadyExist
#define		eIMnetEventExchange				0x0100
#define		eIMnetRegisterError				0x0101
#define		eIMnetUnRegisterError			0x0102
#define		eIMnetUnsupportedFeature		0x0103
#define		eIMnetPropertyError				0x0104
#define		eIMnetInvalidCmd				0x0105
#define		eIMnetInvalidStarter			0x0106
#define		eIMnetInvalidLRC				0x0107
#define		eIMnetInvalidCC					0x0108
#define		eIMnetBodyDataZero				0x0109
#define		eIMnetEncryptKeyLost			0x010A
#define		eIMnetInflateError				0x010B
#define		eIMnetSkip						0x010C

	typedef struct {
		/**
		* 返回码 retCode
		* 0x01兼容版本，能登录，视情况启动更新程序
		* 0x02:不兼容版本，不能登录，提示用户确认自己的程序版本
		* 0xff:未知版本，不能登录，提示用户确认自己的程序版本

		#define CHECK_VERSION_SUCESS			0
		#define CHECK_VERSION_COMPATIBLE		1
		#define CHECK_VERSION_NONCOMPATIBLE		2
		#define CHECK_VERSION_UNKNOWN			0xFF
		*/
		AMInt32		retCode;
	}ImEventCheckVersion;

	typedef struct {
		AMChar*		bindID;		  //绑定帐号的id, 为空表示主帐号
		AMInt32     bindIDLen;
		AMInt32		retCode;		// 返回码
		AMInt32		timestampFlag;	// 时间戳标志
		AMInt32		clientIp;		// 客户端IP
		AMInt32		lastClientip;	// 上次登陆的客户端IP
		AMInt32		serverTime;		// 服务器时间 GMT
		AMChar*	    workKey;        // 加密密钥
		AMInt32     workKeyLen;
		AMChar*	    pwtoken;	    // auto logon use it
		AMInt32     pwtokenLen;
		AMChar*	    webmd5pw;       // 网站md5密码
		AMInt32     webmd5pwLen;
		AMChar*	    bindid;         // 绑定的IMID
		AMInt32     bindidLen;
		AMChar*		rid;
		AMInt32     ridLen;
		AMChar*		remark;          // 备注信息
		AMInt32     remarkLen;     
		AMUInt8		propertyNum;
	}ImRspLogin,
	 ImEventLoginStatus;

	typedef struct {
		AMUInt8		propertyNum;
		AMInt32		retCode;
		AMInt32		timestampFlag;                  // 时间戳标志
		AMChar	*	remark;
		AMInt32		remarkLen;
	}ImRspLogin2,
		ImEventLogin2;

	typedef struct ST_UserGroupList{
		struct ST_UserGroupList* pNext;
		AMInt32					 groupIDHigh;
		AMInt32					 groupIDLow;
		AMInt32					 parentIDup;
		AMInt32					 parentIDlw;
		AMChar*					 groupName;
		AMInt32                  groupNameLen;
		AMInt8					 num;
	}UserGroupList;

	typedef struct {
		AMChar*			bindID;		  //绑定帐号的id, 为空表示主帐号
		AMInt32         bindIDLen;
		AMInt32			retCode;
		UserGroupList*	groupList;  //group首指针
		AMInt32			groupCount; //用来记录Group的个数
		AMInt32			timestamp;
		AMUInt8			propertyNum;
	}ImRspGetGroup,
	ImEventGetGroup;

	typedef struct {
		AMInt32						groupIDHigh;
		AMInt32						groupIDLow;
		AMChar*						contactID;
		AMInt32                     contactIDLen;
		AMChar*						nickName;
		AMInt32                     nickNameLen;
		AMChar*						importance;
		AMInt32                     importanceLen;
	}ContactInfo;

	typedef struct ST_UserContactList {
		ContactInfo                 contactInfo;
		AMInt8						num;
		struct ST_UserContactList*	pNext;
	}UserContactList;

	typedef struct {
		AMChar*						bindID;		  //绑定帐号的id, 为空表示主帐号
		AMInt32                     bindIDLen;
		AMInt32				        retCode;
		UserContactList*	        contactList;  //contact首指针
		AMInt32				        contactCount; //用来记录contact的个数
		AMInt32				        timestamp;
		AMUInt8				        propertyNum;
	}ImRspGetContact,
	 ImEventGetContact;

	typedef struct ST_ContactList {
		AMChar*				   userID;
		AMInt32                userIDLen;
		struct ST_ContactList* pNext;
	}ContactList;

	typedef struct {
		AMChar*				bindID;		  //绑定帐号的id, 为空表示主帐号
		AMInt32             bindIDLen;
		AMInt32				retCode;
		ContactList*	    contactList;
		AMInt32				contactCount;
		AMInt32				timestamp;
		AMUInt8				propertyNum;
	}ImRspCommonContactList,
	ImRspGetBlack,
	ImEventGetBlack,
	ImRspGetReverseBlack,
	ImEventGetReverseBlack,
	ImRspDeleteContact,
	ImEventDeleteContact;

	typedef struct {
		AMInt32     retCode;    //0：成功；其他值：失败
		AMInt32		groupIDHigh;
		AMInt32		groupIDLow;
		AMInt32     timestamp;
		AMChar*		contactID;
		AMInt32     contactIDLen;
		AMInt8      opcode;     //0 - 同意,1 - 拒绝，同时发送拒绝消息给请求方，由客户端使用二级协议传递消息通知对方
		AMUInt8		propertyNum;
	}ImRspAddContactACK,
		ImEventAddContactACK;

	typedef struct ST_ContactStatusList {
		AMChar*		                 userID;
		AMInt32                      userIDLen;
		AMInt8                       basicStatus;
		AMInt8                       predefStatus;
		AMInt8		                 num;
		struct ST_ContactStatusList* pNext;
	}ContactStatusList;

	typedef struct {
		AMInt32             retCode;
		ContactStatusList*  contactStatusList;  // 联系人状态列表
		AMInt32             contactStatusCount; // 状态列表中元素个数
		AMUInt8		        propertyNum;
	}ImRspGetContactStatus,
	ImEventGetContactStatus,
	ImRspSubscribeInfo,
	ImEventSubscribeInfo;

	typedef struct {
		AMChar*		bindID;
		AMInt32     bindIDLen;
		AMUInt32	retCode;		// 返回码
		AMUInt32	needNextlevel;	// 升下一级还需要的活跃度数
		AMUInt32	activity;		// 活跃度
		AMInt8		addcontactFlag; // 添加为联系人校验标志
		AMInt8		sendmsgFlag;	// 发送消息校验标志
		AMInt8		actLevel;		// 活跃度等级
		AMInt8		imlevel;		// IM level,
		AMInt8		mulsendflag;	// 是否允许群发;
		AMUInt8		propertyNum;
	}ImRspGetUserInfo,
		ImEventGetUserInfo;	

	typedef struct {
		AMChar*		bindID;
		AMInt32     bindIDLen;
		AMInt8      type;
		AMChar*     remark;
		AMInt32     remarkLen;
		AMUInt8		propertyNum;
	}ImNtfForceDisconnect,
	ImEventNtfForceDisconnect,
	ImNtfBindIDKicked,
	ImEventNtfBindIDKicked;

	typedef struct {
		AMInt32     retCode;    // 0x00:成功；其他值：失败
		AMInt32     connectNo;  // 连接号
		AMChar*     remark;     // 附带信息
		AMInt32     remarkLen;
		AMUInt8		propertyNum;
	}ImRspReLogin,
	ImEventReLogin;

	typedef struct {
		AMInt32     retCode;        // 0：成功；其他值：失败
		AMInt8      addcontactFlag; // 0：不需要验证；1：需要验证
		AMInt8      sendmsgFlag;    // 0：允许发送；1：不允许发送
		AMInt8      enableSearch;   // 0：不能搜索到；1：可以搜索到
		AMUInt8		propertyNum;
	}ImRspChangeUserVerify,
	ImEventChanageUserVerify;

	//添加联系人相关错误描述
	typedef enum
	{
		eIMADDCONTACTRESULT_SUCCESS = 0,			//"添加成功";
		eIMADDCONTACTRESULT_ADDED,					//"该联系人已经是你的好友，不能再次添加";
		eIMADDCONTACTRESULT_NOID,					//"联系人ID不存在";
		eIMADDCONTACTRESULT_FULL,					//"您的联系人已经达到了最大人数，不能再添加新的联系人了。";
		eIMADDCONTACTRESULT_FULLTODAY,				//"今日添加联系人数目已满";
		eIMADDCONTACTRESULT_NEEDAUTH,				//"对方需要验证";
		eIMADDCONTACTRESULT_NORIGHT,				//"您的帐号未激活，不能添加联系人，请先激活。";
		eIMADDCONTACTRESULT_NOTACTIVEID,			//"对方未激活";
		eIMADDCONTACTRESULT_WAITAUTH,				//"等待验证";
		eIMADDCONTACTRESULT_DENYALL,				//"拒绝被任何人添加";
		eIMADDCONTACTRESULT_HIGHFRENQ,				//"操作太频繁,请稍后再试";
		eIMADDCONTACTRESULT_ESERVICETEAMMATE = 0xc,	//"E客服相关";
		eIMADDCONTACTRESULT_OTHERERROR				//"其他错误";
	}AddContactInfoCode;

	typedef enum {
		eIMADDCONTACT_SUCCESS		= 0,
		eIMADDCONTACT_FAILED		= -1,
		eIMADDCONTACT_NEEDVERIFY	= 1,
		eIMADDCONTACT_WAITAUTH		= 2,
	}AddContactRetCode;

	typedef struct {
		AMChar*		bindID;
		AMInt32		bindIDLen;
		AddContactRetCode		retCode; // 0:成功, -1:失败, 1:需要验证, 2:等待验证
		AMInt32					timestamp;
		ContactInfo				contactInfo;
		AddContactInfoCode		info;
	}ImEventAddContact;
	/*
	 *	ImRspAddContact is not an IMNetEvent. It's here only to support TARGET_VMKIT.addContact.
	 */

	typedef struct {
		AMChar*		bindID;
		AMInt32		bindIDLen;
		AMInt32     timestamp;
		AMInt32     retCode; // 0:成功, -1:失败, 1:需要验证, 2:等待验证
		ContactInfo contactInfo;
		AMInt32		bContactInfoUsed;
		AMInt8      type;
		AMUInt8		propertyNum;
	}ImRspAddContact;

	typedef struct {
		AMInt32     retCode; // 0：成功；其他值：失败
		AMInt32     timestamp;
		AMChar*     blackId; // 黑名单ID
		AMInt32     blackIdLen;
		AMUInt8		propertyNum;
	}ImRspAddBlack,
	ImEventAddBlack;

	typedef struct {
		AMInt32     retCode; // 0：成功；其他值：失败
		AMChar*     blackId; // 黑名单ID
		AMInt32     blackIdLen;
		AMInt32     timestamp;
		AMUInt8		propertyNum;
	}ImRspDeleteBlack,
	ImEventDeleteBlack;

	typedef struct {
		AMInt32		retCode;
		AMChar*		contactID;
		AMInt32		contactIDLen;
		AMChar*		memo;
		AMInt32		memoLen;
		AMUInt8		propertyNum;
	}ImRspGetContactMemo,
		ImEventGetContactMemo;

	typedef struct {
		AMChar*	bindID;
		AMInt32 bindIDLen;
		AMInt32	online; //1:在线消息，0:离线消息
		AMInt32	iType;	//0:文本消息，1:图片消息。图片消息的内容是xml
		AMChar* fromId;
		AMInt32 fromIdLen;
		AMChar* msgContent;
		AMInt32 msgContentLen;
		AMInt32 sendTime;
		AMInt32	iServerType;	//0x01表示建议客户端过滤
	}TextMsg;

	typedef struct ST_ImEventChatMessage{
		TextMsg								msg;
		AMInt32								ackSeq;
		struct ST_ImEventChatMessage*		next;
	}ImEventChatMessage;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventBuzzMessage;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventP2PMessage;

	typedef struct ST_ImEventAutoReply {
		TextMsg							msg;
		struct ST_ImEventAutoReply*		next;
	}ImEventAutoReply;

	typedef struct ST_ImEventU2UMessage {
		AMInt16 cmd;
		AMChar* fromId;
		AMInt32 fromIdLen;
		AMChar* msg;
		AMInt32 msgLen;
	}ImEventU2UMessage;

	//typedef struct ST_ImEventVideoChatInvite {
	//	AMChar* fromId;
	//	AMInt32 fromIdLen;
	//	AMChar* phone;
	//	AMInt32 phoneLen;
	//}ImEventVideoChatInvite;

	//typedef struct ST_ImEventVideoChatInviteCancel {
	//	AMInt32			code;	
	//}ImEventVideoChatInviteCancel;

	//typedef struct ST_ImEventVideoChatInviteRsp {
	//	AMInt32			code;	//accept,reject, or others
	//	AMChar*			fromId;
	//	AMInt32			fromIdLen;
	//	AMChar*			phone;
	//	AMInt32			phoneLen;
	//}ImEventVideoChatInviteRsp;

	typedef struct {
		AMChar* fromId;
		AMInt32 fromIdLen;
		AMChar* msgContent;
		AMInt32 msgContentLen;
		AMInt32 sendTime;
	} OffObj;

	typedef struct ST_ImEventOffObj{
		OffObj							obj;
		struct ST_ImEventOffObj		*	pNext;
	}ImEventOffObj;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventMessageAck;

	typedef struct {
		AMInt32			sendtime; //1:在线消息，0:离线消息
		AMChar*			fromID;
		AMInt32			fromIDLen;
	}ImEventToDeleteOfflineMsg;

	typedef struct {
		AMChar*			bindID;
		AMInt32			bindIDLen;
		AMInt32			online; //1:在线消息，0:离线消息
		AMChar*			fromID;
		AMInt32			fromIDLen;
	}ImEventContactAdded;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventContactIgnoreAdded;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventContactIgnoreDeled;

	typedef struct {
		AMChar*			bindID;
		AMInt32			bindIDLen;
		AMInt32			online; //1:在线消息，0:离线消息
		AMChar*			fromID;
		AMInt32			fromIDLen;
		AMChar*			dispName;
		AMInt32			dispNameLen;
		AMInt32			groupIDHigh;
		AMInt32			groupIDLow;
		AMChar*			verifyInfo;
		AMInt32			verifyInfoLen;
	}ImEventContactAskAddVerify;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
		AMChar*			fromID;
		AMInt32			fromIDLen;
		AMChar*			msg;
		AMInt32			msgLen;
	}ImEventContactAskAddNo;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
		AMChar*			fromID;
		AMInt32			fromIDLen;
		AMInt32			groupIDHigh;
		AMInt32			groupIDLow;
	}ImEventContactAskAddYes;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventWritingMessage;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventGroupBroadcast;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventPluginsQuery;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventPluginsRsp;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventPluginsInvite;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventCustomMessage;

	typedef struct {
		AMInt32			online; //1:在线消息，0:离线消息
	}ImEventFocusTalk;

	typedef struct {
		AMInt32     retCode;        // 0：成功；其他值：失败
		AMChar*     signature;      // 签名内容
		AMInt32     signatureLen;   // 签名长度
		AMUInt8		propertyNum;
	}ImRspChangeSignature,
	ImEventChangeSignature;	

	typedef struct ST_Contact_ExtraInfo {
		AMChar*				   userID;		//联系人长ID
		AMInt32                userIDLen;
		AMInt32                result;		//账号信息获取结果，0:正常
		AMChar*				   phone;		//绑定手机账号
		AMInt32                phoneLen;
		AMInt8		           propertyNum;
		struct ST_Contact_ExtraInfo* pNext;
	}Contact_ExtraInfo;

	typedef struct {
		AMUInt32	retcode;
		AMUInt32	timestamp;
		Contact_ExtraInfo*	    contactExtraInfos;
		AMInt32					contactCount;
		AMUInt8					propertyNum;
	}ImRspGetCNExtraInfo,
		ImEventGetCNExtraInfo;

	typedef struct ST_String_List {
		AMChar*				   str;			//联系人长ID
		AMInt32                strLen;
		struct ST_String_List* pNext;
	}String_List;

	typedef struct ST_Timestamp_Info {
		AMChar*				   userID;			//联系人长ID
		AMInt32                userIDLen;
		AMInt32                timestampFlag;	//时间戳标志
		AMInt32				   timestampList[4];//时间戳
		AMInt8		           propertyNum;
		struct ST_Timestamp_Info* pNext;
	}Timestamp_Info;


	typedef struct ST_Bind_Service {
		AMChar*				   serviceID;		
		AMInt32                serviceIDLen;
		AMChar*				   siteID;			//网站标识
		AMInt32                siteIDLen;
		AMChar*				   webID;			//网站ID
		AMInt32                webIDLen;
		AMChar*				   webUid;			//网站用户ID
		AMInt32                webUidLen;
		String_List*		   webUrl;
		AMInt32				   webUrlCount;
		AMInt8		           propertyNum;
		struct ST_Bind_Service* pNext;
	}Bind_Service;

	typedef struct {
		AMInt32			retcode;
		AMChar*			aliUID;			//统一ID
		AMInt32			aliUIDLen;
		AMChar*			aliUIDToken;	//统一ID token 用于免登
		AMInt32			aliUIDTokenLen;
		Bind_Service*	bindList;
		AMInt32			bindListCount;
		String_List*	loginIDList;
		AMInt32			loginIDListCount;
		AMUInt8					propertyNum;
	}ImRspGetWebBinding,
		ImEventGetWebBinding;

	/*	
	IMPREDEFSTATUS_OFFLINE	    = 0,    // 离线
	IMPREDEFSTATUS_FREE	        = 1,    // 在线
	IMPREDEFSTATUS_BUSY	        = 2,    //忙碌中
	IMPREDEFSTATUS_AWAY	        = 3,    //不在电脑旁
	IMPREDEFSTATUS_INCALL	    = 4,    //接听电话中
	IMPREDEFSTATUS_OUTFORDINNER	= 5,    //外出就餐
	IMPREDEFSTATUS_WAIT	        = 6,    //稍候
	IMPREDEFSTATUS_INVISIBLE	= 7,    // 隐身
	IMPREDEFSTATUS_OFFLINELOGON	= 8,    //离线登陆
	IMPREDEFSTATUS_UNKNOW	    = 9,    //未知
	IMPREDEFSTATUS_FAKEONLINE	= 10,   //假在线，E客服使用
	IMPREDEFSTATUS_NUM	        = 11,   //暂不处理
	IMPREDEFSTATUS_MOBILEONLINE	= 12    //手机在线
	*/
	typedef struct ST_StatusList{
		struct ST_StatusList*   pNext;
		AMChar*                 userID;
		AMInt32                 userIDLen;
		AMInt8                  basicStatus;
		AMInt8                  predefStatus;
		AMInt8					num;
	}StatusList;

	typedef struct {
		StatusList*	    statusList;  //status首指针
		AMInt32			statusCount; //用来记录status的个数
		AMUInt8			propertyNum;
	}ImNtfStatus,
	ImEventNtfStatus;

	typedef struct {
		AMChar*     style;      // 窗口模式
		AMInt32     styleLen;
		AMChar*     message;    // HTML格式
		AMInt32     messageLen;
		AMInt16     cmdId;      // 命令字
		AMUInt8		propertyNum;
	}ImNtfSystemMessage,
	ImEventNtfSystemMessage;

	typedef struct {
		AMChar*     fromID;      
		AMInt32     fromIDLen;
		AMChar*     serviceID;      
		AMInt32     serviceIDLen;
		AMChar*     webID;      
		AMInt32     webIDLen;
		AMInt32     cmdId;      
		OHTable	*	pOhtData;//object of StrStrPair
		AMInt32		iOhtDataLen;
		AMUInt8		propertyNum;
	}ImNtfWebUserMessage,
		ImEventNtfWebUserMessage;

	typedef struct ST_ImEventNtfSubscribeMsg{
		AMChar*     message;        // 订阅消息，如交易提醒等
		AMInt32     messageLen;
		AMUInt8		propertyNum;
		AMInt32		online;
		struct ST_ImEventNtfSubscribeMsg*	next;
	}ImNtfSubscribeMsg
		,ImEventNtfSubscribeMsg;

	typedef struct ST_ImNtfUpdateUsrExtInfo{
		AMUInt8		propertyNum;
		AMInt16		iCount;
		AMChar	*	szContactID;
		AMInt32		iContactIDLen;
		AMChar	*	szType;
		AMInt32		iTypeLen;
		AMChar	*	szValue;
		AMInt32		iValueLen;
		AMInt32		iFlag;
		struct ST_ImNtfUpdateUsrExtInfo *	next;
	}ImNtfUpdateUsrExtInfo,
		ImEventNtfUpdateUsrExtInfo;

	typedef struct {
		AMUInt8		propertyNum;
		AMInt32     retCode;
		AMChar	*	targetId;
		AMInt32		targetIdLen;
		AMInt32		clinetip;
		AMChar *	version;
		AMInt32		versionLen;
		AMUInt8		basicStatus;
		AMUInt8		predefStatus;
		AMUInt8		addcontactFlag; 
		AMUInt8		sendmsgFlag;	//是否允许发消息
		AMUInt8		reverseContact; //暂没什么用
	}ImRspGetPeerInfo,
		ImEventGetPeerInfo;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt8		clientId;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
		AMInt32		retCode;
		AMChar	*	retLongId;
		AMInt32		retLongIdLen;
		AMChar	*	retShowName;
		AMInt32		retShowNameLen;
	}ImRspGetPeerVerifyConfig
		,ImEventGetUserVerifyConfig;

 	typedef struct {
 		AMUInt8		propertyNum;
		AMInt32		retCode;
 		OHTable	*	pOhtData;//object of StrStrPair
		AMInt32		iTotalLength;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
 	}ImRspGetUserUDBProfile
 		,ImEventGetUserUDBProfile;

	typedef struct {
	 AMChar*	contactID;
	 AMInt32	contactIDLen;
	 AMChar*	nickName;
	 AMInt32	nickNameLen;
	 AMUInt8	age;
 	 AMUInt8	gender;
	 AMChar*	city;
	 AMInt32	cityLen;
  	 AMUInt8	basicStatus;
	}SearchUserInfo;
	
	typedef struct ST_SearchUserInfoList {
	 SearchUserInfo userInfo;
	 AMInt8			num;
	 struct ST_SearchUserInfoList* pNext;
	}SearchUserInfoList;
	
	typedef struct {
		AMInt32				        retCode;
		SearchUserInfoList*	        userList;  //user首指针
		AMInt32				        userCount; //用来记录user的个数
		AMInt32				        timestamp;
		AMUInt8				        propertyNum;
	}ImRspSearchUser
 		,ImEventSearchUser;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
		AMInt32		retCode;
		AMInt32		userLevel;
		AMInt32		totalDegree;
		AMInt32		needDegree;
		/*
		这里应该还有一个FT_VECTOR，UnpackImRspGetDegree里面没有解析
		*/
	}ImRspGetDegree
		,ImEventGetDegree;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt8		retCode;
		AMUInt8		mulStatus;
		AMChar	*	parentId;
		AMUInt32	parentIdLen;
		/*
		*这里还有一个Vector<SRcChileId>
		*/
	}ImRspHelpLogin
		, ImEventHelpLogin;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	accountId;
		AMUInt32	accountIdLen;
		AMUInt8		retCode;
	}ImRspHelpChangeSrvMode
		,ImEventHelpChgSrvMode;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	contactId;
		AMUInt32	contactIdLen;
		AMChar	*	messageType;
		AMUInt32	msgTypeLen;
		AMUInt32	ntfTime;
	}ImNtfOperationTip
		, ImEventOperationTip;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	szPacket;
		AMUInt32	uiPacketLen;
	}ImNtfNeedAuthCode
		,ImRawPacket;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;		//返回码
		AMChar	*	szServerIp;		//文件传送服务器地址
		AMInt32		iServerIpLen;
		AMUInt16	uiServerPort;	//端口号
		AMChar	*	szSessionId;	//SESSION号
		AMInt32		iSessionIdLen;
		AMUInt16	uiAppType;		//uiAppType=1 用于指明FTS应用
		AMUInt16	uiSubType;		//uiSubType=3 用于指明离线贴图类型
		AMUInt64	ulObjId;		//对象id，在离线贴图中代表贴图ID
	}ImRspGetAppAddr
		, ImEventGetAppAddr;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt8		retCode;
		AMChar	*	szSession;
		AMUInt32	uiSessionLen;
		AMChar	*	szCode;
		AMUInt32	uiCodeLen;
	}ImRspCheckAuthCode
		,ImEventCheckAuthCode;

	typedef struct {
		AMChar		*sendUID;			// 发送者ID
		AMInt32		sendUIDLen;			
		AMChar		*recevierUID;		// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;			// 离线贴图类型
		AMUInt64	ulObjId;			// 离线贴图ID
		AMChar		*szToken;			// token
		AMInt32		tokenLen;		
		AMChar		*szDownloadURL;		// download url
		AMInt32		downloadURLLen;
		AMChar		*szFileName;			// fileName
		AMInt32		fileNameLen;
		AMChar		*szFileExtName;		// file Ext Name
		AMInt32		fileExtNameLen;
		AMChar		*szFileMD5;			// file MD5
		AMInt32		fileMD5Len;
		AMUInt32	fileSize;			// file size
		AMUInt32	reserved;			// reserved
		AMUInt8		propertyNum;
	}FtReqPutOffObj;

	typedef struct {
		AMChar		*sendUID;			// 发送者ID
		AMInt32		sendUIDLen;			
		AMChar		*recevierUID;		// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;			// 离线贴图类型
		AMChar		*szToken;			// token
		AMInt32		tokenLen;		
		AMUInt64	ulObjId;			// 离线贴图ID
		AMChar		*szDownloadURL;		// download url
		AMInt32		downloadURLLen;
		AMChar		*szFileName;		// fileName
		AMInt32		fileNameLen;
		AMChar		*szFileExtName;		// file Ext Name
		AMInt32		fileExtNameLen;
		AMChar		*szFileMD5;			// file MD5
		AMInt32		fileMD5Len;
		AMUInt32	fileSize;			// file size
		AMUInt32	reserved;			// reserved
		AMUInt8		propertyNum;
	}FtReqGetOffObj;

	typedef struct {
		AMUInt32	retCode;			// 错误码
		AMChar		*errorMsg;			// 错误信息
		AMInt32		errorMsgLen;
		AMChar		*sendUID;			// 发送者ID
		AMInt32		sendUIDLen;			
		AMChar		*recevierUID;		// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;			// 离线贴图类型
		AMUInt64	ulObjId;			// 离线贴图ID
		AMChar		*szToken;			// token
		AMInt32		tokenLen;		
		AMChar		*szDownloadURL;		// download url
		AMInt32		downloadURLLen;
		AMChar		*szFileName;		// fileName
		AMInt32		fileNameLen;
		AMChar		*szFileExtName;		// file Ext Name
		AMInt32		fileExtNameLen;
		AMChar		*szFileMD5;			// file MD5
		AMInt32		fileMD5Len;
		AMUInt32	fileSize;			// file size
		AMUInt32	reserved;			// reserved
		AMUInt8		propertyNum;
	}FtReqDelOffObj
		, FtReqGetOffObjFin;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;		// 错误码
		AMChar		*errorMsg;		// 错误信息
		AMInt32		errorMsgLen;
		AMChar		*sendUID;		// 发送者ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// 离线贴图类型
		AMUInt64	ulObjId;		// 离线贴图ID
		AMUInt32	reserved;
		AMUInt16	totalNum;		// 发送离线贴图的总数目
		AMUInt16	leftNum;		// 还可以再发的数目
		AMUInt16	totalSize;		// 发送离线贴图的总大小
		AMUInt16	leftSize;		// 还可以再发的大小
		AMUInt8		keepDay;		// 当前贴图可保存的天数
	}FtRspPutOffObj
		, FtEventPutOffObj;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;
		AMChar		*errorMsg;		// 错误信息
		AMInt32		errorMsgLen;
		AMChar		*sendUID;		// 发送者ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// 离线贴图类型
		AMChar		*szToken;			// token
		AMInt32		tokenLen;		
		AMChar		*szDownloadURL;		// download url
		AMInt32		downloadURLLen;
	}FtRspPutOffObjFin
		, FtEventPutOffObjFin;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;
		AMChar		*errorMsg;		// 错误信息
		AMInt32		errorMsgLen;

		AMChar		*sendUID;		// 发送者ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// 离线贴图类型
		AMUInt64	ulObjId;		// 离线贴图ID
		AMUInt32	reserved;
		AMUInt16	totalNum;		// 发送离线贴图的总数目
		AMUInt16	leftNum;		// 还可以再发的数目
		AMUInt16	totalSize;		// 发送离线贴图的总大小
		AMUInt16	leftSize;		// 还可以再发的大小
		AMUInt8		keepDay;		// 当前贴图可保存的天数
	}FtRspGetOffObj;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;
		AMChar		*errorMsg;		// 错误信息
		AMInt32		errorMsgLen;

		AMChar		*sendUID;		// 发送者ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// 接受者ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// 离线贴图类型
		AMChar		*szToken;			// token
		AMInt32		tokenLen;	
		AMUInt64	ulObjId;		// 离线贴图ID
		AMUInt32	reserved;
	}FtRspDelOffObj
		, FtRspGetOffObjFin;

	typedef struct {
		AMUInt8		propertyNum;
		AMInt32		retCode;
		AMInt32		expireTime;
		AMChar	*	session;
		AMInt32		sessionLen;
	}ImRspGetWebSession,
		ImEventGetWebSession;

	typedef struct {
		AMInt32		padding;
	}ImEventPrivate;

	typedef struct _UrlParam{
		unsigned char* key;
		unsigned char* value;
	}UrlParam;

#define		TID_LENGTH			10
#define		TBS_NAME_LENGTH		64
#define		TBS_EXTSIGN_LEN		128

	typedef	struct ST_IMTribeId{
		AMChar			*	id;
		AMInt32				idLen;
		AMChar			*	name;
		AMInt32				nameLen;
		AMUInt8				level;
		AMUInt8				status;
		AMChar			*	extSign;
		AMInt32				extSignLen;
		AMUInt32			stamp;
		AMUInt8				open;
		struct ST_IMTribeId	*pNext;
	}IMTribeId;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt8		retCode;
		IMTribeId	*pImTribeIds;
		AMUInt32	tribeInfoCount;
	}ImRspShallowLoginTribe;

	typedef struct ST_IMTribeMemStatus
	{   
		AMChar		*	id;
		AMInt32			idLen;
		AMUInt8			basicStatus;	//	--基本状态 0-不在线 1-在线
		AMUInt8			predefStatus;	//	--预定义状态    
		AMUInt8			level;			//	--群成员级别 1:群主 2:管理员 3:普通成员 5:群游客
		AMChar		*	name;
		AMInt32			nameLen;		//	--群昵称
		struct ST_IMTribeMemStatus	*pNext;
	}IMTribeMemStatus;

	typedef	struct ST_IMTribeInfo
	{
		AMChar		*	id;				//	--群号
		AMInt32			idLen;
		AMChar		*	name;			//	--群名称
		AMInt32			nameLen;
		AMChar		*	masterId;		//	--群主ID
		AMInt32			masterIdLen;
		AMChar		*	category;		//	--群类别
		AMInt32			categoryLen;
		AMChar		*	describe;		//	--群简介
		AMInt32			describeLen;
		AMChar		*	bulletin;       //  --群公告
		AMInt32			bulletinLen;
		AMUInt8			check_mode;		//  --验证方式
		AMChar		*	password;		//	--密码
		AMInt32			passwordLen;
		AMChar		*	keyword;		//	--群关键字
		AMInt32			keywordLen;
		AMUInt8			allow_visitor;	//	--允许群游客
		AMUInt8			forbid_search;	//	--禁止被搜索
		AMChar		*	extSign;		//	--群状态
		AMInt32			extSignLen;
		AMUInt8			open;			//	--是否公开此群 0:不公开 1:公开
		AMUInt32		capacity;		// = 300; --最大群成员数
	}IMTribeInfo;

	typedef	struct	ST_IMTribeExtInfo
	{
		AMUInt8             level;		// = 0; --群等级
		AMUInt32			active;		// = 0; --群人气
		AMChar		*		title;		//	title = "";
		AMInt32				titleLen;
		AMChar		*		url;		// = "";
		AMInt32				urlLen;
	}IMTribeExtInfo;

	typedef struct {
		AMUInt8				propertyNum;
		AMUInt8				retCode;
		AMChar	*			tribeId;
		AMInt32				tribeIdLen;
		IMTribeInfo			info;				//	--群信息
		IMTribeMemStatus*	pMemStatus;		//	--群成员信息
		AMUInt32			memStamp;		
		IMTribeExtInfo		extInfo;			//	--扩展群信息
	}ImRspDeepLoginTribe;

	/************************************************************************/
	// 数据结构定义
	/************************************************************************/
	typedef void* IMnetHandle;
	typedef void* IMnetReference;
	/************************************************************************/
	// 功能简介: 回调函数的定义
	// 参数说明:
	//		IMnetHandle hIMnetHandle   :[IN] 该参数由IMnet模块自动填写
	//		EventContent* pEventContent:[IN] 该参数由IMnet模块自动填写,
	//										 使用者需要的内容在此联合体中.
	/************************************************************************/
	typedef IMnetRetCode (*CallbackFunc)(IMnetHandle hIMnetHandle, EventContent* pEventContent);

	/************************************************************************/
	// extern function declare.
	/************************************************************************/
	/************************************************************************/
	// 功能简介: IMnet模块创建
	// 参数说明: 
	//	    IMnetHandle* phIMnetHandle:[IN/OUT] 输入输出类型,用于请求句柄的创建
	//		void* pReference		  :[IN] 调用者RefenceID
	// 返回值  :
	//		IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetMainCreate(IMnetHandle* phIMnetHandle, IMnetReference pReference);

	/************************************************************************/
	// 功能简介: IMnet模块销毁
	// 参数说明: 
	//		IMnetHandle hIMnetHandle: [IN]待销毁的句柄
	// 返回值  : N/A
	/************************************************************************/
	void IMnetMainDestory(IMnetHandle hIMnetHandle);

	/************************************************************************/
	// 功能简介: 注册EventId上对应的Callback函数。
	// 参数说明: 
	//		EventId id				:[IN]需要注册的EventID
	//		CallbackFunc pCallback	:[IN]需要注册的callback函数
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetMainRegister(IMnetHandle hIMnetHandle, EventId id, CallbackFunc pCallback);

	/************************************************************************/
	// 功能简介: 撤销EventId上对应的Callback函数回调。
	// 参数说明: 
	//		EventId id				:[IN]需要撤销的EventID
	//		CallbackFunc pCallback	:[IN]需要撤销的callback函数
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetMainUnregister(IMnetHandle hIMnetHandle, EventId id, CallbackFunc pCallback);

	/************************************************************************/
	// 功能简介: 得到该模块的Reference
	// 参数说明:
	//		IMnetHandle hIMnetHandle:[IN]IMnet模块句柄
	//  返回值: IMnetReference : Reference ID
	/************************************************************************/
	IMnetReference IMnetGetReference(IMnetHandle hIMnetHandle);

	/************************************************************************/
	//请求接口定义
	/************************************************************************/
	/************************************************************************/
	// 功能简介: 设置IM的IP接入地址和端口号(allot地址),开启模块
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* ip		:[IN] IP地址，格式xxx.xxx.xxx.xxx
	//		AMUInt16 port	:[IN] 端口号
	// 返回值  : 
	/************************************************************************/
	IMnetRetCode IMnetConnectOpen(IMnetHandle hIMnetHandle, AMChar* ip, AMUInt16 port, AMInt32 sync);

#if IM_NET_SHUT_SOCKET
	IMnetRetCode IMnetConnectShut(IMnetHandle hIMnetHandle);
#endif
	/************************************************************************/
	// 功能简介: 设置IM的IP接入地址和端口号(allot地址),关闭模块
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	// 返回值  : 
	/************************************************************************/
	IMnetRetCode IMnetConnectClose(IMnetHandle hIMnetHandle);

	/************************************************************************/
	// 功能简介: 登录
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* name			  :[IN] 用户ID(带有前缀的)
	//		AMChar* password		  :[IN] 明文密码
	//		AMInt32 contactStamp	  :[IN] 用户时间戳
	//		AMInt32 groupStamp		  :[IN] 组时间戳
	//		AMInt32 blackListStamp	  :[IN] 黑名单时间戳
	//		AMInt32 revBlackListStamp :[IN] 反向黑名单时间戳
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/		
	IMnetRetCode IMnetLogin(IMnetHandle hIMnetHandle, 
		AMChar* name, AMChar* password, AMInt32 bIsToken,
		AMInt32 contactStamp, AMInt32 groupStamp, 
		AMInt32 blackListStamp, AMInt32 revBlackListStamp);

	/************************************************************************/
	// 功能简介: 重新登录
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* name		:[IN] 用户ID(带有前缀的)
	//		AMChar* password	:[IN] 明文密码??Token??
	//		AMInt8 basicStatus	:[IN] 
	//		AMInt8 predefStatus	:[IN]		
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetReLogin(IMnetHandle hIMnetHandle, AMChar* name, AMChar* password, 
		AMInt8 basicStatus, AMInt8 predefStatus);

	/************************************************************************/
	// 功能简介: 登出
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetLogoff(IMnetHandle hIMnetHandle);

	IMnetRetCode IMnetLogin2(IMnetHandle hIMnetHandle, const AMChar *szRemark);

	/************************************************************************/
	// 功能简介: 登录后处理
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMInt8 basicStatus	:[IN]
	//		AMInt8 predefStatus	:[IN]
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetPostLogin(IMnetHandle hIMnetHandle, AMInt8 basicStatus, AMInt8 predefStatus);

	/************************************************************************/
	// 功能简介: 发送消息
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* contactID	:[IN] 目标用户ID
	//		AMChar* message		:[IN] 消息内容
	//		AMInt32 length		:[IN] 消息内容长度
	//		AMInt32 type		:[IN] 0存数据库, 1不存数据库
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetSendMessage(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* message, 
		AMInt32 length, AMInt32 type);


	IMnetRetCode IMnetSendMessageEx(IMnetHandle hIMnetHandle, 
		AMChar* contactID, AMInt32 contactIDLen,
		AMChar* message, AMInt32 length, AMInt32 type, 
		AMInt32 secondCmd, AMInt32 ackSeq);
	/*
	 *	发送文件通知消息。message为XML的二级协议。由外部保证。
	 */
	IMnetRetCode IMnetSendFileMessage(IMnetHandle hIMnetHandle, AMChar* contactID, 
		AMChar* message, AMInt32 length, AMInt32 type);
	/************************************************************************/
	// 功能简介: 往黑名单中添加用户
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* contactID	:[IN]要添加到黑名单中的用户ID
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetAddBlack(IMnetHandle hIMnetHandle, AMChar* contactID);

	/************************************************************************/
	// 功能简介: 添加好友
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* contactID	:[IN] 目标用户ID
	//		AMInt32 groupIDHigh	:[IN] 组的id高32位
	//		AMInt32 groupIDLow	:[IN] 组的id低32位
	//		AMInt32 type		:[IN] 
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMInt32 groupIDHigh, 
		AMInt32 groupIDLow, AMInt32 type, const AMChar *szMsg);

	/************************************************************************/
	// 功能简介: 修改签名
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* signature: [IN]新的签名
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetChangeSignature(IMnetHandle hIMnetHandle, AMChar* signature);

	/************************************************************************/
	// 功能简介: 修改状态
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMInt8 basicstatus	: [IN]
	//		AMInt8 predefstatus	: [IN]
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetChangeStatus(IMnetHandle hIMnetHandle, AMInt8 basicstatus, AMInt8 predefstatus);

	/************************************************************************/
	// 功能简介: 修改验证类型
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMInt8 type			: [IN] 0表示不需要验证, 1表示需要验证
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetChangeVerifyType(IMnetHandle hIMnetHandle, AMInt8 type);

	/************************************************************************/
	// 功能简介: 从黑名单中删除用户
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		ContactList* pContactList: [IN]待删除的用户列表
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetDeleteBlack(IMnetHandle hIMnetHandle, AMChar* contactID);

	/************************************************************************/
	// 功能简介: 删除好友
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		ContactList* pContactList: [IN]待删除的好友列表
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetDeleteContact(IMnetHandle hIMnetHandle, ContactList* pContactList);

	/************************************************************************/
	// 功能简介: 删除离线消息
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMInt32 lastTime :[IN] 上一次离线消息时间
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetDeleteOfflineMsg(IMnetHandle hIMnetHandle, AMInt32 lastTime);

	/************************************************************************/
	// 功能简介: 订阅用户状态信息和取消订阅用户状态信息
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		ContactList* pContactList: [IN]用户列表
	//		AMInt8 type				 : [IN] 1表示订阅, 0表示取消订阅
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetSubscribeContactInfo(IMnetHandle hIMnetHandle, ContactList* pContactList, AMInt8 type);

	/************************************************************************/
	// 功能简介: 添加一个组
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* groupName		:[IN] 添加的组名
	//		AMInt32 parentGroupIDHigh :[IN] 添加的组的父亲的组ID 高32位
	//		AMInt32 parentGroupIDLow :[IN] 添加的组的父亲的组ID 低32位
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetAddGroup(IMnetHandle hIMnetHandle, AMChar* groupName, AMInt32 parentGroupIDHigh, AMInt32 parentGroupIDLow);

	/************************************************************************/
	// 功能简介: 
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		ContactList* pContactList: [IN]用户列表
	//		AMInt8 type				 : [IN] 1表示订阅, 0表示取消订阅
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetDeleteGroup(IMnetHandle hIMnetHandle, AMInt32 groupIDHigh, AMInt32 groupIDLow);
	
	/************************************************************************/
	// 功能简介: 
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMInt32 groupIDHigh		:[IN] 组id高32位
	//		AMInt32 groupIDLow		:[IN] 组id低32位
	//		AMChar* groupName		:[IN] 修改后的组名
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetRenameGroup(IMnetHandle hIMnetHandle, AMInt32 groupIDHigh, AMInt32 groupIDLow, AMChar* groupName);

	/************************************************************************/
	// 功能简介: 
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* contactID		:[IN] 目标用户
	//		AMChar* displayName		:[IN] 显示名
	//		AMChar* verifyInfo		:[IN] 验证信息
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetSendVerifyInfo(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* displayName, AMChar* verifyInfo);

	/************************************************************************/
	// 功能简介: 
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* contactID		:[IN] 目标用户
	//		AMChar* rejectReason	:[IN] 拒绝原因
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetRejectAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* rejectReason);

	/************************************************************************/
	// 功能简介: 
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	//		AMChar* contactID		:[IN] 目标用户
	//		AMInt32 groupIDHigh		:[IN] 用户组ID高32位
	//		AMInt32 groupIDLow		:[IN] 用户组ID低32位
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetAcceptAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMInt32 groupIDHigh, AMInt32 groupIDLow);

	//************************************
	// Method:    IMnetGetPeerInfo			获取好友的消息，异步返回RspGetPeerInfo。（好友不在线、不存在则没有返回）
	// Author:    yanlong.shiyl
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szContactID
	//************************************
	IMnetRetCode IMnetGetPeerInfo(IMnetHandle hIMnetHandle, const AMChar *szContactID);

	//************************************
	// Method:    IMnetGetPeerVerifyConfig	获取好友的添加好友配置，异步返回RspGetPeerVerifyConfig
	// Author:    yanlong.shiyl
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szContactID
	//************************************
	IMnetRetCode IMnetGetPeerVerifyConfig(IMnetHandle hIMnetHandle, const AMChar *szContactID, AMInt32 iClientId);

	IMnetRetCode IMnetGetUserUDBProfile(IMnetHandle hIMnetHandle, const AMChar *szContactID);

	IMnetRetCode IMnetSearchUser(IMnetHandle hIMnetHandle, const AMChar *szKeyWord);

	//************************************
	// Method:    IMnetGetSignature				获取好友签名，异步返回NtfUpdateUsrExtInfo
	// Author:    yanlong.shiyl
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szToken		登录的帐号Token
	// Parameter: AMUChar	ucTest				1表示测试环境
	// Parameter: const AMChar * szContactIDs	一个或多个联系人ID组成的字符串（以'\1'分割）
	// Parameter: AMInt32 iCount				联系人ID的个数（不超过20）
	//************************************
	IMnetRetCode IMnetGetSignature(IMnetHandle hIMnetHandle, const AMChar *szToken, AMUChar ucTest,
									const AMChar * szContactIDs, AMInt32 iCount);

	IMnetRetCode IMnetSendMsg2Callback(IMnetHandle hIMnetHandle, EventId id, AMVoid *pMsg, AMUInt32 uiSize, FreeContent freer);
	IMnetRetCode IMnetSendMsg2CallbackProc(IMnetHandle hIMnetHandle, EventId id, AMVoid *pMsg, AMUInt32 uiSize, FreeContent freer, AMBool bLow);
	//************************************
	// Method:    IMnetGetDegree	:获取好友的活跃度，异步返回ImRspGetDegree
	// Author:    yanlong.shiyl 
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: AMChar * contactID
	//************************************
	IMnetRetCode IMnetGetDegree(IMnetHandle hIMnetHandle, AMChar *contactID);

	IMnetRetCode IMnetGetAppAddr(IMnetHandle hIMnetHandle, const AMChar *szSessionId, AMUInt64 ulObjId);

	//************************************
	// Method:    IMnetGetContactMemo		获取我对好友contactId的备注，异步返回RspGetContactMemo
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: AMChar * contactID
	//************************************
	IMnetRetCode IMnetGetContactMemo(IMnetHandle hIMnetHandle, AMChar *contactID);

	IMnetRetCode IMnetChangeSrvMode(IMnetHandle hIMnetHandle, AMUChar ucStatus);

	IMnetRetCode IMnetGetWebSession(IMnetHandle hIMnetHandle);

	/*
	 *	向server发送验证码
	 */
	IMnetRetCode IMnetCheckAuthCode(IMnetHandle hIMnetHandle, const AMChar *szSession, const AMChar *szCode);

	/*
	 *	向server发送原始打包数据。（NtfNeedAuthCheck中带来的数据）
	 */
	IMnetRetCode IMnetSendRawPacket(IMnetHandle hIMnetHandle, const AMChar *szPacket, AMUInt32 uiLen);

	//************************************
	// Method:    IMnetShallowLoginTribe	浅登录Tribe， 异步返回RspShallowLoginTribe
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	//************************************
	IMnetRetCode IMnetShallowLoginTribe(IMnetHandle hIMnetHandle);

	//************************************
	// Method:    IMnetDeepLoginTribe		深登录Tribe, 异步返回RspDeepLoginTribe
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szTribeId
	//************************************
	IMnetRetCode IMnetDeepLoginTribe(IMnetHandle hIMnetHandle, const AMChar *szTribeId);

	// reqGetOffObj, rspGetOffObj
	IMnetRetCode IMnetPackGetOffObj(const FtReqGetOffObj *pGetOffObj, AMChar **pszBuff, AMInt32 *piBuffLen);
	void FreeFtRspGetOffObj(FtRspGetOffObj* ppGetOffObj);
	IMnetRetCode IMnetUnpackGetOffObj(FtRspGetOffObj **pGetOffObj,AMChar *pszBuff, AMInt32 piBuffLen);

	// // reqGetOffObjFin, rspGetOffObjFin
	IMnetRetCode IMnetPackGetOffObjFin(const FtReqGetOffObjFin *pGetOffObj, AMChar **pszBuff, AMInt32 *piBuffLen);
	void FreeFtRspGetOffObjFin(FtRspGetOffObjFin* pGetOffObjFin);
	IMnetRetCode IMnetUnpackGetOffObjFin(FtRspGetOffObjFin **ppGetOffObjFin, AMChar *pszBuff, AMInt32 piBuffLen);

	IMnetRetCode IMnetPackPutOffObj(const FtReqPutOffObj *pPutOffObj, AMChar **pszBuff, AMInt32 *piBuffLen);
	void FreeFtRspPutOffObj(FtRspPutOffObj* pRspPutOffObj);
	IMnetRetCode IMnetUnpackPutOffObj(FtRspPutOffObj **ppGetOffObj, AMChar *pszBuff, AMInt32 piBuffLen);
	
	void FreeFtRspPutOffObjFin(FtRspPutOffObjFin* pRspPutOffObjFin);
	IMnetRetCode IMnetUnpackPutOffObjFin(FtRspPutOffObjFin** ppRspPutOffObjFin, AMUInt8* pBuffer, AMInt32 Length);

	void IMnetPackRelease(AMUInt8* pBuffer);

	IMnetRetCode IMnetGetWebBinding(IMnetHandle hIMnetHandle);

	IMnetRetCode IMnetPutBindInfo(IMnetHandle hIMnetHandle, const AMChar *szBindID, const AMInt32 len);



#ifdef __cplusplus
}
#endif

#endif

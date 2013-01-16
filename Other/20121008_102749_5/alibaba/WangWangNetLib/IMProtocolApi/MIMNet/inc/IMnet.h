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

//��ʽʹ�õı��

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
	//ww_alios�汾��
	//#define	IM_PROTOCOL_VERSION			"1.00.01_ww_alios_na_w700"
	//���İ汾��
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
		* ������ retCode
		* 0x01���ݰ汾���ܵ�¼��������������³���
		* 0x02:�����ݰ汾�����ܵ�¼����ʾ�û�ȷ���Լ��ĳ���汾
		* 0xff:δ֪�汾�����ܵ�¼����ʾ�û�ȷ���Լ��ĳ���汾

		#define CHECK_VERSION_SUCESS			0
		#define CHECK_VERSION_COMPATIBLE		1
		#define CHECK_VERSION_NONCOMPATIBLE		2
		#define CHECK_VERSION_UNKNOWN			0xFF
		*/
		AMInt32		retCode;
	}ImEventCheckVersion;

	typedef struct {
		AMChar*		bindID;		  //���ʺŵ�id, Ϊ�ձ�ʾ���ʺ�
		AMInt32     bindIDLen;
		AMInt32		retCode;		// ������
		AMInt32		timestampFlag;	// ʱ�����־
		AMInt32		clientIp;		// �ͻ���IP
		AMInt32		lastClientip;	// �ϴε�½�Ŀͻ���IP
		AMInt32		serverTime;		// ������ʱ�� GMT
		AMChar*	    workKey;        // ������Կ
		AMInt32     workKeyLen;
		AMChar*	    pwtoken;	    // auto logon use it
		AMInt32     pwtokenLen;
		AMChar*	    webmd5pw;       // ��վmd5����
		AMInt32     webmd5pwLen;
		AMChar*	    bindid;         // �󶨵�IMID
		AMInt32     bindidLen;
		AMChar*		rid;
		AMInt32     ridLen;
		AMChar*		remark;          // ��ע��Ϣ
		AMInt32     remarkLen;     
		AMUInt8		propertyNum;
	}ImRspLogin,
	 ImEventLoginStatus;

	typedef struct {
		AMUInt8		propertyNum;
		AMInt32		retCode;
		AMInt32		timestampFlag;                  // ʱ�����־
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
		AMChar*			bindID;		  //���ʺŵ�id, Ϊ�ձ�ʾ���ʺ�
		AMInt32         bindIDLen;
		AMInt32			retCode;
		UserGroupList*	groupList;  //group��ָ��
		AMInt32			groupCount; //������¼Group�ĸ���
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
		AMChar*						bindID;		  //���ʺŵ�id, Ϊ�ձ�ʾ���ʺ�
		AMInt32                     bindIDLen;
		AMInt32				        retCode;
		UserContactList*	        contactList;  //contact��ָ��
		AMInt32				        contactCount; //������¼contact�ĸ���
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
		AMChar*				bindID;		  //���ʺŵ�id, Ϊ�ձ�ʾ���ʺ�
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
		AMInt32     retCode;    //0���ɹ�������ֵ��ʧ��
		AMInt32		groupIDHigh;
		AMInt32		groupIDLow;
		AMInt32     timestamp;
		AMChar*		contactID;
		AMInt32     contactIDLen;
		AMInt8      opcode;     //0 - ͬ��,1 - �ܾ���ͬʱ���;ܾ���Ϣ�����󷽣��ɿͻ���ʹ�ö���Э�鴫����Ϣ֪ͨ�Է�
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
		ContactStatusList*  contactStatusList;  // ��ϵ��״̬�б�
		AMInt32             contactStatusCount; // ״̬�б���Ԫ�ظ���
		AMUInt8		        propertyNum;
	}ImRspGetContactStatus,
	ImEventGetContactStatus,
	ImRspSubscribeInfo,
	ImEventSubscribeInfo;

	typedef struct {
		AMChar*		bindID;
		AMInt32     bindIDLen;
		AMUInt32	retCode;		// ������
		AMUInt32	needNextlevel;	// ����һ������Ҫ�Ļ�Ծ����
		AMUInt32	activity;		// ��Ծ��
		AMInt8		addcontactFlag; // ���Ϊ��ϵ��У���־
		AMInt8		sendmsgFlag;	// ������ϢУ���־
		AMInt8		actLevel;		// ��Ծ�ȵȼ�
		AMInt8		imlevel;		// IM level,
		AMInt8		mulsendflag;	// �Ƿ�����Ⱥ��;
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
		AMInt32     retCode;    // 0x00:�ɹ�������ֵ��ʧ��
		AMInt32     connectNo;  // ���Ӻ�
		AMChar*     remark;     // ������Ϣ
		AMInt32     remarkLen;
		AMUInt8		propertyNum;
	}ImRspReLogin,
	ImEventReLogin;

	typedef struct {
		AMInt32     retCode;        // 0���ɹ�������ֵ��ʧ��
		AMInt8      addcontactFlag; // 0������Ҫ��֤��1����Ҫ��֤
		AMInt8      sendmsgFlag;    // 0�������ͣ�1����������
		AMInt8      enableSearch;   // 0��������������1������������
		AMUInt8		propertyNum;
	}ImRspChangeUserVerify,
	ImEventChanageUserVerify;

	//�����ϵ����ش�������
	typedef enum
	{
		eIMADDCONTACTRESULT_SUCCESS = 0,			//"��ӳɹ�";
		eIMADDCONTACTRESULT_ADDED,					//"����ϵ���Ѿ�����ĺ��ѣ������ٴ����";
		eIMADDCONTACTRESULT_NOID,					//"��ϵ��ID������";
		eIMADDCONTACTRESULT_FULL,					//"������ϵ���Ѿ��ﵽ���������������������µ���ϵ���ˡ�";
		eIMADDCONTACTRESULT_FULLTODAY,				//"���������ϵ����Ŀ����";
		eIMADDCONTACTRESULT_NEEDAUTH,				//"�Է���Ҫ��֤";
		eIMADDCONTACTRESULT_NORIGHT,				//"�����ʺ�δ������������ϵ�ˣ����ȼ��";
		eIMADDCONTACTRESULT_NOTACTIVEID,			//"�Է�δ����";
		eIMADDCONTACTRESULT_WAITAUTH,				//"�ȴ���֤";
		eIMADDCONTACTRESULT_DENYALL,				//"�ܾ����κ������";
		eIMADDCONTACTRESULT_HIGHFRENQ,				//"����̫Ƶ��,���Ժ�����";
		eIMADDCONTACTRESULT_ESERVICETEAMMATE = 0xc,	//"E�ͷ����";
		eIMADDCONTACTRESULT_OTHERERROR				//"��������";
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
		AddContactRetCode		retCode; // 0:�ɹ�, -1:ʧ��, 1:��Ҫ��֤, 2:�ȴ���֤
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
		AMInt32     retCode; // 0:�ɹ�, -1:ʧ��, 1:��Ҫ��֤, 2:�ȴ���֤
		ContactInfo contactInfo;
		AMInt32		bContactInfoUsed;
		AMInt8      type;
		AMUInt8		propertyNum;
	}ImRspAddContact;

	typedef struct {
		AMInt32     retCode; // 0���ɹ�������ֵ��ʧ��
		AMInt32     timestamp;
		AMChar*     blackId; // ������ID
		AMInt32     blackIdLen;
		AMUInt8		propertyNum;
	}ImRspAddBlack,
	ImEventAddBlack;

	typedef struct {
		AMInt32     retCode; // 0���ɹ�������ֵ��ʧ��
		AMChar*     blackId; // ������ID
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
		AMInt32	online; //1:������Ϣ��0:������Ϣ
		AMInt32	iType;	//0:�ı���Ϣ��1:ͼƬ��Ϣ��ͼƬ��Ϣ��������xml
		AMChar* fromId;
		AMInt32 fromIdLen;
		AMChar* msgContent;
		AMInt32 msgContentLen;
		AMInt32 sendTime;
		AMInt32	iServerType;	//0x01��ʾ����ͻ��˹���
	}TextMsg;

	typedef struct ST_ImEventChatMessage{
		TextMsg								msg;
		AMInt32								ackSeq;
		struct ST_ImEventChatMessage*		next;
	}ImEventChatMessage;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventBuzzMessage;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
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
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventMessageAck;

	typedef struct {
		AMInt32			sendtime; //1:������Ϣ��0:������Ϣ
		AMChar*			fromID;
		AMInt32			fromIDLen;
	}ImEventToDeleteOfflineMsg;

	typedef struct {
		AMChar*			bindID;
		AMInt32			bindIDLen;
		AMInt32			online; //1:������Ϣ��0:������Ϣ
		AMChar*			fromID;
		AMInt32			fromIDLen;
	}ImEventContactAdded;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventContactIgnoreAdded;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventContactIgnoreDeled;

	typedef struct {
		AMChar*			bindID;
		AMInt32			bindIDLen;
		AMInt32			online; //1:������Ϣ��0:������Ϣ
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
		AMInt32			online; //1:������Ϣ��0:������Ϣ
		AMChar*			fromID;
		AMInt32			fromIDLen;
		AMChar*			msg;
		AMInt32			msgLen;
	}ImEventContactAskAddNo;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
		AMChar*			fromID;
		AMInt32			fromIDLen;
		AMInt32			groupIDHigh;
		AMInt32			groupIDLow;
	}ImEventContactAskAddYes;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventWritingMessage;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventGroupBroadcast;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventPluginsQuery;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventPluginsRsp;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventPluginsInvite;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventCustomMessage;

	typedef struct {
		AMInt32			online; //1:������Ϣ��0:������Ϣ
	}ImEventFocusTalk;

	typedef struct {
		AMInt32     retCode;        // 0���ɹ�������ֵ��ʧ��
		AMChar*     signature;      // ǩ������
		AMInt32     signatureLen;   // ǩ������
		AMUInt8		propertyNum;
	}ImRspChangeSignature,
	ImEventChangeSignature;	

	typedef struct ST_Contact_ExtraInfo {
		AMChar*				   userID;		//��ϵ�˳�ID
		AMInt32                userIDLen;
		AMInt32                result;		//�˺���Ϣ��ȡ�����0:����
		AMChar*				   phone;		//���ֻ��˺�
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
		AMChar*				   str;			//��ϵ�˳�ID
		AMInt32                strLen;
		struct ST_String_List* pNext;
	}String_List;

	typedef struct ST_Timestamp_Info {
		AMChar*				   userID;			//��ϵ�˳�ID
		AMInt32                userIDLen;
		AMInt32                timestampFlag;	//ʱ�����־
		AMInt32				   timestampList[4];//ʱ���
		AMInt8		           propertyNum;
		struct ST_Timestamp_Info* pNext;
	}Timestamp_Info;


	typedef struct ST_Bind_Service {
		AMChar*				   serviceID;		
		AMInt32                serviceIDLen;
		AMChar*				   siteID;			//��վ��ʶ
		AMInt32                siteIDLen;
		AMChar*				   webID;			//��վID
		AMInt32                webIDLen;
		AMChar*				   webUid;			//��վ�û�ID
		AMInt32                webUidLen;
		String_List*		   webUrl;
		AMInt32				   webUrlCount;
		AMInt8		           propertyNum;
		struct ST_Bind_Service* pNext;
	}Bind_Service;

	typedef struct {
		AMInt32			retcode;
		AMChar*			aliUID;			//ͳһID
		AMInt32			aliUIDLen;
		AMChar*			aliUIDToken;	//ͳһID token �������
		AMInt32			aliUIDTokenLen;
		Bind_Service*	bindList;
		AMInt32			bindListCount;
		String_List*	loginIDList;
		AMInt32			loginIDListCount;
		AMUInt8					propertyNum;
	}ImRspGetWebBinding,
		ImEventGetWebBinding;

	/*	
	IMPREDEFSTATUS_OFFLINE	    = 0,    // ����
	IMPREDEFSTATUS_FREE	        = 1,    // ����
	IMPREDEFSTATUS_BUSY	        = 2,    //æµ��
	IMPREDEFSTATUS_AWAY	        = 3,    //���ڵ�����
	IMPREDEFSTATUS_INCALL	    = 4,    //�����绰��
	IMPREDEFSTATUS_OUTFORDINNER	= 5,    //����Ͳ�
	IMPREDEFSTATUS_WAIT	        = 6,    //�Ժ�
	IMPREDEFSTATUS_INVISIBLE	= 7,    // ����
	IMPREDEFSTATUS_OFFLINELOGON	= 8,    //���ߵ�½
	IMPREDEFSTATUS_UNKNOW	    = 9,    //δ֪
	IMPREDEFSTATUS_FAKEONLINE	= 10,   //�����ߣ�E�ͷ�ʹ��
	IMPREDEFSTATUS_NUM	        = 11,   //�ݲ�����
	IMPREDEFSTATUS_MOBILEONLINE	= 12    //�ֻ�����
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
		StatusList*	    statusList;  //status��ָ��
		AMInt32			statusCount; //������¼status�ĸ���
		AMUInt8			propertyNum;
	}ImNtfStatus,
	ImEventNtfStatus;

	typedef struct {
		AMChar*     style;      // ����ģʽ
		AMInt32     styleLen;
		AMChar*     message;    // HTML��ʽ
		AMInt32     messageLen;
		AMInt16     cmdId;      // ������
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
		AMChar*     message;        // ������Ϣ���罻�����ѵ�
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
		AMUInt8		sendmsgFlag;	//�Ƿ�������Ϣ
		AMUInt8		reverseContact; //��ûʲô��
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
		SearchUserInfoList*	        userList;  //user��ָ��
		AMInt32				        userCount; //������¼user�ĸ���
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
		����Ӧ�û���һ��FT_VECTOR��UnpackImRspGetDegree����û�н���
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
		*���ﻹ��һ��Vector<SRcChileId>
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
		AMUInt32	retCode;		//������
		AMChar	*	szServerIp;		//�ļ����ͷ�������ַ
		AMInt32		iServerIpLen;
		AMUInt16	uiServerPort;	//�˿ں�
		AMChar	*	szSessionId;	//SESSION��
		AMInt32		iSessionIdLen;
		AMUInt16	uiAppType;		//uiAppType=1 ����ָ��FTSӦ��
		AMUInt16	uiSubType;		//uiSubType=3 ����ָ��������ͼ����
		AMUInt64	ulObjId;		//����id����������ͼ�д�����ͼID
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
		AMChar		*sendUID;			// ������ID
		AMInt32		sendUIDLen;			
		AMChar		*recevierUID;		// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;			// ������ͼ����
		AMUInt64	ulObjId;			// ������ͼID
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
		AMChar		*sendUID;			// ������ID
		AMInt32		sendUIDLen;			
		AMChar		*recevierUID;		// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;			// ������ͼ����
		AMChar		*szToken;			// token
		AMInt32		tokenLen;		
		AMUInt64	ulObjId;			// ������ͼID
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
		AMUInt32	retCode;			// ������
		AMChar		*errorMsg;			// ������Ϣ
		AMInt32		errorMsgLen;
		AMChar		*sendUID;			// ������ID
		AMInt32		sendUIDLen;			
		AMChar		*recevierUID;		// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;			// ������ͼ����
		AMUInt64	ulObjId;			// ������ͼID
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
		AMUInt32	retCode;		// ������
		AMChar		*errorMsg;		// ������Ϣ
		AMInt32		errorMsgLen;
		AMChar		*sendUID;		// ������ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// ������ͼ����
		AMUInt64	ulObjId;		// ������ͼID
		AMUInt32	reserved;
		AMUInt16	totalNum;		// ����������ͼ������Ŀ
		AMUInt16	leftNum;		// �������ٷ�����Ŀ
		AMUInt16	totalSize;		// ����������ͼ���ܴ�С
		AMUInt16	leftSize;		// �������ٷ��Ĵ�С
		AMUInt8		keepDay;		// ��ǰ��ͼ�ɱ��������
	}FtRspPutOffObj
		, FtEventPutOffObj;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;
		AMChar		*errorMsg;		// ������Ϣ
		AMInt32		errorMsgLen;
		AMChar		*sendUID;		// ������ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// ������ͼ����
		AMChar		*szToken;			// token
		AMInt32		tokenLen;		
		AMChar		*szDownloadURL;		// download url
		AMInt32		downloadURLLen;
	}FtRspPutOffObjFin
		, FtEventPutOffObjFin;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;
		AMChar		*errorMsg;		// ������Ϣ
		AMInt32		errorMsgLen;

		AMChar		*sendUID;		// ������ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// ������ͼ����
		AMUInt64	ulObjId;		// ������ͼID
		AMUInt32	reserved;
		AMUInt16	totalNum;		// ����������ͼ������Ŀ
		AMUInt16	leftNum;		// �������ٷ�����Ŀ
		AMUInt16	totalSize;		// ����������ͼ���ܴ�С
		AMUInt16	leftSize;		// �������ٷ��Ĵ�С
		AMUInt8		keepDay;		// ��ǰ��ͼ�ɱ��������
	}FtRspGetOffObj;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt32	retCode;
		AMChar		*errorMsg;		// ������Ϣ
		AMInt32		errorMsgLen;

		AMChar		*sendUID;		// ������ID
		AMInt32		sendUIDLen;
		AMChar		*recevierUID;	// ������ID
		AMInt32		recevierUIDLen;
		AMUInt16	uiSubType;		// ������ͼ����
		AMChar		*szToken;			// token
		AMInt32		tokenLen;	
		AMUInt64	ulObjId;		// ������ͼID
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
		AMUInt8			basicStatus;	//	--����״̬ 0-������ 1-����
		AMUInt8			predefStatus;	//	--Ԥ����״̬    
		AMUInt8			level;			//	--Ⱥ��Ա���� 1:Ⱥ�� 2:����Ա 3:��ͨ��Ա 5:Ⱥ�ο�
		AMChar		*	name;
		AMInt32			nameLen;		//	--Ⱥ�ǳ�
		struct ST_IMTribeMemStatus	*pNext;
	}IMTribeMemStatus;

	typedef	struct ST_IMTribeInfo
	{
		AMChar		*	id;				//	--Ⱥ��
		AMInt32			idLen;
		AMChar		*	name;			//	--Ⱥ����
		AMInt32			nameLen;
		AMChar		*	masterId;		//	--Ⱥ��ID
		AMInt32			masterIdLen;
		AMChar		*	category;		//	--Ⱥ���
		AMInt32			categoryLen;
		AMChar		*	describe;		//	--Ⱥ���
		AMInt32			describeLen;
		AMChar		*	bulletin;       //  --Ⱥ����
		AMInt32			bulletinLen;
		AMUInt8			check_mode;		//  --��֤��ʽ
		AMChar		*	password;		//	--����
		AMInt32			passwordLen;
		AMChar		*	keyword;		//	--Ⱥ�ؼ���
		AMInt32			keywordLen;
		AMUInt8			allow_visitor;	//	--����Ⱥ�ο�
		AMUInt8			forbid_search;	//	--��ֹ������
		AMChar		*	extSign;		//	--Ⱥ״̬
		AMInt32			extSignLen;
		AMUInt8			open;			//	--�Ƿ񹫿���Ⱥ 0:������ 1:����
		AMUInt32		capacity;		// = 300; --���Ⱥ��Ա��
	}IMTribeInfo;

	typedef	struct	ST_IMTribeExtInfo
	{
		AMUInt8             level;		// = 0; --Ⱥ�ȼ�
		AMUInt32			active;		// = 0; --Ⱥ����
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
		IMTribeInfo			info;				//	--Ⱥ��Ϣ
		IMTribeMemStatus*	pMemStatus;		//	--Ⱥ��Ա��Ϣ
		AMUInt32			memStamp;		
		IMTribeExtInfo		extInfo;			//	--��չȺ��Ϣ
	}ImRspDeepLoginTribe;

	/************************************************************************/
	// ���ݽṹ����
	/************************************************************************/
	typedef void* IMnetHandle;
	typedef void* IMnetReference;
	/************************************************************************/
	// ���ܼ��: �ص������Ķ���
	// ����˵��:
	//		IMnetHandle hIMnetHandle   :[IN] �ò�����IMnetģ���Զ���д
	//		EventContent* pEventContent:[IN] �ò�����IMnetģ���Զ���д,
	//										 ʹ������Ҫ�������ڴ���������.
	/************************************************************************/
	typedef IMnetRetCode (*CallbackFunc)(IMnetHandle hIMnetHandle, EventContent* pEventContent);

	/************************************************************************/
	// extern function declare.
	/************************************************************************/
	/************************************************************************/
	// ���ܼ��: IMnetģ�鴴��
	// ����˵��: 
	//	    IMnetHandle* phIMnetHandle:[IN/OUT] �����������,�����������Ĵ���
	//		void* pReference		  :[IN] ������RefenceID
	// ����ֵ  :
	//		IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetMainCreate(IMnetHandle* phIMnetHandle, IMnetReference pReference);

	/************************************************************************/
	// ���ܼ��: IMnetģ������
	// ����˵��: 
	//		IMnetHandle hIMnetHandle: [IN]�����ٵľ��
	// ����ֵ  : N/A
	/************************************************************************/
	void IMnetMainDestory(IMnetHandle hIMnetHandle);

	/************************************************************************/
	// ���ܼ��: ע��EventId�϶�Ӧ��Callback������
	// ����˵��: 
	//		EventId id				:[IN]��Ҫע���EventID
	//		CallbackFunc pCallback	:[IN]��Ҫע���callback����
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetMainRegister(IMnetHandle hIMnetHandle, EventId id, CallbackFunc pCallback);

	/************************************************************************/
	// ���ܼ��: ����EventId�϶�Ӧ��Callback�����ص���
	// ����˵��: 
	//		EventId id				:[IN]��Ҫ������EventID
	//		CallbackFunc pCallback	:[IN]��Ҫ������callback����
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetMainUnregister(IMnetHandle hIMnetHandle, EventId id, CallbackFunc pCallback);

	/************************************************************************/
	// ���ܼ��: �õ���ģ���Reference
	// ����˵��:
	//		IMnetHandle hIMnetHandle:[IN]IMnetģ����
	//  ����ֵ: IMnetReference : Reference ID
	/************************************************************************/
	IMnetReference IMnetGetReference(IMnetHandle hIMnetHandle);

	/************************************************************************/
	//����ӿڶ���
	/************************************************************************/
	/************************************************************************/
	// ���ܼ��: ����IM��IP�����ַ�Ͷ˿ں�(allot��ַ),����ģ��
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* ip		:[IN] IP��ַ����ʽxxx.xxx.xxx.xxx
	//		AMUInt16 port	:[IN] �˿ں�
	// ����ֵ  : 
	/************************************************************************/
	IMnetRetCode IMnetConnectOpen(IMnetHandle hIMnetHandle, AMChar* ip, AMUInt16 port, AMInt32 sync);

#if IM_NET_SHUT_SOCKET
	IMnetRetCode IMnetConnectShut(IMnetHandle hIMnetHandle);
#endif
	/************************************************************************/
	// ���ܼ��: ����IM��IP�����ַ�Ͷ˿ں�(allot��ַ),�ر�ģ��
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	// ����ֵ  : 
	/************************************************************************/
	IMnetRetCode IMnetConnectClose(IMnetHandle hIMnetHandle);

	/************************************************************************/
	// ���ܼ��: ��¼
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* name			  :[IN] �û�ID(����ǰ׺��)
	//		AMChar* password		  :[IN] ��������
	//		AMInt32 contactStamp	  :[IN] �û�ʱ���
	//		AMInt32 groupStamp		  :[IN] ��ʱ���
	//		AMInt32 blackListStamp	  :[IN] ������ʱ���
	//		AMInt32 revBlackListStamp :[IN] ���������ʱ���
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/		
	IMnetRetCode IMnetLogin(IMnetHandle hIMnetHandle, 
		AMChar* name, AMChar* password, AMInt32 bIsToken,
		AMInt32 contactStamp, AMInt32 groupStamp, 
		AMInt32 blackListStamp, AMInt32 revBlackListStamp);

	/************************************************************************/
	// ���ܼ��: ���µ�¼
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* name		:[IN] �û�ID(����ǰ׺��)
	//		AMChar* password	:[IN] ��������??Token??
	//		AMInt8 basicStatus	:[IN] 
	//		AMInt8 predefStatus	:[IN]		
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetReLogin(IMnetHandle hIMnetHandle, AMChar* name, AMChar* password, 
		AMInt8 basicStatus, AMInt8 predefStatus);

	/************************************************************************/
	// ���ܼ��: �ǳ�
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetLogoff(IMnetHandle hIMnetHandle);

	IMnetRetCode IMnetLogin2(IMnetHandle hIMnetHandle, const AMChar *szRemark);

	/************************************************************************/
	// ���ܼ��: ��¼����
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMInt8 basicStatus	:[IN]
	//		AMInt8 predefStatus	:[IN]
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetPostLogin(IMnetHandle hIMnetHandle, AMInt8 basicStatus, AMInt8 predefStatus);

	/************************************************************************/
	// ���ܼ��: ������Ϣ
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* contactID	:[IN] Ŀ���û�ID
	//		AMChar* message		:[IN] ��Ϣ����
	//		AMInt32 length		:[IN] ��Ϣ���ݳ���
	//		AMInt32 type		:[IN] 0�����ݿ�, 1�������ݿ�
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetSendMessage(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* message, 
		AMInt32 length, AMInt32 type);


	IMnetRetCode IMnetSendMessageEx(IMnetHandle hIMnetHandle, 
		AMChar* contactID, AMInt32 contactIDLen,
		AMChar* message, AMInt32 length, AMInt32 type, 
		AMInt32 secondCmd, AMInt32 ackSeq);
	/*
	 *	�����ļ�֪ͨ��Ϣ��messageΪXML�Ķ���Э�顣���ⲿ��֤��
	 */
	IMnetRetCode IMnetSendFileMessage(IMnetHandle hIMnetHandle, AMChar* contactID, 
		AMChar* message, AMInt32 length, AMInt32 type);
	/************************************************************************/
	// ���ܼ��: ��������������û�
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* contactID	:[IN]Ҫ��ӵ��������е��û�ID
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetAddBlack(IMnetHandle hIMnetHandle, AMChar* contactID);

	/************************************************************************/
	// ���ܼ��: ��Ӻ���
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* contactID	:[IN] Ŀ���û�ID
	//		AMInt32 groupIDHigh	:[IN] ���id��32λ
	//		AMInt32 groupIDLow	:[IN] ���id��32λ
	//		AMInt32 type		:[IN] 
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMInt32 groupIDHigh, 
		AMInt32 groupIDLow, AMInt32 type, const AMChar *szMsg);

	/************************************************************************/
	// ���ܼ��: �޸�ǩ��
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* signature: [IN]�µ�ǩ��
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetChangeSignature(IMnetHandle hIMnetHandle, AMChar* signature);

	/************************************************************************/
	// ���ܼ��: �޸�״̬
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMInt8 basicstatus	: [IN]
	//		AMInt8 predefstatus	: [IN]
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetChangeStatus(IMnetHandle hIMnetHandle, AMInt8 basicstatus, AMInt8 predefstatus);

	/************************************************************************/
	// ���ܼ��: �޸���֤����
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMInt8 type			: [IN] 0��ʾ����Ҫ��֤, 1��ʾ��Ҫ��֤
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetChangeVerifyType(IMnetHandle hIMnetHandle, AMInt8 type);

	/************************************************************************/
	// ���ܼ��: �Ӻ�������ɾ���û�
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		ContactList* pContactList: [IN]��ɾ�����û��б�
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetDeleteBlack(IMnetHandle hIMnetHandle, AMChar* contactID);

	/************************************************************************/
	// ���ܼ��: ɾ������
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		ContactList* pContactList: [IN]��ɾ���ĺ����б�
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetDeleteContact(IMnetHandle hIMnetHandle, ContactList* pContactList);

	/************************************************************************/
	// ���ܼ��: ɾ��������Ϣ
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMInt32 lastTime :[IN] ��һ��������Ϣʱ��
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetDeleteOfflineMsg(IMnetHandle hIMnetHandle, AMInt32 lastTime);

	/************************************************************************/
	// ���ܼ��: �����û�״̬��Ϣ��ȡ�������û�״̬��Ϣ
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		ContactList* pContactList: [IN]�û��б�
	//		AMInt8 type				 : [IN] 1��ʾ����, 0��ʾȡ������
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetSubscribeContactInfo(IMnetHandle hIMnetHandle, ContactList* pContactList, AMInt8 type);

	/************************************************************************/
	// ���ܼ��: ���һ����
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* groupName		:[IN] ��ӵ�����
	//		AMInt32 parentGroupIDHigh :[IN] ��ӵ���ĸ��׵���ID ��32λ
	//		AMInt32 parentGroupIDLow :[IN] ��ӵ���ĸ��׵���ID ��32λ
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetAddGroup(IMnetHandle hIMnetHandle, AMChar* groupName, AMInt32 parentGroupIDHigh, AMInt32 parentGroupIDLow);

	/************************************************************************/
	// ���ܼ��: 
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		ContactList* pContactList: [IN]�û��б�
	//		AMInt8 type				 : [IN] 1��ʾ����, 0��ʾȡ������
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetDeleteGroup(IMnetHandle hIMnetHandle, AMInt32 groupIDHigh, AMInt32 groupIDLow);
	
	/************************************************************************/
	// ���ܼ��: 
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMInt32 groupIDHigh		:[IN] ��id��32λ
	//		AMInt32 groupIDLow		:[IN] ��id��32λ
	//		AMChar* groupName		:[IN] �޸ĺ������
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetRenameGroup(IMnetHandle hIMnetHandle, AMInt32 groupIDHigh, AMInt32 groupIDLow, AMChar* groupName);

	/************************************************************************/
	// ���ܼ��: 
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* contactID		:[IN] Ŀ���û�
	//		AMChar* displayName		:[IN] ��ʾ��
	//		AMChar* verifyInfo		:[IN] ��֤��Ϣ
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetSendVerifyInfo(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* displayName, AMChar* verifyInfo);

	/************************************************************************/
	// ���ܼ��: 
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* contactID		:[IN] Ŀ���û�
	//		AMChar* rejectReason	:[IN] �ܾ�ԭ��
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetRejectAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* rejectReason);

	/************************************************************************/
	// ���ܼ��: 
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	//		AMChar* contactID		:[IN] Ŀ���û�
	//		AMInt32 groupIDHigh		:[IN] �û���ID��32λ
	//		AMInt32 groupIDLow		:[IN] �û���ID��32λ
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetAcceptAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMInt32 groupIDHigh, AMInt32 groupIDLow);

	//************************************
	// Method:    IMnetGetPeerInfo			��ȡ���ѵ���Ϣ���첽����RspGetPeerInfo�������Ѳ����ߡ���������û�з��أ�
	// Author:    yanlong.shiyl
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szContactID
	//************************************
	IMnetRetCode IMnetGetPeerInfo(IMnetHandle hIMnetHandle, const AMChar *szContactID);

	//************************************
	// Method:    IMnetGetPeerVerifyConfig	��ȡ���ѵ���Ӻ������ã��첽����RspGetPeerVerifyConfig
	// Author:    yanlong.shiyl
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szContactID
	//************************************
	IMnetRetCode IMnetGetPeerVerifyConfig(IMnetHandle hIMnetHandle, const AMChar *szContactID, AMInt32 iClientId);

	IMnetRetCode IMnetGetUserUDBProfile(IMnetHandle hIMnetHandle, const AMChar *szContactID);

	IMnetRetCode IMnetSearchUser(IMnetHandle hIMnetHandle, const AMChar *szKeyWord);

	//************************************
	// Method:    IMnetGetSignature				��ȡ����ǩ�����첽����NtfUpdateUsrExtInfo
	// Author:    yanlong.shiyl
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: const AMChar * szToken		��¼���ʺ�Token
	// Parameter: AMUChar	ucTest				1��ʾ���Ի���
	// Parameter: const AMChar * szContactIDs	һ��������ϵ��ID��ɵ��ַ�������'\1'�ָ
	// Parameter: AMInt32 iCount				��ϵ��ID�ĸ�����������20��
	//************************************
	IMnetRetCode IMnetGetSignature(IMnetHandle hIMnetHandle, const AMChar *szToken, AMUChar ucTest,
									const AMChar * szContactIDs, AMInt32 iCount);

	IMnetRetCode IMnetSendMsg2Callback(IMnetHandle hIMnetHandle, EventId id, AMVoid *pMsg, AMUInt32 uiSize, FreeContent freer);
	IMnetRetCode IMnetSendMsg2CallbackProc(IMnetHandle hIMnetHandle, EventId id, AMVoid *pMsg, AMUInt32 uiSize, FreeContent freer, AMBool bLow);
	//************************************
	// Method:    IMnetGetDegree	:��ȡ���ѵĻ�Ծ�ȣ��첽����ImRspGetDegree
	// Author:    yanlong.shiyl 
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: AMChar * contactID
	//************************************
	IMnetRetCode IMnetGetDegree(IMnetHandle hIMnetHandle, AMChar *contactID);

	IMnetRetCode IMnetGetAppAddr(IMnetHandle hIMnetHandle, const AMChar *szSessionId, AMUInt64 ulObjId);

	//************************************
	// Method:    IMnetGetContactMemo		��ȡ�ҶԺ���contactId�ı�ע���첽����RspGetContactMemo
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	// Parameter: AMChar * contactID
	//************************************
	IMnetRetCode IMnetGetContactMemo(IMnetHandle hIMnetHandle, AMChar *contactID);

	IMnetRetCode IMnetChangeSrvMode(IMnetHandle hIMnetHandle, AMUChar ucStatus);

	IMnetRetCode IMnetGetWebSession(IMnetHandle hIMnetHandle);

	/*
	 *	��server������֤��
	 */
	IMnetRetCode IMnetCheckAuthCode(IMnetHandle hIMnetHandle, const AMChar *szSession, const AMChar *szCode);

	/*
	 *	��server����ԭʼ������ݡ���NtfNeedAuthCheck�д��������ݣ�
	 */
	IMnetRetCode IMnetSendRawPacket(IMnetHandle hIMnetHandle, const AMChar *szPacket, AMUInt32 uiLen);

	//************************************
	// Method:    IMnetShallowLoginTribe	ǳ��¼Tribe�� �첽����RspShallowLoginTribe
	// Returns:   IMnetRetCode
	// Parameter: IMnetHandle hIMnetHandle
	//************************************
	IMnetRetCode IMnetShallowLoginTribe(IMnetHandle hIMnetHandle);

	//************************************
	// Method:    IMnetDeepLoginTribe		���¼Tribe, �첽����RspDeepLoginTribe
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

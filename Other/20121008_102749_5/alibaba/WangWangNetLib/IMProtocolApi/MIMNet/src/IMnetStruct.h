#ifndef IM_NET_STRUCT_H
#define IM_NET_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "IMnet.h"
/************************************************************************/
// common define
/************************************************************************/

#define IM_MAGIC					"magic"

#define IMNET_MAX_KEY_LEN           8   
#define IMNET_MAX_EXT_LEN           512
#define IMNET_MAX_PSW_LEN           64
#define IMNET_MAX_USER_NAME_LEN     64
#define IMNET_MAX_VERSION_LEN       64
#define IMNET_MAX_HARDCHECK_LEN     16
#define IMNET_MAX_RID_LEN           16
#define IMNET_MAX_TOKEN_LEN         32
#define IMNET_MAX_WEB_MD5_LEN       32
#define IMNET_MAX_BIND_ID_LEN       32

/************************************************************************/
//packet
/************************************************************************/
#define PROTOCOL_HEAD_LENGTH		24
#define PROTOCOL_HEAD_STARTER		-120
#define PROTOCOL_HEAD_MAJOR			6
#define PROTOCOL_HEAD_ENCRYPT		1
#define PROTOCOL_HEAD_NO_ENCRYPT	0

#define PROTOCOL_SECOND_HEAD_LENGTH 8


#undef MACRO_DEF
#undef MACRO_DEFS
#undef MACRO_DEFR
#undef MACRO_DEF_SECOND_PROTOCOL
#undef MACRO_DEF_EXTERN

	typedef enum{
#define MACRO_DEF(id, value, structDef)
#define MACRO_DEFS(id, value, structDef)
#define MACRO_DEFR(id, value, structDef)
#define MACRO_DEF_EXTERN(id, value, structDef)
#define MACRO_DEF_SECOND_PROTOCOL(id, value)    id=value,
#include "IMnetEventDef.h"
	}SecondProtocolId;

#undef MACRO_DEF
#undef MACRO_DEFS
#undef MACRO_DEFR
#undef MACRO_DEF_SECOND_PROTOCOL

	typedef struct {
		AMInt32		groupStamp;
		AMInt32		contactStamp;
		AMInt32		blackListStamp;
		AMInt32		revBlackListStamp;
	}LoginStamp;

	typedef struct {
		AMInt32		connectNo;
		AMInt32		bIsToken;
		LoginStamp	loginStamp;
		AMChar		constDesKey[IMNET_MAX_KEY_LEN];
		AMChar		encryptKey[IMNET_MAX_KEY_LEN];
		AMChar		constVersion[IMNET_MAX_VERSION_LEN];
		AMChar		userName[IMNET_MAX_USER_NAME_LEN];
		AMChar		password[IMNET_MAX_PSW_LEN];
		AMBool		bHasWorkKey;					//���������Ƿ��ǰ��ʺŵ�RSPLogin;
	}VarKeeper;

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
		AMInt32		connectNo;
		AMChar*		remark;
		AMInt32     remarkLen;
		AMInt8		pubKey[IMNET_MAX_KEY_LEN]; 
		AMUInt8		propertyNum;
	}ImRspCheckVersion;

	typedef struct{
		AMUInt8		propertyNum;
	}ImReqCommonSimple,
		ImReqHealthCheck,
		ImReqLogoff;

	typedef struct {
		AMInt32		padding;
	}ImAckHealthCheck;

	typedef struct{
		AMChar		version[IMNET_MAX_VERSION_LEN];
		AMUInt8		propertyNum;
	}ImReqCheckVersion;

	typedef struct{
		AMInt32		connectNo;                      // ���Ӻ�
		AMInt32		language;                       // windows�µ�����ID
		AMInt32		timestampFlag;                  // ʱ�����־
		AMInt32		timestampList[4];
		AMUInt8		tokenFlag;                      // 0== rawpw, 1== tokenpw
		AMUInt8		propertyNum;
		AMInt16		reserved;
		AMUInt8	    encryptKey[IMNET_MAX_KEY_LEN];
		AMChar		password[IMNET_MAX_PSW_LEN];    // ����
		AMChar		version[IMNET_MAX_VERSION_LEN]; // �汾��
		AMChar      hardcode[1][16];                //��ʱ��֪����ʲô�õ�,Ҳ��֪���������ĸ�ֵ
		AMInt32		hardCodeCount;                  //�������hardcode�ĸ���,�����е���.
		AMChar		hardcheck[IMNET_MAX_HARDCHECK_LEN];
		AMChar		rid[IMNET_MAX_RID_LEN];
		AMChar	    extData[IMNET_MAX_EXT_LEN];
	}ImReqLogin;

	typedef struct {
		AMInt32		connectNo;
		//AMChar*		workKey;
		//AMInt32     workKeyLen;
		AMUInt8*	loginBlock;
		AMInt32     loginBlockLen;
	}ImPackLoginInd;

	typedef struct {
		AMInt32		connectNo;          // ���Ӻ�,�����򵥷�ֹ�����ط�������
		AMUInt8	    workKey[IMNET_MAX_KEY_LEN]; // ����RSA Pub Key ���ܹ������������IM_REQ_LOGIN�����DESKEY
		AMUInt8*	loginBlock;         // ��IM_REQ_LOGIN���������DES���ܹ���Ĵ�
		AMInt32     loginBlockLen;
		AMUInt8		propertyNum;
	}ImReqPreLogin;

	typedef struct {
		AMUInt8		propertyNum;
		AMInt32		timestampFlag;                  // ʱ�����־
		AMInt32		timestampList[4];
		AMChar	*	remark;
	}ImReqLogin2;

	typedef struct {
		AMChar*     bindID;
		AMInt32		bindIDLen;
		AMInt8		basicStatus;
		AMInt8		predefStatus;
		AMUInt8		propertyNum;
	}ImReqPostLogin,
		ImReqChangeStatus;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetContact;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetReverseBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetContactStatus;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetUserInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqHelpGetBindTo;


	
	typedef struct {
		AMUInt8		propertyNum;
	}ImReqLoginAgain;

	typedef struct {
		AMInt32		connectNo;                      // ���Ӻ�
		AMInt8		reserved;
		AMUInt8		propertyNum;
		AMInt8		basicStatus;
		AMInt8		predefStatus;
		AMChar		password[IMNET_MAX_PSW_LEN];    // ����
		AMChar		version[IMNET_MAX_VERSION_LEN]; // �汾��
		AMChar	    extData[IMNET_MAX_EXT_LEN];
	}ImReqReLogin;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAddGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqDeleteGroup;

	typedef struct {
		AMChar*     bindID;
		AMInt32		bindIDLen;
		AMInt8	addcontactFlag;	// ��0������Ҫ��֤��1����Ҫ��֤��
		AMInt8	sendmsgFlag;	// ��0�������ͣ�1���������ͣ�
		AMInt8	enableSearch;	// ��0��������������1��������������
		AMUInt8	propertyNum;
	}ImReqChangeUserVerify;

	typedef struct {
		AMChar*     bindID;
		AMInt32		bindIDLen;
		ContactInfo	contactInfo;
		AMInt8		type;
		AMChar	*	szMessage;
		AMUInt32	uiMsgLen;
		AMUInt8		propertyNum;
	}ImReqAddContact;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangeContact;

	typedef struct {
		AMChar*			bindID;
		AMInt32			bindIDLen;
		ContactList*	pContactList;
		AMUInt8			propertyNum;
	}ImReqCommonContactList,
		ImReqDeleteContact,
		ImReqDisableSubscribeInfo,
		ImReqSubscribeInfo;

	typedef struct {
		AMChar*		bindID;
		AMInt32		bindIDLen;
		AMInt32		groupIDHigh;
		AMInt32		groupIDLow;
		AMChar*		contactID;
		AMInt32		contactIDLen;
		AMInt8		opcode;			//0:ͬ�� 1:�ܾ�
		AMChar	*	szMessage;
		AMUInt32	uiMsgLen;
		AMUInt8		propertyNum;
	}ImReqAddContactACK;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetContactDetail;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangeUserDetail;

	typedef struct {
		AMChar		contactID[IMNET_MAX_USER_NAME_LEN];
		AMUInt8		propertyNum;
	}ImReqGetContactMemo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangeContactMemo;

	typedef struct {
		AMChar		contactID[IMNET_MAX_USER_NAME_LEN];
		AMUInt8		propertyNum;
	}ImReqAddBlack;

	typedef struct {
		AMInt32 retCode;	// 0���ɹ�������ֵ��ʧ��
		AMChar*	blackId;	// ������ID
		AMInt32	blackIdLen;
		AMInt32 timestamp;
		AMUInt8	propertyNum;
	}ImReqDeleteBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetOfflineMsg;


	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAddOfflineMsg;

	typedef struct {
		AMChar*		bindID;
		AMInt32		bindIDLen;
		AMInt32		lastTime;
		AMUInt8		propertyNum;
	}ImReqDeleteOfflineMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetSystemMsg;

	typedef struct {
		AMChar*     bindID;
		AMInt32		bindIDLen;
		AMChar*     contactID;
		AMInt32		contactIDLen;
		AMChar*     message;
		AMInt32     messageLen;
		AMInt32     type;
		SecondProtocolId secondCmd;
		AMInt32		ackSeq;
		AMUInt8		propertyNum;
	}ImReqSendIMMessage;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqSendMultiUserMsg;
	
	typedef struct {
		AMUInt8		propertyNum;
	}ImReqUpdateGeneralContact;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetToolsProfile;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangeToolsProfile;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
	}ImReqGetPeerInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangePortrait;	

	typedef struct {
		AMChar*		signature;
		AMInt32		signatureLen;
		AMUInt8		propertyNum;
	}ImReqChangeSignature;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAddBinding;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChangeBinding;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqDeleteBinding;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetBinding;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetFileServerAddress;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqCanKeySearch;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetUsersStatus;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqPreLoginAgain;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetWebSession;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
	}ImReqGetUserUDBProfile;

	typedef struct {
		AMUInt8		propertyNum;
		
		AMUInt32	timeStamp;
		AMUInt8     searchType;
		
		AMChar	*	keyWord;
		AMInt32		keyWordLen;

		AMUInt8     syncAcc;

		AMChar	*	reserve;
		AMInt32		reserveLen;
	}ImReqSearchUser;

	typedef struct {
		AMUInt8		propertyNum;
		AMUInt8		clientId;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
	}ImReqGetPeerVerifyConfig;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetPwdToken;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	szSession;
		AMUInt32	uiSessionLen;
		AMChar	*	szCode;
		AMUInt32	uiCodeLen;
		AMUInt8		uiMode;
	}ImReqCheckAuthCode;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	accountId;
		AMInt32		accountIdLen;
		AMUInt8		status;
	}ImReqHelpLogin;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	accountId;
		AMInt32		accountIdLen;
		AMUInt8		status;
	}ImReqHelpChangeSrvMode;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqHelpSetShareCID;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqHelpGetChildOnline;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqHelpGetOnlineChilds;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqHelpGetServices;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqSendWatchInfo;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetSIPSessionID;

	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	contactId;
		AMInt32		contactIdLen;
	}ImReqGetDegree;

	typedef struct {
		AMInt8  headLen;
		AMInt8  compress;
		AMInt16 cmd;
		AMInt32 ackSeq;
	}ImMessageChildHead;

	typedef struct {
		ImMessageChildHead  childHead;
		AMUInt8*            content;
		AMInt32             contentLen;
	}ImMessageText;

	typedef struct {
		AMChar*         fromId;     // ������
		AMInt32         fromIdLen;
		AMInt8          type;       // 0: ��ͨ������Ϣ, 1: ������Ϣ, 2: �����ϵ��֪ͨ��Ϣ
		AMInt32         sendTime;   // ����ʱ�� !!!GMT
		ImMessageText   text;       // ��Ϣ�壬���ݸ�ʽ�ɶ���Э��ȷ��
		AMInt8			serverType;	// 1��ʾ����ͻ��˹���
	}OfflineMsgInfo;

	typedef struct ST_OfflineMsgList {
		OfflineMsgInfo              offlineMsgInfo;
		AMInt8						num;
		struct ST_OfflineMsgList*	pNext;
	}OfflineMsgList;

	typedef struct {
		AMChar*				bindID;
		AMInt32 			bindIDLen;
		AMInt32             retCode;
		OfflineMsgList*	    offlineMsgList;  //OfflineMsg��ָ��
		AMInt32				offlineMsgCount; //������¼OfflineMsg�ĸ���
		AMInt32				timestamp;
		AMUInt8				propertyNum;
	}ImRspGetOfflineMsg;

	typedef struct {
		AMChar*			bindID;
		AMInt32			bindIDLen;
		AMChar*         sendId;     // �����û���
		AMInt32         sendIdLen;
		AMInt32         sendTime;   // ����ʱ��
		ImMessageText	text;		// ��Ϣ�壬���ݸ�ʽ�ɶ���Э��ȷ��
		AMUInt8			serverType;	// 1��ʾ����ͻ��˹���
		AMChar			shiftFlag;	//��Ϣ�Ƿ񾭹�ת��
		AMUInt8		    propertyNum;
	}ImNtfIMMessage;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspHelpGetBindTo;	
	
	typedef struct {
		AMUInt8		propertyNum;
	}ImRspLogoff;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspAddGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChangeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDeleteGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChangeContact;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetContactDetail;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChangeUserDetail;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChangeContactMemo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfRefreshContact;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfFeeds;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfUserSnsInfo;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfExitInfoMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfWatchInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspAddBinding;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChangeBinding;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDeleteBinding;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetBinding;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetFileServerAddress;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetUsersStatus;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetPwdToken;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspHelpSetShareCID;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqHelpGetShareCID;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspHelpGetShareCID;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspHelpGetChildOnline;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspHelpGetOnlineChilds;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspHelpGetServices;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetSIPSessionID;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfLoginAgain;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDeleteOfflineMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetSystemMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspUpdateGeneralContact;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetToolsProfile;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChangeToolsProfile;	

	/*
	uint32_t m_retcode;
	string m_targetId;
	uint32_t m_clinetip;
	string m_version;
	uint8_t m_basicStatus;
	uint8_t m_predefStatus;
	uint8_t m_addcontactFlag; 
	uint8_t m_sendmsgFlag;	//�Ƿ�������Ϣ
	uint8_t m_reverseContact; //��ûʲô��
	*/

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspLoginAgain;


	typedef struct {
		AMChar		*szSessionId;	//�ͻ�������ʶ���˭SESSIOIN��
		AMInt32		iSessionIdLen;
		AMUInt16	uiAppType;		//uiAppType=1 ����ָ��FTSӦ��
		AMUInt16	uiSubType;		//uiSubType=3 ����ָ��������ͼ����
		AMUInt64	ulObjId;		//����id����������ͼ�д�����ͼID
		AMUInt8		propertyNum;
	}ImReqGetAppAddr;
	
	//������Ⱥ���ܵ�Req��Rsp������TribleGroup��struct������
	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetAddTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetAddTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqUpdateTribeGroup;	

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspUpdateTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqDelTribeGroup;
	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDelTribeGroup;


	typedef struct {
		AMUInt8		propertyNum;
	}ImReqShallowLoginTribe;


	typedef struct {
		AMUInt8		propertyNum;
		AMChar	*	tribeId;
		AMInt32		tribeIdLen;
	}ImReqDeepLoginTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqInviteTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspInviteTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqOnInviteJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspOnInviteJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAskJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspAskJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqExamAskJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspExamAskJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChgLevelTribeMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChgLevelTribeMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqChgTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspChgTribeGroup;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAddStarMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspAddStarMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqDelStarMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDelStarMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqDelTribeMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDelTribeMember;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetTribeBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetTribeBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAddTribeBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspAddTribeBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqDelTribeBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspDelTribeBlack;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqQuitTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspQuitTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqCloseTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspCloseTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetTribeInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetTribeInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqModifyTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspModifyTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetTribeMemberInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetTribeMemberInfo;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqSendTribeMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspSendTribeMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqGetTribeConfig;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspGetTribeConfig;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqSetTribeConfig;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspSetTribeConfig;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqSetOpenTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspSetOpenTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqVisitTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspVisitTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqClearVisitor;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspClearVisitor;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqStartTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspStartTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqRecommendTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspRecommendTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqAuthRecommend;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspAuthRecommend;

	typedef struct {
		AMUInt8		propertyNum;
	}ImReqUpdateTribeCard;

	typedef struct {
		AMUInt8		propertyNum;
	}ImRspUpdateTribeCard;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfInviteTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfAskJoinTribe;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNetTribeMsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfTribeSysmsg;

	typedef struct {
		AMUInt8		propertyNum;
	}ImNtfRecommendTribe;

#define XML_PARAM_CNTOP		"CntOp"
#define XML_PARAM_FROMUID	"FromUID"
#define XML_PARAM_TOUID		"ToUID"
#define XML_PARAM_MSG		"Msg"
#define XML_PARAM_PGID		"PGID"
#define XML_PARAM_RESULT	"Result"
#define XML_PARAM_DISPNAME  "DispName"

	typedef struct {
		AMChar*		result;
		AMInt32		resultLen;
		AMChar*		fromUID;
		AMInt32		fromUIDLen;
		AMChar*		toUID;
		AMInt32		toUIDLen;
		AMChar*		msg;
		AMInt32		msgLen;
		AMChar*		pgID;
		AMInt32		pgIDLen;
		AMChar*		dispName;
		AMInt32		dispNameLen;
	}MessageXML;

	typedef struct {
		AMUInt8		starter;		// 1
		AMUInt8		major;			// 2
		AMUInt8		minor;			// 3
		AMUInt8		msgtype;		// 4
		AMUInt8		encrypt;		// 5
		AMUInt8		compress;		// 6
		AMUInt8		encode;			// 7
		AMUInt8		lrc;			// 8
		AMInt32		seq;			// 12
		AMInt32		bodyLength;		// 16
		AMInt32		cmd;			// 20
		AMInt16		cc;				// 22
		AMInt16		reserved;		// 24

		//if reserved == 1 ,pExtData is valid.
		AMInt32		extLength;
		AMChar	    extData[IMNET_MAX_EXT_LEN]; 
	}PacketHead;

	typedef struct {
		IMnetHandle	hIMnetHandle;
		AMChar	*	szContactIDs;
		AMInt32		iCount;
		AMChar	*	szToken;
		AMChar	*	szAccount;
		AMUChar		ucTest;
	}GetSigParam;

	typedef struct {
		IMnetHandle	hIMnetHandle;
		AMChar		*szID;
	}DoAllotParam;

	typedef struct {
		AMUInt8 uiStarter;
		AMUInt16 uiVersion;
		AMUInt16 uiCmd;
		AMUInt32 uiSessionNo;
		AMUInt32 uiSeq;
		AMUInt16 uiCC;
		AMUInt32 uiLen;
		AMUInt8 uiFlag;
		AMUInt32 uiReserved;
	}FtsPacketHead;

	typedef struct {
		AMUInt32	timestamp;
		AMUInt8		propertyNum;
	}ImReqGetCNExtraInfo;

	typedef struct {
		AMUInt32	timestamp;
		AMUInt8		propertyNum;
	}ImReqSetBinding;

	typedef struct {
		Timestamp_Info*	timestamps;
		String_List*	login_ids;
		AMUInt8			propertyNum;
	}ImReqGetWebBinding;


#ifdef __cplusplus
}
#endif

#endif


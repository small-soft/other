#ifndef __IAIMCALLBACK_H__
#define __IAIMCALLBACK_H__

#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	//CAUTIONS: the =x of the enum definition means something, do not change the x.

	typedef enum {
        
		eLOGIN_NO_ACNT		=1,		// no such account
		eLOGIN_WRONG_PWD	=2,		// wrong password
		eLOGIN_SYS_BLK		=3,		// system block account
		eLOGIN_AUTH_LIMIT	=4,		// 
		eLOGIN_TOO_MANY		=5,		// too many instance 
		eLOGIN_APP_SEVR		=6,
		eLOGIN_WANGHAO		=7,		// wanghao is no longer in use
		eLOGIN_FORBIDDEN	=8,		// forbidden account
		eLOGIN_TIMEOUT		=9,		// login timeout
		eLOGIN_NETPUZZLE	=10,	// net
		eLOGIN_COMPANY		=14,	//AccountNotActivated	
		eLOGIN_PHONEWRONG	=15,	//Wrong Phone
		eLOGIN_CONFIRM		=16,
		eLOGIN_OTHER		,
	}AIM_LOGIN_FAIL_TYPE;

	typedef enum {
		eVERSION_OK			,
		eVERSION_UPDATE		,
		eVERSION_EXPIRE		,
		eVERSION_UNKNOWN	,
	} AIM_VERSION_INFO;

	typedef enum {
		eDATA_GROUP_READY		,
		eDATA_FRIEND_READY		,
		eDATA_STRANGER_READY	,
		eDATA_RECENT_READY		,
		eDATA_BLACK_READY		,

		eDATA_ALLREADY			,

		eDATA_BINDID_ALLREADY	,
		eDATA_BINDID_KICKED		,
	} AIM_DATA_INFO;

	typedef enum {
		eNET_OK				,
		eNET_PUZZLE			,
		eNET_CUT			,
	} AIM_NET_STATUS;

	typedef enum {
		eEXCEPTION_SEND		,
		eEXCEPTION_RECV		,
		eEXCEPTION_PACK		,
		eEXCEPTION_UNPACK	,
	} AIM_EXCEPTION_TYPE;

	typedef enum {
		eADDCONTACT_SUCCESS		= 0,
		eADDCONTACT_FAILED		= -1,
		eADDCONTACT_NEEDVERIFY	= 1,
		eADDCONTACT_WAITAUTH	= 2,
	}AIM_ADDCONTACT_RESULT;

	typedef enum
	{
		eADDCONTACT_INFO_SUCCESS = 0,			//"添加成功";
		eADDCONTACT_INFO_ADDED,					//"该联系人已经是你的好友，不能再次添加";
		eADDCONTACT_INFO_NOID,					//"联系人ID不存在";
		eADDCONTACT_INFO_FULL,					//"您的联系人已经达到了最大人数，不能再添加新的联系人了。";
		eADDCONTACT_INFO_FULLTODAY,				//"今日添加联系人数目已满";
		eADDCONTACT_INFO_NEEDAUTH,				//"对方需要验证";
		eADDCONTACT_INFO_NORIGHT,				//"您的帐号未激活，不能添加联系人，请先激活。";
		eADDCONTACT_INFO_NOTACTIVEID,			//"对方未激活";
		eADDCONTACT_INFO_WAITAUTH,				//"等待验证";
		eADDCONTACT_INFO_DENYALL,				//"拒绝被任何人添加";
		eADDCONTACT_INFO_HIGHFRENQ,				//"操作太频繁,请稍后再试";
		eADDCONTACT_INFO_ESERVICETEAMMATE = 0xc,//"E客服相关";
		eADDCONTACT_INFO_OTHERERROR				//"其他错误";
	}AIM_ADDCONTACT_INFO;

	typedef enum {
		eAIM_GROUP_ADD				,
		eAIM_GROUP_REMOVE			,
	}AIM_UPDATE_GROUP_TYPE;

	typedef	enum {
		eAIM_CONTACT_PRESENCE	=0	,
		eAIM_CONTACT_SIGNATURE	=1	,
		eAIM_CONTACT_PORTRAIT	=2	,
		eAIM_CONTACT_PRESENCE_FIRST	,
	}AIM_UPDATE_CONTACT_TYPE;

	typedef	struct
	{
		AIM_VERSION_INFO			eInfo;
	} AIM_NTF_CHECK_VERSION;

	typedef struct 
	{
		AIM_DATA_INFO				eInfo;
	} AIM_NTF_DATA_READY;

	typedef struct  
	{
		AIM_EXCEPTION_TYPE			eType;
	} AIM_NTF_EXCEPTION;

	typedef struct
	{
		AIM_NET_STATUS				eStatus;
	} AIM_NTF_NET_STATUS;

	typedef struct
	{
		AIM_UPDATE_GROUP_TYPE	eType;
		AMHandle				hGroup;
		AMHandle				hContact;
	}AIM_NTF_UPDATE_GROUP;

	typedef struct
	{
		AIM_UPDATE_CONTACT_TYPE	eType;		//状态和签名时，直接用IAContact_Get得到相应值；Portrait时，需要IAIM_GetPortrait(ContactId)去取
		AMHandle			*	phContacts;
		AMInt32					iCount;
	} AIM_NTF_UPDATE_CONTACT;

	typedef struct  
	{
		AMHandle				hSession;
		AMHandle				hMessage;
	} AIM_NTF_MSG;

	typedef struct
	{
		AMChar				*	szContactId;
	} AIM_NTF_ADDED_BY,
		AIM_NTF_ACCEPTED_BY;

	typedef struct
	{
		AMChar				*	szContactId;
		AMChar				*	szInfo;
	} AIM_NTF_REJECTED_BY;

	typedef struct  
	{
		AMChar				*	szContactId;
		AMChar				*	szVerifyInfo;
	} AIM_NTF_REQUEST_FROM;

	typedef struct  
	{
		AMInt32					iRetCode;
		AMUInt8					uiMulStatus;
		AMChar				*	szParentId;
	} AIM_NTF_HELP_LOGIN;
	//Help_Login, relates only to ECustomer Account

	typedef struct
	{
		AMUInt32				iRetCode;		// 返回码
		AMUInt32				iNeedNextlevel;	// 升下一级还需要的活跃度数
		AMUInt32				iActivity;		// 活跃度
		AMInt8					iAddcontactFlag; // 添加为联系人校验标志
		AMInt8					iSendmsgFlag;	// 发送消息校验标志
		AMInt8					iActLevel;		// 活跃度等级
		AMInt8					iImlevel;		// IM level,
		AMInt8					iMulsendflag;	// 是否允许群发;
	} AIM_NTF_USER_INFO;

	typedef struct  
	{
		AMInt32					iRetCode;
		AIM_LOGIN_FAIL_TYPE		eInfo;
	} AIM_RSP_LOGIN;

	typedef struct  
	{
		AMInt32					iRetCode;
		AMInt32					iVerifyConfig;	//0: no need verify，1: need verify，2: discard all request
	}AIM_RSP_CHG_VERIFY;

	typedef struct
	{
		AMInt32					iRetCode;
	} AIM_RSP_CHG_SRV_MODE;//relates only to ECustomer Account

	typedef struct {
		AMInt32					iRetCode;
		AMChar				*	szSigNature;
	}AIM_RSP_CHG_SIGNATURE;

	typedef struct  
	{
		AIM_ADDCONTACT_RESULT	eRetCode;
		AMChar				*	szContactId;
		AIM_ADDCONTACT_INFO		eInfo;
	}AIM_RSP_ADD_CONTACT;

	typedef struct  
	{
		AMInt32					iRetCode;
		AMChar				*	szContactId;
	}AIM_RSP_DEL_CONTACT;

	typedef struct
	{
		AMInt32					iRetCode;
		AMChar				*	szContactId;
		AMInt8					iOpCode;	////0 - 同意,1 - 拒绝，
	}AIM_RSP_ACCEPT;//RspAddContactAck....

	typedef struct {
		AMInt32					iRetCode; 
		AMChar				*	szBlackId; 
	}AIM_RSP_ADD_BLACK,
		AIM_RSP_DEL_BLACK;

	typedef struct {
		AMInt32					iRetCode;
		AMChar				*	szContactId;
		AMChar				*	szLongId;
		AMChar				*	szShowName;
	}AIM_RSP_GET_VERIFY;

	typedef struct {
		AMInt32					iRetCode;
		AMChar				**	pszKeys;
		AMChar				**	pszValues;
		AMInt32					iCount;
		AMInt32					iTotalLen;
		AMChar				*	szContactId;
	}AIM_RSP_GET_PROFILE;//UDP Profile

	typedef struct {
		AMInt32			iRetCode;
		AMInt32			iUserCount;

		// user info below		
		AMChar		**	pszContactIds;
		AMChar		**	pszNickNames;
		AMUInt8		*	pAges;
		AMUInt8		*	pGenders;
		AMChar		**	pszCitys;
		AMUInt8		*	pBasicStatus;
	} AIM_RSP_SEARCH_USER;

	typedef struct {
		AMInt32					iRetCode;
		AMChar				*	szContactId;
		AMInt32					iUserLevel;
		AMInt32					iTotalDegree;
		AMInt32					iNeedDegree;
	} AIM_RSP_GET_DEGREE;

	typedef struct {
		AMInt32					iRetCode;
		AMChar				*	szContactId;
		AMChar				*	szMemo;
	} AIM_RSP_GET_MEMO;

	typedef struct {
		AMInt32					iRetCode;
		AMChar				**	pszContactIds;
		AMChar				**	pszValues;
		AMInt32					iCount;
	} AIM_RSP_GET_SIGNATURE;

	typedef struct {
		AMInt32					iRetCode;
		AMChar				*	szContactId;
		AMChar				*	szValue;
	} AIM_RSP_GET_PROTRAIT;

	typedef struct  
	{
		AMInt32					iRetCode;
	} AIM_RSP_SEND_MSG;								//目前没有这个事件...//黑名单、本人，可判断...

	typedef struct  
	{
		AMInt32					iRetCode;
		AIM_PRESENCE			ePresence;
	} AIM_RSP_CHG_PRESENCE;							//目前没有这个事件

	typedef enum  
	{
		ePROGRESS_NET	= -1,			//开始建立连接
		ePROGRESS_SERV	= -2,			//开始发送请求
	} AIM_TRANS_PROGRESS;

	typedef struct
	{
		AMInt32		iTaskId;
		AMInt32		iProgress;	//iProgress的取值为以下三种情况：
								//	A、ePROGRESS_NET: 开始建立连接
								//	B、ePROGRESS_SERV: 开始发送请求
								//	C、0至100: 数据发送百分比
	} AIM_NTF_PROGRESS;

	typedef enum
	{
		eAIM_TRANS_MEMORY	= -0x10,	//内存不足
		eAIM_TRANS_FILE,	//文件不可打开
		eAIM_TRANS_FILE_READ,
		eAIM_TRANS_FILE_WRITE,
		eAIM_TRANS_TARGET,	//未找到
		eAIM_TRANS_SOCKET,
		eAIM_TRANS_SEND,
		eAIM_TRANS_RECV,
		eAIM_TRANS_FAIL		= -1,	//一般错误
		eAIM_TRANS_OK		= 0,
	} AIM_TRANS_RESULT;

	typedef struct
	{
		AIM_TRANS_RESULT		eResult;
		AMInt32					iTaskId;
	}AIM_RSP_FILE;

	typedef	struct  
	{
		AMInt32					iAuthId;
		AMInt32					iRetCode;
		AMChar				*	pvData;
		AMInt32					iDataLen;	//为0的时候，表示获取验证码出错
	}AIM_NTF_NEED_AUTH;

	typedef	struct  
	{
		AMInt32					iAuthId;
		AMInt32					iRetCode;
	}AIM_RSP_CHECK_CODE;

	typedef struct  
	{
		AMVoid	*pvArg;
		AIM_RESULT	(*OnNtfForceDisconnected)(AMVoid *);
		AIM_RESULT	(*OnNtfCheckVersion)(AMVoid *, AIM_NTF_CHECK_VERSION *);
		AIM_RESULT	(*OnNtfDataReady)(AMVoid *, AIM_NTF_DATA_READY *);
		AIM_RESULT	(*OnNtfNetInfo)(AMVoid *, AIM_NTF_NET_STATUS *);
		AIM_RESULT	(*OnNtfUpdateGroup)(AMVoid *, AIM_NTF_UPDATE_GROUP *);
		AIM_RESULT	(*OnNtfUpdateContact)(AMVoid *, AIM_NTF_UPDATE_CONTACT *);
		AIM_RESULT	(*OnNtfMesage)(AMVoid *, AIM_NTF_MSG *);
		AIM_RESULT	(*OnNtfAddedBy)(AMVoid *, AIM_NTF_ADDED_BY *);
		AIM_RESULT	(*OnNtfAcceptedBy)(AMVoid *, AIM_NTF_ACCEPTED_BY *);
		AIM_RESULT	(*OnNtfRejectedBy)(AMVoid *, AIM_NTF_REJECTED_BY *);
		AIM_RESULT	(*OnNtfRequestFrom)(AMVoid *, AIM_NTF_REQUEST_FROM *);
		AIM_RESULT	(*OnNtfHelpLogin)(AMVoid *, AIM_NTF_HELP_LOGIN *);
		AIM_RESULT	(*OnNtfUserInfo)(AMVoid *, AIM_NTF_USER_INFO *);
		AIM_RESULT	(*OnNtfProgress)(AMVoid *, AIM_NTF_PROGRESS *);
		AIM_RESULT	(*OnNtfNeedAuth)(AMVoid *, AIM_NTF_NEED_AUTH *);
	
		AIM_RESULT	(*OnRspLogin)(AMVoid *, AIM_RSP_LOGIN *);//17
		AIM_RESULT	(*OnRspChgVerify)(AMVoid *, AIM_RSP_CHG_VERIFY *);
		AIM_RESULT	(*OnRspChgSrvMode)(AMVoid *, AIM_RSP_CHG_SRV_MODE *);
		AIM_RESULT	(*OnRspChgSignature)(AMVoid *, AIM_RSP_CHG_SIGNATURE *);
		AIM_RESULT	(*OnRspAddContact)(AMVoid *, AIM_RSP_ADD_CONTACT *);
		AIM_RESULT	(*OnRspDelContact)(AMVoid *, AIM_RSP_DEL_CONTACT *);
		AIM_RESULT	(*OnRspAccept)(AMVoid *, AIM_RSP_ACCEPT *);
		AIM_RESULT	(*OnRspAddBlack)(AMVoid *, AIM_RSP_ADD_BLACK *);
		AIM_RESULT	(*OnRspDelBlack)(AMVoid *, AIM_RSP_DEL_BLACK *);
		AIM_RESULT	(*OnRspGetVerify)(AMVoid *, AIM_RSP_GET_VERIFY *);
		AIM_RESULT	(*OnRspGetProfile)(AMVoid *, AIM_RSP_GET_PROFILE *);
		AIM_RESULT	(*OnRspGetDegree)(AMVoid *, AIM_RSP_GET_DEGREE *);
		AIM_RESULT	(*OnRspGetMemo)(AMVoid *, AIM_RSP_GET_MEMO *);
		AIM_RESULT	(*OnRspGetSignature)(AMVoid *, AIM_RSP_GET_SIGNATURE *);
		AIM_RESULT	(*OnRspGetPortrait)(AMVoid *, AIM_RSP_GET_PROTRAIT *);
		AIM_RESULT	(*OnRspSendMsg)(AMVoid *, AIM_RSP_SEND_MSG *);
		AIM_RESULT	(*OnRspChgPresence)(AMVoid *, AIM_RSP_CHG_PRESENCE *);
		AIM_RESULT	(*OnRspFile)(AMVoid *, AIM_RSP_FILE *);
		AIM_RESULT	(*OnRspCheckCode)(AMVoid *, AIM_RSP_CHECK_CODE *);
		AIM_RESULT	(*OnRspSearchUser)(AMVoid *, AIM_RSP_SEARCH_USER *);
		
	} AIM_CALLBACK;


#ifdef __cplusplus
};
#endif // __cplusplus

#endif	//__IAIMCALLBACK_H__
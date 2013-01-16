/************************************************************************/
//dengxiang:该文件定义网络协议层的事件类型和原型,切勿直接包含此头文件.
/************************************************************************/
/************************************************************************/
// 其中MACRO_DEF_EXTERN为外部使用类型，其他为内部使用
/************************************************************************/
/************************************************************************/
// IMnet自定义不需要前阶段预处理的控制在128个以内(0x00000080 ~ 0x000000FF)
/************************************************************************/

//IMM_SP_TEXT		即时聊天消息
MACRO_DEF_EXTERN(IM_EVENT_CHAT_MESSAGE			, 0x00000080					, ImEventChatMessage)
//IMM_SP_BUZZ		震动
MACRO_DEF_EXTERN(IM_EVENT_BUZZ_MESSAGE			, 0x00000081					, ImEventBuzzMessage)
//IMM_SP_P2P		P2P模块相关的IMS信息交互消息
MACRO_DEF_EXTERN(IM_EVENT_P2P_MESSAGE			, 0x00000082					, ImEventP2PMessage)
//IMM_SP_AUTO_REPLY 自动回复
MACRO_DEF_EXTERN(IM_EVENT_AUTO_REPLY			, 0x00000083					, ImEventAutoReply)
//IMM_SP_MSG_ACK	消息接收确认
MACRO_DEF_EXTERN(IM_EVENT_MESSAGE_ACK			, 0x00000084					, ImEventMessageAck)

//IMM_SP_CONTACT	添加联系人相关
//IMM_CONTACT_ADDED				不需验证的添加
MACRO_DEF_EXTERN(IM_EVENT_CONTACT_ADDED			, 0x00000085					, ImEventContactAdded)
//IMM_CONTACT_IGNOREUSER_ADDED  阻止用户添加（黑名单）
MACRO_DEF_EXTERN(IM_EVENT_CONTACT_IGNORE_ADDED	, 0x00000086					, ImEventContactIgnoreAdded)
//IMM_CONTACT_IGNOREUSER_DELED  取消阻止用户
MACRO_DEF_EXTERN(IM_EVENT_CONTACT_IGNORE_DELED	, 0x00000087					, ImEventContactIgnoreDeled)
//IMM_CONTACT_ASKADD_REQ        发出添加请求验证
MACRO_DEF_EXTERN(IM_EVENT_CONTACT_ADD_CNT_VERIFY, 0x00000088					, ImEventContactAskAddVerify)
//IMM_CONTACT_ASKADD_NO         答复请求验证，拒绝
MACRO_DEF_EXTERN(IM_EVENT_CONTACT_ASKADD_NO		, 0x00000089					, ImEventContactAskAddNo)
//IMM_CONTACT_ASKADD_YES        答复请求验证，同意
MACRO_DEF_EXTERN(IM_EVENT_CONTACT_ASKADD_YES	, 0x0000008A					, ImEventContactAskAddYes)

//IMM_SP_NOTIFY				通知消息,比如对方正在输入消息
MACRO_DEF_EXTERN(IM_EVENT_WRITING_MESSAGE		, 0x0000008B					, ImEventWritingMessage)
//IMM_SP_GROUP_BROADCAST	收到的群发消息(注意此消息只能被用于接收不能发送)
MACRO_DEF_EXTERN(IM_EVENT_GROUP_BROADCAST		, 0x0000008C					, ImEventGroupBroadcast)
//IMM_SP_PLUGINS_QUERY	    插件查询命令
MACRO_DEF_EXTERN(IM_EVENT_PLUGINS_QUERY			, 0x0000008D					, ImEventPluginsQuery)
//IMM_SP_PLUGINS_RESPONSE   插件查询命令的应答
MACRO_DEF_EXTERN(IM_EVENT_PLUGINS_RSP			, 0x0000008E					, ImEventPluginsRsp)
//IMM_SP_PLUGINS_INVITE	    插件邀请使用
MACRO_DEF_EXTERN(IM_EVENT_PLUGINS_INVITE		, 0x00000090					, ImEventPluginsInvite)
//IMM_SP_CUSTOM_MESSAGE	    关于自定义消息(还没有定义好)
MACRO_DEF_EXTERN(IM_EVENT_CUSTOM_MESSAGE		, 0x00000091					, ImEventCustomMessage)
//IMM_SP_FOCUS_TALK		    即时焦点
MACRO_DEF_EXTERN(IM_EVENT_FOCUS_TALK			, 0x00000092					, ImEventFocusTalk)

//yanlong.shiyl
MACRO_DEF_EXTERN(IM_EVENT_PRIVATE				, 0x00000093					, ImEventPrivate)

MACRO_DEF_EXTERN(IM_EVENT_OFF_OBJ				, 0x00000094					, ImEventOffObj)

MACRO_DEFS(IM_RAW_PACKET						, 0x00000095					, ImRawPacket)

//IM_EVENT_U2U_Message 通用二级协议的回应
MACRO_DEF_EXTERN(IM_EVENT_U2U_Message		, 0x00000096						, ImEventU2UMessage)
	

MACRO_DEF_EXTERN(IM_EVENT_DELETE_OFFLINE_MESSAGE, 0xffffffff					, ImEventToDeleteOfflineMsg)

/************************************************************************/
// 内部自定义并需要后阶段处理的从EVENT_CUSTOMIZE_MAX开始
/************************************************************************/
MACRO_DEF(IM_PACK_LOGIN_IND						, EVENT_CUSTOMIZE_MAX			, ImPackLoginInd)

/************************************************************************/
// 协议定义部分
/************************************************************************/
// 保活检查
MACRO_DEFS(IM_HEALTH_CHECK						, 0x01000001					, ImReqHealthCheck)
MACRO_DEFR(IM_HEALTH_CHECK_ACK					, 0x01000001					, ImAckHealthCheck)

// 版本检查
MACRO_DEFS(IM_REQ_CHECKVERSION					, 0x01000002					, ImReqCheckVersion)
MACRO_DEFR(IM_RSP_CHECKVERSION					, 0x01010002					, ImRspCheckVersion)
MACRO_DEF_EXTERN(IM_EVENT_CHECKVERSION			, IM_RSP_CHECKVERSION			, ImEventCheckVersion)

// 登录
MACRO_DEFS(IM_REQ_LOGIN							, 0x01000003					, ImReqLogin)
MACRO_DEFR(IM_RSP_LOGIN							, 0x01010003					, ImRspLogin)
MACRO_DEF_EXTERN(IM_EVENT_LOGIN_STATUS			, IM_RSP_LOGIN					, ImEventLoginStatus)

// 重新登陆
MACRO_DEFS(IM_REQ_LOGIN_AGAIN					, 0x01000004					, ImReqLoginAgain) 
MACRO_DEFR(IM_RSP_LOGIN_AGAIN					, 0x01010004					, ImRspLoginAgain)

// 登录后继
MACRO_DEFS(IM_REQ_POSTLOGIN						, 0x01000005					, ImReqPostLogin)

// 断线重连
MACRO_DEFS(IM_REQ_RELOGIN						, 0x01000006					, ImReqReLogin)
MACRO_DEFR(IM_RSP_RELOGIN						, 0x01010006					, ImRspReLogin)
MACRO_DEF_EXTERN(IM_EVENT_RELOGIN				, IM_RSP_RELOGIN				, ImEventReLogin)

// 登出
MACRO_DEFS(IM_REQ_LOGOFF						, 0x01000007					, ImReqLogoff)
MACRO_DEFR(IM_RSP_LOGOFF						, 0x01010007					, ImRspLogoff)
//denx: 暂时不用
//MACRO_DEFR(IM_EVENT_LOGOFF						, IM_RSP_LOGOFF					, ImEventLogoff)

// 取联系人分组
MACRO_DEFS(IM_REQ_GETGROUP						, 0x01000008					, ImReqGetGroup)
MACRO_DEFR(IM_RSP_GETGROUP						, 0x01010008					, ImRspGetGroup)
MACRO_DEF_EXTERN(IM_EVENT_GETGROUP				, IM_RSP_GETGROUP				, ImEventGetGroup)

// 增加联系人分组
MACRO_DEFS(IM_REQ_ADDGROUP						, 0x01000009					, ImReqAddGroup)
MACRO_DEFR(IM_RSP_ADDGROUP						, 0x01010009					, ImRspAddGroup)

// 修改联系人分组
MACRO_DEFS(IM_REQ_CHGGROUP						, 0x0100000a					, ImReqChangeGroup)
MACRO_DEFR(IM_RSP_CHGGROUP						, 0x0101000a					, ImRspChangeGroup)

// 删除联系人分组
MACRO_DEFS(IM_REQ_DELGROUP						, 0x0100000b					, ImReqDeleteGroup)
MACRO_DEFR(IM_RSP_DELGROUP						, 0x0101000b					, ImRspDeleteGroup)

// 修改添加联系人检验标志
MACRO_DEFS(IM_REQ_CHGUSERVERIFY					, 0x0100000c					, ImReqChangeUserVerify)
MACRO_DEFR(IM_RSP_CHGUSERVERIFY					, 0x0101000c					, ImRspChangeUserVerify)
MACRO_DEF_EXTERN(IM_EVENT_CHGUSERVERIFY			, IM_RSP_CHGUSERVERIFY			, ImEventChanageUserVerify)

// 取联系人列表
MACRO_DEFS(IM_REQ_GETCONTACT					, 0x0100000d					, ImReqGetContact)
MACRO_DEFR(IM_RSP_GETCONTACT					, 0x0101000d					, ImRspGetContact)
MACRO_DEF_EXTERN(IM_EVENT_GETCONTACT			, IM_RSP_GETCONTACT				, ImEventGetContact)

// 增加联系人 //关键字是老的，但是命令是新的。
MACRO_DEFS(IM_REQ_ADDCONTACT					, 0x01000050					, ImReqAddContact)
MACRO_DEFR(IM_RSP_ADDCONTACT					, 0x01010050					, ImRspAddContact)
MACRO_DEF_EXTERN(IM_EVENT_ADDCONTACT			, IM_RSP_ADDCONTACT				, ImEventAddContact)

// 修改联系人
MACRO_DEFS(IM_REQ_CHGCONTACT					, 0x0100000f					, ImReqChangeContact)
MACRO_DEFR(IM_RSP_CHGCONTACT					, 0x0101000f					, ImRspChangeContact)

// 删除联系人
MACRO_DEFS(IM_REQ_DELCONTACT					, 0x01000010					, ImReqDeleteContact)
MACRO_DEFR(IM_RSP_DELCONTACT					, 0x01010010					, ImRspDeleteContact)
MACRO_DEF_EXTERN(IM_EVENT_DELCONTACT			, IM_RSP_DELCONTACT				, ImEventDeleteContact)

// 同意加为联系人
MACRO_DEFS(IM_REQ_ADDCNTACK						, 0x01000051					, ImReqAddContactACK)
MACRO_DEFR(IM_RSP_ADDCNTACK						, 0x01010051					, ImRspAddContactACK)
MACRO_DEF_EXTERN(IM_EVENT_ADDCNTACK				, IM_RSP_ADDCNTACK				, ImEventAddContactACK)

// 取联系人详细信息，也可以取自己的详细信息
MACRO_DEFS(IM_REQ_GETCNTDETAIL					, 0x01000012					, ImReqGetContactDetail)
MACRO_DEFR(IM_RSP_GETCNTDETAIL					, 0x01010012					, ImRspGetContactDetail)

// 修改登录用户自己的详细信息
MACRO_DEFS(IM_REQ_CHGUSERDETAIL					, 0x01000013					, ImReqChangeUserDetail)
MACRO_DEFR(IM_RSP_CHGUSERDETAIL					, 0x01010013					, ImRspChangeUserDetail)

// 取联系人备注信息
MACRO_DEFS(IM_REQ_GETCNTMEMO					, 0x01000014					, ImReqGetContactMemo)
MACRO_DEFR(IM_RSP_GETCNTMEMO					, 0x01010014					, ImRspGetContactMemo)
MACRO_DEF_EXTERN(IM_EVENT_GETCNTMEMO			, IM_RSP_GETCNTMEMO				, ImEventGetContactMemo)

// 修改联系人备注信息
MACRO_DEFS(IM_REQ_CHGCNTMEMO					, 0x01000015					, ImReqChangeContactMemo)
MACRO_DEFR(IM_RSP_CHGCNTMEMO					, 0x01010015					, ImRspChangeContactMemo)

// 取黑名单用户列表
MACRO_DEFS(IM_REQ_GETBLACK						, 0x01000016					, ImReqGetBlack)
MACRO_DEFR(IM_RSP_GETBLACK						, 0x01010016					, ImRspGetBlack)
MACRO_DEF_EXTERN(IM_EVENT_GETBLACK				, IM_RSP_GETBLACK				, ImEventGetBlack)

// 增加黑名单
MACRO_DEFS(IM_REQ_ADDBLACK						, 0x01000017					, ImReqAddBlack)
MACRO_DEFR(IM_RSP_ADDBLACK						, 0x01010017					, ImRspAddBlack)
MACRO_DEF_EXTERN(IM_EVENT_ADDBLACK				, IM_RSP_ADDBLACK				, ImEventAddBlack)

// 删除黑名单
MACRO_DEFS(IM_REQ_DELBLACK						, 0x01000018					, ImReqDeleteBlack)
MACRO_DEFR(IM_RSP_DELBLACK						, 0x01010018					, ImRspDeleteBlack)
MACRO_DEF_EXTERN(IM_EVENT_DELBLACK				, IM_RSP_DELBLACK				, ImEventDeleteBlack)

// 取反向黑名单列表
MACRO_DEFS(IM_REQ_GETREVBLACK					, 0x01000019					, ImReqGetReverseBlack)
MACRO_DEFR(IM_RSP_GETREVBLACK					, 0x01010019					, ImRspGetReverseBlack)
MACRO_DEF_EXTERN(IM_EVENT_GETREVBLACK			, IM_RSP_GETREVBLACK			, ImEventGetReverseBlack)

// 取用户个人信息
MACRO_DEFS(IM_REQ_GETUSERINFO					, 0x0100001a					, ImReqGetUserInfo)
MACRO_DEFR(IM_RSP_GETUSERINFO					, 0x0101001a					, ImRspGetUserInfo)
MACRO_DEF_EXTERN(IM_EVENT_GETUSERINFO			, IM_RSP_GETUSERINFO			, ImEventGetUserInfo)

// 取所有联系人状态
MACRO_DEFS(IM_REQ_GETCNTSTATUS					, 0x0100001b					, ImReqGetContactStatus) 
MACRO_DEFR(IM_RSP_GETCNTSTATUS					, 0x0101001b					, ImRspGetContactStatus) 
MACRO_DEF_EXTERN(IM_EVENT_GETCNTSTATUS			, IM_RSP_GETCNTSTATUS			, ImEventGetContactStatus)

// 状态变更
MACRO_DEFS(IM_REQ_CHGSTATUS						, 0x0100001c					, ImReqChangeStatus)

// 取离线消息
MACRO_DEFS(IM_REQ_GETOFFLINEMSG					, 0x0100001d					, ImReqGetOfflineMsg)
MACRO_DEFR(IM_RSP_GETOFFLINEMSG					, 0x0101001d					, ImRspGetOfflineMsg)
//MACRO_DEF_EXTERN(IM_EVENT_GETOFFLINEMSG			, IM_RSP_GETOFFLINEMSG			, ImEventGetOfflineMsg)

// 增加离线消息
MACRO_DEFS(IM_REQ_ADDOFFLINEMSG					, 0x0100001e					, ImReqAddOfflineMsg)

// 删除离线消息
MACRO_DEFS(IM_REQ_DELOFFLINEMSG					, 0x0100001f					, ImReqDeleteOfflineMsg)
MACRO_DEFR(IM_RSP_DELOFFLINEMSG					, 0x0101001f					, ImRspDeleteOfflineMsg)

// 取系统消息
MACRO_DEFS(IM_REQ_GETSYSTEMMSG					, 0x01000020					, ImReqGetSystemMsg) 
MACRO_DEFR(IM_RSP_GETSYSTEMMSG					, 0x01010020					, ImRspGetSystemMsg)

// 发送即时消息(一级协议)
MACRO_DEFS(IM_REQ_SENDIMMESSAGE					, 0x01000021					, ImReqSendIMMessage)

// 群发消息(一级协议)
MACRO_DEFS(IM_REQ_SENDMULTIUSERMSG				, 0x01000022					, ImReqSendMultiUserMsg)

// 升级普通联系人为好友
MACRO_DEFS(IM_REQ_UPGGENERALCONTACT				, 0x01000023					, ImReqUpdateGeneralContact)
MACRO_DEFR(IM_RSP_UPGGENERALCONTACT				, 0x01010023					, ImRspUpdateGeneralContact) 

// 取用户设置
MACRO_DEFS(IM_REQ_GETTOOLSPROFILE				, 0x01000024					, ImReqGetToolsProfile)
MACRO_DEFR(IM_RSP_GETTOOLSPROFILE				, 0x01010024					, ImRspGetToolsProfile)

// 修改用户设置
MACRO_DEFS(IM_REQ_CHGTOOLSPROFILE				, 0x01000025					, ImReqChangeToolsProfile)
MACRO_DEFR(IM_RSP_CHGTOOLSPROFILE				, 0x01010025					, ImRspChangeToolsProfile)

// 取用户信息（非联系人）
MACRO_DEFS(IM_REQ_PEERINFO						, 0x01000026					, ImReqGetPeerInfo)
MACRO_DEFR(IM_RSP_PEERINFO						, 0x01010026					, ImRspGetPeerInfo)
MACRO_DEF_EXTERN(IM_EVENT_PEERINFO				, IM_RSP_PEERINFO				, ImEventGetPeerInfo)

// 订阅对方状态/签名/头像变化
MACRO_DEFS(IM_REQ_SUBSCRIBE_INFO				, 0x01000027					, ImReqSubscribeInfo)
MACRO_DEFR(IM_RSP_SUBSCRIBE_INFO				, 0x01010027					, ImRspSubscribeInfo) 
MACRO_DEF_EXTERN(IM_EVENT_SUBSCRIBE_INFO		, IM_RSP_SUBSCRIBE_INFO			, ImEventSubscribeInfo)

// 取消临时订阅
MACRO_DEFS(IM_REQ_DISUBSCRIBE_INFO				, 0x01000028					, ImReqDisableSubscribeInfo)

// 头像变更通知
MACRO_DEFS(IM_REQ_CHGPORTRAIT					, 0x01000029					, ImReqChangePortrait)

// 修改个人签名
MACRO_DEFS(IM_REQ_CHGSIGNATURE					, 0x0100002a					, ImReqChangeSignature)
MACRO_DEFR(IM_RSP_CHGSIGNATURE					, 0x0101002a					, ImRspChangeSignature) 
MACRO_DEF_EXTERN(IM_EVENT_CHGSIGNATURE			, IM_RSP_CHGSIGNATURE			, ImEventChangeSignature)

// 增加网站绑定
MACRO_DEFS(IM_REQ_ADDBINDING					, 0x0100002b                    , ImReqAddBinding)
MACRO_DEFR(IM_RSP_ADDBINDING					, 0x0101002b                    , ImRspAddBinding) 

// 修改网站绑定
MACRO_DEFS(IM_REQ_CHGBINDING					, 0x0100002c                    , ImReqChangeBinding) 
MACRO_DEFR(IM_RSP_CHGBINDING					, 0x0101002c                    , ImRspChangeBinding)  

// 删除网站绑定
MACRO_DEFS(IM_REQ_DELBINDING					, 0x0100002d                    , ImReqDeleteBinding) 
MACRO_DEFR(IM_RSP_DELBINDING					, 0x0101002d                    , ImRspDeleteBinding)  

// 获得所有绑定
MACRO_DEFS(IM_REQ_GETBINDING					, 0x0100002e                    , ImReqGetBinding) 
MACRO_DEFR(IM_RSP_GETBINDING					, 0x0101002e                    , ImRspGetBinding) 

// 能否通过关键字搜索
MACRO_DEFS(IM_REQ_CANKEYSEARCH					, 0x0100002f                    , ImReqCanKeySearch)

// 取部分用户ID的状态
MACRO_DEFS(IM_REQ_GETUSERSSTATUS				, 0x01000031                    , ImReqGetUsersStatus)
MACRO_DEFR(IM_RSP_GETUSERSSTATUS				, 0x01010031                    , ImRspGetUsersStatus) 

// 预登录
MACRO_DEFS(IM_REQ_PRELOGIN						, 0x01000032                    , ImReqPreLogin)
MACRO_DEFS(IM_REQ_PRELOGIN1						, 0x01000041					, ImReqPreLogin)

MACRO_DEFS(IM_REQ_LOGIN2						, 0x01000042					, ImReqLogin2)
MACRO_DEFR(IM_RSP_LOGIN2						, 0x01010042					, ImRspLogin2)
MACRO_DEF_EXTERN(IM_EVENT_LOGIN2				, IM_RSP_LOGIN2					, ImEventLogin2)

// 重新预登录
MACRO_DEFS(IM_REQ_PRELOGIN_AGAIN				, 0x01000033                    , ImReqPreLoginAgain) 

// 取登陆网站的SessionCookie
MACRO_DEFS(IM_REQ_GETWEB_SESSION				, 0x01000034                    , ImReqGetWebSession)
MACRO_DEFR(IM_RSP_GETWEB_SESSION				, 0x01010034                    , ImRspGetWebSession)
MACRO_DEF_EXTERN(IM_EVENT_GETWEBSESSION			, IM_RSP_GETWEB_SESSION			, ImEventGetWebSession)

// 取用户UDB个人信息
MACRO_DEFS(IM_REQ_GET_USERUDBPROFILE			, 0x01000035                    , ImReqGetUserUDBProfile)
MACRO_DEFR(IM_RSP_GET_USERUDBPROFILE			, 0x01010035                    , ImRspGetUserUDBProfile)
MACRO_DEF_EXTERN(IM_EVENT_GETUSERUDBPROFILE		, IM_RSP_GET_USERUDBPROFILE		, ImEventGetUserUDBProfile)

// Search user
MACRO_DEFS(IM_REQ_SEARCHUSER					, 0x01000061                    , ImReqSearchUser)
MACRO_DEFR(IM_RSP_SEARCHUSER					, 0x01010061                    , ImRspSearchUser)
MACRO_DEF_EXTERN(IM_EVENT_SEARCHUSER			, IM_RSP_SEARCHUSER				, ImEventSearchUser)


// 取用户的等级
MACRO_DEFS(IM_REQ_GET_DEGREE					, 0x1000039						, ImReqGetDegree)
MACRO_DEFR(IM_RSP_GET_DEGREE					, 0x1010039						, ImRspGetDegree)
MACRO_DEF_EXTERN(IM_EVENT_GETDEGREE				, IM_RSP_GET_DEGREE				, ImEventGetDegree)

// 取是否验证标志
MACRO_DEFS(IM_REQ_GET_PEER_VERIFY_CONFIG		, 0x01000036                    , ImReqGetPeerVerifyConfig)
MACRO_DEFR(IM_RSP_GET_PEER_VERIFY_CONFIG		, 0x01010036                    , ImRspGetPeerVerifyConfig) 
MACRO_DEF_EXTERN(IM_EVENT_GETPEERVERIFYCONFIG	, IM_RSP_GET_PEER_VERIFY_CONFIG	, ImEventGetUserVerifyConfig)

MACRO_DEFS(IM_REQ_GET_APP_ADDR					, 0x01000090					, ImReqGetAppAddr)
MACRO_DEFR(IM_RSP_GET_APP_ADDR					, 0x01010090					, ImRspGetAppAddr)
MACRO_DEF_EXTERN(IM_EVENT_GET_APP_ADDR			, IM_RSP_GET_APP_ADDR			, ImEventGetAppAddr)

// 获取密码token
MACRO_DEFS(IM_REQ_GET_PWDTOKEN					, 0x01000037                    , ImReqGetPwdToken) 
MACRO_DEFR(IM_RSP_GET_PWDTOKEN					, 0x01010037                    , ImRspGetPwdToken)

// 校验验证码
MACRO_DEFS(IM_REQ_CHECK_AUTHCODE				, 0x01000040                    , ImReqCheckAuthCode) 
MACRO_DEFR(IM_RSP_CHECK_AUTHCODE				, 0x01010040                    , ImRspCheckAuthCode)
MACRO_DEF_EXTERN(IM_EVENT_CHECK_AUTHCODE		, IM_RSP_CHECK_AUTHCODE			, ImEventCheckAuthCode)

// 登录在线客服系统
MACRO_DEFS(IM_REQ_HELP_LOGIN					, 0x01001001                    , ImReqHelpLogin) 
MACRO_DEFR(IM_RSP_HELP_LOGIN					, 0x01010001                    , ImRspHelpLogin)  
MACRO_DEF_EXTERN(IM_EVENT_HELP_LOGIN			, IM_RSP_HELP_LOGIN				, ImEventHelpLogin)

// 拒绝服务/取消拒绝服务
MACRO_DEFS(IM_REQ_HELP_CHG_SRV_MODE				, 0x01001042                    , ImReqHelpChangeSrvMode) 
//MACRO_DEFR(IM_RSP_HELP_CHG_SRV_MODE				, 0x01011042                    , ImRspHelpChangeSrvMode)
MACRO_DEF_EXTERN(IM_EVENT_HELP_CHG_SRV_MODE		, 0x01011042					, ImEventHelpChgSrvMode)

// 设置好友分流
MACRO_DEFS(IM_REQ_HELP_SET_SHARE_CID			, 0x01001003                    , ImReqHelpSetShareCID) 
MACRO_DEFR(IM_RSP_HELP_SET_SHARE_CID			, 0x01010003                    , ImRspHelpSetShareCID)

// 查询某好友是否分流
MACRO_DEFS(IM_REQ_HELP_GET_SHARE_CID			, 0x01001004                    , ImReqHelpGetShareCID)
MACRO_DEFR(IM_RSP_HELP_GET_SHARE_CID			, 0x01010004                    , ImRspHelpGetShareCID)

// 查询子帐号是否真实
MACRO_DEFS(IM_REQ_HELP_GET_CHILD_ONLINE			, 0x01001005                    , ImReqHelpGetChildOnline)
MACRO_DEFR(IM_RSP_HELP_GET_CHILD_ONLINE			, 0x01010005                    , ImRspHelpGetChildOnline)

// 取在线子帐号(非离线)
MACRO_DEFS(IM_REQ_HELP_GET_ONLINECHILDS			, 0x01001006                    , ImReqHelpGetOnlineChilds)
MACRO_DEFR(IM_RSP_HELP_GET_ONLINECHILDS			, 0x01010006                    , ImRspHelpGetOnlineChilds)

// 取开通的功能列表
MACRO_DEFS(IM_REQ_HELP_GET_SERVICES				, 0x01001007                    , ImReqHelpGetServices)
MACRO_DEFR(IM_RSP_HELP_GET_SERVICES				, 0x01010007                    , ImRspHelpGetServices)

// 取绑定到的人
MACRO_DEFS(IM_REQ_HELP_GET_BIND_TO				, 0x01001008                    , ImReqHelpGetBindTo)
MACRO_DEFR(IM_RSP_HELP_GET_BIND_TO				, 0x01010008                    , ImRspHelpGetBindTo)

// 向联系人发送消息
MACRO_DEFS(IM_REQ_SEND_WATCH_INFO				, 0x0100005e                    , ImReqSendWatchInfo)

// 获取SIP SESSION ID
MACRO_DEFS(IM_REQ_GET_SIP_SESSIONID				, 0x01000060                    , ImReqGetSIPSessionID)
MACRO_DEFR(IM_RSP_GET_SIP_SESSIONID				, 0x01010060                    , ImRspGetSIPSessionID)
 
//notify命令上报
MACRO_DEFR(IM_NTF_LOGIN_AGAIN					, 0x01020004                    , ImNtfLoginAgain)

MACRO_DEFR(IM_NTF_FORCEDISCONNECT				, 0x01020005                    , ImNtfForceDisconnect)
MACRO_DEF_EXTERN(IM_EVENT_FORCEDISCONNECT		, IM_NTF_FORCEDISCONNECT		, ImEventNtfForceDisconnect)

MACRO_DEFR(IM_NTF_BINDID_KICKED					, 0x01020106					, ImNtfBindIDKicked)
MACRO_DEF_EXTERN(IM_EVENT_BINDID_KICKED			, IM_NTF_BINDID_KICKED			, ImEventNtfBindIDKicked)

MACRO_DEFR(IM_NTF_STATUS						, 0x0102000f                    , ImNtfStatus)		
MACRO_DEF_EXTERN(IM_EVENT_STATUS				, IM_NTF_STATUS					, ImEventNtfStatus)

MACRO_DEFR(IM_NTF_IMMESSAGE						, 0x01020010                    , ImNtfIMMessage)
//MACRO_DEF_EXTERN(IM_EVENT_IMMESSAGE				, IM_NTF_IMMESSAGE				, ImEventNtfIMMessage)

MACRO_DEFR(IM_NTF_SYSTEMMESSAGE					, 0x01020011                    , ImNtfSystemMessage)
MACRO_DEF_EXTERN(IM_EVENT_SYSTEMMESSAGE			, IM_NTF_SYSTEMMESSAGE			, ImEventNtfSystemMessage)

MACRO_DEFR(IM_NTF_OPERATIONTIP					, 0x0102002b                    , ImNtfOperationTip)

MACRO_DEFR(IM_NTF_UPDATE_USREXTINFO				, 0x0102002c                    , ImNtfUpdateUsrExtInfo)
MACRO_DEF_EXTERN(IM_EVENT_UPDATEUSREXTINFO		, IM_NTF_UPDATE_USREXTINFO		, ImEventNtfUpdateUsrExtInfo)

MACRO_DEFR(IM_NTF_SUBSCRIBE_MSG					, 0x0102002d                    , ImNtfSubscribeMsg)
MACRO_DEF_EXTERN(IM_EVENT_SUBCRIBE_MSG			, IM_NTF_SUBSCRIBE_MSG			, ImEventNtfSubscribeMsg)

MACRO_DEFR(IM_NTF_REFRESH_CONTACT				, 0x01020030                    , ImNtfRefreshContact)

MACRO_DEFR(IM_NTF_FEEDS							, 0x01020031                    , ImNtfFeeds)

MACRO_DEFR(IM_NTF_USER_SNSINFO					, 0x01020032                    , ImNtfUserSnsInfo)

MACRO_DEFR(IM_NTF_NEED_AUTHCODE					, 0x01020040                    , ImNtfNeedAuthCode)

MACRO_DEFR(IM_NTF_EXTINFO_MSG					, 0x0102005d                    , ImNtfExitInfoMsg)

MACRO_DEFR(IM_NTF_WATCH_INFO					, 0x0102005e                    , ImNtfWatchInfo)

MACRO_DEFR(IM_NTF_WEBUSERMESSAGE				, 0x01020101                    , ImNtfWebUserMessage)
MACRO_DEF_EXTERN(IM_EVENT_WEBUSERMESSAGE		, IM_NTF_WEBUSERMESSAGE			, ImEventNtfWebUserMessage)


//IM消息二级协议命令字
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_TEXT			        , 0x0)	//! 即时聊天消息
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_BUZZ			        , 0x1)	//! 震动
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_P2P				    , 0x2)	//!	P2P模块相关的IMS信息交互消息
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_AUTO_REPLY		        , 0x3)	//! 自动回复
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_MSG_ACK			    , 0x4)	//! 消息接收确认
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_CONTACT			    , 0x5)	//! 添加联系人相关

	//! 添加联系人相关的二级的二级协议
	MACRO_DEF_SECOND_PROTOCOL(IMM_CONTACT_ADDED             , 0x301) //不需验证的添加
	MACRO_DEF_SECOND_PROTOCOL(IMM_CONTACT_IGNOREUSER_ADDED  , 0x302) //阻止用户添加（黑名单）
	MACRO_DEF_SECOND_PROTOCOL(IMM_CONTACT_IGNOREUSER_DELED  , 0x303) //取消阻止用户
	MACRO_DEF_SECOND_PROTOCOL(IMM_CONTACT_ASKADD_REQ        , 0x310) //发出添加请求验证
	MACRO_DEF_SECOND_PROTOCOL(IMM_CONTACT_ASKADD_NO         , 0x311) //答复请求验证，拒绝
	MACRO_DEF_SECOND_PROTOCOL(IMM_CONTACT_ASKADD_YES        , 0x312) //答复请求验证，同意

MACRO_DEF_SECOND_PROTOCOL(IMM_SP_NOTIFY			        , 0x6)	//! 通知消息,比如对方正在输入消息
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_GROUP_BROADCAST        , 0x7)	//! 收到的群发消息(注意此消息只能被用于接收不能发送)
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_PLUGINS_QUERY	        , 0x8)	//! 插件查询命令
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_PLUGINS_RESPONSE       , 0x9)	//! 插件查询命令的应答
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_PLUGINS_INVITE	        , 0xa)	//! 插件邀请使用
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_CUSTOM_MESSAGE	        , 0xb)	//! 关于自定义消息(还没有定义好)
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_FOCUS_TALK		        , 0xc)	//! 即时焦点
MACRO_DEF_SECOND_PROTOCOL(IMM_SP_OFFIMG					, 0x22)	//! 离线贴图传输通知

//add by pw for video chat, 2011-7-12
MACRO_DEF_SECOND_PROTOCOL(IMM_VIDEOCHAT_INVITE_REQUEST	, 0x90)	//! 发起视频聊天邀请
MACRO_DEF_SECOND_PROTOCOL(IMM_VIDEOCHAT_INVITE_CANCEL	, 0x91)	//! 取消视频聊天邀请
MACRO_DEF_SECOND_PROTOCOL(IMM_VIDEOCHAT_INVITE_RESPONSE , 0x92)	//! 回应聊天邀请
MACRO_DEF_SECOND_PROTOCOL(IMM_VIDEOCHAT_FINISH	, 0x93)			//! 关闭视频聊天

//以下是群的协议，其中,TRIBEGROUP的协议不处理

MACRO_DEFS( IM_REQ_GET_TRIBEGROUP 				, 0x06000001					, ImReqGetTribeGroup)
MACRO_DEFR( IM_RSP_GET_TRIBEGROUP 				, 0x06010001					, ImRspGetTribeGroup)

MACRO_DEFS( IM_REQ_ADD_TRIBEGROUP 				, 0x06000002					, ImReqGetAddTribeGroup)
MACRO_DEFR( IM_RSP_ADD_TRIBEGROUP 				, 0x06010002					, ImRspGetAddTribeGroup)

MACRO_DEFS( IM_REQ_UPDATE_TRIBEGROUP		 	, 0x06000003					, ImReqUpdateTribeGroup)	
MACRO_DEFR( IM_RSP_UPDATE_TRIBEGROUP		 	, 0x06010003					, ImRspUpdateTribeGroup)

MACRO_DEFS( IM_REQ_DEL_TRIBEGROUP 				, 0x06000004					, ImReqDelTribeGroup)
MACRO_DEFR( IM_RSP_DEL_TRIBEGROUP 				, 0x06010004					, ImRspDelTribeGroup)



MACRO_DEFS( IM_REQ_SHALLOW_LOGINTRIBE 			, 0x06000005					, ImReqShallowLoginTribe)
MACRO_DEFR( IM_RSP_SHALLOW_LOGINTRIBE 			, 0x06010005					, ImRspShallowLoginTribe)

MACRO_DEFS( IM_REQ_DEEP_LOGINTRIBE 				, 0x06000006					, ImReqDeepLoginTribe)
MACRO_DEFR( IM_RSP_DEEP_LOGINTRIBE 				, 0x06010006					, ImRspDeepLoginTribe)

MACRO_DEFS( IM_REQ_INVITE_TRIBE 				, 0x06000007					, ImReqInviteTribe)
MACRO_DEFR( IM_RSP_INVITE_TRIBE 				, 0x06010007					, ImRspInviteTribe)

MACRO_DEFS( IM_REQ_ONINVITE_JOINTRIBE 			, 0x06000008					, ImReqOnInviteJoinTribe)
MACRO_DEFR( IM_RSP_ONINVITE_JOINTRIBE 			, 0x06010008					, ImRspOnInviteJoinTribe)

MACRO_DEFS( IM_REQ_ASK_JOINTRIBE 				, 0x06000009					, ImReqAskJoinTribe)
MACRO_DEFR( IM_RSP_ASK_JOINTRIBE 				, 0x06010009					, ImRspAskJoinTribe)

MACRO_DEFS( IM_REQ_EXAM_ASKJOINTRIBE			, 0x0600000A					, ImReqExamAskJoinTribe)
MACRO_DEFR( IM_RSP_EXAM_ASKJOINTRIBE			, 0x0601000A					, ImRspExamAskJoinTribe)

MACRO_DEFS( IM_REQ_CHGLEVEL_TRIBEMEMBER 		, 0x0600000B					, ImReqChgLevelTribeMember)
MACRO_DEFR( IM_RSP_CHGLEVEL_TRIBEMEMBER 		, 0x0601000B					, ImRspChgLevelTribeMember)

MACRO_DEFS( IM_REQ_CHG_TRIBEGROUP 				, 0x0600000C					, ImReqChgTribeGroup)
MACRO_DEFR( IM_RSP_CHG_TRIBEGROUP 				, 0x0601000C					, ImRspChgTribeGroup)

MACRO_DEFS( IM_REQ_ADD_STARMEMBER 				, 0x0600000D					, ImReqAddStarMember)
MACRO_DEFR( IM_RSP_ADD_STARMEMBER 				, 0x0601000D					, ImRspAddStarMember)

MACRO_DEFS( IM_REQ_DEL_STARMEMBER 				, 0x0600000E					, ImReqDelStarMember)
MACRO_DEFR( IM_RSP_DEL_STARMEMBER 				, 0x0601000E					, ImRspDelStarMember)

MACRO_DEFS( IM_REQ_DEL_TRIBEMEMBER		 		, 0x0600000F					, ImReqDelTribeMember)
MACRO_DEFR( IM_RSP_DEL_TRIBEMEMBER		 		, 0x0601000F					, ImRspDelTribeMember)

MACRO_DEFS( IM_REQ_GET_TRIBEBLACK 				, 0x06000010					, ImReqGetTribeBlack)
MACRO_DEFR( IM_RSP_GET_TRIBEBLACK 				, 0x06010010					, ImRspGetTribeBlack)

MACRO_DEFS( IM_REQ_ADD_TRIBEBLACK 				, 0x06000011					, ImReqAddTribeBlack)
MACRO_DEFR( IM_RSP_ADD_TRIBEBLACK 				, 0x06010011					, ImRspAddTribeBlack)

MACRO_DEFS( IM_REQ_DEL_TRIBEBLACK 				, 0x06000012					, ImReqDelTribeBlack)
MACRO_DEFR( IM_RSP_DEL_TRIBEBLACK 				, 0x06010012					, ImRspDelTribeBlack)

MACRO_DEFS( IM_REQ_QUIT_TRIBE 					, 0x06000013					, ImReqQuitTribe)
MACRO_DEFR( IM_RSP_QUIT_TRIBE 					, 0x06010013					, ImRspQuitTribe)

MACRO_DEFS( IM_REQ_CLOSE_TRIBE			 		, 0x06000014					, ImReqCloseTribe)
MACRO_DEFR( IM_RSP_CLOSE_TRIBE			 		, 0x06010014					, ImRspCloseTribe)

MACRO_DEFS( IM_REQ_GET_TRIBEINFO 				, 0x06000015					, ImReqGetTribeInfo)
MACRO_DEFR( IM_RSP_GET_TRIBEINFO 				, 0x06010015					, ImRspGetTribeInfo)

MACRO_DEFS( IM_REQ_MODIFY_TRIBE 				, 0x06000016					, ImReqModifyTribe)
MACRO_DEFR( IM_RSP_MODIFY_TRIBE 				, 0x06010016					, ImRspModifyTribe)

MACRO_DEFS( IM_REQ_GET_TRIBEMEMBERINFO 			, 0x06000017					, ImReqGetTribeMemberInfo)
MACRO_DEFR( IM_RSP_GET_TRIBEMEMBERINFO 			, 0x06010017					, ImRspGetTribeMemberInfo)

MACRO_DEFS( IM_REQ_SEND_TRIBEMSG 				, 0x06000018					, ImReqSendTribeMsg)
MACRO_DEFR( IM_RSP_SEND_TRIBEMSG 				, 0x06010018					, ImRspSendTribeMsg)

MACRO_DEFS( IM_REQ_GET_TRIBE_CONFIG 			, 0x06000019					, ImReqGetTribeConfig)
MACRO_DEFR( IM_RSP_GET_TRIBE_CONFIG 			, 0x06010019					, ImRspGetTribeConfig)

MACRO_DEFS( IM_REQ_SET_TRIBE_CONFIG 			, 0x0600001A					, ImReqSetTribeConfig)
MACRO_DEFR( IM_RSP_SET_TRIBE_CONFIG 			, 0x0601001A					, ImRspSetTribeConfig)

MACRO_DEFS( IM_REQ_SET_OPEN_TRIBE 				, 0x0600001B					, ImReqSetOpenTribe)
MACRO_DEFR( IM_RSP_SET_OPEN_TRIBE 				, 0x0601001B					, ImRspSetOpenTribe)

MACRO_DEFS( IM_REQ_VISIT_TRIBE 					, 0x0600001C					, ImReqVisitTribe)
MACRO_DEFR( IM_RSP_VISIT_TRIBE 					, 0x0601001C					, ImRspVisitTribe)

MACRO_DEFS( IM_REQ_CLEAR_VISITOR 				, 0x0600001D					, ImReqClearVisitor)
MACRO_DEFR( IM_RSP_CLEAR_VISITOR 				, 0x0601001D					, ImRspClearVisitor)

MACRO_DEFS( IM_REQ_START_TRIBE 					, 0x0600001E					, ImReqStartTribe)
MACRO_DEFR( IM_RSP_START_TRIBE 					, 0x0601001E					, ImRspStartTribe)

MACRO_DEFS( IM_REQ_RECOMMEND_TRIBE 				, 0x06000024					, ImReqRecommendTribe)
MACRO_DEFR( IM_RSP_RECOMMEND_TRIBE 				, 0x06010024					, ImRspRecommendTribe)

MACRO_DEFS( IM_REQ_AUTH_RECOMMEND 				, 0x06000025					, ImReqAuthRecommend)
MACRO_DEFR( IM_RSP_AUTH_RECOMMEND 				, 0x06010025					, ImRspAuthRecommend)

MACRO_DEFS( IM_REQ_UPDATE_TRIBECARD 			, 0x0600003B					, ImReqUpdateTribeCard)
MACRO_DEFR( IM_RSP_UPDATE_TRIBECARD 			, 0x06010035					, ImRspUpdateTribeCard)


MACRO_DEFR( IM_NTF_INVITE_TRIBE 				, 0x06020007					, ImNtfInviteTribe)
MACRO_DEFR( IM_NTF_ASK_JOINTRIBE 				, 0x06020009					, ImNtfAskJoinTribe)
MACRO_DEFR( IM_NTF_TRIBEMSG 					, 0x06020015					, ImNetTribeMsg)
MACRO_DEFR( IM_NTF_TRIBE_SYSMSG 				, 0x06020017					, ImNtfTribeSysmsg)
MACRO_DEFR( IM_NTF_RECOMMEND_TRIBE 				, 0x06020024					, ImNtfRecommendTribe)
// add by pw 2011-07-12 获取绑定电话
//MACRO_DEFS(IM_REQ_GET_CN_EXTRAINFO			, 0x01000171					, ImReqGetCNExtraInfo)
MACRO_DEFR(IM_RSP_GET_CN_EXTRAINFO				, 0x01010171					, ImRspGetCNExtraInfo)
MACRO_DEF_EXTERN(IM_EVENT_GET_CN_EXTRAINFO		, IM_RSP_GET_CN_EXTRAINFO		, ImEventGetCNExtraInfo)

// add by pw 2011-07-19 获取绑定淘宝帐号
MACRO_DEFS(IM_REQ_GETWEBBINDING					, 0x01000100					, ImReqGetWebBinding)
MACRO_DEFR(IM_RSP_GETWEBBINDING					, 0x01010100					, ImRspGetWebBinding)
MACRO_DEF_EXTERN(IM_EVENT_GETWEBBINDING			, IM_RSP_GETWEBBINDING			, ImEventGetWebBinding)

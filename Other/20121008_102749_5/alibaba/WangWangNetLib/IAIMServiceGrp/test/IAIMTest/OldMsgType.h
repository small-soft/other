#ifndef __OLDMSGTYPE_H__
#define __OLDMSGTYPE_H__

typedef enum _AIMsgType
{
	CNT_MESSAGE_SENT = 0,				//本处发出的消息，消息联系人是消息的接受着
	CNT_MESSAGE_RECEIVED = 1,			//本处收到的消息，消息联系人是消息的发送者
	AUTO_REPLAY_CNT_MESSAGE = 2,		//收到的自动回复消息，消息的联系人是消息的发送者
	SUBSCRIBE_MESSAGE = 3,				//订阅消息  7777
	SYSTEM_MESSAGE = 4,					//系统消息  7777

	//以下为系统事件消息  
	ADD_CNT_SUCCESS = 10,				//加好友成功，联系人是所加好友 7777
	ADD_CNT_FAILED = 11,				//加好友失败，消息内容是失败的原因码（详见下面的szAddCntFailInfo）
	ADD_CNT_NEED_REQ = 12,				//添加好友时对方需要验证，收到此消息，应该向对应联系人发送验证请求  7777
	ADDED_BY_PEER = 13,					//被某联系人添加为好友   7777
	REQ_FROM_PEER = 14,					//来自于某联系人的验证请求；消息内容是请求的详细信息 7777
	//
	DECLINED_BY_PEER = 15,				//被某联系人拒绝（为己方发送出验证请求后收到的回复） 7777
	ACCEPTED_BY_PEER = 16,				//被联系人接受（为己方发送出验证请求后收到的回复）  7777
	ADD_BLK_SUCCESS,					//添加黑名单成功
	ADD_BLK_FAILED,						//添加黑名单失败
	REMOVE_BLK_SUCESS,					//移除黑名单成功
	REMOVE_BLK_FAILED,					//移除黑名单失败
	REMOVE_CNT_SUCESS,					//移除联系人成功
	REMOVE_CNT_FAILED,					//移除联系人失败
	ADD_CNT_WAIT_VERIFY,				//正在等待对方的验证（为己方发送出验证请求后收到的回复） 7777
	CHG_VERIFY_OK,						//修改验证状态成功	content为"0"(不需要验证)"1"(需要验证)或"2"(不允许添加)  
	CHG_VERIFY_FAILE,					//修改验证状态失败
	CHG_SIGNATURE_OK,					//修改签名成功		content为当前的签名
	CHG_SIGNATURE_FAIL,					//修改签名失败
	GET_PEER_ADD_VERIFY,				//获取联系人VerifyConfig成功		content为好友验证状态flag, 0不需要验证，1需要验证，2不让加好友，3好友不存在
	MSG_TYPE_TMP,						//不会出现
	GET_PEER_UDB_PROFILE = 30,			//Udb Profile content为偶数个字符串，一键一值排列
	GET_DEGREE_OK,						//获取联系人等级， content为以','分割的三个整数，分别为：等级、总活跃度、升级需要活跃度
	GET_DEGREE_FAIL,
	GET_PEER_SEND_VERIFY,
	HELP_LOGIN_OK,						//contact为parentId, content是以','分割的多个子账号
	HELP_LOGIN_FAIL,					//
	CHG_SERV_MODE_OK,					//修改E客服挂起状态成功
	CHG_SERV_MODE_FAIL,
	GET_CNTMEMO_OK,						//获取我对好友的备注
	GET_CNTMEMO_FAIL

} AIM_MSG_TYPE_OLD;

#endif //__OLDMSGTYPE_H__
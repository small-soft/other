
//
//  CallBackTool.h
//  WangWang
//
//  Created  by littlejie chan on 10-6-3.
//  Modified by tom.lih  on 2012-6-12.
//  Copyright 1999 alibaba. All rights reserved.
//


#import <Foundation/Foundation.h>
#include "CSimpleWangWangNetCallback.mm"

@interface CallBackTool : NSObject {	
	CSimpleWangWangNetCallback *pCallBack;	
	CWangWangNetLib wangwangNetLib;
}

@property (nonatomic,assign) CWangWangNetLib wangwangNetLib;

+ (CallBackTool *)create;

- (void) stop;

+ (void) destory;

- (void) reset;

/*!
 @method		userLogin:
 @abstract		传输资料至服务器进行登录
 @discussion	
 @param			_uid:传入帐号
 @param			_pwd:传入用户密码
 @param			_basicStatus:传入状态
 @result		User对象
 */
- (void) userLogin:(NSString *)_uid password:(NSString *)_pwd loginStatus:(EnLoginStatus)_loginStatus ;    

/*!
 @method		cancelLogin:
 @abstract		登录过程中取消登录
 @discussion	
 @param			
 @result
*/
- (void) cancelLogin;

/*!
 @method		logOff:
 @abstract		注销登录
 @discussion	
 @param			
 @result
*/
- (void) logOff;

- (void) startGetContactList;
- (void) startGetGroupList;
- (void) startGetContactStatusList;

/*!
 @method		getFriendStatus
 @abstract		获取某个好友的状态
 @discussion	
 @param			(NSString *)_uid  好友uid
 @result		
*/
- (void) getFriendStatus:(NSString *)_uid;

- (void) sendMessage:(NSString *)_msg uid:(NSString *)_uid;

/*!
 @method		setSelfDetail
 @abstract		设置个人详细资料
 @discussion	
 @param			
 @result		void
*/
- (void) setSelfDetail:(CContactPersonalDetailInfo&)detailInfo;


/*!
 @method		getUserDetail:
 @abstract		获取某帐号的详细信息
 @discussion	
 @param			_uid:帐号名
 @result
*/
- (void) getUserDetail:(NSString *)_uid;

- (void *) getSignature:(NSString *) _uid :(uint )_count;

/*!
 @method		changeSelfSignature
 @abstract		修改自己的签名
 @discussion	
 @param			(NSString *)signature:新签名
 @result		
*/
- (void) changeSelfSignature:(NSString *) _signature;

/*!
 @method		sendDeleteBlackUserToServer:
 @abstract		把删除黑名单的好友通知服务器
 @discussion	
 @param			(NSString *)_uid:关键字
 @result
*/
- (void) sendDeleteBlackUserToServer:(NSString *)_uid;

/*!
 @method		sendAddBlackToServer:
 @abstract		将好友加入黑名单的信息通知服务器
 @discussion	
 @param			(NSString *)_uid:关键字
 @result
*/
-(void) sendAddBlackToServer:(NSString *)_uid;


/*!
 @method		searchFriends:
 @abstract		搜索关键字相关的联系人
 @discussion	
 @param			_keywork:关键字
 @result
*/
- (void) searchFriends:(NSString *)_keyword;

/*!
 @method		addFriend:
 @abstract		添加好友
 @discussion	
 @param			_uid:好友uid
 @result
*/
- (void) addFriend:(NSString *)_uid;

/*!
 @method		sendAuthMessage:
 @abstract		如果对方设置为“加我为好友，需要我的验证“，这个接口则用来设置想对对方说的话，如表明自己的身份等等
 @discussion	
 @param			_uid:好友uid
 @param			_message:想对对方说的话
 @result
*/
- (void) sendAuthMessage:(NSString *)_uid message:(NSString *)_message;

/*!
 @method		changeAuthFlag
 @abstract		更改自己好友添加的验证方式
 @discussion	
 @param			(int) status;
 @result		
*/
- (void) changeAuthFlag:(int) _flag;

/*!
 @method		sendDeleteUserToServer:
 @abstract		把删除的好友通知服务器
 @discussion	
 @param			(NSString *)_uid:关键字
 @result
*/
- (void) sendDeleteUserToServer:(NSString *)_uid;

/*!
 @method		changeSelfStatus
 @abstract		更改自己的状态
 @discussion	
 @param			(int) status;
 @result		
*/
- (void) changeSelfStatus:(int) _status;

/*!
 @method		sendPicture:uid:
 @abstract		图片路径，uid
 @discussion	发送图片
 @param			
 @result		
*/
- (void) sendPicture:(NSString *)_picPath uid:(NSString *)_uid;

/*!
 @method		cancelSendPicture:_uid:
 @abstract		图片路径，uid
 @discussion	取消发送图片
 @param			
 @result		
*/
- (void) cancelSendPicture:(NSString *)_picPath uid:(NSString *)_uid;


/*!
 @method		handlePeerRequestSendPicture
 @abstract		处理对方发送贴图的请求:允许，拒绝，文件已经存在
 @discussion	
 @param			(NSString *)_uid  发图片给我的用户id
 @param			fileName:(NSString *)_fileName 图片的文件名
 @param			result:(int)_result 处理结果
 @param	        fileSavePath:(NSString *)_fileSavePath 图片保存的绝对路径。只有result为允许的时候，才有意义
 @result		
*/
- (void) handlePeerRequestSendPicture:(NSString *)_uid fileName:(NSString *)_fileName result:(int)_result fileSavePath:(NSString *)_fileSavePath;

/*!
 @method		cancelRecvPicture
 @abstract		取消贴图的接收
 @discussion	
 @param			(NSString *)_uid  发图片给我的用户id
 @param			fileName:(NSString *)_fileName 图片的文件名
 @result		
*/
- (void) cancelRecvPicture:(NSString *)_uid fileName:(NSString *)_fileName;

- (void) wwtest:(NSString *) _uid;

@end


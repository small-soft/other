//
//  CallBackTool.mm
//  WangWang
//
//  Created  by littlejie chan on 10-6-3.
//  Modified by tom.lih  on 2012-6-12.
//  Copyright 1999 alibaba. All rights reserved.
//


#import "CallBackTool.h"
#import "StringConversionUtils.h"
#import "NSString+HTML.h"
#import "LoginToken.h"
#import "AMIMUserDefault.h"

using namespace std;

@implementation CallBackTool

static CallBackTool *toolItem;

@synthesize wangwangNetLib;

+(CallBackTool *)create{
	if (toolItem == nil) {
		toolItem = [[CallBackTool alloc] init];
	}
	return toolItem;
}

inline void sig_do_nothing(int signo)
{
	return ;
}


-(id)init{
	if(self = [super init]){
        
		pCallBack = new CSimpleWangWangNetCallback();
		sigset_t newmask;
		sigset_t oldmask;
		signal(SIGPIPE, sig_do_nothing);
		sigemptyset(&newmask);
		sigaddset(&newmask, SIGPIPE);
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);  
        NSString *documentsDirectory = [paths objectAtIndex:0];  
        
        NSString * path = [NSString stringWithFormat:@"%@/WangWang.sqlite/", documentsDirectory]; 
		
        wangwangNetLib.Start(pCallBack, NSStr2CStr(path));
        
	}
	return self;
}

- (void) reset
{
    wangwangNetLib.Stop();
    
	delete pCallBack;
    pCallBack = new CSimpleWangWangNetCallback();
    sigset_t newmask;
    sigset_t oldmask;
    signal(SIGPIPE, sig_do_nothing);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGPIPE);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);  
    NSString *documentsDirectory = [paths objectAtIndex:0];  
    NSString * path = [NSString stringWithFormat:@"%@/WangWang.sqlite/", documentsDirectory]; 
    NSData * data_path = [path dataUsingEncoding:NSUTF8StringEncoding];
   
    wangwangNetLib.Start(pCallBack, NSStr2CStr(path) );
}

- (void) stop {
	wangwangNetLib.Stop();
}

+ (void) destory {
	if (toolItem != nil) {
		[toolItem dealloc];
        toolItem = nil;
	}
}

- (void) dealloc {
	wangwangNetLib.Stop();
    
	delete pCallBack;
    
	[super dealloc];
}

#pragma mark -
#pragma mark Server Interface
- (void) userLogin:(NSString *)_uid password:(NSString *)_pwd loginStatus:(EnLoginStatus)_loginStatus {
	CWangWangEnviroment wangwangEnv;
    
	wangwangEnv.m_strWangWangVersion = WangWangVersion;
	
    //	NSString *userid = [NSString stringWithFormat:@"%@%@", @"cnalichn", _uid];
	string strUid = NSStr2CStr(_uid);
	string strPassword =  NSStr2CStr(_pwd);
    
	CPassword password;
	password.m_strPassword = strPassword;
	password.m_passwordType = REAL_PASSWORD;
	
	//第一次登录，3个值都是0
	//根据时间戳，服务器会决定是否联系人关系有更新，第一次登录后，在回调接口（onreturngrouplist etc.)里有以下3个对应的时间戳
	//客户端本地应该保存起来，下次登录的时候传递进来	
    
    
	CContactsInfoTimestamp timestamp;
	
    AMIMUserDefault * user = [AMIMDefaultStorageHelper getLastLoginedUser];
    
	timestamp.m_groupListTimestamp = user.groupListTimestamp;
	timestamp.m_contactListTimestamp = user.friendListTimestamp;
    timestamp.m_blackListTimestamp = user.blackListTimestamp;
    //    timestamp.m_blackListTimestamp = 0;
    //    timestamp.m_groupListTimestamp = 0;
    //    timestamp.m_contactListTimestamp = 0;
	
	CContactStatus loginStatus;
	loginStatus.m_strUid = strUid;
	loginStatus.m_defaultPresence = _loginStatus;
	
	CLoginUserLoginInfo loginInfo;
	loginInfo.m_strUid = strUid;
	loginInfo.m_password = password;
	loginInfo.m_timestamp = timestamp;
	loginInfo.m_loginStatus = loginStatus;
	
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);  
    NSString *documentsDirectory = [paths objectAtIndex:0];  
    
    NSString * path = [NSString stringWithFormat:@"%@/WangWang.sqlite/", documentsDirectory]; 
    [[NSUserDefaults standardUserDefaults] setBool:FALSE forKey:@"ww_contact_data_ready"];
    [[NSUserDefaults standardUserDefaults] synchronize];
	wangwangNetLib.Login(pCallBack, NSStr2CStr(path),wangwangEnv, loginInfo);
	
}

- (void) logOff {
	wangwangNetLib.LogOff();
}


- (void) startGetGroupList{
	wangwangNetLib.RequestGetGroupList();
}

- (void) startGetContactList{
	wangwangNetLib.RequestGetContactList();
}

- (void) startGetContactStatusList{
	wangwangNetLib.RequestGetContactStatusList();
}

- (void) getFriendStatus:(NSString *)_uid {
	string uid = NSStr2CStr(_uid);
	wangwangNetLib.GetContactStatus(uid);
}

- (void) sendMessage:(NSString *)_msg uid:(NSString *)_uid{
	string msg = NSStr2CStr(_msg);
	string uid = NSStr2CStr(_uid);
	
	CTextMsg textMsg;
	textMsg.m_strTextContent = msg;
	textMsg.m_strPeerContactId = uid;
	textMsg.m_type = TEXT_MSG_NORMAL_TEXT;
    textMsg.m_nTime = [[NSDate date] timeIntervalSince1970];
    
	wangwangNetLib.SendTextMsg(textMsg);
}

- (void) setSelfDetail:(CContactPersonalDetailInfo&)detailInfo {
	wangwangNetLib.SetSelfDetailInfo(detailInfo);
}

- (void) getUserDetail:(NSString *)_uid {
	string uid = NSStr2CStr(_uid);
	wangwangNetLib.GetContactDetailInfo(uid);
}

- (void *) getSignature:(NSString *)_uid :(uint )_count{
    
    wangwangNetLib.GetSignature(NSStr2CStr(_uid), _count );    
}


- (void) changeSelfSignature:(NSString *) _signature {
	string signature = NSStr2CStr(_signature);
	wangwangNetLib.ChangeSelfSignature(signature);
}

-(void) sendAddBlackToServer:(NSString *)_uid
{
    string uid = NSStr2CStr(_uid);
    wangwangNetLib.AddContact2BlackList(uid);
}

- (void) sendDeleteBlackUserToServer:(NSString *)_uid
{
    string uid = NSStr2CStr(_uid);
    wangwangNetLib.DeleteBlackListContact(uid);
}


- (void) searchFriends:(NSString *)_keyword {
	string keyword = NSStr2CStr(_keyword);
	//wangwangNetLib.SearchConacts(keyword, wangwangNetLib.GetTickCount());
    wangwangNetLib.SearchConacts(keyword, 0);
}

- (void) addFriend:(NSString *)_uid {
	string uid = NSStr2CStr(_uid);
	wangwangNetLib.AddContact(uid);
}

- (void) sendAuthMessage:(NSString *)_uid message:(NSString *)_message  {
	string uid = NSStr2CStr(_uid);
	string message = NSStr2CStr(_message);
	wangwangNetLib.SendAddContactAuthenticationWords(uid, message);
}

- (void) changeAuthFlag:(int) _flag {
	EnAddedAuthFlag flag = EnAddedAuthFlag(_flag);
	wangwangNetLib.ChangeAddedAuthFlag(flag);
}

- (void) sendDeleteUserToServer:(NSString *)_uid
{
	string uid = NSStr2CStr(_uid);
	wangwangNetLib.DeleteContact(uid);
}

- (void) changeSelfStatus:(int) _status {
    
	wangwangNetLib.ChangeSelfStatus((EnDetailStatus)_status);
}

- (void) sendPicture:(NSString *)_picPath uid:(NSString *)_uid{
	string picPath = NSStr2CStr(_picPath);
	string uid = NSStr2CStr(_uid);
	
	wangwangNetLib.SendFile(uid, picPath);
}

- (void) cancelSendPicture:(NSString *)_picPath uid:(NSString *)_uid{
//	string picPath = NSStr2CStr(_picPath);
//	string uid = NSStr2CStr(_uid);
//	
//	wangwangNetLib.CancelSendPicture(uid, picPath);
}

- (void) handlePeerRequestSendPicture:(NSString *)_uid fileName:(NSString *)_fileName result:(int)_result fileSavePath:(NSString *)_fileSavePath {
//	string uid = NSStr2CStr(_uid);
//	string fileName = NSStr2CStr(_fileName);
//	EnPeerRequestSendPicResult result = (EnPeerRequestSendPicResult)_result;
//	string fileSavePath = NSStr2CStr(_fileSavePath);
//	if (result == ACCEPT_PEER_SEND_PIC) {
//		wangwangNetLib.HandlePeerRequestSendPicture(uid, fileName, result, fileSavePath);
//	} else {
//		wangwangNetLib.HandlePeerRequestSendPicture(uid, fileName, result, fileSavePath);
//	}
}

- (void) cancelRecvPicture:(NSString *)_uid fileName:(NSString *)_fileName {
//	string uid = NSStr2CStr(_uid);
//	string fileName = NSStr2CStr(_fileName);
//	wangwangNetLib.CancelRecvPicture(uid, fileName);
}

- (void) wwtest :(NSString *) _uid {
    
    wangwangNetLib.wwtest(NSStr2CStr(_uid)); 
    
}

@end

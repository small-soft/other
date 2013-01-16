
//
//  CSimpleWangWangNetCallback.mm
//
//  Created  by littlejie chan on 10-6-3.
//  Modified by tom.lih  on 2012-6-12.
//  Copyright 1999 alibaba. All rights reserved.
//


#import <Foundation/Foundation.h>

#import <WangWangNetLib/WangWangNetLib.h>
#import <WangWangNetLib/IAIMessage.h>
#import <WangWangNetLib/OldMsgType.h>

#import "NoticationItem.h"
#import "StringConversionUtils.h"
#import "InternetDataTool.h"
#import "AMAppDelegate.h"
#import "NSString+HTML.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMCoreDataHelper.h"
#import "StringUtils.h"
#import "AMIMGroupModel.h"
#import "AMIMUserDefault.h"


class CSimpleWangWangNetCallback: public IWangWangNetCallback
{
public:
	CSimpleWangWangNetCallback()
	{
        //		printf("CSimpleWangWangNetCallback constructor!\n");
	}
	
	~CSimpleWangWangNetCallback()
	{
        //		printf("CSimpleWangWangNetCallback destructor!\n");
	}
	
	////登录的步骤
	//目前分为2个步骤,检查版本号，验证
	//只有最后一个步骤走完，才认为是登录真正成功了
	//之所以提供详细的多个步骤，是提供给外部库一个机会，登录的时候向用户显示
	//当前登录正在做些什么事情,如果不需要此功能，直接处理最后一个步骤	
	virtual void OnLoginResult(int errCode,							
							   EnLoginStep loginStep,							
							   const CLoginFinalResult& loginFinalResult)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		///初始化返回通知数据对象
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
        
		NSLog(@"OnLoginResult: %d, errCode: %d", loginStep, errCode); 
        
		switch (loginStep)
		{
//			case STEP_CHECK_VERSION:
//			{
//
//			}
//				break;
                
			case STEP_AUTH:
			{	
                switch (errCode) {
					case RESULT_OKEY:
						NSLog(@"NO ERROR");
                        
                        m_loginFinalResult = loginFinalResult;
                        resultItem.name = [NSString stringWithFormat:@"%d",STEP_AUTH];
                        
                        [AMIMDefaultStorageHelper changeSelfGroupState:loginFinalResult.m_bGroupListUpdated friendState:loginFinalResult.m_bContactListUpdated blackState:loginFinalResult.m_bBlackListUpdated];
                        
						break;

                    default:
                        NSLog(@"ERROR: login failed!");
                        break;    
				}
				
				///赋值返回数据
				resultItem.errorCode = errCode;
				[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_WW_LOGIN_EVENT object:resultItem];
			}
				break;
			default:
				///返回数据为空，则抛出异常
				[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_WW_LOGIN_EVENT object:nil];
				break;
		}
		
		[pool release];
	}
	
	virtual void OnReturnGroupList(const GroupList_t& groupList, uint32_t nGroupListTimestamp) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
        
        [[AMIMCoreDataHelper getInstance] setGroupListWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]  groupList:groupList]; 
        
		[AMIMDefaultStorageHelper changeSelfGroupTimestamp:nGroupListTimestamp];
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_GROUPLIST object:nil];
		
		[pool release];
	}
    
    
	virtual void OnReturnContactList(const ContactList_t& contactList, uint32_t nContactListTimestamp)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
        [[AMIMCoreDataHelper getInstance] setFriendListWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]  friendList:contactList ];
        [AMIMDefaultStorageHelper changeSelfFriendTimestamp:nContactListTimestamp];
        
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CONTACTLIST object:nil];
        
		[pool release];	
	}

    virtual void OnReturnContactStatus(const ContactStatusList_t& contactStatusList) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
		for (ContactStatusList_t::const_iterator item = contactStatusList.begin(); item != contactStatusList.end(); item++) {
			NSNumber *cntStatus  = [NSNumber numberWithInt:item->m_defaultPresence];
            
            [[AMIMCoreDataHelper getInstance] changeUserStatusWithUid:CStr2NSStr(item->m_strUid) status:cntStatus.intValue ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];  
		}
		
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CONTACTSTATUSLIST object:nil];
        
		[pool release];	
	}
    
    virtual void OnReturnGetContactStatus(const CContactStatus& contactStatus) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		
        [[AMIMCoreDataHelper getInstance] changeUserStatusWithUid:CStr2NSStr(contactStatus.m_strUid) status:contactStatus.m_defaultPresence ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CONTACTSTATUSCHANGED object:nil];
		
		[pool release];
	}
    
    //添加联系人到黑名单里的返回结果
	//enErrCode = NO_ERROR表示操作成功，其他值都表示失败
	//只有操作成功，其他参数才有意义
	virtual void OnReturnAddBlack(int enErrCode, const std::string& strUid){
		
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.errorCode = enErrCode;
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ADDBLACK object:resultItem];
		[pool release];
		
	}
    
    //删除黑名单里的用户的回调接口
	virtual void OnDeleteBlackListContact(const std::string& strUid, int enErrCode) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.errorCode = enErrCode;
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DELETECONTACT object:resultItem];
		[pool release];
	}
    
    virtual void OnRecvSysMsg(const CTextMsg& sysMsg) {
        
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
        switch (sysMsg.m_type)
		{    
            
			case ADD_BLK_SUCCESS:
            {  
                // add black okey 
                OnReturnAddBlack(RESULT_OKEY, sysMsg.m_strPeerContactId);             
                
            }
                break;
                
			case  REMOVE_BLK_SUCESS:
            {  
                // remove black okey 
                OnDeleteBlackListContact(sysMsg.m_strPeerContactId, RESULT_OKEY);
            }
				break;
            
            case REMOVE_CNT_SUCESS:
            {  
                // remove cantact okey 
                OnReturnDeleteContact(RESULT_OKEY, sysMsg.m_strPeerContactId);
                
            }
                break;
                
            case  CHG_SIGNATURE_OK:
            {  
                
                OnChangeSelfSignature(RESULT_OKEY);
                
            }
				break;
            
            case  CHG_SIGNATURE_FAIL:
            {  
                OnChangeSelfSignature(RESULT_FAILED);
                
            }
				break;
                
			default:
				
				break;
                
		}
        
        [pool release];
        
        
    }
    
	///收到对方的文本消息
	virtual void OnRecvTextMsg(const CTextMsg& textMsg) {
        
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
		//不接受空信息和图片信息，图片信息另外处理
		if ([CStr2NSStr(textMsg.m_strTextContent) length] > 0 && textMsg.m_type != TEXT_MSG_PICTURE) {
            
            if(textMsg.m_type == TEXT_MSG_NORMAL_TEXT || textMsg.m_type == TEXT_MSG_AUTO_REPLY || textMsg.m_type == TEXT_MSG_CONTACT){
                NSString * owner = [AMIMDefaultStorageHelper getLastLoginedUserId];
                NSString * msgFrom = CStr2NSStr(textMsg.m_strPeerContactId);
                NSString * msgTo = [AMIMDefaultStorageHelper getLastLoginedUserId];
                NSNumber * msgType = [NSNumber numberWithInt:textMsg.m_type];
                NSNumber * msgSequence = [NSNumber numberWithInt:textMsg.m_nTextSequence];
                //by tom.lih
                NSString * msg = CStr2NSStr(textMsg.m_strTextContent);
 
                NSRange faceRange = [msg rangeOfString:@"\\T\/\:"];
                if(faceRange.location != NSNotFound){
                    msg = [msg stringByReplacingOccurrencesOfString:@"\\T" withString:@""];
                }
                
                faceRange = [msg rangeOfString:@"\\A0"];
                if(faceRange.location != NSNotFound){
                    msg = [msg stringByReplacingOccurrencesOfString:@"\\A0" withString:@""];
                }
                
                faceRange = [msg rangeOfString:@"\\A1"];
                if(faceRange.location != NSNotFound){
                    msg = [msg stringByReplacingOccurrencesOfString:@"\\A1" withString:@""];
                }
                
                NSNumber * hasRead = [NSNumber numberWithBool:NO];
                NSNumber * time = [NSNumber numberWithInt:textMsg.m_nTime];
                
                AMIMUserModel * msgUser = [[AMIMCoreDataHelper getInstance] getFriendWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] uid:msgFrom];
                if(msgUser == nil){
                    
                    [[AMIMCoreDataHelper getInstance] addUsesrWithUid:msgFrom nickname:[msgFrom substringFromIndex:8] groupId:[NSNumber numberWithInt:-2 ].stringValue ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
                    ;
                }
                
                
                [[AMIMCoreDataHelper getInstance] insertNewMsgWithOwnerId:owner msgFrom:msgFrom msgTo:msgTo msgType:msgType msgContent:[StringUtils returnRevMessageString:msg ] hasRead:hasRead msgTime:time msgSequence:msgSequence];
                [[AMIMCoreDataHelper getInstance] modifyContactTimeWithOwner:owner friendId:msgFrom msgTime:time];
                [[AMIMCoreDataHelper getInstance] saveData];
                
                
                AMAppDelegate *ww = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
                AMIMUserDefault * user = [AMIMDefaultStorageHelper getLastLoginedUser];
                if (user.soundNotice) {
                    [ww.soundEffect play];
                }
                if(user.shakeNotice){
                    [ww.soundEffect vibration];
                }
                

                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_REVMSG object:nil];
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_COUNTMSG object:nil];
                
                
            }
			
        }
		[pool release];
	}
    
    
    virtual void OnReturnLoginUserPersonalDetailInfo(const CContactPersonalDetailInfo& personalDetailInfo) {
		//没返回
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		[pool release];
	}
    
    virtual void OnReturnContactPersonalDetailInfo(CContactPersonalDetailInfo &detailInfo){
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NSString *birthday = CStr2NSStr(detailInfo.GetInfo(detailInfo.BIRTHDAY_INFO));
		if ([birthday length] > 10) {
			birthday = [birthday substringToIndex:10];
		}
		NSMutableDictionary *userDeatil = [NSDictionary dictionaryWithObjectsAndKeys:
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.UID_INFO)),NSLocalizedString(@"Member ID", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.DISPNAME_INFO)),NSLocalizedString(@"Name", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.GENDER_INFO)),NSLocalizedString(@"Gender", nil),
										   birthday,NSLocalizedString(@"Birthday", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.CONSTELLATION_INFO)),NSLocalizedString(@"Zodiac Sign", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.SHENGXIAO_INFO)),NSLocalizedString(@"Year of", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.COUNTRY_INFO)),NSLocalizedString(@"Country", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.PROVINCE_INFO)),NSLocalizedString(@"State/Province", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.CITY_INFO)),NSLocalizedString(@"City", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.MOBILEPHONE_INFO)),NSLocalizedString(@"Cell Phone", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.TELEPHONE_INFO)),NSLocalizedString(@"Tel", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.EMAIL_INFO)),NSLocalizedString(@"Email Address", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.CAREER_INFO)),NSLocalizedString(@"Occupation", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.GRADSCHOOL_INFO)),NSLocalizedString(@"School", nil),
										   CStr2NSStr(detailInfo.GetInfo(detailInfo.PERSONALWEBSITE_INFO)),NSLocalizedString(@"Homepage", nil),
										   nil];
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.data = userDeatil;
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_GETUSERDETAIL object:resultItem];
		
		[pool release];
	}
	
    
    //更改签名的返回值
	//NO_ERROR表示成功
	virtual void OnChangeSelfSignature(int enErrCode){
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.errorCode = enErrCode;
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CHANGESELFIGNATURE object:resultItem];
		[pool release];
	}
   
	//联系人的签名发生了变化
	//strContactId,签名发生变化的联系人id
	//strNewSignature, 新的签名
	virtual void OnContactSignatureChanged(const std::string& strContactId, const std::string& strNewSignature){		
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		NSString *user_uid = CStr2NSStr(strContactId);
		NSString *user_newSignature = [CStr2NSStr(strNewSignature) stringByDecodingHTMLEntities];
		resultItem.data=[NSMutableDictionary dictionaryWithObjectsAndKeys:
						 user_uid, @"user_uid",
						 user_newSignature,@"newSignature",nil];
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SIGNATURECHANGED object:resultItem];
		[pool release];
	}
    
    virtual void OnRecvOffLineMsgs(const TextMsgList_t&  offLineMsgs) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		
		for (TextMsgList_t::const_iterator item = offLineMsgs.begin(); item != offLineMsgs.end(); item++) {
            CTextMsg textMsg = *item;
            
            if(textMsg.m_type == TEXT_MSG_NORMAL_TEXT || textMsg.m_type == TEXT_MSG_AUTO_REPLY || textMsg.m_type == TEXT_MSG_CONTACT){
                NSString * owner = [AMIMDefaultStorageHelper getLastLoginedUserId];
                NSString * msgFrom = CStr2NSStr(textMsg.m_strPeerContactId);
                NSString * msgTo = [AMIMDefaultStorageHelper getLastLoginedUserId];
                NSNumber * msgType = [NSNumber numberWithInt:textMsg.m_type];
                NSNumber * msgSequence = [NSNumber numberWithInt:textMsg.m_nTextSequence];
                NSString * msg = CStr2NSStr(textMsg.m_strTextContent);
                NSNumber * hasRead = [NSNumber numberWithBool:NO];
                NSNumber * time = [NSNumber numberWithInt:textMsg.m_nTime];
                
                [[AMIMCoreDataHelper getInstance] insertNewMsgWithOwnerId:owner msgFrom:msgFrom msgTo:msgTo msgType:msgType msgContent:[StringUtils returnRevMessageString:msg ] hasRead:hasRead msgTime:time msgSequence:msgSequence];
                [[AMIMCoreDataHelper getInstance] modifyContactTimeWithOwner:owner friendId:msgFrom msgTime:time];
                [[AMIMCoreDataHelper getInstance] saveData];
                
            }
        }
        
        AMAppDelegate *ww = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        [ww.soundEffect play];
        [ww.soundEffect vibration];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_REVMSG object:nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_COUNTMSG object:nil];
		
		[pool release];
	}
	
	//得到离线添加好友请求
	virtual void OnRecvOfflineContactMsg(const std::string& strUid, const std::string& strMessage) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		[pool release];
	}
	
	//收到离线系统消息
	virtual void OnRecvOfflineSystemMsg(const std::string& strMessage) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		[pool release];
	}
    
    virtual void OnNtfDataReady(int iType) {
        if (iType == eDATA_ALLREADY) {
            [[NSUserDefaults standardUserDefaults] setBool:TRUE forKey:@"ww_contact_data_ready"];
            [[NSUserDefaults standardUserDefaults] synchronize];
            //[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_WW_LOGIN_DATAREADY object:nil];
        }
    }
    
    virtual void OnCallBackTest() {
        NSLog(@"call back test okey!");	
	}
    
    
    virtual void OnGetSignature(UidSignatures_t & uidSigs) {
        
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
        NSDictionary *dict;
        
        if (uidSigs.empty()) {
            dict = [NSDictionary dictionaryWithObjectsAndKeys:@"",@"uid",@"",@"signature",nil];
            
        } else {
            
            NSString *ns_uid;
            NSString *ns_signature;
            
            
            ns_uid =CStr2NSStr(uidSigs[0].m_strUid);
            ns_signature=[CStr2NSStr(uidSigs[0].m_strSignature) stringByDecodingHTMLEntities];
            
            dict = [NSDictionary dictionaryWithObjectsAndKeys:
                    CStr2NSStr(uidSigs[0].m_strUid),@"uid",
                    [CStr2NSStr(uidSigs[0].m_strSignature) stringByDecodingHTMLEntities],@"signature",
                    nil];
            
            
        }
        
        
        NoticationItem *item = [[[NoticationItem alloc] init] autorelease];
        
        
        item.data =  [NSMutableDictionary dictionaryWithDictionary:dict];
        NSLog(@"item.data: %@", item.data);
        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SIGNATUREDOWNLOADED object:item];
        
        
		[pool release];
	}   
    
    
    virtual void OnNetworkError() {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_NETWORKERROR object:nil];
		[pool release];
	}
    
    virtual void OnForceDisconnect() {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FORCEDISCONNECT object:nil];
		[pool release];
	}
    

    //一些联系人状态发生变化的通知
	virtual void OnContactStatusChanged(const ContactStatusList_t& contactStatusList) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
		for (ContactStatusList_t::const_iterator item = contactStatusList.begin(); item != contactStatusList.end(); item++) {
            
            
            [[AMIMCoreDataHelper getInstance] changeUserStatusWithUid:CStr2NSStr(item->m_strUid) status:item->m_defaultPresence ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
		}
        
        
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CONTACTSTATUSCHANGED object:nil];
        
		[pool release];
	}
    
    //删除联系人的返回结果
	//enErrCode = NO_ERROR表示删除成功，其他值都表示失败
	//只有操作成功，其他参数（strUid)才有意义
	virtual void OnReturnDeleteContact(int enErrCode, const std::string& strUid){
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.errorCode = enErrCode;
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DELETECONTACT object:resultItem];
		[pool release];
	}
    
    //addedContact表示是哪个被添加的联系人，包含有所在组的id，这个联系人的昵称
	//添加联系人的结果，只有当enErrCode为ADD_CONTACT_PEER_DENY时，才能使用strDenyWords，这个表示对方拒绝你时想对你说的话
	virtual void OnAddContactResult(const CAddedContact& addedContact, int enErrCode, const std::string& strDenyWords) {
        
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		
        BOOL isAdd = YES;
        
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.errorCode = enErrCode;
        
		NSString *uid = CStr2NSStr(addedContact.m_strUid);
		NSString *nickName = CStr2NSStr(addedContact.m_strDispName);
		NSNumber *groupId = [NSNumber numberWithInt:addedContact.m_nGroupId];
		
		resultItem.data = [NSMutableDictionary dictionaryWithObjectsAndKeys:
						   uid,@"user_uid",
						   nickName,@"user_nickname",
						   groupId,@"group_id",
						   [AMIMDefaultStorageHelper getLastLoginedUserId],@"ownerId",
						   nil];
		
		if (enErrCode ==  eMSG_TYPE_CONTACT_ADD_OK) {  
            [[AMIMCoreDataHelper getInstance] addUsesrWithUid:uid nickname:nickName groupId:[groupId stringValue]  ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
            ;
            
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ADDFRIENDRESULT object:resultItem];
            		
		} else if (enErrCode == eMSG_TYPE_CONTACT_ADD_FAIL) {
			
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ADDFRIENDRESULT object:resultItem];
            
		}else if (enErrCode == eMSG_TYPE_CONTACT_NEED_REQ) {
            
            [[NSNotificationCenter defaultCenter] postNotificationName : NOTIFICATION_NEEDAUTHCODE object :resultItem];
		}
		
		[pool release];
	}
    
    //返回搜索联系人的结果
	virtual void OnReturnSearchContacts(const SearchContactList_t& searchContactList, uint32_t nTimestamp){
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		
		NSMutableDictionary *friendsDictionary = [[NSMutableDictionary alloc] init];
		NSDictionary *friendInfo;
		
		CAccountUtils accountUtil;
		
		for (SearchContactList_t::const_iterator item = searchContactList.begin(); item != searchContactList.end(); item++) {
			accountUtil.Init(item->m_strUid);
			friendInfo = [NSDictionary dictionaryWithObjectsAndKeys:
                          CStr2NSStr(accountUtil.GetShortUid()),@"name",
                          CStr2NSStr(accountUtil.GetSiteName()),@"from",
                          [NSNumber numberWithInt:item->m_basiCStatus],@"status",
                          nil];
			[friendsDictionary setValue:friendInfo forKey:CStr2NSStr(item->m_strUid)];
		}
		NoticationItem *resultItem = [[[NoticationItem alloc] init] autorelease];
		resultItem.data = friendsDictionary;
		[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SEARCHFRIENDSRESULT object:resultItem];
		[friendsDictionary release];
		[pool release];
	}

    //好友请求添加我为好友
	//strAuthenticationWords为好友发送的验证的话
	virtual void OnRequestAddMyself(const std::string& strPeerId, const std::string& strAuthenticationWords){
        //		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        //		DataCommonController *dc = [DataCommonController create];
        //		NSString *uid = CStr2NSStr(strPeerId);
        //		User *u = [dc searchUserWithUID:uid];
        //		if (u == nil || [u.groupId intValue] != BLACKLIST_CONTACTS_GROUP_ID) {
        //			CAccountUtils accountUtil;
        //			accountUtil.Init(strPeerId);
        //			
        //			NSMutableDictionary *messageDic = [[NSMutableDictionary alloc] init];
        //			[messageDic setValue:[LocalDataTool getCurrentUid] forKey:@"uid"];
        //			[messageDic setValue:[NSString stringWithFormat:NSLocalizedString(@"%@[%@]wants to add you!", nil),CStr2NSStr(accountUtil.GetShortUid()),CStr2NSStr(accountUtil.GetSiteName())] forKey:@"message"];
        //			[messageDic setValue:[NSNumber numberWithInt:MESSAGE_TYPE_RequestAddMyself] forKey:@"messageType"];
        //			[messageDic setValue:[NSNumber numberWithBool:NO] forKey:@"isRead"];
        //			[messageDic setValue:uid forKey:@"to"];
        //			[messageDic setValue:CStr2NSStr(strAuthenticationWords) forKey:@"words"];
        //			[messageDic setValue:[NSDate date] forKey:@"time"];
        //			
        //			[dc addMessage:messageDic];
        //			[dc writeCoreData];
        //			[messageDic release];
        //			NSDictionary *userDic = [LocalDataTool getCurrentUserInfo];
        //			if ([[userDic objectForKey:@"soundNotice"] boolValue]) {
        //				AMAppDelegate *ww = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        //				[ww.soundEffect play];
        //			}
        //			if ([[userDic objectForKey:@"shakeNotice"] boolValue]) {
        //				AMAppDelegate *ww = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        //				[ww.soundEffect vibration];
        //			}
        //			[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_COUNTMSG object:nil];
        //		}
        //		
        //		[pool release];
	}

	//被好友添加成功了
    virtual void OnMyselfAdded(const std::string& strPeerId) {
        
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
//        NSNumber * time = [NSNumber numberWithInt:[[NSDate date] timeIntervalSince1970]];
//        NSString * uid = [AMIMDefaultStorageHelper getLastLoginedUserId];
//
//        NSString * nsContent =[NSString stringWithFormat:NSLocalizedString(@"%@ 添加了你为好友!", nil),CStr2NSStr(strPeerId)];
//        
//        NSString * nsfid =[NSString stringWithFormat:NSLocalizedString(@"%@", nil),CStr2NSStr(strPeerId)];
//        
//        [[AMIMCoreDataHelper getInstance] insertNewMsgWithOwnerId : uid msgFrom:nsfid  msgTo:uid msgType:[NSNumber numberWithInt: TEXT_MSG_CONTACT ] msgContent:nsContent hasRead:[NSNumber numberWithBool:NO] msgTime:time msgSequence:[NSNumber numberWithInt:-1]]; 
//        
//        [[AMIMCoreDataHelper getInstance] modifyContactTimeWithOwner:uid friendId: nsfid msgTime:time];
//        [[AMIMCoreDataHelper getInstance] saveData];
//        
//        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_COUNTMSG object:nil];
        
        [pool release];
	}

    
private:
	CLoginFinalResult m_loginFinalResult;
};


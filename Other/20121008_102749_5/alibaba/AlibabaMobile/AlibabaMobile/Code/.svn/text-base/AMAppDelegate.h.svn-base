//
//  AMAppDelegate.h
//  AlibabaMobile
//
//  Created by  on 11-12-19.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "MyUITabBarController.h"
#import "AMMobileMessage.h"
#import "AMMobileMessageQueryResult.h"
#import "SoundEffect.h"
#import "AMIMUser.h"
#import "LoginTokenHelper.h"
#define NOTIFICATION_MSG_RECV                   @"AlibabaMsgRecved"
#define NOTIFICATION_MSG_READ                   @"AlibabaMsgRead"
#define NOTIFICATION_MSG_RECV_FAILED            @"AlibabaMsgRecvFailed"
#define NOTIFICATION_MSG_GOTO_MESSAGE_CENTER    @"AlibabaMsgGotoMessageCenter"

@interface AMAppDelegate : UIResponder <UIApplicationDelegate, RKOceanClientDelegate,LoginTokenHelperDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic, retain) MyUITabBarController *tabBarController;

@property (nonatomic, retain) NSMutableArray * mMsgResult;
@property (nonatomic, retain) NSMutableArray * mMsgGroupDict;

@property (nonatomic, retain) NSString * terminateId;
@property (nonatomic, retain) NSString * model;
@property (nonatomic, retain) NSString * system;
@property (nonatomic, retain) NSString * version ;
@property (nonatomic, retain) NSString * deviceTokenStr;

@property (nonatomic, retain) NSString * gLoginUserName;
@property (nonatomic, retain) NSString * gAccessToken;
@property (nonatomic, retain) NSString * gAccessTokenTimeout;
@property (nonatomic, retain) NSString * gRefreshToken;
@property (nonatomic, retain) NSString * gRefreshTokenTimeout; 

-(int) getUnReadMsgNum;
-(void) reLoadMsgList;

/*
 *旺旺相关
 */
@property (nonatomic, retain) SoundEffect *soundEffect;

@property (nonatomic, assign) BOOL isWwLogined;
@property (nonatomic, assign) BOOL isWwNeedReconnect;
@property (nonatomic, assign) BOOL isBackground;
@property (nonatomic, assign) BOOL isWwReLogined;


@end

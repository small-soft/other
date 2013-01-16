//
//  AppDelegate.m
//  zzzz
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//
#import <RestKit/RestKit.h>
#import <RestKit/CoreData.h>
#import <AudioToolbox/AudioToolbox.h>

#import "AMAppDelegate.h"

#import "AMLogiticsViewController.h"
#import "AMFavoritesViewController.h"
#import "AMIMViewController.h"
#import "AMMoreViewController.h"

#import "AMCategory.h"
#import "AMMessage.h"
#import "ConstDef.h"

#import "AMMessageRequest.h"
#import "AMMobileMessage.h"
#import "AMMobileMessageQueryResult.h"
#import "LoginToken.h"
#import "StringUtils.h"
#import "UIHelp.h"
#import "KeyValueObject.h"
#import "InternetDataTool.h"
#import "CallBackTool.h"

#import "AMLogTraceService.h"
#import "Utils.h"
#import "AMVersionCheck.h"
#import "AliToastView.h"
#import "AMMobileMessageType.h"

#import "AMUncaughtExceptionService.h"
#import <libkern/OSMemoryNotification.h>
#import "MessageCenterListViewController.h"
#import "AMHomeViewController.h"
#import "AMOrderStateRightViewController.h"

#import "AMDeviceRegistRequest.h"

@interface AMAppDelegate()

@property (nonatomic, retain) AMMessageRequest * requestMsgCnt;
@property (nonatomic, retain) AMMessageRequest * requestMsgList;
@property (nonatomic, retain) AMMessageRequest * requestMsgTypeList;
@property (nonatomic, retain) AMMessageRequest * requestNewMsg;
@property (nonatomic, retain) AMLogTraceService * logTraceService;
@property (nonatomic, retain) AMVersionCheck * versionCheck;
@property (nonatomic,retain) RKOceanClient *oceanClient;
@property (nonatomic, retain) NSMutableArray * lastRequestArray;

@property (retain, nonatomic) IBOutlet UINavigationController *navController;
@end

@implementation UINavigationBar (CustomImage)

-(void)drawRect:(CGRect)rect 
{
    UIImage *image = [UIImage imageNamed:@"bg_topbar"];
    [image drawInRect:CGRectMake(0,0,self.frame.size.width,self.frame.size.height)];
}

@end

@implementation AMAppDelegate

@synthesize requestMsgCnt = _requestMsgCnt;
@synthesize requestMsgList = _requestMsgList;
@synthesize requestMsgTypeList = _requestMsgTypeList;
@synthesize requestNewMsg = _requestNewMsg;
@synthesize logTraceService = _logTraceService;

@synthesize mMsgResult = _mMsgResult;
@synthesize mMsgGroupDict = _mMsgGroupDict;

@synthesize window = _window;
@synthesize tabBarController = _tabBarController;

@synthesize terminateId = _terminateId;
@synthesize  model = _model;
@synthesize  system = _system;
@synthesize  version = _version;
@synthesize  deviceTokenStr = _deviceTokenStr;

@synthesize  gLoginUserName;
@synthesize  gAccessToken;
@synthesize  gAccessTokenTimeout;
@synthesize  gRefreshToken;
@synthesize  gRefreshTokenTimeout; 
@synthesize versionCheck=_versionCheck;
@synthesize oceanClient = _oceanClient;
@synthesize lastRequestArray = _lastRequestArray;
/*
 *旺旺相关
 */
@synthesize soundEffect = _soundEffect;
@synthesize isWwLogined = _isWwLogined;
@synthesize isWwNeedReconnect = _isWwNeedReconnect;
@synthesize isBackground = _isBackground;
@synthesize isWwReLogined = _isWwReLogined;

@synthesize navController = _navController;

-(NSArray *)lastRequestArray{
    if (nil ==_lastRequestArray) {
        _lastRequestArray = [[NSMutableArray alloc]init];
    }
    return _lastRequestArray;
}
-(RKOceanClient*)oceanClient{
    if (nil==_oceanClient) {
        _oceanClient = [[RKOceanClient alloc] init];
        _oceanClient.delegate = self;
    }
    return _oceanClient;
}

-(AMVersionCheck*)versionCheck
{
    if (!_versionCheck) {
        _versionCheck = [[AMVersionCheck alloc]init];
    }
    return _versionCheck;
}

- (void)dealloc
{
    [_soundEffect release];

    [_mMsgResult release];
    [_mMsgGroupDict release];
    [_requestMsgCnt release];
    [_requestMsgList release];
    [_requestMsgTypeList release];
    [_requestNewMsg release];
    
    //[_window release];
    //[_tabBarController release];
 
    [_terminateId release];
    [_model release];
    [self.system release];
    [self.version release];
    [self.deviceTokenStr release];
    
    [self.gLoginUserName release];
    [self.gAccessToken release];
    [self.gAccessTokenTimeout release];
    [self.gRefreshToken release];
    [self.gRefreshTokenTimeout release]; 
    [_versionCheck release];
    
    [_oceanClient release];
    [[LoginTokenHelper sharedTokenHelper] setDelegate:nil];
    [_lastRequestArray release];

    [_navController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSLog(@"== application didFinishLaunchingWithOptions");
    
    // Register notification types
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationType)(UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeSound)];
    
    // Check CoreData data model version
    [self appVersionCheck];
    
    // Initialize RestKit
    RKObjectManager* objectManager = [RKObjectManager managerWithBaseURLString: AMCONST_BASE_URL]; 
    
    // Enable automatic network activity indicator management
    objectManager.client.requestQueue.showsNetworkActivityIndicatorWhenBusy = YES;
    //由于存在默认路径下的缓存及缓存策略 因此只需设定过期时间即可。
//    objectManager.client.cacheTimeoutInterval = 1000 * 60;
    
    _isWwLogined = NO;
    _isWwReLogined = NO;
    
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){
//        [LoginToken checkLoginParameter];
        [LoginToken checkAccessTokenExpired];
    }
    
//    objectManager.client.authenticationType = RKRequestAuthenticationTypeOcean;
//    objectManager.client.OceanAccessToken = [LoginToken getAccessToken];
//    objectManager.client.OceanRefreshToken = [LoginToken getRefreshToken];
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.tabBarController = [[[MyUITabBarController alloc] initWithNibName:@"MyUITabBarController" bundle:nil] autorelease];

    self.window.rootViewController = self.tabBarController;
    //[self.window addSubview:self.tabBarController.view];
    
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"bg_topbar"] forBarMetrics:UIBarMetricsDefault];
    }
    
    [application setStatusBarStyle:UIStatusBarStyleBlackOpaque];
        
    [self.window makeKeyAndVisible];
    
    NSDictionary *userInfo = [launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
    if ( userInfo ) {
        NSLog(@"didFinishLaunchingWithOptions when in background, key =[%@]", userInfo);
        
        NSNumber *messageId = [userInfo objectForKey:@"id"];
        NSLog(@"Alert id: %@", messageId);
        
        NSString *type = [userInfo objectForKey:@"type"];
        NSLog(@"type string: %@", type);
        
        if (type != nil && [type isEqualToString:(MSG_TYPE_WW_OFFLINE_MSG)]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ENTER_WW object:self];
        } else {
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_GOTO_MESSAGE_CENTER object:self];
        }
    }
    //added by christ.yuj
    [[LoginTokenHelper sharedTokenHelper] setDelegate:self];
    
    [self wangwangInit];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(groupMsgList) name:NOTIFICATION_MSG_READ object:nil];

    if([loginUserName length] > 3){
        [self loadRequestMsgCnt];
        //[self loadMsgTypeListRequest];
    }
    
    // Add log trace point here
    if ( [Utils isApplicationFirstLaunched] ) {
        [AMLogUtils appendLog:SYS_FIRST_TIME_USE_AFTER_INSTALL];
    }
    
    [AMLogUtils appendLog:SYS_APP_START];
    
    // Start log trace service
    self.logTraceService = [[AMLogTraceService alloc] init];
    [self.logTraceService startLogService];
    [self.versionCheck loadObjectsFromRemote];
    
    /*
     *add exception handler to collect the crash log 
     *
     *christ.yuj
     */
    [AMUncaughtExceptionService setDefaultHandler];
    
    return YES;
}


- (void) appVersionCheck
{
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    NSString  *version = [userDefault objectForKey:@"appVersion"];
    NSString *versionCode = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    if(version != nil && ![version isEqualToString:versionCode]){
        [userDefault removeObjectForKey:@"appVersion"];
        [userDefault removeObjectForKey:@"accountInfoListDict"];
        [userDefault removeObjectForKey:@"im_login_UserName"];
        [userDefault removeObjectForKey:@"im_login_RefreshToken"];
        [userDefault removeObjectForKey:@"im_login_AccessTokenTimeout"];
        [userDefault removeObjectForKey:@"im_login_AccessToken"];
        [userDefault removeObjectForKey:@"im_login_RefreshTokenTimeout"];
        [userDefault removeObjectForKey:@"im_login_AccessToken_time"];
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);  
        NSString *documentsDirectory = [paths objectAtIndex:0];  
        NSString * path = [NSString stringWithFormat:@"%@/AlibabaMobile.sqlite", documentsDirectory];
        NSURL *url = [NSURL fileURLWithPath:path];
        [[NSFileManager defaultManager] removeItemAtURL:url error:nil];
    }
    
    [userDefault setValue:versionCode forKey:@"appVersion"];
}

-(void) reLoadMsgList {
    //[_mMsgResult removeAllObjects];
    //[_mMsgGroupDict removeAllObjects];
    [self loadRequestMsgCnt];
    //[self loadMsgTypeListRequest];    
}

-(void)loginSucc {
    [self reLoadMsgList];
}

- (void) wangwangInit {
  //  [CallBackTool create];
	//初始化声音
	NSString *path = [NSString stringWithFormat: @"%@/%@",[[NSBundle mainBundle] resourcePath],@"Sent.wav"];
	self.soundEffect = [[SoundEffect alloc] initWithContentsOfFile:path];
}

- (void) applicationDidBecomeActive:(UIApplication *)application {
    NSLog(@"== applicationDidBecomeActive");
    
    self.isBackground = NO;
    
    if (application) {
        int msgNum = application.applicationIconBadgeNumber;
        NSLog(@"== applicationIconBadgeNumber = %d", msgNum);
        if (msgNum > 0) {
            [self reLoadMsgList];
        }
    }
    
    [application setApplicationIconBadgeNumber:0];
    if(self.isWwNeedReconnect){
        [[NSNotificationCenter defaultCenter] postNotificationName:NOITFICATION_RECONNECTWW object:nil];
        self.isWwReLogined = YES;
        self.isWwNeedReconnect = NO;
    }
}

-(void) applicationWillEnterForeground:(UIApplication *)application{
    NSLog(@"== applicationWillEnterForeground");
    
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){
        [LoginToken checkAccessTokenExpired];
    }
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     //[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_HOME object:self];
    //[self.tabBarController entryTabBarItem:@"home"];
//    NSLog(@"Recieve memory warning");
//    NSLog(@"~~~~~~~~~~~~~~level~~~~~~~~~~~~~~~ %d", (int)OSMemoryNotificationCurrentLevel());
//    NSString *msg = [NSString stringWithFormat:@"内存告警级别：%d",(int)OSMemoryNotificationCurrentLevel()];
//    UIAlertView *alert = [[UIAlertView alloc] 
//                          initWithTitle:@"内存不足！" 
//                          message:msg 
//                          delegate:self    
//                          cancelButtonTitle:@"取消"                          
//                          otherButtonTitles:@"确定" ,
//                          nil]; 
//    [alert show]; 
//    [alert release];

    //[NSThread sleepForTimeInterval:1];
    //[pool drain];
}

- (void) applicationDidEnterBackground:(UIApplication *)application
{
    self.isBackground = YES;
    [[NSNotificationCenter defaultCenter] postNotificationName:NOITFICATION_APPGOBACKGROUND object:nil];
}

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    NSLog(@"My device token is: [%@]", deviceToken );
    
    UIDevice * device = [UIDevice currentDevice];
    
    self.terminateId = device.uniqueIdentifier;
    self.model = device.localizedModel;
    self.system = device.systemName;
    self.version = device.systemVersion;
   
    // Convert body to real JSON NSString
    if (deviceToken != nil) {
        NSRange range = {1, [[deviceToken description] length] - 2};
        self.deviceTokenStr = [[[deviceToken description] substringWithRange: range] stringByReplacingOccurrencesOfString:@" " withString:@""];
        
        NSLog(@"Converted device token is: [%@]", self.deviceTokenStr);
    }
    
    // 注册机器信息
    [self registDeviceToRemote];
}

- (void)registDeviceToRemote {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    BOOL isRegistDevice =[defaults boolForKey:@"is_registe_device"];
    if (isRegistDevice) {
        return;
    }
    
    AMDeviceRegistRequest * registRequest = [[AMDeviceRegistRequest alloc] init];
    registRequest.terminateId = self.terminateId;
    registRequest.model = self.model;
    registRequest.system  = self.system;
    registRequest.version  = self.version;
    registRequest.deviceTokenStr  = self.deviceTokenStr;
    registRequest.appId  = AMCONST_APP_ID;
    registRequest.appVersion = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    registRequest.downloadChannel = [[[NSBundle mainBundle]infoDictionary]objectForKey:@"Download channel"];
    
    registRequest.currentUserId  = [LoginToken getLoginUserName];
//    registRequest.transactionType = AMTRANSACTION_TYPE_DEVICE_REGIST;
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_DEVICE_REGIST usingBlock:^(RKObjectLoader* loader) {
        //        loader.delegate = self;    
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = registRequest;
    }];
    
    [registRequest release];
    
    [defaults setBool:YES forKey:@"is_registe_device"];
}   


- (void) application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    NSLog(@"Failed to register device, error: %@", error);
}

// Process remote messages
- (void) application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    NSLog(@"== Receive remote notification: [%@]", userInfo);
    
    NSDictionary *alertDictionary = [userInfo objectForKey:@"aps"];
    NSLog(@"Alert Dictionary: %@", alertDictionary);

    NSString *alertJosn = [alertDictionary objectForKey:@"alert"];
    NSLog(@"Alert string: %@", alertJosn);
    
    NSNumber *alertId = [userInfo objectForKey:@"id"];
    NSLog(@"Alert id: %@", alertId);
    
    NSString *type = [userInfo objectForKey:@"type"];
    NSLog(@"type string: %@", type);
    
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3) {
        return ;
    }
    
    [self loadNewMsgDetailRequest:alertId];
        
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
        
    if([[UIApplication sharedApplication] applicationState] != UIApplicationStateActive) {
        application.applicationIconBadgeNumber = 0;
        
        if ([type isEqualToString:(MSG_TYPE_WW_OFFLINE_MSG)]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ENTER_WW object:self];
        } else {
            [self.tabBarController entryMsgCenter];
        }
    } else if ([type isEqualToString:(MSG_TYPE_WW_OFFLINE_MSG)]) {
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:alertJosn] show];
    }
}

#pragma data
- (void)loadObjectsMsgCntFromRemote
{
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MESSAGE_COUNT usingBlock:^(RKObjectLoader* loader) {
        
        // Change Method to POST
        loader.delegate = self.oceanClient;
        loader.method = RKRequestMethodPOST;
        loader.params = _requestMsgCnt;
    }];
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
    
    if([response isOK]){
        NSString * tempStr =  [response bodyAsString];
        if([StringUtils getIndexOf:@"{" inFather:tempStr] == -1){
            int count = 0;
            @try {
                count = tempStr.intValue;
            } @catch ( NSException * e ) {
                NSLog(@"Invalid number!");
            }
            
            if ( count > 0 ) {
                [self loadMsgListRequest:count];
            } else {
                [self.mMsgResult removeAllObjects];
                [self.mMsgGroupDict removeAllObjects];
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_RECV object:self];
            }
        }   
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {   
    NSLog(@"Loaded objects: %@", objects);
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        
        if ([objectLoader.params respondsToSelector:@selector(transactionType)] && [objects count] > 0 ) {
            NSInteger transactionType = (NSInteger)[(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
            id obj = [objects objectAtIndex:0];
            if (transactionType == AMTRANSACTION_TYPE_MESSAGE_COUNT){
                return;
            } else if (transactionType == AMTRANSACTION_TYPE_MESSAGE_LIST){
                AMMobileMessageQueryResult * result = obj;
                if(self.mMsgResult == nil){
                    self.mMsgResult = [[NSMutableArray alloc] init ];
                }else{
                    [self.mMsgResult removeAllObjects];
                }
                
                if(self.mMsgGroupDict == nil){
                    self.mMsgGroupDict = [[NSMutableArray alloc] init ];
                } else {
                    [self.mMsgGroupDict removeAllObjects];
                }
                
                NSInteger msgCnt = result.messages.count;
                AMMobileMessage * msg = nil;
                for (int i = 0; i < msgCnt; i++) {
                    // filter ww offline msg
                    msg = ((AMMobileMessage *)[result.messages objectAtIndex:i]);
                    if (msg == nil || msg.type == nil || [msg.type isEqualToString:(MSG_TYPE_WW_OFFLINE_MSG)]) {
                        continue;
                    }
                    [self.mMsgResult addObject:msg];
                }
                
                [self groupMsgList];
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_RECV object:self];
                return;
            }else if (transactionType == AMTRANSACTION_TYPE_MESSAGE_DETAIL){
                if (objects == nil || [objects count] < 1) {
                    return ;
                }
                
                AMMobileMessage * msg = (AMMobileMessage *)[objects objectAtIndex:0];
                if (msg == nil || msg.type == nil || [msg.type isEqualToString:(MSG_TYPE_WW_OFFLINE_MSG)]) {
                    return ;
                }
                [self.mMsgResult insertObject:msg atIndex:0];
                [self groupMsgList];
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_RECV object:self];
                return;
            }else if (transactionType == AMTRANSACTION_TYPE_MESSAGE_TYPE){
                NSArray * typeList = (NSArray *)objects;
                NSLog(@"typeList.count = %d", typeList.count);// typeList.count
//                AMMobileMessageType * msg = (AMMobileMessageType *)[obj objectAtIndex:0];
//                if (msg == nil || msg.source == nil || msg.displayName) {
//                    return ;
//                }
                
                // [self.mMsgResult insertObject:msg atIndex:0];
                // [self groupMsgList];
                // [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_RECV object:self];
                return;
            }
        }
    }
    return;
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
    NSLog(@"didFailWithError, error: %@", error);
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline){
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_RECV_FAILED object:self];
    }
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = (NSInteger)[(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if (transactionType == AMTRANSACTION_TYPE_MESSAGE_COUNT){
            return;
        }
    }

	NSLog(@"Hit error: %@", error);
}

-(void)loadRequestMsgCnt {
    if(_requestMsgCnt == nil) {
        _requestMsgCnt = [[AMMessageRequest alloc] init];
    }
    
    _requestMsgCnt.transactionType = AMTRANSACTION_TYPE_MESSAGE_COUNT;
    _requestMsgCnt.memberId = [LoginToken getLoginUserName];
    _requestMsgCnt.requestURL = OCEAN_API_URL_MESSAGE_COUNT;
    
    [self loadObjectsMsgCntFromRemote];
}

- (void)loadObjectsMsgListFromRemote {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* mapping = [AMMobileMessageQueryResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MESSAGE_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMMobileMessageQueryResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _requestMsgList;
    }];
}

-(void)loadMsgListRequest:(int)count {
    if(_requestMsgList == nil){
        _requestMsgList = [[AMMessageRequest alloc] init];
    }
    
    _requestMsgList.memberId = [LoginToken getLoginUserName];
    _requestMsgList.pageSize = [NSNumber numberWithInt: count];
    _requestMsgList.newMessageOnly = [NSNumber numberWithBool:NO];
    _requestMsgList.pageIndex = [NSNumber numberWithInt:0];
    _requestMsgList.requestURL = OCEAN_API_URL_MESSAGE_LIST;
    _requestMsgList.transactionType = AMTRANSACTION_TYPE_MESSAGE_LIST;
    
    [self loadObjectsMsgListFromRemote];
}

-(void)loadMsgTypeListRequest {
    if(_requestMsgTypeList == nil){
        _requestMsgTypeList = [[AMMessageRequest alloc] init];
    }
    _requestMsgTypeList.requestURL = OCEAN_API_URL_MESSAGE_TYPE;
    _requestMsgTypeList.transactionType = AMTRANSACTION_TYPE_MESSAGE_TYPE;
    
    [self loadObjectsMsgTypeListFromRemote];
}

- (void)loadObjectsMsgTypeListFromRemote {
   
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: [AMMobileMessageType sharedObjectMapping]];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MESSAGE_TYPE usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMMobileMessageType class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _requestMsgTypeList;
    }];
}

- (void)loadNewMsgDetailFromRemote {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* mapping = [AMMobileMessage sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MESSAGE_DETAIL usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMMobileMessage class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _requestNewMsg;
    }];
}

-(void)loadNewMsgDetailRequest:(NSNumber *)msgId
{
    if(_requestNewMsg == nil){
        _requestNewMsg = [[AMMessageRequest alloc] init];
    }

//    _requestNewMsg.memberId = [LoginToken getLoginUserName];
    _requestNewMsg.requestURL = OCEAN_API_URL_MESSAGE_DETAIL;
    _requestNewMsg.messageId = msgId;
    _requestNewMsg.transactionType = AMTRANSACTION_TYPE_MESSAGE_DETAIL;
    
    [self loadNewMsgDetailFromRemote];
} 

- (void) groupMsgList {
    if(self.mMsgGroupDict == nil){
        self.mMsgGroupDict = [[NSMutableArray alloc] init ];
    } 
    
    if(self.mMsgResult == nil || self.mMsgResult.count <= 0){
        return ;
    }
    
    int nNewCount = 0;
    NSMutableArray * msgArray = [[NSMutableArray alloc] initWithArray:self.mMsgResult];
    while(msgArray.count > 0){
        AMMobileMessage * msg = [msgArray objectAtIndex:0];
        NSString * source = [msg sourceDisplayName];
        if (!msg.hasRead.boolValue) {
            nNewCount++;
        }
        
        int index = [self getKeyObjectObject:source];
        if( index >= 0 ){ // 已经存在
            KeyValueObject * obj = [self.mMsgGroupDict objectAtIndex:index];
            int count = ((NSNumber *)(obj.value)).intValue;
            count ++;
            obj.value = [NSNumber numberWithInt:count];
        }else{ // 不存在
            KeyValueObject * obj = [[KeyValueObject alloc] init];
            obj.key = source;
            obj.value = [NSNumber numberWithInt:1];
            [self.mMsgGroupDict addObject:obj];
            [obj release];
        }
        [msgArray removeObject:msg];
    }
    
    if (nNewCount > 0 && [self.mMsgGroupDict count] > 1 && ![(NSString *)((KeyValueObject *)[self.mMsgGroupDict objectAtIndex:1]).key isEqualToString: AMSourceName_New]) {
        KeyValueObject * objNew = [[KeyValueObject alloc] init];
        objNew.key = [NSString stringWithString:AMSourceName_New]; // 未读消息
        objNew.value = [NSNumber numberWithInt:nNewCount];
        [self.mMsgGroupDict insertObject:objNew atIndex:0];
        [objNew release];
    }else if (nNewCount == 0 && [self.mMsgGroupDict count] > 1){
        if ( [(NSString *)((KeyValueObject *)[self.mMsgGroupDict objectAtIndex:1]).key isEqualToString: AMSourceName_New] ) {
            [self.mMsgGroupDict removeObjectAtIndex:1];
        }
    }
    
    if ( ![(NSString *)((KeyValueObject *)[self.mMsgGroupDict objectAtIndex:0]).key isEqualToString: AMSourceName_All] ) {
        KeyValueObject * objAll = [[KeyValueObject alloc] init];
        objAll.key = [NSString stringWithString:AMSourceName_All]; // 所有消息
        objAll.value = [NSNumber numberWithInt:self.mMsgResult.count];
        [self.mMsgGroupDict insertObject:objAll atIndex:0];
        [objAll release];
    }

    [msgArray release];
}

-(int)getKeyObjectObject:(NSString *)source {
    if(self.mMsgGroupDict != nil && self.mMsgGroupDict.count >0) {
        
        int size = self.mMsgGroupDict.count;
        
        for(int i=0;i<size; i++){
            KeyValueObject * obj = [self.mMsgGroupDict objectAtIndex:i];
            if([((NSString *)(obj.key)) isEqualToString:source] ){
                return i;
            }
        }
    }
    
    return -1;
}

- (int) getUnReadMsgNum
{
    if(self.mMsgResult != nil && self.mMsgResult.count > 0){
        int size = self.mMsgResult.count;
        int newNum = 0;
        for(int i=0;i<size; i++){
            AMMobileMessage * msg = [self.mMsgResult objectAtIndex:i];
            if([msg hasRead].boolValue == NO){
                newNum ++;
            }
        }
        return newNum;
    }
    
    return 0;
}

-(void) applicationWillTerminate:(UIApplication *)application {
    // Add log trace point here
    [AMLogUtils appendLog:SYS_APP_EXIT];
}

#pragma mark RKOceanClientDelegate methods
- (void)OceanClient:(RKOceanClient *)oceanClient Request:(RKRequest *)request didAcessTokenOutOfDate:(RKResponse *)response{
    NSMutableDictionary * dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setObject:request forKey:@"request"];
    [dictionary setObject:@"NO" forKey:@"isSended"];
    [self.lastRequestArray addObject:dictionary];
    [[LoginTokenHelper sharedTokenHelper] updateAccessToken];
    [AMUncaughtExceptionService instance].count = 1;
    
}

- (void)OceanClient:(RKOceanClient *)oceanClient didRefreshTokenOutOfDate:(RKResponse *)response{
//    [self.mLoadingView endLoadingView];
//    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"鉴权失败"] show]; 
//    
//    UIViewController *nextController;
//    nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
//    nextController.hidesBottomBarWhenPushed=YES;
//    
//    [self.navigationController pushViewController:nextController animated:YES];
    [AMUncaughtExceptionService instance].count = 2;
}

- (void)OceanClient:(RKOceanClient *)oceanClient didDonotLogin:(RKResponse *)response{
//    [self.mLoadingView endLoadingView];
//    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"请您重新登陆"] show]; 
}

-(void)loginTokenHelperDidUpdateAccessToken{
    for (NSMutableDictionary * dictionary in self.lastRequestArray) {
        if ([(NSString*)[dictionary objectForKey:@"isSended"] isEqualToString:@"NO"]) {
            [(RKRequest*)[dictionary objectForKey:@"request"] send];
            [dictionary setObject:@"YES" forKey:@"isSended"];
        }
    }
}

@end

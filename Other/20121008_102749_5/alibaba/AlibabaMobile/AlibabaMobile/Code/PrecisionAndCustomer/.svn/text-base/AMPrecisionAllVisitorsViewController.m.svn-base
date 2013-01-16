//
//  AMPrecisionAllVisitorsViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "AMPrecisionAllVisitorsViewController.h"
#import "AMIMViewController.h"
#import "LoginToken.h"
#import "AliTabViewController.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliImageControlFactory.h"
#import "UIHelp.h"
#import "AMMoreLoadingCell.h"
#import "AliTableViewCellAllVisitor.h"
#import "ConstDef.h"
#import "AMCUDResult.h"
#import "AliToastView.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
#import "AMRequestDelegate.h"

#import "AMPrecisionUserInfoResult.h"
#import "AMPrecisionVisitorStatusResult.h"
#import "AMPrecisionTalkPermissionResult.h"
#import "AMPrecisionSaveFreeUserResResult.h"
#import "NoticationItem.h"
#import "AMPrecisionVisitorListRequest.h"
#import "AMPrecisionVisitorListResult.h"
#import "AMPrecisionVisitor.h"
#import "AMPrecisionDetailViewController.h"
#import "UserDataUtils.h"
#import "AMTotalCountView.h"
#import "AMMoreLoadingView.h"
#import "AMIMTalkViewController.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
#define DEFAULT_PAGE_SIZE  9

@interface AMPrecisionAllVisitorsViewController()
@property (nonatomic,copy)NSString *loginUserName;
@property (nonatomic,assign)NSInteger tempCurrentPage;
@end
@implementation AMPrecisionAllVisitorsViewController
@synthesize controllers;
@synthesize allVisitorTableView;
@synthesize visitorListRequest = _visitorListRequest;
@synthesize userInfoRequest = _userInfoRequest;
@synthesize visitorStatusRequest = _visitorStatusRequest;
@synthesize talkPermissionRequest = _talkPermissionRequest;
@synthesize saveFreeUserResRequest = _saveFreeUserResRequest;
@synthesize objMan;
@synthesize mLoadingView = _mLoadingView;
@synthesize loginUserName=_loginUserName;
@synthesize sectionGroupDict = _sectionGroupDict;
@synthesize sectionGroupArrayKey = _sectionGroupArrayKey;
@synthesize mNavigationController = _mNavigationController;
@synthesize tempCurrentPage = _tempCurrentPage;

-(UIView*)mLoadingView {
    if (!_mLoadingView) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib) {
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];            
        }
        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    return _mLoadingView;
}

- (void) showLoadingView {
    [self.mLoadingView setHidden:NO];
}
//去除加载进度
-(void) endLoadingView {
    [self.mLoadingView setHidden:YES];
}

- (void) showNodataMessage {
    [self.mLoadingView setHidden:NO];
    [self.mLoadingView.loadingView setHidden:YES];
    [self.mLoadingView.noDataView setHidden:NO];
}

- (id)initWithNavigation:(UINavigationController *)navigation {
    self = [super init];
    if (self) {
        self.mNavigationController = navigation;
        isFirstLoadView = YES;
    }
    return self;
}

- (void)didReceiveMemoryWarning {
//    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

- (void)loadObjectsFromRemoteAllVisitor {
    
    isLoading = YES;
    
//    if(isPullViewLoad){
//        isPullViewLoad = NO;
//    }else{
        if(currentAllVisitorPage > 1){
            AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
            self.allVisitorTableView.tableFooterView = moreloadingView;
            [moreloadingView release];
        }
        else {
            self.allVisitorTableView.tableFooterView = nil;
            [self.mLoadingView showLoadingView];
        }
//    }

    [self.mLoadingView.noDataView setHidden:YES];

    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* favResultMapping = [AMPrecisionVisitorListResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: favResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_VISITOR_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionVisitorListResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.visitorListRequest;
    }];
}

- (void)loadObjectsFromRemoteUserInfo {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* resultMapping = [AMPrecisionUserInfoResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_GET_USERINFO usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionUserInfoResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.userInfoRequest;
    }];
}

- (void)loadObjectsFromRemoteVisitorStatus {
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* resultMapping = [AMPrecisionVisitorStatusResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_VISITOR_STATUS usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionVisitorStatusResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.visitorStatusRequest;
    }];
}

- (void)loadObjectsFromRemoteTalkPermission {
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* resultMapping = [AMPrecisionTalkPermissionResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_TALK_PERMISSION usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionTalkPermissionResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.talkPermissionRequest;
    }];
}

- (void)loadObjectsFromRemoteSaveFreeUserRes {
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* resultMapping = [AMPrecisionSaveFreeUserResResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_SAVE_FREE_USER_RES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionSaveFreeUserResResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.saveFreeUserResRequest;
    }];
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   

    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
        //NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
        //[UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
        //NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
        //[UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        gLastDisplayErrorTimeInterval = currentTime;
    }
}

+(NSString *)dateGroup:(NSString*)inputDate{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd"];
    
    NSString *today = [dateFormatter stringFromDate:[NSDate date]];
//    NSLog(@"currentDateStr=%@",today);
    
    NSDate *yesterdayDate = [NSDate dateWithTimeIntervalSinceNow: -(24 * 60 * 60)]; 
    NSString *yesterday = [dateFormatter stringFromDate:yesterdayDate];
//    NSLog(@"yesterdayDateStr=%@",yesterday);
    
    NSDate *beforeYesterdayDate = [NSDate dateWithTimeIntervalSinceNow: -(48 * 60 * 60)]; 
    NSString *beforeYesterday = [dateFormatter stringFromDate:beforeYesterdayDate];
//    NSLog(@"beforeYesterdayStr=%@",beforeYesterday);
    [dateFormatter release];
    if([inputDate isEqualToString:today]){
        return NSLocalizedString(@"Today", nil);
    }else if([inputDate isEqualToString:yesterday]){
        return NSLocalizedString(@"Yesterday", nil);
    }else if([inputDate isEqualToString:beforeYesterday]){
        return NSLocalizedString(@"DayBeforeYesterday", nil);
    }else{
        return inputDate;
    }
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    if (objects == nil || !([objectLoader.params respondsToSelector:@selector(transactionType)])) {
        return ;
    }
    NSLog(@"Loaded objects: %@", objects);  
    
    NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
    if (transactionType == AMTRANSACTION_TYPE_PRECISION_VISITOR_LIST) {
        isLoading = NO;
        AMPrecisionVisitorListResult *result = (AMPrecisionVisitorListResult*)[objects objectAtIndex:0];
    
        //增加section
        if(self.sectionGroupArrayKey==nil){
            self.sectionGroupArrayKey = [[NSMutableArray alloc] init];
        }
    
        if(self.sectionGroupDict==nil){
            self.sectionGroupDict = [[NSMutableDictionary alloc] init];
        }
    
        if([result.allVisitor count] > 0){
        
            if (isPullViewLoad) {
                [self.sectionGroupDict removeAllObjects];
                [self.sectionGroupArrayKey removeAllObjects];
                isPullViewLoad = NO;
            }

            
            //table section分组
            for(int i=0; i<result.allVisitor.count; i++){
                AMPrecisionVisitor *visitors = (AMPrecisionVisitor*)[result.allVisitor objectAtIndex:i] ;
                NSString *time = visitors.gmtAccess;
                BOOL isCurrent = [visitors.current boolValue];
            
                NSRange range = {0,10};
                
                NSString *timeSub = nil;
                if (isCurrent) {
                    timeSub = NSLocalizedString(@"Current", nil);;
                } else {
                    timeSub = [time substringWithRange:range];
                }

                NSLog(@"time=%@",timeSub);
                //获得日期分组
                if (![self.sectionGroupArrayKey containsObject:timeSub]) {
                    if (isCurrent) {
                        [self.sectionGroupArrayKey insertObject:timeSub atIndex:0];
                    }else {
                        [self.sectionGroupArrayKey addObject:timeSub];  
                    }
                }
            
                NSMutableArray *tempArray = [self.sectionGroupDict objectForKey:timeSub];
                if(tempArray==nil){
                    tempArray = [[NSMutableArray alloc] init] ;
                    [tempArray addObject:visitors];
                    [self.sectionGroupDict setObject:tempArray forKey:timeSub];
                    [tempArray release];
                }else{
                    [tempArray addObject:visitors];
                }
            }
        }
        
//        [self.sectionGroupArrayKey count];
        allVisitorTotalCount = [[result total] intValue];
        [self.allVisitorTableView reloadData];
        [allVisitorTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
        
        if (allVisitorTotalCount<=0) {
            [self showNodataMessage];
        }
        else {
            [self endLoadingView];
        }
        
        if(currentAllVisitorPage * DEFAULT_PAGE_SIZE >= allVisitorTotalCount){
            AMTotalCountView * totalFooterView = [[AMTotalCountView alloc] init];
            [totalFooterView setTotalCount:allVisitorTotalCount];
            self.allVisitorTableView.tableFooterView = totalFooterView;
            [totalFooterView release];
        }
    } else if(transactionType == AMTRANSACTION_TYPE_PRECISION_GET_USERINFO){
        AMPrecisionUserInfoResult * result = (AMPrecisionUserInfoResult*)[objects objectAtIndex:0];
        if (result == nil || result.siteId == nil || result.userType == nil) {
            return ;
        }
        NSLog(@"%@", result);
        
        NSString * memberId = [LoginToken getLoginUserName];
        NSString * uniqueStr = [UserDataUtils generateUniqueStr:memberId:result.siteId];
        
        [UserDataUtils setPmUserInfo:result.siteId:result.userType:uniqueStr];
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_PM_SET_FORMALUSER_IMG_VISIBLE object:self];
        [self loadRequest];
    } else if(transactionType == AMTRANSACTION_TYPE_PRECISION_VISITOR_STATUS){
        AMPrecisionVisitorStatusResult * result = (AMPrecisionVisitorStatusResult *)[objects objectAtIndex:0];
        if (result == nil || result.handShake == nil) {
            return ;
        }
        mCurVisitor.handShake = result.handShake;
        
        NSLog(@"visitor status handShake = %d", [[result handShake] boolValue]);
        
        isHandShake  = [[result handShake] boolValue];
        [self gotoTalk:mCurVisitor.aliimId:isHandShake:mCurVisitor.visitorId];
    } else if(transactionType == AMTRANSACTION_TYPE_PRECISION_TALK_PERMISSION){
        AMPrecisionTalkPermissionResult * result = (AMPrecisionTalkPermissionResult *)[objects objectAtIndex:0];
        if (result == nil || result.hasPermissionUsed == nil || result.talked == nil) {
            return ;
        }
        
        BOOL canTalk = [[result hasPermissionUsed] boolValue];
        BOOL isTalked = [[result talked] boolValue];
        
        NSLog(@"visitor status canTalk = %d", canTalk);
        NSLog(@"visitor status isTalked = %d", isTalked);
        
        if (isTalked) {
            if (mGotoDetail) {
                [self gotoVisitorDetail:YES];
            } else {
                [self loadVisitorStatusRequest:mCurVisitor.visitorId];
            }
        } else {
            if (mGotoDetail) {
                [self gotoVisitorDetail:canTalk];
            } else {
                if (canTalk) {
                    UIAlertView *alert = [[UIAlertView alloc] 
                                          initWithTitle:NSLocalizedString(@"Notice", nil) 
                                          message:NSLocalizedString(@"PM_Use_Talk_Confirm", nil) 
                                          delegate:self 
                                          cancelButtonTitle:NSLocalizedString(@"Cancel", nil) 
                                          otherButtonTitles:NSLocalizedString(@"OK", nil),
                                          nil];
                    [alert setTag:0];
                    [alert show];
                    [alert release];
                } else {
                    UIAlertView *alert = [[UIAlertView alloc] 
                                          initWithTitle:NSLocalizedString(@"Notice", nil) 
                                          message:NSLocalizedString(@"PM_Cannot_Talk", nil) 
                                          delegate:self 
                                          cancelButtonTitle:NSLocalizedString(@"OK", nil)
                                          otherButtonTitles:nil,
                                          nil];
                    [alert setTag:1];
                    [alert show];
                    [alert release];
                }
            }
        }
        mGotoDetail = NO;
    } else if (transactionType == AMTRANSACTION_TYPE_PRECISION_SAVE_FREE_USER_RES) {
        AMPrecisionSaveFreeUserResResult * result = (AMPrecisionSaveFreeUserResResult *)[objects objectAtIndex:0];
        if (result == nil || result.rspResult == nil) {
            return ;
        }
        NSLog(@"SaveFreeUserResResult = %d", [[result rspResult] boolValue]);
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    
    [allVisitorTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
    
    if (!([objectLoader.params respondsToSelector:@selector(transactionType)])) {
        return ;
    }
    
    NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
    
    isLoading = NO;
    
    if([error code] == RKRequestBaseURLOfflineError||[error code] == RKRequestConnectionTimeoutError||[error code] == -1009){
        if([self.sectionGroupArrayKey count]) {

            if (transactionType == AMTRANSACTION_TYPE_PRECISION_VISITOR_LIST){
                if (isPullViewLoad) {
                    [self.allVisitorTableView.pullToRefreshView stopAnimating];
                }
                AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
                self.allVisitorTableView.tableFooterView = errorMessageView;
                [errorMessageView release];
                if (!isPullViewLoad) {
                    currentAllVisitorPage --; 
                }else {
                    currentAllVisitorPage = self.tempCurrentPage;
                }
                isPullViewLoad = NO;
            }
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
    }
}

- (void)gotoVisitorDetail:(BOOL)canTalk {
    AMPrecisionDetailViewController * infoController = [[[AMPrecisionDetailViewController alloc] initWithVisitorId:mCurVisitor.visitorId] autorelease];
    
    infoController.sellerMemberId = [LoginToken getLoginUserName];
    infoController.siteId = [UserDataUtils getPmSiteId];
    infoController.visitorId = mCurVisitor.visitorId;
    infoController.wwId = mCurVisitor.aliimId;
    infoController.hasTalkPermision = canTalk;
    
    [self.mNavigationController pushViewController:infoController animated:YES];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    NSLog(@"alertView click tag = %d, index = %d", alertView.tag, buttonIndex);
    switch (alertView.tag) {
        case 0:
            if (buttonIndex ==  1) {
                [self loadVisitorStatusRequest:mCurVisitor.visitorId];
            }
            break;
        default:
            break;
    }
}

-(void) gotoTalk:(NSString *) wwId:(BOOL)isHandShakeSucc:(NSString *)visitorId{
    NSString *loginUserName = nil;
    loginUserName = [LoginToken getLoginUserName];
    if([loginUserName length] > 3 && [LoginToken isWangWangLogined]){
        [self loadSaveFreeUserResRequest:visitorId];
    } else {
        mSaveFreeUserResWhenLogined = YES;
    }
    
    if([LoginToken isWangWangLogined]) 
    {
        [self enterTalk];
    }
    else 
    {
        isTalkAfterWwLogin = YES;
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
    }
    
    if (isHandShakeSucc) {
        mCurVisitorId = wwId;
    } else {
        mCurVisitorId = visitorId;
    }
}

-(void) enterTalk {
    if (mCurVisitor) 
    {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam : YES : isHandShake : mCurVisitor.visitorId : mCurVisitor.aliimId : mCurVisitor.showName];

        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.mNavigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

- (void) onWwLoginSucc {
    if (mSaveFreeUserResWhenLogined) {
        [self loadSaveFreeUserResRequest:mCurVisitorId];
        mSaveFreeUserResWhenLogined = NO;
    }
    
    if (isTalkAfterWwLogin) {
        [self enterTalk];
        isTalkAfterWwLogin = NO;
    }
}

#pragma mark - View lifecycle

-(void)loadRequest {

    if ([LoginToken isAppLogined]) {
        
        if (![UserDataUtils checkUniqueStrValid]) {
            return ;
        }
        
        if (nil == self.visitorListRequest) {
            self.visitorListRequest = [[AMPrecisionVisitorListRequest alloc] init]; 
        }
        
        self.visitorListRequest.requestURL = OCEAN_API_URL_PRECISION_VISITOR_LIST;  
        self.visitorListRequest.beginPage = [NSNumber numberWithInt: currentAllVisitorPage];
        self.visitorListRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_VISITOR_LIST;
        self.visitorListRequest.siteId = [UserDataUtils getPmSiteId];
        [self loadObjectsFromRemoteAllVisitor];
    }else {
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        [self.mNavigationController pushViewController:nextController animated:YES];
        [nextController release];
    }
}

-(void)loadGetUserInfoRequest {
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if ([loginUserName length] > 3) {
        if (nil == self.userInfoRequest) {
            self.userInfoRequest = [[AMPrecisionUserInfoRequest alloc] init]; 
        }
        
        self.userInfoRequest.requestURL = OCEAN_API_URL_PRECISION_GET_USERINFO;  
        self.userInfoRequest.memberId = loginUserName;
        self.userInfoRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_GET_USERINFO;
        [self loadObjectsFromRemoteUserInfo];
    }else {
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        [self.mNavigationController pushViewController:nextController animated:YES];
        [nextController release];
    }
}

-(void)loadVisitorStatusRequest:(NSString *)visitorId {
    NSString *loginUserName = nil;
    loginUserName = [LoginToken getLoginUserName];
    if ([loginUserName length] > 3) {
        if (![UserDataUtils checkUniqueStrValid]) {
            return ;
        }
        
        //[self showLoadingView];
        if (nil == self.visitorStatusRequest) {
            self.visitorStatusRequest = [[AMPrecisionVisitorStatusRequest alloc] init]; 
        }
        
        self.visitorStatusRequest.requestURL = OCEAN_API_URL_PRECISION_VISITOR_STATUS;  
        self.visitorStatusRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_VISITOR_STATUS;
        self.visitorStatusRequest.sellerMemberId = loginUserName;
        self.visitorStatusRequest.siteId = [UserDataUtils getPmSiteId];
        self.visitorStatusRequest.visitorId = visitorId;
        [self loadObjectsFromRemoteVisitorStatus];
    }else {
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        [self.mNavigationController pushViewController:nextController animated:YES];
        [nextController release];
    }
}

-(void)loadTalkPermissionRequest:(NSString *)visitorId {
    NSString *loginUserName = nil;
    loginUserName = [LoginToken getLoginUserName];
    if ([loginUserName length] > 3) {
        if (![UserDataUtils checkUniqueStrValid]) {
            return ;
        }
        
        if (nil == self.talkPermissionRequest) {
            self.talkPermissionRequest = [[AMPrecisionTalkPermissionRequest alloc] init]; 
        }
        
        self.talkPermissionRequest.requestURL = OCEAN_API_URL_PRECISION_TALK_PERMISSION;  
        self.talkPermissionRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_TALK_PERMISSION;
        self.talkPermissionRequest.siteId = [UserDataUtils getPmSiteId];
        self.talkPermissionRequest.visitorId = visitorId;
        [self loadObjectsFromRemoteTalkPermission];
    }else {
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        [self.mNavigationController pushViewController:nextController animated:YES];
        [nextController release];
    }
}

-(void)loadSaveFreeUserResRequest:(NSString *)visitorId {
    NSString *loginUserName = nil;
    loginUserName = [LoginToken getLoginUserName];
    if ([loginUserName length] > 3) {
        if (![UserDataUtils checkUniqueStrValid]) {
            return ;
        }
        
        if (nil == self.saveFreeUserResRequest) {
            self.saveFreeUserResRequest = [[AMPrecisionSaveFreeUserResRequest alloc] init]; 
        }
        
        self.saveFreeUserResRequest.requestURL = OCEAN_API_URL_PRECISION_SAVE_FREE_USER_RES;  
        self.saveFreeUserResRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_SAVE_FREE_USER_RES;
        self.saveFreeUserResRequest.siteId = [UserDataUtils getPmSiteId];
        self.saveFreeUserResRequest.visitorId = visitorId;
        [self loadObjectsFromRemoteSaveFreeUserRes];
    }else {
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        [self.mNavigationController pushViewController:nextController animated:YES];
        [nextController release];
    }
}


-(void)objManInit {
    objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcachecustomer/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;

    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 100.0 && !isLoading) {
        if(currentAllVisitorPage*DEFAULT_PAGE_SIZE < allVisitorTotalCount) {
            currentAllVisitorPage++;
            [self loadRequest];
        }
    }

}

- (void) onLoginSucc {
    
    [self clearData];
    [self loadGetUserInfoRequest];
//    [self loadRequest];
    //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
    if(self.mLoadingView.loadingView.hidden==YES){
        self.mLoadingView.loadingView.hidden = NO;
    }
//    [self showLoadingView];
    self.allVisitorTableView.tableFooterView = nil;
    
}

- (void) clearData {
    currentAllVisitorPage = 1;
    allVisitorTotalCount = 0;
    [self.sectionGroupDict removeAllObjects];
    [self.sectionGroupArrayKey removeAllObjects];
    self.sectionGroupDict = nil;
    self.sectionGroupArrayKey = nil;
//    [self.allVisitorTableView reloadData];
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [self objManInit];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onLoginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    
    [self.allVisitorTableView addPullToRefreshWithActionHandler:^{
        NSLog(@"refresh dataSource");
        allVisitorTableView.pullToRefreshView.lastUpdatedDate = [NSDate date]; 
        //        [allVisitorTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil afterDelay:2];
        
//        [self clearData];
        self.allVisitorTableView.tableFooterView = nil;
        self.tempCurrentPage = currentAllVisitorPage;
        currentAllVisitorPage = 1;
        [self loadGetUserInfoRequest];
        //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
        if(self.mLoadingView.loadingView.hidden==NO){
            self.mLoadingView.loadingView.hidden = YES;
        }
        //        [self showLoadingView];
        self.allVisitorTableView.tableFooterView = nil;
        isPullViewLoad = YES;
    }];
    
//    [self.allVisitorTableView.pullToRefreshView triggerRefresh];
//    [self objManInit];
    currentAllVisitorPage = 1;
    allVisitorTotalCount = 0;
    
    mSaveFreeUserResWhenLogined = NO;
    mGotoDetail = NO;
//    mReloadList = NO;
    
    isTalkAfterWwLogin = NO;
    isHandShake = NO;
}


- (void)viewDidUnload {
    self.objMan = nil;
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    self.userInfoRequest = nil;
    self.visitorListRequest = nil;
    self.visitorStatusRequest = nil;
    self.talkPermissionRequest = nil;
    self.saveFreeUserResRequest = nil;
    [self.sectionGroupDict removeAllObjects];
    [self.sectionGroupArrayKey removeAllObjects];
    self.sectionGroupDict = nil;
    self.sectionGroupArrayKey = nil;
    self.allVisitorTableView = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (isFirstLoadView) {
        if ([UserDataUtils checkUniqueStrValid]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_PM_SET_FORMALUSER_IMG_VISIBLE object:self];
            [self loadRequest];
        } else {
            [self loadGetUserInfoRequest];
        }

        isFirstLoadView = NO;
    }
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
    
//    if (mReloadList) {
//        [self clearData];
//        [self loadGetUserInfoRequest];
//        [self showLoadingView];
//        self.allVisitorTableView.tableFooterView = nil;
//        mReloadList = NO;
//    }
}

- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

//这个方法告诉表格第section个分组有多少行
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    NSString *key = [self.sectionGroupArrayKey objectAtIndex:section];
    NSArray *visitors = [self.sectionGroupDict objectForKey:key];
    NSInteger j = [visitors count];
    return j;
}

//设置cell高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath { 
    return [AliTableViewCellAllVisitor cellHeight]; 
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 30.0;
}

//以下为增加section title相关

//表格有几个分组
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    NSInteger i = [self.sectionGroupArrayKey count];
    return i;
}

//表格第section分组的名称
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *key = [self.sectionGroupArrayKey objectAtIndex:section];
    
    //替换title-->今天，昨天，前天
    NSString *keyConvert = [AMPrecisionAllVisitorsViewController dateGroup:key];
    return keyConvert;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
    
    AliTableViewCellAllVisitor *cell = (AliTableViewCellAllVisitor *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellAllVisitor cellIdentifer]];
    if (cell == nil)  {
        cell = [AliTableViewCellAllVisitor createCell];
        cell.frame = CGRectMake(0.0, 0.0, 320, [AliTableViewCellAllVisitor cellHeight]-19);
    }
    //某个分组的某一行是什么数据，返回一个UITableViewCell
    NSUInteger section = [indexPath section];
    //获取这个分组的日期名称
    NSLog(@"section = %d, self.sectionGroupArrayKey count = %d", section, [self.sectionGroupArrayKey count]);
    if (section >= [self.sectionGroupArrayKey count]) {
        return cell;
    }
    
    NSString *key = [self.sectionGroupArrayKey objectAtIndex:section];
    //获得日期分组对应下的访客
    NSMutableArray *visitorsArray = [self.sectionGroupDict objectForKey:key];
    
    AMPrecisionVisitor *allVisitor = (AMPrecisionVisitor*)[visitorsArray objectAtIndex:row ] ;
    
    cell.title.text = allVisitor.showName;
    cell.talkBtn.param = allVisitor;
    [cell.talkBtn addTarget:self action:@selector(talkAction:) forControlEvents:UIControlEventTouchUpInside];
    
    return cell;
}


- (IBAction)talkAction:(id)sender {
    [AMLogUtils appendLog: PRECISION_HOME_FOUR];
    
    mGotoDetail = NO;
    AMPrecisionVisitor * visitor = ((AliParamButton *)sender).param;
    if (visitor == nil) {
        return ;
    }
    mCurVisitor = visitor;
    
    if ([UserDataUtils isPmFreeUser]) {
        [self loadTalkPermissionRequest:visitor.visitorId];
    } else {
        [self loadVisitorStatusRequest:visitor.visitorId];
    }
}

//单击行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [AMLogUtils appendLog: PRECISION_HOME_THREE];
    
    NSUInteger section = [indexPath section];
    //获取这个分组的日期名称
    NSString *key = [self.sectionGroupArrayKey objectAtIndex:section];
    //获得日期分组对应下的访客
    NSMutableArray *visitorsArray = [self.sectionGroupDict objectForKey:key];
    NSUInteger row = [indexPath row];
    AMPrecisionVisitor * visitor = (AMPrecisionVisitor*)[visitorsArray objectAtIndex:row ] ;
    
    mCurVisitor = visitor;
    if ([UserDataUtils isPmFreeUser]) {
        mGotoDetail = YES;
        [self loadTalkPermissionRequest:visitor.visitorId];
    } else {
        [self gotoVisitorDetail:YES];
    }
    
    [self.allVisitorTableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [mCurVisitor release];
    [mCurVisitorId release];
    [_visitorListRequest release];
    [controllers release];
    [allVisitorTableView release];
    [_userInfoRequest release];
    [_visitorStatusRequest release];
    [_talkPermissionRequest release];
    [_saveFreeUserResRequest release];
    [objMan release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [_loginUserName release];
    [_sectionGroupDict release];
    [_sectionGroupArrayKey release];
    
    [super dealloc];
}

@end

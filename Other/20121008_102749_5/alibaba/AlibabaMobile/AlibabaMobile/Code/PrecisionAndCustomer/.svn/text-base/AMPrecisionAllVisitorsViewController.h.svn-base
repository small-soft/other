//
//  AMPrecisionAllVisitorsViewController.h
//  AlibabaMobile
//
//  Created by xiaowen on 12-6-25.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <RestKit/RestKit.h>
#import "HJObjManager.h"
#import "AliSegmentedControl.h"
#import "AliLoadingDataView.h"

#import "AMPrecisionVisitorListRequest.h"
#import "AMPrecisionUserInfoRequest.h"
#import "AMPrecisionVisitorStatusRequest.h"
#import "AMPrecisionTalkPermissionRequest.h"
#import "AMPrecisionSaveFreeUserResRequest.h"
#import "AMPrecisionVisitor.h"
#import "SVPullToRefresh.h"

@interface AMPrecisionAllVisitorsViewController : UIViewController <UITabBarDelegate,UITableViewDelegate, UITableViewDataSource,RKObjectLoaderDelegate,UIAlertViewDelegate> {
    
    int allVisitorTotalCount;
    int currentAllVisitorPage;
    BOOL isLoading;
    
    AMPrecisionVisitor *mCurVisitor;
    NSString * mCurVisitorId;
    BOOL mSaveFreeUserResWhenLogined;
    BOOL mGotoDetail;
    BOOL isPullViewLoad;
    
    BOOL isFirstLoadView;
    
    // 旺旺聊天相关
    BOOL isTalkAfterWwLogin;
    BOOL isHandShake;
}

@property (nonatomic,retain) NSMutableArray *controllers;
@property (nonatomic, retain) IBOutlet UITableView *allVisitorTableView;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) AliLoadingDataView * mLoadingView;
@property (nonatomic, retain) UINavigationController * mNavigationController;

@property (nonatomic, retain) AMPrecisionVisitorListRequest * visitorListRequest;
@property (nonatomic, retain) AMPrecisionUserInfoRequest * userInfoRequest;
@property (nonatomic, retain) AMPrecisionVisitorStatusRequest * visitorStatusRequest;
@property (nonatomic, retain) AMPrecisionTalkPermissionRequest * talkPermissionRequest;
@property (nonatomic, retain) AMPrecisionSaveFreeUserResRequest * saveFreeUserResRequest;

@property (nonatomic, retain) NSMutableDictionary * sectionGroupDict;
@property (nonatomic, retain) NSMutableArray * sectionGroupArrayKey;

- (void)loadObjectsFromRemoteAllVisitor;
+ (NSString *)dateGroup:(NSString*)inputDate;
- (id)initWithNavigation:(UINavigationController *)navigation;

@end

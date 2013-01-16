//
//  AMFavoritesViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <RestKit/RestKit.h>
#import "HJObjManager.h"
#import "AMCustomerSuggestListRequest.h"
#import "AliLoadingDataView.h"
#import "AMCustomerSuggestStatRequest.h"
#import "AMCustomerSuggestStatResult.h"
#import "AMCustomerSuggestAddRequest.h"
#import "AMCustomerSuggestListMainModel.h"
#import "OceanClientViewController.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"
@interface AMCustomerSuggestViewController : OceanClientViewController <UITabBarDelegate,UITableViewDelegate, UITableViewDataSource> {
    int suggestTotalCount;
    int currentSuggestPage;
    BOOL isLoading;
    AMCustomerSuggestListRequest *_suggestListRequest;//推荐用户列表请求
    AMCustomerSuggestStatRequest *_suggestStatRequest;
    UINavigationController * mNavigationController;
    BOOL mUpdateHeader;
//    BOOL isLastCustomerSuggestStatLoaded;
    BOOL mIsUserTalk;
    BOOL isFirstLoadHeader;
    BOOL isFirstStateObjectLoad;
    int mCurIdx;
    AMCustomerSuggestListMainModel * mCurCostomer;
//    BOOL isPullViewLoad;
    
    // 旺旺聊天相关
    BOOL isTalkAfterWwLogin;
}

@property (nonatomic, retain) IBOutlet UITableView *suggestTableView;
@property (nonatomic, retain) NSMutableArray* suggestListObjects;
@property (nonatomic, retain) AMCustomerSuggestStatResult* suggestStatObjects;
@property (nonatomic, retain) AMCustomerSuggestListRequest *suggestListRequest;
@property (nonatomic, retain) AMCustomerSuggestStatRequest *suggestStatRequest;
@property (nonatomic, retain) AMCustomerSuggestAddRequest *addRequest;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) AliLoadingDataView * mLoadingView;
@property (nonatomic, retain) UIView*headerView;
@property (nonatomic, retain) UINavigationController * mNavigationController;
@property (nonatomic,assign) BOOL isFirstLoadView;

//防止重新加载时会闪一下的问题 但是这个其实有没有都可以
@property (nonatomic) BOOL isFirstLoad;
@property (nonatomic) BOOL isRefresh;

- (void)loadObjectsFromRemoteSuggestList;
- (id)initWithNavigation:(UINavigationController *)navigation;
//用于延迟加载
-(void)loadRequestForFirstTime;

@end

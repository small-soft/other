//
//  AMFavoritesViewController.h
//  AlibabaMobile
//
//  Created by xiaowen on 12-6-26.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <RestKit/RestKit.h>
#import "HJObjManager.h"
#import "AliLoadingDataView.h"
#import "AMCustomerMyCustomerRequest.h"
#import "AMCustomerMyCustomerGroupRequest.h"
#import "AliTableViewMyCustomerPickerView.h"
#import "AliCustomerSearchView.h"
#import "SVPullToRefresh.h"
#import "OceanClientViewController.h"
@interface AMCustomerMyCustomerViewController : OceanClientViewController <UITabBarDelegate,UITableViewDelegate, UITableViewDataSource,AliTableViewMyCustomerPickerViewDelegate,AliCustomerSearchViewDelegate> {


    int myCustonerTotalCount;
    int currentMyCustomerPage;
    BOOL isLoading;
    AMCustomerMyCustomerRequest *_myCustomerRequest;
    UINavigationController * mNavigationController;
    BOOL isNeedReload;
    NSMutableDictionary *_allAreaDict;
    NSMutableDictionary *_allCategoryDict;
    NSNumber *_totalCount;
    BOOL isPullViewLoad;
    
    BOOL isFromPicker;
    // 旺旺聊天相关
    BOOL isTalkAfterWwLogin;
    NSString *contactName;
    NSString *contactId;
}

@property (nonatomic,retain) IBOutlet UITableView *myCustomerTableView;
@property (nonatomic, retain) NSMutableArray* myCustomersObjects;
@property (nonatomic, retain) NSMutableArray* myCustomersGroupObjects;
@property (nonatomic, retain) NSMutableArray* myCustomersAreaObjects;
@property (nonatomic, retain) AMCustomerMyCustomerRequest *myCustomerRequest;
@property (nonatomic, retain) AMCustomerMyCustomerGroupRequest *myCustomerGroupRequest;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) AliLoadingDataView * mLoadingView;
@property (nonatomic, retain) UINavigationController * mNavigationController;
@property (nonatomic, retain) UIView*headerView;

@property (nonatomic, retain) IBOutlet UIButton *buttonAllCategory;
@property (nonatomic, retain) IBOutlet UIButton *buttonAllArea;
@property (nonatomic, retain) IBOutlet UIButton *buttonQuickSearch;
@property (nonatomic, retain) IBOutlet UIButton *cancelButton;
@property (nonatomic, retain) UILabel *totalCountLabel;
@property (nonatomic,retain)AliTableViewMyCustomerPickerView*categoryPicker;
@property (nonatomic,retain)AliTableViewMyCustomerPickerView*areaPicker;

@property (retain, nonatomic) IBOutlet AliCustomerSearchView *searchView;

@property (nonatomic, retain) IBOutlet UIView * mMyCustomerSelectionView;

@property (nonatomic, retain) NSMutableDictionary *allAreaDict;
@property (nonatomic, retain) NSMutableDictionary *allCategoryDict;
@property (nonatomic, retain) NSNumber *totalCount;

@property (nonatomic, retain) IBOutlet UILabel *totalPreLabel;
@property (nonatomic, retain) IBOutlet UILabel *totalMidLabel;
@property (nonatomic, retain) IBOutlet UILabel *totalEndLabel;
//用于延迟加载
@property (nonatomic,assign)BOOL isFirstLoadView;

- (void)loadObjectsFromRemoteMyCustomer;
- (id)initWithNavigation:(UINavigationController *)navigation;
- (IBAction)cancelbtnClicked:(id)sender;
-(void)loadRequestForFirstTime;
@end

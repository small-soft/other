//
//  AMIMHomeViewController.m
//  AlibabaMobile
//
//  Created by  on 12-6-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>
#import "AMCustomerAndPrecisionHomeViewController.h"
#import "CallBackTool.h"
#import "LoginToken.h"
#import "HJObjManager.h"
#import "HJManagedImageV.h"
#import "StringUtils.h"
#import "UIHelp.h"
#import "AMIMRecentFriendListViewController.h"
#import "AMIMUserDetailViewController.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "MessageCenterButtonView.h"

#import "AMPrecisionAllVisitorsViewController.h"
#import "AMCustomerMyCustomerViewController.h"
#import "AMCustomerSuggestViewController.h"
#import "UserDataUtils.h"

#define COREDATA_CURRENT_CONTEXT @"CurrentCoreDataContext"

#define TAB_CONTENT_ALLVISITOR 0
#define TAB_CONTENT_MYCUSTOMER 1
#define TAB_CONTENT_SUGGEST 2


@interface AMCustomerAndPrecisionHomeViewController()
{
   
    NSArray *  _stateArray;
    UIView * currentView;
}

@property (nonatomic, retain) AliNavigationBackButton * backButton;

@property (nonatomic, retain) NSMutableDictionary * dataDict;

@property (nonatomic,retain) HJObjManager *objMan;

@property (nonatomic, retain) IBOutlet HJManagedImageV * mHeadImage;
@property (nonatomic, retain) IBOutlet UILabel * mNameLabel;
@property (nonatomic, retain) IBOutlet UIButton * mStatePickerBtn;

@property (nonatomic, retain) IBOutlet UIImageView * stateBkImgView;
@property (nonatomic, retain) IBOutlet UIButton * stateBtn;

@property (nonatomic, retain) IBOutlet UIButton * mSettingBtn;

@property (nonatomic, retain) IBOutlet UIImageView * mTopBkImg;

@property (nonatomic, retain) AMCustomerMyCustomerViewController * mMyCustomersViewController;
@property (nonatomic, retain) AMPrecisionAllVisitorsViewController * mAllVisitorsViewController;
@property (nonatomic, retain) AMCustomerSuggestViewController * mSuggestViewController;

@property (retain,nonatomic)AliSegmentedControl *mSegmentedControl;

@end

@implementation AMCustomerAndPrecisionHomeViewController


@synthesize backButton = _backButton;
@synthesize dataDict = _dataDict;

@synthesize objMan = _objMan;
@synthesize mHeadImage = _mHeadImage;
@synthesize mNameLabel = _mNameLabel;
@synthesize mStatePickerBtn = _mStatePickerBtn;
@synthesize mTopBkImg =_mTopBkImg;

@synthesize stateBtn = _stateBtn;
@synthesize stateBkImgView = _stateBkImgView;
@synthesize mSettingBtn = _mSettingBtn;

@synthesize mMyCustomersViewController = _mMyCustomersViewController;
@synthesize mAllVisitorsViewController = _mAllVisitorsViewController;
@synthesize mSuggestViewController = _mSuggestViewController;

@synthesize mSegmentedControl = _mSegmentedControl;
@synthesize businessType = _businessType;
@synthesize parentTitle = _parentTitle;

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_objMan release];
    [_mHeadImage release];
    [_mNameLabel release];
    [_mStatePickerBtn release];
    [_stateArray release];
    [currentView release];
    [_mTopBkImg release];
    [_stateBkImgView release];
    [_stateBtn release];
    [_mSettingBtn release];
    [_mMyCustomersViewController release];
    [_mAllVisitorsViewController release];
    [_mSuggestViewController release];
    
    [_businessType release];
    [_parentTitle release];
    [super dealloc];
}

- (id)init
{
    self = [super initWithNibName:@"AMCustomerAndPrecisionHomeViewController" bundle:nil];
    if (self) {
        NSLog(@"customer and precision home init...");
    }
    return self;
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.leftBarButtonItem = self.backButton;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setFormalUserImgVisable) name:NOTIFICATION_PM_SET_FORMALUSER_IMG_VISIBLE object:nil];
    
    [self setLogo];
    [self objManInit];
    NSLog(@"businessType=%@",self.businessType);

    [self initContentViews];
    [self.view addSubview:self.mSegmentedControl];
    if([@"customer" isEqualToString:self.businessType]){
        [self.mSegmentedControl setSelectedIndex:1];
//        [NSThread sleepForTimeInterval:0.5];
    }else if([@"precision" isEqualToString:self.businessType]){
        [self.mSegmentedControl setSelectedIndex:0];
    }else {
        [self.mSegmentedControl setSelectedIndex:2];
    }
    

}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

-(AliNavigationBackButton*)backButton
{
    if (!_backButton) 
    {
        NSString * title = nil;
        if (_parentTitle) {
            title = _parentTitle;
        } else {
            title = @"返回";
        }
        
        _backButton = [[AliNavigationBackButton alloc] initWithTitle:title];
        _backButton.navigationBackDelegate = self;
    }
    return _backButton;
}

-(void) viewDidUnload
{
    [_objMan release];
    _objMan = nil;
    [_mSegmentedControl release];
    _mSegmentedControl = nil;
    if (currentView) {
        [currentView removeFromSuperview];
        currentView = nil;
    }
    [_mMyCustomersViewController release];
    _mMyCustomersViewController = nil;
    [_mAllVisitorsViewController release];
    _mAllVisitorsViewController = nil;
    [_mSuggestViewController release];
    _mSuggestViewController = nil;
    self.mHeadImage = nil;
    self.mNameLabel = nil;
    self.mStatePickerBtn = nil;
    _stateArray = nil;;
    self.mTopBkImg = nil;
    self.stateBkImgView = nil;
    self.stateBtn = nil;
    self.mSettingBtn = nil;
    
    [super viewDidUnload];
}

-(AliSegmentedControl*)mSegmentedControl
{
    if (_mSegmentedControl==nil) {
        _mSegmentedControl = [[AliSegmentedControl alloc] initWithFrame:CGRectMake(0, 0, 320, 40)];
        _mSegmentedControl.delegate = self;
        
        NSArray *titleArray =  [[NSArray alloc] initWithObjects:@"所有访客",@"我的客户",@"推荐客户",nil];
        for(NSString *title in titleArray){
            [_mSegmentedControl addItem:title];
        }
        
        [self.mSegmentedControl addExImg:@"pay"];
        [self.mSegmentedControl setExImgVisable:NO];
        [titleArray release];
    }
    return _mSegmentedControl;
}

- (void) setLogo
{
    UIImageView * logoImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"logo_topbar"]];
    self.navigationItem.titleView = logoImg;
    [logoImg release];
}

- (void) initContentViews
{
    _mAllVisitorsViewController = [[AMPrecisionAllVisitorsViewController alloc] initWithNavigation:self.navigationController];
    _mMyCustomersViewController = [[AMCustomerMyCustomerViewController alloc] initWithNavigation:self.navigationController];
    _mSuggestViewController = [[AMCustomerSuggestViewController alloc] initWithNavigation:self.navigationController];
    
    currentView = nil;

    //初始化第一个tab view
    UIView *nextView = nil;
    if([@"customer" isEqualToString:self.businessType]){
        _mMyCustomersViewController.view.hidden = NO;
        _mAllVisitorsViewController.view.hidden = YES;
        _mSuggestViewController.view.hidden = YES;
        nextView = _mMyCustomersViewController.view;
    }else if ([@"precision" isEqualToString:self.businessType]){
        _mAllVisitorsViewController.view.hidden = NO;
        _mMyCustomersViewController.view.hidden = YES;
        _mSuggestViewController.view.hidden = YES;
        nextView = _mAllVisitorsViewController.view;  
    }else {
        _mAllVisitorsViewController.view.hidden = YES;
        _mMyCustomersViewController.view.hidden = YES;
        _mSuggestViewController.view.hidden = NO;
        nextView = _mSuggestViewController.view;  
    }

    if(nextView != nil && nextView != currentView){
        [currentView removeFromSuperview];
        [self.view insertSubview:nextView atIndex:0];
        currentView = nextView;
    }
}

- (void) segmentValueChanged:(int)nowIndex
{
    NSLog(@"nowIndex=%d",nowIndex);
    UIView * nextView = nil;;
    switch (nowIndex) {
        case TAB_CONTENT_MYCUSTOMER:
        {
            _mMyCustomersViewController.view.hidden = NO;
            _mAllVisitorsViewController.view.hidden = YES;
            _mSuggestViewController.view.hidden = YES;
            nextView = _mMyCustomersViewController.view;
            [AMLogUtils appendLog: CUSTOMERMANAGER_TAB_TEN];
        }
            break;
        case TAB_CONTENT_ALLVISITOR:
        {
            _mMyCustomersViewController.view.hidden = YES;
            _mAllVisitorsViewController.view.hidden = NO;
            _mSuggestViewController.view.hidden = YES;
            nextView = _mAllVisitorsViewController.view;
            [AMLogUtils appendLog: PRECISION_HOME_ONE];
        }
            break;
        case TAB_CONTENT_SUGGEST:
        {
            _mMyCustomersViewController.view.hidden = YES;
            _mAllVisitorsViewController.view.hidden = YES;
            _mSuggestViewController.view.hidden = NO;
            nextView = _mSuggestViewController.view;
            [AMLogUtils appendLog: CUSTOMERMANAGER_TAB_ELVEN];
        }
            break;
        default:
            break;
    }
    
    if(nextView != nil && nextView != currentView){
        [currentView removeFromSuperview];
        [self.view insertSubview:nextView atIndex:0];
        currentView = nextView;
        //以下代码用于修复在ios4.3版本中无法刷新页面的问题
        if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
        {
            if (currentView ==_mMyCustomersViewController.view) {
                [_mMyCustomersViewController viewWillAppear:YES];
            }else if(currentView == _mSuggestViewController.view){
                [_mSuggestViewController viewWillAppear:YES];
            }else if(currentView == _mAllVisitorsViewController.view){
                [_mAllVisitorsViewController viewWillAppear:YES];
            }  
            
        }
        
    }
}

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"];
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
}

- (void) setFormalUserImgVisable{
    [self.mSegmentedControl setExImgVisable:![UserDataUtils isPmFreeUser]];    
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    if (currentView ==_mMyCustomersViewController.view) {
        [_mMyCustomersViewController viewWillAppear:animated];
    }else if(currentView == _mSuggestViewController.view){
        [_mSuggestViewController viewWillAppear:animated];
    }else if(currentView == _mAllVisitorsViewController.view){
        [_mAllVisitorsViewController viewWillAppear:animated];
    }
}
- (void)viewWillDisappear:(BOOL)animated
{
  	[super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden = NO;
}

@end
//
//  AMOrderManageHomeViewController.m
//  AlibabaMobile
//
//  Created by  on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>
#import "AMOrderManageHomeViewController.h"
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

#import "AMOrderBuyedTableViewController.h"
#import "AMOrderSelledTableViewController.h"
#import "UserDataUtils.h"

#import "AMOrderStateRightViewController.h"
//#import "AMAppDelegate.h"

#define COREDATA_CURRENT_CONTEXT @"CurrentCoreDataContext"

#define TAB_CONTENT_ORDEROUT 0
#define TAB_CONTENT_ORDERIN 1


@interface AMOrderManageHomeViewController()
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

@property (nonatomic, retain) AMOrderBuyedTableViewController * mOrderBuyedTableViewController;
@property (nonatomic, retain) AMOrderSelledTableViewController * mOrderSelledTableViewController;

//@property (retain,nonatomic)AliSegmentedControl *mSegmentedControl;

@property (retain,nonatomic) AMSegmentedCtlWithButton * mSegmentedControl;

@property (retain,nonatomic) AMOrderStateRightViewController * rightViewController;

@end

@implementation AMOrderManageHomeViewController


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

@synthesize mOrderBuyedTableViewController = _mOrderBuyedTableViewController;
@synthesize mOrderSelledTableViewController = _mOrderSelledTableViewController;

@synthesize mSegmentedControl = _mSegmentedControl;
@synthesize businessType = _businessType;
@synthesize parentTitle = _parentTitle;
@synthesize rightViewController = _rightViewController;

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICATION_ORDER_STATE object:nil];
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
    
    [_businessType release];
    [_parentTitle release];
    [_mOrderBuyedTableViewController release];
    [_mOrderSelledTableViewController release];
    
    [_rightViewController release];
    [super dealloc];
}

- (id)init
{
    self = [super initWithNibName:@"AMOrderManageHomeViewController" bundle:nil];
    if (self) {
        NSLog(@"order manmage home init...");

    }
    return self;
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
//     self.navigationController.navigationBarHidden = YES;
    
    
    self.navigationItem.leftBarButtonItem = self.backButton;
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setFormalUserImgVisable) name:NOTIFICATION_PM_SET_FORMALUSER_IMG_VISIBLE object:nil];
    
    [[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICATION_ORDER_STATE object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(restoreViewLocationEvent:) name:NOTIFICATION_ORDER_STATE object:nil];
    
    [self setLogo];
    [self objManInit];
    NSLog(@"businessType=%@",self.businessType);

    [self.view addSubview:self.mSegmentedControl];
    if([@"orderin" isEqualToString:self.businessType]){
        [self.mSegmentedControl setSelectedIndex:1];
    }else if([@"orderout" isEqualToString:self.businessType]){
        [self.mSegmentedControl setSelectedIndex:0];
    }
    
    
    [self initContentViews];
    
    //init order state (right place， must get the window)
    self.rightViewController = [[[AMOrderStateRightViewController alloc] initWithNibName:@"AMOrderStateRightViewController" bundle:nil] autorelease];
//    self.rightViewController = [[AMOrderStateRightViewController alloc]  autorelease];
//    self.rightViewController.view.frame = CGRectMake(320-self.rightViewController.view.frame.size.width,
//                                                     20,
//                                                     self.rightViewController.view.frame.size.width,
//                                                     self.rightViewController.view.frame.size.height);
    self.rightViewController.view.frame = CGRectMake(40,
                                                     20,
                                                     self.rightViewController.view.frame.size.width,
                                                     self.rightViewController.view.frame.size.height);
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    [appDelegate.window addSubview:self.rightViewController.view];
    // invisible left and right view
    
    [self.rightViewController setVisible:NO];
    
    
    
}

-(void)restoreViewLocationEvent:(id)sender{
//    NSString *requestKey = [sender object];
    [self restoreViewLocation];
    
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
            title = @"工具";
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
    [_mOrderSelledTableViewController release];
    _mOrderSelledTableViewController = nil;
    [_mOrderBuyedTableViewController release];
    _mOrderBuyedTableViewController = nil;
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

-(AMSegmentedCtlWithButton*)mSegmentedControl
{
    if (_mSegmentedControl==nil) {
        _mSegmentedControl = [[AMSegmentedCtlWithButton alloc] initWithFrame:CGRectMake(0, 0, 320, 40)];
        _mSegmentedControl.mSegmentedControl.frame = CGRectMake(70, 0, 180, 40);
        self.mSegmentedControl.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
        _mSegmentedControl.delegate = self;
        [self.mSegmentedControl setItemsHidden:UISegmentedControlHidden Hidden:YES];
        [self.mSegmentedControl.button setTitle:@"筛选" forState:UIControlStateNormal];
        self.mSegmentedControl.backButton.hidden = NO;
        [self.mSegmentedControl.button addTarget:self action:@selector(filterOrderState:) forControlEvents:UIControlEventTouchUpInside];
        [self.mSegmentedControl.backButton addTarget:self action:@selector(backToAppCenter:) forControlEvents:UIControlEventTouchUpInside];
        NSArray *titleArray =  [[NSArray alloc] initWithObjects:@"卖出货品",@"买入货品",nil];
        for(NSString *title in titleArray){
            [_mSegmentedControl addItem:title];
        }
        [titleArray release];
    }
    return _mSegmentedControl;
}



-(void) filterOrderState:(id) sender{
    NSLog(@"filterOrderState");
//    [(AMAppDelegate *)[[UIApplication sharedApplication] delegate] makeRightViewVisible];
    [self makeRightViewVisible];
    [self moveToLeftSide];
}



// 订单主页面移向左侧
- (void)moveToLeftSide {
    [self animateHomeViewToSide:CGRectMake(-280.0f,
                                           self.navigationController.view.frame.origin.y,
                                           self.navigationController.view.frame.size.width,
                                           self.navigationController.view.frame.size.height)];
}

// 订单主页面位置恢复
- (void)restoreViewLocation {
//    homeViewIsOutOfStage = NO;
//    [(AMAppDelegate *)[[UIApplication sharedApplication] delegate] makeRightViewDisappear];
    [self makeRightViewDisappear];
    [UIView animateWithDuration:0.3
                     animations:^{
                         self.navigationController.view.frame = CGRectMake(0,
                                                                           self.navigationController.view.frame.origin.y,
                                                                           self.navigationController.view.frame.size.width,
                                                                           self.navigationController.view.frame.size.height);
                     }
                     completion:^(BOOL finished){
                         UIControl *overView = (UIControl *)[[[UIApplication sharedApplication] keyWindow] viewWithTag:1688];
                         [overView removeFromSuperview];
                     }];
}


- (void)makeRightViewVisible {
    self.navigationController.view.layer.shadowColor = [UIColor blackColor].CGColor;
    self.navigationController.view.layer.shadowOpacity = 0.4f;
    self.navigationController.view.layer.shadowOffset = CGSizeMake(12.0, 1.0f);
    self.navigationController.view.layer.shadowRadius = 7.0f;
    self.navigationController.view.layer.masksToBounds = NO;
    [self.rightViewController setVisible:YES];
}

- (void)makeRightViewDisappear{
    [self.rightViewController setVisible:NO];
}

- (void)animateHomeViewToSide:(CGRect)newViewRect {
    [UIView animateWithDuration:0.2
                     animations:^{
                         self.navigationController.view.frame = newViewRect;
                     }
                     completion:^(BOOL finished){
                         UIControl *overView = [[UIControl alloc] init];
                         overView.tag = 1688;
                         overView.backgroundColor = [UIColor clearColor];
                         overView.frame = self.navigationController.view.frame;
                         [overView addTarget:self action:@selector(restoreViewLocation) forControlEvents:UIControlEventTouchDown];
                         [[[UIApplication sharedApplication] keyWindow] addSubview:overView];
                         [overView release];
                     }];
}


-(void) backToAppCenter:(id) sender{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) setLogo
{
    UIImageView * logoImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"logo_topbar"]];
    self.navigationItem.titleView = logoImg;
    [logoImg release];
}

- (void) initContentViews
{
    _mOrderSelledTableViewController = [[AMOrderSelledTableViewController alloc] initWithNavigation:self.navigationController];
    _mOrderBuyedTableViewController = [[AMOrderBuyedTableViewController alloc] initWithNavigation:self.navigationController];
    
    currentView = nil;

    //初始化第一个tab view
    UIView *nextView = nil;
    if([@"orderout" isEqualToString:self.businessType]){
        _mOrderSelledTableViewController.view.hidden = NO;
        _mOrderBuyedTableViewController.view.hidden = YES;
        nextView = _mOrderSelledTableViewController.view;
        _mOrderSelledTableViewController.isReceiveOrderStateNotify = YES;
        _mOrderBuyedTableViewController.isReceiveOrderStateNotify = NO;
    }else if ([@"orderin" isEqualToString:self.businessType]){
//        _mAllVisitorsViewController.view.hidden = NO;
        _mOrderBuyedTableViewController.view.hidden = NO;
        _mOrderSelledTableViewController.view.hidden = YES;

        nextView = _mOrderBuyedTableViewController.view;
        
        _mOrderSelledTableViewController.isReceiveOrderStateNotify = NO;
        _mOrderBuyedTableViewController.isReceiveOrderStateNotify = YES;
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
        case TAB_CONTENT_ORDEROUT:
        {
            _mOrderSelledTableViewController.view.hidden = NO;
            _mOrderBuyedTableViewController.view.hidden = YES;
            nextView = _mOrderSelledTableViewController.view;
            [AMLogUtils appendLog: CUSTOMERMANAGER_TAB_TEN];
            _mOrderSelledTableViewController.isReceiveOrderStateNotify = YES;
            _mOrderBuyedTableViewController.isReceiveOrderStateNotify = NO;
            
        }
            break;
        case TAB_CONTENT_ORDERIN:
        {
            _mOrderSelledTableViewController.view.hidden = YES;
            _mOrderBuyedTableViewController.view.hidden = NO;
            nextView = _mOrderBuyedTableViewController.view;
            _mOrderSelledTableViewController.isReceiveOrderStateNotify = NO;
            _mOrderBuyedTableViewController.isReceiveOrderStateNotify = YES;
        }
            break;
        default:
            break;
    }
    
    if(nextView != nil && nextView != currentView){
        [currentView removeFromSuperview];
        [self.view insertSubview:nextView atIndex:0];
        currentView = nextView;
    }
}

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcacheorder/"];
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
}

- (void)viewWillAppear:(BOOL)animated
{
    self.navigationController.navigationBarHidden = YES;
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
  	[super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden = NO;
}

@end
//
//  AliTabViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTabViewController.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliImageControlFactory.h"
#import "UIHelp.h"


const int DEFAULT_TABBAR_AREA_HEIGHT = 40;
const int DEFAULT_TABBAR_AREA_WIDTH = 320;
const int DEFAULT_TABBAR_WIDTH = 320;
const int DEFAULT_TABBAR_HEIGHT = 40;

@interface AliTabViewController()
{
    int mCurrentTabIndex;
    
    UIViewController * mCurrentViewController;
    AliSegmentedControl  * mSegmentedControl;
    NSMutableArray * mViewControllerArray;
    
}

- (void) segmentValueChanged:(int)nowIndex;
- (UIViewController *) getViewControllerById:(int)tabIndex;
- (void) customTitleBar;
- (void) customTabbarArea;
- (void) navigationBack;

@end


@implementation AliTabViewController

@synthesize dataDict = _dataDict;

#pragma  private funciton
- (void) segmentValueChanged:(int)nowIndex
{
    if(nowIndex != mCurrentTabIndex){
        [self switchContentView:nowIndex];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];
    
    // rocky.wenk: 让tab中的ViewController也可以收到viewWillAppear消息
    UIViewController * controller = [self getViewControllerById:mCurrentTabIndex];
    [controller viewWillAppear: animated];
}

- (void) switchContentView:(int)tabIndex
{
    mCurrentTabIndex = tabIndex;
    UIViewController * controller = [self getViewControllerById:tabIndex];
    [self.view insertSubview:controller.view atIndex:0];
    if(mCurrentViewController != nil)
        [mCurrentViewController.view removeFromSuperview];
    mCurrentViewController = controller;
}

- (UIViewController *) getViewControllerById:(int)tabIndex
{
    if(mViewControllerArray != nil
       && mViewControllerArray.count >0
       && mViewControllerArray.count > tabIndex){
        return [mViewControllerArray objectAtIndex:tabIndex];
    }
    return nil;
}

- (void) customTitleBar
{
    //custome title back button
    if (self.mBackButton == nil) {
        self.mBackButton = [[AliNavigationBackButton alloc] initWithTitle:@"返回"];
    }
    
    self.mBackButton.navigationBackDelegate = self;
    self.navigationItem.leftBarButtonItem = self.mBackButton;
    
    //custome title label
    if (self.mTitleLabel == nil) {
        self.mTitleLabel = [[AliNavigationTitleLabel alloc] initWithTitle:@"标 题"];
    }
    
    self.navigationItem.titleView = self.mTitleLabel;
    
    //add right nav button
    if (self.mRightNavigationItem == nil) {
        self.mRightNavigationItem = [[UIBarButtonItem alloc] init];
    }
    
    self.navigationItem.rightBarButtonItem = self.mRightNavigationItem;
}

-(void) customTabbarArea
{
    UIImageView * tabbarAreaBk = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, DEFAULT_TABBAR_AREA_WIDTH, DEFAULT_TABBAR_AREA_HEIGHT)];
    tabbarAreaBk.image = [UIImage imageNamed:@"bg_tabbar"];
    [self.view insertSubview:tabbarAreaBk atIndex:0];
    [tabbarAreaBk release];
//    AliImageButton * lineImg = [[AliImageControlFactory sharedInstance] getImageButtonWithType:LINE_DIVIDED];
//    lineImg.frame = CGRectMake(0, 40, 320, 2);
//    [self.view addSubview:lineImg];
    
    if (mSegmentedControl == nil) {
        mSegmentedControl = [[AliSegmentedControl alloc] initWithFrame:CGRectMake(0, 0, DEFAULT_TABBAR_WIDTH, DEFAULT_TABBAR_HEIGHT)];
    }
    
    mSegmentedControl.delegate = self;
    [self.view addSubview:mSegmentedControl];
    
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma public function

- (id)init
{
    [super init];
    if (self) {
        self.view.backgroundColor = [UIHelp colorWithHexString:@"0xF5F5F5"];
        [self customTitleBar];
        [self customTabbarArea];
        mViewControllerArray = [[NSMutableArray alloc] init];
        mCurrentTabIndex = 0;
        mCurrentViewController = nil;
        
        self.dataDict = [[NSMutableDictionary alloc] init];
    }
    return self;
}

-(void) addTabPage:(NSString *)tabTitle viewControllerName:(NSString *)viewControllerName
{
    Class class = NSClassFromString(viewControllerName);
    AliTabContentViewController * viewController  = [[class alloc] initWithData:self.dataDict navigationController:self.navigationController];
    
    [mViewControllerArray addObject:viewController];
    [mSegmentedControl addItem:tabTitle];
    /*------修改内存问题，修改人：孟希羲 修改时间：2012.08.03------*/
#warning release the viewController, maybe result to crash
    [viewController release];
}

-(void) dealloc
{
    /*------修改内存问题，修改人：孟希羲 修改时间：2012.08.03------*/
#warning release the viewController, maybe result to crash
    if(mCurrentViewController != nil)
        [mCurrentViewController.view removeFromSuperview];
    self.mBackButton = nil;
    self.mTitleLabel = nil;
    self.mRightNavigationItem = nil;
    [mSegmentedControl release];
    [mViewControllerArray release];
    [_dataDict release];
    
    [super dealloc];
}

//设置导航栏返回按钮文字
- (void) setBackButtonText:(NSString *)backButtonText
{
    if(self.mBackButton)
        [self.mBackButton setTitle:backButtonText];
}

//设置导航栏标题文字
-(void) setTitle:(NSString *)title
{
    if(self.mTitleLabel){
        [self.mTitleLabel setText:title];
        [self.mTitleLabel sizeToFit];
    }
}

//设置导航栏右边的控件，可自定义
-(void) setNavigationRightItem:(UIView *)view
{
    if(self.mRightNavigationItem)
        self.mRightNavigationItem.customView = view;
}

@end

//
//  MyUITabBarController.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MyUITabBarController.h"
#import "AMLogiticsViewController.h"
#import "AMFavoritesViewController.h"
#import "AMIMViewController.h"
#import "AMAppCenterViewController.h"
#import "LoginToken.h"
#import "UIHelp.h"
#import "AMIMHomeViewController.h"
#import "NoticationItem.h"
#import "CallBackTool.h"
#import "AMIMUserDefault.h"
#import "AMIMDefaultStorageHelper.h"
#import "LoginToken.h"
#import "AliTabItemView.h"
#import "AliNavigationViewController.h"
#import "AESCrypto.h"
#import "AliSearchViewController.h"
#import "AliToastView.h"
#import "AMHomeDressViewController.h"
#import "AMHomeFurnitureViewController.h"
#import "AMHomeIndustryViewController.h"
#import "AMHomeMaterialsViewController.h"
#import "AMHomeProductViewController.h"
#import "AMIndustrySelectHomeViewController.h"
#import "AMBeginerNavigateViewControl.h"
#import "UserDataUtils.h"
#import "MessageCenterListViewController.h"

#define SELECTED_VIEW_CONTROLLER_TAG 98456345
#define ITEMID_KEYWORD_NAME @"name"
#define ITEMID_KEYWORD_TITLE @"title"
#define ITEMID_KEYWORD_IMAGE @"image"
#define ITEMID_KEYWORD_FOCUSIMAGE @"focusImage"
#define ITEMID_KEYWORD_VIEWCONTROLLER @"viewController"
#define ITEMID_KEYWORD_VIEW @"view"

#define ITEMNAME_HOME @"home"
#define ITEMNAME_WW @"ww"
#define ITEMNAME_FAV @"fav"
#define ITEMNAME_SEARCH @"search"
#define ITEMNAME_APPCENTER @"appCenter"
#define ITEMNAME_LOGIN @"login"

#define TABBAR_IDX_HOME    0
#define TABBAR_IDX_SEARCH  1
#define TABBAR_IDX_FAV     2
#define TABBAR_IDX_APPCTR  3
#define TABBAR_IDX_WW      4

#define ALERT_IF_LOGIN_WANGWANG_TAG     99
#define ALERT_FORCEQUIT_WANGWANG_TAG    100
#define ALERT_NETWORKERROR_WANGWANG_TAG 101

@interface MyUITabBarController() {
    BOOL isTimeout;
    BOOL loginHere;
    BOOL isLogining;
    
    BOOL isEnterWwAfterWwLogin;
}

-(void)hideTabBar:(id)sender;
-(void)unHideTabBar:(id)sender;

@property(nonatomic) NSUInteger lastSelectedIndex;

@property(nonatomic,retain)NSArray * tabBarItemsSource;
@property(nonatomic,retain)NSArray * tabBarHomeItemsSource;

@property(nonatomic,retain) AMBeginerNavigateViewControl *beginerNavigateViewControl;
@property(nonatomic,retain) AMIndustrySelectHomeViewController *industrySelectHomeViewController;

@property (nonatomic)BOOL tabBatHidden;
@end


@implementation MyUITabBarController

@synthesize aliTabBar = _aliTabBar;
@synthesize contentView = _contentView;
@synthesize tabBarItemArray = _tabBarItemArray;
@synthesize tabBarItemsSource = _tabBarItemsSource;
@synthesize tabBarHomeItemsSource = _tabBarHomeItemsSource;
@synthesize lastSelectedIndex = _lastSelectedIndex;
@synthesize tabBatHidden = _tabBatHidden;
@synthesize mLoadingView = _mLoadingView;

@synthesize beginerNavigateViewControl = _beginerNavigateViewControl;
@synthesize industrySelectHomeViewController = _industrySelectHomeViewController;


-(void)setTabBatHidden:(BOOL)tabBatHidden
{
    if (_tabBatHidden != tabBatHidden) {
        
        //[UIView setAnimationDuration:2.0];
        //[UIView beginAnimations:@"scale" context:nil];
        
        if (tabBatHidden) {
            self.aliTabBar.alpha = 0.0f;
            self.contentView.frame =CGRectMake(0,0,self.view.frame.size.width, self.view.frame.size.height);
        }
        else {
            self.aliTabBar.alpha = 1.0f;
            self.contentView.frame =CGRectMake(0,0,self.view.frame.size.width, self.view.frame.size.height-self.aliTabBar.frame.size.height + 5);
        }
        
        //[UIView commitAnimations];
        _tabBatHidden = tabBatHidden;
    }
}

-(void)initTabBarItemArray
{
    [self.tabBarItemArray removeAllObjects];
    for (NSDictionary*data in self.tabBarItemsSource) {
        NSString*name = [data objectForKey:ITEMID_KEYWORD_NAME];
        
        if ([name isEqualToString:ITEMNAME_HOME]||[name isEqualToString:ITEMNAME_SEARCH]||[name isEqualToString:ITEMNAME_FAV]||[name isEqualToString:ITEMNAME_APPCENTER]||[name isEqualToString:ITEMNAME_WW]) {
            [self.tabBarItemArray addObject:data];
        }
    }
}

-(NSMutableArray*)tabBarItemArray
{
    if (!_tabBarItemArray) {
        _tabBarItemArray = [[NSMutableArray alloc]init];
    }
    return  _tabBarItemArray;
}

- (void) replaceTabItem:(NSString *)sourceName withName:(NSString *)newName{
    NSMutableDictionary * newData;
    for (NSMutableDictionary * data in self.tabBarItemsSource) {
        NSString*keyword = [data objectForKey:ITEMID_KEYWORD_NAME];
        if ([keyword isEqualToString:newName]) {
            newData = data;
            break;
        }
    }
    
    NSUInteger count = [self.tabBarItemArray count];
    for (NSUInteger i=0; i<count; i++) {
        NSMutableDictionary*data = [self.tabBarItemArray objectAtIndex:i];
        NSString*keyword = [data objectForKey:ITEMID_KEYWORD_NAME];
        if ([keyword isEqualToString:sourceName]) {
            [self.tabBarItemArray replaceObjectAtIndex:i withObject:newData];
            break;
        }
    }
}

- (void) setHome
{
    int newIdx = 0;
    newIdx = [UserDataUtils getSelectNumber] - 1;
    if (newIdx < 0 || newIdx >= [_tabBarHomeItemsSource count]) {
        return ;
    }

    NSMutableDictionary * newData = [_tabBarHomeItemsSource objectAtIndex:newIdx];
    [_tabBarItemArray replaceObjectAtIndex:0 withObject:newData];
    
    self.aliTabBar.reload = YES;
    self.aliTabBar.reloadItemContent = YES;
    [self.aliTabBar setNewSelectedItem : 0];
    
    // reload = YES 后需要把旺旺的图标刷新一次
    [self tabBarItemViewUnHighlighted:self.aliTabBar atIndex:TABBAR_IDX_WW];
}

-(NSArray*)tabBarItemsSource
{
    if (!_tabBarItemsSource) {
        UIViewController *viewCtrSearch = [[AliSearchViewController alloc] initWithNibName:@"AliSearchViewController" bundle:nil];        
        UIViewController *viewCtrIm = [[AMIMHomeViewController alloc] init];
        UIViewController *viewCtrFav = [[AMFavoritesViewController alloc] initWithNibName:@"AMFavoritesViewController_iPhone" bundle:nil] ;
        UIViewController *viewCtrApp = [[AMAppCenterViewController alloc] initWithNibName:@"AMAppCenterViewController" bundle:nil] ;
        UIViewController *viewCtrLogin = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] ;
        AliNavigationViewController *search = [[AliNavigationViewController alloc]initWithRootViewController:viewCtrSearch] ;
        AliNavigationViewController *im = [[AliNavigationViewController alloc]initWithRootViewController:viewCtrIm] ;
        AliNavigationViewController *favorites = [[AliNavigationViewController alloc]initWithRootViewController:viewCtrFav] ;
        AliNavigationViewController *app = [[AliNavigationViewController alloc]initWithRootViewController:viewCtrApp] ;
        AliNavigationViewController *login = [[AliNavigationViewController alloc]initWithRootViewController:viewCtrLogin] ;
         
        /* for iOS 4.3 */
        if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
        {
            search.delegate = self;
            im.delegate = self;
            favorites.delegate = self;
            app.delegate = self;
            login.delegate = self;
        }

        int homeIdx = [UserDataUtils getSelectNumber] - 1;
        if (homeIdx < 0 || homeIdx > 4) {
            homeIdx = 0;
        }
        
        _tabBarItemsSource = [[NSArray arrayWithObjects:
                               [self.tabBarHomeItemsSource objectAtIndex:homeIdx],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_SEARCH,ITEMID_KEYWORD_NAME,@"搜索", ITEMID_KEYWORD_TITLE,@"icon_toolbar_search_n.png", ITEMID_KEYWORD_IMAGE,  @"icon_toolbar_search_p.png",ITEMID_KEYWORD_FOCUSIMAGE, search, ITEMID_KEYWORD_VIEWCONTROLLER,[AliTabItemView createView],ITEMID_KEYWORD_VIEW , nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_FAV,ITEMID_KEYWORD_NAME,@"收藏夹", ITEMID_KEYWORD_TITLE,@"icon_toolbar_fav.png", ITEMID_KEYWORD_IMAGE,  @"icon_toolbar_fav_p",ITEMID_KEYWORD_FOCUSIMAGE, favorites, ITEMID_KEYWORD_VIEWCONTROLLER,[AliTabItemView createView],ITEMID_KEYWORD_VIEW , nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_APPCENTER,ITEMID_KEYWORD_NAME,@"工具", ITEMID_KEYWORD_TITLE,@"icon_toolbar_tool.png", ITEMID_KEYWORD_IMAGE,  @"icon_toolbar_tool_p",ITEMID_KEYWORD_FOCUSIMAGE, app, ITEMID_KEYWORD_VIEWCONTROLLER, [AliTabItemView createView],ITEMID_KEYWORD_VIEW ,nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_WW,ITEMID_KEYWORD_NAME,@"旺旺", ITEMID_KEYWORD_TITLE,@"icon_toolbar_ww_dis.png", ITEMID_KEYWORD_IMAGE,  @"icon_toolbar_ww",ITEMID_KEYWORD_FOCUSIMAGE, im, ITEMID_KEYWORD_VIEWCONTROLLER,[AliTabItemView createView],ITEMID_KEYWORD_VIEW , nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_LOGIN,ITEMID_KEYWORD_NAME,@"登录", ITEMID_KEYWORD_TITLE, login, ITEMID_KEYWORD_VIEWCONTROLLER,nil], 
                               nil] retain];
        
//        [viewCtrSearch release];
//        [viewCtrFav release];
//        [viewCtrApp release];
//        [viewCtrLogin release];
//        [viewCtrIm release];
        
        [search release];
        [im release];
        [favorites release];
        [app release];
        [login release];
    }
    
    return _tabBarItemsSource;
}

-(NSArray*)tabBarHomeItemsSource
{
    if (!_tabBarHomeItemsSource) {
        UIViewController *viewCtr1 = [[AMHomeDressViewController alloc] init];
        UIViewController *viewCtr2 = [[AMHomeProductViewController alloc] init];
        UIViewController *viewCtr3 = [[AMHomeFurnitureViewController alloc] init];
        UIViewController *viewCtr4 = [[AMHomeIndustryViewController alloc] init];
        UIViewController *viewCtr5 = [[AMHomeMaterialsViewController alloc] init];

        AliNavigationViewController *navCtr1 = [[AliNavigationViewController alloc]initWithRootViewController:viewCtr1];
        AliNavigationViewController *navCtr2 = [[AliNavigationViewController alloc]initWithRootViewController:viewCtr2];
        AliNavigationViewController *navCtr3 = [[AliNavigationViewController alloc]initWithRootViewController:viewCtr3];
        AliNavigationViewController *navCtr4 = [[AliNavigationViewController alloc]initWithRootViewController:viewCtr4];
        AliNavigationViewController *navCtr5 = [[AliNavigationViewController alloc]initWithRootViewController:viewCtr5];
        
        /* for iOS 4.3 */
        if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
        {
            navCtr1.delegate = self;
            navCtr2.delegate = self;
            navCtr3.delegate = self;
            navCtr4.delegate = self;
            navCtr5.delegate = self;
        }
        
        _tabBarHomeItemsSource = [[NSArray arrayWithObjects:
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_HOME,ITEMID_KEYWORD_NAME,@"首页", ITEMID_KEYWORD_TITLE,@"icon_toolbar_home.png", ITEMID_KEYWORD_IMAGE, @"icon_toolbar_home_p",ITEMID_KEYWORD_FOCUSIMAGE,navCtr1,ITEMID_KEYWORD_VIEWCONTROLLER, [AliTabItemView createView],ITEMID_KEYWORD_VIEW ,nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_HOME,ITEMID_KEYWORD_NAME,@"首页", ITEMID_KEYWORD_TITLE,@"icon_toolbar_home.png", ITEMID_KEYWORD_IMAGE, @"icon_toolbar_home_p",ITEMID_KEYWORD_FOCUSIMAGE,navCtr2, ITEMID_KEYWORD_VIEWCONTROLLER, [AliTabItemView createView],ITEMID_KEYWORD_VIEW ,nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_HOME,ITEMID_KEYWORD_NAME,@"首页", ITEMID_KEYWORD_TITLE,@"icon_toolbar_home.png", ITEMID_KEYWORD_IMAGE, @"icon_toolbar_home_p",ITEMID_KEYWORD_FOCUSIMAGE,navCtr3, ITEMID_KEYWORD_VIEWCONTROLLER, [AliTabItemView createView],ITEMID_KEYWORD_VIEW ,nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_HOME,ITEMID_KEYWORD_NAME,@"首页", ITEMID_KEYWORD_TITLE,@"icon_toolbar_home.png", ITEMID_KEYWORD_IMAGE, @"icon_toolbar_home_p",ITEMID_KEYWORD_FOCUSIMAGE,navCtr4, ITEMID_KEYWORD_VIEWCONTROLLER, [AliTabItemView createView],ITEMID_KEYWORD_VIEW ,nil],
                               [NSDictionary dictionaryWithObjectsAndKeys:ITEMNAME_HOME,ITEMID_KEYWORD_NAME,@"首页", ITEMID_KEYWORD_TITLE,@"icon_toolbar_home.png", ITEMID_KEYWORD_IMAGE, @"icon_toolbar_home_p",ITEMID_KEYWORD_FOCUSIMAGE,navCtr5, ITEMID_KEYWORD_VIEWCONTROLLER, [AliTabItemView createView],ITEMID_KEYWORD_VIEW ,nil],
                               nil] retain];
        [viewCtr1 release];
        [viewCtr2 release];
        [viewCtr3 release];
        [viewCtr4 release];
        [viewCtr5 release];
        
        [navCtr1 release];
        [navCtr2 release];
        [navCtr3 release];
        [navCtr4 release];
        [navCtr5 release];
    }    
    return _tabBarHomeItemsSource;
}

- (void) homeSelect
{
    // 如果为0，表示需要选择行业
//    if(YES){
    if ([UserDataUtils getSelectNumber] == 0 || [UserDataUtils getFirstLaunch]) {
        _industrySelectHomeViewController = [[AMIndustrySelectHomeViewController alloc] initWithNibName:@"AMIndustrySelectHomeViewController" bundle:nil];
        
        // Remove the current view controller's view
        UIView* currentView = [self.view viewWithTag:SELECTED_VIEW_CONTROLLER_TAG];
        [currentView removeFromSuperview];
        
        // Set the view controller's frame to account for the tab bar
        self.industrySelectHomeViewController.view.frame = CGRectMake(0,0,self.view.frame.size.width, self.contentView.frame.size.height);
        
        // Se the tag so we can find it later
        self.industrySelectHomeViewController.view.tag = SELECTED_VIEW_CONTROLLER_TAG;
        
        if ([self.industrySelectHomeViewController.view isDescendantOfView:self.contentView]) {
            [self.contentView bringSubviewToFront:self.industrySelectHomeViewController.view];
        } else {
            [self.contentView addSubview:self.industrySelectHomeViewController.view];
        }
        self.tabBatHidden = YES;
    }
}

- (void) beginerNavigate
{
//    if(YES){
    if ([UserDataUtils getFirstLaunch]) {
        _beginerNavigateViewControl = [[AMBeginerNavigateViewControl alloc] initWithNibName:@"AMBeginerNavigateViewControl" bundle:nil ];
        
        // Remove the current view controller's view
        UIView* currentView = [self.view viewWithTag:SELECTED_VIEW_CONTROLLER_TAG];
        [currentView removeFromSuperview];
        
        // Set the view controller's frame to account for the tab bar
        self.beginerNavigateViewControl.view.frame = CGRectMake(0,0,self.view.frame.size.width, self.contentView.frame.size.height);
        
        // Se the tag so we can find it later
        self.beginerNavigateViewControl.view.tag = SELECTED_VIEW_CONTROLLER_TAG;
        
        if ([self.self.beginerNavigateViewControl.view isDescendantOfView:self.contentView]) {
            [self.contentView bringSubviewToFront:self.self.beginerNavigateViewControl.view];
        } else {
            [self.contentView addSubview:self.beginerNavigateViewControl.view];
        }
        self.tabBatHidden = YES;
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self initTabBarItemArray];
    self.aliTabBar.delegate = self;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(beginerNavigate) name:NOTIFICATION_BEGINER object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(homeSelect) name:NOTIFICATION_HOME_SELECT object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cancelLoginEvent:) name:NOTIFICATION_CANCELLOGIN object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(entryFavEvent:) name:NOTIFICATION_FAV object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(entrySearchEvent:) name:NOTIFICATION_SEARCH object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(entryWWEvent:) name:NOTIFICATION_ENTER_WW object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(entryHomeEvent:) name:NOTIFICATION_HOME object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucessEvent:) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginEvent:) name:NOTIFICATION_WW_LOGIN_EVENT object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(hideTabBar:) name:NOTIFICATION_HIDETABBAR object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(unHideTabBar:) name:NOTIFICATION_UNHIDETABBAR object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onNetworkError) name:NOTIFICATION_NETWORKERROR object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(forceDisconnect) name:NOTIFICATION_FORCEDISCONNECT object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(doWwLogin) name:NOITFICATION_RECONNECTWW object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setHome) name:NOTIFICATION_CHANGE_HOME object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onDoWwLoginEvent) name:NOTIFICATION_DO_WW_LOGIN object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onLogout) name:NOTIFICATION_QUITWANGWANG object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onLogout) name:NOTIFICATION_LOGOUT object:nil];
    
    self.view.backgroundColor = [UIHelp colorWithHexString:@"0xF5F5F5"];
    loginHere = NO;
    isLogining = NO;
    self.aliTabBar.alpha = 1.0f;
    self.contentView.frame = CGRectMake(0,0,self.view.frame.size.width, self.view.frame.size.height-self.aliTabBar.frame.size.height + 5);

	// Do any additional setup after loading the view, typically from a nib.
}

-(void)hideTabBar:(id)sender{
    self.tabBatHidden = YES;
}

-(void)unHideTabBar:(id)sender{
    self.tabBatHidden = NO;    
}

-(void)cancelLoginEvent:(id)sender{

    if (self.aliTabBar.selectedItem >= self.tabBarItemArray.count) {
        return ;
    }
    
    NSDictionary*data = [self.tabBarItemArray objectAtIndex:self.aliTabBar.selectedItem];
    NSString*keyword = [data objectForKey:ITEMID_KEYWORD_NAME];
    
    if([keyword isEqualToString:ITEMNAME_FAV]||[keyword isEqualToString:ITEMNAME_WW]){
        [self.aliTabBar setNewSelectedItem:(NSInteger)self.lastSelectedIndex];
        self.tabBatHidden = NO;
    }
}

-(void)loginSucessEvent:(id)sender{
    if (self.aliTabBar.selectedItem >= self.tabBarItemArray.count) {
        return ;
    }
    
    NSDictionary*data = [self.tabBarItemArray objectAtIndex:self.aliTabBar.selectedItem];
    NSString*keyword = [data objectForKey:ITEMID_KEYWORD_NAME];
    
        if([keyword isEqualToString:ITEMNAME_FAV]||[keyword isEqualToString:ITEMNAME_WW]){
        self.aliTabBar.reloadItemContent = YES;
        [self.aliTabBar setNewSelectedItem:self.aliTabBar.selectedItem];
        self.tabBatHidden = NO;
    }
}

-(void)entryHomeEvent:(id)sender{
    [self entryTabBarItem:ITEMNAME_HOME];
}

-(void)entryTabBarItem:(NSString*)name{
    NSUInteger count = [self.tabBarItemArray count];
    // 先看tabBar中有没有
    for (NSUInteger i=0; i<count; i++) {
        NSDictionary*data = [self.tabBarItemArray objectAtIndex:i];
        NSString*keyword = [data objectForKey:ITEMID_KEYWORD_NAME];
        if ([keyword isEqualToString:name]) {
            self.lastSelectedIndex = self.aliTabBar.selectedItem;
            [self.aliTabBar setNewSelectedItem:i];
            return;
        }
    }
    return ;
}

-(void) entryMsgCenter {
    [self entryTabBarItem:ITEMNAME_HOME];

    MessageCenterListViewController * msgCenterView = [[[MessageCenterListViewController alloc] init] autorelease];
    NSDictionary * data = [self.tabBarItemArray objectAtIndex:0];
    UINavigationController * homeCtr = [data objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER];
    
    [homeCtr popToRootViewControllerAnimated:NO];
    [homeCtr pushViewController:msgCenterView animated:YES];
}

-(void)entryWWEvent:(id)sender {
    [self entryTabBarItem:ITEMNAME_WW];
}

-(void)entryFavEvent:(id)sender{
    [self entryTabBarItem:ITEMNAME_FAV];
}

-(void)entrySearchEvent:(id)sender{
    [self entryTabBarItem:ITEMNAME_SEARCH];
}

-(UIImage*)tabBarBackgroundImage:(AliCustomTabBar *)tabBar {
    return [UIImage imageNamed:@"bg_home_tab.png"];
}

- (NSUInteger)tabBarItemCount:(AliCustomTabBar*)tabBar {
    return [self.tabBarItemArray count];
}

-(void)tabBarItemViewDidSelected:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex {
    BOOL isLogin=NO;
    NSString *userName = [LoginToken getLoginUserName];
    
    if([userName length] > 3){
        isLogin = YES;
    }
    
    // Remove the current view controller's view
    UIView* currentView = [self.view viewWithTag:SELECTED_VIEW_CONTROLLER_TAG];
    [currentView removeFromSuperview];
    
    NSDictionary* data = [self.tabBarItemArray objectAtIndex:itemIndex];
    NSString *itemName = [data objectForKey:ITEMID_KEYWORD_NAME];
    UIViewController* viewController;
    
    if (!isLogin && ([itemName isEqualToString:ITEMNAME_FAV])) {
        for (NSDictionary* temp in self.tabBarItemsSource) {
            NSString *tempName = [temp objectForKey:ITEMID_KEYWORD_NAME];
            if ([tempName isEqualToString:ITEMNAME_LOGIN]) {
                viewController = [temp objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER];
                break;
            }
        }
        self.tabBatHidden=YES;
    }
    else {
        viewController = [data objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER];
        self.tabBatHidden=NO;
    }
    
    // Set the view controller's frame to account for the tab bar
    viewController.view.frame = CGRectMake(0,0,self.view.frame.size.width, self.contentView.frame.size.height);
    
    // Se the tag so we can find it later
    viewController.view.tag = SELECTED_VIEW_CONTROLLER_TAG;
    
    if ([viewController.view isDescendantOfView:self.contentView]) {
        [self.contentView bringSubviewToFront:viewController.view];
    } else {
        [self.contentView addSubview:viewController.view];
    }
    
    if([itemName isEqualToString:ITEMNAME_HOME]){
        int newIdx = 0;
        newIdx = [UserDataUtils getSelectNumber] - 1;
        if (newIdx < 0 || newIdx >= [_tabBarHomeItemsSource count]) {
            
        }
        else {
            switch (newIdx) {
                case 0:
                    [AMLogUtils appendLog:APP_HOME_BAR_ONE_ONE];
                    break;
                case 1:
                    [AMLogUtils appendLog:APP_HOME_BAR_ONE_TWO];
                    break;
                case 2:
                    [AMLogUtils appendLog:APP_HOME_BAR_ONE_THREE];
                    break;
                case 3:
                    [AMLogUtils appendLog:APP_HOME_BAR_ONE_FOUR];
                    break;
                case 4:
                    [AMLogUtils appendLog:APP_HOME_BAR_ONE_FIVE];
                    break;               
                default:
                    break;
            }
        }
        
    }else if([itemName isEqualToString:ITEMNAME_WW]){
        [AMLogUtils appendLog:APP_HOME_BAR_TWO];
    }else if ([itemName isEqualToString:ITEMNAME_FAV]) {
        [AMLogUtils appendLog:APP_HOME_BAR_THREE];
    }else if ([itemName isEqualToString:ITEMNAME_APPCENTER]){
        [AMLogUtils appendLog:APP_HOME_BAR_TWELVE];
    }else if ([itemName isEqualToString:ITEMNAME_SEARCH]){
        [AMLogUtils appendLog:APP_HOME_BAR_ELEVEN];
    }

    self.lastSelectedIndex = self.aliTabBar.selectedItem;
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
    {
        [viewController viewWillAppear:NO];
    }
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        self.mLoadingView.noDataMessageLabel.text = @"旺旺登录中...";
        
        [self.view addSubview:self.mLoadingView];
        [self.mLoadingView setHidden:NO];
    }
    return _mLoadingView;
}

- (void) showLoadingView
{
//    if(self.view.frame.size.height == 480){
//        self.mLoadingView.frame = CGRectMake(self.mLoadingView.frame.origin.x, self.mLoadingView.frame.origin.y + 44, self.mLoadingView.frame.size.width, self.mLoadingView.frame.size.height);
//    }
//    [self.mLoadingView setHidden:NO];
    [self.mLoadingView showLoadingView];
}

-(void) endLoadingView {
//  [self.mLoadingView setHidden:YES];
    [self.mLoadingView endLoadingView];
}

-(BOOL)tabBarItemViewShouldDidSelected:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex {
    int count = self.tabBarItemArray.count;
    if (itemIndex >= count || self.aliTabBar.selectedItem >= count) {
        return NO;
    }

    NSDictionary *itemData = [self.tabBarItemArray objectAtIndex:itemIndex];
    NSString *name = [itemData objectForKey:ITEMID_KEYWORD_NAME];
    if([name isEqualToString:ITEMNAME_WW]){
        NSString *loginUserName=nil;
        loginUserName=[LoginToken getLoginUserName];
        if([loginUserName length] > 3){
            if([LoginToken isWangWangLogined]){
                return YES;
            }else{
                if(!isLogining){
                    isEnterWwAfterWwLogin = YES;
                    [self shouldLoginWw];
                }
                return NO;
            }
        }
        else {
            [self gotoLogin: YES: YES];
            return NO;
        }
    }
    return YES;
}

- (void) onDoWwLoginEvent {
    isEnterWwAfterWwLogin = NO;
    [self shouldLoginWw];
}

- (void) shouldLoginWw {
    if ([LoginToken isAppLogined]) {
        if ([LoginToken isChildAccountLogined]) {
            NSString * errorMsg = [NSString stringWithFormat:@"暂不支持子帐号登陆"]; ;
            [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show];
        } else {
            UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"提醒" message:@"其他已登录旺旺将被登出" delegate:self cancelButtonTitle:@"取消" otherButtonTitles: @"确定",nil]autorelease];
            alert.tag = ALERT_IF_LOGIN_WANGWANG_TAG;
            [alert show];
            
            isLogining = YES;
            loginHere = YES;
        }
    } else {
        [self gotoLogin: YES: isEnterWwAfterWwLogin];
    }
}

- (void) gotoLogin:(BOOL) isLoginWw : (BOOL) isEnterWw {
    AMIMViewController *nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
    nextController.hidesBottomBarWhenPushed = YES;
    nextController.loginWangwang = isLoginWw;
    nextController.enterWangwang = isEnterWw;
    
    NSDictionary* data = [self.tabBarItemArray objectAtIndex:self.aliTabBar.selectedItem];
    AliNavigationViewController* viewController = [data objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER];
    [viewController pushViewController:nextController animated:YES];
   
}

- (UIControl*) tabBarItemView:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex {
    // Get the right data
    NSDictionary* data = [self.tabBarItemArray objectAtIndex:itemIndex];
    // Return the image for this tab bar item
    AliTabItemView *control = [data objectForKey:ITEMID_KEYWORD_VIEW];
    control.itemIcon.image = [UIImage imageNamed:[data objectForKey:ITEMID_KEYWORD_IMAGE]];
    control.itemTitle.text = [data objectForKey:ITEMID_KEYWORD_TITLE];
    control.itemHighlighted=NO;
    
    if (!control.itemTitle.text) {
        control.itemIcon.frame = CGRectMake((control.frame.size.width - control.itemIcon.frame.size.width)/2, (control.frame.size.height - control.itemIcon.frame.size.height)/2, control.itemIcon.frame.size.width, control.itemIcon.frame.size.height);
    }
    
    return control;
}

-(void)tabBarItemViewHighlighted:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex {
    if (itemIndex >= self.tabBarItemArray.count) {
        return ;
    }

    NSDictionary* data = [self.tabBarItemArray objectAtIndex:itemIndex];
    // Return the image for this tab bar item
    AliTabItemView *control = [data objectForKey:ITEMID_KEYWORD_VIEW];
    control.itemIcon.image = [UIImage imageNamed:[data objectForKey:ITEMID_KEYWORD_FOCUSIMAGE]];
    control.itemHighlighted=YES;
}

-(void)tabBarItemViewUnHighlighted:(AliCustomTabBar *)tabBar atIndex:(NSUInteger)itemIndex {
    if (itemIndex >= self.tabBarItemArray.count) {
        return ;
    }

    NSDictionary* data = [self.tabBarItemArray objectAtIndex:itemIndex];
    // Return the image for this tab bar item
    AliTabItemView *control = [data objectForKey:ITEMID_KEYWORD_VIEW];
    if (itemIndex == TABBAR_IDX_WW && [LoginToken isWangWangLogined]) {
        control.itemIcon.image = [UIImage imageNamed:[data objectForKey:ITEMID_KEYWORD_FOCUSIMAGE]];
    } else {
        control.itemIcon.image = [UIImage imageNamed:[data objectForKey:ITEMID_KEYWORD_IMAGE]];        
    }

    control.itemHighlighted=NO;
}

-(void) onLogout {
    [self tabBarItemViewUnHighlighted:self.aliTabBar atIndex:TABBAR_IDX_WW];
}

- (void) doWwLogin {
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_WW_START_LOGIN object:self];
    
    AMIMUserDefault * user = [AMIMDefaultStorageHelper getLastLoginedUser];
    AESCrypto * crypto = [[AESCrypto alloc] init];
    
    CallBackTool *tool = [CallBackTool create];
    
    NSString *realPassword = [crypto decryptText:(NSData *)(user.passwd)];
    if ([realPassword length] == 17 && user.isSpecialPassWord) {
        realPassword = [realPassword substringToIndex:[realPassword length]-1];
    }
    
    [tool userLogin:user.uid password:realPassword loginStatus:(EnLoginStatus)(user.status)];
    isTimeout = YES;
    //[self performSelector:@selector(timeOut) withObject:nil afterDelay:30.0];
}

- (void) timeOut {
	if (![NSThread isMainThread]) {
		[self performSelectorOnMainThread:@selector(timeOut) withObject:nil waitUntilDone:YES];
		return;
	}
	if (isTimeout == YES) {
        [self performSelectorOnMainThread:@selector(endLoadingView) withObject:nil waitUntilDone:NO];
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:NSLocalizedString(@"Network error, please sign in again.", nil) 
							  message:nil
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	}
}

- (void) onLoginEvent:(NoticationItem *) dic {
    isTimeout = NO;

	if (dic == nil) {
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:nil
							  message:NSLocalizedString(@"Unknown error", nil) 
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	} else if (dic.errorCode == RESULT_OKEY) {
        [self refreshUI];
	} else if (dic.errorCode == eLOGIN_NO_ACNT) {
        
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:nil
							  message:NSLocalizedString(@"Member ID does not exist.", nil) 
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	} else if (dic.errorCode == eLOGIN_WRONG_PWD) {
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:nil
							  message:NSLocalizedString(@"Incorrect password!", nil) 
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	} else if (dic.errorCode == eLOGIN_TIMEOUT) {
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:nil
							  message:NSLocalizedString(@"登录超时.", nil) 
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	} else if (dic.errorCode == eLOGIN_SYS_BLK || dic.errorCode == eLOGIN_FORBIDDEN) {
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:nil
							  message:NSLocalizedString(@"This account is blocked!", nil) 
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	}else {
		UIAlertView *alert = [[UIAlertView alloc] 
							  initWithTitle:nil
							  message:NSLocalizedString(@"Unknown error", nil) 
							  delegate:self 
							  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
							  otherButtonTitles:nil];
		[alert show];
		[alert release];
	}
    
    if(loginHere && dic.errorCode != RESULT_OKEY){
        loginHere = NO;
        isLogining = NO;
    }
    
    [self performSelectorOnMainThread:@selector(endLoadingView) withObject:nil waitUntilDone:NO];
}

- (void) onWwLoginEvent:(NSNotification *) notification {
    NoticationItem * dic = [notification object];
    [self performSelectorOnMainThread:@selector(onLoginEvent:) withObject:dic waitUntilDone:NO];
}

- (void) refreshUI {
	//[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(timeOut) object:nil];
    
    [LoginToken setWangWangLogined:YES];
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_WW_LOGIN_SUCC object:self];
    
    [self tabBarItemViewUnHighlighted:self.aliTabBar atIndex:TABBAR_IDX_WW];

    if(loginHere){
        loginHere = NO;

        if (isEnterWwAfterWwLogin) {
            [self entryTabBarItem:ITEMNAME_WW];
            self.tabBatHidden = NO;
            isEnterWwAfterWwLogin = NO;
        }
        
        isLogining = NO;
        
        AMAppDelegate * appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        appDelegate.isWwNeedReconnect = NO;
    }
}

inline void sig_do_nothing(int signo)
{
	return ;
}

- (void) forceDisconnect {
    isLogining = NO;
//    [LoginToken setWangWangLogined:NO];
	[self performSelectorOnMainThread:@selector(forceQuit) withObject:nil waitUntilDone:YES];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (alertView.tag) {
        // 是否旺旺登录的弹出框
        case ALERT_IF_LOGIN_WANGWANG_TAG:
        {
            // 确定按钮
            if (buttonIndex == 1) {
                // loading show
                [self performSelectorOnMainThread:@selector(showLoadingView) withObject:nil waitUntilDone:NO];
                
                [self performSelectorInBackground:@selector(doWwLogin) withObject:nil];
            }else {
                isLogining = NO;
                loginHere = NO;
            }
        }
            break;
            
        case ALERT_FORCEQUIT_WANGWANG_TAG:
        case ALERT_NETWORKERROR_WANGWANG_TAG:
        {
            NSDictionary *itemData = [self.tabBarItemArray objectAtIndex:self.aliTabBar.selectedItem];
            NSString *name = [itemData objectForKey:ITEMID_KEYWORD_NAME];
            
            //if(buttonIndex == 0 && [name isEqualToString:ITEMNAME_WW]){
            
            if(buttonIndex == 0 ) {
                //by tom.lih
                if([LoginToken isWangWangLogined]){
                    [LoginToken setWangWangLogined:NO];
                    [[InternetDataTool create].operationQueue cancelAllOperations];
                
                    CallBackTool *tool = [CallBackTool create];
                    [tool logOff];
                    [self performSelectorOnMainThread:@selector(initWWNavController) withObject:nil waitUntilDone:YES];
                
                }
                
                if([name isEqualToString:ITEMNAME_WW]){
                    [self entryTabBarItem:ITEMNAME_APPCENTER];
                }
            }
        }
            break;
            
        default:
            NSLog(@"other message box!");
            break;
    }
}

- (void) initWWNavController {
    
    [self onLogout];
    
    NSUInteger wwIndex=0;
    NSUInteger count = [self.tabBarItemArray count];
    for (NSUInteger i=0; i<count; i++) {
        NSMutableDictionary*data = [self.tabBarItemArray objectAtIndex:i];
        NSString*keyword = [data objectForKey:ITEMID_KEYWORD_NAME];
        if ([keyword isEqualToString:ITEMNAME_WW]) {
            wwIndex=i;
            break;
        }
    }

    int iCount;
    int index;
    iCount =[ [[[self.tabBarItemArray objectAtIndex:wwIndex] objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER] viewControllers] count];
    
    for ( index =iCount; index > 1; index--) {
        [[[self.tabBarItemArray objectAtIndex:wwIndex] objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER] popViewControllerAnimated:NO];
    }
    

}
- (void) forceQuit {
    //UINavigationController * wangwangNavigationController =  [self.viewControllers objectAtIndex:2];
   /* NSDictionary* data = [self.tabBarItems objectAtIndex:2];
    UINavigationController* wangwangNavigationController = [data objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER];
    [wangwangNavigationController popToRootViewControllerAnimated:NO];    
    */
//    [LoginToken setWangWangLogined:NO];
//    [self onLogout];

	UIAlertView *alert = [[UIAlertView alloc]
						  initWithTitle:@"下线通知"
						  message:@"您的帐号在另一客户端登录，您被迫下线" 
						  delegate:self 
						  cancelButtonTitle:@"确定" 
						  otherButtonTitles:nil];
    alert.tag = ALERT_FORCEQUIT_WANGWANG_TAG;
	[alert show];
	[alert release];
	sigset_t newmask;
	sigset_t oldmask;
	signal(SIGPIPE, sig_do_nothing);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGPIPE);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
}

- (void) onNetworkError {
    [self performSelectorOnMainThread:@selector(endLoadingView) withObject:nil waitUntilDone:NO];
    AMAppDelegate * appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    
    if(appDelegate.isBackground){
        appDelegate.isWwNeedReconnect = YES;
    }
    
    if(appDelegate.isWwNeedReconnect){
        //by tom.lih
        [LoginToken setWangWangLogined:NO];
        [[InternetDataTool create].operationQueue cancelAllOperations];
        CallBackTool *tool = [CallBackTool create];
        [tool logOff];

        sigset_t newmask;
        sigset_t oldmask;
        signal(SIGPIPE, sig_do_nothing);
        sigemptyset(&newmask);
        sigaddset(&newmask, SIGPIPE);
        sigprocmask(SIG_BLOCK, &newmask, &oldmask);
        return;
    }
    
    isLogining = NO;

//    CallBackTool *tool = [CallBackTool create];
//    [tool logOff];
//    [CallBackTool destory];
    
//    [InternetDataTool destoryObject];
    
	sigset_t newmask;
	sigset_t oldmask;
	signal(SIGPIPE, sig_do_nothing);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGPIPE);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	[self performSelectorOnMainThread:@selector(showNetworkError) withObject:nil waitUntilDone:YES];
}

- (void) showNetworkError {
//    [LoginToken setWangWangLogined:NO];
//    [self onLogout];
    
    NSDictionary* data = [self.tabBarItemArray objectAtIndex:2];
    UINavigationController* wangwangNavigationController = [data objectForKey:ITEMID_KEYWORD_VIEWCONTROLLER];
    [wangwangNavigationController popToRootViewControllerAnimated:NO];
    
	UIAlertView *alert = [[UIAlertView alloc]
						  initWithTitle:@"下线通知"
						  message:@"网络错误" 
						  delegate:self 
						  cancelButtonTitle:@"确定" 
						  otherButtonTitles:nil];
    alert.tag = ALERT_NETWORKERROR_WANGWANG_TAG;
	[alert show];
	[alert release];
}

- (void)dealloc {

    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [_aliTabBar release];
    [_tabBarItemArray release];
    [_contentView release];
    [_tabBarItemsSource release];
    [_tabBarHomeItemsSource release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [_beginerNavigateViewControl release];
    [_industrySelectHomeViewController release];
    
    [super dealloc];
}

- (void)viewDidUnload {

//     _mLoadingView = nil;
    self.mLoadingView = nil;
    [_tabBarItemArray release];
    _tabBarItemArray = nil;
    [_tabBarItemsSource release];
    _tabBarItemsSource = nil;
    [_tabBarHomeItemsSource release];
    _tabBarHomeItemsSource = nil;
    if (_industrySelectHomeViewController) {
        [_beginerNavigateViewControl release];
        _beginerNavigateViewControl = nil;
    }
    if (_industrySelectHomeViewController) {
        [_industrySelectHomeViewController release];
        _industrySelectHomeViewController = nil;
    }
    
    [self setAliTabBar:nil];
    [self setContentView:nil];
    [super viewDidUnload];
}

-(void)viewWillAppear:(BOOL)animated
{
    [self beginerNavigate];  
    [super viewWillAppear:animated];
}

- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController {  
    [viewController viewWillAppear:NO];  
}  

- (void)navigationController:(UINavigationController *)navigationController   
      willShowViewController:(UIViewController *)viewController animated:(BOOL)animated { 
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
    {
//        [viewController viewWillAppear:animated];  
        //[viewController viewWillDisappear:animated];
    }
}  

- (void)navigationController:(UINavigationController *)navigationController   
       didShowViewController:(UIViewController *)viewController animated:(BOOL)animated { 
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
    {
        [viewController viewDidAppear:animated];  
 
    }
}  

@end

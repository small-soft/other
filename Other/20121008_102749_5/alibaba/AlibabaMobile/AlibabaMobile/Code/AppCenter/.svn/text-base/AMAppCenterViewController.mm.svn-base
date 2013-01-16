//
//  AMAppCenterViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAppCenterViewController.h"
#import "AMBlockBoxCell.h"
#import "AMLogiticsViewController.h"
#import "AMFavoritesViewController.h"
#import "AMIMHomeViewController.h"
#import "AMBannerContentDetailViewController.h"
#import "LoginToken.h"
#import "AMAppDelegate.h"
#import "AMMoreViewController.h"
#import "LogoutRequest.h"
#import "InternetDataTool.h"
#import "CallBackTool.h"
#import "ConstDef.h"
#import "AliToastView.h"
#import "AMIMViewController.h"
#import "AMNewsViewController.h"
#import "AMMarketpriceViewController.h"
#import "AMCategoryViewController.h"
#import "ImageMagazineCategoryViewController.h"
#import "AliSearchViewController.h"
#import "AliNavigationViewController.h"
#import "AMRegisterViewController.h"
#import "AMOrderDetailViewController.h"
#import "AMCustomerAndPrecisionHomeViewController.h"
#import "AMOrderManageHomeViewController.h"


#define INFOVIEW_CENTER_MAX_Y 65
#define INFOVIEW_CENTER_MIN_Y 8

#define DATD_KEYWORD_TITLE  (@"title")
#define DATD_KEYWORD_IMAGE  (@"image")
#define DATD_KEYWORD_FOCUSIMAGE  (@"focusImage")
#define DATD_KEYWORD_SELECTOR  (@"selector")

@interface AMAppCenterViewController ()

@property (nonatomic,retain) NSMutableArray* blockBoxData;
@property (nonatomic) BOOL showInfo;
@property (nonatomic,retain)UIBarButtonItem*backButtonView;
@property (retain,nonatomic)LogoutRequest *logoutRequset;
@property (nonatomic)  int btnPressedCode; //登录0,注册1，切换2,注销3
@property (nonatomic,retain) AMIMViewController * loginViewCtr;

@end

@implementation AMAppCenterViewController
@synthesize contentTable = _contentTable;
@synthesize infoButton = _infoButton;
@synthesize infoButtonUp = _infoButtonUp;
@synthesize infoView = _infoView;
@synthesize showInfoView = _showInfoView;
@synthesize currentUserLabel = _currentUserLabel;
@synthesize loginButton = _loginButton;
@synthesize registerButton = _registerButton;
@synthesize blockBoxData = _blockBoxData;
@synthesize showInfo = _showInfo;
@synthesize backButtonView = _backButtonView;
@synthesize logoutRequset = _logoutRequset;
@synthesize btnPressedCode = _btnPressedCode;
@synthesize loginViewCtr = _loginViewCtr;

-(LogoutRequest*)logoutRequset
{
    if (!_logoutRequset) {
        _logoutRequset = [[LogoutRequest alloc] init]; 
        _logoutRequset.requestURL=OCEAN_API_URL_LOGOUT;
    }
    
    _logoutRequset.accessToken=[LoginToken getAccessToken]; 
    UIDevice * device = [UIDevice currentDevice];
    _logoutRequset.appId = AMCONST_APP_ID;
    _logoutRequset.terminalId = device.uniqueIdentifier;
    return _logoutRequset;
}

-(void)setShowInfo:(BOOL)showInfo
{
    _showInfo = showInfo;
    CGFloat _changeY=0;
    if (_showInfo) {    
        [self.infoButton setHidden:YES];
        [self.infoButtonUp setHidden:NO];
        _changeY = INFOVIEW_CENTER_MAX_Y;
    }
    else {
        [self.infoButton setHidden:NO];
        [self.infoButtonUp setHidden:YES];       
        _changeY = INFOVIEW_CENTER_MIN_Y;
    }
        
    [UIView setAnimationDuration:1.0];
    [UIView beginAnimations:@"flipping" context:nil];   
    [self.infoView setCenter:CGPointMake(160, _changeY)];
    [UIView commitAnimations];
}

-(void)entryHome
{
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_HOME object:self];
}

-(void)entryWW
{
    [AMLogUtils appendLog: APP_CENTER_THREE]; 
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ENTER_WW object:self];
}

-(void)entrySearch
{
//    AliSearchViewController *categoryListController  = [[AliSearchViewController alloc] initWithNibName:@"AliSearchViewController" bundle:nil];
//    [self.navigationController pushViewController:categoryListController animated:YES];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SEARCH object:self];
}

-(void)entryCategory
{
    AMCategoryViewController *categoryListController  = [[[AMCategoryViewController alloc] initWithNibName:@"AMCategoryViewController" bundle:nil] autorelease];
    categoryListController.parentTitle = @"应用中心";
    [self.navigationController pushViewController:categoryListController animated:YES];
}

-(void)entryImageMagazine
{
    // Pictorials
    ImageMagazineCategoryViewController *imageMagazineCategoryViewController = [[[ImageMagazineCategoryViewController alloc] init]autorelease];
    imageMagazineCategoryViewController.parentTitle = @"应用中心";
    [self.navigationController pushViewController:imageMagazineCategoryViewController animated:YES];
}

-(void)entryPrice
{
    AMMarketpriceViewController *marketpriceListController  = [[[AMMarketpriceViewController alloc] initWithNibName:@"AMMarketpriceViewController" bundle:nil]autorelease];
    marketpriceListController.parentTitle = @"应用中心";
    [self.navigationController pushViewController:marketpriceListController animated:YES];
}

-(void)entryNews
{
    AMNewsViewController *newsListController  = [[[AMNewsViewController alloc] initWithNibName:@"AMNewsViewController" bundle:nil]autorelease];
    newsListController.parentTitle = @"应用中心";
    [self.navigationController pushViewController:newsListController animated:YES];
}

-(void)entryOrderManage
{
    
}

-(void)entryBusiness
{
    
}

-(void)entryLogitics
{
    [AMLogUtils appendLog: APP_CENTER_ONE]; 
    
    AMLogiticsViewController *viewCtr = [[AMLogiticsViewController alloc] initWithNibName:@"AMLogiticsViewController_iPhone" bundle:nil];    
    viewCtr.parentTitle = @"应用中心";
    [self.navigationController pushViewController:viewCtr animated:YES];
}

-(void)entryFav
{
   [AMLogUtils appendLog: APP_CENTER_TWO]; 
   
   [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FAV object:self];
}

-(void)entryForum
{
    [AMLogUtils appendLog: APP_CENTER_SIX];

    AMBannerContentDetailViewController *viewController = [[[AMBannerContentDetailViewController alloc] initWithNibName:@"AMBannerContentDetailViewController" bundle:nil] autorelease];

    viewController.showToolBar=YES;
    viewController.parentTitle = @"应用中心";
    viewController.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:viewController animated:YES];
}

//精准营销跳转
-(void)entryPrecision
{
    [AMLogUtils appendLog: APP_CENTER_SEVEN];
    
    if ([LoginToken isAppLogined]) {
        if ([LoginToken isChildAccountLogined]) {
            [self showChildAccountUnavailable];
        } else {
            AMCustomerAndPrecisionHomeViewController *viewCtr = [[[AMCustomerAndPrecisionHomeViewController alloc] initWithNibName:@"AMCustomerAndPrecisionHomeViewController" bundle:nil]autorelease];
            viewCtr.businessType = @"precision";
            viewCtr.parentTitle = @"应用中心";
            [self.navigationController pushViewController:viewCtr animated:YES];
        }
    } else {
        [self enterLogin];
    }
}

//询盘管理跳转
-(void)entryCustomer
{
    [AMLogUtils appendLog: APP_CENTER_EIGHT];
    
    if ([LoginToken isAppLogined]) {
        if ([LoginToken isChildAccountLogined]) {
            [self showChildAccountUnavailable];
        } else {
            AMCustomerAndPrecisionHomeViewController *viewCtr = [[[AMCustomerAndPrecisionHomeViewController alloc] initWithNibName:@"AMCustomerAndPrecisionHomeViewController" bundle:nil]autorelease];
            viewCtr.businessType = @"customer";
            viewCtr.parentTitle = @"应用中心";
            [self.navigationController pushViewController:viewCtr animated:YES];
        }
    } else {
        [self enterLogin];
    }
}

-(void) showChildAccountUnavailable{
    NSString * errorMsg = [NSString stringWithFormat:@"该功能未获授权请更换帐号操作"]; ;
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show];
}

//买入货品
-(void)entryOrderIn
{
    
    if ([LoginToken isAppLogined]) {
        AMOrderManageHomeViewController *viewCtr = [[[AMOrderManageHomeViewController alloc] initWithNibName:@"AMOrderManageHomeViewController" bundle:nil]autorelease];
        viewCtr.businessType = @"orderin";
        viewCtr.parentTitle = @"应用中心";

        [self.navigationController pushViewController:viewCtr animated:YES];
    } else {
        [self enterLogin];
    }
}

//卖出货品
-(void)entryOrderOut
{
    
    if ([LoginToken isAppLogined]) {
        AMOrderManageHomeViewController *viewCtr = [[[AMOrderManageHomeViewController alloc] initWithNibName:@"AMOrderManageHomeViewController" bundle:nil]autorelease];
        viewCtr.businessType = @"orderout";
        viewCtr.parentTitle = @"应用中心";

        [self.navigationController pushViewController:viewCtr animated:YES];
    } else {
        [self enterLogin];
    }
}
-(void) entryOrders
{
    AMOrderDetailViewController * con = [[[AMOrderDetailViewController alloc ] init] autorelease];
    [self.navigationController pushViewController:con animated:YES];
}

-(NSMutableArray*)blockBoxData
{
    if (!_blockBoxData) {
          _blockBoxData = [[NSArray arrayWithObjects:
                         [NSDictionary dictionaryWithObjectsAndKeys:@"首页", DATD_KEYWORD_TITLE,@"App_icon_home.png", DATD_KEYWORD_IMAGE,@"entryHome", DATD_KEYWORD_SELECTOR,nil],
                         [NSDictionary dictionaryWithObjectsAndKeys:@"旺旺", DATD_KEYWORD_TITLE,@"App_icon_ww.png", DATD_KEYWORD_IMAGE,@"entryWW" ,DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"搜索", DATD_KEYWORD_TITLE,@"App_icon_search.png", DATD_KEYWORD_IMAGE,@"entrySearch" , DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"类目浏览", DATD_KEYWORD_TITLE,@"App_icon_list.png", DATD_KEYWORD_IMAGE,@"entryCategory",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"热门画报", DATD_KEYWORD_TITLE,@"App_icon_pictorial.png", DATD_KEYWORD_IMAGE,@"entryImageMagazine",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"价格行情", DATD_KEYWORD_TITLE,@"App_icon_price.png", DATD_KEYWORD_IMAGE,@"entryPrice",  DATD_KEYWORD_SELECTOR,nil],      
                          [NSDictionary dictionaryWithObjectsAndKeys:@"最新资讯", DATD_KEYWORD_TITLE,@"App_icon_new.png", DATD_KEYWORD_IMAGE,@"entryNews",  DATD_KEYWORD_SELECTOR,nil],
                        //  [NSDictionary dictionaryWithObjectsAndKeys:@"订单管理", DATD_KEYWORD_TITLE,@"App_icon_order.png", DATD_KEYWORD_IMAGE,@"entryOrderManage",  DATD_KEYWORD_SELECTOR,nil],
                        //  [NSDictionary dictionaryWithObjectsAndKeys:@"生意经", DATD_KEYWORD_TITLE,@"App_icon_bussines.png", DATD_KEYWORD_IMAGE,@"entryBusiness",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"收藏夹", DATD_KEYWORD_TITLE,@"App_icon_fav.png", DATD_KEYWORD_IMAGE,@"entryFav",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"物流", DATD_KEYWORD_TITLE,@"App_icon_logistics.png", DATD_KEYWORD_IMAGE,@"entryLogitics",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"论坛", DATD_KEYWORD_TITLE,@"App_icon_forum.png", DATD_KEYWORD_IMAGE,@"entryForum",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"精准营销", DATD_KEYWORD_TITLE,@"App_icon_marketing.png", DATD_KEYWORD_IMAGE,@"entryPrecision",  DATD_KEYWORD_SELECTOR,nil],
                          [NSDictionary dictionaryWithObjectsAndKeys:@"询盘管理", DATD_KEYWORD_TITLE,@"App_icon_advisory.png", DATD_KEYWORD_IMAGE,@"entryCustomer",  DATD_KEYWORD_SELECTOR,nil],
                        [NSDictionary dictionaryWithObjectsAndKeys:@"卖出货品", DATD_KEYWORD_TITLE,@"App_icon_sale.png", DATD_KEYWORD_IMAGE,@"entryOrderOut",  DATD_KEYWORD_SELECTOR,nil],
                        [NSDictionary dictionaryWithObjectsAndKeys:@"买入货品", DATD_KEYWORD_TITLE,@"App_icon_buy.png", DATD_KEYWORD_IMAGE,@"entryOrderIn",  DATD_KEYWORD_SELECTOR,nil],
//                        [NSDictionary dictionaryWithObjectsAndKeys:@"订单详情", DATD_KEYWORD_TITLE,@"App_icon_advisory.png", DATD_KEYWORD_IMAGE,@"entryOrders",  DATD_KEYWORD_SELECTOR,nil],
                          nil] retain];
    }
    return _blockBoxData;
}

-(UIBarButtonItem*)backButtonView
{
    if (!_backButtonView) {
        _backButtonView = [[UIBarButtonItem alloc]init];
        UIButton * button = [UIButton buttonWithType:UIButtonTypeCustom];

         [button setImage:[UIImage imageNamed:@"icon_app_info"] forState:UIControlStateNormal];
         button.frame = CGRectMake(0, 0, 30, 29); 
               
        [button addTarget:self action:@selector(navigationBack) forControlEvents:UIControlEventTouchUpInside];
        _backButtonView.customView = button;
    }
    return _backButtonView;
}

- (void)dealloc {
    [_contentTable release];
    [_blockBoxData release];
    [_infoButton release];
    [_infoView release];
    [_infoButtonUp release];
    [_currentUserLabel release];
    [_showInfoView release];
    [_backButtonView release];
    [_logoutRequset release];
    [_loginButton release];
    [_registerButton release];
    [_loginViewCtr release];
    [super dealloc];
}

-(void)move:(UIPanGestureRecognizer*)gesture {
    CGPoint translatedPoint = [gesture translationInView:self.infoView];

    static CGFloat _firstY=0;
  
    CGFloat _changeY=0;
    if([gesture state] == UIGestureRecognizerStateBegan) {
        _firstY = [self.infoView center].y;
    }
    
    _changeY = translatedPoint.y+_firstY;
    if (_changeY<INFOVIEW_CENTER_MIN_Y) 
    {
        _changeY = INFOVIEW_CENTER_MIN_Y;
    }
    
    if (_changeY>INFOVIEW_CENTER_MAX_Y) {
        _changeY = INFOVIEW_CENTER_MAX_Y;
    }
    
    if([gesture state] == UIGestureRecognizerStateEnded) {
        if (translatedPoint.y<=0) {
            self.showInfo = NO;
        }
        if (translatedPoint.y>0) {
            self.showInfo = YES;
        }       
    }
    else {
        translatedPoint = CGPointMake(160, _changeY);
        
        [self.infoView setCenter:translatedPoint];
    }
}

-(void)navigationBack
{
    AMMoreViewController *viewController = [[[AMMoreViewController alloc] initWithNibName:@"AMMoreViewController_iPhone" bundle:nil] autorelease];
    viewController.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:viewController animated:YES];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    UIPanGestureRecognizer *panRecognizer =[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(move:)];
    [self.infoView addGestureRecognizer:panRecognizer];

    [panRecognizer release];
    
    [self.navigationController setNavigationBarHidden:NO animated:YES];
    
    self.navigationItem.leftBarButtonItem = self.backButtonView;
    
    UIImageView * logoImageView = [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"logo_topbar"]];
    self.navigationItem.titleView = logoImageView;
    [logoImageView release];
}

-(void)viewWillAppear:(BOOL)animated
{
    NSString *loginUserName=[LoginToken getLoginUserName];
    if (loginUserName&&loginUserName.length>0) {
        self.currentUserLabel.text = [@"当前帐户:" stringByAppendingString:loginUserName];
        [self.loginButton setTitle:@"切换帐户" forState:UIControlStateHighlighted];
        [self.loginButton setTitle:@"切换帐户" forState:UIControlStateNormal];
        [self.loginButton setTitle:@"切换帐户" forState:UIControlStateSelected];

        [self.registerButton setTitle:@"注销帐户" forState:UIControlStateHighlighted];
        [self.registerButton setTitle:@"注销帐户" forState:UIControlStateNormal];
        [self.registerButton setTitle:@"注销帐户" forState:UIControlStateSelected];
    }
    else {
        self.currentUserLabel.text = @"当前帐户:未登录";

        [self.loginButton setTitle:@"登录帐户" forState:UIControlStateHighlighted];
        [self.loginButton setTitle:@"登录帐户" forState:UIControlStateNormal];
        [self.loginButton setTitle:@"登录帐户" forState:UIControlStateSelected];
        
        [self.registerButton setTitle:@"注册帐户" forState:UIControlStateHighlighted];
        [self.registerButton setTitle:@"注册帐户" forState:UIControlStateNormal];
        [self.registerButton setTitle:@"注册帐户" forState:UIControlStateSelected];
    }
    [super viewWillAppear:animated];
}

-(void)viewWillDisappear:(BOOL)animated
{
    self.showInfo=NO;
}

- (void)viewDidUnload
{
    [self setContentTable:nil];
    _blockBoxData = nil;
    [self setInfoButton:nil];
    [self setInfoView:nil];
    [self setInfoButtonUp:nil];
    [self setCurrentUserLabel:nil];
    [self setShowInfoView:nil];
    [self setLoginButton:nil];
    [self setRegisterButton:nil];
    self.loginViewCtr = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_app"];
        self.tabBarItem.title=@"应用中心";
    }
    
    return self;
}

- (IBAction)infoButtonPressed {
    self.showInfo=!self.showInfo;
}

- (void)logoutWW
{
    if([LoginToken isWangWangLogined]){
        [LoginToken setWangWangLogined:NO];
        [[InternetDataTool create].operationQueue cancelAllOperations];
        CallBackTool *tool = [CallBackTool create];
        //by tom.lih
        [tool logOff];
        
        sigset_t newmask;
        sigset_t oldmask;
        signal(SIGPIPE, sig_do_nothing);
        sigemptyset(&newmask);
        sigaddset(&newmask, SIGPIPE);
        sigprocmask(SIG_BLOCK, &newmask, &oldmask);
        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_QUITWANGWANG object:nil];
    }
}

- (void) userlogout
{
    [self logoutWW];
    [self logOutCNA]; 
}

- (void) enterLogin {
    if (!self.loginViewCtr) {
        self.loginViewCtr = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
    }
    
    self.loginViewCtr.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:self.loginViewCtr animated:YES];
}

- (IBAction)changeAccount {
    _loginButton.enabled =false;
    _registerButton.enabled =false;
    NSString *loginUserName=[LoginToken getLoginUserName];
    if (loginUserName && loginUserName.length>0) {
        _btnPressedCode=2;//切换用户
    }else {
        _btnPressedCode=0;//登录
    }
    
    [self enterLogin];
    
    _loginButton.enabled =true;
    _registerButton.enabled =true;   
}

inline void sig_do_nothing(int signo)
{
	return ;
}

- (IBAction)logOutButtonPressed {
    
    NSString *loginUserName=[LoginToken getLoginUserName];
    NSLog(@"login user name: %@", loginUserName);
    if (loginUserName&&loginUserName.length>0) {
        _btnPressedCode=3;
        _loginButton.enabled =false;
        _registerButton.enabled =false;
        [self performSelectorInBackground:@selector(userlogout) withObject:nil];
    }
    else {
        NSLog(@"registering...");
        _btnPressedCode=1;
        _loginButton.enabled =false;
        _registerButton.enabled =false;
        
        AMRegisterViewController * registerControl = [[[AMRegisterViewController alloc]init ] autorelease];
        
        registerControl.backController = self;
        [self.navigationController pushViewController:registerControl animated:YES];
        _loginButton.enabled =true;
        _registerButton.enabled =true;
//        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:ALIBABA_CHINA_WEB_SITE]];
     //   [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"未登录"] show];

    }
}

- (void)logOutCNA {
    if ([LoginToken isAppLogined]) {
        //检查accesstoken是否过期
        [LoginToken checkAccessTokenExpired];
        
        // Load the object model via RestKit
        RKObjectManager* objectManager = [RKObjectManager sharedManager];
        objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
        
        [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_LOGOUT usingBlock:^(RKObjectLoader* loader) {
            // Change Method to POST
            loader.delegate = self;
            loader.method = RKRequestMethodPOST;
            loader.params = self.logoutRequset;
        }];

    }
}
#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"Loaded objects: %@", objects);    
    [LoginToken setLoginParameter :0 :@"" :@"" :@"" :@"" :@""];     
   self.currentUserLabel.text = @"当前帐户:未登录";
    [self.loginButton setTitle:@"登录帐户" forState:UIControlStateHighlighted];
    [self.loginButton setTitle:@"登录帐户" forState:UIControlStateNormal];
    [self.loginButton setTitle:@"登录帐户" forState:UIControlStateSelected];
    
    [self.registerButton setTitle:@"注册帐户" forState:UIControlStateHighlighted];
    [self.registerButton setTitle:@"注册帐户" forState:UIControlStateNormal];
    [self.registerButton setTitle:@"注册帐户" forState:UIControlStateSelected];

    if (_btnPressedCode==3) {
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"注销成功"] show];
    }

    //注销成功后，发送注销消息，在原来的的逻辑上做了推迟
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_LOGOUT object:self];
    _loginButton.enabled =true;
    _registerButton.enabled =true;  
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
	NSLog(@"Hit error: %@", error);  
    
    if (_btnPressedCode==3) {
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"注销失败"] show];
    }
    _loginButton.enabled =true;
    _registerButton.enabled =true;
}


#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AMBlockBoxCell cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    int num= [self.blockBoxData count]/[AMBlockBoxCell cellBoxViewArrayCount];
  
    if ([self.blockBoxData count]%[AMBlockBoxCell cellBoxViewArrayCount]) {
        num++;
    }
    return num;
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AMBlockBoxCell *cell = (AMBlockBoxCell *)[tableView dequeueReusableCellWithIdentifier: [AMBlockBoxCell cellIdentifer]];
    if (cell == nil)  
    {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMBlockBoxCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMBlockBoxCell class]])
                cell = (AMBlockBoxCell *)oneObject;
         }
    NSUInteger index = [indexPath row] *[AMBlockBoxCell cellBoxViewArrayCount];
    
    for (AMBoxView *box in cell.cellBoxViewArray) {
        if (index>=[self.blockBoxData count]) {
            break;
        }
        box.tag = index;
        NSDictionary *data = [self.blockBoxData objectAtIndex:index++]; 
        box.boxIcon.image = [UIImage imageNamed:[data objectForKey:DATD_KEYWORD_IMAGE]];
        
        box.boxTitle.text = [data objectForKey:DATD_KEYWORD_TITLE];
       [box addTarget:self action:@selector(boxUpAction:)  forControlEvents:UIControlEventTouchUpInside];    
       [box addTarget:self action:@selector(boxDownAction:) forControlEvents:UIControlEventTouchDown];   
        [box addTarget:self action:@selector(boxUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside]; 
    }
     return cell;
}

-(void)boxDownAction:(AMBoxView*)sender
{
    sender.boxFocusIcon.image = [UIImage imageNamed:@"App_icon_press"]; 
}
-(void)boxUpAction:(AMBoxView*)sender
{
    NSDictionary *data = [self.blockBoxData objectAtIndex:sender.tag]; 
   [self performSelector:NSSelectorFromString([data objectForKey:DATD_KEYWORD_SELECTOR])];
   sender.boxFocusIcon.image = nil; 
}

-(void)boxUpOutsideAction:(AMBoxView*)sender
{
    sender.boxFocusIcon.image = nil; 
}

@end

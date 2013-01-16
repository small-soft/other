//
//  AMHomeBaseViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-22.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomeBaseViewController.h"
#import "MessageCenterButtonView.h"
#import "LoginToken.h"
#import "AMLogUtils.h"
#import "AMAppDelegate.h"
#import "MessageCenterListViewController.h"
#import "AMIMViewController.h"
#import "AMIndustrySelectHomeViewController.h"
#import "AMIndustySelectHomeView.h"

@interface AMHomeBaseViewController ()
@property (nonatomic,retain) AliNavigationBackButton *button;
@property (nonatomic,retain) AMIndustySelectHomeView *industySelectHomeView;
@property (nonatomic,assign) BOOL isIndustryViewShow;
@property (nonatomic,assign) CGFloat industySelectHomeViewHeight;
@end

@implementation AMHomeBaseViewController
@synthesize funcListTable = _funcListTable;
@synthesize observer = _observer;
@synthesize navBgImgeView = _navBgImgeView;
@synthesize button = _button;
@synthesize sourceData = _sourceData;
@synthesize menuViewCount;
@synthesize industySelectHomeView = _industySelectHomeView;
@synthesize industrySelectPickView = _industrySelectPickView;
@synthesize isIndustryViewShow;
@synthesize industySelectHomeViewHeight;

#pragma mark control method
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (id)init
{
    self = [super init];
    if (self) {  
        self.observer = [[RKReachabilityObserver alloc] initWithHost:AMCONST_HOST];	
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reachabilityChanged:) name:RKReachabilityDidChangeNotification object:self.observer];
        
        MessageCenterButtonView * msgButton;
        NSString *loginUserName=nil;
        loginUserName=[LoginToken getLoginUserName];
        if([loginUserName length] > 3){
            AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
            msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:[appDelegate getUnReadMsgNum]];
        }else{
            msgButton = [[MessageCenterButtonView alloc] initWithState:NO num:0];
        }
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_RECV object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_READ object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(gotoMessageCenter) name:NOTIFICATION_MSG_GOTO_MESSAGE_CENTER object:nil];
        
        //        [msgButton changeLoginState:NO];
        [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
        [msgButton release];
        
        self.navigationItem.rightBarButtonItem = rightItem;
        [rightItem release];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_LOGOUT object:nil];
    }

    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    if ([self showBackButton]) {
        self.navigationItem.leftBarButtonItem = self.button;
    }
    _industySelectHomeView = [AMIndustySelectHomeView createView];
    self.industySelectHomeView.delegate = self;
    [self.view addSubview:self.industySelectHomeView];
    self.isIndustryViewShow = NO;
    self.industySelectHomeViewHeight = self.industySelectHomeView.frame.size.height;
    
    _industrySelectPickView = [AMIndustrySelectPickView createView];
    self.industrySelectPickView.delegate = self;
    self.industrySelectPickView.lableTitle.text = [self commonHomeViewBackButtonTitle];
    self.navigationItem.titleView = self.industrySelectPickView;
    self.industrySelectPickView.lableTitle.frame = CGRectMake(self.industrySelectPickView.lableTitle.frame.origin.x - 5 , self.industrySelectPickView.lableTitle.frame.origin.y, self.industrySelectPickView.lableTitle.frame.size.width, self.industrySelectPickView.lableTitle.frame.size.height);
    self.industrySelectPickView.mSelectTypeButtonUp.frame = CGRectMake(self.industrySelectPickView.mSelectTypeButtonUp.frame.origin.x - 5, self.industrySelectPickView.mSelectTypeButtonUp.frame.origin.y, self.industrySelectPickView.mSelectTypeButtonUp.frame.size.width, self.industrySelectPickView.mSelectTypeButtonUp.frame.size.height);
    self.industrySelectPickView.mSelectTypeButtonDown.frame = CGRectMake(self.industrySelectPickView.mSelectTypeButtonDown.frame.origin.x - 5, self.industrySelectPickView.mSelectTypeButtonDown.frame.origin.y, self.industrySelectPickView.mSelectTypeButtonDown.frame.size.width, self.industrySelectPickView.mSelectTypeButtonDown.frame.size.height);
    [self.industrySelectPickView.mSelectTypeButtonUp setImage:[UIImage imageNamed:@"h_com_drop01_nor"] forState:UIControlStateNormal];
    [self.industrySelectPickView.mSelectTypeButtonDown setImage:[UIImage imageNamed:@"h_com_drop_nor"] forState:UIControlStateNormal];
//    [self.industrySelectPickView sizeToFit];
    
    
    self.industrySelectPickView.mSelectTypeButtonUp.hidden = YES;
    
    self.funcListTable = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStylePlain];
    self.funcListTable.frame = CGRectMake(self.funcListTable.frame.origin.x, self.funcListTable.frame.origin.y, self.funcListTable.frame.size.width, self.funcListTable.frame.size.height);
    self.funcListTable.delegate = self;
    self.funcListTable.dataSource = self;
    self.funcListTable.backgroundColor = [UIColor clearColor];
    self.funcListTable.separatorColor = [UIColor clearColor];
//    self.funcListTable.showsVerticalScrollIndicator = YES;
//    [self.funcListTable sizeToFit];
//    self.funcListTable.autoresizesSubviews = YES;
//    self.funcListTable.bounces = YES;
    self.funcListTable.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview:self.funcListTable];
    [self.view bringSubviewToFront:self.funcListTable];
    
    menuViewCount = 0;
    
}

- (void)viewDidUnload
{
    [self.funcListTable removeFromSuperview];
    self.funcListTable = nil;
    self.navBgImgeView = nil;
    [_sourceData release];
    _sourceData = nil;
    self.industySelectHomeView = nil;
    self.industrySelectPickView = nil;
    self.button = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}
- (void)viewWillAppear:(BOOL)animated
{
    self.industySelectHomeView.frame = CGRectMake(self.industySelectHomeView.frame.origin.x, self.industySelectHomeView.frame.origin.y, self.industySelectHomeView.frame.size.width,0);
    self.navigationController.navigationBar.hidden = NO;
    
    self.isIndustryViewShow = NO;
    self.industrySelectPickView.isButtonUp = false;
    [(MessageCenterButtonView *)self.navigationItem.rightBarButtonItem.customView setHidden:NO];
    self.industrySelectPickView.mSelectTypeButtonUp.hidden = YES;
    self.industrySelectPickView.mSelectTypeButtonDown.hidden = NO;

    [super viewWillAppear:animated];
    
}

-(void)viewWillDisappear:(BOOL)animated
{

    [super viewWillDisappear:animated];
//    [self.navigationController setNavigationBarHidden:NO animated:YES];
    
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_observer release];
    [_funcListTable release];
    [_navBgImgeView release];
    [_button release];
    [_sourceData release];
    [_industySelectHomeView release];
    [_industrySelectPickView release];

    [super dealloc];
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark restkit received update
- (void)reachabilityChanged:(NSNotification *)notification {
    RKReachabilityObserver* observer = (RKReachabilityObserver *) [notification object];
    
    RKLogCritical(@"AMHomeBaseViewController - Received reachability update: %@", observer);
    
    if ([observer isNetworkReachable]) {
        if ([observer isConnectionRequired]) {
            return;
        }            
        
        if (RKReachabilityReachableViaWiFi == [observer networkStatus]) {
            // Online via WiFi
            NSLog(@"Online via WiFi...");
        } else if (RKReachabilityReachableViaWWAN == [observer networkStatus]) {
            // Online via 3G or Edge
            NSLog(@"Online via 3G or Edge...");
        }
    } else {
        // Network unreachable!
        NSLog(@"Network unreachable!");
    }
}

#pragma mark MessageCenter 
- (void)loginOut
{
    self.navigationItem.rightBarButtonItem = nil;
    MessageCenterButtonView *msgButton = [[MessageCenterButtonView alloc] initWithState:NO num:0];    
    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];
    //修改人 孟希羲
    [msgButton release];
}

- (void)gotoMessageCenter {
    // Add log trace point here
    [AMLogUtils appendLog: APP_HOME_PAGE_SIX];
    
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){ 
        [self openMsgList];
    }else{
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;   
        [self.navigationController pushViewController:nextController animated:YES];            
    } 
}

- (IBAction)msgBtnAction:(MessageCenterButtonView *)sender
{
    [AMLogUtils appendLog:INDUSTRIAL_DRESS_PAGE_ONE];
    sender.hightlightedImg.alpha = 0.0;
    [self gotoMessageCenter];
}

- (void) recvNewMsg
{
    NSString * loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){  
        AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        
        int newMsgNum =  [appDelegate getUnReadMsgNum];
        self.navigationItem.rightBarButtonItem = nil;
        MessageCenterButtonView * msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:newMsgNum];
        //        [msgButton changeLoginState:YES];
        //        [msgButton setMsgNum:newMsgNum];
        [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
        
        self.navigationItem.rightBarButtonItem = rightItem;
        [rightItem release];
        [msgButton release];
    }
}

- (void) loginSucc
{  
    self.navigationItem.rightBarButtonItem = nil;
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    int newMsgNum =  [appDelegate getUnReadMsgNum];
    MessageCenterButtonView * msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:newMsgNum];
    
    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];
    [msgButton release];
}

-(void)openMsgList{
    MessageCenterListViewController * msgViewController = [[MessageCenterListViewController alloc] init];
    msgViewController.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:msgViewController animated: YES];
    [msgViewController release];
}

#pragma mark common Home View method

-(AliNavigationBackButton*)button
{
    if (!_button) {
        NSString *title = [self commonHomeViewBackButtonTitle];
        if (!title) {
            title = @"返回";
        }
        _button = [[AliNavigationBackButton alloc] initWithTitle:title];
        _button.navigationBackDelegate = self;
        [(UIButton*)_button.customView setBackgroundImage:nil forState:UIControlStateNormal];
        [(UIButton*)_button.customView setBackgroundImage:nil forState:UIControlStateHighlighted];
        
    }
    return _button;
}

-(void)changePickFrame:(CGFloat)x yframe:(CGFloat)y
{
    self.industrySelectPickView.mSelectTypeButtonUp.frame = CGRectMake(self.industrySelectPickView.mSelectTypeButtonUp.frame.origin.x - x, self.industrySelectPickView.mSelectTypeButtonUp.frame.origin.y, self.industrySelectPickView.mSelectTypeButtonUp.frame.size.width, self.industrySelectPickView.mSelectTypeButtonUp.frame.size.height);
    self.industrySelectPickView.mSelectTypeButtonDown.frame = CGRectMake(self.industrySelectPickView.mSelectTypeButtonDown.frame.origin.x - x, self.industrySelectPickView.mSelectTypeButtonDown.frame.origin.y, self.industrySelectPickView.mSelectTypeButtonDown.frame.size.width, self.industrySelectPickView.mSelectTypeButtonDown.frame.size.height);
}

-(BOOL)showBackButton
{
    return NO;
}

-(NSString*)commonHomeViewBackButtonTitle
{
    return nil;
}

- (void) navigationBack
{
//    AMIndustrySelectHomeViewController *industrySelectController = [[AMIndustrySelectHomeViewController alloc] initWithNibName:@"AMIndustrySelectHomeViewController" bundle:nil ];
//    [self.navigationController pushViewController:industrySelectController animated:NO];
//    [industrySelectController release];
    //不用navigation的方式，用下拉方式展示
    [self showTableView];
}

#pragma mark AMIndustrySelectPickViewDelegate Methods
-(void)industrySelectPickViewEvent
{
    [self showTableView];
}
#pragma mark AMSelectPickViewDelegate Methods
-(void)showTableView
{
    //版本2.1
    
    
//    [UIView setAnimationDuration:0.9];
    if (self.isIndustryViewShow) {
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_UNHIDETABBAR object:nil];
        self.isIndustryViewShow = NO;
        [UIView beginAnimations:@"HomeSelectUp" context:nil];
        self.industySelectHomeView.frame = CGRectMake(self.industySelectHomeView.frame.origin.x, self.industySelectHomeView.frame.origin.y, self.industySelectHomeView.frame.size.width,0);
        [UIView commitAnimations];
        
        self.industySelectHomeView.alpha = 0.0;
        [self.view sendSubviewToBack:self.industySelectHomeView];
        
        
    }
    else {
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_HIDETABBAR object:nil];
        self.isIndustryViewShow = YES;
        [UIView beginAnimations:@"HomeSelectDown" context:nil];
        self.industySelectHomeView.frame = CGRectMake(self.industySelectHomeView.frame.origin.x, self.industySelectHomeView.frame.origin.y, self.industySelectHomeView.frame.size.width,self.industySelectHomeViewHeight);
        [UIView commitAnimations];
       
        self.industySelectHomeView.alpha = 1.0;
        
        
        [self.view bringSubviewToFront:self.industySelectHomeView];
        

    }
    
    if (self.industrySelectPickView.isButtonUp) {
        [(MessageCenterButtonView *)self.navigationItem.rightBarButtonItem.customView setHidden:NO];
        self.industrySelectPickView.isButtonUp = false;
        self.industrySelectPickView.mSelectTypeButtonUp.hidden = YES;
        self.industrySelectPickView.mSelectTypeButtonDown.hidden = NO;
    }
    else {
        [(MessageCenterButtonView *)self.navigationItem.rightBarButtonItem.customView setHidden:YES];
        self.industrySelectPickView.isButtonUp = true;
        self.industrySelectPickView.mSelectTypeButtonUp.hidden = NO;
        self.industrySelectPickView.mSelectTypeButtonDown.hidden = YES;
    }
    
}
#pragma mark Table View Data Source Methods

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
{
    return 0;
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section;
{
    return 0;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
{
    return nil;
}
#pragma mark Table View Data Source Methods end

#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
{
    return;
}
#pragma mark AliChannel Delegate Methods
-(void)AliChannelReloadData
{
    return;
}
#pragma mark AliAdv Delegate Methods
-(UIViewController*)superController;
{
    return self;
}
-(NSString*)superControllerName
{
    return @"HomeBaseView";
}
-(void)dataReload
{
    return;
}
#pragma mark MenuView Delegate Methods
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView
{
    return 0;
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index
{
    return;
}

- (AMMenuItemView *)menuView:(AMMenuView *)menuView ItemViewForRowAtIndex:(NSInteger)index
{
    return nil;
}

@end

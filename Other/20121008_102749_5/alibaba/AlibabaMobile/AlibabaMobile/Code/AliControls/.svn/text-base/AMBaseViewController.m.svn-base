//
//  AMBaseViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//



//
//  AliBaseViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <RestKit/RestKit.h>

#import "ConstDef.h"
#import "UIHelp.h"
#import "AliToastView.h"
#import "AMBaseViewController.h"

@interface AMBaseViewController ()

@end


@implementation AMBaseViewController

@synthesize observer = _observer;

@synthesize mLoadingView = _mLoadingView;
@synthesize mBackButton = _mBackButton;
@synthesize mTitleLabel = _mTitleLabel;
@synthesize mRightNavigationItem = _mRightNavigationItem;

- (id)init
{
    self = [super init];
    if (self) {  
		self.observer = [[RKReachabilityObserver alloc] initWithHost:AMCONST_HOST];	
		
		// Register for notifications
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(reachabilityChanged:)
                                                     name:RKReachabilityDidChangeNotification
                                                   object:_observer];
    }
    return self;
}

- (void)reachabilityChanged:(NSNotification *)notification {
    RKReachabilityObserver* observer = (RKReachabilityObserver *) [notification object];
    
    RKLogCritical(@"AliBaseViewController - Received reachability update: %@", observer);
    
    if ([observer isNetworkReachable]) {
        if ([observer isConnectionRequired]) {
            return;
        }            
        
        if (RKReachabilityReachableViaWiFi == [observer networkStatus]) {
            // Online via WiFi
            NSLog(@"Online via WiFi...");
            //            [[AliToastView MakeToastWithType: TOAST_STYLE_COMMON info:NSLocalizedString(@"NetworkAvailableViaWifi", @"")] show];
            
        } else if (RKReachabilityReachableViaWWAN == [observer networkStatus]) {
            // Online via 3G or Edge
            NSLog(@"Online via 3G or Edge...");
        }
    } else {
        // Network unreachable!
        NSLog(@"Network unreachable!");
    }
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        
        
        [self.view addSubview:self.mLoadingView];
        [self.mLoadingView setHidden:NO];
    }
    return _mLoadingView;
}

- (void) showLoadingView
{
    if(self.view.frame.size.height == 480){
        self.mLoadingView.frame = CGRectMake(self.mLoadingView.frame.origin.x, self.mLoadingView.frame.origin.y + 44, self.mLoadingView.frame.size.width, self.mLoadingView.frame.size.height);
    }
    [self.mLoadingView setHidden:NO];
}

// 去除加载进度
-(void) endLoadingView
{
    [self.mLoadingView setHidden:YES];
}

- (void) customTitleBar
{
    //custome title back button
    if (self.mBackButton == nil) {
        self.mBackButton = [[AMNavigationBackButton alloc] initWithTitle:@"返 回"];
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
- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
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


#pragma mark - View lifecycle
- (void)viewDidUnload {
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    [super viewDidUnload];
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIHelp colorWithHexString:@"0xF5F5F5"];
    [self customTitleBar];
    
    
    // Do any additional setup after loading the view from its nib.
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_observer release];  
	
	self.mBackButton = nil;
    self.mTitleLabel = nil;
    self.mRightNavigationItem = nil;
    self.mLoadingView = nil;
//    _mLoadingView = nil;
    
    [super dealloc];
}

@end

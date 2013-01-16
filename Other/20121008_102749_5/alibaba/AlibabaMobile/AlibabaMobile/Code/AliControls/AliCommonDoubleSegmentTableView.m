//
//  AliCommonTableView.m
//  AlibabaMobile
//
//  Created by zzh on 12-8-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCommonDoubleSegmentTableView.h"
#import "UIHelp.h"
#import "ConstDef.h"
#import "AliToastView.h"

NSInteger gDoubleSegmentLastDisplayErrorTimeInterval = 00;

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AliCommonDoubleSegmentTableView()
@property (nonatomic,retain) AliNavigationBackButton *button;
@property (nonatomic,retain) AliNavigationButton *optionButton;
@property (retain,nonatomic)AliSegmentedControl *mSegmentedControl;
@property (nonatomic,retain)AliRightBarButtonItem*buttonsItem;
-(void) showLoadingView;
-(void) endLoadingView;
@end


@implementation AliCommonDoubleSegmentTableView

@synthesize observer = _observer;

@synthesize mLoadingView = _mLoadingView;
@synthesize isReload=_isReload;
@synthesize button=_button;
@synthesize optionButton=_optionButton;
@synthesize mSegmentedControl=_mSegmentedControl;
@synthesize buttonsItem=_buttonsItem;


-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_observer release];
    [_buttonsItem release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [_button release];
    [_optionButton release];
    [_mSegmentedControl release];
    
    [super dealloc];
}

-(AliRightBarButtonItem*)buttonsItem
{
    if (!_buttonsItem) {
        _buttonsItem = [AliRightBarButtonItem createView:[self commonTableViewRightButtonTitles]];
        _buttonsItem.delegate = self;
    }
    return _buttonsItem;
}
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
    
    RKLogCritical(@"AliCommonTableView - Received reachability update: %@", observer);
    
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
        
        // End loading view
        [self endLoadingView];
    }
}

-(AliNavigationBackButton*)button
{
    if (!_button) {
        NSString *title = [self commonTableViewBackButtonTitle];
        if (!title) {
            title = @"返回";
        }
        _button = [[AliNavigationBackButton alloc] initWithTitle:title];
        _button.navigationBackDelegate = self;

    }
    return _button;
}
-(AliNavigationButton*)optionButton
{
    if (!_optionButton) {
    
        _optionButton = [[AliNavigationButton alloc] initWithTitle:[self commonTableViewOptionButtonTitle] style:NAV_BTN_STYLE_COMMON];
        _optionButton.navigationButtonDelegate = self;       
    }
    return _optionButton;
}

-(AliSegmentedControl*)mSegmentedControl
{
  if (_mSegmentedControl==nil) {
        _mSegmentedControl = [[AliSegmentedControl alloc] initWithFrame:CGRectMake(0, [self segmentStartY], 320, 40)];
        _mSegmentedControl.delegate = self;
       NSArray *segment = [self commonTableViewSegmentTitle];
      for (NSString *title in segment) {
          [_mSegmentedControl addItem:title];
      }
    }
    return _mSegmentedControl;
}

- (void) navigationButtonClick
{
    [self commonTableViewOptionButtonClick];
}
- (void) commonTableViewOptionButtonClick
{
    return;
}
- (void)viewDidUnload {
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    [super viewDidUnload];
}

-(void)viewDidLoad
{
    if ([self showBackButton]) {
        self.navigationItem.leftBarButtonItem = self.button;
    }
    
    self.view.backgroundColor =RGB(0xf0,0xf0,0xf0);
    
    
    UIView *titleView = [self commonTableViewNavigationTitleView];
    if (titleView) {
        self.navigationItem.titleView = titleView;
    }
    else {
        self.navigationItem.title=[self commonTableViewNavigationTitle];
    }
    
//    NSString *navigationTitle = [self commonTableViewNavigationTitle];
//    if(navigationTitle!=nil||navigationTitle.length==0){
//        [self.navigationItem.titleView contentSizeForViewInPopover];
//    }
    
    NSString *option = [self commonTableViewOptionButtonTitle];
    if (option) {
        self.navigationItem.rightBarButtonItem = self.optionButton;
    }
    else {
        NSArray *rightTitles = [self commonTableViewRightButtonTitles];
        if (rightTitles) {
            self.navigationItem.rightBarButtonItem = self.buttonsItem;
        }
    }

    NSArray *segment = [self commonTableViewSegmentTitle];
    if (segment&&[segment count]>0) {
        [self.view addSubview:self.mSegmentedControl];
     }
    [super viewDidLoad];
}
-(void)viewWillAppear:(BOOL)animated
{
    if (self.isReload) 
    {
        NSString *title = [self commonTableViewBackButtonTitle];
        if (!title) {
            title = @"返回";
        }

        [self.button setTitle:title];
        
        UIView *titleView = [self commonTableViewNavigationTitleView];
        if (!titleView) {
            self.navigationItem.titleView = titleView;
        }
        else {
            self.navigationItem.title=[self commonTableViewNavigationTitle];
        }

    }
    [super viewWillAppear:animated];
}
-(void)viewWillDisappear:(BOOL)animated {
    [self endLoadingView];;
    
    [super viewWillDisappear:animated];
}
-(int)loadingStartY
{
    NSArray *segment = [self commonTableViewSegmentTitle];
    if (segment&&[segment count]>0) {
        return 40+[self segmentStartY];
    }
    return 0;
}
-(CGFloat)segmentStartY
{
    return 0;
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,[self loadingStartY]+40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    return _mLoadingView;
}


- (void) showLoadingView
{
    [self.mLoadingView setHidden:NO];
    [self.mLoadingView.loadingView setHidden:NO];
    [self.mLoadingView.noDataView setHidden:YES];
   
}
//去除加载进度
-(void) endLoadingView
{
   [self.mLoadingView setHidden:YES];
}

-(NSString*)commonTableViewBackButtonTitle
{
    return nil;
}
-(NSString*)commonTableViewNavigationTitle
{
    return nil;
}
-(NSString*)commonTableViewOptionButtonTitle
{
    return nil;
}
-(UIView*)commonTableViewNavigationTitleView
{
    return nil;
}
-(NSArray*)commonTableViewSegmentTitle
{
    return nil;
}
-(NSArray*)commonTableViewRightButtonTitles
{
    return nil;
}
-(BOOL)showBackButton
{
    return YES;
}


- (void) segmentValueChanged:(int)nowIndex
{
    return;
}
- (void) changeSegmentIndex:(int)nowIndex
{
    [self.mSegmentedControl setSelectedIndex:nowIndex];
}


- (void) showNodataMessage
{

    [self.mLoadingView setHidden:NO];
    [self.mLoadingView.loadingView setHidden:YES];
    [self.mLoadingView.noDataView setHidden:NO];
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
   NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);   
}
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"didFailLoadWithError: %@", error);   
    

//    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
//    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gDoubleSegmentLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
//        
//        gDoubleSegmentLastDisplayErrorTimeInterval = currentTime;
//    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gDoubleSegmentLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
//        
//        gDoubleSegmentLastDisplayErrorTimeInterval = currentTime;
//    }

}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects;
{
    [self endLoadingView];
   
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    [self endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }
}

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    [self endLoadingView];
    [self navigationBack];
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)loadObjectsFromRemote
{
   [self showLoadingView];
}
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
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
{
    return;
}
-(void)AliRightBarButtonItem:(NSInteger)selectedButton
{
    return;
}

@end

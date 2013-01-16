//
//  AMTableViewController.m
//  AlibabaMobile
//
//  Created by  on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMTableViewController.h"
#import "AMLoadingDataView.h"
#import "UIHelp.h"
#import "ConstDef.h"
#import "AMToastView.h"

static NSInteger sLastDisplayErrorTimeInterval = 0;

@implementation AMTableViewController

-(id)init
{
    self = [super init];
    if (self) {  
		_observer = [[RKReachabilityObserver alloc] initWithHost:AMCONST_HOST];	
		
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
    
    RKLogCritical(@"AMAddFavTableViewController - Received reachability update: %@", observer);
    
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
        if(_loadingView){
            [_loadingView endLoadingView];
        }
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);   
}
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"didFailLoadWithError: %@", error);   
    
    [_loadingView endLoadingView];
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - sLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        sLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - sLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        
        sLastDisplayErrorTimeInterval = currentTime;
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSArray *)objects
{
    [_loadingView endLoadingView];
    
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	
}


-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    AM_RELEASE_SAFELY(_observer);
    AM_RELEASE_SAFELY(_loadingView);
    AM_RELEASE_SAFELY(_segmentedControl);
    [super dealloc];
}
@end

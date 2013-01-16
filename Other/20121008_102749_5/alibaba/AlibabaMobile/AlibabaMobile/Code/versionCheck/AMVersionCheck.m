//
//  AMVersionCheck.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMVersionCheck.h"
#import "AMVersionCheckRequest.h"
#import "ConstDef.h"
#import "AMAppVersion.h"
#import "UIHelp.h"

@interface AMVersionCheck ()

@property (retain,nonatomic)AMVersionCheckRequest *request;
@property (nonatomic, retain) NSString *myPlatform;
@property (nonatomic, retain) NSString *myVersion;
@property (nonatomic, retain) NSString *myDeviceId;
@property (nonatomic,retain)AMAppVersion * result;
@end

@implementation AMVersionCheck
@synthesize myVersion=_myVersion;
@synthesize myPlatform=_myPlatform;
@synthesize myDeviceId=_myDeviceId;
@synthesize request=_request;
@synthesize result=_result;
-(NSString*)myPlatform
{
    return @"IOS4.3+ for iPhone";
}
-(NSString*)myVersion
{
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
}
-(NSString*)myDeviceId
{
    return  [[UIDevice currentDevice] uniqueIdentifier];
}
-(AMVersionCheckRequest*)request
{
    if (!_request) {
        _request = [[AMVersionCheckRequest alloc]init];
    }
    _request.myDeviceId = self.myDeviceId;
    _request.myPlatform = self.myPlatform;
    _request.myVersion = self.myVersion;
//    _request.myVersion = @"1.1.0";//如需测试更新功能，打开
    return _request;
}
-(void)dealloc
{
    [_request release];
    [_myVersion release];
    [_myPlatform release];
    [_myDeviceId release];
    [_result release];
    [super dealloc];
}

- (void)loadObjectsFromRemote {
     // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* offerResultMapping = [AMAppVersion sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: offerResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_UPDATE_REQUEST_URL usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMAppVersion class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
  
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        
        gLastDisplayErrorTimeInterval = currentTime;
    }
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);  
    self.result = [objects objectAtIndex:0];
    if ([self.result.isVersionAvailable boolValue]) {
        
        NSString *msg = [[NSString alloc]initWithFormat:@"有新版本发布，是否现在就更新？"];
        UIAlertView *alert = [[UIAlertView alloc] 
                              initWithTitle:@"" 
                              message:msg 
                              delegate:self    
                              cancelButtonTitle:@"取消"                          otherButtonTitles:@"好" ,
                              nil]; 
        [alert show]; 
        
        [msg release];
        [alert release];

    }else{
        //if no update
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_NO_UPDATE_CHECK object:self];
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {  
        NSLog(@"取消");
    }
    else {    
        NSLog(@"更新");
        
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:self.result.downloadUrl]]; 
         }
}

@end

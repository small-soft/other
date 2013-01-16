//
//  AMDeviceRegistRequest.m
//  AlibabaMobile
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMDeviceRegistRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMDeviceRegistRequest


@synthesize transactionType = _transactionType;
@synthesize requestURL = _requestURL;

@synthesize terminateId = _terminateId;
@synthesize  model = _model;
@synthesize  system = _system;
@synthesize  version = _version;
@synthesize  deviceTokenStr = _deviceTokenStr;
@synthesize  appId = _appId;
@synthesize  appVersion = _appVersion;
@synthesize currentUserId = _currentUserId;
@synthesize downloadChannel = _downloadChannel;

- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}


- (NSData*)HTTPBody {
    
    NSString * tokenRequestStr = [NSString stringWithFormat:@"{terminalInfo:{terminalId:\"%@\",phoneModel:\"%@\",osPlatform:\"%@\",osVersion:\"%@\",iosDeviceToken:\"%@\"},appInfo:{appId:\"%@\",appVersion:\"%@\",currentUserId:\"%@\",downloadChannel:\"%@\"}}", self.terminateId, self.model, self.system, self.version, self.deviceTokenStr, self.appId, self.appVersion, self.currentUserId,self.downloadChannel];
    
    NSString *_data_ = tokenRequestStr;
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_DEVICE_REGIST params:params];
    
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}


-(void) dealloc
{
    [self.requestURL release];
    [self.terminateId release];
    [self.model release];
    [self.system release];
    [self.version release];
    [self.deviceTokenStr release];
    [self.appId release];
    [self.appVersion release];
    [self.requestURL release];
    [self.currentUserId release];
    [self.downloadChannel release];
    
    [super dealloc];
}

@end

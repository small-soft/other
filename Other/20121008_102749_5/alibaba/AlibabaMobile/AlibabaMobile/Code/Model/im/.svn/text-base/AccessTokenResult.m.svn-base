//
//  AccessTokenResult.m
//  AlibabaMobile
//
//  Created by lih on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AccessTokenResult.h"

@implementation AccessTokenResult

@synthesize mAccessToken = _mAccessToken;
@synthesize mAccessTokenTimeout = _mAccessTokenTimeout;
@synthesize mResourceOwnerId = _mResourceOwnerId;
@synthesize mUid = _mUid;


- (NSString*)description {
    return @"AccessTokenResult";
}

- (void)dealloc { 
    [_mAccessToken release];  
    [_mAccessTokenTimeout release]; 
    [_mResourceOwnerId release]; 
    [_mUid release]; 
    
    [super dealloc];
}

@end

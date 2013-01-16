//
//  LoginResult.m
//  AlibabaMobile
//
//  Created by mardin partytime on 1/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "LoginResult.h"


@implementation LoginResult

@synthesize mResourceOwnerId = _mResourceOwnerId;
@synthesize mUid = _mUid;
@synthesize mAccessToken = _mAccessToken;
@synthesize mAccessTokenTimeout = _mAccessTokenTimeout;
@synthesize mRefreshToken = _mRefreshToken;
@synthesize mRefreshTokenTimeout = _mRefreshTokenTimeout;

- (NSString*)description {
    //return [NSString stringWithFormat:@"(ID: %@)", self.];
    return @"LoginResult";
}

- (void)dealloc {
    [_mAccessToken release];   
    [_mAccessTokenTimeout release];
    [_mRefreshToken release];
    [_mRefreshTokenTimeout release];
    [_mResourceOwnerId release];
    [_mUid release];
    
    [super dealloc];
}

@end


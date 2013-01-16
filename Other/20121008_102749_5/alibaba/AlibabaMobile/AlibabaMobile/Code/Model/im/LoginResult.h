//
//  LoginResult.h
//  AlibabaMobile
//
//  Created by mardin partytime on 1/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LoginResult : NSObject {
    
    NSString * _mAccessToken;
    NSString * _mAccessTokenTimeout;
    NSString * _mRefreshToken;
    NSString * _mRefreshTokenTimeout;  
    NSString * _mResourceOwnerId;
    NSString * _mUid;
}


@property(nonatomic, retain) NSString * mAccessToken;
@property(nonatomic, retain) NSString * mAccessTokenTimeout;
@property(nonatomic, retain) NSString * mRefreshToken;
@property(nonatomic, retain) NSString * mRefreshTokenTimeout;
@property (nonatomic, retain) NSString * mResourceOwnerId;
@property (nonatomic, retain) NSString * mUid;

@end
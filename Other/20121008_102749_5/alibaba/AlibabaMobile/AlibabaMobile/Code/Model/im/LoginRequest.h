//  LoginRequest.h
//  AlibabaMobile
//
//  Created by mardin partytime on 1/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_LOGIN ([@"/authn/" stringByAppendingString:AMCONST_APP_KEY])

extern NSString * const LOGIN_ID;
extern NSString * const EMAIL;
extern NSString * const MOBILE;

@interface LoginRequest : NSObject<RKRequestSerializable> {
    NSString * _account;
    NSString * _password;
    NSString * _needRefreshToken;  
    NSString * _loginIdType;
}

@property(nonatomic, retain) NSString * account;
@property(nonatomic, retain) NSString * password;
@property(nonatomic, retain) NSString * needRefreshToken;
@property(nonatomic, retain) NSString * loginIdType;


@end
//
//  LoginToken.h
//  AlibabaMobile
//
//  Created by mardin partytime on 1/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import "AccessTokenRequest.h"
#import "AccessTokenResult.h"


@interface LoginToken : NSObject
+ (void) setWangWangLogined:(BOOL)logined;

+ (BOOL) isWangWangLogined;

+ (BOOL) isAppLogined;

+ (BOOL) isChildAccountLogined;

+ (void) checkLoginParameter;

+ (void) checkAccessTokenExpired;

+(void)setLoginParameter:(BOOL) rememberPWD:(NSString *)userName :(NSString *)accessToken :(NSString *)accessTokenTimeout :(NSString *)refreshToken:(NSString *)refreshTokenTimeout;

+(void)updateAccessToken:(NSString *)accessToken :(NSString *)accessTokenTimeout;

//+(void)setLoginUserName:(NSString *)userName;
+(NSString *)getLoginUserName;

//+(void)setAccessToken:(NSString *)accessToken;
+(NSString *)getAccessToken;

//+(void)setAccessTokenTimeout:(NSString *)accessTokenTimeout;
+(NSString *)getAccessTokenTimeout;


//+(void)setRefreshToken:(NSString *)refreshToken;
+(NSString *)getRefreshToken;

//+(void)setRefreshTokenTimeout:(NSString *)refreshTokenTimeout;
+(NSString *)getRefreshTokenTimeout;

@end

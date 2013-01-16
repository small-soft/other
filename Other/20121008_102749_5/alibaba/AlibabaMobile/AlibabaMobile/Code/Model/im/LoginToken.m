//
//  LoginToken.m
//  AlibabaMobile
//
//  Created by mardin partytime on 1/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LoginToken.h"
#import "AMAppDelegate.h"
#import "ConstDef.h"
#import "LoginTokenHelper.h"

#define HOUR_TIME_BASE_DAY  @"2012-01-01 01:01:01"

@implementation LoginToken

+ (void) setWangWangLogined:(BOOL)logined
{
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    @synchronized(appDelegate){
        appDelegate.isWwLogined = logined;
    }
}

+ (BOOL) isWangWangLogined
{
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    @synchronized(appDelegate){
        NSString *loginUserName = nil;
        loginUserName = [LoginToken getLoginUserName];
        if(loginUserName && [loginUserName length] > 3 && appDelegate.isWwLogined){
            return YES;            
        }
        else {
            return NO;
        }
    }
}

+ (BOOL) isAppLogined
{
    NSString *loginUserName=[LoginToken getLoginUserName];
    if (loginUserName && loginUserName.length > 0) {
        return YES;
    } else {
        return NO;
    }
}

+ (BOOL) isChildAccountLogined
{
    NSString *loginUserName=[LoginToken getLoginUserName];
    if (loginUserName && loginUserName.length > 0) 
    {
        NSRange range = [loginUserName rangeOfString:@":"]; 
        if(range.location != NSNotFound)
        {
                return YES;            
        }
    }
    
    return NO;
}

+(void)updateAccessToken:(NSString *)accessToken :(NSString *)accessTokenTimeout{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    [defaults setValue:accessToken forKey:@"im_login_AccessToken"];
    [defaults setValue:accessTokenTimeout forKey:@"im_login_AccessTokenTimeout"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    appDelegate.gAccessToken = accessToken;
    appDelegate.gAccessTokenTimeout = accessTokenTimeout;
}


+ (NSUInteger) getHourSinceBaseDay {
    NSDateFormatter *dateFormat=[[NSDateFormatter alloc] init];
    [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSDate *baseDay=[dateFormat dateFromString:HOUR_TIME_BASE_DAY];  ///base time 
    
    NSTimeInterval baseTimeInSencond=[baseDay timeIntervalSince1970]*1;
    
    NSDate* today = [NSDate dateWithTimeIntervalSinceNow:0];
    NSTimeInterval now=[today timeIntervalSince1970]*1;
    
    NSTimeInterval diff=now-baseTimeInSencond;
    
    NSUInteger theUIntHour =(NSUInteger)diff/3600;
    [dateFormat release];
    return theUIntHour;
}

+ (void) checkLoginParameter {
    [[LoginTokenHelper sharedTokenHelper] updateAccessToken];
}

+ (void) checkAccessTokenExpired {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSUInteger savedHour =[[defaults objectForKey:@"im_login_AccessToken_time"] intValue];
    NSUInteger currentHour =[self getHourSinceBaseDay]; 
    if(currentHour - savedHour > 7){
//        LoginTokenHelper *tokenHelper = (LoginTokenHelper *)[[LoginTokenHelper alloc] init];
//        [tokenHelper updateAccessToken];
        NSUInteger theUIntHour =[self getHourSinceBaseDay];  
        NSString* theHourConvert = [NSString stringWithFormat:@"%d", theUIntHour];
        [defaults setValue:theHourConvert  forKey:@"im_login_AccessToken_time"];
        [[LoginTokenHelper sharedTokenHelper] updateAccessToken];
    }
    
}

+(void)setLoginParameter:(BOOL)  rememberPWD:(NSString *)userName :(NSString *)accessToken :(NSString *)accessTokenTimeout :(NSString *)refreshToken:(NSString *)refreshTokenTimeout{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    if (rememberPWD) {
        
        [defaults setValue:userName forKey:@"im_login_UserName"];
        [defaults setValue:accessToken forKey:@"im_login_AccessToken"];      
        
        NSUInteger theUIntHour =[self getHourSinceBaseDay];  
        NSString* theHour = [NSString stringWithFormat:@"%d", theUIntHour];
        [defaults setValue:theHour  forKey:@"im_login_AccessToken_time"];
        
        [defaults setValue:accessTokenTimeout forKey:@"im_login_AccessTokenTimeout"];
        [defaults setValue:refreshToken forKey:@"im_login_RefreshToken"];
        [defaults setValue:refreshTokenTimeout forKey:@"im_login_RefreshTokenTimeout"];
        
    }else{
        [defaults setValue:@"" forKey:@"im_login_UserName"];
        [defaults setValue:@"" forKey:@"im_login_AccessToken"];
        [defaults setValue:@"" forKey:@"im_login_AccessToken_time"];
        [defaults setValue:@"" forKey:@"im_login_AccessTokenTimeout"];
        [defaults setValue:@"" forKey:@"im_login_RefreshToken"];
        [defaults setValue:@"" forKey:@"im_login_RefreshTokenTimeout"];
    }
    [[NSUserDefaults standardUserDefaults] synchronize];    
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    appDelegate.gLoginUserName = userName;
    appDelegate.gAccessToken = accessToken;
    appDelegate.gAccessTokenTimeout = accessTokenTimeout;
    appDelegate.gRefreshToken = refreshToken;
    appDelegate.gRefreshTokenTimeout = refreshTokenTimeout;
}


+(NSString *)getLoginUserName{
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.gLoginUserName == nil) {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        appDelegate.gLoginUserName= [defaults objectForKey:@"im_login_UserName"];
    }
    return appDelegate.gLoginUserName;    
    
}

+(NSString *)getAccessToken{
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.gAccessToken == nil) {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        appDelegate.gAccessToken= [defaults objectForKey:@"im_login_AccessToken"];
    }
    return appDelegate.gAccessToken;     
}

+(NSString *)getAccessTokenTimeout{
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.gAccessTokenTimeout == nil) {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        appDelegate.gAccessTokenTimeout= [defaults objectForKey:@"im_login_AccessTokenTimeout"];
    }
    return appDelegate.gAccessTokenTimeout; 
}


+(NSString *)getRefreshToken {
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.gRefreshToken == nil) {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        appDelegate.gRefreshToken= [defaults objectForKey:@"im_login_RefreshToken"];
    }
    return appDelegate.gRefreshToken; 
}


+(NSString *)getRefreshTokenTimeout {
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.gRefreshTokenTimeout == nil) {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        appDelegate.gRefreshTokenTimeout= [defaults objectForKey:@"im_login_RefreshTokenTimeout"];
    }
    return appDelegate.gRefreshTokenTimeout; 
}


/*
 +(void)setLoginUserName:(NSString *)userName{
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 appDelegate.gLoginUserName = userName;
 }
 
 +(void)setAccessToken:(NSString *)accessToken{
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 appDelegate.gAccessToken = accessToken;
 }
 
 +(void)setAccessTokenTimeout:(NSString *)accessTokenTimeout{
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 appDelegate.gAccessTokenTimeout = accessTokenTimeout;
 }
 
 +(void)setRefreshToken:(NSString *)refreshToken{
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 appDelegate.gRefreshToken = refreshToken;
 }
 
 +(void)setRefreshTokenTimeout:(NSString *)refreshTokenTimeout {
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 appDelegate.gRefreshTokenTimeout = refreshTokenTimeout;
 }
 
 +(NSString *)getLoginUserName{
 
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 return appDelegate.gLoginUserName;
 
 }
 
 +(NSString *)getAccessToken{
 
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 return appDelegate.gAccessToken;
 
 }
 
 +(NSString *)getAccessTokenTimeout{
 
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 return appDelegate.gAccessTokenTimeout;
 }
 
 +(NSString *)getRefreshToken {
 
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 return appDelegate.gRefreshToken;
 
 }
 
 +(NSString *)getRefreshTokenTimeout {
 
 AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
 return appDelegate.gRefreshTokenTimeout;
 
 } 
 */

@end

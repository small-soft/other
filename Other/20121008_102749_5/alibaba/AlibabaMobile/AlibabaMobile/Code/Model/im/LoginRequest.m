//
//  LoginRequest.m
//  AlibabaMobile
//
//  Created by mardin partytime on 1/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "LoginRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

NSString * const LOGIN_ID = @"LOGIN_ID";
NSString * const EMAIL = @"EMAIL";
NSString * const MOBILE = @"MOBILE";

@implementation LoginRequest  

@synthesize account = _account;
@synthesize password = _password;
@synthesize needRefreshToken = _needRefreshToken;
@synthesize loginIdType = _loginIdType;

/**
 * The value of the Content-Type header for the HTTP Body representation of the serialization
 */
- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {

    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
   
    
    if(_loginIdType == nil || [_loginIdType isEqualToString:@""]) {
        _loginIdType = LOGIN_ID;
    }
    
    [params setObject: [self loginIdType] forKey: @"loginIdType"];   
    [params setObject: [self account] forKey: @"account"];
    [params setObject: [self password] forKey: @"password"];
    [params setObject: [self needRefreshToken] forKey: @"needRefreshToken"];
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX_OAUTH resourcePath:OCEAN_API_URL_LOGIN params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_account release];
    [_password release];
    [_loginIdType release];
    [_needRefreshToken release];
    
    [super dealloc];
}

@end

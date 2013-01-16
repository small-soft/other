//
//  AccessTokenRequest.m
//  AlibabaMobile
//
//  Created by lih on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <RestKit/RestKit.h>
#import "AccessTokenRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AccessTokenRequest

@synthesize refreshToken = _refreshToken;

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
//    [params setObject: [self refreshToken] forKey: @"refreshToken"];
    [params setObject: self.refreshToken forKey: @"refreshToken"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX_OAUTH resourcePath:OCEAN_API_URL_GET_ACCESSTOKEN params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_refreshToken release];
    [super dealloc];
}

@end

//
//  AMHotAreaRequest.m
//  AlibabaMobile
//
//  Created by zzh on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotAreaRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMHotAreaRequest

// Impliment RKRequestSerializable delegate methods here

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
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_HOT_AREA params:nil];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}


@end

//
//  AMCategoryRequest.m
//  AlibabaMobile
//
//  Created by  on 11-12-27.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMCategoryRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"


@implementation AMCategoryRequest

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
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CATEGORIES params:nil];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

@end

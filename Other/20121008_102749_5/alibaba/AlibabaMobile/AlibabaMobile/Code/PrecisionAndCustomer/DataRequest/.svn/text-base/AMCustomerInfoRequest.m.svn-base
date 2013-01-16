//
//  AMCustomerInfoRequest.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerInfoRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMCustomerInfoRequest
@synthesize request = _request;

@synthesize pageInfo = _pageInfo;
@synthesize pageSize = _pageSize;
@synthesize pageIndex = _pageIndex;
@synthesize buyerId = _buyerId;

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
    
    NSString *signedBodyString = nil;
    
    NSString *_data_ = [NSString stringWithFormat: @"{customerBuyerId:\"%@\"}", self.buyerId];

    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CUSTOMER_USERINFO params:params];
    NSLog(@"REQUEST:%@",signedBodyString );
    [params release];	
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];

}

- (void) dealloc {
    
    [_pageInfo release];
    [_pageSize release];
    [_request release];
    
    [super dealloc];
}

@end

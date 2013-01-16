//
//  AMOrderDetailRequest.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderDetailRequest.h"
#import "SecurityUtil.h"


@implementation AMOrderDetailRequest

@synthesize orderid = _orderid;

-(void)dealloc
{
    [self.orderid release];
    self.orderid = nil;
    
    [super dealloc];
}

- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {
    
    

    NSString *signedBodyString = nil;
    
    NSString *_data_ = [NSString stringWithFormat: @"{orderid:\"%@\"}", self.orderid];
    
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_ORDER_DETAIL params:params];
    NSLog(@"REQUEST:%@",signedBodyString );
    [params release];	
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];

}


@end

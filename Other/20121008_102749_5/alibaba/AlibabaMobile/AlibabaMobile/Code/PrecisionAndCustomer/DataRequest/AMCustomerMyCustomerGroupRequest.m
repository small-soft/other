//
//  AMGuestRequest.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "AMCustomerMyCustomerGroupRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMCustomerMyCustomerGroupRequest
//@synthesize request = _request;
//
//@synthesize pageInfo = _pageInfo;
//@synthesize pageSize = _pageSize;
//@synthesize pageIndex = _pageIndex;

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
    
    
//    NSMutableDictionary *wrappedParams1 = [[[NSMutableDictionary alloc] init] autorelease];
//    self.pageSize = [NSNumber numberWithInt:10]; 
    
    
    
//    [wrappedParams1 setObject:self.pageSize forKey:@"pageSize"];
//    [wrappedParams1 setObject:self.pageIndex forKey:@"pageIndex"];
    
//    NSMutableDictionary *wrappedParams2 = [[[NSMutableDictionary alloc] init] autorelease];
//    
//    [wrappedParams2 setObject:wrappedParams1 forKey:@"pageInfo"];
//    
//    self.request = wrappedParams2;
    
    NSString *signedBodyString = nil;
    
    NSString *_data_ = [NSString stringWithFormat: @"{}"];
    
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
//    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CUSTOMER_USERINFO params:params];
//    NSLog(@"REQUEST:%@",signedBodyString );
    
    
    
    
//    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCustomerMyCustomerGroupRequest class]];
//    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
//    
//    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
//    NSError *error = nil;
//    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
//    
//    // Create NSDictionary object and setObject to it
//    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
//    [params setObject: _data_ forKey: @"_data_"];
//    
//    NSString *paramsString = [NSString stringWithString:@""];
//    
//    
//    if (params != nil && [params count] > 0) {
//        for (NSString *key in [params allKeys]) {
//            NSString *value = [params objectForKey: key];
//            paramsString = [paramsString stringByAppendingFormat:[paramsString length] == 0 ? @"%@=%@" : @"&%@=%@", key, value];
//        }
//    }

        
    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CUSTOMER_MYCUSTOMER_GROUP_LIST params:params];
    [params release];
//    
//    NSString *signedBodyString = [paramsString stringByAppendingFormat: @"&access_token=d2885bce-abb4-44c0-95f5-032f059f8d36"];

    NSLog(@"REQUEST=https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getDDGroupAndArea/5005?%@",signedBodyString );
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
//    return [paramsString dataUsingEncoding: NSUTF8StringEncoding];

}

- (void) dealloc {
    
    [super dealloc];
}

@end

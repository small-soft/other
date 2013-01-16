//
//  AMMyLogisticsOrderRequest.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMyLogisticsOrderRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>
#import "LoginToken.h"
@interface AMMyLogisticsOrderRequest()

@property (nonatomic, retain) NSDictionary * pageInfo;
@end



@implementation AMMyLogisticsOrderRequest

@synthesize pageIndex=_pageIndex;
@synthesize pageSize = _pageSize;
@synthesize pageInfo=_pageInfo;


- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */

- (NSData*)HTTPBody {
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
    
    if (self.pageIndex) {
        [wrappedParams setObject:self.pageIndex forKey:@"pageIndex"];
    }
    if (self.pageSize) {
        [wrappedParams setObject:self.pageSize forKey:@"pageSize"];
    }
    
    self.pageInfo = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMMyLogisticsOrderRequest class]];
    [requestMapping mapKeyPath:@"pageInfo" toAttribute:@"pageInfo"];  
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_TRADE_SALE_REQUEST_URL params:params];
    [params release];    
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

-(void)dealloc
{
    [_pageIndex release];
    [_pageSize release];
    [_pageInfo release];

    [super dealloc];
}

@end

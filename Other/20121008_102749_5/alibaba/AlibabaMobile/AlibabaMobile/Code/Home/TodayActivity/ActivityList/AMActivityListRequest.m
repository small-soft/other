//
//  AMGuestRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/activity.topic.findTopicGroup/5005?_data_={request:{configName:%22offer-list%22,summary:%22%22}}

#import "AMActivityListRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMActivityListRequest
@synthesize request = _request;
@synthesize industryId = _industryId;

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
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
    
    if (self.industryId) {
        [wrappedParams setObject:[NSString stringWithFormat:@"app_%@_jinrihuodongios",self.industryId] forKey:@"configName"];
    }
    
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMActivityListRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    
    // 不使用签名，否则在测试环境会报错
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_ACTIVITY params:params isUseSignature:NO];
    [params release];

    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    
    [self.industryId release];
    self.industryId = nil;
    [_request release];
    _request = nil;
    
    [super dealloc];
}

@end

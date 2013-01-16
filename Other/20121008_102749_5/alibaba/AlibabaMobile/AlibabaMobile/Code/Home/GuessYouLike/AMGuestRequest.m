//
//  AMGuestRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/recommend.getOffers/5005?targetId=60&_data_={"request":{"count":10,"positionId":"android_homepage_offer","termId":"d01f62eb7d83d52ff54e48fcf72c41c1"}}&clickId=13&clickUUID=bb086ed1-6777-44c5-98c7-dd9ed8724577&deviceId=d01f62eb7d83d52ff54e48fcf72c41c1&pageId=1

#import "AMGuestRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMGuestRequest
@synthesize request = _request;
@synthesize count = _count;
@synthesize ios_homepage_offer = _ios_homepage_offer;
@synthesize termId = _termId;

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
    self.count = [NSNumber numberWithInt:10];
    self.ios_homepage_offer = @"ios_homepage_offer";
    self.termId = [[UIDevice currentDevice] uniqueIdentifier];
    if (self.count) {
        [wrappedParams setObject:self.count forKey:@"count"];
    }
    if (self.ios_homepage_offer) {
        [wrappedParams setObject:self.ios_homepage_offer forKey:@"positionId"];
    }
    if (self.termId) {
        [wrappedParams setObject:self.termId forKey:@"termId"];
    }
    
    
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMGuestRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_GUEST params:params];
    [params release];
    
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    
    [_count release];
    [_ios_homepage_offer release];
    [_termId release];
    [_request release];
    
    [super dealloc];
}

@end

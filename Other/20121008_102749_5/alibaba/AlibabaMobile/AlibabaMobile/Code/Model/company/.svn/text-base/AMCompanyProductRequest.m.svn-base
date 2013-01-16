//
//  AMCompanyProductRequest.m
//  AlibabaMobile
//
//  Created by mardin partytime on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMCompanyProductRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMCompanyProductRequest
@synthesize request = _request;
@synthesize memberId = _memberId;
@synthesize pageSize = _pageSize;
@synthesize beginPage = _beginPage;

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
    
    if (self.memberId) {
        [wrappedParams setObject:self.memberId forKey:@"memberId"];
    }
    if (self.pageSize) {
        [wrappedParams setObject:self.pageSize forKey:@"pageSize"];
    }
    if (self.beginPage) {
        [wrappedParams setObject:self.beginPage forKey:@"beginPage"];
    }
    
 
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCompanyProductRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_COMPANY_PRODUCTLIST params:params];
    [params release];
    
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {

    [_memberId release];
    [_pageSize release];
    [_beginPage release];
    [_request release];
    
    [super dealloc];
}

@end




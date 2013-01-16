//
//  AMCustomerSuggestAddRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerSuggestAddRequest.h"
#import "AMCUDFavoriteRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMCustomerSuggestAddRequest

@synthesize customerMemberId = _customerMemberId;
@synthesize leadsId = _leadsId;

@synthesize transactionType = _transactionType;
@synthesize request = _request;

@synthesize requestURL = _requestURL;

- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_CUSTOMER_SUGGEST_ADD;
    }
    return self;
}

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
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCustomerSuggestAddRequest class]];
    
	[requestMapping mapKeyPath:@"customerMemberId" toAttribute:@"customerMemberId"];
	[requestMapping mapKeyPath:@"leadsId" toAttribute:@"leadsId"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    self.request = nil;
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    [params release];
    
    NSLog(@"%@", signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_customerMemberId release];
    [_leadsId release];
    
    [_request release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end

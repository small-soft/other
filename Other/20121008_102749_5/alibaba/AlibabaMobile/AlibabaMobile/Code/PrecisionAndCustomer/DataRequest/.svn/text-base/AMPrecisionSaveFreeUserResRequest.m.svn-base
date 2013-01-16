//
//  AMPrecisionSaveFreeUserResRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionSaveFreeUserResRequest.h"
#import "AMCUDFavoriteRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMPrecisionSaveFreeUserResRequest

@synthesize siteId = _siteId;
@synthesize visitorId = _visitorId;

@synthesize transactionType = _transactionType;
@synthesize request = _request;

@synthesize requestURL = _requestURL;

- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_PRECISION_SAVE_FREE_USER_RES;
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
    
    NSMutableDictionary *wrappedParams = nil;
    
    if ((self.transactionType == (int)AMTRANSACTION_TYPE_PRECISION_SAVE_FREE_USER_RES)){
        wrappedParams = [[NSMutableDictionary alloc] init];
        [wrappedParams setObject: self.siteId forKey: @"siteId"];
        [wrappedParams setObject: self.visitorId forKey: @"visitorId"];
        
        self.request = wrappedParams;
        [wrappedParams release];
    }
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMPrecisionSaveFreeUserResRequest class]];

	[requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    self.request = nil;
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_visitorId release];
    [_siteId release];
    
    [_request release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end
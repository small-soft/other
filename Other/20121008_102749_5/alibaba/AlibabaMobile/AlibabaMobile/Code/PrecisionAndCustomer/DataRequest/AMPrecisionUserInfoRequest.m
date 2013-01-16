//
//  AMPrecisionUserInfoRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionUserInfoRequest.h"
#import "AMCUDFavoriteRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>
#import "LoginToken.h"

@implementation AMPrecisionUserInfoRequest

@synthesize memberId = _memberId;
@synthesize transactionType = _transactionType;

@synthesize requestURL;

- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_PRECISION_GET_USERINFO;
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

    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMPrecisionUserInfoRequest class]];

	[requestMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_memberId release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end

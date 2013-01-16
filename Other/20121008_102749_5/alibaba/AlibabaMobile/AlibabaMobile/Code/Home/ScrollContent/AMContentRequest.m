//
//  AMContentRequest.m
//  AlibabaMobile
//
//  Created by zzh on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMContentRequest.h"
#import "SecurityUtil.h"
#import "AMLogUtils.h"
#import "ConstDef.h"
#import <RestKit/RestKit.h>

@implementation AMContentRequest

@synthesize name = _name;
@synthesize aop_responseFormat = _aop_responseFormat;

- (id) init {
    if (self = [super init]) {
     //   _name = @"picture-news-config";
     //   _name = @"home_banner_new";
        
        _aop_responseFormat = @"json";
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
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMContentRequest class]];
    [requestMapping mapKeyPath:@"name" toAttribute:@"name"];
    [requestMapping mapKeyPath:@"aop_responseFormat" toAttribute:@"_aop_responseFormat"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];

    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CONTENTS params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

@end

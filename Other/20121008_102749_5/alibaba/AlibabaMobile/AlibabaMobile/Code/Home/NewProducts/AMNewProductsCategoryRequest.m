//
//  AMNewProductsCategoryRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-5-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsCategoryRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import "AMLogUtils.h"
#import <RestKit/RestKit.h>

@implementation AMNewProductsCategoryRequest

@synthesize names = _names;
@synthesize aop_responseFormat = _aop_responseFormat;

- (id) init {
    if (self = [super init]) {
        //   _name = @"picture-news-config";
        _names = @"new_product_category";
//        _names = @"new_product_dress";
        
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
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMNewProductsCategoryRequest class]];
    [requestMapping mapKeyPath:@"names" toAttribute:@"names"];
    [requestMapping mapKeyPath:@"aop_responseFormat" toAttribute:@"_aop_responseFormat"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_NEWPRODUCTS_CATEGORY params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
    
}


@end

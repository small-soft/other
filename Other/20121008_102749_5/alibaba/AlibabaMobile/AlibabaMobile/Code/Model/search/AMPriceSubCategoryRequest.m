//
//  AMPriceSubCategoryRequest.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPriceSubCategoryRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"

#import <RestKit/RestKit.h>

@implementation AMPriceSubCategoryRequest

@synthesize categoryId = _categoryId;

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
 
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMPriceSubCategoryRequest class]];
    [requestMapping mapKeyPath:@"categoryId" toAttribute:@"cateId"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_PRICE_SUB_CATEGORIES params:params];
    [params release];    
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_categoryId release];
    
    [super dealloc];
}

@end

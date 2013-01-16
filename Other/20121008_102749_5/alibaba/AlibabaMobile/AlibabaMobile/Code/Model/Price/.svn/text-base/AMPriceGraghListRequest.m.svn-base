//
//  AMPriceGraghListRequest.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-13.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMPriceGraghListRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMPriceGraghListRequest
@synthesize request = _request;
@synthesize areaId = _areaId;
@synthesize themeId = _themeId;
@synthesize sourceFormId = _sourceFormId;

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
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
    
    if (self.themeId) {
        [wrappedParams setObject: self.themeId forKey:@"themeId"];
    }
    if (self.areaId) {
        [wrappedParams setObject: self.areaId forKey:@"areaId"];   
    }
    if (self.sourceFormId) {
        [wrappedParams setObject: self.sourceFormId forKey:@"sourceFormId"];
    }
    
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMPriceGraghListRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_SEARCH_PRICE_GRAGH params:params];
    NSString *subString = @"&_aop_signature=";
    NSRange range = [signedBodyString rangeOfString:subString];
    int location = range.location;

    NSString *newSignedBodyString= [signedBodyString substringToIndex:location];
    
    
    NSLog(@"%@",newSignedBodyString);
    [params release];
    
    return [newSignedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_themeId release];
    [_sourceFormId release];
    [_areaId release];
    
    [super dealloc];
}


@end

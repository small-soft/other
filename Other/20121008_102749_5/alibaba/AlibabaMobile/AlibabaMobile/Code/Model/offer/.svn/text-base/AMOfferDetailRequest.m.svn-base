//
//  AMOfferDetailRequest.m
//  AlibabaMobile
//
//  Created by mardin partytime on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferDetailRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMOfferDetailRequest

@synthesize request = _request;
@synthesize offerId = _offerId;
@synthesize imageSizeType = _imageSizeType;
@synthesize disableLink = _disableLink;

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
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMOfferDetailRequest class]];
    [requestMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
    
    if (self.disableLink) {
        [wrappedParams setObject:self.disableLink forKey:@"disableLink"];
    }
    if (self.imageSizeType) {
        [wrappedParams setObject:self.imageSizeType forKey:@"imageSizeType"];
    }
    self.request = wrappedParams;
    
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];

    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = nil;
    signedBodyString = [NSString stringWithFormat: @"_data_=%@", _data_];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    
    [_offerId release];
    [_imageSizeType release];
    [_disableLink release];
    [_request release];
   
    [super dealloc];
}

@end


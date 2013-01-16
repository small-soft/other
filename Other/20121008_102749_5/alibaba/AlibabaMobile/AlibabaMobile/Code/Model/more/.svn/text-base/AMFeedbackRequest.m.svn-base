//
//  AMFeedbackRequest.m
//  AlibabaMobile
//
//  Created by lih on 12-2-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMFeedbackRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMFeedbackRequest

@synthesize content = _content;
@synthesize type = _type;
@synthesize source = _source;
@synthesize memberId = _memberId;
@synthesize suggestion = _suggestion;

@synthesize requestURL;


- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_FEEDBACK;
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
    wrappedParams = [[NSMutableDictionary alloc] init];
    
    [wrappedParams setObject: self.content forKey: @"content"];
    [wrappedParams setObject: self.type forKey: @"type"];
    [wrappedParams setObject: self.source forKey: @"source"];
    if(self.memberId!=nil){
        [wrappedParams setObject: self.memberId forKey: @"memberId"];
    }
    
        
    self.suggestion = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMFeedbackRequest class]];

    [requestMapping mapKeyPath:@"suggestion" toAttribute:@"suggestion"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    [wrappedParams release];
        
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_FEEDBACK params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_content release];
    [_type release];
    [_source release];
    [_memberId release];
    [_suggestion release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end

//
//  LogoutRequest.m
//  AlibabaMobile
//
//  Created by lih on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "LogoutRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation LogoutRequest

@synthesize terminalId = _terminalId;
@synthesize appId = _appId;
@synthesize accessToken;
@synthesize requestURL;

- (id) init {
    if (self = [super init]) {
        self.accessToken = nil;
        self.requestURL = OCEAN_API_URL_LOGOUT;
    }    
    return self;
}

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
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[LogoutRequest class]];
    [requestMapping mapKeyPath:@"terminalId" toAttribute:@"terminalId"];
    [requestMapping mapKeyPath:@"appId" toAttribute:@"appId"];

    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    
    [params setObject: _data_ forKey: @"_data_"];
    
    NSString *signedBodyString = nil;
    if (nil != accessToken) {
        [params setObject: accessToken forKey: @"access_token"];
        signedBodyString = [NSString stringWithFormat: @"_data_=%@&access_token=%@", _data_, accessToken];
    }
    
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_terminalId release];
    [_appId release];
    [super dealloc];
}

@end
//
//  AMCompanyDetailRequest.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCompanyDetailRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMCompanyDetailRequest

@synthesize memberId, request;

- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

- (NSData*)HTTPBody { 
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCompanyDetailRequest class]];
    [requestMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
   
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


@end

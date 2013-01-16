//
//  AMVersionCheckRequest.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMVersionCheckRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMVersionCheckRequest
@synthesize myVersion=_myVersion;
@synthesize myPlatform=_myPlatform;
@synthesize myDeviceId=_myDeviceId;


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
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMVersionCheckRequest class]];
    [requestMapping mapKeyPath:@"myVersion" toAttribute:@"myVersion"];
    [requestMapping mapKeyPath:@"myPlatform" toAttribute:@"myPlatform"];
    [requestMapping mapKeyPath:@"myDeviceId" toAttribute:@"myDeviceId"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];

    // Create NSDictionary object and setObject to it
   _data_ = CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,(CFStringRef)_data_, NULL, CFSTR(":/?#[]@!$&’()*+,;="), kCFStringEncodingUTF8);
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    
    NSString *signedBodyString = [NSString stringWithFormat: @"_data_=%@", _data_];
    
    [params release];    
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

-(void)dealloc
{
    [_myVersion release];
    [_myPlatform release];
    [_myDeviceId release];

    [super dealloc];
}
@end

//
//  AMGeoGraphicInfoRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMGeoGraphicInfoRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

#import <RestKit/RestKit.h>

@implementation AMGeoGraphicInfoRequest

@synthesize latitude=_latitude;
@synthesize longitude=_longitude;

-(void)dealloc
{
    [_latitude release];
    [_longitude release];
    [super dealloc];
}


- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMGeoGraphicInfoRequest class]];
    [requestMapping mapKeyPath:@"latitude" toAttribute:@"latitude"];
    [requestMapping mapKeyPath:@"longitude" toAttribute:@"longitude"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    
    [params setObject: _data_ forKey: @"_data_"];
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_GEO params:params];
    
    [params release];    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

@end

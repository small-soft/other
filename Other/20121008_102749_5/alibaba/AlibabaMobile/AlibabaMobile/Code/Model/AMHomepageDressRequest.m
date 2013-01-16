//
//  AMHomepageDressRequest.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMHomepageDressRequest
@synthesize transactionType = _transactionType;
@synthesize request = _request;
@synthesize industryId = _industryId;
@synthesize summary = _summary;
@synthesize configName = _configName;

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
    if (self.industryId) {
        [wrappedParams setObject: self.industryId forKey:@"industryId"];
    }
    NSMutableDictionary *wrappedParamsInter = [[[NSMutableDictionary alloc] init] autorelease];
        
    if (self.configName) {
        [wrappedParamsInter setObject: self.configName forKey:@"configName"];
    }
    if (self.summary) {
        [wrappedParamsInter setObject: self.summary forKey:@"summary"];   
    }
    NSMutableArray *wrappedParamsInterArray = [[NSMutableArray alloc] init];
    [wrappedParamsInterArray addObject:wrappedParamsInter];
    [wrappedParams setObject:wrappedParamsInterArray forKey:@"dataRequests"];
    [wrappedParamsInterArray release];
//    [wrappedParams setObject:wrappedParamsInter forKey:@"dataRequests"];
    
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMHomepageDressRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    //加入方括号
//    NSRange range = [_data_ rangeOfString:@"dataRequests"];
//    int location = range.location;
//    NSMutableString * _newData_ =  [NSMutableString stringWithString:_data_];  
//    [_newData_ insertString:@"[" atIndex:location+14];  
//    [_newData_ insertString:@"]" atIndex:_newData_.length - 2];  
//    NSString * _newdata_ = [NSMutableString stringWithString:_newData_]; 
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
//    [params setObject: _newdata_ forKey: @"_data_"];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_INDUSTRY_CONTENTS params:params];
    /*NSString *subString = @"&_aop_signature=";
    range = [signedBodyString rangeOfString:subString];
    location = range.location;
    
    NSString *newSignedBodyString= [signedBodyString substringToIndex:location];
    
    
    NSLog(@"signedBodyString : %@",newSignedBodyString);*/
    NSLog(@"signedBodyString : %@",signedBodyString);
    [params release];
    
    NSLog(@"=========params:%@",signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_request release];
    [_industryId release];
    [_summary release];
    [_configName release];
    [super dealloc];
}

@end

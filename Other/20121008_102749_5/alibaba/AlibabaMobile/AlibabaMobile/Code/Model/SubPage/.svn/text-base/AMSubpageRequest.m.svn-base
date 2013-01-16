//
//  AMIndustrySubpageRequest.m
//  AlibabaMobile
//
//  Created by  on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageRequest.h"
#import <RestKit/RestKit.h>
#import "ConstDef.h"
#import "SecurityUtil.h"
//@implementation AMDataRequests
//@synthesize configName,summary;
//@end

@implementation AMSubpageRequest
@synthesize transactionType = _transactionType;
@synthesize industryId = _industryId;
@synthesize categoryId = _categoryId;
@synthesize dataRequests = _dataRequests;
@synthesize request = _request;
@synthesize loginId = _loginId;
@synthesize terminalId = _terminalId;
- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}


- (NSData*)HTTPBody {
    
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
    if (self.industryId) {
        [wrappedParams setObject: self.industryId forKey:@"industryId"];
    }
    if (self.categoryId) {
        [wrappedParams setObject:self.categoryId forKey:@"categoryId"];
    }
    
    if (self.loginId) {
        [wrappedParams setObject: self.loginId forKey:@"loginId"];
    }
    
    if (self.terminalId) {
        [wrappedParams setObject: self.terminalId forKey:@"terminalId"];
    }
    
    if (self.dataRequests) {
        [wrappedParams setObject:self.dataRequests forKey:@"dataRequests"];
    }
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMSubpageRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
//    [requestMapping mapKeyPath:@"industryId" toAttribute:@"industryId"];
//    [requestMapping mapKeyPath:@"categoryId" toAttribute:@"categoryId"];
//    [requestMapping mapKeyPath:@"dataRequests" toAttribute:@"dataRequests"];
//    RKObjectMapping* dataRequestMapping = [RKObjectMapping mappingForClass:[AMDataRequests class]];
//    [dataRequestMapping mapKeyPath:@"configName" toAttribute:@"configName"];
//    [dataRequestMapping mapKeyPath:@"summary" toAttribute:@"summary"];
//    [requestMapping mapRelationship:@"dataRequests" withMapping:dataRequestMapping];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];

    
    
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_INDUSTRY_SUBPAGE params:params];
    
    NSLog(@"signedBodyString : %@",signedBodyString);
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_request release];
    [_industryId release];
    [_categoryId release];
    [_dataRequests release];
    [_terminalId release];
    [_loginId release];
    [super dealloc];
}
@end

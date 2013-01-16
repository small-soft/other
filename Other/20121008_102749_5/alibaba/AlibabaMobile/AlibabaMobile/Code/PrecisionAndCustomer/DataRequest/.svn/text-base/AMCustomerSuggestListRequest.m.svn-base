//
//  AMCustomerSuggestListRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerSuggestListRequest.h"
#import "AMCUDFavoriteRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMCustomerSuggestListRequest

@synthesize pageInfo = _pageInfo;
@synthesize pageIndex = _pageIndex;
@synthesize pageSize = _pageSize;
@synthesize requestURL = _requestURL;
@synthesize transactionType = _transactionType;

- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_CUSTOMER_SUGGEST_LIST;
        self.pageIndex = [NSNumber numberWithInt:1];
    }
    return self;
}

- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

- (NSData*)HTTPBody {
    
    NSMutableDictionary *wrappedParams = nil;
    
    wrappedParams = [[NSMutableDictionary alloc] init];
//    self.pageIndex = [NSNumber numberWithInt:1];
    self.pageSize = [NSNumber numberWithInt:9];
    [wrappedParams setObject: self.pageIndex forKey: @"pageIndex"];
    [wrappedParams setObject: self.pageSize forKey: @"pageSize"];
        
    self.pageInfo = wrappedParams;
    [wrappedParams release];
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCustomerSuggestListRequest class]];
    
	[requestMapping mapKeyPath:@"pageInfo" toAttribute:@"pageInfo"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    self.pageInfo = nil;
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    NSLog(@"url=https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getLeadsCustomer/5005?%@",signedBodyString);
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_pageIndex release];
    [_pageSize release];
    [_pageInfo release];
    self.requestURL = nil;
    
    [super dealloc];
}

@end
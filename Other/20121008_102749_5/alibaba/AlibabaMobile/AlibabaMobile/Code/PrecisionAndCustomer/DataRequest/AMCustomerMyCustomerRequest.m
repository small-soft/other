//
//  AMGuestRequest.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getCustomerList/5005?_data_={request:{pageInfo:{pageSize:10,pageIndex:4}}}&access_token=19db41eb-1d70-4f74-88cc-8ad6adb6fc46

#import "AMCustomerMyCustomerRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMCustomerMyCustomerRequest
@synthesize request = _request;

@synthesize pageInfo = _pageInfo;
@synthesize pageSize = _pageSize;
@synthesize pageIndex = _pageIndex;
@synthesize groupId = _groupId;
@synthesize province = _province;
@synthesize buyerName = _buyerName;
@synthesize corpName = _corpName;
@synthesize phoneNumber = _phoneNumber;

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
    
    
    NSMutableDictionary *wrappedParams1 = [[[NSMutableDictionary alloc] init] autorelease];
    self.pageSize = [NSNumber numberWithInt:10]; 
//    self.pageIndex = [NSNumber numberWithInt:4];
    
    
    
    [wrappedParams1 setObject:self.pageSize forKey:@"pageSize"];
    [wrappedParams1 setObject:self.pageIndex forKey:@"pageIndex"];
    
    NSMutableDictionary *wrappedParams2 = [[[NSMutableDictionary alloc] init] autorelease];
    
    [wrappedParams2 setObject:wrappedParams1 forKey:@"pageInfo"];
    if (!self.province) {
        self.province = @"eqAll";
    }
    [wrappedParams2 setObject:self.province forKey:@"province"];
    if(!self.groupId){
        self.groupId = @"eqAll";
    }

    if(self.corpName){
        [wrappedParams2 setObject:self.corpName forKey:@"corpName"];
    }
    
    if(self.phoneNumber){
        [wrappedParams2 setObject:self.phoneNumber forKey:@"phoneNumber"];
    }
    
    if(self.buyerName){
        [wrappedParams2 setObject:self.buyerName forKey:@"buyerName"];
    }
    [wrappedParams2 setObject:self.groupId forKey:@"groupId"];
    self.request = wrappedParams2;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCustomerMyCustomerRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    
    NSString *paramsString = [NSString stringWithString:@""];
    
    
    if (params != nil && [params count] > 0) {
        for (NSString *key in [params allKeys]) {
            NSString *value = [params objectForKey: key];
            paramsString = [paramsString stringByAppendingFormat:[paramsString length] == 0 ? @"%@=%@" : @"&%@=%@", key, value];
        }
    }

        
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CUSTOMER_MYCUSTOMER_LIST params:params];
    [params release];

    NSLog(@"REQUEST=https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getCustomerList/5005?%@",signedBodyString );
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];

}

- (void) dealloc {
    
    [_request release];
    [_pageInfo release];
    [_pageSize release];
    [_phoneNumber release];
    [_groupId release];
    [_province release];
    [_corpName release];
    [_buyerName release];
    [super dealloc];
}

@end

//
//  AMNewProductsListRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-5-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsListRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMNewProductsListRequest

@synthesize operationId = _operationId;
@synthesize pageSize = _pageSize;
@synthesize pageIndex = _pageIndex;

@synthesize requestURL;

-(id)init {
    [super init];
    if (self) {
        self.pageIndex = [NSNumber numberWithInt: 1];
        self.pageSize = [NSNumber numberWithInt: 20];
        self.operationId = [NSString stringWithFormat:@"clothing_women"];
        self.requestURL = OCEAN_API_URL_NEWPRODUCTS_LIST;
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
    NSString *signedBodyString = nil;
    
//    NSString *_data_ = [NSString stringWithFormat: @"{request:{page:%@,count:%@,categoryid:\"%@\"}}", self.page, self.count, self.categoryid];
  
    NSString *_data_ = [NSString stringWithFormat: @"{request:{operationId:\"%@\",pageInfo:{pageIndex:%@,pageSize:%@}}}", self.operationId, self.pageIndex, self.pageSize];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    [params release];	
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];

}

- (void) dealloc {
    [_operationId release];
    [_pageIndex release];
    [_pageSize release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end

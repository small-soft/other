//
//  AMNewProductsListRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-5-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_NEWPRODUCTS_LIST ([@"/operation.listOffer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMNewProductsListRequest : NSObject <RKRequestSerializable> {
    
    NSNumber * _pageIndex;

    NSNumber * _pageSize;
    NSString * _operationId;
}

@property(nonatomic, retain) NSString * operationId;
@property(nonatomic, retain) NSNumber * pageIndex;
@property(nonatomic, retain) NSNumber * pageSize;

@property(nonatomic, retain) NSString * requestURL;

- (id) init;
@end
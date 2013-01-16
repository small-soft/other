//
//  AMCustomerInfoRequest.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_CUSTOMER_USERINFO ([@"/customer.getCustomer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCustomerInfoRequest : NSObject<RKRequestSerializable> {
    
    NSDictionary * _request;
    
    NSDictionary * _pageInfo;
    NSNumber *pageSize;
    NSNumber *pageIndex;
}

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic,retain) NSDictionary * pageInfo;
@property (nonatomic,retain) NSNumber *pageSize;
@property (nonatomic,retain) NSNumber *pageIndex; 
@property (nonatomic,retain) NSString *buyerId;


@end

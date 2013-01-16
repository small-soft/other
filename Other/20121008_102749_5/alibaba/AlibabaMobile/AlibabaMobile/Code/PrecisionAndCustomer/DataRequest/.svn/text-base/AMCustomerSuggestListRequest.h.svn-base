//
//  AMCustomerSuggestListRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getLeadsCustomer/5005?_aop_signature=E0FF47B266F7C9B8447C3D9E4E3134E9C703880D&access_token=3224e1c3-936f-48c4-85b2-4aea7fbe80e7&targetId=53&_data_={"pageInfo":{"pageIndex":1,"pageSize":9}}&clickId=11&clickUUID=90627cbd-9168-4e0f-9616-43b9e79e026f&deviceId=d01f62eb7d83d52ff54e48fcf72c41c1&pageId=50

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_CUSTOMER_SUGGEST_LIST ([@"/customer.getLeadsCustomer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCustomerSuggestListRequest : NSObject <RKRequestSerializable, AMRequestDelegate>{
    
    NSNumber *_pageIndex;
    NSNumber *_pageSize;
	NSDictionary *_pageInfo;
    
}
@property (nonatomic, retain) NSNumber *pageIndex;
@property (nonatomic, retain) NSNumber *pageSize;
@property (nonatomic, retain) NSDictionary *pageInfo;
@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;

@end

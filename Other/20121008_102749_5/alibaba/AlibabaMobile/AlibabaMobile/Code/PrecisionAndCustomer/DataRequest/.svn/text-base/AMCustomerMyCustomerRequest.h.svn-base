//
//  AMGuestRequest.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.  --》modify by xiaowen
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getCustomerList/5005?_aop_signature=B1DE97C251D72D5E2DE1A8A877D62E7DEA963CE7&access_token=9a8c3c90-1eb7-4578-900e-014973ab86a8&targetId=70&_data_={"request":{"groupId":"eqAll","pageInfo":{"pageIndex":1,"pageSize":9},"province":"eqAll"}}&clickId=15&clickUUID=a4373062-9a7d-4f09-aae4-d599977a6c3d&deviceId=d01f62eb7d83d52ff54e48fcf72c41c1&pageId=106

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_CUSTOMER_MYCUSTOMER_LIST ([@"/customer.getCustomerList/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCustomerMyCustomerRequest : NSObject<RKRequestSerializable> {
    
    NSDictionary * _request;
    
    NSDictionary * _pageInfo;
    NSNumber *_pageSize;
    NSNumber *_pageIndex;
    NSString *_groupId;
    NSString *_province;
    NSString *_corpName;
    NSString *_buyerName;
    NSString *_phoneNumber;
    
}

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic,retain) NSDictionary * pageInfo;
@property (nonatomic,retain) NSNumber *pageSize;
@property (nonatomic,retain) NSNumber *pageIndex; 
@property (nonatomic,retain) NSString *groupId;
@property (nonatomic,retain) NSString *province;
@property (nonatomic,retain) NSString *corpName;
@property (nonatomic,retain) NSString *buyerName;
@property (nonatomic,retain) NSString *phoneNumber;

@end

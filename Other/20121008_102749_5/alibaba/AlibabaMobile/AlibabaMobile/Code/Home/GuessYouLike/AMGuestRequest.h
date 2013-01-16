//
//  AMGuestRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/recommend.getOffers/5005?targetId=60&_data_={"request":{"count":10,"positionId":"android_homepage_offer","termId":"d01f62eb7d83d52ff54e48fcf72c41c1"}}&clickId=13&clickUUID=bb086ed1-6777-44c5-98c7-dd9ed8724577&deviceId=d01f62eb7d83d52ff54e48fcf72c41c1&pageId=1

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_GUEST ([@"/recommend.getOffers/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMGuestRequest : NSObject<RKRequestSerializable> {
    
    NSDictionary * _request;
    
    NSNumber *count;
    NSString *ios_homepage_offer;
    NSString *termId;
    
}

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic,retain) NSNumber *count;
@property (nonatomic,retain) NSString *ios_homepage_offer;
@property (nonatomic,retain) NSString *termId;


@end

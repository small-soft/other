//
//  AMGuestRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/activity.topic.findTopicGroup/5005?_data_={request:{configName:%22offer-list%22,summary:%22%22}}

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_ACTIVITY ([@"/activity.topic.findTopicGroup/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMActivityListRequest : NSObject<RKRequestSerializable> {
    
    NSDictionary * _request;
    NSString *_industryId;
}

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic,retain) NSString *industryId;


@end
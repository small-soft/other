//
//  AMTopicOfferRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/activity.topic.listTopicOffer/5005?_data_={topicId:102904}

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_TOPIC_OFFER_LIST ([@"/activity.topic.listTopicOffer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMTopicOfferRequest : NSObject<RKRequestSerializable>{
    
    NSNumber *_topicId;
    NSNumber *_pageSize;
    NSNumber *_pageIndex;
    NSString *_requestURL;
    
}

@property (retain,nonatomic) NSNumber *topicId;
@property (retain,nonatomic) NSNumber *pageSize;
@property (retain,nonatomic) NSNumber *pageIndex;
@property (retain,nonatomic) NSString *requestURL;

-(id) init;
@end

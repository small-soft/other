//
//  AMGuessResult.m
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
//{"tags":"xianhuo","requiredCategories":"326","startDate":"20120805032040000+0800","expired":false,"offerCount":0,"endDate":"20120906000000000+0800","bu":"服装服饰","topicLogo":"http://i05.c.aliimg.com/bttopic/12841/1338036023524.gif","id":102533,"market":"服装服饰","topicUrl":"http://small.china.alibaba.com/topic/general/topic_detail.htm?tid=102533","description":"2012年服饰配件行业将开始重点运营，将对符合要求的服饰配件诚信通会员免费推广，抓住开幕良机，过时不候！服饰配件重点品类包括：帽子，腰带腰链，领带领结，手套，围巾丝巾披肩","name":"2012服饰配件供应商招募"}

#import "AMActivityListResult.h"

@implementation AMActivityListResult

@synthesize topicList = _topicList;
@synthesize summary = _summary;
@synthesize updated = _updated;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMActivityListResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"summary" toAttribute:@"summary"];
            [sharedObjectMapping mapKeyPath:@"updated" toAttribute:@"updated"];
			[sharedObjectMapping mapRelationship:@"topicList" withMapping:[AMActivity sharedObjectMapping]];

        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_summary release];
    [_updated release];
    [_topicList release];
    
    [super dealloc];
}

@end




@implementation AMActivity

@synthesize buKeywords = _buKeywords;
@synthesize endDate = _endDate;
@synthesize description = _description;
@synthesize activityId = _activityId;
@synthesize market = _market;
@synthesize name = _name;
@synthesize startDate = _startDate;
@synthesize topicLogo = _topicLogo;
@synthesize topicUrl = _topicUrl;
@synthesize offerCount = _offerCount;
@synthesize expired = _expired;
@synthesize topicStartDate = _topicStartDate;
@synthesize topicEndDate = _topicEndDate;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMActivity class]] retain];
			[sharedObjectMapping mapKeyPath:@"buKeywords" toAttribute:@"buKeywords"];
			[sharedObjectMapping mapKeyPath:@"endDate" toAttribute:@"endDate"];
			[sharedObjectMapping mapKeyPath:@"description" toAttribute:@"description"];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"activityId"];
			[sharedObjectMapping mapKeyPath:@"market" toAttribute:@"market"];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
			[sharedObjectMapping mapKeyPath:@"startDate" toAttribute:@"startDate"];
			[sharedObjectMapping mapKeyPath:@"topicLogo" toAttribute:@"topicLogo"];
			[sharedObjectMapping mapKeyPath:@"topicUrl" toAttribute:@"topicUrl"];
            [sharedObjectMapping mapKeyPath:@"offerCount" toAttribute:@"offerCount"];
            [sharedObjectMapping mapKeyPath:@"expired" toAttribute:@"expired"];
            [sharedObjectMapping mapKeyPath:@"topicStartDate" toAttribute:@"topicStartDate"];
            [sharedObjectMapping mapKeyPath:@"topicEndDate" toAttribute:@"topicEndDate"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {

    [_buKeywords release];
    [_endDate release];
    [_description release];
    [_activityId release];
    [_market release];
    [_name release];
    [_startDate release];
    [_topicLogo release];
    [_topicUrl release];
    [_offerCount release];
    [_expired release];
    [_topicStartDate release];
    [_topicEndDate release];
    
    [super dealloc];
}

@end

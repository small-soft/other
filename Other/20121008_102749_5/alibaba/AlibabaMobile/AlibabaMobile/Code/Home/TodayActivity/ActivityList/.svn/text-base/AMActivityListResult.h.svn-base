//
//  AMGuessResult.h
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

// {"tags":"xianhuo","requiredCategories":"326","startDate":"20120805032040000+0800","expired":false,"offerCount":0,"endDate":"20120906000000000+0800","bu":"服装服饰","topicLogo":"http://i05.c.aliimg.com/bttopic/12841/1338036023524.gif","id":102533,"market":"服装服饰","topicUrl":"http://small.china.alibaba.com/topic/general/topic_detail.htm?tid=102533","description":"2012年服饰配件行业将开始重点运营，将对符合要求的服饰配件诚信通会员免费推广，抓住开幕良机，过时不候！服饰配件重点品类包括：帽子，腰带腰链，领带领结，手套，围巾丝巾披肩","name":"2012服饰配件供应商招募"}

#import "AMObjectMappingDelegate.h"

@interface AMActivityListResult : NSObject <AMObjectMappingDelegate> {
    
    NSArray * _topicList;
    NSString * _summary;
    NSString *_updated;
    
}

@property(nonatomic, retain)  NSArray * topicList;
@property(nonatomic, copy)  NSString * summary;
@property(nonatomic, copy)  NSString *updated;;

@end


@interface AMActivity : NSObject <AMObjectMappingDelegate> {

    /**
     * 活动id
     */
    NSNumber * _activityId;
    
    /**
     * 开始日期
     */
    NSNumber * _startDate;
    
    /**
     * market
     */
    NSString * _market;
    
    /**
     * _topicUrl
     */
    NSString * _topicUrl;
    
    /**
     * description
     */
    NSString * _description;
    
    /**
     * 活动titile
     */
    NSString * _name;
    
    /**
     * 关键字
     */
    NSString * _buKeywords;
    
    /**
     * endDate
     */
    NSNumber * _endDate;
    
    /**
     * 活动图片
     */
    NSString * _topicLogo;
    
    /**
     * 是否过期，返回true or false
     */
    NSString * _expired;
    
    /**
     * 参与活动的产品数量
     */
    NSString *_offerCount;
    
    NSString *_topicStartDate;
    
    NSString *_topicEndDate;
}

@property(nonatomic, retain) NSNumber * activityId;
@property(nonatomic, retain) NSNumber * startDate;
@property(nonatomic, retain) NSString * market;
@property(nonatomic, retain) NSString * topicUrl;
@property(nonatomic, retain) NSString * description;
@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSString * buKeywords;
@property(nonatomic, retain) NSNumber * endDate;
@property(nonatomic, retain) NSString * topicLogo;
@property(nonatomic, retain) NSString * expired;
@property(nonatomic, retain) NSString * offerCount;
@property(nonatomic, retain) NSString * topicStartDate;
@property(nonatomic, retain) NSString * topicEndDate;


@end

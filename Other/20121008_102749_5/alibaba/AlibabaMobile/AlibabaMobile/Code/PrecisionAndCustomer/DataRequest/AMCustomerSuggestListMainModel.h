//
//  AMCustomerSuggestListMainModel.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMCustomerImage.h"

//推荐客户数据请求resultList对应数据model
@interface AMCustomerSuggestListMainModel : NSObject <AMObjectMappingDelegate> {
    
    NSString *_name;//姓名
    NSString *_province;//省份地址
    NSString *_mainBiz;//行业类型，比如服装
    NSString *_interestInfo;//关注我的公司内的我的公司
    NSString *_visitDate;//关注我的公司内的日期
    NSString *_intent;//意向度，M-->中
    NSArray *_buyItems;//最想买，返回为数组
    NSString *_overdueDays;//几天后过期
    AMCustomerImage *_headImage;//客户图片
}

@property(nonatomic, retain) NSString *name;
@property(nonatomic, retain) NSString *province;
@property(nonatomic, retain) NSString *mainBiz;
@property(nonatomic, retain) NSString *interestInfo;
@property(nonatomic, retain) NSString *visitDate;
@property(nonatomic, retain) NSString *intent;
@property(nonatomic, retain) NSArray *buyItems;
@property(nonatomic, retain) NSString *overdueDays;
@property(nonatomic, retain) NSString *customerMemberId;
@property(nonatomic, retain) NSString *leadsId;
@property(nonatomic, retain) NSString *status;
@property(nonatomic, retain) AMCustomerImage *headImage;

@end

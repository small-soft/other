//
//  AMRecommendBrandsResult.h
//  AlibabaMobile
//
//  Created by 佳 刘 on 12-9-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

// {"brands":{"md5Checksum":"7dc637e0991d93925469d94603dfc33e","imageUrl":"http://img.china.alibaba.com/img/ibank/2012/992/595/633595299.jpg","children":[{"id":"brand1","imageUrl":"http://img.china.alibaba.com/img/ibank/2012/434/395/633593434.jpg","name":"品牌1","hasChild":false,"type":"brand"},{"id":"brand2","imageUrl":"http://img.china.alibaba.com/img/ibank/2012/434/395/633593434.jpg","name":"品牌2","hasChild":false,"type":"brand"}],"type":"brands","updated":true,"hasChild":true}}

#import "AMObjectMappingDelegate.h"


@interface AMRecommendBrandsItem : NSObject <AMObjectMappingDelegate> 

@property(nonatomic,retain) NSString *brandId;
@property(nonatomic,retain) NSString *imageUrl;
@property(nonatomic,retain) NSString *name;
@property(nonatomic,retain) NSString *hasChild;
@property(nonatomic,retain) NSString *type;


@end

@interface AMRecommendBrands : NSObject <AMObjectMappingDelegate> 

@property(nonatomic, retain)  NSArray *children;
@property(nonatomic, copy)  NSString *updated;
@property(nonatomic, copy)  NSString *type;
@property(nonatomic, copy)  NSString *hasChild;
@property(nonatomic, copy) NSString *imageUrl;
@property(nonatomic, copy) NSString *md5Checksum;

@end

@interface AMRecommendBrandsResult : NSObject <AMObjectMappingDelegate> 

@property(nonatomic, retain) AMRecommendBrands *brandsios;
@end
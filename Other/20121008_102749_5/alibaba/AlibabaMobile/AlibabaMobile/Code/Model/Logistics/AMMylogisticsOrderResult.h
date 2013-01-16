//
//  AMMylogisticsOrderResult.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMObjectMappingDelegate.h"



@interface AMMylogisticsOrderResult : NSObject <AMObjectMappingDelegate> 


@property(nonatomic, retain) NSNumber * totalCount;
@property(nonatomic, retain) NSNumber * pageSize;
@property(nonatomic, retain) NSNumber * pageIndex;
@property(nonatomic, retain) NSArray * resultList;
@end

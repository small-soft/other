//
//  AMSubpageRecommendOrHistoryResult.h
//  AlibabaMobile
//
//  Created by  on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AMObjectMappingDelegate.h"
@interface AMSubpageRecommendOrHistoryResult : NSObject<AMObjectMappingDelegate>

@property(nonatomic, copy) NSString *type;
@property(nonatomic, assign) BOOL updated;
@property(nonatomic, assign) BOOL hasChild;
@property(nonatomic, retain) NSArray *children;

@end

@interface AMSubpageRecommendOrHistoryChildren : NSObject<AMObjectMappingDelegate>

@property(nonatomic, copy) NSString *ID;
@property(nonatomic, copy) NSString *type;
@property(nonatomic, copy) NSString *name;
@property(nonatomic, assign) BOOL hasChild;
//@property(nonatomic, retain) NSArray *children;
@end

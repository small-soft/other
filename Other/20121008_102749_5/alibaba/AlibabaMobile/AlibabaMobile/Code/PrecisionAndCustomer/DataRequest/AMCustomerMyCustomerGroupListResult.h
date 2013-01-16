//
//  AMCustomerMyCustomerGroupListResult.h
//  AlibabaMobile
//
//  Created by xiaowen on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMObjectMappingDelegate.h"

@interface AMCustomerMyCustomerGroupListResult : NSObject <AMObjectMappingDelegate> {
    
    NSArray * _resultList;
}



@property(nonatomic, retain) NSArray * resultList;

@end

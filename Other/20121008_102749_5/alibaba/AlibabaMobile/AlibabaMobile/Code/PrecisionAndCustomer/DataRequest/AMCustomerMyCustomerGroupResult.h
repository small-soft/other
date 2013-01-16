//
//  AMCustomerMyCustomerGroupResult.h
//  AlibabaMobile
//
//  Created by xiaowen on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMObjectMappingDelegate.h"

@interface AMCustomerMyCustomerGroupResult : NSObject <AMObjectMappingDelegate> {
    
    NSArray * _groupList;
    NSArray * _areaList;
}



@property(nonatomic, retain) NSArray * groupList;
@property(nonatomic, retain) NSArray * areaList;

@end

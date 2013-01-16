//
//  AMGuessResult.m
//  AlibabaMobile
//
//  Created by xiaowen.jul on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerMyCustomerGroupResult.h"
#import "AMCustomerMyCustomerGroupListResult.h"

@implementation AMCustomerMyCustomerGroupResult


@synthesize groupList =_groupList;
@synthesize areaList = _areaList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerMyCustomerGroupResult class]] retain];
            
			[sharedObjectMapping mapRelationship:@"groupList" withMapping:[AMCustomerMyCustomerGroupListResult sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"areaList" withMapping:[AMCustomerMyCustomerGroupListResult sharedObjectMapping]];
            
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCustomerMyCustomerGroupListResult sharedObjectMapping] forKeyPath:@"groupList"];
            [mappingProvider setMapping:[AMCustomerMyCustomerGroupListResult sharedObjectMapping] forKeyPath:@"areaList"];
            
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    
    [_areaList release];
    [_groupList release];
    
    [super dealloc];
}

@end

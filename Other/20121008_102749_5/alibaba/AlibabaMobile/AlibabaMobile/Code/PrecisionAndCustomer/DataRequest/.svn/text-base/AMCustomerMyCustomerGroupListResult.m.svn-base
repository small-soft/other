//
//  AMCustomerMyCustomerGroupListResult.m
//  AlibabaMobile
//
//  Created by xiaowen.jul on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerMyCustomerGroupListResult.h"
#import "AMCustomerMyCustomerGroupModel.h"

@implementation AMCustomerMyCustomerGroupListResult


@synthesize resultList =_resultList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerMyCustomerGroupListResult class]] retain];
            
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMCustomerMyCustomerGroupModel sharedObjectMapping]];
            
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCustomerMyCustomerGroupModel sharedObjectMapping] forKeyPath:@"resultList"];
            
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    
    [_resultList release];
 
    [super dealloc];
}

@end

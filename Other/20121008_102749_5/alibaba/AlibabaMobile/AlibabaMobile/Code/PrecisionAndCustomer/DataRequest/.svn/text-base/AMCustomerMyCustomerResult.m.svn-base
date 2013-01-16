//
//  AMGuessResult.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.  --》modify by xiaowen
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerMyCustomerResult.h"
#import "AMCustomerMyCustomerListModel.h"

@implementation AMCustomerMyCustomerResult

@synthesize totalCount =_totalCount;
@synthesize pageSize =_pageSize;
@synthesize pageIndex =_pageIndex;
@synthesize resultList =_resultList;
@synthesize success =_success;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerMyCustomerResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMCustomerMyCustomerListModel sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCustomerMyCustomerListModel sharedObjectMapping] forKeyPath:@"resultList"];
            
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_totalCount release];
    [_pageSize release];
    [_pageIndex release];
    [_resultList release];
    [_success release];
    
    [super dealloc];
}

@end

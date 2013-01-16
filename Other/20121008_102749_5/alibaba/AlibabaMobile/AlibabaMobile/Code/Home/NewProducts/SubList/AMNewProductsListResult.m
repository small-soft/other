//
//  AMNewProductsListResult.m
//  AlibabaMobile
//
//  Created by amon on 12-5-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsListResult.h"
#import "AMNewProductsListItem.h"
#import <RestKit/RestKit.h>

@implementation AMNewProductsListResult

@synthesize totalCount = _totalCount;
@synthesize pageSize = _pageSize;
@synthesize resultList = _resultList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewProductsListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapKeyPath:@"pageSize" toAttribute:@"pageSize"];
			
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMNewProductsListItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMNewProductsListItem sharedObjectMapping] forKeyPath:@"resultList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_totalCount release];
    [_pageSize release];
    [_resultList release];
    
    [super dealloc];
}

@end

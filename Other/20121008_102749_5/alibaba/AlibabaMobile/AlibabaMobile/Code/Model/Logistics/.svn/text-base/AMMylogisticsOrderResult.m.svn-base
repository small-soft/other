//
//  AMMylogisticsOrderResult.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMylogisticsOrderResult.h"
#import "AMMylogisticsOrder.h"
@implementation AMMylogisticsOrderResult
@synthesize resultList = _resultList;
@synthesize totalCount = _totalCount;
@synthesize pageSize=_pageSize;
@synthesize pageIndex=_pageIndex;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMylogisticsOrderResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapKeyPath:@"pageSize" toAttribute:@"pageSize"];
            [sharedObjectMapping mapKeyPath:@"pageIndex" toAttribute:@"pageIndex"];
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMMylogisticsOrder sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMMylogisticsOrder sharedObjectMapping] forKeyPath:@"resultList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_pageSize release];
    [_totalCount release];
    [_resultList release];
    [_pageIndex release];
    [super dealloc];
}

@end

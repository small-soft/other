//
//  AMSubpageResult.m
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageResult.h"

@implementation AMSubpageResult
@synthesize tree = _tree;
@synthesize recommend = _recommend;
@synthesize history = _history;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSubpageResult class]] retain];
            
			[sharedObjectMapping mapRelationship:@"tree" withMapping:[AMSubpageTreeResult sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"recommend" withMapping:[AMSubpageRecommendOrHistoryResult sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"history" withMapping:[AMSubpageRecommendOrHistoryResult sharedObjectMapping]];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_tree release];
    [_recommend release];
    [_history release];
    [super dealloc];
}
@end
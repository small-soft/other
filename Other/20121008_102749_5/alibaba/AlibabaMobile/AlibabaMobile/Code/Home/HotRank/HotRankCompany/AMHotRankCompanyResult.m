//
//  AMHotRankResult.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankCompanyResult.h"
#import "AMHotRankCompany.h"
@implementation AMHotRankCompanyResult

@synthesize total = _total;
@synthesize rankList = _rankList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotRankCompanyResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];
			[sharedObjectMapping mapRelationship:@"rankList" withMapping:[AMHotRankCompany sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHotRankCompany sharedObjectMapping] forKeyPath:@"rankList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc{
    [_total release];
    [_rankList release]; 
    [super dealloc];
}

@end

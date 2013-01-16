//
//  AMSpecialPriceOfferResult.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSpecialPriceOfferResult.h"
#import "AMSpecialPriceOffer.h"
@implementation AMSpecialPriceOfferResult

@synthesize totalCount = _totalCount;
@synthesize resultList = _resultList;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSpecialPriceOfferResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMSpecialPriceOffer sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMSpecialPriceOffer sharedObjectMapping] forKeyPath:@"resultList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc{
    [_totalCount release];
    [_resultList release]; 
    [super dealloc];
}

@end


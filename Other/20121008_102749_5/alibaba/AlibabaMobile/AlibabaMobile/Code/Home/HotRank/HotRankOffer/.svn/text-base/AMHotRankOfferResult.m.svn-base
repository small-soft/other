//
//  AMHotRankOfferResult.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankOfferResult.h"
#import "AMHotRankOffer.h"
@implementation AMHotRankOfferResult

@synthesize total = _total;
@synthesize offerList = _offerList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotRankOfferResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];
			[sharedObjectMapping mapRelationship:@"offerList" withMapping:[AMHotRankOffer sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHotRankOffer sharedObjectMapping] forKeyPath:@"offerList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc{
    [_total release];
    [_offerList release]; 
    [super dealloc];
}

@end


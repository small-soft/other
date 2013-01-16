//
//  AMGuessResult.m
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMGuessResult.h"

@implementation AMGuessResult

@synthesize offerList = _offerList;
@synthesize ctrIds = _ctrIds;
@synthesize recId = _recId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMGuessResult class]] retain];
			[sharedObjectMapping mapRelationship:@"offerList" withMapping:[AMOffer sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMOffer sharedObjectMapping] forKeyPath:@"offerList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_ctrIds release];
    [_recId release];
    [_offerList release];
    
    [super dealloc];
}

@end

//
//  AMCustomerSuggestListResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerSuggestListResult.h"

#import "AMCustomerSuggestListMainModel.h"
#import <RestKit/RestKit.h>


@implementation AMCustomerSuggestListResult

@synthesize totalCount = _totalCount;
@synthesize resultList = _resultList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerSuggestListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
            
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMCustomerSuggestListMainModel sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCustomerSuggestListMainModel sharedObjectMapping] forKeyPath:@"resultList"];
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_totalCount release];
    [_resultList release];
    [super dealloc];
}

@end

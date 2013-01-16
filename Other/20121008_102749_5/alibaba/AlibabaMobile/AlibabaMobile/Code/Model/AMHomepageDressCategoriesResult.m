//
//  AMHomepageDressCategoriesResult.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressCategoriesResult.h"

@implementation AMHomepageDressCategoriesResult
@synthesize categories = _categories;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressCategoriesResult class]] retain];
            
			[sharedObjectMapping mapRelationship:@"categories" withMapping:[AMHomepageDressBanner sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHomepageDressBanner sharedObjectMapping] forKeyPath:@"categories"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_categories release];
    
    [super dealloc];
}
@end






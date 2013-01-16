//
//  AMHomepageDressResult.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressResult.h"

@implementation AMHomepageDressResult
@synthesize bannersios = _bannersios;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            //因为单例的缘故所以必须要retain住
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressResult class]] retain];
//            sharedObjectMapping = [RKObjectMapping mappingForClass:[AMHomepageDressResult class]];
            
			[sharedObjectMapping mapRelationship:@"bannersios" withMapping:[AMHomepageDressBanner sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHomepageDressBanner sharedObjectMapping] forKeyPath:@"bannersios"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_bannersios release];
    
    [super dealloc];
}
@end





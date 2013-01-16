//
//  AMHomepageDressEvent3Result.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressEvent3Result.h"

@implementation AMHomepageDressEvent3Result
@synthesize event3 = _event3;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressEvent3Result class]] retain];
            
			[sharedObjectMapping mapRelationship:@"event3" withMapping:[AMHomepageDressEvent1 sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHomepageDressEvent1 sharedObjectMapping] forKeyPath:@"event3"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_event3 release];
    
    [super dealloc];
}
@end


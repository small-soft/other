//
//  AMHomepageDressEvent2Result.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressEvent2Result.h"

@implementation AMHomepageDressEvent2Result
@synthesize event2 = _event2;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressEvent2Result class]] retain];
            
			[sharedObjectMapping mapRelationship:@"event2" withMapping:[AMHomepageDressEvent1 sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHomepageDressEvent1 sharedObjectMapping] forKeyPath:@"event2"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_event2 release];
    
    [super dealloc];
}
@end


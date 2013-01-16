//
//  AMHomepageDressEvent1Result.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressEvent1Result.h"

@implementation AMHomepageDressEvent1Result
@synthesize event1ios = _event1ios;
@synthesize event2ios = _event2ios;
@synthesize event3ios = _event3ios;
@synthesize price = _price;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressEvent1Result class]] retain];
            
			[sharedObjectMapping mapRelationship:@"event1ios" withMapping:[AMHomepageDressEvent1 sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHomepageDressEvent1 sharedObjectMapping] forKeyPath:@"event1ios"];
            
            // Setup object mapping
            [sharedObjectMapping mapRelationship:@"event2ios" withMapping:[AMHomepageDressEvent1 sharedObjectMapping]];
            [mappingProvider setMapping:[AMHomepageDressEvent1 sharedObjectMapping] forKeyPath:@"event2ios"];
            
            // Setup object mapping
            [sharedObjectMapping mapRelationship:@"event3ios" withMapping:[AMHomepageDressEvent1 sharedObjectMapping]];
			[mappingProvider setMapping:[AMHomepageDressEvent1 sharedObjectMapping] forKeyPath:@"event3ios"];
            
            // Setup object mapping
            [sharedObjectMapping mapRelationship:@"price" withMapping:[AMHomepageDressEvent1 sharedObjectMapping]];
			[mappingProvider setMapping:[AMHomepageDressEvent1 sharedObjectMapping] forKeyPath:@"price"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_event1ios release];
    [_event2ios release];
    [_event3ios release];
    [_price release];
    
    [super dealloc];
}
@end

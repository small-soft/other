//
//  AMPrecisionVisitorListResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitorListResult.h"
#import "AMPrecisionVisitor.h"
#import <RestKit/RestKit.h>


@implementation AMPrecisionVisitorListResult

@synthesize total = _total;
@synthesize allVisitor = _allVisitor;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionVisitorListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];

			[sharedObjectMapping mapRelationship:@"allVisitor" withMapping:[AMPrecisionVisitor sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMPrecisionVisitor sharedObjectMapping] forKeyPath:@"allVisitor"];
        }
    }
    return sharedObjectMapping;
}

- (void) dealloc {
    [_total release];
    [_allVisitor release];
    [super dealloc];
}

@end

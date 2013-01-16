//
//  AMPrecisionVisitorListResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitorStatusResult.h"
#import <RestKit/RestKit.h>


@implementation AMPrecisionVisitorStatusResult

@synthesize handShake = _handShake;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionVisitorStatusResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"handShake" toAttribute:@"handShake"];
        }
    }
    return sharedObjectMapping;
}

- (void) dealloc {
    [_handShake release];
    [super dealloc];
}

@end
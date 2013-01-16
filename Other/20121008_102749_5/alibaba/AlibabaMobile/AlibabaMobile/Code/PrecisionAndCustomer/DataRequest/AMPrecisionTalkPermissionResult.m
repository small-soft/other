//
//  AMPrecisionTalkPermissionResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionTalkPermissionResult.h"
#import <RestKit/RestKit.h>


@implementation AMPrecisionTalkPermissionResult

@synthesize hasPermissionUsed = _hasPermissionUsed;
@synthesize talked = _talked;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionTalkPermissionResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"hasPermissionUsed" toAttribute:@"hasPermissionUsed"];
   			[sharedObjectMapping mapKeyPath:@"talked" toAttribute:@"talked"];
        }
    }
    return sharedObjectMapping;
}

- (void) dealloc {
    [_hasPermissionUsed release];
    [_talked release];
    [super dealloc];
}

@end
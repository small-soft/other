//
//  AMPrecisionSaveFreeUserResResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionSaveFreeUserResResult.h"
#import <RestKit/RestKit.h>


@implementation AMPrecisionSaveFreeUserResResult

@synthesize rspResult = _rspResult;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionSaveFreeUserResResult class]] retain];
   			[sharedObjectMapping mapKeyPath:@"result" toAttribute:@"rspResult"];
        }
    }
    return sharedObjectMapping;
}

- (void) dealloc {
    [_rspResult release];
    [super dealloc];
}

@end
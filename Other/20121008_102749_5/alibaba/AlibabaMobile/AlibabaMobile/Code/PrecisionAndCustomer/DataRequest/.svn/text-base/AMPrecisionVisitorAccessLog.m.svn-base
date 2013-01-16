//
//  AMPrecisionVisitorAccessLog.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitorAccessLog.h"
#import "AMPrecisionVisitorAccessLogDetail.h"

@implementation AMPrecisionVisitorAccessLog

@synthesize time = _time;
@synthesize logList = _logList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionVisitorAccessLog class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"time" toAttribute:@"time"];
            
            [sharedObjectMapping mapRelationship:@"logList" withMapping:[AMPrecisionVisitorAccessLogDetail sharedObjectMapping]];
            
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMPrecisionVisitorAccessLogDetail sharedObjectMapping] forKeyPath:@"logList"];
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_time release];
    [_logList release];
    
    [super dealloc];
}

@end

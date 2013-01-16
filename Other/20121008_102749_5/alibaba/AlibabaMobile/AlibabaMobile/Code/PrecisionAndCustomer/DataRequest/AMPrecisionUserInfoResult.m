//
//  AMPrecisionUserInfoResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionUserInfoResult.h"
#import <RestKit/RestKit.h>

@implementation AMPrecisionUserInfoResult

@synthesize siteId = _siteId;
@synthesize userType = _userType;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionUserInfoResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"siteId" toAttribute:@"siteId"];
			[sharedObjectMapping mapKeyPath:@"userType" toAttribute:@"userType"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString *) description {
    return [NSString stringWithFormat:@"siteId = %@, userType = %@", _siteId, _userType];
}

- (void) dealloc {
    [_siteId release];
    [_userType release];
    [super dealloc];
}

@end

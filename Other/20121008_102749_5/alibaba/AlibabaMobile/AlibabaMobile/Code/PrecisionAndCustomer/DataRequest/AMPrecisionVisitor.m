//
//  AMCustomerMyVisitorResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitor.h"

#import "AMFavoriteOffer.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMPrecisionVisitor

@synthesize gmtAccess = _gmtAccess;
@synthesize showName = _showName;
@synthesize visitorId = _visitorId;
@synthesize handShake = _handShake;
@synthesize current = _current;
@synthesize aliimId = _aliimId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionVisitor class]] retain];
			[sharedObjectMapping mapKeyPath:@"gmtAccess" toAttribute:@"gmtAccess"];
			[sharedObjectMapping mapKeyPath:@"showName" toAttribute:@"showName"];
			[sharedObjectMapping mapKeyPath:@"visitorId" toAttribute:@"visitorId"];
  			[sharedObjectMapping mapKeyPath:@"handShake" toAttribute:@"handShake"];
   			[sharedObjectMapping mapKeyPath:@"current" toAttribute:@"current"];
  			[sharedObjectMapping mapKeyPath:@"aliimId" toAttribute:@"aliimId"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_gmtAccess release];
    [_showName release];
    [_visitorId release];
    [_handShake release];
    [_current release];
    [_aliimId release];
    [super dealloc];
}

@end
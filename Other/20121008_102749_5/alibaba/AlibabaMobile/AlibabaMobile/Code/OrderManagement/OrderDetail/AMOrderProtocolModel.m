//
//  AMOrderProtocolModel.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderProtocolModel.h"

@implementation AMOrderProtocolModel

@synthesize ensurePayment;
@synthesize gmtDeadline;

-(void) dealloc
{
    [gmtDeadline release];
    gmtDeadline = nil;
    
    [super dealloc];
    
}

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderProtocolModel class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"ensurePayment" toAttribute:@"ensurePayment"];
            [sharedObjectMapping mapKeyPath:@"gmtDeadline" toAttribute:@"gmtDeadline"];
        }
    }
    
    return sharedObjectMapping;
}

@end

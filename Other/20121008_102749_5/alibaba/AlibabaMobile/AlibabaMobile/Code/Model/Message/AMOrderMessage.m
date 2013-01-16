//
//  AMOrderMessage.m
//  AlibabaMobile
//
//  Created by  on 12-10-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderMessage.h"

@implementation AMOrderMessage
@synthesize orderId = _orderId;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderMessage class]] retain];
            [sharedObjectMapping mapKeyPath:@"orderId" toAttribute:@"orderId"];
        }
    }
    
    return sharedObjectMapping;
}


- (void)dealloc
{
    [_orderId release];
    [super dealloc];
}


@end

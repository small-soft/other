//
//  AMCustomerMyCustomerGroupModel.m
//  AlibabaMobile
//
//  Created by xiaowen on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerMyCustomerGroupModel.h"

@implementation AMCustomerMyCustomerGroupModel

@synthesize identifier = _identifier;
@synthesize count = _count;
@synthesize value = _value;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerMyCustomerGroupModel class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"count" toAttribute:@"count"];
			[sharedObjectMapping mapKeyPath:@"value" toAttribute:@"value"];
       }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
    
    [_identifier release];
    [_count release];
    [_value release];

    [super dealloc];
}
@end




//
//  AMCustomerSuggestAddResult.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerSuggestAddResult.h"
#import <RestKit/RestKit.h>


@implementation AMCustomerSuggestAddResult

@synthesize success = _success;
@synthesize resultCode = _resultCode;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerSuggestAddResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
			[sharedObjectMapping mapKeyPath:@"resultCode" toAttribute:@"resultCode"];
        }
    }
    return sharedObjectMapping;
}

- (void) dealloc {
    [_success release];
    [_resultCode release];
    [super dealloc];
}

@end
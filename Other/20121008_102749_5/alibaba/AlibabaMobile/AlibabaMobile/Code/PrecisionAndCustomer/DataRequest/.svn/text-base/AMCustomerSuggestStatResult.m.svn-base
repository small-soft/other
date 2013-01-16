//
//  AMCustomerSuggestListMainModel.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerSuggestStatResult.h"

#import <RestKit/RestKit.h>
#import "AMCustomerImage.h"

@implementation AMCustomerSuggestStatResult

@synthesize unPotentialEnquiryCount = _unPotentialEnquiryCount;
@synthesize freeHavedImported = _freeHavedImported;
@synthesize potentialEnquiryCount= _potentialEnquiryCount;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerSuggestStatResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"unPotentialEnquiryCount" toAttribute:@"unPotentialEnquiryCount"];
            [sharedObjectMapping mapKeyPath:@"freeHavedImported" toAttribute:@"freeHavedImported"];
            [sharedObjectMapping mapKeyPath:@"potentialEnquiryCount" toAttribute:@"potentialEnquiryCount"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_unPotentialEnquiryCount release];
    [_freeHavedImported release];
    [_potentialEnquiryCount release];
    [super dealloc];
}

@end

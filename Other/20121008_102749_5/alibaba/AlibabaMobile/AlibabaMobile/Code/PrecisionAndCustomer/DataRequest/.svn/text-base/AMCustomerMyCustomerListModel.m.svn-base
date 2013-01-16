//
//  AMCustomerList.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerMyCustomerListModel.h"
#import "AMCustomerMyCustomerModel.h"

@implementation AMCustomerMyCustomerListModel

@synthesize lastEnquiryTime=_lastEnquiryTime;
@synthesize limited=_limited;
@synthesize enquiryTotalTimes=_enquiryTotalTimes;
@synthesize strLastEnquiryTime=_strLastEnquiryTime;
@synthesize customer=_customer;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerMyCustomerListModel class]] retain];
			[sharedObjectMapping mapKeyPath:@"lastEnquiryTime" toAttribute:@"lastEnquiryTime"];
			[sharedObjectMapping mapKeyPath:@"limited" toAttribute:@"limited"];
			[sharedObjectMapping mapKeyPath:@"enquiryTotalTimes" toAttribute:@"enquiryTotalTimes"];
			[sharedObjectMapping mapKeyPath:@"strLastEnquiryTime" toAttribute:@"strLastEnquiryTime"];

			[sharedObjectMapping mapRelationship:@"customer" withMapping: [AMCustomerMyCustomerModel sharedObjectMapping]];
            
     
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCustomerMyCustomerModel sharedObjectMapping] forKeyPath:@"customer"];
            
       }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
    
    [_lastEnquiryTime release];
    [_limited release];
    [_enquiryTotalTimes release];
    [_strLastEnquiryTime release];
    [_customer release];

    [super dealloc];
}
@end




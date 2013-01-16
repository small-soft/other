//
//  AMCustomerInfoResult.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerInfoResult.h"
#import "AMEnqueryItem.h"

@implementation AMCustomerInfoResult



@synthesize success =_success;
@synthesize enquiryTotalTimes=_enquiryTotalTimes;
@synthesize returnObject=_returnObject;
@synthesize enquriesList=_enquriesList;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerInfoResult class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
            [sharedObjectMapping mapKeyPath:@"enquiryTotalTimes" toAttribute:@"enquiryTotalTimes"];

			
            
            [sharedObjectMapping mapRelationship:@"enquriesList" withMapping:[AMEnqueryItem sharedObjectMapping]];
            
            [sharedObjectMapping mapRelationship:@"returnObject" withMapping:[AMCustomerInfo sharedObjectMapping]];
            
//            			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMEnqueryItem sharedObjectMapping] forKeyPath:@"enquriesList"];
			[mappingProvider setMapping:[AMCustomerInfo sharedObjectMapping] forKeyPath:@"returnObject"];
            
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
//    [_ctrIds release];
//    [_recId release];
//    [_offerList release];
    
    [super dealloc];
}

@end

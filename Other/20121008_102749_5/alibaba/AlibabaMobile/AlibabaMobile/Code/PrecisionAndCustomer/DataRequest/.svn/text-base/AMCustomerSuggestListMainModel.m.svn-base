//
//  AMCustomerSuggestListMainModel.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerSuggestListMainModel.h"

#import <RestKit/RestKit.h>
#import "AMCustomerImage.h"

@implementation AMCustomerSuggestListMainModel

@synthesize name = _name;
@synthesize province = _province;
@synthesize mainBiz = _mainBiz;
@synthesize interestInfo = _interestInfo;
@synthesize visitDate = _visitDate;
@synthesize intent = _intent;
@synthesize buyItems = _buyItems;
@synthesize overdueDays = _overdueDays;
@synthesize headImage = _headImage;
@synthesize customerMemberId = _customerMemberId;
@synthesize leadsId = _leadsId;
@synthesize status = _status;



+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerSuggestListMainModel class]] retain];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];
            [sharedObjectMapping mapKeyPath:@"mainBiz" toAttribute:@"mainBiz"];
            [sharedObjectMapping mapKeyPath:@"interestInfo" toAttribute:@"interestInfo"];
            [sharedObjectMapping mapKeyPath:@"visitDate" toAttribute:@"visitDate"];
            [sharedObjectMapping mapKeyPath:@"intent" toAttribute:@"intent"];
            [sharedObjectMapping mapKeyPath:@"buyItems" toAttribute:@"buyItems"];
            [sharedObjectMapping mapKeyPath:@"overdueDays" toAttribute:@"overdueDays"];
            [sharedObjectMapping mapKeyPath:@"customerMemberId" toAttribute:@"customerMemberId"];
            [sharedObjectMapping mapKeyPath:@"leadsId" toAttribute:@"leadsId"];
            [sharedObjectMapping mapKeyPath:@"status" toAttribute:@"status"];
            
			[sharedObjectMapping mapRelationship:@"headImage" withMapping:[AMCustomerImage sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCustomerImage sharedObjectMapping] forKeyPath:@"headImage"];
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_name release];
    [_province release];
    [_mainBiz release];
    [_interestInfo release];
    [_visitDate release];
    [_intent release];
    [_buyItems release];
    [_overdueDays release];
    [_headImage release];
    [_customerMemberId release];
    [_status release];
    [super dealloc];
}

@end

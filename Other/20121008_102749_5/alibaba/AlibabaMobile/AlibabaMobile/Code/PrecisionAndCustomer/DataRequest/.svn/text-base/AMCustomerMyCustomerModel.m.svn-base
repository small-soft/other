//
//  AMCustomer.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerMyCustomerModel.h"

@implementation AMCustomerMyCustomerModel

@synthesize city=_city;
@synthesize corpName=_corpName;
@synthesize phoneNumber=_phoneNumber;
@synthesize province=_province;
@synthesize jobTitle=_jobTitle;
@synthesize buyerId=_buyerId;
@synthesize buyerName=_buyerName;
@synthesize memberId=_memberId;
@synthesize mobile=_mobile;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerMyCustomerModel class]] retain];
			[sharedObjectMapping mapKeyPath:@"city" toAttribute:@"city"];
			[sharedObjectMapping mapKeyPath:@"corpName" toAttribute:@"corpName"];
			[sharedObjectMapping mapKeyPath:@"phoneNumber" toAttribute:@"phoneNumber"];
			[sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];
			[sharedObjectMapping mapKeyPath:@"jobTitle" toAttribute:@"jobTitle"];
            [sharedObjectMapping mapKeyPath:@"buyerId" toAttribute:@"buyerId"];
            [sharedObjectMapping mapKeyPath:@"buyerName" toAttribute:@"buyerName"];
            [sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
            [sharedObjectMapping mapKeyPath:@"mobile" toAttribute:@"mobile"];
			
			
			
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
    
    [_city release];
    [_corpName release];
    [_phoneNumber release];
    [_province release];
    [_jobTitle release];
    [_buyerId release];
    [_buyerName release];
    [_memberId release];
    [_mobile release];
    
    [super dealloc];
}
@end

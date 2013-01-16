//
//  CustomerInfo.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCustomerInfo.h"

@implementation AMCustomerInfo

@synthesize  city=_city;
@synthesize  corpName=_corpName;
@synthesize  phoneNumber=_phoneNumber;
@synthesize province=_province;
@synthesize  gender=_gender;

@synthesize  longitude=_longitude;
@synthesize  jobTitle=_jobTitle;
@synthesize  buyerId=_buyerId;
@synthesize  buyerName=_buyerName;
@synthesize  country=_country;

@synthesize  address=_address;
@synthesize  email=_email;
@synthesize  memberId=_memberId;
@synthesize  latitude=_latitude;
@synthesize  phoneArea=_phoneArea;

@synthesize  phoneCountry=_phoneCountry;
@synthesize  mobile=_mobile;


@synthesize  saleKeywords=_saleKeywords;
@synthesize  faxCountry=_faxCountry;
@synthesize  faxArea=_faxArea;
@synthesize  faxNumber=_faxNumber;
@synthesize  postalCode=_postalCode;
@synthesize  groupId=_groupId;
@synthesize  groupName=_groupName;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerInfo class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"city" toAttribute:@"city"];
            [sharedObjectMapping mapKeyPath:@"corpName" toAttribute:@"corpName"];
            [sharedObjectMapping mapKeyPath:@"phoneNumber" toAttribute:@"phoneNumber"];
            [sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];
            [sharedObjectMapping mapKeyPath:@"gender" toAttribute:@"gender"];
            [sharedObjectMapping mapKeyPath:@"longitude" toAttribute:@"longitude"];
            [sharedObjectMapping mapKeyPath:@"jobTitle" toAttribute:@"jobTitle"];
            [sharedObjectMapping mapKeyPath:@"buyerId" toAttribute:@"buyerId"];
            [sharedObjectMapping mapKeyPath:@"buyerName" toAttribute:@"buyerName"];
            [sharedObjectMapping mapKeyPath:@"country" toAttribute:@"country"];
            [sharedObjectMapping mapKeyPath:@"address" toAttribute:@"address"];
            [sharedObjectMapping mapKeyPath:@"email" toAttribute:@"email"];
            [sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
            [sharedObjectMapping mapKeyPath:@"latitude" toAttribute:@"latitude"];
            [sharedObjectMapping mapKeyPath:@"phoneArea" toAttribute:@"phoneArea"];
            [sharedObjectMapping mapKeyPath:@"phoneCountry" toAttribute:@"phoneCountry"];
            [sharedObjectMapping mapKeyPath:@"mobile" toAttribute:@"mobile"];
            
            [sharedObjectMapping mapKeyPath:@"saleKeywords" toAttribute:@"saleKeywords"];
            [sharedObjectMapping mapKeyPath:@"faxCountry" toAttribute:@"faxCountry"];
            [sharedObjectMapping mapKeyPath:@"faxArea" toAttribute:@"faxArea"];
            [sharedObjectMapping mapKeyPath:@"faxNumber" toAttribute:@"faxNumber"];
            [sharedObjectMapping mapKeyPath:@"postalCode" toAttribute:@"postalCode"];
            [sharedObjectMapping mapKeyPath:@"groupId" toAttribute:@"groupId"];
            [sharedObjectMapping mapKeyPath:@"groupName" toAttribute:@"groupName"];
//            
//			[sharedObjectMapping mapRelationship:@"returnObject" withMapping:[CustomerInfo sharedObjectMapping]];
//            
//            [sharedObjectMapping mapRelationship:@"enquriesList" withMapping:[CustomerInfo sharedObjectMapping]];
//            
//            //            			
//			// Setup object mapping
//			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//			[mappingProvider setMapping:[CustomerInfo sharedObjectMapping] forKeyPath:@"returnObject"];
//            
//            [mappingProvider setMapping:[CustomerInfo sharedObjectMapping] forKeyPath:@"enquriesList"];
        }
    }
    
    return sharedObjectMapping;
}
@end

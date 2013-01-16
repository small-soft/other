//
//  CustomerInfo.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCustomerInfo : NSObject<AMObjectMappingDelegate>{
    NSString * _city;
    NSString * _corpName;
    NSString * _phoneNumber;
    NSString * _province;
    NSString * _gender;
    
    NSString * _longitude;
    NSString * _jobTitle;
    NSString * _buyerId;
    NSString * _buyerName;
    NSString * _country;
    
    NSString * _address;
    NSString * _email;
    NSString * _memberId;
    NSString * _latitude;
    NSString * _phoneArea;
    
    NSString * _phoneCountry;
    NSString * _mobile;
    
    NSString * _saleKeywords;
    NSString * _faxCountry;
    NSString * _faxArea;
    NSString * _faxNumber;
    NSString * _postalCode;
    NSString * _groupId;
    NSString * _groupName;
    
    
}

 



@property(nonatomic, retain) NSString * city;
@property(nonatomic, retain) NSString * corpName;
@property(nonatomic, retain) NSString * phoneNumber;
@property(nonatomic, retain) NSString * province;
@property(nonatomic, retain) NSString * gender;

@property(nonatomic, retain) NSString * longitude;
@property(nonatomic, retain) NSString * jobTitle;
@property(nonatomic, retain) NSString * buyerId;
@property(nonatomic, retain) NSString * buyerName;
@property(nonatomic, retain) NSString * country;

@property(nonatomic, retain) NSString * address;
@property(nonatomic, retain) NSString * email;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * latitude;
@property(nonatomic, retain) NSString * phoneArea;

@property(nonatomic, retain) NSString * phoneCountry;
@property(nonatomic, retain) NSString * mobile;


@property(nonatomic, retain) NSString * saleKeywords;
@property(nonatomic, retain) NSString * faxCountry;
@property(nonatomic, retain) NSString * faxArea;
@property(nonatomic, retain) NSString * faxNumber;
@property(nonatomic, retain) NSString * postalCode;
@property(nonatomic, retain) NSString * groupId;
@property(nonatomic, retain) NSString * groupName;



@end

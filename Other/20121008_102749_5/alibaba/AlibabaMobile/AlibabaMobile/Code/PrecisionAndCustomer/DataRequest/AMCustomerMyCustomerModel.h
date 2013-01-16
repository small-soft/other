//
//  AMCustomer.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AMObjectMappingDelegate.h"

@interface AMCustomerMyCustomerModel : NSObject <AMObjectMappingDelegate> {
    NSString * _city;
    NSString *_corpName;
    NSString * _phoneNumber;
    NSString * _province;
    NSString * _jobTitle;
    NSString * _buyerId;
    NSString * _buyerName;
    NSString * _memberId;
    NSString * _mobile;
}

@property(nonatomic, retain) NSString *city;
@property(nonatomic, retain) NSString *corpName;
@property(nonatomic, retain) NSString * phoneNumber;
@property(nonatomic, retain) NSString * province;
@property(nonatomic, retain) NSString * jobTitle;
@property(nonatomic, retain) NSString * buyerId;
@property(nonatomic, retain) NSString * buyerName;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * mobile;


@end

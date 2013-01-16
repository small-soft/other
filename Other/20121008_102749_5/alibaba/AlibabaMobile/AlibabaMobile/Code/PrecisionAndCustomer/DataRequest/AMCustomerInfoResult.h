//
//  AMCustomerInfoResult.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMObjectMappingDelegate.h"
//#import "AMCustomerList.h"


#import "AMCustomerInfo.h"

@interface AMCustomerInfoResult : NSObject <AMObjectMappingDelegate> {
    
    
    NSString * _success;
    NSNumber *_enquiryTotalTimes;
    AMCustomerInfo *_returnObject;
    NSArray * _enquriesList;

    
}


@property(nonatomic, retain)  NSString * success;
@property(nonatomic, retain)  NSNumber * enquiryTotalTimes;
@property(nonatomic, retain)  AMCustomerInfo *returnObject;
@property(nonatomic, retain)  NSArray * enquriesList;

@end

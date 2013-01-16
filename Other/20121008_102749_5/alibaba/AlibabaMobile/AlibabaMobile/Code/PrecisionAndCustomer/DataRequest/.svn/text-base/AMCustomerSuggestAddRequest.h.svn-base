//
//  AMCustomerSuggestAddRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_CUSTOMER_SUGGEST_ADD ([@"/customer.addCustomer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCustomerSuggestAddRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {
}

@property (nonatomic, retain) NSString *customerMemberId;
@property (nonatomic, retain) NSString *leadsId;

@property (nonatomic, retain) NSDictionary  *request;

@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;

@end

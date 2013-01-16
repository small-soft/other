//
//  AMCustomerSuggestStatRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/customer.getLeadsStat/5005?_aop_signature=5E0E11E8E887DA1112056F96C916572F885DAB7B&access_token=bcd81818-11df-429c-b14e-1c6cbb9d6668&targetId=53&_data_=%7B%7D&clickId=11&clickUUID=32528011-aed8-408c-a363-999979ccbbcf&deviceId=d01f62eb7d83d52ff54e48fcf72c41c1&pageId=50

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_CUSTOMER_SUGGEST_STAT ([@"/customer.getLeadsStat/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCustomerSuggestStatRequest : NSObject <RKRequestSerializable, AMRequestDelegate>{
    
}

@property (nonatomic, retain) NSString *requestURL;
@property (nonatomic) NSInteger transactionType;
@end

//
//  AMPrecisionUserInfoRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_PRECISION_GET_USERINFO ([@"/itrade.getUserInfo/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMPrecisionUserInfoRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {

}

@property (nonatomic, retain) NSString *memberId;

@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;

@end

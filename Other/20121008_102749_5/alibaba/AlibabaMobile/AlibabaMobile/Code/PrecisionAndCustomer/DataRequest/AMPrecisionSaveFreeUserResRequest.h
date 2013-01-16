//
//  AMPrecisionSaveFreeUserResRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_PRECISION_SAVE_FREE_USER_RES ([@"/itrade.saveFreeUseRes/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMPrecisionSaveFreeUserResRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {
}

@property (nonatomic, retain) NSString *siteId;
@property (nonatomic, retain) NSString *visitorId;

@property (nonatomic, retain) NSDictionary  *request;

@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;

@end

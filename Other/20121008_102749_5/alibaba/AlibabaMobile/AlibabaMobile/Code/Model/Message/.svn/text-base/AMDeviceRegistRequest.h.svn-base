//
//  AMDeviceRegistRequest.h
//  AlibabaMobile
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_DEVICE_REGIST ([@"/ops.appdata.processTerminalAndAppInfo/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMDeviceRegistRequest : NSObject<RKRequestSerializable, AMRequestDelegate>


@property (nonatomic, assign) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;

@property (nonatomic, retain) NSString * terminateId;
@property (nonatomic, retain) NSString * model;
@property (nonatomic, retain) NSString * system;
@property (nonatomic, retain) NSString * version ;
@property (nonatomic, retain) NSString * deviceTokenStr;
@property (nonatomic, retain) NSString * appId;
@property (nonatomic, retain) NSString * appVersion;
@property (nonatomic, retain) NSString * currentUserId;
@property (nonatomic, retain) NSString * downloadChannel;

@end

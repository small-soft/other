//
//  AMVersionCheckRequest.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_UPDATE_REQUEST_URL ([@"/feedback.getMyUpdateInfo/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMVersionCheckRequest : NSObject<RKRequestSerializable> 

@property (nonatomic, retain) NSString *myPlatform;
@property (nonatomic, retain) NSString *myVersion;
@property (nonatomic, retain) NSString *myDeviceId;

@end

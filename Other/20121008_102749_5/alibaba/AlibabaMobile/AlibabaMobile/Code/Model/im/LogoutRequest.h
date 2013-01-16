//
//  LogoutRequest.h
//  AlibabaMobile
//
//  Created by lih on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_LOGOUT ([@"/ops.appdata.onUserLogout/" stringByAppendingString:AMCONST_APP_KEY])

@interface LogoutRequest : NSObject<RKRequestSerializable> {
    NSString * _terminalId;
    NSString * _appId;
}

@property(nonatomic, retain) NSString * terminalId;
@property(nonatomic, retain) NSString * appId;
@property (nonatomic, retain) NSString *accessToken;
@property (nonatomic, retain) NSString *requestURL;

@end
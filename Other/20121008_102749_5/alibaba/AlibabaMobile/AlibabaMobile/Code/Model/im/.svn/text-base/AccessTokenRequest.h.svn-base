//
//  AccessTokenRequest.h
//  AlibabaMobile
//
//  Created by lih on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_GET_ACCESSTOKEN ([@"/getAccessToken/" stringByAppendingString:AMCONST_APP_KEY])

@interface AccessTokenRequest : NSObject <RKRequestSerializable> {
    
    NSString * _refreshToken;    
}

@property(nonatomic, retain) NSString * refreshToken;

@end

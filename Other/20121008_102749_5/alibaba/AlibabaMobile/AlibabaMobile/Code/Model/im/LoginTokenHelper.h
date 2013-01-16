//
//  LoginTokenHelper.h
//  AlibabaMobile
//
//  Created by lih on 12-3-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import "AccessTokenRequest.h"
#import "AccessTokenResult.h"

@class LoginTokenHelper;
@protocol  LoginTokenHelperDelegate<NSObject>

@required
-(void)loginTokenHelperDidUpdateAccessToken;

@end

@interface LoginTokenHelper : NSObject <RKObjectLoaderDelegate>

@property (nonatomic, assign)id<LoginTokenHelperDelegate> delegate;
@property (nonatomic, retain)AccessTokenRequest *accessTokenRequest;
@property (nonatomic, retain)AccessTokenResult  *object;

+ (id)sharedTokenHelper;
-(void) updateAccessToken;

@end


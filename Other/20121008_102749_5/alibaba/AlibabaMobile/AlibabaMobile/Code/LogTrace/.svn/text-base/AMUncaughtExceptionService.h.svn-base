//
//  AMUncaugthExceptionService.h
//  AlibabaMobile
//
//  Created by  on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import "AMUncaughtExceptionRequest.h"

@interface AMUncaughtExceptionService : NSObject<RKObjectLoaderDelegate> {
    AMUncaughtExceptionRequest *_request;
}

+ (AMUncaughtExceptionService *)instance;
+ (void) destroy;

+ (void) catchException:(NSException *)exception;
+ (void) setDefaultHandler;
+ (NSUncaughtExceptionHandler*) getHandler;
@property (nonatomic, assign) NSUInteger count;
@end

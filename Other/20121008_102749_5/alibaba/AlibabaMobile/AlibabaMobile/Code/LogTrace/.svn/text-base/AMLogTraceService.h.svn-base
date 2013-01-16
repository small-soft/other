//
//  AMLogTraceService.h
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AMLogRequest.h"

@interface AMLogTraceService : NSObject <RKObjectLoaderDelegate> {
    NSRunLoop *logRunLoop;
    AMLogRequest *_request;
}

@property (nonatomic, retain) AMLogRequest * request;

- (void) startLogService;
- (void) stopLogService;

@end

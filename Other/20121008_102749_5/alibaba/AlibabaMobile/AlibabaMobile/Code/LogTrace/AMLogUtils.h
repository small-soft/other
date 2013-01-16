//
//  AMLogUtils.h
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 12-3-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMLogTypeCode.h"

@interface AMLogUtils : NSObject {
}

+ (NSString *) getLogType;
+ (void) setLogType: (NSString *)type;
+ (void) appendLog: (NSString *)type;
+ (NSDictionary *) getLogHeader;
+ (void)appendLogTraceToHTTPRequest:(NSMutableDictionary *)params;

@end

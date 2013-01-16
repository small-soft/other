//
//  AMLogUtils.m
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 12-3-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMLogUtils.h"
#import "Utils.h"
#import "LoginToken.h"
#import "AMIMCoreDataHelper.h"
#import <Foundation/Foundation.h>
#import "ConstDef.h"
#import "AMTerminalLog.h"

#define AMKEY_LOG_TYPE  @"AMLogType"

@implementation AMLogUtils

+ (NSString *)getLogType {
    // First get type from Thread-local storage
    NSMutableDictionary *md = [[NSThread currentThread] threadDictionary];
    if (md != nil) {
        return [md objectForKey:AMKEY_LOG_TYPE];
    }
    
    return nil;
}

+ (void)setLogType: (NSString *)type {
    // Set type to  Thread-local storage
    NSMutableDictionary *md = [[NSThread currentThread] threadDictionary];
    if (md != nil && type != nil) {
        [md setObject:type forKey:AMKEY_LOG_TYPE];
    } else if (md != nil) {
        [md removeObjectForKey:AMKEY_LOG_TYPE];
    }
    
    NSLog(@"AMLogUtils: log type [%@] is set!", type);
}

+ (void)appendLog: (NSString *)type {
    NSString * identifiedType = [NSString stringWithFormat:@"%@[%@]",type, [Utils createUUID]];
    [[AMIMCoreDataHelper getInstance] appendLog: identifiedType];
    [AMLogUtils setLogType:identifiedType];
}

+ (NSDictionary *) getLogHeader {
    NSMutableDictionary *header = [[[NSMutableDictionary alloc] init] autorelease];
    
    NSString *versionCode = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    [header setObject: [NSString stringWithString:AMCONST_APP_ID] forKey:@"appId"];
    [header setObject: [NSString stringWithFormat:@"%@:%@", AMCONST_APP_ID, versionCode] forKey:@"appVersion"];
    [header setObject: [NSNumber numberWithInteger:AMVERSION_IPHONE] forKey:@"versionType"];
    if ([LoginToken getLoginUserName]) {
        [header setObject: [LoginToken getLoginUserName] forKey:@"userId"];
    }
    [header setObject: [[UIDevice currentDevice] localizedModel] forKey:@"model"];
    [header setObject: [[[UIDevice currentDevice] systemName] stringByAppendingString:[[UIDevice currentDevice] systemVersion]] forKey:@"osVersion"];
    [header setObject: [NSNumber numberWithInt:640] forKey:@"screenWidth"];
    [header setObject: [NSNumber numberWithInt:960] forKey:@"screenHeight"];
    [header setObject: [NSString stringWithFormat:@"%@",[NSNumber numberWithLong:[[NSDate date] timeIntervalSince1970]]] forKey:@"postTime"];
    [header setObject:[[UIDevice currentDevice] uniqueIdentifier] forKey:@"id"];
//    for (NSString* key in [header allKeys]) {
//        NSLog(@"header key = %@ object = %@",key,[header objectForKey:key]);
//    }
    return header;
}

+ (void)appendLogTraceToHTTPRequest:(NSMutableDictionary *)params {
    NSString *type = [AMLogUtils getLogType];

    if (type != nil) {
        NSRange rangeStart = [type rangeOfString:@"["];
        int locationStart = rangeStart.location;
        //int leightStart = rangeStart.length;
        NSRange rangeEnd = [type rangeOfString:@"]"];
        int locationEnd = rangeEnd.location;
        //int leightEnd = rangeEnd.length;
        
        NSRange range = NSMakeRange(locationStart + 1, locationEnd - locationStart - 1);
        NSString *uuid = [type substringWithRange: range];
        NSString *typeWithoutUUID = [type substringToIndex:locationStart];
        
        NSString *targetID = nil;
        NSArray *typeComponents = [typeWithoutUUID componentsSeparatedByString:@"-"];
        if (typeComponents != nil && [typeComponents count] == 3) {
            targetID = [typeComponents objectAtIndex:1];
        } else if(typeComponents != nil && [typeComponents count] == 4) {
            targetID = [typeComponents objectAtIndex:3];
        }
        
        if (typeComponents != nil && [typeComponents count] >= 3) {
            [params setObject:[typeComponents objectAtIndex:1] forKey:@"pageId"];
            [params setObject:[typeComponents objectAtIndex:2] forKey:@"clickId"];
            [params setObject:targetID forKey:@"targetId"];
        }
        
        [params setObject:uuid forKey:@"clickUUID"];
        [params setObject:[[UIDevice currentDevice] uniqueIdentifier] forKey:@"deviceId"];
    }
    
    [AMLogUtils setLogType:nil];
}


@end

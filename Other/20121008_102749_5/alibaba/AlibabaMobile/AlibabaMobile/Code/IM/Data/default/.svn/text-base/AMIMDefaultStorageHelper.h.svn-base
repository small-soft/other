//
//  AMIMDefaultStorageHelper.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-19.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>

@class  AMIMUserDefault;

@interface AMIMDefaultStorageHelper : NSObject


+ (AMIMUserDefault * )getLoginedUser:(NSString *)uid;
+ (AMIMUserDefault * )getLoginedUserWithIndex:(int)index;
+ (void) deleteUserWithIndex:(int)index;
+ (void) deleteUser:(NSString *)uid;
+(int) getLoginedUserNum;
+ (BOOL) hasLoginedUser;
+ (NSString *) getLastLoginedUserId;
+ (AMIMUserDefault *) getLastLoginedUser;
+ (void) changeLastLoginedUser:(NSString *)uid;
+ (NSMutableArray *) getLoginedUserList;
+ (void) addLoginedUser:(AMIMUserDefault *) user;
+ (void) changeSelfState:(int)state;
+ (void) changeSelfGroupState:(BOOL)groupState friendState:(BOOL)friendState blackState:(BOOL)blackState;
+ (void) changeSelfGroupTimestamp:(int)timestamp;
+ (void) changeSelfFriendTimestamp:(int)timestamp ;
+ (void) changeSelfBlackTimestamp:(int)timestamp ;
+(void)changeSelfNotickWithMusic:(bool)music shake:(bool)shake;

@end

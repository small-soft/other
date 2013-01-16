//
//  AMIMDefaultStorageHelper.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-19.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>
#import "AMIMDefaultStorageHelper.h"
#import "AMIMUserDefault.h"

#define IM_DEFAULT_DATA_ACCOUNT_INFO @"accountInfoListDict"
#define IM_DEFAULT_DATA_LAST_LOGINED_USER @"lastLoginedUser"
#define IM_DEFAULT_DATA_LOGINED_USER_LIST @"loginedUserList"


@implementation AMIMDefaultStorageHelper

+ (void) deleteUserWithIndex:(int)index
{
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    if(userList != nil && userList.count >index){
        [userList removeObjectAtIndex:index];
    }
    
    [accountInfoDict setValue:userList forKey:IM_DEFAULT_DATA_LOGINED_USER_LIST];
    [[NSUserDefaults standardUserDefaults] setValue:accountInfoDict forKey:IM_DEFAULT_DATA_ACCOUNT_INFO];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (void) deleteUser:(NSString *)uid
{
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    if(userList != nil && userList.count >0){
        int size = userList.count;
        for(int i=0; i<size; i++){
            if([((AMIMUserDefault *)[NSKeyedUnarchiver unarchiveObjectWithData:[userList objectAtIndex:i]]).uid isEqualToString:uid]){
                [userList removeObjectAtIndex:i];
                break;
            }
        }
    }
    
    [accountInfoDict setValue:userList forKey:IM_DEFAULT_DATA_LOGINED_USER_LIST];
    [[NSUserDefaults standardUserDefaults] setValue:accountInfoDict forKey:IM_DEFAULT_DATA_ACCOUNT_INFO];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
}

+(int) getLoginedUserNum
{
    
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    
    if(userList != nil && userList.count >0){
        return userList.count;
    }else{
        return 0;
    }

}

+ (BOOL) hasLoginedUser
{
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    
    if(userList != nil && userList.count >0){
        return YES;
    }else{
        return NO;
    }
    
}

+ (NSString *) getLastLoginedUserId
{
    
	NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSString * lastLoginedUser = (NSString *)[accountInfoDict objectForKey:IM_DEFAULT_DATA_LAST_LOGINED_USER];
   
    return lastLoginedUser;
}

+ (AMIMUserDefault *) getLastLoginedUser
{

    NSString *lastUid = [AMIMDefaultStorageHelper getLastLoginedUserId] ;
    
    AMIMUserDefault * user = [AMIMDefaultStorageHelper getLoginedUser:lastUid];
    
    return user;
}

+ (AMIMUserDefault * )getLoginedUserWithIndex:(int)index
{
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    if(userList != nil && userList.count >index){
        return [NSKeyedUnarchiver unarchiveObjectWithData:[userList objectAtIndex:index]];
    }
    return  nil;
}

+ (AMIMUserDefault * )getLoginedUser:(NSString *)uid
{
    [uid retain];
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    if(userList != nil && userList.count > 0){
        int size = userList.count;
        for(int i=0; i<size; i++){
            NSData * data = (NSData *)[userList objectAtIndex:i];
            AMIMUserDefault * tempUser = [NSKeyedUnarchiver unarchiveObjectWithData:data];
            NSLog(@"uid:%@", tempUser.uid);
            NSLog(@"passwd:%@", tempUser.passwd);
            if([tempUser.uid isEqualToString:uid]){
                return tempUser;
            }
        }
    }
    
    [uid release];
    return nil;
}

+ (void) changeLastLoginedUser:(NSString *)uid
{
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    [accountInfoDict setValue:uid forKey:IM_DEFAULT_DATA_LAST_LOGINED_USER];
    [[NSUserDefaults standardUserDefaults] setValue:accountInfoDict forKey:IM_DEFAULT_DATA_ACCOUNT_INFO];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (NSMutableArray *) getLoginedUserList
{
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[[NSUserDefaults standardUserDefaults] objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];

    return userList;
}

+ (void) addLoginedUser:(AMIMUserDefault *) user
{
   
    [AMIMDefaultStorageHelper deleteUser:user.uid];

    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    NSMutableDictionary *accountInfoDict = [NSMutableDictionary dictionaryWithDictionary:[userDefault objectForKey:IM_DEFAULT_DATA_ACCOUNT_INFO]];
     
    
    NSMutableArray * userList =  [NSMutableArray arrayWithArray: [accountInfoDict objectForKey:IM_DEFAULT_DATA_LOGINED_USER_LIST]];
    [userList insertObject:[NSKeyedArchiver archivedDataWithRootObject:user] atIndex:0];
    
    [accountInfoDict setValue:userList forKey:IM_DEFAULT_DATA_LOGINED_USER_LIST];
    [userDefault setObject:accountInfoDict forKey:IM_DEFAULT_DATA_ACCOUNT_INFO];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (void) changeSelfState:(int)state
{
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLastLoginedUser];
    user.status = state;
    [AMIMDefaultStorageHelper deleteUser:user.uid];
    [AMIMDefaultStorageHelper addLoginedUser:user];
}

+ (void) changeSelfGroupState:(BOOL)groupState friendState:(BOOL)friendState blackState:(BOOL)blackState
{
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLastLoginedUser];
    user.groupListUpdated = groupState;
    user.friendListUpdated = friendState;
    user.blackListUpdated = blackState;
    [AMIMDefaultStorageHelper deleteUser:user.uid];
    [AMIMDefaultStorageHelper addLoginedUser:user];
}

+ (void) changeSelfGroupTimestamp:(int)timestamp 
{
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLastLoginedUser];
    user.groupListTimestamp = timestamp;
    
    [AMIMDefaultStorageHelper deleteUser:user.uid];
    [AMIMDefaultStorageHelper addLoginedUser:user];
}

+ (void) changeSelfFriendTimestamp:(int)timestamp 
{
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLastLoginedUser];
    user.friendListTimestamp = timestamp;
    
    [AMIMDefaultStorageHelper deleteUser:user.uid];
    [AMIMDefaultStorageHelper addLoginedUser:user];
}

+ (void) changeSelfBlackTimestamp:(int)timestamp 
{
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLastLoginedUser];
    user.blackListTimestamp = timestamp;
    
    [AMIMDefaultStorageHelper deleteUser:user.uid];
    [AMIMDefaultStorageHelper addLoginedUser:user];
}

+(void)changeSelfNotickWithMusic:(bool)music shake:(bool)shake
{
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLastLoginedUser];
    user.soundNotice = music;
    user.shakeNotice = shake;
    
    [AMIMDefaultStorageHelper deleteUser:user.uid];
    [AMIMDefaultStorageHelper addLoginedUser:user];
}


@end

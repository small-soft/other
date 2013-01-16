//
//  UserDataUtils.m
//  AlibabaMobile
//
//  Created by  on 12-1-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "UserDataUtils.h"
#import "LoginToken.h"

NSString * const USER_TYPE_FREEUSER = @"freeUser";
NSString * const USER_TYPE_FORMALUSER = @"formalUser";

@implementation UserDataUtils

// 精准营销相关
+(void)setPmUserInfo:(NSString *)siteId :(NSString *)userType :(NSString *)uniqueStr {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    [defaults setValue:siteId forKey:@"pm_site_id"];
    [defaults setValue:userType forKey:@"pm_user_type"];
    [defaults setValue:uniqueStr forKey:@"pm_unique_string"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+(NSString *)getPmSiteId {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    return [defaults objectForKey:@"pm_site_id"];
}

+(NSString *)getPmUserType {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    return [defaults objectForKey:@"pm_user_type"];
}

+(NSString *)getPmUniqueStr {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    return [defaults objectForKey:@"pm_unique_string"];
}

+(NSString *) generateUniqueStr:(NSString *)memberId:(NSString *)siteId {
    return [NSString stringWithFormat:@"%@Alibaba%@", memberId, siteId];;
}

+(BOOL) isPmFreeUser {
    NSString * userType = [UserDataUtils getPmUserType];
    if (userType != nil && [USER_TYPE_FREEUSER isEqualToString:userType]) {
        return YES;
    } else {
        return NO;
    }
}

+ (BOOL) checkUniqueStrValid {
    NSString * uniqueStr = [UserDataUtils getPmUniqueStr];
    NSString * memberId = [LoginToken getLoginUserName];
    NSString * siteId = [UserDataUtils getPmSiteId];

    if (uniqueStr == nil || memberId == nil || siteId == nil) {
        return NO;
    }

    NSString * newUniqueStr = [UserDataUtils generateUniqueStr:memberId :siteId];

    if ([uniqueStr isEqualToString:newUniqueStr]) {
        return YES;
    } else {
        return NO;
    }
}

// 行业首页选择
+ (void) setSelectNumber:(NSInteger)selectNumber;
{
    selectNumber = selectNumber + 1;
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    [defaults setInteger:selectNumber forKey:@"selectNumber"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}
+ (void) setFirstLaunch: (BOOL)firstLaunch
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    [defaults setBool:firstLaunch forKey:@"firstLaunch"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}
+ (void) setNavigationHomeBar: (BOOL)navigationHomeBar
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    [defaults setBool:navigationHomeBar forKey:@"navigationHomeBar"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}
+ (NSInteger) getSelectNumber
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    return [defaults integerForKey:@"selectNumber"];
}
+ (BOOL) getFirstLaunch
{
//    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
//    return [defaults boolForKey:@"firstLaunch"];
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger integer = [defaults integerForKey:@"selectNumber"];
    if (integer == 0) {
        return YES;
    }
    else {
        return NO;
    }

}
+ (BOOL) getNavigationHomeBar
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    return [defaults boolForKey:@"navigationHomeBar"];
}

+(NSString*)getBrandsCateId{
    NSUserDefaults * userDefault = [NSUserDefaults standardUserDefaults];
    return [userDefault objectForKey:@"defaultCategoryId"];
}

+(void)setBrandsCateId:(NSString *)brandsCateId{
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    [userDefault setValue:brandsCateId  forKey:@"defaultCategoryId"];
    [userDefault synchronize];
}
+(NSInteger)getLastCateOffset{
    NSUserDefaults * userDefault = [NSUserDefaults standardUserDefaults];
    return [userDefault integerForKey:@"lastCateOffset"];
}
+(void)setLastCateOffset:(NSInteger)lastCateOffset{
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    [userDefault setInteger:lastCateOffset forKey:@"lastCateOffset"];
    [userDefault synchronize];

}
@end

//
//  UserDataUtils.h
//  AlibabaMobile
//
//  Created by  on 12-1-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UserDataUtils : NSObject

// 精准营销相关
+ (void) setPmUserInfo:(NSString *)siteId :(NSString *)userType :(NSString *)uniqueStr;
+ (NSString *) getPmSiteId;
+ (NSString *) getPmUserType;
+ (NSString *) getPmUniqueStr;
+ (NSString *) generateUniqueStr:(NSString *)memberId:(NSString *)siteId;
+ (BOOL) isPmFreeUser;
+ (BOOL) checkUniqueStrValid;
// 行业首页选择
+ (void) setSelectNumber:(NSInteger)selectNumber;
+ (void) setFirstLaunch: (BOOL)firstLaunch;
+ (void) setNavigationHomeBar: (BOOL)navigationHomeBar;
+ (NSInteger) getSelectNumber;
+ (BOOL)       getFirstLaunch;
+ (BOOL)       getNavigationHomeBar;
//品牌库
+ (NSString*) getBrandsCateId;
+ (void) setBrandsCateId:(NSString*)brandsCateId;
+(NSInteger)getLastCateOffset;
+ (void) setLastCateOffset:(NSInteger)lastCateOffset;
@end

//
//  Utils.h
//  AlibabaMobile
//
//  Created by  on 12-1-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HJObjManager.h"

@interface Utils : NSObject

+ (NSString *) generateBodyString: (NSDictionary *)params;
+ (NSString *) createUUID;
+ (BOOL) isApplicationFirstLaunched;
+ (void)launchMailApp:(NSString *) emailAddress;
+ (HJObjManager *) createObjManagerDefault;
+ (HJObjManager *) createObjManagerWithLoadingBufferSize:(int)loadingBufferSize memCacheSize:(int)memCacheSize fileCountLimit:(long)fileCountLimit fileAgeLimit:(long)fileAgeLimit;
@end

//
//  AMHotAreaRequest.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_HOT_AREA ([@"/search.area.getHotAreas/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMHotAreaRequest : NSObject<RKRequestSerializable>

@end

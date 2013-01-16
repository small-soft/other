//
//  AMGeoGraphicInfoRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_GEO ([@"/search.geo.listGeographicInfo/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMGeoGraphicInfoRequest : NSObject<RKRequestSerializable> 

@property (nonatomic,retain)NSString *latitude;
@property (nonatomic,retain)NSString*longitude;

@end

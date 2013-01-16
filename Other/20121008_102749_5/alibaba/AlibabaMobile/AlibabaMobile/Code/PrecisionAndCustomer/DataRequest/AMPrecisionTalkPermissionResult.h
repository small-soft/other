//
//  AMPrecisionTalkPermissionResult.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMPrecisionTalkPermissionResult : NSObject <AMObjectMappingDelegate> {
}

@property(nonatomic, retain) NSNumber * hasPermissionUsed;
@property(nonatomic, retain) NSNumber * talked;

@end

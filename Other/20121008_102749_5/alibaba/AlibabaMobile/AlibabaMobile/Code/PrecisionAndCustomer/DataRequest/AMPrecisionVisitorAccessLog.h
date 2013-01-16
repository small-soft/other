//
//  AMPrecisionVisitorAccessLog.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMPrecisionVisitorAccessLog : NSObject<AMObjectMappingDelegate> {
}

@property(nonatomic, retain) NSString * time;
@property(nonatomic, retain) NSArray * logList;

@end

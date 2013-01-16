//
//  AMPrecisionVisitorAccessLogDetail.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMPrecisionVisitorAccessLogDetail : NSObject<AMObjectMappingDelegate> {
}

@property(nonatomic, retain) NSString * title;
@property(nonatomic, retain) NSNumber * browseCount; //int
@property(nonatomic, retain) NSString * stayTime;
@property(nonatomic, retain) NSString * openTime;
@property(nonatomic, retain) NSString * isPageClose;
@property(nonatomic, retain) NSString * url;
@property(nonatomic, retain) NSNumber * stayMilliSeconds; //long

@end
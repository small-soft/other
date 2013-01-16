//
//  AMCustomerSuggestAddResult.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCustomerSuggestAddResult : NSObject <AMObjectMappingDelegate> {
}

@property(nonatomic, retain) NSNumber * success;
@property(nonatomic, retain) NSString * resultCode;

@end

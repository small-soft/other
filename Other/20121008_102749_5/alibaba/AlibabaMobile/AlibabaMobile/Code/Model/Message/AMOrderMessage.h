//
//  AMOrderMessage.h
//  AlibabaMobile
//
//  Created by  on 12-10-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
@interface AMOrderMessage : NSObject<AMObjectMappingDelegate>
@property (nonatomic, copy) NSString * orderId;
@end

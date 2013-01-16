//
//  AMHomeContent.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMAppPath.h"

@interface AMHomeContent : NSObject <AMObjectMappingDelegate>
@property(nonatomic, retain) AMAppPath * appPath;
@property(nonatomic, retain) NSString * clickId;
@property(nonatomic, retain) NSString * imageUrl;
@property(nonatomic, retain) NSString * operationDesc;

@end

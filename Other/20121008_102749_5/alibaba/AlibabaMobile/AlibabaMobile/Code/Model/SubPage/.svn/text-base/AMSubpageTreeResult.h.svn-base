//
//  AMSubpageTreeResult.h
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMSubpageTreeResult : NSObject<AMObjectMappingDelegate>

@property(nonatomic, copy) NSString *md5Checksum;
@property(nonatomic, copy) NSString *type;
@property(nonatomic, assign) BOOL updated;
@property(nonatomic, assign) BOOL hasChild;
@property(nonatomic, retain) NSArray *children;

@end

@interface AMSubpageTreeChildren : NSObject<AMObjectMappingDelegate>

@property(nonatomic, copy) NSString *ID;
@property(nonatomic, copy) NSString *type;
@property(nonatomic, copy) NSString *name;
@property(nonatomic, copy) NSString *imageUrl;
@property(nonatomic, assign) BOOL hasChild;
@property(nonatomic, retain) NSArray *children;
@end

//
//  AMMappingUtil.h
//  AlibabaMobile
//
//  Created by  on 12-9-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
@interface AMMappingUtil : NSObject
+(id)performMappingWithMapping:(RKObjectMappingDefinition*)configuredObjectMapping forJsonString:(NSString*)jsonString;
@end

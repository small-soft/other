//
//  AMBrandsCategoryRequest.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMObjectMappingDelegate.h"

@interface AMBrandsRequest: NSObject<RKRequestSerializable>
{
    NSInteger _catId;
}

@property (nonatomic)  NSInteger  catId;


@end

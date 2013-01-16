//
//  AMBrandsResult.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMBrandsResult  :  NSObject <AMObjectMappingDelegate>
{
    NSString * _success;
    NSMutableArray * _resultList;
}

@property (nonatomic,retain) NSString * success;
@property (nonatomic,retain) NSMutableArray * resultList;

@end

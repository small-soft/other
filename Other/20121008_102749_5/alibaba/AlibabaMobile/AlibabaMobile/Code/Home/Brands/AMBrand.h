//
//  AMBrand.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMBrand  :  NSObject <AMObjectMappingDelegate>
{
    NSString * _brandId;
    NSString * _brandName;
    NSString * _logo;
    NSString * _keyword;
}

@property (nonatomic, retain) NSString * brandId;
@property (nonatomic, retain) NSString * brandName;
@property (nonatomic, retain) NSString * logo;
@property (nonatomic, retain) NSString * keyword;

@end

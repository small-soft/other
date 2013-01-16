//
//  NSString+StringUtil.m
//  GHUnitProject
//
//  Created by mardin partytime on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSString+StringUtil.h"

@implementation NSString (StringUtil)

- (NSNumber *)lengthAsNumber {
    unsigned int length = self.length;
    
    return [NSNumber numberWithUnsignedInt:length];
}

@end

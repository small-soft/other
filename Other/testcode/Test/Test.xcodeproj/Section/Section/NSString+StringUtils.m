//
//  NSString+StringUtils.m
//  Section
//
//  Created by 佳 刘 on 12-9-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSString+StringUtils.h"

@implementation NSString (StringUtils)

- (BOOL)compareIgnoreCase:(NSString *)str {
    
    return [self compare:str options:NSCaseInsensitiveSearch] == NSOrderedSame;
}

@end

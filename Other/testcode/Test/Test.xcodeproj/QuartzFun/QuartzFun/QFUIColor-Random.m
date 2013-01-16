//
//  QFUIColor-Random.m
//  QuartzFun
//
//  Created by 佳 刘 on 12-10-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "QFUIColor-Random.h"

@implementation UIColor(Random)
+(UIColor *)randomColor {
    static BOOL seeded = NO;
    if (!seeded) {
        seeded = YES;
        srandom(time(NULL));
    }
    
    CGFloat red = (CGFloat)random();
    CGFloat blue = (CGFloat)random();
    CGFloat green = (CGFloat)random();

    return [UIColor colorWithRed:red green:green blue:blue alpha:1.f];
}

@end

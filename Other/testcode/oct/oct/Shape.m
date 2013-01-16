//
//  Shape.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Shape.h"

@implementation Shape
@synthesize x = _x;
@synthesize y = _y;

- (void)draw {
    NSLog(@"draw a shape in (%d,%d)!",self.x,self.y);
} // draw

- (Shape *)initWithX:(NSInteger)x andY:(NSInteger)y {
    if (self = [super init]) {
        self.x = x;
        self.y = y;
    }
    
    return self;
} // initWithX

@end

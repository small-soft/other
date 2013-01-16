//
//  Circle.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Circle.h"

@implementation Circle 
@synthesize r = _r;

- (Circle *)initWithX:(NSInteger)x andY:(NSInteger)y andR:(NSInteger)r {
    if (self = [super initWithX:x andY:y]) {
        self.r = r;
    }
    
    return self;
} // initWithX

- (void)draw {
    NSLog(@"draw a circle in (%d,%d) and r = %d",self.x,self.y,self.r);
} // draw

@end

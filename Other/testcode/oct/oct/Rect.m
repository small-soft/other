//
//  Rect.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Rect.h"

@implementation LJRect
@synthesize width = _width;
@synthesize height = _height;

- (void)draw {
    NSLog(@"draw a rect in (%d,%d) and width=%d , height = %d",self.x,self.y,self.width,self.height);
} // draw

- (LJRect *)initWithX:(NSInteger)x andY:(NSInteger)y andWidth:(NSInteger)width andHeight:(NSInteger)height {
    if (self = [super initWithX:x andY:y]) {
        self.width = width;
        self.height = height;
    }
    
    return self;
} // initWithX

@end

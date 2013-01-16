//
//  Rect.h
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Shape.h"

@interface LJRect : Shape {
    NSInteger _width;
    NSInteger _height;
}

@property (nonatomic) NSInteger width;
@property (nonatomic) NSInteger height;

- (LJRect *) initWithX:(NSInteger)x andY:(NSInteger)y andWidth:(NSInteger)width andHeight:(NSInteger)height;

@end

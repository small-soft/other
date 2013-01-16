//
//  Circle.h
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Shape.h"

@interface Circle : Shape {
    NSInteger _r;
}

@property (nonatomic) NSInteger r;

- (Circle *) initWithX:(NSInteger)x andY:(NSInteger)y andR:(NSInteger)r;

@end

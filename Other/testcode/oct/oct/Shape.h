//
//  Shape.h
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Shape : NSObject {
    NSInteger _x;
    NSInteger _y;
}

@property (nonatomic) NSInteger x;
@property (nonatomic) NSInteger y;

- (Shape *) initWithX:(NSInteger)x andY:(NSInteger)y;

- (void) draw ;
@end

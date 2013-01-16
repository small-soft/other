//
//  Engine.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Engine.h"

@implementation Engine

@synthesize horsePower = _horsePower;

- (id)copyWithZone:(NSZone *)zone {
    Engine *engineCopy;
    engineCopy = [[[self class]allocWithZone:zone]init];
    
    return engineCopy;
}

@end

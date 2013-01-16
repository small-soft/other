//
//  Tire.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Tire.h"

@implementation Tire
@synthesize pressure = _pressure;
@synthesize treadDepth = _treadDepth;

- (Tire *) initWithPressure:(float)pressure treadDepth:(float)treadDepth {
    if (self = [super init]) {
        self.pressure = pressure;
        self.treadDepth = treadDepth;
    }
    
    return self;
}

- (id)copyWithZone:(NSZone *)zone {
    Tire *tireCopy = [[[self class] allocWithZone:zone] initWithPressure:self.pressure treadDepth:self.treadDepth];
                      
    return tireCopy;
}


@end //tire

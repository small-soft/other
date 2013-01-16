//
//  AllWeatherRadial.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AllWeatherRadial.h"

@implementation AllWeatherRadial
@synthesize rainHandling = _rainHandling;
@synthesize snowHandling = _snowHandling;

- (AllWeatherRadial *)initWithRainHanding:(float)rainHanding snowHanding:(float)snowHanding {
    if (self=[super initWithPressure:1. treadDepth:2.]) {
        self.rainHandling = rainHanding;
        self.snowHandling = snowHanding;
    }
    
    return self;
}

- (id)copyWithZone:(NSZone *)zone {
    AllWeatherRadial *tireCopy = [super copyWithZone:zone];
    
    tireCopy.rainHandling = self.rainHandling;
    tireCopy.snowHandling = self.snowHandling;
    
    return tireCopy;
}
@end

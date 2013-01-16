//
//  AllWeatherRadial.h
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Tire.h"

@interface AllWeatherRadial : Tire {
    float _rainHandling;
    float _snowHandling;
}

@property (nonatomic) float rainHandling;
@property (nonatomic) float snowHandling;

- (AllWeatherRadial *) initWithRainHanding:(float)rainHanding snowHanding:(float)snowHanding;
@end

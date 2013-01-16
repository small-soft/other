//
//  Tire.h
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Tire : NSObject <NSCopying> {
    float _pressure;
    float _treadDepth;
}

@property (nonatomic) float pressure;
@property (nonatomic) float treadDepth;

- (Tire *) initWithPressure:(float)pressure treadDepth:(float)treadDepth ;
@end

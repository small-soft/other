//
//  Car.h
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
@class Engine;

@interface Car : NSObject <NSCopying>{
    Engine *_engine;
    NSMutableArray *_tires;
}

@property (nonatomic,retain) Engine *engine;
@property (nonatomic,retain) NSMutableArray *tires; 
@end

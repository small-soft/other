//
//  Car.m
//  oct
//
//  Created by mardin partytime on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Car.h"
#import "Tire.h"
#import "Engine.h"

@implementation Car
@synthesize engine = _engine;
@synthesize tires = _tires;

- (id)init {
    if (self = [super init]) {
        self.engine = [[[Engine alloc]init]autorelease];
        
        self.tires = [NSMutableArray arrayWithCapacity:4];
        [self.tires addObject:[[[Tire alloc]init]autorelease]];
        [self.tires addObject:[[[Tire alloc]init]autorelease]];
        [self.tires addObject:[[[Tire alloc]init]autorelease]];
        [self.tires addObject:[[[Tire alloc]init]autorelease]];
    }
    
    return self;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"this is a car,i have a engine(%@) and four tires(%@,%@,%@,%@)",self.engine,[self.tires objectAtIndex:0],[self.tires objectAtIndex:1],[self.tires objectAtIndex:2],[self.tires objectAtIndex:3]];
}

- (id)copyWithZone:(NSZone *)zone {
    Car *carCopy = [[[self class]allocWithZone:zone]init];
    
    carCopy.engine = [[self.engine copy] autorelease];
    
    for (int i = 0; i < 4; i++) {
        Tire *tireCopy;
        
        tireCopy = [[[self.tires objectAtIndex:i] copy]autorelease];
    }
    
    return carCopy;
}

- (void)setNilValueForKey:(NSString *)key {
    
}

- (id)valueForUndefinedKey:(NSString *)key {
    return nil;
}

- (void)setValue:(id)value forUndefinedKey:(NSString *)key {
    
}
@end

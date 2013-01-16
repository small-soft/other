//
//  Thingie.m
//  GHUnitProject
//
//  Created by 佳 刘 on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Thingie.h"

@implementation Thingie
@synthesize shoeSize;
@synthesize name;
@synthesize magicNumber;
@synthesize subThingies;

- (id)initwithName:(NSString *)n magicNumber:(int)mc shoeSize:(float)ss {
    if (self = [super init]) {
        self.name = n;
        self.magicNumber = mc;
        self.shoeSize = ss;
    }
    
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super init]) {
        self.name = [aDecoder decodeObjectForKey:@"name"];
        self.magicNumber = [aDecoder decodeIntForKey:@"magicNumber"];
        self.shoeSize = [aDecoder decodeFloatForKey:@"shoeSize"];
        self.subThingies = [aDecoder decodeObjectForKey:@"subThingies"];                        
    } 
    return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:name forKey:@"name"];
    [aCoder encodeInt:magicNumber forKey:@"magicNumber"];
    [aCoder encodeFloat:shoeSize forKey:@"shoeSize"];
    [aCoder encodeObject:subThingies forKey:@"subThingies"];
}

- (NSString *)description {
    return [NSString stringWithFormat:@"name:%@|magicNumber:%d|shoeSize:%f|subThingies:%@",self.name,self.magicNumber,self.shoeSize,self.subThingies];
}
@end

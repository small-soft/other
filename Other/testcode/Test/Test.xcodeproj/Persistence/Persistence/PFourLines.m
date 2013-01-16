//
//  PFourLines.m
//  Persistence
//
//  Created by 佳 刘 on 12-9-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PFourLines.h"

@implementation PFourLines
@synthesize field1;
@synthesize field2;
@synthesize field3;
@synthesize field4;

-(void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:field1 forKey:kField1Key];
    [aCoder encodeObject:field2 forKey:kField2Key];
    [aCoder encodeObject:field3 forKey:kField3Key];
    [aCoder encodeObject:field3 forKey:kField4Key];
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super init]) {
        self.field1 = [aDecoder decodeObjectForKey:kField1Key];
        self.field2 = [aDecoder decodeObjectForKey:kField2Key];
        self.field3 = [aDecoder decodeObjectForKey:kField3Key];
        self.field4 = [aDecoder decodeObjectForKey:kField4Key];
    }
    
    return self;
}

- (id)copyWithZone:(NSZone *)zone {
    PFourLines *copy = [[[self class] allocWithZone:zone]init];
    copy.field1 = [[self.field1 copyWithZone:zone]autorelease];
    copy.field2 = [[self.field2 copyWithZone:zone]autorelease];
    copy.field3 = [[self.field3 copyWithZone:zone]autorelease];
    copy.field4 = [[self.field4 copyWithZone:zone]autorelease];
    
    return copy;
}

@end

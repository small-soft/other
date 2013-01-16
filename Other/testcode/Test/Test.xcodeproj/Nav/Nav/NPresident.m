//
//  NPresident.m
//  Nav
//
//  Created by 佳 刘 on 12-9-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NPresident.h"

@implementation President
@synthesize name;
@synthesize party;
@synthesize number;
@synthesize toYear;
@synthesize fromYear;

-(void)dealloc {
    [self.name release];
    [self.fromYear release];
    [self.toYear release];
    [self.party release];
    
    [super dealloc];
}

#pragma mark -
#pragma mark nscoding
-(void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeInt:self.number forKey:kPresidentNumberKey];
    [aCoder encodeObject:self.name forKey:kPresidentNameKey];
    [aCoder encodeObject:self.fromYear forKey:kPresidentFromKey];
    [aCoder encodeObject:self.toYear forKey:kPresidentToKey];
    [aCoder encodeObject:self.party forKey:kPresidentPartyKey];
}

-(id)initWithCoder:(NSCoder *)aDecoder {
    if (self == [super init]) {
        self.number = [aDecoder decodeIntForKey:kPresidentNumberKey];
        self.name = [aDecoder decodeObjectForKey:kPresidentNameKey];
        self.fromYear = [aDecoder decodeObjectForKey:kPresidentFromKey];
        self.toYear = [aDecoder decodeObjectForKey:kPresidentToKey];
        self.party = [aDecoder decodeObjectForKey:kPresidentPartyKey];
    }
    
    return self;
}

@end

//
//  KeyValueObject.m
//  AlibabaMobile
//
//  Created by  on 12-2-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "KeyValueObject.h"
#import "AliKeyValueMapView.h"


@implementation KeyValueObject

@synthesize key = _key;
@synthesize value = _value;
@synthesize type = _type;

- (id) init
{
    [super init];

    _key = nil;
    _value = nil;
    _type = VALUE_STYLE_PLAIN;
    
    return self;
}

- (id) initWithKey:(id)key value:(id)value
{
    self = [self init];
    if(self){
        self.key = key;
        self.value = value;
    }
    return self;
    
}

- (id) initWithType:(int)type
{
    self = [self init];
    if(self){
        self.type = type;
    }
    return self;
}

- (void) dealloc {
    [_key release];
    [_value release];
    
    [super dealloc];
}

@end

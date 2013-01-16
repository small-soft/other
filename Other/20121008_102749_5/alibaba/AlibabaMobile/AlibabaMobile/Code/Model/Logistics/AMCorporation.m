//
//  AMCorporation.m
//  AlibabaMobile
//
//  Created by  on 12-1-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCorporation.h"
#import <RestKit/RestKit.h>

@implementation AMCorporation

@synthesize name = _name;
@synthesize code = _code;
@synthesize pinyin = _pinyin;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCorporation class]] retain];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
			[sharedObjectMapping mapKeyPath:@"code" toAttribute:@"code"];
			[sharedObjectMapping mapKeyPath:@"pinyin" toAttribute:@"pinyin"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString*)description {
    return [NSString stringWithFormat:@"name: %@ (code: %@)", self.name, self.code];
}

- (void) dealloc {
    [_name release];
    [_code release];
    [_pinyin release];
    
    [super dealloc];
}

@end

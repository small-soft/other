//
//  AMCorpsByLetter.m
//  AlibabaMobile
//
//  Created by  on 12-1-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCorpsByLetter.h"
#import "AMCorporation.h"
#import <RestKit/RestKit.h>

@implementation AMCorpsByLetter

@synthesize key = _key;
@synthesize corps = _corps;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCorpsByLetter class]] retain];
			[sharedObjectMapping mapKeyPath:@"key" toAttribute:@"key"];
			[sharedObjectMapping mapRelationship:@"corps" withMapping:[AMCorporation sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCorporation sharedObjectMapping] forKeyPath:@"corps"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString*)description {
    return [NSString stringWithFormat:@"key: %@ [corps: %@]", self.key, self.corps];
}

- (void) dealloc {
    [_key release];
    [_corps release];
    
    [super dealloc];
}

@end

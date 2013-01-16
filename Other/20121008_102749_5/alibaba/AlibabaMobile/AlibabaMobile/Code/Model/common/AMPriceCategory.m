//
//  AMPriceCategory.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
// 


#import "AMPriceCategory.h"

@implementation AMPriceCategory

@synthesize identifier = _identifier;
@synthesize parentId = _parentId;
@synthesize industryId = _industryId;
@synthesize parentName = _parentName;
@synthesize name = _name;
@synthesize leaf = _leaf;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPriceCategory class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"parentId" toAttribute:@"parentId"];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
			[sharedObjectMapping mapKeyPath:@"leaf" toAttribute:@"leaf"];
			[sharedObjectMapping mapKeyPath:@"industryId" toAttribute:@"industryId"];
			[sharedObjectMapping mapKeyPath:@"parentName" toAttribute:@"parentName"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString*)description {
    return [NSString stringWithFormat:@"%@ (ID: %@)", self.name, self.identifier];
}

- (void)dealloc {
    [_identifier release];
    [_parentId release];
    [_name release];
    [_industryId release];
    [_parentName release];

    [super dealloc];
}

@end

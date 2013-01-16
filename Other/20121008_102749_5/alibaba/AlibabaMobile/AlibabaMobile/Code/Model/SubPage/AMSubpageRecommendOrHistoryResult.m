//
//  AMSubpageRecommendOrHistoryResult.m
//  AlibabaMobile
//
//  Created by  on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageRecommendOrHistoryResult.h"

@implementation AMSubpageRecommendOrHistoryResult

@synthesize type = _type;
@synthesize children = _children;
@synthesize updated = _updated;
@synthesize hasChild= _hasChild;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSubpageRecommendOrHistoryResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"updated" toAttribute:@"updated"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            [sharedObjectMapping mapRelationship:@"children" withMapping:[AMSubpageRecommendOrHistoryChildren sharedObjectMapping]];
        }
    }
    
    return sharedObjectMapping;
}
- (void)dealloc
{
    [_type release];
    [_children release];
    [super dealloc];
}
@end

@implementation AMSubpageRecommendOrHistoryChildren
@synthesize type = _type;
@synthesize name = _name;
@synthesize hasChild = _hasChild;
@synthesize ID = _ID;
//@synthesize children = _children;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSubpageRecommendOrHistoryChildren class]] retain];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"ID"];
            
            //			[sharedObjectMapping mapRelationship:@"children" withMapping:[AMSubpageRecommendChildren sharedObjectMapping]];
			
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_type release];
    [_name release];
    [_ID release];
    //    [_children release];
    [super dealloc];
}
@end

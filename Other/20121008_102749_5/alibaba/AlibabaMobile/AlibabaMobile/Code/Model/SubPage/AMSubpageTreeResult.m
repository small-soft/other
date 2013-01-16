//
//  AMSubpageTreeResult.m
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageTreeResult.h"
#import "ConstDef.h"
@implementation AMSubpageTreeResult
@synthesize md5Checksum = _md5Checksum;
@synthesize type = _type;
@synthesize children = _children;
@synthesize updated = _updated;
@synthesize hasChild= _hasChild;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSubpageTreeResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"md5Checksum" toAttribute:@"md5Checksum"];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"updated" toAttribute:@"updated"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            [sharedObjectMapping mapRelationship:@"children" withMapping:[AMSubpageTreeChildren sharedObjectMapping]];
        }
    }
    
    return sharedObjectMapping;
}
- (void)dealloc
{
    [_md5Checksum release];
    [_type release];
    [_children release];
    [super dealloc];
}


@end

@implementation AMSubpageTreeChildren
@synthesize type = _type;
@synthesize name = _name;
@synthesize imageUrl = _imageUrl;
@synthesize hasChild = _hasChild;
@synthesize ID = _ID;
@synthesize children = _children;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSubpageTreeChildren class]] retain];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"imageUrl" toAttribute:@"imageUrl"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"ID"];
            
			[sharedObjectMapping mapRelationship:@"children" withMapping:[AMSubpageTreeChildren sharedObjectMapping]];
			
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_type release];
    [_name release];
    [_imageUrl release];
    [_ID release];
    [_children release];
    [super dealloc];
}

@end


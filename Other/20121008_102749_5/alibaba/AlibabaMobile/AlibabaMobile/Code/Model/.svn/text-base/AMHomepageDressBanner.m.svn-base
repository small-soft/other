//
//  AMHomepageDressBanner.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressBanner.h"

@implementation AMHomepageDressBanner
@synthesize md5Checksum = _md5Checksum;
@synthesize type = _type;
@synthesize children = _children;
@synthesize updated = _updated;
@synthesize hasChild= _hasChild;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressBanner class]] retain];
			[sharedObjectMapping mapKeyPath:@"md5Checksum" toAttribute:@"md5Checksum"];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"updated" toAttribute:@"updated"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            
			[sharedObjectMapping mapRelationship:@"children" withMapping:[AMHomepageDressChilden sharedObjectMapping]];
			
//			// Setup object mapping
//			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//			[mappingProvider setMapping:[AMHomepageDressChilden sharedObjectMapping] forKeyPath:@"children"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_md5Checksum release];
    [_type release];
    [_children release];
    
    [super dealloc];
}
@end

@implementation AMHomepageDressChilden
@synthesize jumpPath = _jumpPath;
@synthesize imageUrl = _imageUrl;
@synthesize type = _type;
@synthesize name = _name;
@synthesize hasChild = _hasChild;
@synthesize clickId = _clickId;
@synthesize ID = _ID;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressChilden class]] retain];
			[sharedObjectMapping mapKeyPath:@"clickId" toAttribute:@"clickId"];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"imageUrl" toAttribute:@"imageUrl"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"ID"];
            
			[sharedObjectMapping mapRelationship:@"jumpPath" withMapping:[AMHomepageDressChildenJumpPath sharedObjectMapping]];
			
//			// Setup object mapping
//			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//			[mappingProvider setMapping:[AMHomepageDressChildenJumpPath sharedObjectMapping] forKeyPath:@"jumpPath"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_imageUrl release];
    [_type release];
    [_name release];
    [_clickId release];
    [_jumpPath release];
    [_ID release];
    
    [super dealloc];
}

@end

@implementation AMHomepageDressChildenJumpPath
@synthesize busiType = _busiType;
@synthesize pageId = _pageId;
@synthesize type = _type;
@synthesize params = _params;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressChildenJumpPath class]] retain];
			[sharedObjectMapping mapKeyPath:@"busiType" toAttribute:@"busiType"];
            [sharedObjectMapping mapKeyPath:@"pageId" toAttribute:@"pageId"];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            
            [sharedObjectMapping mapRelationship:@"params" withMapping:[AMHomepageDressChildenParams sharedObjectMapping]];
			
//			// Setup object mapping
//			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//			[mappingProvider setMapping:[AMHomepageDressChildenParams sharedObjectMapping] forKeyPath:@"params"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_busiType release];
    [_pageId release];
    [_type release];
    [_params release];
    
    [super dealloc];
}
@end

@implementation AMHomepageDressChildenParams
@synthesize entry_url = _entry_url;
@synthesize pictureNewsId = _pictureNewsId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressChildenParams class]] retain];
			[sharedObjectMapping mapKeyPath:@"entry_url" toAttribute:@"entry_url"];
            [sharedObjectMapping mapKeyPath:@"pictureNewsId" toAttribute:@"pictureNewsId"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_entry_url release];
    [_pictureNewsId release];
    
    [super dealloc];
}

@end
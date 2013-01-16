//
//  AMRecommendBrandsResult.m
//  AlibabaMobile
//
//  Created by 佳 刘 on 12-9-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMRecommendBrandsResult.h"

@implementation AMRecommendBrandsResult

@synthesize brandsios = _brandsios;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMRecommendBrandsResult class]] retain];
            
			[sharedObjectMapping mapRelationship:@"brandsios" withMapping:[AMRecommendBrands sharedObjectMapping]];
            
//            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//			[mappingProvider setMapping:[AMRecommendBrands sharedObjectMapping] forKeyPath:@"brands"];
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_brandsios release];
    
    [super dealloc];
}

@end




@implementation AMRecommendBrands

@synthesize children = _children;
@synthesize hasChild = _hasChild;
@synthesize imageUrl = _imageUrl;
@synthesize type = _type;
@synthesize updated = _updated;
@synthesize md5Checksum = _md5Checksum;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMRecommendBrands class]] retain];
			[sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
			[sharedObjectMapping mapKeyPath:@"imageUrl" toAttribute:@"imageUrl"];
			[sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
			[sharedObjectMapping mapKeyPath:@"updated" toAttribute:@"updated"];
            [sharedObjectMapping mapKeyPath:@"md5Checksum" toAttribute:@"md5Checksum"];
            [sharedObjectMapping mapRelationship:@"children" withMapping:[AMRecommendBrandsItem sharedObjectMapping]];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    
    [_children release];
    [_hasChild release];
    [_imageUrl release];
    [_type release];
    [_updated release];
    [_md5Checksum release];
    
    [super dealloc];
}

@end

@implementation AMRecommendBrandsItem

@synthesize brandId = _brandId;
@synthesize hasChild = _hasChild;
@synthesize type = _type;
@synthesize imageUrl = _imageUrl;
@synthesize name = _name;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMRecommendBrandsItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"brandId"];
			[sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
			[sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
			[sharedObjectMapping mapKeyPath:@"imageUrl" toAttribute:@"imageUrl"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapRelationship:@"children" withMapping:[AMRecommendBrandsItem sharedObjectMapping]];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    
    [_hasChild release];
    [_imageUrl release];
    [_type release];
    [_name release];
    [_brandId release];
    
    [super dealloc];
}

@end


//
//  AMBrandCategory.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandCategory.h"

@implementation AMBrandCategory

@synthesize cateId=_cateId;
@synthesize cateName=_cateName;

-(void) dealloc
{
    [_cateId release];
    [_cateName release];
    [super dealloc];
}

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMBrandCategory class]] retain];
            [sharedObjectMapping mapKeyPath:@"cateId" toAttribute:@"cateId"];
            [sharedObjectMapping mapKeyPath:@"cateName" toAttribute:@"cateName"];
            
        }
    }
    
    return sharedObjectMapping;
}

@end

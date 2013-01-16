//
//  AMBrand.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrand.h"

@implementation AMBrand

@synthesize brandId=_brandId;
@synthesize brandName=_brandName;
@synthesize logo=_logo;
@synthesize keyword=_keyword;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMBrand class]] retain];
            [sharedObjectMapping mapKeyPath:@"brandId" toAttribute:@"brandId"];
            [sharedObjectMapping mapKeyPath:@"brandName" toAttribute:@"brandName"];
            [sharedObjectMapping mapKeyPath:@"logo" toAttribute:@"logo"];
            [sharedObjectMapping mapKeyPath:@"keyword" toAttribute:@"keyword"];
            
        }
    }
    
    return sharedObjectMapping;
}

-(void)dealloc
{
    [_brandId release];
    [_brandName release];
    [_logo release];
    [super dealloc];
}

@end

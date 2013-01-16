//
//  AMBrandsCategoryResult.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandsCategoryResult.h"
#import "AMBrandCategory.h"

@implementation AMBrandsCategoryResult

@synthesize cates=_cates;

-(void) dealloc
{
    [_cates release];
    [super dealloc];
}

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMBrandsCategoryResult class]] retain];
            

            [sharedObjectMapping mapRelationship:@"cates" withMapping:[AMBrandCategory sharedObjectMapping]];
         			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMBrandCategory sharedObjectMapping] forKeyPath:@"cates"];
           
        }
    }
    
    return sharedObjectMapping;
}

@end

//
//  AMBrandsResult.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandsResult.h"
#import "AMBrand.h"

@implementation AMBrandsResult

@synthesize resultList=_resultList;
@synthesize success=_success;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMBrandsResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
                        
            [sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMBrand sharedObjectMapping]];
            
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMBrand sharedObjectMapping] forKeyPath:@"resultList"];
            
        }
    }
    
    return sharedObjectMapping;
}


-(void) dealloc
{
    [_success release];
    [_resultList release];
    
    [super dealloc];
}

@end

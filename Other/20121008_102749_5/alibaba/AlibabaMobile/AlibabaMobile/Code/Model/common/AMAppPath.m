//
//  AMAppPath.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAppPath.h"

@implementation AMAppPath

@synthesize busiType=_busiType;
@synthesize pageId = _pageId;
@synthesize type = _type;
@synthesize params = _params;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMAppPath class]] retain];
			[sharedObjectMapping mapKeyPath:@"busiType" toAttribute:@"busiType"];
			[sharedObjectMapping mapKeyPath:@"pageId" toAttribute:@"pageId"];
			[sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
			
			[sharedObjectMapping mapRelationship:@"params" withMapping:[AMAppPathParams sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMAppPathParams sharedObjectMapping] forKeyPath:@"params"];
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

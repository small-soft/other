//
//  AMHotRankResult.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankResult.h"

@implementation AMHotRankResult

@synthesize appPath = _appPath;
@synthesize clickId = _clickId;
@synthesize imageUrl=_imageUrl;
@synthesize operationDesc=_operationDesc;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotRankResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"clickId" toAttribute:@"clickId"];
            [sharedObjectMapping mapKeyPath:@"imageUrl" toAttribute:@"imageUrl"];
            [sharedObjectMapping mapKeyPath:@"operationDesc" toAttribute:@"operationDesc"];
            [sharedObjectMapping mapRelationship:@"appPath" withMapping:[AMAppPath sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMAppPath sharedObjectMapping] forKeyPath:@"appPath"];
            
        }
    }
    
    return sharedObjectMapping;
}

-(NSString*)description {
    return [NSString stringWithFormat:@"%@,%@", self.imageUrl, self.clickId];
}

- (void)dealloc {
    [_appPath release];
    [_clickId release];
    [_imageUrl release];
    [super dealloc];
}

@end

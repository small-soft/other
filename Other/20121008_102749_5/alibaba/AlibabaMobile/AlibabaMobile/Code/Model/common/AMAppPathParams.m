//
//  AMAppPathParams.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAppPathParams.h"

@implementation AMAppPathParams

@synthesize entry_url = _entry_url;
@synthesize pictureNewsId=_pictureNewsId;

//for hotrank add by xiaowen 2012-5-14
@synthesize cateId = _cateId;
@synthesize comId = _comId;
@synthesize secondcate = _secondcate;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMAppPathParams class]] retain];
			[sharedObjectMapping mapKeyPath:@"entry_url" toAttribute:@"entry_url"];
            [sharedObjectMapping mapKeyPath:@"pictureNewsId" toAttribute:@"pictureNewsId"];
            [sharedObjectMapping mapKeyPath:@"cateId" toAttribute:@"cateId"];
            [sharedObjectMapping mapKeyPath:@"comId" toAttribute:@"comId"];
            [sharedObjectMapping mapKeyPath:@"secondcate" toAttribute:@"secondcate"];
			
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    
    [_entry_url release];
    [_pictureNewsId release];
    [_cateId release];
    [_comId release];
    [_secondcate release];
    
    [super dealloc];
}


@end

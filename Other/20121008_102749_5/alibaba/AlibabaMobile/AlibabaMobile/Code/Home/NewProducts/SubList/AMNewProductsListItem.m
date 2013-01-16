//
//  AMNewProductsListItem.m
//  AlibabaMobile
//
//  Created by amon on 12-5-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsListItem.h"

@implementation AMNewProductsListItem
@synthesize subject = _subject;
@synthesize listImgUrl = _listImgUrl;
@synthesize unit = _unit;
@synthesize rmbPrice = _rmbPrice;
@synthesize offerId = _offerId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewProductsListItem class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"subject" toAttribute:@"subject"];
            [sharedObjectMapping mapKeyPath:@"unit" toAttribute:@"unit"];
            [sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
            [sharedObjectMapping mapKeyPath:@"listImgUrl" toAttribute:@"listImgUrl"];
			[sharedObjectMapping mapRelationship:@"rmbPrice" withMapping:[AMMoney sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMMoney sharedObjectMapping] forKeyPath:@"rmbPrice"];
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc{
    [_subject release];
    [_unit release];
    [_listImgUrl release];
    [_rmbPrice release];
    [super dealloc];
}

@end

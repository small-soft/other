//
//  AMSpecialPriceOffer.m
//  AlibabaMobile
//
//  Created by amon on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSpecialPriceOffer.h"

@implementation AMSpecialPriceOffer
@synthesize subject = _subject;
@synthesize originalPrice = _originalPrice;
@synthesize specialPrice = _specialPrice;
@synthesize listImgUrl = _listImgUrl;
@synthesize unit = _unit;
@synthesize price = _price;
@synthesize offerId = _offerId;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSpecialPriceOffer class]] retain];
            [sharedObjectMapping mapKeyPath:@"subject" toAttribute:@"subject"];
            [sharedObjectMapping mapKeyPath:@"originalPrice" toAttribute:@"originalPrice"];
            [sharedObjectMapping mapKeyPath:@"specialPrice" toAttribute:@"specialPrice"];
            [sharedObjectMapping mapKeyPath:@"unit" toAttribute:@"unit"];
            [sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
            [sharedObjectMapping mapKeyPath:@"listImgUrl" toAttribute:@"listImgUrl"];
			[sharedObjectMapping mapRelationship:@"price" withMapping:[AMMoney sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMMoney sharedObjectMapping] forKeyPath:@"price"];
            
            
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc{
    
    [_subject release];
    [_specialPrice release];
    [_originalPrice release];
    [_unit release];
    [_listImgUrl release];
    [_price release];
    [super dealloc];
}
@end


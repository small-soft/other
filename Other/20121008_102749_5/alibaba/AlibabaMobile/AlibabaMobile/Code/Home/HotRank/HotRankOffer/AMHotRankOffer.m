//
//  AMHotRankOffer.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankOffer.h"

@implementation AMHotRankOffer
@synthesize subject = _subject;
@synthesize offerPaymentGMV = _offerPaymentGMV;
@synthesize rankRiseNum = _rankRiseNum;
@synthesize listImgUrl = _listImgUrl;
@synthesize unit = _unit;
@synthesize price = _price;
@synthesize offerId = _offerId;
@synthesize tradeQuantity = _tradeQuantity;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotRankOffer class]] retain];
           
            [sharedObjectMapping mapKeyPath:@"subject" toAttribute:@"subject"];
            [sharedObjectMapping mapKeyPath:@"offerPaymentGMV" toAttribute:@"offerPaymentGMV"];
            [sharedObjectMapping mapKeyPath:@"rankRiseNum" toAttribute:@"rankRiseNum"];
            [sharedObjectMapping mapKeyPath:@"unit" toAttribute:@"unit"];
            [sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
            [sharedObjectMapping mapKeyPath:@"listImgUrl" toAttribute:@"listImgUrl"];
            [sharedObjectMapping mapKeyPath:@"tradeQuantity" toAttribute:@"tradeQuantity"];
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
    [_offerPaymentGMV release];
    [_rankRiseNum release];
    [_unit release];
    [_listImgUrl release];
    [_price release];
    [_tradeQuantity release];
    
    [super dealloc];
}
@end


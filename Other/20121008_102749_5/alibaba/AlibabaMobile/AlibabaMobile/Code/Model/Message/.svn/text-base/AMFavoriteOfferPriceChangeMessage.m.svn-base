//
//  AMFavoriteOfferPriceChangeMessage.m
//  AlibabaMobile
//
//  Created by  on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMFavoriteOfferPriceChangeMessage.h"

@implementation AMFavoriteOfferPriceChangeMessage
@synthesize offerId = _offerId;
@synthesize favoriteId = _favoriteId;

@synthesize newPriceDate = _newPriceDate;
@synthesize newPrice = _newPrice;
@synthesize oldPrice = _oldPrice;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMFavoriteOfferPriceChangeMessage class]] retain];
            [sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
            [sharedObjectMapping mapKeyPath:@"favoriteId" toAttribute:@"favoriteId"];
            [sharedObjectMapping mapKeyPath:@"newPrice" toAttribute:@"newPrice"];
            [sharedObjectMapping mapKeyPath:@"newPriceDate" toAttribute:@"newPriceDate"];
            [sharedObjectMapping mapKeyPath:@"oldPrice" toAttribute:@"oldPrice"];
        }
    }
    
    return sharedObjectMapping;
}


- (void)dealloc
{
    [_offerId release];
    [_favoriteId release];
    [_newPrice release];
    [_newPriceDate release];
    [_oldPrice release];
    [super dealloc];
}
@end

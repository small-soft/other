//
//  AMSpecialPriceOfferRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_SPECIAL_PRICE_OFFER_LIST ([@"/offer.queryNewSpecialPriceOffer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMSpecialPriceOfferRequest : NSObject<RKRequestSerializable>{
    
    NSString *_industryId;
    NSString *_requestURL;
    NSNumber *_pageSize;
    NSNumber *_pageIndex;
    
}

@property (retain,nonatomic) NSString *industryId;
@property (retain,nonatomic) NSString *requestURL;
@property (retain,nonatomic) NSNumber *pageSize;
@property (retain,nonatomic) NSNumber *pageIndex;

-(id) init;
@end

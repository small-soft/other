//
//  AMHotRankOfferRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"
#define OCEAN_API_URL_HOT_RANK_OFFER_LIST ([@"/rank.getMutiCategoryTradeRank/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMHotRankOfferRequest : NSObject<RKRequestSerializable,AMRequestDelegate>{
    
    NSNumber * _beginPage;
    NSNumber * _pageSize;
    NSNumber *_rankCycle;
    NSString *cateIds;
    NSString *_listMode;
    NSInteger _transactionType;
}

@property (retain,nonatomic) NSNumber *beginPage;
@property (retain,nonatomic) NSNumber *pageSize;
@property (retain,nonatomic) NSNumber *rankCycle;
@property (retain,nonatomic) NSString *requestURL;
@property (retain,nonatomic) NSString *cateIds;
@property (retain,nonatomic) NSString*listMode;
@property (nonatomic) NSInteger transactionType; 
-(id) init;
@end

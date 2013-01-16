//
//  AMHotRankRequest.h
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"
#define OCEAN_API_URL_HOT_RANK_COMPANY_LIST ([@"/rank.getCompanyTradeRank/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMHotRankCompanyRequest : NSObject<RKRequestSerializable,AMRequestDelegate>{
    
    NSNumber * _page;
    NSNumber * _count;
    NSNumber *_rankCycle;
    NSString *_cateId;
    NSString *_listMode;//"U" or "H"
    NSInteger _transactionType;
}

@property (retain,nonatomic) NSNumber *page;
@property (retain,nonatomic) NSNumber *count;
@property (retain,nonatomic) NSNumber *rankCycle;
@property (retain,nonatomic) NSString *requestURL;
@property (retain,nonatomic) NSString *cateId;
@property (retain,nonatomic) NSString *listMode;
@property (nonatomic) NSInteger transactionType; 
-(id) init;
@end

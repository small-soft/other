//
//  AMHotRankOffer.h
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMMoney.h"

@interface AMHotRankOffer : NSObject<AMObjectMappingDelegate> {
    
    NSNumber *_satisfiedRate;//商品满意度
    NSString *_subject;//产品名称
    NSNumber *_offerPaymentGMV;//交易金额
    
    NSNumber *_rankRiseNum;//上升排名
    NSNumber *_tradeQuantity;
    NSString *listImgUrl;//图片
    NSString *_unit;//单位
    NSNumber * _offerId;
    AMMoney *_price;
    
//    NSNumber *_price;//价格
    
}

@property (retain,nonatomic) NSString *subject;

@property (retain,nonatomic) NSNumber *offerPaymentGMV;;
@property (retain,nonatomic) NSString *listImgUrl;
@property (retain,nonatomic) NSString *unit;
@property (retain,nonatomic) NSNumber *offerId;
@property (retain,nonatomic) NSNumber *rankRiseNum;
@property (retain,nonatomic) NSNumber *tradeQuantity;
@property (retain,nonatomic) AMMoney *price;
@end

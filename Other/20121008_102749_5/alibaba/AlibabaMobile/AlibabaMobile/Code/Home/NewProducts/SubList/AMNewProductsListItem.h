//
//  AMNewProductsListItem.h
//  AlibabaMobile
//
//  Created by amon on 12-5-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMMoney.h"

@interface AMNewProductsListItem : NSObject<AMObjectMappingDelegate> {
    
    NSString *_subject;//产品名称  
    NSString *listImgUrl;//图片
    NSString *_unit;//单位
    NSNumber * _offerId;
    AMMoney *_rmbPrice;
    
}

@property (retain,nonatomic) NSString *subject;
@property (retain,nonatomic) NSString *listImgUrl;
@property (retain,nonatomic) NSString *unit;
@property (retain,nonatomic) NSNumber *offerId;
@property (retain,nonatomic) AMMoney *rmbPrice;
@end

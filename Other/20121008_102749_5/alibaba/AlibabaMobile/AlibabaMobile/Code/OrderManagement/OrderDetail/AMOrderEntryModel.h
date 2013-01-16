//
//  AMOrderEntryModel.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMOrderEntryModel : NSObject<AMObjectMappingDelegate>
{
    NSString * _productName;
    NSString * _mainSummImageUrl;
    
    NSString * _unit;
    NSNumber * _entryDiscount;
    NSNumber * _entryCouponAmount;
    NSNumber * _discountPrice;
    NSNumber * _quantity;
    
    NSArray * _specItems;
    
    
}



@property (nonatomic, retain) NSString * productName;
@property (nonatomic, retain) NSString * mainSummImageUrl;


@property (nonatomic, retain) NSString * unit;
@property (nonatomic, retain) NSNumber * entryDiscount;
@property (nonatomic, retain) NSNumber * entryCouponAmount;
@property (nonatomic, retain) NSNumber * discountPrice;
@property (nonatomic, retain) NSNumber * quantity;

@property (nonatomic, retain) NSArray *  specItems;

@end

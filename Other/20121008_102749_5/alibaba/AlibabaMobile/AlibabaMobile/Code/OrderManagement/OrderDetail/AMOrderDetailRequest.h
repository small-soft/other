//
//  AMOrderDetailRequest.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"
#import "ConstDef.h"

#define OCEAN_API_URL_ORDER_DETAIL ([@"/trade.order.findOrderById/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMOrderDetailRequest : NSObject <RKRequestSerializable, AMRequestDelegate> 
{
//    NSNumber * _orderid;
    NSString * _orderid;
}
//@property (nonatomic,retain) NSNumber * orderid;
@property (nonatomic,retain) NSString * orderid;

@end

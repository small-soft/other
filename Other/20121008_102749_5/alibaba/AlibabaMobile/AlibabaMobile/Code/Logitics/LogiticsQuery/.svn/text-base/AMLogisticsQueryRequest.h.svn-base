//
//  AMLogisticsQueryRequest.h
//  AlibabaMobile
//
//  Created by  on 12-1-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_LOGISTICS_QUERY ([@"/trade.logis.listTraceInfo/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_ORDER_LOGISTICS_QUERY ([@"/trade.logis.findLogisSimpleOrder/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMLogisticsQueryRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {
    NSInteger _transactionType;
    
    NSString * _companyId;
    NSString * _deliveryId;
    NSString * _logisticsId;
}

/**
 * For transation type
 */
@property (nonatomic) NSInteger transactionType;

/**
 * Company ID
 */
@property(nonatomic, retain) NSString * companyId;

/**
 * Delivery ID
 */
@property(nonatomic, retain) NSString * deliveryId;

/**
 * logisticsId ID, for my order logistics query
 */
@property(nonatomic, retain) NSString * logisticsId;

@end

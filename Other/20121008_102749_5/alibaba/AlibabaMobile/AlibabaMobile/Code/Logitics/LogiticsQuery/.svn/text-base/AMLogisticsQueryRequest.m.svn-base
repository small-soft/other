//
//  AMLogisticsQueryRequest.m
//  AlibabaMobile
//
//  Created by  on 12-1-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMLogisticsQueryRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMLogisticsQueryRequest

@synthesize transactionType = _transactionType;
@synthesize companyId = _companyId;
@synthesize deliveryId = _deliveryId;
@synthesize logisticsId = _logisticsId;

- (NSString*)description {
    return [NSString stringWithFormat:@"Company: %@ (Delivery ID: %@); Logistic ID: %@", self.companyId, self.deliveryId], self.logisticsId;
}

// Impliment RKRequestSerializable delegate methods here  

/**
 * The value of the Content-Type header for the HTTP Body representation of the serialization
 */
- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {
    
    // Create NSDictionary object and setObject to it
    NSString * resourcePath = OCEAN_API_URL_LOGISTICS_QUERY;
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    if ([self transactionType] == AMTRANSACTION_TYPE_FAVORITE_LOGISTICS_TRACESTEP) {
        [params setObject: [self companyId] forKey: @"logisticsCompanyId"];
        [params setObject: [self deliveryId] forKey: @"mailNo"];
    } else if ([self transactionType] == AMTRANSACTION_TYPE_QUERY_LOGIS_SIMPLE_ORDER) {
        resourcePath = OCEAN_API_URL_ORDER_LOGISTICS_QUERY;
        [params setObject: [self logisticsId] forKey: @"logisticsID"];
    }
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX_PARAM resourcePath:resourcePath params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void)dealloc {
    [_companyId release];
    [_deliveryId release];
    [_logisticsId release];
    
    [super dealloc];
}

@end

//
//  AMMylogisticsOrder.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMObjectMappingDelegate.h"

@interface AMMylogisticsOrder : NSObject<AMObjectMappingDelegate>

@property(nonatomic, retain) NSString * aliUID;
@property(nonatomic, retain) NSString * tradeOrderId;
@property(nonatomic, retain) NSString * cargoName;
@property(nonatomic, retain) NSString * logisticsCorpName;
@property(nonatomic, retain) NSString * logisticsCompanyid;
@property(nonatomic, retain) NSString * mailNo;
@property(nonatomic, retain) NSString * receiverName;
@property(nonatomic, retain) NSString * receiverCorpName;
@property(nonatomic, retain) NSString * logisticsID;

@end


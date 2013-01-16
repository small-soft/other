//
//  AMMylogisticsOrder.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMylogisticsOrder.h"

@implementation AMMylogisticsOrder
@synthesize aliUID=_aliUID,tradeOrderId=_tradeOrderId,cargoName=_cargoName,
logisticsCorpName = _logisticsCorpName,logisticsCompanyid=_logisticsCompanyid,
mailNo=_mailNo,receiverName=_receiverName,
receiverCorpName=_receiverCorpName,logisticsID=_logisticsID;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMylogisticsOrder class]] retain];
			[sharedObjectMapping mapKeyPath:@"aliUID" toAttribute:@"aliUID"];
			[sharedObjectMapping mapKeyPath:@"tradeOrderId" toAttribute:@"tradeOrderId"];
			[sharedObjectMapping mapKeyPath:@"cargoName" toAttribute:@"cargoName"];
			[sharedObjectMapping mapKeyPath:@"logisticsCorpName" toAttribute:@"logisticsCorpName"];
			[sharedObjectMapping mapKeyPath:@"logisticsCompanyid" toAttribute:@"logisticsCompanyid"];
			[sharedObjectMapping mapKeyPath:@"mailNo" toAttribute:@"mailNo"];
			[sharedObjectMapping mapKeyPath:@"receiverName" toAttribute:@"receiverName"];
			[sharedObjectMapping mapKeyPath:@"receiverCorpName" toAttribute:@"receiverCorpName"];
			[sharedObjectMapping mapKeyPath:@"logisticsID" toAttribute:@"logisticsID"];
			
        }
    }
    
    return sharedObjectMapping;
}
-(void)dealloc
{
    [_aliUID release];
    [_tradeOrderId release];
    [_cargoName release];
    [_logisticsCorpName release];
    [_logisticsCompanyid release];
    [_mailNo release];
    [_receiverName release];
    [_receiverCorpName release];
    [_logisticsID release];
    [super dealloc];
}
@end

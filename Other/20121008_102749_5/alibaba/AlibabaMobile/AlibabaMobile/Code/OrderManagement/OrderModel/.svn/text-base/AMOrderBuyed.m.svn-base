//
//  AMOrderBuyed.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-8-30.
//
//NSNumber *_orderId;//订单号
//NSNumber *_gmtModified;//下单时间
//NSString *_entryStatus;//订单状态
//NSNumber *_sumPayment;//实付款
//NSString *_buyerCompanyName;//卖家
//NSArray *_orderEntries;

#import "AMOrderBuyed.h"

@implementation AMOrderBuyed
@synthesize identifier = _identifier;
@synthesize gmtModified = _gmtModified;
@synthesize entryStatus = _entryStatus;
@synthesize sumPayment = _sumPayment;
@synthesize buyerCompanyName = _buyerCompanyName;
@synthesize orderEntries = _orderEntries;
@synthesize status = _status;
@synthesize totalCount = _totalCount;
@synthesize sellerCompanyName = _sellerCompanyName;

-(void) dealloc
{
    [_identifier release];
    [_gmtModified release];
    [_entryStatus release];
    [_sumPayment release];
    [_buyerCompanyName release];
    [_orderEntries release];
    [_status release];
    [_totalCount release];
    [_sellerCompanyName release];
    [super dealloc];
}

+ (RKObjectMapping *)sharedObjectMapping
{
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderBuyed class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"gmtModified" toAttribute:@"gmtModified"];
            [sharedObjectMapping mapKeyPath:@"entryStatus" toAttribute:@"entryStatus"];
			[sharedObjectMapping mapKeyPath:@"sumPayment" toAttribute:@"sumPayment"];
            [sharedObjectMapping mapKeyPath:@"status" toAttribute:@"status"];
            [sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
            [sharedObjectMapping mapKeyPath:@"sellerCompanyName" toAttribute:@"sellerCompanyName"];//买家名称
            [sharedObjectMapping mapKeyPath:@"buyerCompanyName" toAttribute:@"buyerCompanyName"];
            [sharedObjectMapping mapKeyPath:@"orderEntries" toAttribute:@"orderEntries"];
        }
    }
    
    return sharedObjectMapping;
}
@end

//
//  AMOrderModel.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderModel.h"


@implementation AMOrderModel


@synthesize Id=_Id;
@synthesize gmtCreate=_gmtCreate;
@synthesize sumPayment=_sumPayment;
@synthesize status=_status;

@synthesize carriage=_carriage;


@synthesize buyerCompanyName=_buyerCompanyName;
@synthesize sellerCompanyName=_sellerCompanyNamel;
@synthesize buyerMemberId=_buyerMemberId;
@synthesize sellerMemberId=_sellerMemberId;
@synthesize buyerAlipayLoginId=_buyerAlipayLoginId;
@synthesize sellerAlipayLoginId=_sellerAlipayLoginId;

@synthesize buyerName=_buyerName;
@synthesize buyerMobile=_buyerMobile;
@synthesize buyerPhone=_buyerPhone;
@synthesize toArea=_toArea;

@synthesize orderInvoiceModel=_orderInvoiceModel;
@synthesize orderEntries=_orderEntries;
@synthesize logisticsOrderList = _logisticsOrderList;

@synthesize buyerFeedback=_buyerFeedback;
@synthesize orderProtocalModel=_orderProtocolModel;

-(void)dealloc{
    [_Id release];
    _Id = nil;
    [_gmtCreate release];
    _gmtCreate = nil;
    [_sumPayment release] ;
    _sumPayment = nil;
    [_status release];
    _status = nil;
    
    [_carriage release];
    _carriage = nil;
    
    [_buyerCompanyName release];
    _buyerCompanyName=nil;
    [_sellerCompanyNamel release];
    _sellerCompanyNamel = nil;
    [_buyerMemberId release]; 
    _buyerMemberId = nil;
    [_sellerMemberId release];
    _sellerMemberId  = nil;
    [_buyerAlipayLoginId release];
    _buyerAlipayLoginId = nil;
    [_sellerAlipayLoginId release];
    _sellerAlipayLoginId = nil;
    
    [_buyerName release];
    _buyerName = nil;
    [_buyerMobile release];
    _buyerMobile = nil;
    [_buyerPhone release];
    _buyerPhone = nil;
    [_toArea release];
    _toArea = nil;
    
    [_orderInvoiceModel release];
    _orderInvoiceModel = nil;
    [_orderEntries release];
    _orderEntries = nil;
    [_logisticsOrderList release];
    _logisticsOrderList = nil;
    
    [_buyerFeedback release];
    _buyerFeedback = nil;
    [_orderProtocolModel release];
    _orderProtocolModel = nil;
    
    [super dealloc];
}

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;

    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderModel class]] retain];
        
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"Id"];
            [sharedObjectMapping mapKeyPath:@"gmtCreate" toAttribute:@"gmtCreate"];
            [sharedObjectMapping mapKeyPath:@"sumPayment" toAttribute:@"sumPayment"];
            [sharedObjectMapping mapKeyPath:@"status" toAttribute:@"status"];
            [sharedObjectMapping mapKeyPath:@"carriage" toAttribute:@"carriage"];
            [sharedObjectMapping mapKeyPath:@"buyerCompanyName" toAttribute:@"buyerCompanyName"];
            [sharedObjectMapping mapKeyPath:@"sellerCompanyName" toAttribute:@"sellerCompanyName"];
            [sharedObjectMapping mapKeyPath:@"buyerMemberId" toAttribute:@"buyerMemberId"];
            [sharedObjectMapping mapKeyPath:@"sellerMemberId" toAttribute:@"sellerMemberId"];
            [sharedObjectMapping mapKeyPath:@"buyerAlipayLoginId" toAttribute:@"buyerAlipayLoginId"];
            [sharedObjectMapping mapKeyPath:@"sellerAlipayLoginId" toAttribute:@"sellerAlipayLoginId"];
            [sharedObjectMapping mapKeyPath:@"buyerName" toAttribute:@"buyerName"];
            [sharedObjectMapping mapKeyPath:@"buyerMobile" toAttribute:@"buyerMobile"];
            [sharedObjectMapping mapKeyPath:@"buyerPhone" toAttribute:@"buyerPhone"];
            [sharedObjectMapping mapKeyPath:@"toArea" toAttribute:@"toArea"];
            
            [sharedObjectMapping mapKeyPath:@"buyerFeedback" toAttribute:@"buyerFeedback"];

            [sharedObjectMapping mapRelationship:@"orderInvoiceModel" withMapping:[AMOrderInvoiceModel sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"orderEntries" withMapping:[AMOrderEntryModel sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"logisticsOrderList" withMapping:[AMOrderLogisticsModel sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"orderProtocalModel" withMapping:[AMOrderProtocolModel sharedObjectMapping]];
            
            
            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMOrderInvoiceModel sharedObjectMapping] forKeyPath:@"orderInvoiceModel"];
            [mappingProvider setMapping:[AMOrderEntryModel sharedObjectMapping] forKeyPath:@"orderEntries"];
            [mappingProvider setMapping:[AMOrderLogisticsModel sharedObjectMapping] forKeyPath:@"logisticsOrderList"];
            [mappingProvider setMapping:[AMOrderProtocolModel sharedObjectMapping] forKeyPath:@"orderProtocalModel"];
        
        }
    }

    return sharedObjectMapping;

}

@end

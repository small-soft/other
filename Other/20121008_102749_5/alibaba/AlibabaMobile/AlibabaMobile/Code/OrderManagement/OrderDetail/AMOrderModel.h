//
//  AMOrderModel.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMOrderInvoiceModel.h"
#import "AMOrderEntryModel.h"
#import "AMOrderLogisticsModel.h"
#import "AMOrderProtocolModel.h"

@interface AMOrderModel : NSObject<AMObjectMappingDelegate>
{
    //基本信息
    NSNumber * _Id;
    NSNumber * _gmtCreate;
    NSNumber * _sumPayment;
    NSString * _status;
    
    NSNumber * _carriage;

    
    NSString * _buyerCompanyName;
    NSString * _sellerCompanyName;
    NSString * _buyerMemberId;
    NSString * _sellerMemberId;
    NSString * _buyerAlipayLoginId;
    NSString * _sellerAlipayLoginId;
    
    NSString * _buyerName;
    NSString * _buyerMobile;
    NSString * _buyerPhone;
    NSString * _toArea;
    
    NSArray * _orderEntries;
    AMOrderInvoiceModel * _orderInvoiceModel;
    
    
    NSString * _buyerFeedback;
    AMOrderProtocolModel * _orderProtocolModel;
    
    
    
}


@property (nonatomic,retain) NSNumber * Id;
@property (nonatomic,retain) NSNumber * gmtCreate;
@property (nonatomic,retain) NSNumber * sumPayment;
@property (nonatomic,retain) NSString * status;

@property (nonatomic,retain) NSNumber * carriage;


@property (nonatomic,retain) NSString * buyerCompanyName;
@property (nonatomic,retain) NSString * sellerCompanyName;
@property (nonatomic,retain) NSString * buyerMemberId;
@property (nonatomic,retain) NSString * sellerMemberId;
@property (nonatomic,retain) NSString * buyerAlipayLoginId;
@property (nonatomic,retain) NSString * sellerAlipayLoginId;

@property (nonatomic,retain) NSString * buyerName;
@property (nonatomic,retain) NSString * buyerMobile;
@property (nonatomic,retain) NSString * buyerPhone;
@property (nonatomic,retain) NSString * toArea;

@property (nonatomic,retain) AMOrderInvoiceModel * orderInvoiceModel;
@property (nonatomic, retain) NSArray * logisticsOrderList;
@property (nonatomic,retain) NSArray * orderEntries;

@property (nonatomic,retain) NSString * buyerFeedback;
@property (nonatomic,retain) AMOrderProtocolModel * orderProtocalModel;

@end

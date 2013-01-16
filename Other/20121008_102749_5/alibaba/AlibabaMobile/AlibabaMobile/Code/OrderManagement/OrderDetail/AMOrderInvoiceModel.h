//
//  AMOrderInvoiceModel.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"


@interface AMOrderInvoiceModel : NSObject<AMObjectMappingDelegate>
{
    NSString * _invoiceCompanyName;
    NSString * _taxpayerIdentify;
    NSString * _bankAndAccount;
    NSString * _receivePhone;
    NSString * _receiveAddress;
}


@property (nonatomic,retain) NSString * invoiceCompanyName;
@property (nonatomic,retain) NSString * taxpayerIdentify;
@property (nonatomic,retain) NSString * bankAndAccount;
@property (nonatomic,retain) NSString * receivePhone;
@property (nonatomic,retain) NSString * receiveAddress;


@end

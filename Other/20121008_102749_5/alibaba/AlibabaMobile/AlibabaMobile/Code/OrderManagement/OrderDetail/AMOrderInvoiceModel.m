//
//  AMOrderInvoiceModel.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderInvoiceModel.h"


@implementation AMOrderInvoiceModel


@synthesize invoiceCompanyName=_invoiceCompanyName;
@synthesize taxpayerIdentify=_taxpayerIdentify;
@synthesize bankAndAccount=_bankAndAccount;
@synthesize receivePhone=_receivePhone;
@synthesize receiveAddress=_receiveAddress;

-(void)dealloc{
    [_invoiceCompanyName release];
    _invoiceCompanyName  = nil;
    [_taxpayerIdentify release];
    _taxpayerIdentify = nil;
    [_bankAndAccount release];
    _bankAndAccount = nil;
    [_receivePhone release];
    _receivePhone = nil;
    [_receiveAddress release];
    _receiveAddress = nil;
    
    [super dealloc];
}



+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderInvoiceModel class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"invoiceCompanyName" toAttribute:@"invoiceCompanyName"];
            [sharedObjectMapping mapKeyPath:@"taxpayerIdentify" toAttribute:@"taxpayerIdentify"];
            [sharedObjectMapping mapKeyPath:@"bankAndAccount" toAttribute:@"bankAndAccount"];
            [sharedObjectMapping mapKeyPath:@"receivePhone" toAttribute:@"receivePhone"];
            [sharedObjectMapping mapKeyPath:@"receiveAddress" toAttribute:@"receiveAddress"];
           
            
//            [sharedObjectMapping mapRelationship:@"orderInvoiceModel" withMapping:[AMOrderInvoiceModel sharedObjectMapping]];
//            
//            
//            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//            [mappingProvider setMapping:[AMOrderInvoiceModel sharedObjectMapping] forKeyPath:@"orderInvoiceModel"];
            
            
            
        }
    }
    
    return sharedObjectMapping;
    
}

@end

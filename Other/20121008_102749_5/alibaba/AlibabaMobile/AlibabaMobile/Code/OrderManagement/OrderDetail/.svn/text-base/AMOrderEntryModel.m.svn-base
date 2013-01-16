//
//  AMOrderEntryModel.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderEntryModel.h"
#import "AMSpecItem.h"

@implementation AMOrderEntryModel

@synthesize mainSummImageUrl=_mainSummImageUrl;
@synthesize productName=_productName;


@synthesize  unit=_unit;
@synthesize  entryDiscount=_entryDiscount;
@synthesize  entryCouponAmount=_entryCouponAmount;
@synthesize  discountPrice=_discountPrice;
@synthesize  quantity=_quantity;

@synthesize  specItems=_specItems;

-(void) dealloc
{
    [_productName release];
    [_mainSummImageUrl release];
    
    [_unit release];
    [_entryDiscount release];
    [_entryCouponAmount release]; 
    [_discountPrice release];
    [_quantity release];
    
    [_specItems release];
    
    _productName = nil;
    _mainSummImageUrl= nil;
    
    _unit= nil;
    _entryDiscount= nil;
    _entryCouponAmount= nil;
    _discountPrice= nil;
    _quantity= nil;
    
    _specItems= nil;

    
    [super dealloc];
}


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderEntryModel class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"mainSummImageUrl" toAttribute:@"mainSummImageUrl"];
            [sharedObjectMapping mapKeyPath:@"productName" toAttribute:@"productName"];
            [sharedObjectMapping mapKeyPath:@"unit" toAttribute:@"unit"];
            [sharedObjectMapping mapKeyPath:@"entryDiscount" toAttribute:@"entryDiscount"];
            [sharedObjectMapping mapKeyPath:@"entryCouponAmount" toAttribute:@"entryCouponAmount"];
            [sharedObjectMapping mapKeyPath:@"discountPrice" toAttribute:@"discountPrice"];
            [sharedObjectMapping mapKeyPath:@"quantity" toAttribute:@"quantity"];

                        
            
            [sharedObjectMapping mapRelationship:@"specItems" withMapping:[AMSpecItem sharedObjectMapping]];
            //            
            //            
            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMSpecItem sharedObjectMapping] forKeyPath:@"specItems"];
            
            
            
        }
    }
    
    return sharedObjectMapping;
    
}

@end

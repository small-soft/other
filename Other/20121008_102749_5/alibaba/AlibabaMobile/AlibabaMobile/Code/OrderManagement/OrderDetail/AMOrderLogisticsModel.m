//
//  AMOrderLogisticsModel.m
//  AlibabaMobile
//
//  Created by alimobile on 12-9-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderLogisticsModel.h"
#import "AMSpecItem.h"


@implementation AMOrderLogisticsModel

@synthesize toContact = _toContact;
@synthesize logisticsBillNo = _logisticsBillNo;
@synthesize logisticsCompany = _logisticsCompany;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderLogisticsModel class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"toContact" toAttribute:@"toContact"];
            [sharedObjectMapping mapKeyPath:@"logisticsBillNo" toAttribute:@"logisticsBillNo"];
            
            
            [sharedObjectMapping mapRelationship:@"logisticsCompany" withMapping:[AMOrderLogisticsCompanyModel sharedObjectMapping]];
            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMOrderLogisticsCompanyModel sharedObjectMapping] forKeyPath:@"logisticsCompany"];
            
            
            
        }
    }
    
    return sharedObjectMapping;
    
}

- (void) dealloc{
    [_toContact release];
    [_logisticsBillNo release];
    [_logisticsCompany release];
    [super dealloc];
}

@end

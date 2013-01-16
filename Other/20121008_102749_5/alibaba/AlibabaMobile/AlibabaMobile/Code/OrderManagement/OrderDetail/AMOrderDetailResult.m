//
//  AMOrderDetailResult.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderDetailResult.h"
#import "AMObjectMappingDelegate.h"
#import "AMOrderModel.h"

@implementation AMOrderDetailResult

@synthesize orderModel=_orderModel;
@synthesize success=_success;

-(void)dealloc
{
    [_orderModel release];
    _orderModel = nil;
    [_success release];
    _success = nil;
    
    [super dealloc];
}


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderDetailResult class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
                        
            [sharedObjectMapping mapRelationship:@"orderModel" withMapping:[AMOrderModel sharedObjectMapping]];
            
                       
            //            			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMOrderModel sharedObjectMapping] forKeyPath:@"orderModel"];
			
            
            
        }
    }
    
    return sharedObjectMapping;
}


@end

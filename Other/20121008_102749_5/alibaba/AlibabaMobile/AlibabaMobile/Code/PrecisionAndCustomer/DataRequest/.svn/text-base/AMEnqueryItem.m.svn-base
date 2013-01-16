//
//  EnqueryItem.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMEnqueryItem.h"

#import "AMEnqueryProductItem.h"

@implementation AMEnqueryItem



@synthesize enquiriesSource=_enquiriesSource;
@synthesize sendedSample=_sendedSample;
@synthesize enquiriesDate=_enquiriesDate;
@synthesize status=_status;
@synthesize enquiriesId=_enquiriesId;
@synthesize sendedQuotation=_sendedQuotation;
@synthesize productItems=_productItems;
@synthesize intent=_intent;

@synthesize memo=_memo;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMEnqueryItem class]] retain];
            
            
            [sharedObjectMapping mapKeyPath:@"enquiriesSource" toAttribute:@"enquiriesSource"];
            [sharedObjectMapping mapKeyPath:@"sendedSample" toAttribute:@"sendedSample"];
            [sharedObjectMapping mapKeyPath:@"enquiriesDate" toAttribute:@"enquiriesDate"];
            [sharedObjectMapping mapKeyPath:@"status" toAttribute:@"status"];
            [sharedObjectMapping mapKeyPath:@"enquiriesId" toAttribute:@"enquiriesId"];
            [sharedObjectMapping mapKeyPath:@"sendedQuotation" toAttribute:@"sendedQuotation"];
//            [sharedObjectMapping mapKeyPath:@"productItems" toAttribute:@"productItems"];
            [sharedObjectMapping mapKeyPath:@"intent" toAttribute:@"intent"];
            [sharedObjectMapping mapKeyPath:@"memo" toAttribute:@"memo"];
            
            [sharedObjectMapping mapRelationship:@"productItems" withMapping:[AMEnqueryProductItem sharedObjectMapping]];
            
            
           
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMEnqueryProductItem sharedObjectMapping] forKeyPath:@"productItems"];
                      
        }
    }
    
    return sharedObjectMapping;
}


@end

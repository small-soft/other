//
//  EnqueryProductItem.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMEnqueryProductItem.h"

 

@implementation AMEnqueryProductItem


@synthesize itemId=_itemId;
@synthesize productName=_productName;
@synthesize price=_price;
@synthesize quantity=_quantity;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMEnqueryProductItem class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"itemId" toAttribute:@"itemId"];
            [sharedObjectMapping mapKeyPath:@"productName" toAttribute:@"productName"];
            [sharedObjectMapping mapKeyPath:@"price" toAttribute:@"price"];
            [sharedObjectMapping mapKeyPath:@"quantity" toAttribute:@"quantity"];
            
            
        }
    }
    
    return sharedObjectMapping;
}


@end

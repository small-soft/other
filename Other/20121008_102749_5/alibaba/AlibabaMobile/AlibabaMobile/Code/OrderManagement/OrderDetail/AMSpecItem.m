//
//  AMSpecItem.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//产品属性


#import "AMSpecItem.h"

@implementation AMSpecItem
@synthesize  specName=_specName;
@synthesize specValue=_specValue;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSpecItem class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"specName" toAttribute:@"specName"];
            [sharedObjectMapping mapKeyPath:@"specValue" toAttribute:@"specValue"];
            
            
  
            
            
            
        }
    }
    
    return sharedObjectMapping;
    
}


@end

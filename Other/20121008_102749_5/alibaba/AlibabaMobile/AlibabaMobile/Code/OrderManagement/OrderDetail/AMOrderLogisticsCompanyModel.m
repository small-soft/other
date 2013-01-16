//
//  AMOrderLogisticsCompanyModel.m
//  AlibabaMobile
//
//  Created by alimobile on 12-9-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderLogisticsCompanyModel.h"
#import "AMSpecItem.h"


@implementation AMOrderLogisticsCompanyModel

@synthesize companyName = _companyName;
@synthesize companyNo = _companyNo;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderLogisticsCompanyModel class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"companyName" toAttribute:@"companyName"];
            [sharedObjectMapping mapKeyPath:@"companyNo" toAttribute:@"companyNo"];
        }
    }
    
    return sharedObjectMapping;
    
}

- (void) dealloc{
    [_companyName release];
    [_companyNo release];
    [super dealloc];
}

@end

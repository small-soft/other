//
//  AMCustomerSuggestListMainModel.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCustomerSuggestStatResult : NSObject <AMObjectMappingDelegate> {
    
    NSNumber *unPotentialEnquiryCount;//错过询盘
    NSNumber *potentialEnquiryCount;//潜在询盘
    NSNumber *freeHavedImported;
    
}

@property(nonatomic, retain) NSNumber *unPotentialEnquiryCount;
@property(nonatomic, retain) NSNumber *potentialEnquiryCount;
@property(nonatomic, retain) NSNumber *freeHavedImported;

@end

//
//  AMCustomerSuggestListResult.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCustomerSuggestListResult : NSObject <AMObjectMappingDelegate> {

    NSNumber *_totalCount;
    NSArray * _resultList;
}

@property(nonatomic, retain) NSNumber * totalCount;
@property(nonatomic, retain) NSArray  * resultList;

@end

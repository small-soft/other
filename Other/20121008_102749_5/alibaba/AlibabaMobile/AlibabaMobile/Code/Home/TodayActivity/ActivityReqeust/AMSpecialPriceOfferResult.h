//
//  AMSpecialPriceOfferResult.h
//  AlibabaMobile
//
//  Created by amon on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
@interface AMSpecialPriceOfferResult : NSObject<AMObjectMappingDelegate>{
    NSNumber *_totalCount;
    NSArray *_resultList;
    
    
}

@property (nonatomic,retain) NSNumber *totalCount;
@property (nonatomic,retain) NSArray *resultList;

@end

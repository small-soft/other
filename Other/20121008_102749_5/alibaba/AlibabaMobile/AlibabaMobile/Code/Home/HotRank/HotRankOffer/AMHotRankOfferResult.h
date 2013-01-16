//
//  AMHotRankOfferResult.h
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
/**
 热销排行--产品
 */
@interface AMHotRankOfferResult : NSObject<AMObjectMappingDelegate>{
    NSNumber *_total;
    NSArray *_offerList;
    
    
}

@property (nonatomic,retain) NSNumber *total;
@property (nonatomic,retain) NSArray *offerList;

@end

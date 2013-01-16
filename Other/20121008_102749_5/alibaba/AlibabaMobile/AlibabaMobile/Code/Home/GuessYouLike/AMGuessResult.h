//
//  AMGuessResult.h
//  AlibabaMobile
//
//  Created by amon on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMObjectMappingDelegate.h"
#import "AMOffer.h"

@interface AMGuessResult : NSObject <AMObjectMappingDelegate> {
    
    NSArray * _offerList;
    NSString * ctrIds;
    NSString *recId;
    
}

@property(nonatomic, retain)  NSArray * offerList;
@property(nonatomic, retain)  NSString * ctrIds;
@property(nonatomic, retain)  NSString *recId;;

@end

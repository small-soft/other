//
//  AMCurrency.h
//  AlibabaMobile
//
//  Created by  on 12-1-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCurrency : NSObject <AMObjectMappingDelegate> {
    NSNumber * _defaultFractionDigits;
    NSString * _currencyCode;
    NSString * _symbol;
}

@property (nonatomic, retain) NSNumber * defaultFractionDigits;
@property (nonatomic, retain) NSString * currencyCode;
@property (nonatomic, retain) NSString * symbol;

@end

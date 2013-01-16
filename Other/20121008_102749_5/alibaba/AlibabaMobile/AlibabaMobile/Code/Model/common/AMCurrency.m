//
//  AMCurrency.m
//  AlibabaMobile
//
//  Created by  on 12-1-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCurrency.h"

@implementation AMCurrency

@synthesize defaultFractionDigits = _defaultFractionDigits;
@synthesize currencyCode = _currencyCode;
@synthesize symbol = _symbol;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCurrency class]] retain];
            [sharedObjectMapping mapKeyPath:@"defaultFractionDigits" toAttribute:@"defaultFractionDigits"];
            [sharedObjectMapping mapKeyPath:@"currencyCode" toAttribute:@"currencyCode"];
            [sharedObjectMapping mapKeyPath:@"symbol" toAttribute:@"symbol"];
        }
    }
    
    return sharedObjectMapping;
}

-(void) dealloc {
    [_defaultFractionDigits release];
    [_currencyCode release];
    [_symbol release];
    
    [super dealloc];
}

@end

//
//  AliKeyValueCell.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-2-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliKeyValueCellForInvoice.h"

@implementation AliKeyValueCellForInvoice

@synthesize keyLabel = _keyLabel;
@synthesize valueLabel = _valueLabel;
@synthesize seceptorImageView = _seceptorImageView;
@synthesize iconImageView = _iconImageView;


-(void) dealloc
{
    [_keyLabel  release];
    [_valueLabel release];
    [_seceptorImageView release];
    [_iconImageView release];
    
    [super dealloc];
}

@end

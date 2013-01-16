//
//  AMIMUserInfoTableCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-14.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMUserInfoTableCell.h"

@implementation AMIMUserInfoTableCell

@synthesize keyLabel = _keyLabel;
@synthesize valueLabel = _valueLabel;


-(void) dealloc
{
    [_keyLabel release];
    [_valueLabel release];
    
    [super dealloc];
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code
    }
    return self;
}



@end

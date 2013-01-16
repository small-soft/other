//
//  AMSimpleCell.m
//  AlibabaMobile
//
//  Created by lih on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSimpleCell.h"

@implementation AMSimpleCell
@synthesize leftLabel=_leftLabel;
@synthesize middleLabel=_middleLabel;
@synthesize rightLabel=_rightLabel;

+(CGFloat)cellHeight
{
    return 44.0;
}

+(NSString*)cellIdentifer
{
    return @"AmSimpleCell";
}

- (void)dealloc {   
    [_leftLabel release];
    [_middleLabel release];
    [_rightLabel release];
    [super dealloc];
}

@end

//
//  AliPageControl.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliPageControl.h"

@implementation AliPageControl

-(id) initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    [self setCurrentPage:1];
    return self;
}

-(id) init
{
    self = [super init];
    [self setCurrentPage:1];
    return self;
}



-(void) updateDots
{
    for (int i = 0; i < [self.subviews count]; i++)
    {
        UIImageView* dot = [self.subviews objectAtIndex:i];

        dot.frame = CGRectMake(dot.frame.origin.x,dot.frame.origin.y,6,6);
        if (i == self.currentPage) dot.image = [UIImage imageNamed:@"icon_Main_slidercircle_focus"];
        else dot.image = [UIImage imageNamed:@"icon_Main_slidercircle.png"];
    }
}

-(void) setCurrentPage:(NSInteger)page
{
    [super setCurrentPage:page];
    [self updateDots];
}

- (void)endTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event { // 点击事件
    [super endTrackingWithTouch:touch withEvent:event];
    [self updateDots];
}

-(void)dealloc
{
    [super dealloc];
}

@end

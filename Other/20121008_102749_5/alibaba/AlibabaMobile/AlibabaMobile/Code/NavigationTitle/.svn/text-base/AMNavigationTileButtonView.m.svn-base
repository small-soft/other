//
//  AMNavigationTileButtonView.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNavigationTileButtonView.h"
#import "UIHelp.h"

@implementation AMNavigationTileButtonView

@synthesize titleButton=_titleButton;
@synthesize arrowButton=_arrowButton;

- (void) setTitle:(NSString *)title
{
    self.titleButton.titleLabel.shadowColor = [UIColor blackColor];
    self.titleButton.titleLabel.shadowOffset = CGSizeMake(0, -1);
    int titleWidth = [UIHelp getLabelSizeWithFont:self.titleButton.titleLabel.font labelString:title labelHeight:self.titleButton.frame.size.height].width;
    [self.titleButton setTitle:title forState:UIControlStateNormal];
    
    self.titleButton.frame = CGRectMake(self.arrowButton.frame.size.width, self.titleButton.frame.origin.y, titleWidth, self.titleButton.frame.size.height);
    self.arrowButton.frame = CGRectMake(self.titleButton.frame.origin.x + self.titleButton.frame.size.width , self.arrowButton.frame.origin.y, self.arrowButton.frame.size.width, self.arrowButton.frame.size.height);
    self.frame = CGRectMake(0, self.frame.origin.y, self.titleButton.frame.size.width + self.arrowButton.frame.size.width*2 , self.frame.size.height);
    
}


-(void)dealloc
{
    [_titleButton release];
    [_titleButton release];
    [super dealloc];
}

@end

//
//  MessageTypeListCell.m
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 12-5-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MessageTypeListCell.h"
#import "UIHelp.h"

@interface MessageTypeListCell()

@end

@implementation MessageTypeListCell

@synthesize mTitleLabel = _mTitleLabel;

- (void) setTitle:(NSString *)title
{
    self.mTitleLabel.text = title;
    //int titleLabelHeight = [UIHelp getLabelSizeWithFont:self.mTitleLabel.font labelString:self.mTitleLabel.text labelWidth:self.mTitleLabel.frame.size.width].height;
    self.mTitleLabel.frame = CGRectMake(self.mTitleLabel.frame.origin.x, self.mTitleLabel.frame.origin.y, self.mTitleLabel.frame.size.width, 45);
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, 45);
}

-(void)dealloc
{
    [_mTitleLabel release];
    
    [super dealloc];
}

@end

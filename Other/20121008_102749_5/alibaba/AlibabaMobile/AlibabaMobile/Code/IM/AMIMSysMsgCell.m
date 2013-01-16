//
//  AMIMSysMsgCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMSysMsgCell.h"
#import "UIHelp.h"

@implementation AMIMSysMsgCell

@synthesize titleLabel = _titleLabel;
@synthesize timeLabel = _timeLabel;
@synthesize msgLabel = _msgLabel;
@synthesize bkImgView = _bkImgView;

- (void) dealloc
{
    [_titleLabel release];
    [_timeLabel release];
    [_msgLabel release];
    [_bkImgView release];
    
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

- (void) setMsg:(NSString *)msg
{
    _msgLabel.text = msg;
    int height = [UIHelp getLabelSizeWithFont:_msgLabel.font labelString:msg labelWidth:_msgLabel.frame.size.width].height;
    _msgLabel.frame = CGRectMake(_msgLabel.frame.origin.x, _msgLabel.frame.origin.y, _msgLabel.frame.size.width, height);
    
    int bkImgHeight = 46 + height;
    _bkImgView.frame = CGRectMake(_bkImgView.frame.origin.x, _bkImgView.frame.origin.y, _bkImgView.frame.size.width, bkImgHeight);
    
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, bkImgHeight + 10);
    
}


@end

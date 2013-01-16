//
//  AMIMMsgCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-22.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMMsgCell.h"
#import "UIHelp.h"

@implementation AMIMMsgCell

@synthesize headImg = _headImg;
@synthesize msgLabel = _msgLabel;
@synthesize timeLabel= _timeLabel;

- (id)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void) dealloc
{
    [_headImg release];
    [_msgLabel release];
    [_timeLabel release];
    
    [super dealloc];
}

- (void) setText:(NSString *) text
{
//{
//    _msgLabel.text = text;
//    _msgLabel.numberOfLines = 0;
//    
//    int labelWidth = [UIHelp getLabelSizeWithFont:_msgLabel.font labelString:text labelHeight:16].width;
//    labelWidth = (labelWidth > 200 ? 200 : labelWidth);
//    int labelHeight = [UIHelp getLabelSizeWithFont:_msgLabel.font labelString:text labelWidth:labelWidth].height;
//    _msgLabel.frame = CGRectMake(80, 20, labelWidth, labelHeight);
    [_msgLabel setContentStr:text];
   
    int labelWidth = _msgLabel.frame.size.width;
    int labelHeight = _msgLabel.frame.size.height;
    
    _msgLabel.frame =  CGRectMake(80, 32, labelWidth, labelHeight);
    
    UIImageView * bkImgView = [[UIImageView alloc] init];
    bkImgView.frame = CGRectMake(60, 22, labelWidth+40, labelHeight + 20);
    bkImgView.backgroundColor = [UIColor clearColor];
    
    UIImage * bkImg = [UIImage imageNamed:@"bg_aliww_dailog"];
    bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height*3/4];
    
    bkImgView.image = bkImg;
    
    [self insertSubview:bkImgView atIndex:0];
    [bkImgView release];
    
    int viewHeight = _msgLabel.frame.size.height + 40;
    viewHeight = (viewHeight > 60?viewHeight:60);
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, viewHeight);
}



@end

//
//  AMIMRecentContactCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-22.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMRecentContactCell.h"

@implementation AMIMRecentContactCell

@synthesize headImg = _headImg;
@synthesize nameLabel = _nameLabel;
@synthesize signLabel = _signLabel;
@synthesize timeLabel = _timeLabel;
@synthesize bkImgView = _bkImgView;
@synthesize msgNumLabel = _msgNumLabel;
@synthesize msgNumBkImg = _msgNumBkImg;

- (void)dealloc
{
    [_headImg release];
    [_nameLabel release];
    [_signLabel release];
    [_timeLabel release];
    [_bkImgView release];
    [_msgNumLabel release];
    [_msgNumBkImg release];
    
    [super dealloc];
}

- (id)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void) setNewMsgNum:(int)num
{
    if(num >0){
        NSString * text = [NSString stringWithFormat:@"%d", num];
        _msgNumLabel.text = text;
        [_msgNumLabel sizeToFit];
        
        UIImage * bkImg = [UIImage imageNamed:@"bg_aliww_dialognumber"];
        bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height/2];

        
        _msgNumLabel.frame = CGRectMake(self.frame.size.width - _msgNumLabel.frame.size.width-23, _msgNumLabel.frame.origin.y, _msgNumLabel.frame.size.width, _msgNumLabel.frame.size.height);
       

        _msgNumBkImg.image = bkImg;
        _msgNumBkImg.frame = CGRectMake(_msgNumLabel.frame.origin.x -8, _msgNumLabel.frame.origin.y -1, _msgNumLabel.frame.size.width+16, _msgNumLabel.frame.size.height+2);

    }else{
        _msgNumLabel.hidden = YES;
        _msgNumBkImg.hidden =YES;
    }
   
}

@end

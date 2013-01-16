//
//  AMIMFriendListItemCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

//#import <QuartzCore/QuartzCore.h>
//#import <UIKit/UIKit.h>
#import "AMIMFriendListItemCell.h"


const NSString * IM_FRIEND_LIST_ITEM_CELL_ID = @"im_friend_list_item_cell_id";

@implementation AMIMFriendListItemCell

@synthesize headImg = _headImg;
@synthesize nameLabel = _nameLabel;
@synthesize signLabel = _signLabel;
@synthesize statusImg = _statusImg;
@synthesize detailBtn = _detailBtn;
@synthesize msgNumLabel = _msgNumLabel;

- (void) setHeadInvisible
{
    UIImageView * coverImg = [[UIImageView alloc] initWithFrame:self.headImg.frame];
//    coverImg.layer.masksToBounds = YES;
//    coverImg.layer.cornerRadius = 5.0;
    
    
    coverImg.backgroundColor = [UIColor clearColor];
    coverImg.image = [UIImage imageNamed:@"tx_aliww_detail_mask"];
//    coverImg.alpha = 0.5f;
    
    [self addSubview:coverImg];
    [coverImg release];
}


- (void) setNewMsgNum:(int)num
{
    if(num >0){
        NSString * text = [NSString stringWithFormat:@"%d", num];
        _msgNumLabel.text = text;
        [_msgNumLabel sizeToFit];

        _msgNumLabel.layer.cornerRadius=2;
        _msgNumLabel.frame = CGRectMake(self.frame.size.width - _detailBtn.frame.size.width-28, _msgNumLabel.frame.origin.y, _msgNumLabel.frame.size.width+8, _msgNumLabel.frame.size.height);
        
        _msgNumLabel.hidden = NO;
        
    }else{
        _msgNumLabel.hidden = YES;
    }
    
}

- (void) dealloc
{
    [_headImg release];
    [_nameLabel release];
    [_signLabel release];
    [_statusImg release];
    [_detailBtn release];
    [_msgNumLabel release];
    
    [super dealloc];
}



@end

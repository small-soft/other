//
//  AMIMFriendListItemCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMFriendSearchListItemCell.h"


const NSString * IM_FRIEND_SEARCH_LIST_ITEM_CELL_ID = @"im_friend_search_list_item_cell_id";

@implementation AMIMFriendSearchListItemCell

@synthesize headImg = _headImg;
@synthesize nameLabel = _nameLabel;
@synthesize signLabel = _signLabel;
@synthesize statusImg = _statusImg;
@synthesize detailBtn = _detailBtn;

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

- (void) dealloc
{
    [_headImg release];
    [_nameLabel release];
    [_signLabel release];
    [_statusImg release];
    [_detailBtn release];
    
    [super dealloc];
}



@end

//
//  AMIMFriendListItemCell.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJObjManager.h"
#import "HJManagedImageV.h"
#import "AliParamButton.h"

@interface AMIMFriendSearchListItemCell : UITableViewCell

@property (nonatomic, retain) IBOutlet HJManagedImageV * headImg;
@property (nonatomic, retain) IBOutlet UILabel * nameLabel;
@property (nonatomic, retain) IBOutlet UILabel * signLabel;
@property (nonatomic, retain) IBOutlet UIImageView * statusImg;
@property (nonatomic, retain) IBOutlet AliParamButton * detailBtn;

- (void) setHeadInvisible;

@end

//
//  AMChannelTableViewCell.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-27.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTableViewCell.h"
#import "AliChannelCellBlock.h"
#import "AMMenuView.h"

@interface AMChannelTableViewCell : AliTableViewCell
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@property (retain, nonatomic) IBOutlet AMMenuView *menuView;

@end

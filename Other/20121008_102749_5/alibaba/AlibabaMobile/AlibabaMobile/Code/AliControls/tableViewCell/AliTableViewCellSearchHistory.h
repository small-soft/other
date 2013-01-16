//
//  AliTableViewCellSearchHistory.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliCustomLabel.h"
#import "AliTableViewCell.h"
@interface AliTableViewCellSearchHistory : AliTableViewCell
@property (retain, nonatomic) IBOutlet AliCustomLabel *title;
@property (retain, nonatomic) IBOutlet UIImageView *splitLine;
@property (retain, nonatomic) IBOutlet UIButton *editButton;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end

//
//  AMIndustrySelectHomeCell.h
//  AlibabaMobile
//
//  Created by amon on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
#define AM_INDUSTRY_SELECT_HOME_CELL_HEIGHT 93

@interface AMIndustrySelectHomeCell : UITableViewCell

@property (nonatomic,retain) IBOutlet UIImageView * bkImage;
@property (nonatomic,retain) IBOutlet UIImageView * upTypeImage;
@property (nonatomic,retain) IBOutlet UIImageView * bottomTypeImage;
@property (nonatomic,retain) IBOutlet UIImageView * buttomSeparateImage;
@property (nonatomic,retain) IBOutlet UILabel *typeLabel;
@property (nonatomic,retain) IBOutlet UILabel *introduceLabel;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end

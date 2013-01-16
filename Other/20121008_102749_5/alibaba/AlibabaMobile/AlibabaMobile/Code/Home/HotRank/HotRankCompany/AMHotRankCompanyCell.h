//
//  AMHotRankCompanyCell.h
//  AlibabaMobile
//
//  Created by amon on 12-4-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//NSNumber *_satisfiedRate;//商品满意度
//NSString *companyName;//公司
//NSNumber *_companyPaymentGMV;//交易额
//NSString *_cityName;//城市
//NSNumber *_rankRiseNum;//上升排名

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
#define AM_HOT_RANK_COMPANY_CELL_HEIGHT 199

@interface AMHotRankCompanyCell : UITableViewCell

//@property (nonatomic,retain) IBOutlet HJManagedImageV *companyRegisterImage;

@property (nonatomic,retain) IBOutlet UIImageView * bkImage;
@property (nonatomic,retain) IBOutlet UIImageView * iconImage;
@property (nonatomic,retain) IBOutlet HJManagedImageV *logoImage1;
@property (nonatomic,retain) IBOutlet HJManagedImageV *logoImage2;
@property (nonatomic,retain) IBOutlet HJManagedImageV *logoImage3;
@property (nonatomic,retain) IBOutlet HJManagedImageV *logoImage4;

@property (nonatomic,retain) IBOutlet UILabel *companyNameLabel;
@property (nonatomic,retain) IBOutlet UILabel *companyNameLastLabel;
@property (nonatomic,retain) IBOutlet UILabel *cityNameLabel;
@property (nonatomic,retain) IBOutlet UILabel *satisfiedRateFrontLabel;
@property (nonatomic,retain) IBOutlet UILabel *satisfiedRateLabel;
@property (nonatomic,retain) IBOutlet UILabel *companyPaymentGMVLabel;
@property (nonatomic,retain) IBOutlet UILabel *rankRiseNumLabel;
@property (nonatomic,retain) IBOutlet UILabel *rankRiseNumFrontLabel;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;

@end

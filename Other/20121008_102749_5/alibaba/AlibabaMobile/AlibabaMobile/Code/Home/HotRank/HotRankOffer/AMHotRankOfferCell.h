//
//  AMHotRankOfferCell.h
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
#define AM_HOT_RANK_OFFER_CELL_HEIGHT 112

@interface AMHotRankOfferCell : UITableViewCell

@property (nonatomic,retain) IBOutlet UIImageView * bkImage;
@property (nonatomic,retain) IBOutlet UIImageView * subImage;
@property (nonatomic,retain) IBOutlet UIImageView * iconImage;
@property (nonatomic,retain) IBOutlet HJManagedImageV *listImg;
@property (nonatomic,retain) IBOutlet UILabel *subjectLabel;
@property (nonatomic,retain) IBOutlet UILabel *offerPaymentGMVLabel;
@property (nonatomic, retain) IBOutlet UILabel *rankingChangeLabel;
@property (nonatomic, retain) IBOutlet UILabel *rankingChangeFrontLabel;
@property (nonatomic,retain) IBOutlet UILabel *priceLabel;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;

@end

//
//  AMHotRankOfferCell.h
//  AlibabaMobile
//
//  Created by amon on 12-6-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
#import "AliParamButton.h"
#import "AliTableViewCell.h"

#define ALI_TABLEVIEW_SUGGEST_CELL_HEIGHT 200

@interface AliTableViewCellSuggest : AliTableViewCell

@property (nonatomic,retain) IBOutlet UIImageView * bkImage;
@property (nonatomic,retain) IBOutlet HJManagedImageV *headImg;
@property (nonatomic,retain) IBOutlet UILabel *name;
@property (nonatomic,retain) IBOutlet UILabel *province;
@property (nonatomic,retain) IBOutlet UILabel *mainBiz;
@property (nonatomic,retain) IBOutlet UILabel *interestInfo;
@property (nonatomic,retain) IBOutlet UILabel *visitDate;
@property (nonatomic,retain) IBOutlet UILabel *intent;
@property (nonatomic,retain) IBOutlet UILabel *buyItems;
@property (nonatomic,retain) IBOutlet UILabel *overdueDays;
@property (nonatomic,retain) IBOutlet UILabel *overdueDaysEnd;
@property (nonatomic, retain) IBOutlet AliParamButton * talkBtn;
@property (nonatomic, retain) IBOutlet AliParamButton * addBtn;
@property (nonatomic, retain) IBOutlet AliParamButton * addBtnPre;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end

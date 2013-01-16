//
//  AMHotRankCompanyCell.m
//  AlibabaMobile
//
//  Created by amon on 12-4-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankCompanyCell.h"

@implementation AMHotRankCompanyCell
@synthesize cityNameLabel,companyNameLabel,companyNameLastLabel,companyPaymentGMVLabel,rankRiseNumFrontLabel,rankRiseNumLabel,satisfiedRateFrontLabel,satisfiedRateLabel,bkImage,logoImage1,iconImage,logoImage2,logoImage3,logoImage4;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

+(CGFloat)cellHeight{
    return AM_HOT_RANK_COMPANY_CELL_HEIGHT;
}
+(NSString*)cellIdentifer{
    return @"AMHotRankCompanyIdeniifier";
}

- (void) dealloc{
    [cityNameLabel release];
    [companyNameLabel release];
    [companyPaymentGMVLabel release];
    [rankRiseNumLabel release];
    [rankRiseNumFrontLabel release];
    [satisfiedRateFrontLabel release];
    [satisfiedRateLabel release];
    [companyNameLastLabel release];
    [bkImage release];
    [logoImage1 release];
    [logoImage2 release];
    [logoImage3 release];
    [logoImage4 release];
    [iconImage release];
    [super dealloc];
}
@end

//
//  AMHotRankOfferCell.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankOfferCell.h"

@implementation AMHotRankOfferCell
@synthesize bkImage,listImg,subImage,subjectLabel,offerPaymentGMVLabel,rankingChangeLabel,rankingChangeFrontLabel,priceLabel,iconImage;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    
    // Configure the view for the selected state
}

+(CGFloat)cellHeight{
    return 112;
}
+(NSString*)cellIdentifer{
    return @"AMHotRankOfferIdeniifier";
}

- (void) dealloc{
    [subjectLabel release];
    [offerPaymentGMVLabel release];
    [rankingChangeLabel release];
    [rankingChangeFrontLabel release];
    [priceLabel release];
    [bkImage release];
    [listImg release];
    [iconImage release];
    [subImage release];
    [super dealloc];
}
@end

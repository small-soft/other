//
//  AMHotRankOfferCell.m
//  AlibabaMobile
//
//  Created by amon on 12-6-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellMyCustomer.h"

@implementation AliTableViewCellMyCustomer
@synthesize buyerName,provinceAndCity,corpName,enquiryTotalTimes,strLastEnquiryTime,talkBtn;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
    }
    return self;
}

+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellMyCustomer" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellMyCustomer class]])
        {
            AliTableViewCellMyCustomer *obj = (AliTableViewCellMyCustomer *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellMyCustomer cellHeight]);
            [obj.talkBtn setImage:[UIImage imageNamed:@"icon_ww.png"] forState:UIControlStateNormal];
            [obj.talkBtn setImageEdgeInsets:UIEdgeInsetsMake(0, -2, 0, 0)];
            return  obj;
        }
    }
    return nil;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    
    // Configure the view for the selected state
}

+(CGFloat)cellHeight{
    return ALI_TABLEVIEW_MY_CUSTOMER_CELL_HEIGHT;
}
+(NSString*)cellIdentifer{
    return @"AliTableViewCellMyCustomerIdeniifier";
}

- (void) dealloc{
    [buyerName release];
    [provinceAndCity release];
    [corpName release];
    [enquiryTotalTimes release];
    [strLastEnquiryTime release];
    [talkBtn release];
    [super dealloc];
}
@end

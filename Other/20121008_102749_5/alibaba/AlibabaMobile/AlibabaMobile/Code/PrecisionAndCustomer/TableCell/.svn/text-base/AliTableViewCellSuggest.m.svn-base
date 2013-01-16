//
//  AMHotRankOfferCell.m
//  AlibabaMobile
//
//  Created by amon on 12-6-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellSuggest.h"

@implementation AliTableViewCellSuggest
@synthesize bkImage,headImg,name,province,mainBiz,interestInfo,visitDate,intent,buyItems,overdueDays,overdueDaysEnd,talkBtn,addBtn,addBtnPre;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
    }
    return self;
}

+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellSuggest" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellSuggest class]])
        {
            AliTableViewCellSuggest *obj = (AliTableViewCellSuggest *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellSuggest cellHeight]);
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
    return ALI_TABLEVIEW_SUGGEST_CELL_HEIGHT;
}
+(NSString*)cellIdentifer{
    return @"AliTableViewCellSuggestIdeniifier";
}

- (void) dealloc{
    [headImg release];
    [name release];
    [province release];
    [mainBiz release];
    [bkImage release];
    [interestInfo release];
    [visitDate release];
    [intent release];
    [buyItems release];
    [overdueDays release];
    [overdueDaysEnd release];
    [talkBtn release];
    [addBtn release];
    [addBtnPre release];
    [super dealloc];
}
@end

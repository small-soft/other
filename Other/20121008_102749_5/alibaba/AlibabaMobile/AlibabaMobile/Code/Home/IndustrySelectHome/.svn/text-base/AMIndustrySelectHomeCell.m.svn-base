//
//  AMIndustrySelectHomeCell.m
//  AlibabaMobile
//
//  Created by amon on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMIndustrySelectHomeCell.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

@implementation AMIndustrySelectHomeCell
@synthesize bkImage,upTypeImage,bottomTypeImage,buttomSeparateImage,typeLabel,introduceLabel;

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

+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIndustrySelectHomeCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMIndustrySelectHomeCell class]])
        {
            AMIndustrySelectHomeCell *obj = (AMIndustrySelectHomeCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMIndustrySelectHomeCell cellHeight]);
//            [obj setupView];
//            obj.hideIdentifyIMage = NO;
            UIView *bg = [[UIView alloc]init];
            bg.backgroundColor = RGB(0xe1, 0xe1, 0xe1);
            obj.selectedBackgroundView = bg;
            [bg release];
            return  (AMIndustrySelectHomeCell *)oneObject;
        }
    }
    return nil;
}

+(CGFloat)cellHeight{
    return AM_INDUSTRY_SELECT_HOME_CELL_HEIGHT;
}
+(NSString*)cellIdentifer{
    return @"AMIndustrySelectHomeCellIdeniifier";
}

- (void) dealloc{

    [buttomSeparateImage release];
    [introduceLabel release];
    [typeLabel release];
    [bkImage release];
    [upTypeImage release];
    [bottomTypeImage release];
    [super dealloc];
}
@end

//
//  AMBannerTableViewCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMBannerTableViewCell.h"

@implementation AMBannerTableViewCell
@synthesize bannerView=_bannerView;


-(void)setupView
{
    
}
+(CGFloat)cellHeight
{
    return 107.0;
}
+(NSString*)cellIdentifer
{
    return @"homepageBanner";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMBannerTableViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMBannerTableViewCell class]])
        {
            AMBannerTableViewCell *obj = (AMBannerTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMBannerTableViewCell cellHeight]);
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}



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

- (void)dealloc {
    [_bannerView release];
    [super dealloc];
}

@end

//
//  AliBannerTableViewCell.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliBannerTableViewCell.h"

@implementation AliBannerTableViewCell
@synthesize bannerView=_bannerView;


-(void)setupView
{
    
}
+(CGFloat)cellHeight
{
    return 110.0;
}
+(NSString*)cellIdentifer
{
    return @"homeBanner";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliBannerTableViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliBannerTableViewCell class]])
        {
            AliBannerTableViewCell *obj = (AliBannerTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliBannerTableViewCell cellHeight]);
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

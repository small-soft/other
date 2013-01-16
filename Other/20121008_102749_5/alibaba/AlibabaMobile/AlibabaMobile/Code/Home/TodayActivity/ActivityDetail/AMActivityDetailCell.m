//
//  AMActivityDetailCell.m
//  AlibabaMobile
//
//  Created by amon on 12-8-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMActivityDetailCell.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

@implementation AMActivityDetailCell
@synthesize eventProductImage,subjectLabel,unitLabel,leaveFactoryPriceAmountLabel,listImg,leaveFactoryPriceAmountPreLabel,backgroundImage,loadingTextNotify;

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
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMActivityDetailCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMActivityDetailCell class]])
        {
            AMActivityDetailCell *obj = (AMActivityDetailCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMActivityDetailCell cellHeight]);
            UIView *bg = [[UIView alloc]init];
            bg.backgroundColor = RGB(0xe1, 0xe1, 0xe1);
            obj.selectedBackgroundView = bg;
            [bg release];
            UIImage *backImg=[UIImage imageNamed:@"activity_bg_02.png"];
            backImg=[backImg stretchableImageWithLeftCapWidth:backImg.size.width/2 topCapHeight:backImg.size.height/2];
            obj.backgroundImage=[[UIImageView alloc]initWithImage:backImg];
            [obj.backgroundImage setFrame:CGRectMake(10, 10, 300, 360)];
            [obj addSubview:obj.backgroundImage];
            obj.listImg.frame = CGRectMake(10, 10, 299, 299);
            obj.listImg.layer.masksToBounds = YES;
            obj.listImg.layer.cornerRadius= 2.0;
            [obj insertSubview:obj.loadingTextNotify aboveSubview:obj.backgroundImage];
            [obj insertSubview:obj.listImg aboveSubview:obj.loadingTextNotify];
            
            return  (AMActivityDetailCell *)oneObject;
        }
    }
    return nil;
}

+(CGFloat)cellHeight{
    return TODAY_EVENT_CELL_HEIGHT;
}
+(NSString*)cellIdentifer{
    return @"AMActivityDetailCellIdeniifier";
}

-(UILabel*)loadingTextNotify
{
    if (!loadingTextNotify) {
        loadingTextNotify = [[UILabel alloc] init];
        NSString *loadText = @"图片加载中...:";
        CGSize labelSize = [loadText sizeWithFont:[UIFont systemFontOfSize:30.0f]];
        loadingTextNotify.frame = CGRectMake(55,145,labelSize.width,labelSize.height);
        loadingTextNotify.textColor = RGB(0x99,0x99,0x99) ;
        loadingTextNotify.numberOfLines = 1;
        loadingTextNotify.text = @"图片加载中...";
        loadingTextNotify.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:30.0f];
        loadingTextNotify.textAlignment = UITextAlignmentCenter;
    }
    return loadingTextNotify;
}

- (void) dealloc{

    [unitLabel release];
    [leaveFactoryPriceAmountLabel release];
    [subjectLabel release];
    [eventProductImage release];
    [listImg release];
    [leaveFactoryPriceAmountPreLabel release];
    [backgroundImage release];
    [loadingTextNotify release];
    [super dealloc];
}
@end

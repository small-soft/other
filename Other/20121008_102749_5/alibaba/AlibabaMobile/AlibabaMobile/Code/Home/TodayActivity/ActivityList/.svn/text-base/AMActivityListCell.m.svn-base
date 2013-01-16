//
//  AliTableViewCellOfferDetail.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMActivityListCell.h"
#import "NSAttributedString+HTML.h"
#import "NSDate+DateUtil.h"
#import "UIView+UIViewUtil.h"

#define MAIN_WIDTH (300.0)
#define MAIN_HEIGHT (170.0)
#define HALF_WIDTH (MAIN_WIDTH/2 - MARGIN * 2)
#define BORDER_WIDTH (4)

@implementation AMActivityListCell
@synthesize icon = _icon;

#pragma - mark
#pragma mark cell lifecycle
- (void)dealloc {
    [nodataImage release];
    [_icon release];
    [title release];
    [validDate release];
    [productCount release];
    [experied release];
    [super dealloc];
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

-(void)setupView
{
    [self setupBg];
    [self setupNodataImage];
    [self setupIcon];
    [self setupTitle];
    [self setupValidDate];
    [self setupProductCount];
    [self setupExperied];
    
    [super setupView];
}

-(void)cellSetData:(AMActivityListCell*)cell withActivity:(AMActivity *)data
{

    [_icon clear];
    _icon.image = nil;
    _icon.url = [NSURL URLWithString:data.topicLogo];   
    
    // 如果有图片，则不显示默认图片
    if (data.topicLogo) {
        nodataImage.hidden = YES;
    }
    
    NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[data.name dataUsingEncoding:NSUTF8StringEncoding]documentAttributes:NULL];
    title.text=attributedText.plainTextString;
    // [attributedText release];
    
//    NSDate *start = [NSDate dateWithTimeIntervalSince1970:data.startDate.longLongValue/1000];
//    NSDate *end = [NSDate dateWithTimeIntervalSince1970:data.endDate.longLongValue/1000];
 
    validDate.text = [NSString stringWithFormat:@"活动时间：%@ - %@",data.topicStartDate,data.topicEndDate];
    
    productCount.text = [NSString stringWithFormat:@"%@",data.offerCount];
 
    if ([data.expired isEqualToString:@"true"]) {
        experied.text = @"已过期";
    } else {
        experied.text = @"进行中";
    }
}

+(CGFloat)cellHeight
{
    return MAIN_HEIGHT + MARGIN;
}
+(NSString*)cellIdentifer
{
    return @"cellActivity";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMActivityListCell" owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMActivityListCell class]])
        {
            AMActivityListCell *obj = (AMActivityListCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMActivityListCell cellHeight]);
            
            [obj setupView];
            UIView *bg = [[UIView alloc]init];
            bg.backgroundColor = RGB(0xdb, 0xdb, 0xdb);
            obj.backgroundView = bg;
            [bg release];
            
            return  obj;
        }
    }
    return nil;
}

#pragma - mark
#pragma mark setup methods

-(void)setupBg{
    bgView.frame = CGRectMake(MARGIN - BORDER_WIDTH, MARGIN - BORDER_WIDTH, MAIN_WIDTH + BORDER_WIDTH * 2, MAIN_HEIGHT + BORDER_WIDTH * 2);
    bgView.backgroundColor = RGB(0xdb, 0xdb, 0xdb);
    
    UIImage *img = [UIImage imageNamed:@"activity_bg_01.png"];    
    bgView.image = [img stretchableImageWithLeftCapWidth:img.size.width/2 topCapHeight:img.size.height/2];
    
    UIImage *highlightedImage = [UIImage imageNamed:@"activity_bg_02.png"];    
    bgView.highlightedImage = [highlightedImage stretchableImageWithLeftCapWidth:highlightedImage.size.width/2 topCapHeight:highlightedImage.size.height/2];
    
}

-(void)setupNodataImage
{
    
    nodataImage.image = [UIImage imageNamed:@"nodata_pic"];    
    nodataImage.frame = CGRectMake(BORDER_WIDTH, BORDER_WIDTH, MAIN_WIDTH, 123.);
    
}
-(void)setupIcon
{
    _icon.frame = nodataImage.frame;
}
-(void)setupTitle
{
    title.fontSize = 16.0;
    title.font = [UIFont boldSystemFontOfSize:16];
    title.r = 0x33;
    title.g = 0x33;
    title.b = 0x33;
    title.numberOfLines = 1;
    
    title.frame=CGRectMake(MARGIN, MARGIN + [nodataImage endY] - 3, MAIN_WIDTH, title.fontSize);
    
}
-(void)setupValidDate
{
    validDate.fontSize = 12.0;
    validDate.r = 0x99;
    validDate.g = 0x99;
    validDate.b = 0x99;
    validDate.textAlignment = UITextAlignmentLeft;
    
    validDate.frame = CGRectMake(MARGIN , [productCount endY] + MARGIN - 3, MAIN_WIDTH, experied.fontSize);
    
}

-(void)setupProductCount
{
    productCount.fontSize = 14.0;
    productCount.r = 0xcc;
    productCount.g = 0x00;
    productCount.b = 0x00;
    productCount.numberOfLines = 1;
    productCount.textAlignment = UITextAlignmentRight;
    
    productCount.frame = CGRectMake(150 + MARGIN, MARGIN + [nodataImage endY], HALF_WIDTH - 100, productCount.fontSize);
    
    productCountLabel.fontSize = 14.0;
    productCountLabel.r = 0x99;
    productCountLabel.g = 0x99;
    productCountLabel.b = 0x99;
    productCountLabel.numberOfLines = 1;
    productCountLabel.textAlignment = UITextAlignmentRight;
    productCountLabel.text = @"件商品参与活动";
    
    productCountLabel.frame = CGRectMake(150 + MARGIN, MARGIN + [nodataImage endY], HALF_WIDTH, productCountLabel.fontSize);
 
    productCount.hidden = YES;
    productCountLabel.hidden = YES;
}

-(void)setupExperied
{
    experied.fontSize = 12.0;
    experied.r = 0x99;
    experied.g = 0x99;
    experied.b = 0x99;
    
    experied.frame = CGRectMake(150 + MARGIN * 2 , [productCount endY] + MARGIN, HALF_WIDTH, experied.fontSize);
    
    experied.hidden = YES;
}

@end

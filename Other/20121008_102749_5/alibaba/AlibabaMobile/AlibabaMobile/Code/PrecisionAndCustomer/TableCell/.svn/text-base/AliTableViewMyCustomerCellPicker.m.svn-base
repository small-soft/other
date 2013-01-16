//
//  AliTableViewCellPicker.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewMyCustomerCellPicker.h"

@implementation AliTableViewMyCustomerCellPicker
//@synthesize icon=_icon;
@synthesize title=_title;

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

-(void)setupTitle
{
    self.title.fontSize = 13.0f;
    self.title.r = 0x33;
    self.title.g = 0x33;
    self.title.b = 0x33;
    CGFloat startX= 5.0f;
    CGFloat endX=self.frame.size.width - 10;
    self.title.frame = CGRectMake(startX, (self.frame.size.height - self.title.fontSize)/2, endX - startX, self.title.fontSize);
}

-(void)setupView
{

//    [self setupIcon];
    [self setupTitle];
    
    [super setupView];
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupView];
}
+(CGFloat)cellHeight
{
    return 45.0;
}
+(CGFloat)cellWidth
{
    return 118.0;
}
+(NSString*)cellIdentifer
{
    return @"myCustomerCellPicker";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewMyCustomerCellPicker" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewMyCustomerCellPicker class]])
        {
            AliTableViewMyCustomerCellPicker *obj = (AliTableViewMyCustomerCellPicker *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, [AliTableViewMyCustomerCellPicker cellWidth], [AliTableViewMyCustomerCellPicker cellHeight]);
            [obj setupView];

            return  obj;
        }
    }
    return nil;
}
- (void)dealloc {
//    [_icon release];
    [_title release];
    [super dealloc];
}
@end

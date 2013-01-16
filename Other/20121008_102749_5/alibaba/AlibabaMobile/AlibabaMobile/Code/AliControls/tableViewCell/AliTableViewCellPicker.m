//
//  AliTableViewCellPicker.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellPicker.h"

@implementation AliTableViewCellPicker
@synthesize icon=_icon;
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
-(void)setupIcon
{
    UIImage *image = [UIImage imageNamed:@"icon_picker_price"];
    CGSize imageSize = [image size];
    self.icon.frame = CGRectMake(15, (self.frame.size.height - imageSize.height)/2, imageSize.width, imageSize.height);
}
-(void)setupTitle
{
    self.title.fontSize = 16.0;
    self.title.r = 0x33;
    self.title.g = 0x33;
    self.title.b = 0x33;
    CGFloat startX= self.icon.frame.origin.x + self.icon.frame.size.width +10;
    CGFloat endX=self.frame.size.width - 25;
    self.title.frame = CGRectMake(startX, (self.frame.size.height - self.title.fontSize)/2, endX - startX, self.title.fontSize);
}

-(void)setupView
{

    [self setupIcon];
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
    return 43.0;
}
+(CGFloat)cellWidth
{
    return 110.0;
}
+(NSString*)cellIdentifer
{
    return @"cellPicker";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellPicker" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellPicker class]])
        {
            AliTableViewCellPicker *obj = (AliTableViewCellPicker *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, [AliTableViewCellPicker cellWidth], [AliTableViewCellPicker cellHeight]);
            [obj setupView];

            return  obj;
        }
    }
    return nil;
}
- (void)dealloc {
    [_icon release];
    [_title release];
    [super dealloc];
}
@end

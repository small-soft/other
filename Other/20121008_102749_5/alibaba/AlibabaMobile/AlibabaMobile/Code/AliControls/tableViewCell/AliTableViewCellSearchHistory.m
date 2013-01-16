//
//  AliTableViewCellSearchHistory.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellSearchHistory.h"
#define MARGIN (15.0)
@implementation AliTableViewCellSearchHistory
@synthesize title=_title;
@synthesize splitLine = _splitLine;
@synthesize editButton = _editButton;
- (void)dealloc {
    [_title release];
    [_splitLine release];
    [_editButton release];
    [super dealloc];
}
-(void)setupEditButton
{
    UIImage *bg = [UIImage imageNamed:@"icon_edit"];
    CGSize bgSize = bg.size;
    self.editButton.frame = CGRectMake(self.frame.size.width - 20.0-bgSize.width, 0, bgSize.width+20, self.frame.size.height);
    [self.editButton setImage:bg forState:UIControlStateNormal];
    [self.editButton setImage:bg forState:UIControlStateHighlighted];
    [self.editButton setImage:bg forState:UIControlStateSelected];

    
}
-(void)setupSplitLine
{
    UIImage *bg = [UIImage imageNamed:@"bg_aliww_line.png"];
    CGSize bgSize = bg.size;
    self.splitLine.image = bg;
    self.splitLine.frame = CGRectMake(self.editButton.frame.origin.x
                                       - bgSize.width, (self.frame.size.height - bgSize.height)/2, bgSize.width, bgSize.height);
    
}
-(void)setupTitle
{
    self.title.fontSize = 16.0;
    self.title.r = 0x33;
    self.title.g = 0x33;
    self.title.b = 0x33;
    self.title.frame = CGRectMake(MARGIN, (self.frame.size.height - self.title.fontSize)/2 - 3, self.splitLine.frame.origin.x - MARGIN -10.0, self.title.fontSize + 3);
}


-(void)setupView
{
    [self setupEditButton];
    [self setupSplitLine];
    [self setupTitle];
    [super setupView]; 
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
+(CGFloat)cellHeight
{
    return 42.0;
}
+(NSString*)cellIdentifer
{
    return @"cellSearchHistory";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellSearchHistory" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellSearchHistory class]])
        {
            AliTableViewCellSearchHistory *obj = (AliTableViewCellSearchHistory *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellSearchHistory cellHeight]);
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}


@end

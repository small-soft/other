//
//  AMOrderLogCell.m
//  AlibabaMobile
//
//  Created by alimobile on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderLogCell.h"
#define MARGIN (15.0)
@implementation AMOrderLogCell
@synthesize logisticsNo = _logisticsNo;
@synthesize logisticsName = _logisticsName;
@synthesize toContact = _toContact;


//-(void)setupTitle
//{
//    self.title.fontSize = 16.0;
//    self.title.r = 0x33;
//    self.title.g = 0x33;
//    self.title.b = 0x33;
//}

-(void)setupView{

//    [self setupTitle];
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
    return 90.0;
}
+(NSString*)cellIdentifer
{
    return @"orderCellCategory";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMOrderLogCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMOrderLogCell class]])
        {
            AMOrderLogCell *obj = (AMOrderLogCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMOrderLogCell cellHeight]);
            [obj setupView];
            return  (AMOrderLogCell *)oneObject;
        }
    }
    return nil;
}
- (void)dealloc {
    [_toContact release];
    [_logisticsName release];
    [_logisticsNo release];
    [super dealloc];
}
@end

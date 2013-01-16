//
//  AliChannelTableViewCell.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliChannelTableViewCell.h"

@implementation AliChannelTableViewCell
@synthesize cellBlock1=_cellBlock1;
@synthesize cellBlock2=_cellBlock2;

-(void)setupView
{

}
+(CGFloat)cellHeight
{
    return 44.0;
}
+(NSString*)cellIdentifer
{
    return @"homeChannel";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliChannelTableViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliChannelTableViewCell class]])
        {
            AliChannelTableViewCell *obj = (AliChannelTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliChannelTableViewCell cellHeight]);
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
-(void)drawRect:(CGRect)rect
{
    [super drawRect:rect];
    CGContextSetLineCap(UIGraphicsGetCurrentContext(), kCGLineCapRound);
    CGContextSetLineWidth(UIGraphicsGetCurrentContext(), 1);
    CGContextSetAllowsAntialiasing(UIGraphicsGetCurrentContext(), YES);
    CGContextSetRGBStrokeColor(UIGraphicsGetCurrentContext(), 224.0/255.0, 224.0/255.0, 224.0/255.0, 1.0);
    CGContextBeginPath(UIGraphicsGetCurrentContext());
    CGContextMoveToPoint(UIGraphicsGetCurrentContext(), rect.size.width/2, 4.0);
    CGContextAddLineToPoint(UIGraphicsGetCurrentContext(), rect.size.width/2, rect.size.height-4);
    CGContextStrokePath(UIGraphicsGetCurrentContext());

}
- (void)dealloc {
    [_cellBlock1 release];
    [_cellBlock2 release];
    [super dealloc];
}
@end

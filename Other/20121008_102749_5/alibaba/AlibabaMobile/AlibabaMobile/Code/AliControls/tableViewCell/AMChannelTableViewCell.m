//
//  AMChannelTableViewCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-27.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMChannelTableViewCell.h"

@implementation AMChannelTableViewCell
@synthesize menuView = _menuView;

-(void)setupView
{
    
}
+(CGFloat)cellHeight
{
    return 260;
}
+(NSString*)cellIdentifer
{
    return @"homeChannelView";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMChannelTableViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMChannelTableViewCell class]])
        {
            AMChannelTableViewCell *obj = (AMChannelTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMChannelTableViewCell cellHeight]);
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
    /*CGContextSetLineCap(UIGraphicsGetCurrentContext(), kCGLineCapRound);
    CGContextSetLineWidth(UIGraphicsGetCurrentContext(), 1);
    CGContextSetAllowsAntialiasing(UIGraphicsGetCurrentContext(), YES);
    CGContextSetRGBStrokeColor(UIGraphicsGetCurrentContext(), 224.0/255.0, 224.0/255.0, 224.0/255.0, 1.0);
    CGContextBeginPath(UIGraphicsGetCurrentContext());
    CGContextMoveToPoint(UIGraphicsGetCurrentContext(), rect.size.width/2, 4.0);
    CGContextAddLineToPoint(UIGraphicsGetCurrentContext(), rect.size.width/2, rect.size.height-4);
    CGContextStrokePath(UIGraphicsGetCurrentContext());*/
    
}
- (void)dealloc {
    [_menuView release];
    [super dealloc];
}

@end

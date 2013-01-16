//
//  AMChannelTableViewCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-27.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//
// 该cell用于父子结构的cell，包含mainView和subView，mainView是整体概述或者是logo图片等，subView是子元素的列表

#import "AMMainSubViewCell.h"

@implementation AMMainSubViewCell
@synthesize mainView = _mainView;
@synthesize subView = _subView;

-(void)setupView
{
    self.mainView.frame = CGRectMake(0.0, 0.0, self.frame.size.width / 5, [AMMainSubViewCell cellHeight]);
    
    self.subView.frame = CGRectMake(self.frame.size.width / 5, 0.0, (self.frame.size.width * 4)/ 5, [AMMainSubViewCell cellHeight]);
    
    [super setupView];
}
+(CGFloat)cellHeight
{
    return 80;
}
+(NSString*)cellIdentifer
{
    return @"mainSubViewCell";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMMainSubViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMMainSubViewCell class]])
        {
            AMMainSubViewCell *obj = (AMMainSubViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMMainSubViewCell cellHeight]);
//            obj.bounds = CGRectMake(0.0, 0.0, 320.0, [AMMainSubViewCell cellHeight]);
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
    [_subView release];
    [_mainView release];
    [super dealloc];
}

@end

//
//  GraphNode.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "GraphNode.h"

@implementation GraphNode
@synthesize id_,name;
@synthesize lableInfo;
@synthesize mybuttonType;

- (id)initWithID:(NSInteger)newID
            name:(NSString *)newName
rect:(CGRect)frame
{
    
    self.id_ = newID;
    self.name = newName;
    [self initWithFrame:frame];
    return self;
}

- (void)btAction:(id)sender{
}

-(void) dealloc {
    [name release];
    [lableInfo release];
    [super dealloc];
}


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    return self;
}


-(void) drawRect:(CGRect)rect 
{
    //UIColor *colorBackground = [UIColor colorWithRed:5/255.0 green:141/255.0 blue:191/255.0 alpha:1.0];
    //UIColor *colorBorder = [UIColor colorWithRed:5/255.0 green:141/255.0 blue:191/255.0 alpha:1.0];
    UIImage *imageButtonBackground = [UIImage imageNamed:@"select_background"];
 /*
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect currentRect = CGRectMake(self.layer.frame.origin.x + self.layer.frame.size.width/2 - 13.0/2, self.layer.frame.origin.y + self.layer.frame.size.height/2 - 13.0/2, 13.0, 13.0);
    //设置矩形填充颜色：红色    
    CGContextSetStrokeColorWithColor(context, colorBorder.CGColor);
    CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
    //设置画笔线条粗细    
    CGContextSetLineWidth(context, 2.0);    
    
    //扇形参数    
    double radius=13.0;//半径    
    int startX=self.layer.frame.origin.x + self.layer.frame.size.width/2 - 13.0/2;//圆心x坐标    
    int startY=self.layer.frame.origin.y + self.layer.frame.size.height/2 - 13.0/2;//圆心y坐标        
    int clockwise=0;//0=逆时针,1=顺时针    
    
    //逆时针画扇形    
    CGContextAddEllipseInRect(context, currentRect);
    CGContextDrawPath(context, kCGPathFillStroke);
  */
    //self.layer.frame = CGRectMake(self.layer.frame.origin.x + self.layer.frame.size.width/2 - 13.0/2, self.layer.frame.origin.y + self.layer.frame.size.height/2 - 13.0/2, 13.0, 13.0);
    //[ self.layer setBackgroundColor: [[UIColor clearColor] CGColor]];
    //[ self.layer setBorderColor: [colorBorder CGColor]];
    //[ self.layer setBorderWidth: 2.0];
    
    switch (mybuttonType) {
        case 0:
            break;
        case 1:
            //[ self.layer setCornerRadius:7.0f];
            [self setImage:imageButtonBackground forState:UIControlStateNormal];
            break;
        case 2:
            break;
        case 3:
            break;  
        default:
            break;
    }

    //[ self.layer setMasksToBounds:YES];
    //[layerView release];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end

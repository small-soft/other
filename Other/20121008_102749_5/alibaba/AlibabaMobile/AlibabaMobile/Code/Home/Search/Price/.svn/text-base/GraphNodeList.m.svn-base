//
//  GraphNodeList.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "GraphNodeList.h"
#import "GraphNodeLine.h"
#import "ConstDef.h"
#import "AMPriceGraghListResult.h"
#import "AMPriceGraghListRequest.h"

#define OCEAN_API_URL_SEARCH_PRICEGRAGH ([@"/news.priceMarket.getHistoryPrice/" stringByAppendingString:AMCONST_APP_KEY])

@interface GraphNodeList()

@end

@implementation GraphNodeList
@synthesize dataSource;
@synthesize xValuesFormatter = _xValuesFormatter, yValuesFormatter = _yValuesFormatter;
@synthesize drawAxisX = _drawAxisX, drawAxisY = _drawAxisY, drawGridX = _drawGridX, drawGridY = _drawGridY;
@synthesize xValuesColor = _xValuesColor, yValuesColor = _yValuesColor, gridXColor = _gridXColor, gridYColor = _gridYColor;
@synthesize drawInfo = _drawInfo, info = _info, infoColor = _infoColor;
@synthesize lableInfo;
@synthesize numberOfPlots;
@synthesize indexofButtons;
@synthesize imageButton,imageButtonBackground,imagePopView,imagePopViewUp;
@synthesize lists;



+ (UIColor *)colorByIndex:(NSInteger)index {
	
	UIColor *color;
	
	switch (index) {
		case 0: color = RGB(5, 141, 191);
			break;
		case 1: color = RGB(80, 180, 50);
			break;		
		case 2: color = RGB(255, 102, 0);
			break;
		case 3: color = RGB(255, 158, 1);
			break;
		case 4: color = RGB(252, 210, 2);
			break;
		case 5: color = RGB(248, 255, 1);
			break;
		case 6: color = RGB(176, 222, 9);
			break;
		case 7: color = RGB(106, 249, 196);
			break;
		case 8: color = RGB(178, 222, 255);
			break;
		case 9: color = RGB(4, 210, 21);
			break;
		default: color = RGB(204, 204, 204);
			break;
	}
	
	return color;
}


+ (GraphNodeList *)loadGraphInfoList:(CGRect)frame
{
    GraphNodeList *graphNodelist = [[GraphNodeList alloc] initWithFrame:frame];
//    return [graphNodelist autorelease];
    return graphNodelist;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        //lists = [[NSMutableArray arrayWithCapacity:0] retain];
        indexofButtons = -1;
        _drawAxisX = YES;
        _drawAxisY = YES;
        _drawGridX = YES;
        _drawGridY = YES;
        //_xValuesFormatter = YES;
        NSNumberFormatter *numberFormatter = [NSNumberFormatter new];
        [numberFormatter setNumberStyle:NSNumberFormatterDecimalStyle];
        [numberFormatter setMinimumFractionDigits:0];
        [numberFormatter setMaximumFractionDigits:0];
        
        _yValuesFormatter = nil;
        
        NSDateFormatter *dateFormatter = [NSDateFormatter new];
        [dateFormatter setDateFormat:@"MM/dd"];
        _xValuesFormatter = nil;
        
        [dateFormatter release];
        [numberFormatter release];

        
        _xValuesColor = [[UIColor blackColor] retain];
        _yValuesColor = [[UIColor blackColor] retain];
        
        _gridXColor = [[UIColor blackColor] retain];
        _gridYColor = [[UIColor blackColor] retain];
        
        _drawInfo = YES;
        _infoColor = [[UIColor blackColor] retain];
        [self setBackgroundColor:[UIColor clearColor]];
        
        //PopView
        popView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, POPVIEWWIDTH, POPVIEWHEIGHT)];
        imagePopView = [[UIImageView alloc] initWithFrame:popView.frame];
        //[popView setBackgroundColor:[UIColor clearColor]];
        imagePopViewOrigent = 1;
        imagePopViewUpOrigent = 3;
        UIImage *imageTmp = [UIImage imageNamed:@"pop"];
        imageTmp = [imageTmp stretchableImageWithLeftCapWidth:imageTmp.size.width*7/8 topCapHeight:imageTmp.size.height/4];
        CGSize itemSize = popView.frame.size;
        UIGraphicsBeginImageContext(itemSize);
        CGRect imageRect = CGRectMake(0.0, 0.0, itemSize.width, itemSize.height);
        //[imageTmp drawInRect:imageRect];
        [imageTmp drawInRect:imageRect];
        self.imagePopView.image = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        
        [popView addSubview:imagePopView];
        
        //[popView setBackgroundColor:[UIColor colorWithPatternImage: self.imagePopView.image]];
        [popView setAlpha:0.0f];
        
        //button
        imageButton = [UIImage imageNamed:@"select_pop"];
        imageButtonBackground = [UIImage imageNamed:@"select_background"];
        
        UIGraphicsEndImageContext();

        
        lableInfo = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, popView.frame.size.width - 20.0,  popView.frame.size.height - 20.0) ];
        lableInfo.center = CGPointMake(popView.center.x + 5.0, popView.center.y - 5.0);
        lableInfo.numberOfLines = 2;
        lableInfo.adjustsFontSizeToFitWidth = YES; 
        lableInfo.lineBreakMode = UILineBreakModeClip;
        lableInfo.backgroundColor = [UIColor clearColor];
        lableInfo.font = [UIFont fontWithName:@ "Arial Rounded MT Bold"  size:(13)];
        lableInfo.textAlignment = UITextAlignmentLeft;
        lableInfo.textColor = [UIColor whiteColor];
        numberOfPlots = 1;
        //[lableInfo setBackgroundColor:[UIColor blueColor]];
        //[lableInfo setTextAlignment:UITextAlignmentCenter];
        
        [popView addSubview:lableInfo];
        [self addSubview:popView];
        

    }
    return self;
}

- (void)dealloc {
    
    lists = nil;
//	NSLog(@"lists retainCount : %d",[lists retainCount]);
	[_xValuesFormatter release];
	[_yValuesFormatter release];
	
	[_xValuesColor release];
	[_yValuesColor release];
	
	[_gridXColor release];
	[_gridYColor release];
	
	[_info release];
	[_infoColor release];
    [lableInfo release];
    [popView release];
    [imagePopView release];
    [imagePopViewUp release];
    
	
	[super dealloc];
}
//清除原先留在屏幕上的button控件，不清除会产生bug，导致死机！！！
-(void)releaseGraphList
{
    //NSLog(@"lists releaseGraphList : %d",[lists count]);
    if (indexofButtons != -1) {
        //[(GraphNodeLine *)[lists objectAtIndex:indexofButtons] setBackgroundColor:[UIColor whiteColor]];
        [(GraphNodeLine *)[lists objectAtIndex:indexofButtons] setImage:imageButtonBackground forState:UIControlStateNormal];
        indexofButtons = -1;
    }
    for (GraphNodeLine *bt in lists){
        [bt removeFromSuperview];
    }
    [popView setAlpha:0.0f];
    self.lists = nil;
}
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef c = UIGraphicsGetCurrentContext();
	CGContextSetFillColorWithColor(c, [UIColor clearColor].CGColor);
	CGContextFillRect(c, rect);//用当前背景的颜色填充给定的rect区域
    
    if (self.lists != nil) {
        [self releaseGraphList];
    }
    self.lists = [self.dataSource graphNodeList:self];//获取所需要的lists信息，用于button按钮
    //NSLog(@"lists retainCount : %d",[lists retainCount]);
	numberOfPlots = [self.dataSource graphViewNumberOfPlots:self];//获取当前需要画几条线
	
	if (!numberOfPlots) {
		return;
	}
    if ([lists count] > 0) {
        CGFloat offsetX = _drawAxisY ? OFFSETX : 10.0f;
        CGFloat offsetY = (_drawAxisX || _drawInfo) ? OFFSETY : 10.0f;
        
        CGFloat minY = 50000.0f;
        CGFloat maxY = 0.0;
        
        UIFont *font = [UIFont systemFontOfSize:11.0f];
        
        for (NSUInteger plotIndex = 0; plotIndex < numberOfPlots; plotIndex++) {
            
            NSArray *values = [self.dataSource graphView:self yValuesForPlot:plotIndex];
            
            for (NSUInteger valueIndex = 0; valueIndex < values.count; valueIndex++) 
            {
                //找出最大值
                if ([[values objectAtIndex:valueIndex] floatValue] > maxY) {
                    maxY = [[values objectAtIndex:valueIndex] floatValue];
                }
                //找出最小值
                if ([[values objectAtIndex:valueIndex] floatValue] < minY) {
                    minY = [[values objectAtIndex:valueIndex] floatValue];
                }
            }
        }
        maxY = maxY + maxY/10 ;
        minY = minY - minY/10;
        if (minY > maxY) {
            minY = 0;
        }
        
        //CGFloat step = (maxY - minY) / STEPYPOINT;//将Y方向分为六份
        CGFloat stepY = (FRAMEHEIGHT - (offsetY * 2)) / (maxY - minY);//计算Y方向的间隔
        
        NSMutableArray *xValues = [[NSMutableArray alloc] initWithCapacity:0];
        for (GraphNodeLine *gNodeLine in lists) {
            [xValues addObject:gNodeLine.xVlaues];
        }
       // NSLog(@"xValues in GraphNodeList retainCount : %d",[xValues retainCount]);
        NSUInteger xValuesCount = xValues.count;
        //NSLog(@"xValuesCount:%d",xValuesCount);
        
        //固定的间距大小，每行显示6个数字
        CGFloat stepX = (FRAMEWIDTH - (offsetX * 2)) / 5;
        
        for (NSUInteger i = 0; i < xValuesCount; i++) {//x方向画虚线以及数字信息
            
            NSUInteger x = (i) * stepX;
            
            NSUInteger index = i;
            if (index == (xValuesCount - 1)) {//绘制X轴黑线
                CGContextSetLineWidth(c, 1.0f);
                
                CGPoint startPoint = CGPointMake(0, self.frame.size.height - offsetY);
                CGPoint endPoint = CGPointMake(self.frame.size.width, self.frame.size.height - offsetY);
                
                CGContextMoveToPoint(c, startPoint.x, startPoint.y);
                CGContextAddLineToPoint(c, endPoint.x, endPoint.y);
                CGContextClosePath(c);
                
                CGContextSetStrokeColorWithColor(c, [UIColor blackColor].CGColor);
                CGContextStrokePath(c);
                
            }
            
            if (_drawGridX) {//绘制X方向网格（主要是绘制x轴上的小黑点）
                
                
                CGContextSetLineWidth(c, 1.0f);
                
                CGPoint startPoint = CGPointMake(x + offsetX, self.frame.size.height - offsetY - 5.0);
                CGPoint endPoint = CGPointMake(x + offsetX, self.frame.size.height - offsetY);
                
                CGContextMoveToPoint(c, startPoint.x, startPoint.y);
                CGContextAddLineToPoint(c, endPoint.x, endPoint.y);
                CGContextClosePath(c);
                
                CGContextSetStrokeColorWithColor(c, [UIColor blackColor].CGColor);
                CGContextStrokePath(c);
            }
            
            
            if (_drawAxisX) {//绘制X轴上的坐标点文字
                
                id valueToFormat = [xValues objectAtIndex:index];
                NSString *valueString;
                
                if (_xValuesFormatter) {
                    valueString = [_xValuesFormatter stringForObjectValue:valueToFormat];
                } else {
                    valueString = [NSString stringWithFormat:@"%@", valueToFormat];
                }
                
                [self.xValuesColor set];
                [valueString drawInRect:CGRectMake(x+offsetX, self.frame.size.height - 20.0f, 60.0f, 20.0f) withFont:font
                          lineBreakMode:UILineBreakModeTailTruncation alignment:UITextAlignmentLeft];
            }
        }
         //NSLog(@"xValues in before GraphNodeList retainCount : %d",[xValues retainCount]);
//        [xValues release];
        NSLog(@"xValues in GraphNodeList retainCount : %d",[xValues retainCount]);
        
        CGContextSetLineDash(c, 0, NULL, 0);
        
        for (NSUInteger plotIndex = 0; plotIndex < numberOfPlots; plotIndex++) {//画出需要的若干条线，这里为一条
            
            NSMutableArray *yValues = [[NSMutableArray alloc] initWithCapacity:0];
            for (GraphNodeLine *gNodeLine in lists) {
                [yValues addObject:gNodeLine.yVlaues];
            }
            
            //用于填充数据下面的面积
            BOOL shouldFill = NO;
            /*
             if ([self.dataSource respondsToSelector:@selector(graphView:shouldFillPlot:)]) {
             shouldFill = [self.dataSource graphView:self shouldFillPlot:plotIndex];
             }
             */
            CGColorRef plotColor = [GraphNodeList colorByIndex:plotIndex].CGColor;
            //NSLog(@"yValues.count:%d",yValues.count);
            if (yValues.count > 0) 
            {
                //[UIView beginAnimations:@"nodelist" context:nil];
                //[UIView setAnimationDuration:0.8f]; 
                //只有一个点的时候不需要画线因此特殊处理
                if (yValues.count == 1) {
                    NSUInteger valueIndex = 0;
 
                    NSUInteger x = valueIndex * stepX;
                    NSUInteger y = ([[yValues objectAtIndex:valueIndex] intValue] - minY) * stepY;
                    CGPoint startPoint = CGPointMake(x + offsetX, self.frame.size.height - y - offsetY);
                    //添加触摸点
                    GraphNodeLine *bt = [lists objectAtIndex:valueIndex];
                    [bt setCenter:startPoint];
                    [bt addTarget:self action:@selector(btAction:) forControlEvents:UIControlEventTouchUpInside];
                    [self addSubview:bt];
                }
                else {
                    for (NSUInteger valueIndex = 0; valueIndex < yValues.count - 1; valueIndex++) {//画出该条折现
                        
                        NSUInteger x = valueIndex * stepX;
                        NSUInteger y = ([[yValues objectAtIndex:valueIndex] intValue] - minY) * stepY;
                        
                        CGContextSetLineWidth(c, 1.5f);
                        
                        CGPoint startPoint = CGPointMake(x + offsetX, self.frame.size.height - y - offsetY);
                        
                        x = (valueIndex + 1) * stepX;
                        y = ([[yValues objectAtIndex:valueIndex + 1] intValue]  - minY) * stepY ;
                        
                        CGPoint endPoint = CGPointMake(x + offsetX, self.frame.size.height - y - offsetY);
                        
                        CGContextMoveToPoint(c, startPoint.x, startPoint.y);
                        CGContextAddLineToPoint(c, endPoint.x, endPoint.y);
                        CGContextClosePath(c);
                        
                        CGContextSetStrokeColorWithColor(c, plotColor);
                        
                        CGContextStrokePath(c);
                        
                        
                        //添加触摸点
                        GraphNodeLine *bt = [lists objectAtIndex:valueIndex];
                        
                        [bt setCenter:startPoint];
                        [bt addTarget:self action:@selector(btAction:) forControlEvents:UIControlEventTouchUpInside];
                        [self addSubview:bt];
                        
                        if (valueIndex == yValues.count - 2) {
                            GraphNodeLine *bt = [lists objectAtIndex:valueIndex+1];           
                            [bt setCenter:endPoint];
                            [bt addTarget:self 
                                   action:@selector(btAction:) 
                         forControlEvents:UIControlEventTouchUpInside];
                            
                            //[self addSubview:bt];
                            [self insertSubview:bt atIndex:0];
                        }
                        
                        if (shouldFill) {
                            
                            CGContextMoveToPoint(c, startPoint.x, self.frame.size.height - offsetY);
                            CGContextAddLineToPoint(c, startPoint.x, startPoint.y);
                            CGContextAddLineToPoint(c, endPoint.x, endPoint.y);
                            CGContextAddLineToPoint(c, endPoint.x, self.frame.size.height - offsetY);
                            CGContextClosePath(c);
                            
                            CGContextSetFillColorWithColor(c, plotColor);
                            CGContextFillPath(c);
                        }
                    }
                    
                }
                
                //[UIView commitAnimations];
            }
//            [yValues release];
            
        }
        
        if (_drawInfo) {
            
            font = [UIFont boldSystemFontOfSize:13.0f];
            [self.infoColor set];
            [_info drawInRect:CGRectMake(0.0f, 5.0f, self.frame.size.width, 20.0f) withFont:font
                lineBreakMode:UILineBreakModeTailTruncation alignment:UITextAlignmentCenter];
        }

    }
//self.lists = nil;
//NSLog(@"lists retainCount last: %d",[[self.dataSource graphNodeList:self] retainCount]);
    [self bringSubviewToFront:popView];
	
}

- (void)reloadData {
	
	[self setNeedsDisplay];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    //UITouch *touch = [touches anyObject];
    //CGPoint location = [touch locationInView:self ];
    
    // [touch view]获得当前touch的view
    
    //[allTouches count]获得当前touch的是否是多触摸，如果 [allTouches count] == 1就不是多触摸。
    
    switch ([allTouches count]) {
        case 1: {
            // potential pan gesture
            //UITouch *touch = [[allTouches allObjects] objectAtIndex:0];
            if (indexofButtons != -1) {
                //[(GraphNodeLine *)[lists objectAtIndex:indexofButtons] setBackgroundColor:[UIColor whiteColor]];
                [(GraphNodeLine *)[lists objectAtIndex:indexofButtons] setImage:imageButtonBackground forState:UIControlStateNormal];
                indexofButtons = -1;
            }
            
            [popView setAlpha:0.0f];
        } break;
            
        case 2: {
            // potential zoom gesture
            
        } break;
            
        default:

            break;
            
    }
}

- (void)btAction:(id)sender{
    GraphNodeLine *newBt = (GraphNodeLine*)sender;
    //UIColor *color = newBt.backgroundColor; 
    //[newBt setBackgroundColor:[UIColor colorWithRed:54/255.0f green:152/255.0f blue:241/255.0f alpha:0.75f]];
    [newBt setImage:imageButton forState:UIControlStateNormal];
    [lableInfo setText:newBt.lableInfo];

    
    UIScrollView *scrollView = (UIScrollView*)[self superview];
    if (scrollView) {
        if (imagePopViewUpOrigent == 4) {
            lableInfo.center = CGPointMake( lableInfo.center.x,  lableInfo.center.y - 10);
        }

        popView.center = CGPointMake(newBt.center.x + popView.frame.size.width/4, newBt.center.y - popView.frame.size.height/2 - 10.0);
        imagePopView.transform = CGAffineTransformMakeScale(1.0, 1.0); 
        imagePopViewUpOrigent = 3;
        imagePopViewOrigent = 1;

        if ((newBt.center.x  - scrollView.contentOffset.x - OFFSETX <= 0)) {
            popView.center = CGPointMake(newBt.center.x+OFFSETX + popView.frame.size.width/4, newBt.center.y - popView.frame.size.height/2 - 10.0);
                         
        }
        else if(newBt.center.x  - scrollView.contentOffset.x - FRAMEWIDTH + 3*OFFSETX >= 0) {
            popView.center = CGPointMake(newBt.center.x-OFFSETX - popView.frame.size.width/4, newBt.center.y - popView.frame.size.height/2 - 10.0);
            if (imagePopViewOrigent != 2) {
                imagePopView.transform = CGAffineTransformMakeScale(-1.0, 1.0); 
                imagePopViewOrigent = 2;
            }

        }
        if ((newBt.center.y + 2*OFFSETY - FRAMEHEIGHT >= 0)) {
            popView.center = CGPointMake(popView.center.x, newBt.center.y - popView.frame.size.height/2 - 10.0);
        }
        else if ((newBt.center.y - FRAMEHEIGHT/4 <= 0)) {
            popView.center = CGPointMake(popView.center.x, newBt.center.y + popView.frame.size.height/2 + 10.0);
            lableInfo.center = CGPointMake( lableInfo.center.x,  lableInfo.center.y + 10);
            //lableInfo.center = CGPointMake(popView.center.x - 5.0, popView.center.y + 5.0);
            if (imagePopViewUpOrigent != 4) {
                if (imagePopViewOrigent == 1) {
                    imagePopView.transform = CGAffineTransformMakeScale(1.0, -1.0); 
                }
                else if(imagePopViewOrigent == 2) {
                    imagePopView.transform = CGAffineTransformMakeScale(-1.0, -1.0); 
                }
                imagePopViewUpOrigent = 4;
            }

        }
        
    }
    else {
        [popView setBackgroundColor:[UIColor colorWithPatternImage: imagePopView.image]];
        popView.center = CGPointMake(newBt.center.x, newBt.center.y - popView.frame.size.height/2);
    }
    [UIView beginAnimations:@"pick" context:nil];
    [UIView setAnimationDuration:0.3f]; 
    [popView setAlpha:1.0f];
    [UIView commitAnimations];
    
    if (indexofButtons != -1) {
        //[[lists objectAtIndex:indexofButtons] setBackgroundColor:color];
        if ([lists indexOfObject:newBt] != indexofButtons) {
            [[lists objectAtIndex:indexofButtons] setImage:imageButtonBackground forState:UIControlStateNormal];
            indexofButtons = [lists indexOfObject:newBt];
            if (indexofButtons == NSNotFound) {
                indexofButtons = -1;
                for (GraphNodeLine *index in lists) {
                    [index setImage:imageButtonBackground forState:UIControlStateNormal];
                }
            }

        }
        
            }
    else {
        indexofButtons = [lists indexOfObject:newBt];
    }

}

@end

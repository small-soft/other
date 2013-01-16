//
//  S7GraphView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

//
//  S7GraphView.m
//  S7Touch
//
//  Created by Aleks Nesterow on 9/27/09.
//  aleks.nesterow@gmail.com
//  
//  Thanks to http://snobit.habrahabr.ru/ for releasing sources for his
//  Cocoa component named GraphView.
//  
//  Copyright © 2009, 7touchGroup, Inc.
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the distribution.
//  * Neither the name of the 7touchGroup, Inc. nor the
//  names of its contributors may be used to endorse or promote products
//  derived from this software without specific prior written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY 7touchGroup, Inc. "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL 7touchGroup, Inc. BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  

#import "S7GraphView.h"
#import "GraphNodeLine.h"

@interface S7GraphView (PrivateMethods)

- (void)initializeComponent;

@end

@implementation S7GraphView

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

@synthesize dataSource = _dataSource, xValuesFormatter = _xValuesFormatter, yValuesFormatter = _yValuesFormatter;
@synthesize drawAxisX = _drawAxisX, drawAxisY = _drawAxisY, drawGridX = _drawGridX, drawGridY = _drawGridY;
@synthesize xValuesColor = _xValuesColor, yValuesColor = _yValuesColor, gridXColor = _gridXColor, gridYColor = _gridYColor;
@synthesize drawInfo = _drawInfo, info = _info, infoColor = _infoColor;

@synthesize lableInfo;

- (id)initWithFrame:(CGRect)frame {
	
    if (self = [super initWithFrame:frame]) {
		[self initializeComponent];
    }
	
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder {
	
	if (self = [super initWithCoder:decoder]) {
		[self initializeComponent];
	}
	
	return self;
}

- (void)dealloc {
	
	[_xValuesFormatter release];
	[_yValuesFormatter release];
	
	[_xValuesColor release];
	[_yValuesColor release];
	
	[_gridXColor release];
	[_gridYColor release];
	
	[_info release];
	[_infoColor release];

    
	
	[super dealloc];
}

- (void)drawRect:(CGRect)rect {
	
	CGContextRef c = UIGraphicsGetCurrentContext();
	CGContextSetFillColorWithColor(c, self.backgroundColor.CGColor);
	CGContextFillRect(c, rect);//用当前背景的颜色填充给定的rect区域
	
	NSUInteger numberOfPlots = [self.dataSource graphViewNumberOfPlots:self];//获取当前需要画几条线
	
	if (!numberOfPlots) {
		return;
	}
	
    CGFloat offsetX = _drawAxisY ? 20.0f : 10.0f;
	CGFloat offsetY = (_drawAxisX || _drawInfo) ? OFFSETY : 10.0f;
	
	CGFloat minY = 50000.0f;
	CGFloat maxY = 0.0;
	
	UIFont *font = [UIFont systemFontOfSize:11.0f];
	
	for (NSUInteger plotIndex = 0; plotIndex < numberOfPlots; plotIndex++) 
    {
		
		NSArray *values = [self.dataSource graphView:self yValuesForPlot:plotIndex];
        //NSLog(@"values in S7GraphView retainCount : %d",[values retainCount]);
		
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
        //将最大值取整
        /*
        if (maxY < 100) {
            maxY = ceil(maxY / 10) * 10;
        } 
        
        if (maxY > 100 && maxY < 1000) {
            maxY = ceil(maxY / 100) * 100;
        } 
        
        if (maxY > 1000 && maxY < 10000) {
            maxY = ceil(maxY / 1000) * 1000;
        }
        
        if (maxY > 10000 && maxY < 100000) {
            maxY = ceil(maxY / 10000) * 10000;
        }
        //将最小值取整
        if (minY < 100) {
            minY = minY/2;
        } 
        
        if (minY > 100 && minY < 1000) {
            minY = (float)((int)(minY / 100 -0.5) * 100);
        } 
        
        if (minY > 1000 && minY < 10000) {
            minY = (float)((int)(minY / 1000 -0.5) * 1000);
        }
        
        if (minY > 10000 && minY < 100000) {
            minY = (float)((int)(minY / 10000 -0.5) * 10000);
        }
         */
    maxY = maxY + maxY/10 ;
    minY = minY - minY/10;
    if (minY > maxY) {
        minY = 0;
    }
    CGFloat step = (maxY - minY) / STEPYPOINT;//将Y方向分为六份
    CGFloat stepY = (FRAMEHEIGHT - (offsetY * 2)) / (maxY - minY);//计算Y方向的间隔
	
	for (NSUInteger i = 0; i < (STEPYPOINT+1); i++) 
    {//勾画出界面的轮廓，虚线以及数字信息
		
		NSUInteger y = (i * step) * stepY;
		NSUInteger value = i * step + minY;
		
		if (_drawGridY) {
			
			CGContextSetLineWidth(c, 0.1f);
			CGPoint startPoint = CGPointMake(0, FRAMEHEIGHT - y - offsetY);
			CGPoint endPoint = CGPointMake(5.0, FRAMEHEIGHT - y - offsetY);

			
            if (i%2 == 1) {
                CGRect currentRect = CGRectMake(startPoint.x, startPoint.y, 480, stepY*step);
                CGContextSetFillColorWithColor(c, self.xValuesColor.CGColor);
                CGContextAddRect(c, currentRect);
                CGContextDrawPath(c, kCGPathFillStroke);
            }
            if( i == STEPYPOINT ){
                CGRect currentRect = CGRectMake(0, FRAMEHEIGHT - offsetY, 480, offsetY);
                CGContextSetFillColorWithColor(c, self.gridYColor.CGColor);
                CGContextAddRect(c, currentRect);
                CGContextDrawPath(c, kCGPathFillStroke);
            }
            CGContextSetLineWidth(c, 1.0f);
            CGContextMoveToPoint(c, startPoint.x, startPoint.y);
			CGContextAddLineToPoint(c, endPoint.x, endPoint.y);
			CGContextClosePath(c);
			
			CGContextSetStrokeColorWithColor(c, [UIColor blackColor].CGColor);
			CGContextStrokePath(c);
            			//CGContextStrokePath(c);
            
		}
		
		if (i > 0 && _drawAxisY) 
        {
			
			NSNumber *valueToFormat = [NSNumber numberWithInt:value];
			NSString *valueString;
			
			if (_yValuesFormatter) {//将数字信息显示在纵轴上
				valueString = [_yValuesFormatter stringForObjectValue:valueToFormat];
			} else {
				valueString = [valueToFormat stringValue];
			}
			
			[self.yValuesColor set];
			CGRect valueStringRect = CGRectMake(3.0f, FRAMEHEIGHT - y - offsetY, 50.0f, 20.0f);
			
			[valueString drawInRect:valueStringRect withFont:font
					  lineBreakMode:UILineBreakModeTailTruncation alignment:UITextAlignmentLeft];
		}
	}

     
}

- (void)reloadData {
	
	[self setNeedsDisplay];
}


 - (void)btAction:(id)sender{
}


#pragma mark PrivateMethods

- (void)initializeComponent {
	
	_drawAxisX = YES;
	_drawAxisY = YES;
	_drawGridX = YES;
	_drawGridY = YES;
	
	_xValuesColor = [RGB(235, 235, 235) retain];
	_yValuesColor = [[UIColor blackColor] retain];
	
	_gridXColor = [RGB(245, 245, 245) retain];
	_gridYColor = [RGB(213, 213, 213) retain];
	
	_drawInfo = YES;
	_infoColor = [[UIColor blackColor] retain];
}

@end

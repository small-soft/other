//
//  QFQuartzFunView.m
//  QuartzFun
//
//  Created by 佳 刘 on 12-10-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "QFGLFunView.h"
#import "QFUIColor-Random.h"
#import "Texture2D.h"

@implementation QFGLFunView
@synthesize firstTouch;
@synthesize lastTouch;
@synthesize currentColor;
@synthesize shapeType;
@synthesize useRandomColor;
@synthesize sprite;

- (CGRect)currentRect {
    return  CGRectMake((firstTouch.x > lastTouch.x) ? lastTouch.x:firstTouch.x,(firstTouch.y > lastTouch.y)?lastTouch.y:firstTouch.y, fabsf(firstTouch.x - lastTouch.x), fabsf(firstTouch.y-lastTouch.y));
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        self.currentColor = [UIColor redColor];
        self.useRandomColor = NO;
        
        self.sprite = [[Texture2D alloc]initWithImage:[UIImage imageNamed:@"iphone.png"]];
        
        glBindTexture(GL_TEXTURE_2D, sprite.name);
        
    }
    
    return self;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

- (void)draw {
    glLoadIdentity();
    
    glClearColor(0.78f, 0.78f, 0.78f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    CGColorRef color = currentColor.CGColor;
    const CGFloat *components = CGColorGetComponents(color);
    CGFloat red = components[0];
    CGFloat green = components[1];
    CGFloat blue = components[2];

    glColor4f(red, green, blue, 1.);
    
    switch (shapeType) {
        case kLineShape:
            glDisable(GL_TEXTURE_2D);
            GLfloat vertices[4];
            
            vertices[0] = firstTouch.x;
            vertices[1] = self.frame.size.height - firstTouch.y;
            vertices[2] = lastTouch.x;
            vertices[3] = self.frame.size.height - lastTouch.y;
            glLineWidth(2.0);
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glDrawArrays(GL_LINES, 0, 2);
            break;
            
        case kRectShape:
            glDisable(GL_TEXTURE_2D);
            
            GLfloat rectVertices[8];
            GLfloat minX = (firstTouch.x > lastTouch.x) ? lastTouch.x:firstTouch.x;
            
            GLfloat minY = (self.frame.size.height - firstTouch.y > self.frame.size.height - lastTouch.y)?self.frame.size.height - lastTouch.y:self.frame.size.height - firstTouch.y;
            
            GLfloat maxX = (firstTouch.x > lastTouch.x)?firstTouch.x:lastTouch.x;
            
            GLfloat maxY = (self.frame.size.height - firstTouch.y > self.frame.size.height - lastTouch.y)?self.frame.size.height - firstTouch.y:self.frame.size.height - lastTouch.y;
            
            rectVertices[0] = maxX;
            rectVertices[1] = maxY;
            rectVertices[2] = minX;
            rectVertices[3] = maxY;
            rectVertices[4] = minX;
            rectVertices[5] = minY;
            rectVertices[6] = maxX;
            rectVertices[7] = minY;
            
            glVertexPointer(2, GL_FLAT, 0, vertices);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            
            
            break;
        default:
            break;
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    if (useRandomColor) {
        self.currentColor = [UIColor randomColor];
    }
    
    // 获取起始点
    UITouch *touch = [touches anyObject];
    firstTouch = [touch locationInView:self];
    lastTouch = [touch locationInView:self];
    
    // 整体重绘
    [self draw];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    // 获取重点
    UITouch *touch = [touches anyObject];
    lastTouch = [touch locationInView:self];
    
    [self draw];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    lastTouch = [touch locationInView:self];
    
    // 整体重绘
    [self draw];
}

- (void)dealloc {
    [currentColor release];    
    [super dealloc];
}

@end

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
    
    // 设置颜色
    CGColorRef color = currentColor.CGColor;
    const CGFloat *components = CGColorGetComponents(color);
    CGFloat red = components[0];
    CGFloat green = components[1];
    CGFloat blue = components[2];

    glColor4f(red, green, blue, 1.);
    
    switch (shapeType) {
        // 画线
        case kLineShape:
            // 关闭映像纹理的功能，如果允许使用纹理，则不会显示刚才设置的颜色
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
        // 四边形
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
        // 椭圆
        case kEclipseShape:
            glDisable(GL_TEXTURE_2D);
            GLfloat eVertices[720];
            GLfloat xradius = (firstTouch.x > lastTouch.x) ? (firstTouch.x - lastTouch.x)/2 : (lastTouch.x - firstTouch.x)/2;
            GLfloat yradius = (self.frame.size.height - firstTouch.y > self.frame.size.height - lastTouch.y) ? ((self.frame.size.height - firstTouch.y) - (self.frame.size.height - lastTouch.y))/2:((self.frame.size.height - lastTouch.y) - (self.frame.size.height - firstTouch.y))/2;
            
            for (int i = 0; i<720; i+=2) {
                GLfloat xOffset = (firstTouch.x > lastTouch.x)?lastTouch.x +xradius:lastTouch.x + xradius;
                GLfloat yOffset = (self.frame.size.height - firstTouch.y > self.frame.size.height - lastTouch.y)?self.frame.size.height - lastTouch.y + yradius:self.frame.size.height - firstTouch.y + yradius;
                eVertices[i] = (cos(degreesToRadian(i/2))*xradius) + xOffset;
                eVertices[i+1] = (sin(degreesToRadian(i/2))*yradius) + yOffset;
            }
            
            glVertexPointer(2, GL_FLAT, 0, eVertices);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
            
            break;
            
        case kImageShape:
            glEnable(GL_TEXTURE_2D);
            [sprite drawAtPoint:CGPointMake(lastTouch.x, self.frame.size.height - lastTouch.y)];
            
            break;
        default:
            break;
    }
    
    // 完成绘图之后，渲染其缓冲器，并告诉视图上下文显示新渲染的缓冲器
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
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

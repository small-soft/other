//
//  QFQuartzFunView.h
//  QuartzFun
//
//  Created by 佳 刘 on 12-10-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Constants.h"
#import "OpenGLES2DView.h"

@class Texture2D;

@interface QFGLFunView : OpenGLES2DView {
    CGPoint firstTouch;
    CGPoint lastTouch;
    UIColor *currentColor;
    BOOL useRandomColor;
    
    ShapeType shapeType;
    Texture2D *sprite;
}

@property CGPoint firstTouch;
@property CGPoint lastTouch;
@property (nonatomic,retain) UIColor *currentColor;
@property ShapeType shapeType;
@property BOOL useRandomColor;
@property (nonatomic,retain) Texture2D *sprite;

@end

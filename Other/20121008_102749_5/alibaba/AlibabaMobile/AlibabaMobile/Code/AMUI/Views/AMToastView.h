//
//  AMToastView.h
//  AlibabaMobile
//
//  Created by  on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define DEFAULT_TOAST_X  60
#define DEFAULT_TOAST_Y  144
#define DEFAULT_TOAST_WIDTH  200
#define DEFAULT_TOAST_HEIGHT  70

#define LABEL_MAX_WIDTH  180
#define LABEL_MAX_HEIGTH 80

#define AMTOAST_STYLE_COMMON  0
#define AMTOAST_STYLE_SUCC  1
#define AMTOAST_STYLE_FAIL  2
#define AMTOAST_STYLE_FAV  3
#define AMTOAST_SHOW_TIME  2

@interface AMToastView : UIView
{
    UILabel * _textLabel;
    UIImageView * _typeImage;
    int _type;
    NSString * _text;
}

+ (AMToastView *)MakeToastWithType:(int)type info:(NSString *)text;
- (void) show;
@end

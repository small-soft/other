//
//  AMUIBarButtonItem.m
//  AlibabaMobile
//
//  Created by  on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMUIBarButtonItem.h"
#import "StringUtils.h"
#import "ConstDef.h"

//backbutton 默认字体大小
static const float BACK_BTN_FONT_SIZE = 14.0f;
//backbutton 默认字体颜色
static const int BACK_BTN_FONT_COLOR = 0xffffff;

//backbutton inserts padding
static const float BACK_BTN_LEFT_INSERT = 12.0f;

static const float BACK_BTN_RIGHT_INSERT = 12.0f;

static const float BACK_BTN_TOP_INSERT = 4.0f;

static const float BACK_BTN_BOTTOM_INSERT = 4.0f;

@implementation AMUIBarButtonItem

@synthesize buttonItemClickDelegate = _buttonItemClickDelegate;
@synthesize text = _text;
@synthesize AMStyle = _AMStyle;

- (id) initWithTitle:(NSString *)title style:(AMUIBarButtonItemStyle)style
{
    self = [self init];
    if(self){
        self.text = title;
        self.AMStyle = style;
    }
    
    return self;
}


- (void) setContentView
{
    UIButton * button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.titleLabel.font = [UIFont boldSystemFontOfSize:BACK_BTN_FONT_SIZE];
    button.titleLabel.shadowColor = [UIColor blackColor];
    button.titleLabel.shadowOffset = CGSizeMake(0, -1);
    
    UIImage * btnBackImg;
    UIImage * btnBackImgPressed;
    switch (self.AMStyle) {
        case AMUIBarButtonItemStyleNavMain:{
            btnBackImg = [UIImage imageNamed:@"btn_tb_v"];
            btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
            btnBackImgPressed = [UIImage imageNamed:@"btn_tb_v_tap"];
            btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
            break;
        }
        case AMUIBarButtonItemStyleNavCommon:
        default:{
            btnBackImg = [UIImage imageNamed:@"btn_tb_normal"];
            btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
            btnBackImgPressed = [UIImage imageNamed:@"btn_tb_normal_tap"];
            btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
            break;
        }
    }
    
    
    CGSize textSize = [StringUtils getStringSize:_text font:button.titleLabel.font];
    int buttonWidth = BACK_BTN_LEFT_INSERT + BACK_BTN_RIGHT_INSERT + textSize.width;
    int buttonHeight = btnBackImg.size.height;
    
    button.frame = CGRectMake(0, 0, buttonWidth, buttonHeight); 
    
    [button setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [button setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    
    [button setContentEdgeInsets:UIEdgeInsetsMake(BACK_BTN_TOP_INSERT, BACK_BTN_LEFT_INSERT, BACK_BTN_BOTTOM_INSERT, BACK_BTN_RIGHT_INSERT)];
    
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [button setContentHorizontalAlignment:UIControlContentHorizontalAlignmentRight];
    [button setTitle:_text forState:UIControlStateNormal];
    [button addTarget:self action:@selector(AMUIBarButtonItemClick) forControlEvents:UIControlEventTouchUpInside];
    
    self.customView = button;
}

-(IBAction)AMUIBarButtonItemClick:(id)sender
{
    if(self.buttonItemClickDelegate){
        [self.buttonItemClickDelegate buttonItemClick];
    }
}

- (void)dealloc
{
    AM_RELEASE_SAFELY(_text);
    AM_RELEASE_SAFELY(_buttonItemClickDelegate);
    [super dealloc];
}
@end

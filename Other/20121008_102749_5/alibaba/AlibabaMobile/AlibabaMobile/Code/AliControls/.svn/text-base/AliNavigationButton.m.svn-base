//
//  BackButton.m
//  AlibabaMobile
//
//  Created by xiejin on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

const int NAV_BTN_STYLE_COMMON = 0;
const int NAV_BTN_STYLE_MAIN = 1;

#import "AliNavigationButton.h"
#import "StringUtils.h"


//backbutton 默认字体大小
static const float BACK_BTN_FONT_SIZE = 14.0f;
//backbutton 默认字体颜色
static const int BACK_BTN_FONT_COLOR = 0xffffff;

//backbutton inserts padding
static const float BACK_BTN_LEFT_INSERT = 12.0f;

static const float BACK_BTN_RIGHT_INSERT = 12.0f;

static const float BACK_BTN_TOP_INSERT = 4.0f;

static const float BACK_BTN_BOTTOM_INSERT = 4.0f;

@interface AliNavigationButton ()
{

}

@property (nonatomic, assign) int style;
@property (nonatomic, retain) NSString * text;

- (void) initContentView;

@end


@implementation AliNavigationButton 

@synthesize  navigationButtonDelegate = _navigationButtonDelegate;
@synthesize style = _style;
@synthesize  text = _text;


#pragma mark interface methods


-(id)init
{
    [super init];
    if(self){
        _text = @"";
        _style = NAV_BTN_STYLE_COMMON;
        _navigationButtonDelegate = nil;
    }
    return self;
}

- (id) initWithTitle:(NSString *)title style:(int)style
{
    self = [self init];
    if(self){
        self.text = title;
        self.style = style;
    }
    
    return self;
}


- (void)setText:(NSString *)text
{
    if(_text){
        [_text release];
    }
    _text = [text retain];
    [self initContentView];
}

- (void) initContentView
{
    UIButton * button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.titleLabel.font = [UIFont boldSystemFontOfSize:BACK_BTN_FONT_SIZE];
    button.titleLabel.shadowColor = [UIColor blackColor];
    button.titleLabel.shadowOffset = CGSizeMake(0, -1);
    
    UIImage * btnBackImg;
    UIImage * btnBackImgPressed;
    switch (_style) {
        case NAV_BTN_STYLE_MAIN:{
            btnBackImg = [UIImage imageNamed:@"btn_tb_v"];
            btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
            btnBackImgPressed = [UIImage imageNamed:@"btn_tb_v_tap"];
            btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
            break;
        }   
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
    [button addTarget:self action:@selector(navigationBack) forControlEvents:UIControlEventTouchUpInside];
    
    self.customView = button;
}


- (IBAction) navigationBack
{
    if(self.navigationButtonDelegate){
        [self.navigationButtonDelegate navigationButtonClick];
    }
}

- (void) dealloc
{

    [_text release];
    [super dealloc];
}

@end

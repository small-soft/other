//
//  BackButton.m
//  AlibabaMobile
//
//  Created by xiejin on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliNavigationBackButton.h"
#import "StringUtils.h"



//backbutton 默认字体大小
static const float BACK_BTN_FONT_SIZE = 14.0f;
//backbutton 默认字体颜色
static const int BACK_BTN_FONT_COLOR = 0xffffff;

//backbutton inserts padding
static const float BACK_BTN_LEFT_INSERT = 15.0f;

static const float BACK_BTN_RIGHT_INSERT = 12.0f;

static const float BACK_BTN_TOP_INSERT = 4.0f;

static const float BACK_BTN_BOTTOM_INSERT = 4.0f;

static const int BUTTON_MAX_WIDTH = 94;

@interface AliNavigationBackButton()
{
}

- (IBAction) navigationBack;

@end

@implementation AliNavigationBackButton 

@synthesize  navigationBackDelegate = _navigationBackDelegate;

#pragma mark interface methods


- (id) initWithTitle:(NSString *)title
{
    self = [super init ];
    if(self){
        self.navigationBackDelegate = nil;
        
        [self setTitle:title];
    }

    return self;
}


-(void) setTitle:(NSString *)title
{
    UIButton * button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.titleLabel.font = [UIFont boldSystemFontOfSize:BACK_BTN_FONT_SIZE];
    button.titleLabel.shadowColor = [UIColor blackColor];
    button.titleLabel.shadowOffset = CGSizeMake(0, -1);
    
    UIImage * btnBackImg = [UIImage imageNamed:@"btn_tb_back"];
    btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
    
    UIImage * btnBackImgPressed = [UIImage imageNamed:@"btn_tb_back_tap"];
    btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];

    
    CGSize textSize = [StringUtils getStringSize:title font:button.titleLabel.font];
    int buttonWidth = BACK_BTN_LEFT_INSERT + BACK_BTN_RIGHT_INSERT + textSize.width;
    int buttonHeight = btnBackImg.size.height;
    buttonWidth = (buttonWidth >BUTTON_MAX_WIDTH?BUTTON_MAX_WIDTH:buttonWidth);
    button.titleLabel.lineBreakMode = UILineBreakModeTailTruncation;
    
    button.frame = CGRectMake(0, 0, buttonWidth, buttonHeight); 
    
    [button setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [button setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [button setContentEdgeInsets:UIEdgeInsetsMake(BACK_BTN_TOP_INSERT, BACK_BTN_LEFT_INSERT, BACK_BTN_BOTTOM_INSERT, BACK_BTN_RIGHT_INSERT)];
    
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [button setContentHorizontalAlignment:UIControlContentHorizontalAlignmentRight];
    [button setTitle:title forState:UIControlStateNormal];
    [button addTarget:self action:@selector(navigationBack) forControlEvents:UIControlEventTouchUpInside];
    
    self.customView = button;
    
}


- (IBAction) navigationBack
{
    if(self.navigationBackDelegate){
        [self.navigationBackDelegate navigationBack];
    }
}

- (void) dealloc
{
    [_navigationBackDelegate release];
    [super dealloc];
}

@end

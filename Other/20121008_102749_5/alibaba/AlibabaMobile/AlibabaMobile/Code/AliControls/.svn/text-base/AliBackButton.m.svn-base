//
//  BackButton.m
//  AlibabaMobile
//
//  Created by xiejin on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliBackButton.h"
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


@interface AliBackButton()
{

}

- (IBAction) navigationBack;

@end

@implementation AliBackButton 

@synthesize  navigationBackDelegate = _navigationBackButton;

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
    self.titleLabel.font = [UIFont boldSystemFontOfSize:BACK_BTN_FONT_SIZE];
    self.titleLabel.shadowColor = [UIColor blackColor];
    self.titleLabel.shadowOffset = CGSizeMake(0, -1);
    
    UIImage * btnBackImg = [UIImage imageNamed:@"btn_tb_back"];
    btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
    
    UIImage * btnBackImgPressed = [UIImage imageNamed:@"btn_tb_back_tap"];
    btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
    
    
    CGSize textSize = [StringUtils getStringSize:title font:self.titleLabel.font];
    int buttonWidth = BACK_BTN_LEFT_INSERT + BACK_BTN_RIGHT_INSERT + textSize.width;
    int buttonHeight = btnBackImg.size.height;
    self.titleLabel.lineBreakMode = UILineBreakModeTailTruncation;
    NSLog(@"buttonwidth: %d", buttonWidth);
    
    self.frame = CGRectMake(0, 0, buttonWidth, buttonHeight); 
    
    [self setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [self setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [self setContentEdgeInsets:UIEdgeInsetsMake(BACK_BTN_TOP_INSERT, BACK_BTN_LEFT_INSERT, BACK_BTN_BOTTOM_INSERT, BACK_BTN_RIGHT_INSERT)];
    
    [self setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self setContentHorizontalAlignment:UIControlContentHorizontalAlignmentRight];
    [self setTitle:title forState:UIControlStateNormal];
    [self addTarget:self action:@selector(navigationBack) forControlEvents:UIControlEventTouchUpInside];    
}

- (void) setButtonImageNormal:(NSString *)normal pressed:(NSString *)pressed
{
    NSString * title = self.titleLabel.text;
    self.titleLabel.font = [UIFont boldSystemFontOfSize:BACK_BTN_FONT_SIZE];
    
    UIImage * btnBackImg = [UIImage imageNamed:normal];
    btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
    
    UIImage * btnBackImgPressed = [UIImage imageNamed:pressed];
    btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
    
    
    CGSize textSize = [StringUtils getStringSize:title font:self.titleLabel.font];
    int buttonWidth = BACK_BTN_LEFT_INSERT + BACK_BTN_RIGHT_INSERT + textSize.width;
    int buttonHeight = btnBackImg.size.height;
    
    self.frame = CGRectMake(0, 0, buttonWidth, buttonHeight); 
    
    [self setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [self setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [self setContentEdgeInsets:UIEdgeInsetsMake(BACK_BTN_TOP_INSERT, BACK_BTN_LEFT_INSERT, BACK_BTN_BOTTOM_INSERT, BACK_BTN_RIGHT_INSERT)];
    
    [self setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self setContentHorizontalAlignment:UIControlContentHorizontalAlignmentRight];
    [self setTitle:title forState:UIControlStateNormal];
    [self addTarget:self action:@selector(navigationBack) forControlEvents:UIControlEventTouchUpInside]; 
}


- (IBAction) navigationBack
{
    if(self.navigationBackDelegate){
        [self.navigationBackDelegate navigationBack];
    }
}

- (void) dealloc
{
    self.navigationBackDelegate = nil;
    [super dealloc];
}

@end

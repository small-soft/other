//
//  AliRightBarButtonItem.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliRightBarButtonItem.h"
#import "AliUIButton.h"
#define TITLE_FONT_SIZE (14.0)
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AliRightBarButtonItem()
@property (nonatomic,retain) NSMutableArray*buttonArray;
@property (nonatomic,retain)UIView * buttonsView;
@property (nonatomic,assign)NSUInteger totalCount;
@end
@implementation AliRightBarButtonItem
@synthesize buttonArray=_buttonArray;
@synthesize buttonsView=_buttonsView;
@synthesize delegate=_delegate;
@synthesize totalCount = _totalCount;
-(void)dealloc
{
    [_buttonArray release];
    [_buttonsView release];
    [_delegate release];
    [super dealloc];
    
}

-(NSMutableArray*)buttonArray
{
    if (!_buttonArray) {
        _buttonArray = [[NSMutableArray alloc]init];
    }
    return _buttonArray;
}
-(UIView*)buttonsView
{
    if (!_buttonsView) {
        //解决类目title无法显示的bug  -->modify by xiaowen
        _buttonsView = [[UIView alloc] initWithFrame:CGRectMake(320 - self.totalCount*60, 0, self.totalCount * 60, 40)];
    }
    return _buttonsView;
}
-(void)buttonTouchUpInside:(AliUIButton*)button
{
    if ([self.delegate respondsToSelector:@selector(AliRightBarButtonItem:)]) {
        [self.delegate AliRightBarButtonItem:button.tag];
    }
}
-(AliUIButton*)createButton:(NSString*)title
{
    AliUIButton *button = [AliUIButton buttonWithType:UIButtonTypeCustom];
    [button setTitleColor:RGB(0xff,0xff,0xff) forState:UIControlStateNormal];
    [button setTitleColor:RGB(0xff,0xff,0xff) forState:UIControlStateHighlighted];
    [button setTitleColor:RGB(0xff,0xff,0xff) forState:UIControlStateSelected];
    

    button.titleLabel.font = [UIFont boldSystemFontOfSize:TITLE_FONT_SIZE]; 
    button.titleLabel.shadowColor = [UIColor blackColor];
    button.titleLabel.shadowOffset = CGSizeMake(0, -1);

    
   
    
    
    CGSize textSize = [title sizeWithFont:button.titleLabel.font];
    
    UIImage *buttonImage = [UIImage imageNamed:@"btn_tb_normal"];
    UIImage *btnBackImgPressed = [UIImage imageNamed:@"btn_tb_normal_tap"];
  
    AliUIButton *lastButton = [self.buttonArray lastObject];
    CGFloat endX = 0,buttonWidth=0;
    buttonWidth = textSize.width+20.0;
    //使用的是栈的形式绘制。。。所以尼玛这要从最右边开始。。。
    if (lastButton) {
        endX = lastButton.frame.origin.x - 10.0;
    }
    else {
        endX = self.buttonsView.frame.size.width;
        
    }
    button.frame = CGRectMake(endX - buttonWidth, (self.buttonsView.frame.size.height - buttonImage.size.height)/2, buttonWidth, buttonImage.size.height);
     [button setContentEdgeInsets:UIEdgeInsetsMake((buttonImage.size.height - textSize.height)/2, 10, (buttonImage.size.height - textSize.height)/2, 10)];
  
    [button setBackgroundImage:buttonImage forState:UIControlStateNormal];
    [button setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [button setBackgroundImage:btnBackImgPressed forState:UIControlStateSelected];
    [button setTitle:title forState:UIControlStateNormal];
    [button setTitle:title forState:UIControlStateHighlighted];
    [button setTitle:title forState:UIControlStateSelected];
    

    button.tag = [self.buttonArray count];
    [button addTarget:self action:@selector(buttonTouchUpInside:) forControlEvents:UIControlEventTouchUpInside];
       return button;
}

-(void)setupView:(NSArray*)titles
{
    for (NSString*title in titles) {
        AliUIButton* button = [self createButton:title];
        if (button) {
            [self.buttonArray addObject:button];
        }
        [self.buttonsView addSubview:button];
    }
    //AliUIButton *lastButton = [self.buttonArray lastObject];

    //self.buttonsView.frame = CGRectMake(lastButton.frame.origin.x, 0, 320-lastButton.frame.origin.x, 40);
    
}
+(AliRightBarButtonItem*)createView:(NSArray*)titles
{
    AliRightBarButtonItem *barItem = [[[AliRightBarButtonItem alloc] init] autorelease];
    barItem.totalCount = [titles count];
    barItem.customView = barItem.buttonsView;
    [barItem setupView:titles];
    return barItem;
}


@end

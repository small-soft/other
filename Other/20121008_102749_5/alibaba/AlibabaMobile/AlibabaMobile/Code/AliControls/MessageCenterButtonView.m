//
//  MessageCenterButtonView.m
//  AlibabaMobile
//
//  Created by  on 12-2-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MessageCenterButtonView.h"

@interface MessageCenterButtonView()

@property (nonatomic, retain) UIImageView * secepter;
@property (nonatomic, retain) UIImageView * msgButton;
@property (nonatomic, retain) UILabel * msgLabel;
@property (nonatomic, retain) UILabel * noLoginLabel;

@property (nonatomic, assign) int msgNum;
@property (nonatomic, assign) BOOL logined;

- (void) initContentView;

@end

@implementation MessageCenterButtonView

@synthesize secepter = _secepter;
@synthesize  msgLabel = _msgLabel;
@synthesize  msgButton = _msgButton;
@synthesize msgNum = _msgNum;
@synthesize logined = _logined;
@synthesize hightlightedImg = _hightlightedImg;
@synthesize noLoginLabel = _noLoginLabel;

-(id)initWithState:(BOOL)state num:(int)number
{
    [super init];
    if(self){
        self.msgNum = number;
        self.logined = state;
        
        [self initContentView];
    }
    return self;
}

- (void)dealloc
{
    [self.secepter release];
    [self.msgButton release];
    [self.msgLabel release];
    [self.hightlightedImg release];
    [self.noLoginLabel release];
    [super dealloc];
}

- (void) initContentView
{
    int tempX = 0;
    UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"m_line"]];
    imageViewTmp.alpha = 0.0;
    self.secepter = imageViewTmp;
    [imageViewTmp release];
    [self.secepter sizeToFit];
    self.secepter.frame = CGRectMake(0, 0, self.secepter.frame.size.width, self.secepter.frame.size.height);
    [self addSubview:self.secepter];
    tempX += (self.secepter.frame.size.width + 10);
    
    
    //消息中心按钮颜色不同，以背景图片方式实现
//    UIImageView * buttonBg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"message_bg"]];
//    buttonBg.alpha = 0.0;
//    
//    [buttonBg sizeToFit];
//    
//    buttonBg.frame = CGRectMake(self.secepter.frame.size.width, 0, buttonBg.frame.size.width + 10, 44);
//    
//    [self addSubview:buttonBg];
//    [buttonBg release];
    
    if(self.logined){
        [self.noLoginLabel setHidden:YES];
        self.msgButton.frame = CGRectMake(tempX, (44-self.msgButton.frame.size.height)/2, self.msgButton.frame.size.width, self.msgButton.frame.size.height);
    }else {
            
        UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_topbar_infocenter"]];
        self.msgButton = imageViewTmp;
        [imageViewTmp release];
        [self.noLoginLabel setHidden:YES];
        self.msgButton.frame = CGRectMake(tempX, (44-self.msgButton.frame.size.height)/2, self.msgButton.frame.size.width, self.msgButton.frame.size.height);
//        self.msgButton.frame = CGRectMake(tempX, (44-self.msgButton.frame.size.height)/2-8, self.msgButton.frame.size.width, self.msgButton.frame.size.height);
//        self.noLoginLabel = [[UILabel alloc] initWithFrame:CGRectMake(tempX-4, (44-self.msgButton.frame.size.height)/2+4, self.msgButton.frame.size.width+10, self.msgButton.frame.size.height+10)];
//        self.noLoginLabel.text = @"未登录";
//        self.noLoginLabel.backgroundColor = [UIColor clearColor];
//        self.noLoginLabel.font = [UIFont boldSystemFontOfSize:10.0f];
//        self.noLoginLabel.textColor = [UIColor whiteColor];
//        self.noLoginLabel.textAlignment = UITextAlignmentCenter;
//        if(self.noLoginLabel){
//            [self addSubview:self.noLoginLabel];
//        }
//         [self.noLoginLabel setHidden:YES];
    }
    
    [self.msgButton sizeToFit];
    [self addSubview:self.msgButton];
    _hightlightedImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_topbar_infocenter_p"]];
    self.hightlightedImg.alpha = 0.0f;
    self.hightlightedImg.frame = self.msgButton.frame;
    [self addSubview:self.hightlightedImg];
    
  
    tempX += (self.msgButton.frame.size.width + 10);
    
   
    if(self.logined == YES){
        
        self.msgLabel = [[UILabel alloc] init];
        self.msgLabel.text = [[NSNumber numberWithInt: self.msgNum] stringValue];
        
        self.msgLabel.textAlignment = UITextAlignmentCenter;
        
        self.msgLabel.font = [UIFont boldSystemFontOfSize:14.0f];
        
        if(self.msgNum>=0&&self.msgNum<10){
            self.msgLabel.font = [UIFont boldSystemFontOfSize:12.0f];
        }else if(self.msgNum>=10&&self.msgNum<=99){
            self.msgLabel.font = [UIFont boldSystemFontOfSize:10.0f];
        }else if(self.msgNum>=100){
            self.msgLabel.font = [UIFont boldSystemFontOfSize:10.0f];
            self.msgLabel.text = @"...";
        }
        
        self.msgLabel.textColor = [UIColor whiteColor];
        [self.msgLabel sizeToFit];
        //UIColor * color = [UIColor colorWithPatternImage:[UIImage imageNamed:@"message"]];
        //self.msgLabel.backgroundColor = color;
        self.msgLabel.backgroundColor = [UIColor clearColor];
        
//        self.msgLabel.frame = CGRectMake(tempX, (44 - self.msgLabel.frame.size.height)/2, self.msgLabel.frame.size.width, self.msgLabel.frame.size.height);
//   self.msgLabel.frame = CGRectMake(tempX-20, 0, 30, 30);  
        self.msgLabel.frame = CGRectMake(tempX-20, 5, 17, 17); 
        
#warning 修改人 孟希羲 针对iphone 3gs下消息中心图片显示不正常问题进行修改
        UIImageView *imageViewLable= [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"message"]];
        //imageViewLable.frame = CGRectMake(tempX, (44 - self.msgLabel.frame.size.height)/2, self.msgLabel.frame.size.width, self.msgLabel.frame.size.height);
        imageViewLable.center = CGPointMake( self.msgLabel.center.x + 1,  self.msgLabel.center.y);
        [self addSubview:imageViewLable];
        [imageViewLable release];
        [self addSubview:self.msgLabel];

//        tempX +=(self.msgLabel.frame.size.width + 10);
        tempX +=(self.msgLabel.frame.size.width-20 );
    }

//    self.frame = CGRectMake(0, 0, tempX, 44);
    self.frame = CGRectMake(0, 0, tempX, 44);
    [self addTarget:self action:@selector(highlightedAction:) forControlEvents:UIControlEventTouchDown];
    
    [self addTarget:self action:@selector(cancelHightedAction:) forControlEvents:UIControlEventTouchUpOutside];
}

- (IBAction)highlightedAction:(id)sender
{
    self.hightlightedImg.alpha = 1.0f;
//    self.hightlightedImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@""]];
//    self.hightlightedImg.tag = 0;
//    [self.hightlightedImg sizeToFit];
//    self.hightlightedImg.frame = CGRectMake((self.frame.size.width-self.hightlightedImg.frame.size.width)/2, (self.frame.size.height-self.hightlightedImg.frame.size.height)/2, self.hightlightedImg.frame.size.width, self.hightlightedImg.frame.size.height);
//    [self insertSubview:self.hightlightedImg atIndex:0];
}

- (IBAction)cancelHightedAction:(id)sender
{
    self.hightlightedImg.alpha = 0.0f;
//    [self.hightlightedImg release];
//    UIView * view = [self viewWithTag:0];
//    [view removeFromSuperview];
}

- (void) setMsgNum:(int)msgNum
{
    _msgNum = msgNum;
    [self initContentView];
}

- (void) changeLoginState:(BOOL)state
{
    self.logined = state;
    [self initContentView];
}

@end

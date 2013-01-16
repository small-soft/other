//
//  WwStatePickView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "WwNoticePickView.h"
#import "UIHelp.h"
#import "StringUtils.h"

@interface WwNoticePickView()
{
    int _type;
}

@end

@implementation WwNoticePickView

@synthesize delegate = _delegate;

- (void) dealloc
{
    [_delegate release];
    [super dealloc];
}

- (id) initWithMusic:(bool)music shake:(bool)shake
{
    
    self = [super init];
    if(self){
        _type = [self getSelectedIndexWithMusic:music shake:shake];
        [self initComponents];             
        
    }
    return self;
}

- (void) initComponents
{
    for(UIView *view in [self subviews])
    {
        [view removeFromSuperview];
    }
    
    self.frame = CGRectMake(0, 0 , 320, 480);
    self.backgroundColor = [UIColor clearColor];
    
    UIImageView * bkView = [[UIImageView alloc] init ];
    bkView.frame = CGRectMake(0, 64, 320, 436);
    bkView.backgroundColor = [UIColor blackColor];
    bkView.alpha = 0.5;
    [self addSubview:bkView];
    [bkView release];
    
    UIView * seceptorView = [[UIView alloc] init ];
    seceptorView.frame = CGRectMake(0, 298, 320, 2);
    seceptorView.backgroundColor = [UIHelp colorWithHexString:@"0xff7300"];
    [self addSubview:seceptorView];
    [seceptorView release];
    
    int size = 4;
    int selectedIndex = _type;
    for(int i=0; i<size; i++){
        UIButton * btn = [[UIButton alloc] initWithFrame:CGRectMake(0, 300 + 45*i, 320, 45)];
        btn.backgroundColor = [UIColor whiteColor];
        [btn setBackgroundImage:[UIImage imageNamed:@"bg_listclick"] forState:UIControlStateHighlighted];
        
        UIImageView * imageView = [[UIImageView alloc] initWithFrame:CGRectMake(10, 7, 30, 30)];
        imageView.backgroundColor = [UIColor clearColor];
        
        UILabel * textLabel = [[UILabel alloc] initWithFrame:CGRectMake(50, 7, 150, 30)];
        textLabel.backgroundColor = [UIColor clearColor];
        textLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
        textLabel.font = [UIFont systemFontOfSize:16.0f];
        
        switch (i) {
            case 0:
                imageView.image = [UIImage imageNamed:@"icon_aliww_music"];
                textLabel.text = @"声音提示";
                break;
            case 1:
                imageView.image = [UIImage imageNamed:@"icon_aliww_zd"];
                textLabel.text = @"震动提示";
                break;
            case 2:
                imageView.image = [UIImage imageNamed:@"icon_aliww_zdl"];
                textLabel.text = @"声音+震动提示";
                break;
            case 3:
                imageView.image = [UIImage imageNamed:@"icon_aliww_jy"];
                textLabel.text = @"静音";
                break;
            default:
                break;
        }
        
        
        [btn addSubview:imageView];
        [imageView release];
        [btn addSubview:textLabel];
        [textLabel release];
        
        if(selectedIndex == i){
            UIImageView * selectedView = [[UIImageView alloc]  init ];
            selectedView.frame = CGRectMake(270, 7, 30, 30);
            selectedView.image = [UIImage imageNamed:@"icon_list_Checkmark"];
            [btn addSubview:selectedView];
            [selectedView release];
        }
        
        UIImageView * lineGray = [[UIImageView alloc] init ];
        lineGray.frame = CGRectMake(0, 44, 320, 1);
        lineGray.image = [UIImage imageNamed:@"line_gray"];
        [btn addSubview:lineGray];
        [lineGray release];
        
        btn.tag = i;
        [btn addTarget:self action:@selector(itemClick:) forControlEvents:UIControlEventTouchUpInside];    
        [self addSubview:btn];
        [btn release];
    }
    
}

- (int) getSelectedIndexWithMusic:(bool)music shake:(bool)shake
{
    if(music){
        if(shake){
            return 2;
        }else{
            return 0;
        }
    }else{
        if(shake){
            return 1;
        }else{
            return 3;
        }
    }
}

- (IBAction) itemClick:(id)sender
{
    int index = ((UIButton *)sender).tag;
    _type = index;
    
    if(_delegate){
        bool music = NO;
        bool shake = NO;
        switch (index) {
            case 0:
                music = YES;
                shake = NO;
                break;
            case 1:
                music = NO;
                shake = YES;
                break;
            case 2:
                music = YES;
                shake = YES;
                break;
            case 3:
                music = NO;
                shake = NO;
                break;
            default:
                music = YES;
                shake = NO;
                break;
        }

        [_delegate noticePickedMusic:music shake:shake];
    }
    [self initComponents];
    
    [UIView setAnimationDuration:0.7];
    [UIView beginAnimations:@"hide" context:nil];
    self.alpha = 0.0f;
    [UIView commitAnimations];
}

@end

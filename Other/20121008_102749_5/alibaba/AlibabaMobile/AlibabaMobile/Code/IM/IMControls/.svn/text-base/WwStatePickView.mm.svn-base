//
//  WwStatePickView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>

#import "WwStatePickView.h"
#import "UIHelp.h"
#import "StringUtils.h"

@interface WwStatePickView()
{
    int _status;
}

@end

@implementation WwStatePickView

@synthesize delegate = _delegate;

- (void) dealloc
{
    [_delegate release];
    [super dealloc];
}

- (id) initWithState:(int)status
{
    
    self = [super init];
    if(self){
        _status = status;
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
    int selectedIndex = [self getSelectedIndex:_status];
    for(int i=0; i<size; i++){
        UIButton * btn = [[UIButton alloc] initWithFrame:CGRectMake(0, 300 + 45*i, 320, 45)];
        btn.backgroundColor = [UIColor whiteColor];
        [btn setBackgroundImage:[UIImage imageNamed:@"bg_listclick"] forState:UIControlStateHighlighted];
        
        UIImageView * imageView = [[UIImageView alloc] initWithFrame:CGRectMake(10, 7, 30, 30)];
        imageView.backgroundColor = [UIColor clearColor];
        
        UILabel * textLabel = [[UILabel alloc] initWithFrame:CGRectMake(50, 7, 100, 30)];
        textLabel.backgroundColor = [UIColor clearColor];
        textLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
        textLabel.font = [UIFont systemFontOfSize:16.0f];
        
        switch (i) {
            case 0:
                imageView.image = [UIImage imageNamed:@"icon_aliww_online"];
                textLabel.text = @"我有空";
                break;
            case 1:
                imageView.image = [UIImage imageNamed:@"icon_aliww_busy"];
                textLabel.text = @"忙碌中";
                break;
            case 2:
                imageView.image = [UIImage imageNamed:@"icon_aliww_hide"];
                textLabel.text = @"隐身";
                break;
            case 3:
                imageView.image = [UIImage imageNamed:@"icon_aliww_outing"];
                textLabel.text = @"离开";
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

- (int) getSelectedIndex:(int)status
{
    switch (status) {
        case IMPREDEFSTATUS_FREE:
            return 0;
        case IMPREDEFSTATUS_BUSY:
            return 1;
        case IMPREDEFSTATUS_INVISIBLE:
            return 2;
        case IMPREDEFSTATUS_AWAY:
            return 3;
            
        default:
            return 0;
    }
}

- (IBAction) itemClick:(id)sender
{
    int index = ((UIButton *)sender).tag;
    
    
    
    if(_delegate){
        int state;
        switch (index) {
            case 0:
                state = IMPREDEFSTATUS_FREE;
                break;
            case 1:
                state = IMPREDEFSTATUS_BUSY;
                break;
            case 2:
                state = IMPREDEFSTATUS_INVISIBLE;
                break;
            case 3:
                state = IMPREDEFSTATUS_AWAY;
                break;
            default:
                state = IMPREDEFSTATUS_FREE;
                break;
        }
        [_delegate statePicked:state];
        _status = state;
        [self initComponents];
    }
    
    [UIView setAnimationDuration:0.7];
    [UIView beginAnimations:@"hide" context:nil];
    self.alpha = 0.0f;
    [UIView commitAnimations];
}

@end

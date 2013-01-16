//
//  AMToastView.m
//  AlibabaMobile
//
//  Created by  on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMToastView.h"
#import "ConstDef.h"

@implementation AMToastView

+ (AMToastView *)MakeToastWithType:(int)type info:(NSString *)text {
    AMToastView * toastView = [[[AMToastView alloc] initWithType:type text:text] autorelease];
    
    return toastView;
}

- (void) show {
    [self performSelectorOnMainThread:@selector(showThread) withObject:nil waitUntilDone:YES];
}

- (void) showThread {
    UIWindow * window = [[UIApplication sharedApplication].windows objectAtIndex:0];
    self.alpha = 0.0;
    [window addSubview:self];
    [NSTimer scheduledTimerWithTimeInterval:(AMTOAST_SHOW_TIME) target:self selector:@selector(hide) userInfo:nil repeats:YES];
    [UIView beginAnimations:@"show" context:NULL];                                                                                   
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];                                                                           
    [UIView setAnimationDuration:0.5];                                                                                               
    self.alpha = 1.0f;                                                                                                        
    [UIView commitAnimations];  
}

- (void)hide {
    [UIView beginAnimations:@"hide" context:NULL];                                                                                  
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];                                                                         
    [UIView setAnimationDelegate:self];                                                                                             
    [UIView setAnimationDidStopSelector:@selector(dismissToast)];                                                                   
    [UIView setAnimationDuration:0.8];                                                                                              
    self.alpha = 0.0f;                                                                                                       
    [UIView commitAnimations];     
}

- (IBAction) dismissToast {
    self.hidden = YES;
    [self removeFromSuperview ];
}

- (id)initWithType:(int) type text:(NSString *)text {
    [super init ];
    if(self){
        [self setContentAndType:type andText:text];
    }
    return self;
}

- (void) setContentAndType:(int)type andText:(NSString *)text{
    _type = type;
    _text = text;
    CGSize labelSize = [_text sizeWithFont:[UIFont boldSystemFontOfSize:16.0f] constrainedToSize:CGSizeMake(LABEL_MAX_WIDTH, LABEL_MAX_HEIGTH) lineBreakMode:UILineBreakModeCharacterWrap];
    
    CGFloat toastTotalHeigth = DEFAULT_TOAST_HEIGHT + labelSize.height;
    
    UIImage * bgImg = [UIImage imageNamed:@"bg_toast"];
    bgImg = [bgImg stretchableImageWithLeftCapWidth:bgImg.size.width/4 topCapHeight:bgImg.size.height/4];
    
    
    UIImageView * bkImgView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, DEFAULT_TOAST_WIDTH, toastTotalHeigth)];
    bkImgView.backgroundColor = [UIColor clearColor];
    bkImgView.image = bgImg;
    
    [self addSubview:bkImgView];
    [bkImgView release];
    
    _typeImage = [[UIImageView alloc] initWithFrame:CGRectMake(85, 15, 30, 30)];
    _typeImage.backgroundColor = [UIColor clearColor];
    _typeImage.contentMode = UIViewContentModeCenter;
    _typeImage.image = [UIImage imageNamed:[self getTypeImage]];
    [self addSubview:_typeImage];
    AM_RELEASE_SAFELY(_typeImage);
    
    _textLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 55, 170, 16)];
    _textLabel.backgroundColor = [UIColor clearColor];
    _textLabel.font = [UIFont boldSystemFontOfSize:16.0f];
    _textLabel.textColor = [UIColor whiteColor];
    _textLabel.textAlignment = UITextAlignmentCenter;
    _textLabel.lineBreakMode = UILineBreakModeCharacterWrap;
    [_textLabel setNumberOfLines:0];
    
    _textLabel.text = _text;
    _textLabel.frame = CGRectMake(10, 55, LABEL_MAX_WIDTH, labelSize.height);
    
    [self addSubview:_textLabel];
    AM_RELEASE_SAFELY(_textLabel);
    
    self.frame = CGRectMake(DEFAULT_TOAST_X, DEFAULT_TOAST_Y, DEFAULT_TOAST_WIDTH, toastTotalHeigth);
}

- (NSString *)getTypeImage {
    switch (_type) {
        case AMTOAST_STYLE_SUCC:
            return @"icon_toast_success";
            break;
        case AMTOAST_STYLE_FAIL:
            return @"icon_toast_info";
            break;
        case AMTOAST_STYLE_FAV:
            return @"icon_fav_toast";
            break;
        default:
            return @"icon_toast_info";
            break;
    }
}

-(void) dealloc {
    AM_RELEASE_SAFELY(_textLabel);
    AM_RELEASE_SAFELY(_typeImage);
    AM_RELEASE_SAFELY(_text);
    
    [super dealloc];
}

@end

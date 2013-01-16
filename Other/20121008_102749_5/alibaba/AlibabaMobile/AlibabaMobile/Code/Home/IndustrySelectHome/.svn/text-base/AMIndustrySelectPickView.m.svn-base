//
//  AMIndustrySelectPickView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-29.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIndustrySelectPickView.h"
#import "UIHelp.h"
#import "StringUtils.h"

@interface AMIndustrySelectPickView()

@end


@implementation AMIndustrySelectPickView
@synthesize delegate = _delegate;
@synthesize lableTitle = _lableTitle;
@synthesize mSelectTypeButtonUp = _mSelectTypeButtonUp;
@synthesize mSelectTypeButtonDown = _mSelectTypeButtonDown;
@synthesize isButtonUp;

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIndustrySelectPickView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMIndustrySelectPickView class]])
        {
            AMIndustrySelectPickView *obj = (AMIndustrySelectPickView *)oneObject;
            [obj initView];
            return obj;
        }
    }
    return nil;
}

- (id)initView
{
    if (self) {
        // Initialization code
//        NSString *strTmp = [NSString stringWithFormat:@"服装服饰"];
//        CGSize labelSizePre = [strTmp sizeWithFont:[UIFont systemFontOfSize:20.0f]];
//        self.lableTitle = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, labelSizePre.width, labelSizePre.height)];
        self.lableTitle.font = [UIFont fontWithName:@"Arial-BoldMT" size:21.0f];
        self.lableTitle.numberOfLines = 1;
        self.lableTitle.lineBreakMode = UILineBreakModeWordWrap;
        self.lableTitle.backgroundColor = [UIColor clearColor];
        self.lableTitle.textColor = [UIColor whiteColor];
        //self.lableTitle.shadowColor = [UIColor blackColor];
        //self.lableTitle.shadowOffset = CGSizeMake(0, -1);
//        self.lableTitle.text = [StringUtils makeTitleFromString:@"" ofLength:13.0f];
        
//        self.lableTitle .text = strTmp;
//        self.lableTitle.center = self.center;
//        [self.lableTitle sizeToFit];

        //self.lableTitle.text = [NSString stringWithFormat:@"服装服饰"];
//        [self addSubview:self.lableTitle];
        self.isButtonUp = false;
        [self addTarget:self action:@selector(selectTypeButtonUp:) forControlEvents:UIControlEventTouchUpInside];
        [self addTarget:self action:@selector(selectTypeButtonDown:) forControlEvents:UIControlEventTouchDown];
        [self addTarget:self action:@selector(selectTypeButtonUpOutside:) forControlEvents:UIControlEventTouchUpOutside];
        self.backgroundColor = [UIColor clearColor];
        self.mSelectTypeButtonDown.backgroundColor = [UIColor clearColor];
        self.mSelectTypeButtonUp.backgroundColor = [UIColor clearColor];
        self.lableTitle.frame =  CGRectMake(self.lableTitle.frame.origin.x + 15, self.lableTitle.frame.origin.y + 1, self.lableTitle.frame.size.width, self.lableTitle.frame.size.height);
        self.mSelectTypeButtonDown.frame =  CGRectMake(self.mSelectTypeButtonDown.frame.origin.x +20, self.mSelectTypeButtonDown.frame.origin.y, self.mSelectTypeButtonDown.frame.size.width, self.mSelectTypeButtonDown.frame.size.height);
        self.mSelectTypeButtonUp.frame =  CGRectMake(self.mSelectTypeButtonUp.frame.origin.x +20, self.mSelectTypeButtonUp.frame.origin.y, self.mSelectTypeButtonUp.frame.size.width, self.mSelectTypeButtonUp.frame.size.height);
        [self.mSelectTypeButtonUp setBackgroundImage:[UIImage imageNamed:@"h_com_drop01_nor"] forState:UIControlStateNormal];
        [self.mSelectTypeButtonDown setBackgroundImage:[UIImage imageNamed:@"h_com_drop_nor"] forState:UIControlStateNormal];
//        [self.mSelectTypeButtonUp sizeToFit];
//        [self.mSelectTypeButtonDown sizeToFit];
    }
    return self;
}

- (void)dealloc {
    [_lableTitle release];
    [_mSelectTypeButtonUp release];
    [_mSelectTypeButtonDown release];

    [super dealloc];
}

-(IBAction)selectTypeButtonUp:(UIButton *)sender
{
//    if (self.isButtonUp) {
//        self.isButtonUp = false;
//        self.mSelectTypeButtonUp.hidden = YES;
//        self.mSelectTypeButtonDown.hidden = NO;
//    }
//    else {
//        self.isButtonUp = true;
//        self.mSelectTypeButtonUp.hidden = NO;
//        self.mSelectTypeButtonDown.hidden = YES;
//    }
    if ([self.delegate respondsToSelector:@selector(industrySelectPickViewEvent)]) {
        [self.delegate industrySelectPickViewEvent];
    }
//    [NSThread sleepForTimeInterval:0.1];
    if (self.isButtonUp) {
        [self.mSelectTypeButtonDown setBackgroundImage:[UIImage imageNamed:@"h_com_drop_nor"] forState:UIControlStateNormal];
    }
    else {
        [self.mSelectTypeButtonUp setBackgroundImage:[UIImage imageNamed:@"h_com_drop01_nor"] forState:UIControlStateNormal];
    }
}
-(IBAction)selectTypeButtonDown:(UIButton *)sender
{
    if (self.isButtonUp) {
        [self.mSelectTypeButtonUp setBackgroundImage:[UIImage imageNamed:@"h_nav_p"] forState:UIControlStateHighlighted];
        [self.mSelectTypeButtonUp setBackgroundImage:[UIImage imageNamed:@"h_nav_p"] forState:UIControlStateNormal];
    }
    else {
        [self.mSelectTypeButtonDown setBackgroundImage:[UIImage imageNamed:@"h_nav_p"] forState:UIControlStateHighlighted];
        [self.mSelectTypeButtonDown setBackgroundImage:[UIImage imageNamed:@"h_nav_p"] forState:UIControlStateNormal];
    }

}
-(IBAction)selectTypeButtonUpOutside:(UIButton *)sender
{
    if (self.isButtonUp) {
        [self.mSelectTypeButtonUp setBackgroundImage:[UIImage imageNamed:@"h_com_drop01_nor"] forState:UIControlStateNormal];
    }
    else {
        [self.mSelectTypeButtonDown setBackgroundImage:[UIImage imageNamed:@"h_com_drop_nor"] forState:UIControlStateNormal];
    }

}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end

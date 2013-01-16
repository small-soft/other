//
//  AMButtonLableView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-18.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMButtonLableView.h"

@implementation AMButtonLableView
@synthesize button = _button;
@synthesize lableTitle = _lableTitle;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code

    }
    return self;
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code
        NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMButtonLableView" owner:self options:nil];
        self = [views objectAtIndex:0];
        
        [self.button.titleLabel setFont:[UIFont boldSystemFontOfSize:14.0f]];
        [self.button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
//        self.button.titleLabel.textAlignment = UITextAlignmentCenter;
        self.button.titleLabel.shadowColor = [UIColor colorWithRed:100/255.0 green:82/255.0 blue:0/255.0 alpha:0.2];
        self.button.titleLabel.shadowOffset = CGSizeMake(-0.5, -0.5);
//        self.button.titleLabel.shadowColor = [UIColor blackColor];
//        self.button.titleLabel.shadowOffset = CGSizeMake(-1, -1);
        self.lableTitle.text = [NSString stringWithString:@""]; 
        self.lableTitle.textColor = [UIColor whiteColor];
        self.lableTitle.hidden = YES;
        
    }
    return self;
}

-(void) dealloc
{
    [_button release];
    [_lableTitle release];
    
    [super dealloc];
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

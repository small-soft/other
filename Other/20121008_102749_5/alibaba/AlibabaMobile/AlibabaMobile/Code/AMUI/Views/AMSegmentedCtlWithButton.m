//
//  AMSegmentedCtlWithButton.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-18.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMSegmentedCtlWithButton.h"

@implementation AMSegmentedCtlWithButton
@synthesize segmentedControl = _segmentedControl;
@synthesize mSegmentedControl = _mSegmentedControl;
@synthesize button = _button;
@synthesize isMSegmentedControl = _isMSegmentedControl;
@synthesize backButton = _backButton;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        _mSegmentedControl = [[AMFavSegmentedControl alloc] initWithFrame:CGRectMake(58, 0, 203, 40)];
        _segmentedControl = [[UISegmentedControl alloc] initWithFrame:CGRectMake(58, 5, 203, 30)];
//  
        [self.mSegmentedControl setBgImage:@"btn_tab_lift_n" WithIndex:BUTTON_INDEX_LEFT WithState:BUTTON_STATE_NORMAL];
        [self.mSegmentedControl setBgImage:@"btn_tab_lift_p" WithIndex:BUTTON_INDEX_LEFT WithState:BUTTON_STATE_SELECTED];
        [self.mSegmentedControl setBgImage:@"btn_tab_middle_n" WithIndex:BUTTON_INDEX_MIDDLE WithState:BUTTON_STATE_NORMAL];
        [self.mSegmentedControl setBgImage:@"btn_tab_middle_p" WithIndex:BUTTON_INDEX_MIDDLE WithState:BUTTON_STATE_SELECTED];
        [self.mSegmentedControl setBgImage:@"btn_tab_right_n" WithIndex:BUTTON_INDEX_RIGHT WithState:BUTTON_STATE_NORMAL];
        [self.mSegmentedControl setBgImage:@"btn_tab_right_p" WithIndex:BUTTON_INDEX_RIGHT WithState:BUTTON_STATE_SELECTED];
        _button = [UIButton buttonWithType:UIButtonTypeCustom];
        self.button.frame = CGRectMake(276, 5, 40, 30);
        UIImage *buttonImage = [UIImage imageNamed:@"btn_tb_normal"];
        UIImage *btnBackImgPressed = [UIImage imageNamed:@"btn_tb_normal_tap"];
        
        
        [self.button setBackgroundImage:buttonImage forState:UIControlStateNormal];
        [self.button setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
//        [self.button setImage:[UIImage imageNamed:@"icon_aliww_re"] forState:UIControlStateNormal];
        [self.button setTitle:@"刷新" forState:UIControlStateNormal];
        [self.button setTitleColor:[UIColor colorWithRed:255/255.0 green:255/255.0 blue:255/255.0 alpha:1.0] forState:UIControlStateNormal];
        
        
        self.button.titleLabel.font = [UIFont boldSystemFontOfSize:14.0]; 
        self.button.titleLabel.shadowColor = [UIColor blackColor];
        self.button.titleLabel.shadowOffset = CGSizeMake(0, -1);


        
//        _backButton= [UIButton buttonWithType:UIButtonTypeCustom];
//        self.backButton.frame = CGRectMake(5, 5, 40, 30);
//        UIImage *buttonBackImage = [UIImage imageNamed:@"btn_tb_back"];
//        UIImage *btnBackBackImgPressed = [UIImage imageNamed:@"btn_tb_back_tap"];
//        
//        
//        [self.backButton setBackgroundImage:buttonBackImage forState:UIControlStateNormal];
//        [self.backButton setBackgroundImage:btnBackBackImgPressed forState:UIControlStateHighlighted];
        
        self.backButton = [[AliBackButton alloc] initWithTitle:@"工具"];
        [self.backButton setButtonImageNormal:@"btn_tb_back" pressed:@"btn_tb_back_tap"];
        self.backButton.frame = CGRectMake(5, 5, self.backButton.frame.size.width, self.backButton.frame.size.height);
//        self.backButton = nil;
        
        self.backButton.hidden = YES;
        
//        self.segmentedControl.tintColor = [UIColor redColor];
        [self ChangeSegmentFont: self.segmentedControl];  
//        self.mSegmentedControl.hidden = YES;
        [self setItemsHidden:UISegmentedControlHidden Hidden:YES];
//        [self.button setTitle:@"刷新" forState:UIControlStateNormal];
//        [self.button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        [self addSubview:self.segmentedControl];
        [self addSubview:self.mSegmentedControl];
        [self addSubview:self.button];
        [self addSubview:self.backButton];
    }
    return self;
}



- (void)setItemsHidden:(NSUInteger)segmentedControlHidden Hidden:(BOOL)hidden
{
    switch (segmentedControlHidden) {
        case UIAMFavSegmentedControlHidden:
            self.isMSegmentedControl = !hidden;
            self.mSegmentedControl.hidden = hidden;
            self.segmentedControl.hidden = !hidden;
            break;
        case UISegmentedControlHidden:
            self.isMSegmentedControl = hidden;
            self.segmentedControl.hidden = hidden;
            self.mSegmentedControl.hidden = !hidden;
            break;
        case UIButtonHidden:
            self.button.hidden = hidden;
            break;
        default:
            self.isMSegmentedControl = !hidden;
            self.mSegmentedControl.hidden = hidden;
            self.segmentedControl.hidden = !hidden;
            break;
    }
}
- (void) setBgImage:(NSString *)imageName WithIndex:(int)index WithState:(int) state
{
    if (self.isMSegmentedControl) {
        [self.mSegmentedControl setBgImage:imageName WithIndex:index WithState:state];
    }
    
}
- (void) setLableTitle:(NSString *)imageName WithIndex:(int)index Visable:(BOOL)visable
{
     if (self.isMSegmentedControl) {
         [self.mSegmentedControl setLableTitle:imageName WithIndex:index Visable:visable];
     }
}
- (void) setDelegate:(id)delegate
{
    if (self.isMSegmentedControl) {
        self.mSegmentedControl.delegate = delegate;
    }
}
- (void) addItem:(NSString *)name
{
    if (self.isMSegmentedControl) {
        [self.mSegmentedControl addItem:name];
    }
}
- (void) setSelectedIndex:(int)index
{
    if (self.isMSegmentedControl) {
        [self.mSegmentedControl setSelectedIndex:index];
    }
    else {
         self.segmentedControl.selectedSegmentIndex = index;//设置默认选择项索引
    }
       
}
- (void) insertSegmentWithTitle:(NSString *)title atIndex:(NSUInteger)index animated:(BOOL)animated
{
    if (self.isMSegmentedControl) {
        [self addItem:title];
    }
    else {
        [self.segmentedControl insertSegmentWithTitle:title atIndex:index animated:animated];
    }
}

- (void)ChangeSegmentFont:(UIView *)aView  
{  
    if ([aView isKindOfClass:[UILabel class]])  
    {  
        UILabel *lb = (UILabel *)aView;  
        [lb setTextAlignment:UITextAlignmentCenter];  
        [lb setFont:[UIFont systemFontOfSize:13]];  
    }  
    NSArray *na = [aView subviews];  
    NSEnumerator *ne = [na objectEnumerator];  
    UIView *subView;  
    while (subView = [ne nextObject])   
    {  
        [self ChangeSegmentFont: subView];  
    }  
}  

- (void) dealloc {
    [_mSegmentedControl release];
    [_backButton release];
    [_button release];
    [_segmentedControl release];
    
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

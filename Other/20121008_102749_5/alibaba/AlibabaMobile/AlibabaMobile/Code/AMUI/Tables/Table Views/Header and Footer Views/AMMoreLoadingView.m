//
//  AMMoreLoadingView.m
//  AlibabaMobile
//
//  Created by  on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMoreLoadingView.h"
#import "ConstDef.h"
@interface AMMoreLoadingView(){
    UILabel * _moreLoadingLabel;
    UIActivityIndicatorView * _moreLoadingIndicator;
}
@property (nonatomic, retain) UILabel * moreLoadingLabel;
@property (nonatomic, retain) UIActivityIndicatorView * moreLoadingIndicator;
@end
@implementation AMMoreLoadingView
@synthesize moreLoadingLabel = _moreLoadingLabel;
@synthesize moreLoadingIndicator = _moreLoadingIndicator;
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:CGRectMake(0, 0, 320, 28 )];
    self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    if (self) {
        // Initialization code
        self.moreLoadingLabel = [self createLabel];
        self.moreLoadingIndicator = [self createIndicator];
    }
    return self;
}

- (UILabel *)createLabel
{
    UILabel *tempLabel = [[UILabel alloc] init];
    [tempLabel setFrame:CGRectMake(60, 0, 240, 28)];
    tempLabel.autoresizingMask =UIViewAutoresizingFlexibleWidth;
    tempLabel.textAlignment = UITextAlignmentCenter;
    tempLabel.text = NSLocalizedString(@"MoreLoading", nil);
    tempLabel.backgroundColor = [UIColor clearColor];
    tempLabel.font = [UIFont fontWithName:@"Heiti SC" size:12];
    [self addSubview:tempLabel];
    return [tempLabel autorelease];
}

-(UIActivityIndicatorView *) createIndicator
{
    UIActivityIndicatorView *tempIndicator = [[UIActivityIndicatorView alloc]init];
    [tempIndicator setFrame:CGRectMake(80, 0, 28 , 28)];
    tempIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
    tempIndicator.autoresizingMask =UIViewAutoresizingFlexibleWidth;
    [tempIndicator startAnimating];
    tempIndicator.backgroundColor = [UIColor clearColor];
    [self addSubview:tempIndicator];
    return [tempIndicator autorelease];
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/
-(void)dealloc
{
    AM_RELEASE_SAFELY(_moreLoadingLabel);
    AM_RELEASE_SAFELY(_moreLoadingIndicator);
    [super dealloc];
}
@end

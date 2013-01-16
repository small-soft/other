//
//  AMTotalCountView.m
//  AlibabaMobile
//
//  Created by  on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMTotalCountView.h"
#import "ConstDef.h"
@interface AMTotalCountView()
@property (nonatomic, retain) UILabel * totalCountResultLabel;
@end
@implementation AMTotalCountView
@synthesize totalCountResultLabel = _totalCountResultLabel;
- (id)init
{
    self = [super initWithFrame:CGRectMake(0, 0, 320, 28 )];
    self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    if (self) {
        // Initialization code
        self.totalCountResultLabel = [self createLabel];
        [self setTotalCount:0];
    }
    return self;
}

- (void)dealloc
{
    AM_RELEASE_SAFELY(_totalCountResultLabel);
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

- (UILabel *)createLabel
{
    UILabel *tempLabel = [[UILabel alloc] init];
    [tempLabel setFrame:CGRectMake(0, 0, 320, 28)];
    tempLabel.autoresizingMask =UIViewAutoresizingFlexibleWidth;
    tempLabel.textAlignment = UITextAlignmentCenter;

    [self addSubview:tempLabel];
    return [tempLabel autorelease];
}

- (void)setTotalCount:(int)totalCount{
    self.totalCountResultLabel.text = [NSString stringWithFormat:@"%@%d%@",NSLocalizedString(@"TotalCountHeader", nil),totalCount,NSLocalizedString(@"TotalCountTail", nil),nil];
}

@end

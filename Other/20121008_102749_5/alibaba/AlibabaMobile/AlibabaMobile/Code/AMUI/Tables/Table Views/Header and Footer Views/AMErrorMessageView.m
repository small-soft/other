//
//  AMErrorMessageView.m
//  AlibabaMobile
//
//  Created by  on 12-9-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMErrorMessageView.h"
#import "ConstDef.h"
@implementation AMErrorMessageView
@synthesize errorMessageLabel = _errorMessageLabel;

- (id)init
{
    self = [super initWithFrame:CGRectMake(0, 0, 320, 28 )];
    self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    if (self) {
        // Initialization code
        self.errorMessageLabel = [self createLabel];
        self.errorMessageLabel.text = @"网络连接失败，请在网络连接正常时重试";
    }
    return self;
}

- (void)dealloc
{
    AM_RELEASE_SAFELY(_errorMessageLabel);
    [super dealloc];
}

- (UILabel *)createLabel
{
    UILabel *tempLabel = [[UILabel alloc] init];
    [tempLabel setFrame:CGRectMake(0, 0, 320, 28)];
    tempLabel.autoresizingMask =UIViewAutoresizingFlexibleWidth;
    tempLabel.textAlignment = UITextAlignmentCenter;
    tempLabel.font = [UIFont fontWithName:@"Heiti SC" size:12];
    tempLabel.numberOfLines = 2;
    tempLabel.backgroundColor = [UIColor clearColor];
    [self addSubview:tempLabel];
    return [tempLabel autorelease];
}
@end

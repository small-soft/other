//
//  NavigationTitleLabel.m
//  AlibabaMobile
//
//  Created by  on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliNavigationTitleLabel.h"
#import "UIHelp.h"
#import "StringUtils.h"

//navigation title font size
const float NAV_TITLE_FONT_SIZE = 20.0f;

//navigation title color
const int NAV_TITLE_FONT_COLOR = 0xffffff;

//navigation title max characters num
const int NAV_TITLE_MAX_CHARS_NUM = 13;

@implementation AliNavigationTitleLabel

- (id) initWithTitle:(NSString *)title
{
    self = [super init];
    if(self){
                
        self.backgroundColor = [UIColor clearColor];
        self.textColor = [UIColor whiteColor];
        self.font = [UIFont boldSystemFontOfSize:NAV_TITLE_FONT_SIZE];
        self.shadowColor = [UIColor blackColor];
        self.shadowOffset = CGSizeMake(0, -1);
        self.text = [StringUtils makeTitleFromString:title ofLength:NAV_TITLE_MAX_CHARS_NUM];
        [self sizeToFit];
    }
    return self;
}

@end

//
//  AMExpressName.m
//  AlibabaMobile
//
//  Created by zzh on 12-2-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMExpressName.h"

@implementation AMExpressName
@synthesize content=_content;
@synthesize button=_button;
@synthesize contentButton = _contentButton;

+(CGFloat)cellHeight
{
    return 44.0;
}
+(NSString*)cellIdentifer
{
    return @"expressName";
}

- (void)dealloc {
    [_content release];
    [_button release];
    [_contentButton release];
    [super dealloc];
}
@end

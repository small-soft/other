//
//  AMExpressHistory.m
//  AlibabaMobile
//
//  Created by zzh on 12-2-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMExpressHistory.h"

@implementation AMExpressHistory
@synthesize content=_content;

+(CGFloat)cellHeight
{
    return 44.0;
}
+(NSString*)cellIdentifer
{
    return @"expressHistory";
}

- (void)dealloc {
    [_content release];
    [super dealloc];
}
@end

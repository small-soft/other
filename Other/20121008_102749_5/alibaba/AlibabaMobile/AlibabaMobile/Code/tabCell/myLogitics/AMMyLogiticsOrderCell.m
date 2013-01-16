//
//  AMMyLogiticsOrderCell.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMyLogiticsOrderCell.h"

@implementation AMMyLogiticsOrderCell
@synthesize name=_name;
@synthesize content=_content;
+(CGFloat)cellHeight
{
    return 44.0;
}
+(NSString*)cellIdentifer
{
    return @"myLogiticsOrder";
}

- (void)dealloc {
    [_name release];
    [_content release];
    [super dealloc];
}

+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMMyLogiticsOrderCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMMyLogiticsOrderCell class]])
        {
            return  (AMMyLogiticsOrderCell *)oneObject;
        }
    }
    return nil;
}

@end

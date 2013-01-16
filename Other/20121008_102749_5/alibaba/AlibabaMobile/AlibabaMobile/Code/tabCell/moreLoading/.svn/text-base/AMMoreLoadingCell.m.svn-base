//
//  AMMoreLoadingCell.m
//  AlibabaMobile
//
//  Created by zzh on 12-2-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMoreLoadingCell.h"

@implementation AMMoreLoadingCell
+(CGFloat)cellHeight
{
    return 28.0;
}
+(NSString*)cellIdentifer
{
    return @"moreLoading";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle]loadNibNamed:@"AMMoreLoadingCell" 
                                                owner:self options:nil];
    for (id oneObject in nib) {
        if ([oneObject isKindOfClass:[AMMoreLoadingCell class]]) {
            AMMoreLoadingCell *obj = (AMMoreLoadingCell *) oneObject;
            obj.selectionStyle = UITableViewCellSelectionStyleGray;
            return obj;
        }
    }
    return nil;
}
@end

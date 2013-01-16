//
//  AMSingleLineWithIconCell.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliTableViewCell.h"
@interface AMSingleLineWithIconCell : AliTableViewCell
@property (retain, nonatomic) IBOutlet UIImageView *icon;
@property (retain, nonatomic) IBOutlet UILabel *content;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
@end

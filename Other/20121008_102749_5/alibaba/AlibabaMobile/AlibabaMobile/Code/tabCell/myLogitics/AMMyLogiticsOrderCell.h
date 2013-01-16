//
//  AMMyLogiticsOrderCell.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliTableViewCell.h"

@interface AMMyLogiticsOrderCell : AliTableViewCell
@property (retain, nonatomic) IBOutlet UILabel *name;
@property (retain, nonatomic) IBOutlet UILabel *content;
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end

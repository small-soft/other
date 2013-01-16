//
//  AMNewsCategoryCell.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AMNewsCategoryCell : UITableViewCell

@property (retain, nonatomic) IBOutlet UILabel *content;
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;

@end

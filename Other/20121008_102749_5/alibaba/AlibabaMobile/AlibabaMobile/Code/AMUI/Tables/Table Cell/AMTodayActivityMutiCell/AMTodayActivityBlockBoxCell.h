//
//  AMTodayActivityBlockBoxCell.h
//  AlibabaMobile
//
//  Created by amon on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMTodayActivityBoxView.h"
@interface AMTodayActivityBlockBoxCell : UITableViewCell
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(NSUInteger)cellBoxViewArrayCount; 
@property (nonatomic,readonly,retain) NSMutableArray* cellBoxViewArray;
@end

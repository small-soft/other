//
//  AMExpressDetailGroupName.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AMExpressDetailGroup : UITableViewCell

@property (retain, nonatomic) IBOutlet UILabel *contentTitle;
@property (retain, nonatomic) IBOutlet UILabel *contentValue;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
@end

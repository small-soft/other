//
//  AMExpressName.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AMExpressName : UITableViewCell
@property (retain, nonatomic) IBOutlet UILabel *content;
@property (retain, nonatomic) IBOutlet UIButton *button;
@property (retain, nonatomic) IBOutlet UIButton *contentButton;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
@end

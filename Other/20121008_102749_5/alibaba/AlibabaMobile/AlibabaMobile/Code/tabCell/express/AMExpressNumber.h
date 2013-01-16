//
//  AMExpressNumber.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AMExpressNumber : UITableViewCell

@property (retain, nonatomic) IBOutlet UITextField *content;

@property (retain, nonatomic) IBOutlet UIButton *button;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;

@end

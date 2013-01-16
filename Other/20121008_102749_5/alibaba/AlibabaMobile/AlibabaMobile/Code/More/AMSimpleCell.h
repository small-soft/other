//
//  AMSimpleCell.h
//  AlibabaMobile
//
//  Created by lih on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface AMSimpleCell : UITableViewCell

@property (retain, nonatomic) IBOutlet UILabel *leftLabel;
@property (retain, nonatomic) IBOutlet UILabel *middleLabel;
@property (retain, nonatomic) IBOutlet UILabel *rightLabel;
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
@end

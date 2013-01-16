//
//  AMOrderLogCell.h
//  AlibabaMobile
//
//  Created by alimobile on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTableViewCell.h"
#import "AliCustomLabel.h"
@interface AMOrderLogCell : AliTableViewCell
@property (retain, nonatomic) IBOutlet AliCustomLabel *logisticsName;//物流公司
@property (retain, nonatomic) IBOutlet AliCustomLabel *logisticsNo;//运单号
@property (retain, nonatomic) IBOutlet AliCustomLabel *toContact;//收件人
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end

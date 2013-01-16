//
//  AliTableViewCellPriceDetail.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTableViewCell.h"
#import "AliCustomLabel.h"
#import "AMPriceResult.h"
@interface AliTableViewCellPriceDetail : AliTableViewCell

@property (retain, nonatomic) IBOutlet AliCustomLabel *title;
@property (retain, nonatomic) IBOutlet AliCustomLabel *price;
@property (retain, nonatomic) IBOutlet AliCustomLabel *params;
@property (retain, nonatomic) IBOutlet AliCustomLabel *upDown;
@property (retain, nonatomic) IBOutlet AliCustomLabel *date;


+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
-(void)cellSetData:(AMPriceItem *)data;
@end

//
//  AliTableViewCellOfferDetail.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTableViewCell.h"
#import "HJManagedImageV.h"
#import "AliCustomLabel.h"
#import "AMActivityListResult.h"

@interface AMActivityListCell : AliTableViewCell {
    IBOutlet AliCustomLabel *productCountLabel;
    IBOutlet UIImageView *nodataImage; // 默认底图
    IBOutlet AliCustomLabel *title; // 活动标题
    IBOutlet AliCustomLabel *validDate; // 有效日期
    IBOutlet AliCustomLabel *productCount; // 参与的商品数量
    IBOutlet AliCustomLabel *experied; // 是否过期
    IBOutlet UIImageView *bgView;
}

@property (nonatomic,retain) IBOutlet HJManagedImageV *icon; // 通过url载入的图片

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
-(void)cellSetData:(AMActivityListCell*)cell withActivity:(AMActivity *)data;

@end

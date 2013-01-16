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
#import "AMOffer.h"
#import "AMFavoriteOffer.h"
@interface AliTableViewCellOfferDetail : AliTableViewCell
@property (retain, nonatomic) IBOutlet UIImageView *nodataImage;
@property (retain, nonatomic) IBOutlet HJManagedImageV *icon;
@property (retain, nonatomic) IBOutlet AliCustomLabel *title;
@property (retain, nonatomic) IBOutlet AliCustomLabel *address;
@property (retain, nonatomic) IBOutlet AliCustomLabel *price;
@property (retain, nonatomic) IBOutlet AliCustomLabel *orderStart;
@property (retain, nonatomic) IBOutlet AliCustomLabel *preTrade;
@property (retain, nonatomic) IBOutlet AliCustomLabel *trade;
@property (retain, nonatomic) IBOutlet AliCustomLabel *sufTrade;
@property (retain, nonatomic) IBOutlet AliCustomLabel *line;


+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
-(void)cellSetData:(AliTableViewCellOfferDetail*)cell amOffer:(AMOffer *)data;
-(void)cellSetData:(AliTableViewCellOfferDetail*)cell favOffer:(AMFavoriteOffer *)data;

@end

//
//  AliTableViewCellCompany.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTableViewCell.h"
#import "HJManagedImageV.h"
#import "AliCustomLabel.h"
#import "AMCompany.h"
#import "AMFavoriteCompany.h"
@interface AliTableViewCellCompanyDetail : AliTableViewCell
@property (retain, nonatomic) IBOutlet HJManagedImageV *icon;
@property (retain, nonatomic) IBOutlet AliCustomLabel *title;
@property (retain, nonatomic) IBOutlet AliCustomLabel *registerTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *registerSubTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *orderTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *orderSubTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *modelTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *modelSubTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *addressTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *addressSubTitle;
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
-(void)cellSetData:(AliTableViewCellCompanyDetail*)cell amCompany:(AMCompany *)data;
-(void)cellSetData:(AliTableViewCellCompanyDetail*)cell amFavCompany:(AMFavoriteCompany *)data;

@end

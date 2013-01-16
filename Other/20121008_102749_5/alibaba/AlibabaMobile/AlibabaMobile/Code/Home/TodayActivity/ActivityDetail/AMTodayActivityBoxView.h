//
//  AMTodayActivityBoxView.h
//  AlibabaMobile
//
//  Created by amon on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"

@interface AMTodayActivityBoxView : UIControl
@property (retain, nonatomic) UIImageView *leaveFactoryImage;
@property (retain, nonatomic) UIImageView *leaveFactoryImageFocusIcon;
@property (retain, nonatomic) UILabel *subject;
@property (retain, nonatomic) UILabel *leaveFactoryPrice;
@property (retain, nonatomic) UILabel *leaveFactoryPricePre;
@property (retain, nonatomic) UILabel *unit;
@property (nonatomic,retain) IBOutlet HJManagedImageV *listImg;
@property (nonatomic, retain) UILabel *loadingTextNotify;
@property (retain, nonatomic) UIImageView * blockBackImg;

@end

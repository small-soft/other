//
//  AMBannerTableViewCell.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMAdvView.h"
#import "AliTableViewCell.h"
@interface AMBannerTableViewCell : AliTableViewCell

@property (retain, nonatomic) IBOutlet AMAdvView *bannerView;
+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end

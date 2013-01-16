//
//  AdViewController.h
//  MobWinSample
//
//  Created by ben.zhaoguo on 11-12-26.
//  Copyright 2011 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "MobWinBannerView.h"
#import "MobWinBannerViewDelegate.h"

@interface AdViewController : UIViewController<MobWinBannerViewDelegate> {
	//
	// 腾讯MobWIN提示：
	// 开发者必须申明
	//
	MobWinBannerView *adBanner;
}

@property (nonatomic, assign) MobWinBannerSizeIdentifier adType;

- (IBAction)backPressed:(id)sender;

@end

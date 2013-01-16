//
//  AliBaseViewController.h
//  AlibabaMobile
//
//  Created by  on 12-2-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>

#import "AMNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliLoadingDataView.h"


@interface AMBaseViewController : UIViewController<AMNavigationBackDelegate>{
	RKReachabilityObserver *_observer;
    AliLoadingDataView * _mLoadingView;
}

@property (nonatomic, retain) RKReachabilityObserver *observer;

@property (nonatomic, retain) AMNavigationBackButton * mBackButton;
@property (nonatomic, retain) AliNavigationTitleLabel * mTitleLabel;
@property (nonatomic, retain) UIBarButtonItem * mRightNavigationItem;
@property (nonatomic,retain) AliLoadingDataView * mLoadingView;

//设置导航栏返回按钮文字
- (void) setBackButtonText:(NSString *)backButtonText;
//设置导航栏标题文字
-(void) setTitle:(NSString *)title;
//设置导航栏右边的控件，可自定义
- (void) setNavigationRightItem:(UIView *)view;
- (void) endLoadingView;
- (void) showLoadingView;


@end

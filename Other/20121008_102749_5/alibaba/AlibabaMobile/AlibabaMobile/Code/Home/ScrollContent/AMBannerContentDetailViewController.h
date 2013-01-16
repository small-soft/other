//
//  AMBannerContentDetailViewController.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "AliWebViewController.h"

@interface AMBannerContentDetailViewController : AliWebViewController

@property (retain, nonatomic) IBOutlet UIWebView *contentWebView;
@property (copy ,nonatomic) NSString *url;
@property (retain, nonatomic) IBOutlet UIButton *lastButton;
@property (retain, nonatomic) IBOutlet UIButton *nextButton;
@property (retain, nonatomic) IBOutlet UIButton *homeButton;
@property (retain, nonatomic) IBOutlet UIView *noDataView;
@property (retain, nonatomic) IBOutlet UIView *loadingView;
@property (retain, nonatomic) IBOutlet UIButton *refreshButton;
@property (copy, nonatomic) NSString *navigationTitle;
@property (nonatomic)BOOL showToolBar;
@property (retain, nonatomic) IBOutlet UIView *toolBarView;
@property (retain,nonatomic) NSString *parentTitle;
@end

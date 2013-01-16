//
//  AMCompanyCreditViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTabContentViewController.h"
#import "AMCompanyTabViewController.h"
#import "AliLoadingDataView.h"
@class AMCompanyDetail;

@class AMCreditResult;

@interface AMCompanyCreditViewController : AliTabContentViewController

@property (nonatomic, retain) AMCompanyDetail * mCompanyDetail;
@property (nonatomic, retain) AMCreditResult * mCreditResult;
@property (nonatomic, retain) UIScrollView * mMainScrollView;
@property (nonatomic, retain) AliLoadingDataView * mLoadingView;

- (void) initContentData;
- (NSMutableArray *) initPersonalInfo;
- (NSMutableArray *) initCreditInfo;
- (NSMutableArray *) initEnterpriseInfo;

@end

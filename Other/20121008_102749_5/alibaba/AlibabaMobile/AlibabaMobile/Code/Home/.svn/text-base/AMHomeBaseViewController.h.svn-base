//
//  AMHomeBaseViewController.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-22.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <RestKit/RestKit.h>
#import "AliNavigationBackButton.h"
#import "AliAdvView.h"
#import "AliChannel.h"
#import "ConstDef.h"
#import "AliToastView.h"
#import "AMMenuView.h"
#import "HJManagedImageV.h"
#import "AMMenuItemView.h"
#import "UIHelp.h"
#import "UserDataUtils.h"
#import "AMIndustySelectHomeView.h"
#import "AMIndustrySelectPickView.h"

#define AMCONST_HOME_DRESS      @"fuzhuangfushi"
#define AMCONST_HOME_MATERIAL   @"yuancailiao"
#define AMCONST_HOME_PRODUCT    @"gongyepin"
#define AMCONST_HOME_FURNITURE  @"jiajubaihuo"
#define AMCONST_HOME_COMMODITY  @"xiaoshangpin"

#define AMCONST_HOME_CATEGORIES @"categories"
#define AMCONST_HOME_SUMMARY    @""
#define AMCONST_HOME_BANNERS    @"bannersios"
#define AMCONST_HOME_EVENT1     @"event1ios"
#define AMCONST_HOME_EVENT2     @"event2ios"
#define AMCONST_HOME_EVENT3     @"event3ios"
#define AMCONST_HOME_PRICE     @"price"


@interface AMHomeBaseViewController : UIViewController<UITableViewDataSource,UITableViewDelegate,UIScrollViewDelegate,AliChannelDelegate,AliAdvViewDelegate,AMMenuViewDelegate,AliNavigationBackDelegate,AMSelectPickViewDelegate,AMIndustrySelectPickViewDelegate> {
    RKReachabilityObserver *_observer;
    UIImageView * _navBgImgeView; //用于子类页面覆盖navBar背景图所用
    NSArray     * _sourceData;
    NSUInteger  menuViewCount;
    AMIndustrySelectPickView *industrySelectPickView;
}

@property (nonatomic,assign)  NSUInteger     menuViewCount;
@property (nonatomic, retain) RKReachabilityObserver *observer;
@property (retain, nonatomic) UITableView * funcListTable;
@property (nonatomic, retain) UIImageView * navBgImgeView;
@property (nonatomic, retain) NSArray    * sourceData;
@property (nonatomic, retain) AMIndustrySelectPickView *industrySelectPickView;

#pragma mark AliChannel Delegate Methods
-(void)AliChannelReloadData;
#pragma mark AliAdv Delegate Methods
-(UIViewController*)superController;
-(NSString*)superControllerName;
-(void)dataReload;
#pragma mark common function
-(NSString*)commonHomeViewBackButtonTitle;
-(BOOL)showBackButton;
-(void)changePickFrame:(CGFloat)x yframe:(CGFloat)y;
@end

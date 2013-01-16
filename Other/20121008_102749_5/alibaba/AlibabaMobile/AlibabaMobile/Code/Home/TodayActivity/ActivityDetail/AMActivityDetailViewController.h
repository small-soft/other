//
//  AMActivityDetailViewController.h
//  AlibabaMobile
//
//  Created by alimobile on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTabViewController.h"
#import <RestKit/RestKit.h>
#import "AliCommonTableView.h"
#import "AMTopicOfferRequest.h"
#import "AMSpecialPriceOfferRequest.h"

#define AM_ACTIVITY_PRICE_TYPE_ACTIVITY  0//服装服饰的今日活动
#define AM_ACTIVITY_PRICE_TYPE_STOCK  1 //小商品的创业进货
#define AM_ACTIVITY_PRICE_TYPE_PRICE  2//家具百货的特价专场
#define AM_ACTIVITY_PRICE_TYPE_PRICE_SMART  3//小商品的今天特价
#define AM_ACTIVITY_PRICE_TYPE_ACTIVITY_HOME 4 //家具百货的今日活动

@interface AMActivityDetailViewController : AliTabViewController<RKObjectLoaderDelegate>
{
    int _displayModel;//0 表示大图显示，1表示小图显示
    AMTopicOfferRequest * _topicOfferRequest;
    AMSpecialPriceOfferRequest * _specialPriceOfferRequest;
    BOOL isLoading;
    BOOL isOffLine;
    BOOL isAllowSwitch;
    int totalCount;
    int offerPosition;
    int businessType;
    NSString *_industryId;
}

@property (readwrite,nonatomic)int displayModel;
@property (nonatomic, retain) IBOutlet UITableView * mTableView;
@property (nonatomic, retain) AMTopicOfferRequest * topicOfferRequest;
@property (nonatomic, retain) AMSpecialPriceOfferRequest * specialPriceOfferRequest;
@property (nonatomic, retain) NSNumber * activityId;
@property (nonatomic, retain) NSString *activityTitle;
@property (nonatomic, retain) NSString *industryId;
@property (readwrite) int totalCount;
@property (readwrite) int currentPageIndex;
@property (readwrite) BOOL isLoading;
@property (readwrite) int offerPosition;
@property (readwrite) int businessType;
@property (retain, nonatomic) UIButton *switchBtn;
@property (retain,nonatomic)  NSTimer *timer;

@end



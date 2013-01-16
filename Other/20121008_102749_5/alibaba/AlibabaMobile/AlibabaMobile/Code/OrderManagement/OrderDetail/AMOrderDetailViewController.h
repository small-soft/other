//
//  AMOrderDetailViewController.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AliBaseViewController.h"
#import "AMOrderDetailRequest.h"
#import "AMOrderDetailResult.h"
#import "AMCompanyTabViewController.h"
#import "AMIMTalkViewController.h"
#import "AMOrderLogisticsViewController.h"

#import "HJObjManager.h"
#import "AliMemberContactView.h"

#define NOTIFICATION_ORDER_TO_COMPANYDETAIL @"NOTIFICATION_ORDER_TO_COMPANYDETAIL"


@interface AMOrderDetailViewController : AliBaseViewController<UIScrollViewDelegate, RKObjectLoaderDelegate,MemberContactDelegate>
{
    BOOL _showAllProducts;
    AMOrderDetailRequest * _request;
    AMOrderDetailResult * _result;
    NSString * _memberId;
    NSString * _orderId;
}

@property (nonatomic) BOOL showAllProducts;
@property (nonatomic) BOOL isSoldOrderInfo;

@property (nonatomic, retain) IBOutlet UIScrollView * mContentView;

@property (nonatomic,retain) AMOrderDetailRequest * request;
@property (nonatomic,retain) AMOrderDetailResult * result;


@property (nonatomic,retain) NSString * memberId;
@property (nonatomic,retain) NSString * orderId;

@property (nonatomic, retain) HJObjManager *objMan;

@property (nonatomic) BOOL isTalkAfterWwLogin;


@property (nonatomic) NSInteger countOfKinds;

//页面几大组成板块
@property (nonatomic,retain) UIView * basicInfoSubiew;
@property (nonatomic,retain) UIView * productsDetailSubview;
@property (nonatomic,retain) UIView * buyerSellerInfoSubview;
@property (nonatomic,retain) UIView * receiverInfoSubview;
@property (nonatomic,retain) UIView * logisticsInfoSubview;

@property (nonatomic,retain) UIView * buyerFeedbackSubview;
@property (nonatomic,retain) UIView * protocalSubview;

@property (nonatomic,retain) UIView * invoiceInfoSubview;

@property (nonatomic,retain) UIView * basicAndProducts;

@property (nonatomic,retain) UIButton * showOrHide;
@property (nonatomic,retain) UIButton * showOrHideBig;




@end

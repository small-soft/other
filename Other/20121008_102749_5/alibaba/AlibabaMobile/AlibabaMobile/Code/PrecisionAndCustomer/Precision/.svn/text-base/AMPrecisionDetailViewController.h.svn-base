//
//  AMPrecisionDetailViewController.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-29.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliSmallRemoteImageGallery.h"
#import "AliTabContentViewController.h"
#import "AliTabViewController.h"
#import "AMOfferTabViewController.h"

#import "AMCustomerInfoRequest.h"
#import "AMCustomerInfoResult.h"
#import "AMPrecisionVisitorDetailRequest.h"
#import "AMPrecisionVisitorDetailResult.h"
#import "ConstDef.h"
#import "AliCommonTableView.h"
#import "AMPrecisionSaveFreeUserResRequest.h"
#import "AMPrecisionTalkPermissionRequest.h"

#define NOTIFICATION_PRECISION_VIEW_SHOW @"showFull"
#define NOTIFICATION_PRECISION_VIEW_HIDE @"hideFull"

@class AMAddress;

@interface AMPrecisionDetailViewController : AliCommonTableView<RKObjectLoaderDelegate, UIAlertViewDelegate> {
    NSString * mCurVisitorId;
    BOOL mSaveFreeUserResWhenLogined;
    
    int _partHeight;

    // 旺旺聊天相关
    BOOL isTalkAfterWwLogin;
}

@property (nonatomic, retain) AMCustomerInfoRequest * request;
@property (nonatomic, retain) AMCustomerInfoResult * objects;

@property (nonatomic, retain) AMPrecisionVisitorDetailRequest * detailRequest;
@property (nonatomic, retain) AMPrecisionVisitorDetailResult * detailObjects;

@property (nonatomic, retain) AMPrecisionSaveFreeUserResRequest * saveFreeUserResRequest;
@property (nonatomic, retain) AMPrecisionTalkPermissionRequest * talkPermissionRequest;

@property (nonatomic, retain) NSString * sellerMemberId;
@property (nonatomic, retain) NSString * siteId;
@property (nonatomic, retain) NSString * visitorId;
@property (nonatomic, retain) NSString * wwId;
@property (nonatomic) BOOL hasTalkPermision;

@property (nonatomic, retain) UIView * precisionView;
@property (nonatomic, retain) UIView * precisionFullView;
@property (nonatomic) int  partHeight;


@property (nonatomic, retain) IBOutlet UIScrollView * mContentScrollView;

@property (nonatomic, retain) IBOutlet UIButton * mButton;

//@property (nonatomic, retain) AliLoadingDataView * mLoadingView;

- (IBAction)actionGotoTalk:(id)sender;

-(UILabel *) getSubjectLabel:(NSString *)subject;

- (id)initWithVisitorId:(NSString *)visitorId ;
- (void)loadObjectsFromRemote;

@end
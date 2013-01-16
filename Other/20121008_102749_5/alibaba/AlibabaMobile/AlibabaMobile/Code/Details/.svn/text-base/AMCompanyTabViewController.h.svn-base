//
//  AMCompanyTabViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliNavigationBackButton.h"
#import "AliTabViewController.h"
#import "AliTabContentViewController.h"
#import "AMFavoriteRequest.h"


@class AMCompanyDetail;
@class AMCompanyCredit;
@class AMCompanyDetailRequest;
@class amcompanyCreditRequest;
@class AMCreditResult;
@class AMCreditResultRequest;

extern const NSString * TAB_VIEW_COMPANY_DETAIL;
extern const NSString * TAB_VIEW_COMPANY_CREDIT;
extern const NSString * TAB_VIEW_MEMBER_ID;

@interface AMCompanyTabViewController : AliTabViewController  <RKObjectLoaderDelegate, UIAlertViewDelegate>
{
    int dataLoadedTime;

    //数据下载相关
    AMCompanyDetail * mCompanyDetail;
    AMCompanyDetailRequest * _companyDetailRequest;
    NSMutableArray    * _objects;

    AMCreditResult * mCreditResult;
    AMCreditResultRequest * _creditResultRequest;
    
    UIImage * btnBackImg ;
    UIImage * btnBackImgPressed;
}

@property (nonatomic, retain) NSString * mMemberId;
@property (nonatomic, retain) NSString * mCompanyName;
@property (nonatomic, retain) AMFavoriteRequest *addFavoriteRequset;
@property (nonatomic, retain) AMFavoriteRequest *delFavoriteRequset;

- (id)initWithMemberId:(NSString *)memberId companyName:(NSString *)companyName preViewName: (NSString *)preViewName;
-(void)loadRequest;
- (void)loadObjectsFromRemote;



@end

//
//  AMCustomerInfoViewController.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-13.
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
#import "ConstDef.h"

#import "AliCommonTableView.h"


@class AMAddress;
//
@interface AMCustomerInfoViewController : AliCommonTableView<RKObjectLoaderDelegate, UIAlertViewDelegate>
{
    AMCustomerInfoRequest * _request;
    AMCustomerInfoResult * _objects;
    
    // 旺旺聊天相关
    BOOL isTalkAfterWwLogin;
}


@property (nonatomic, retain) IBOutlet UIScrollView * mContentScrollView;

@property (nonatomic, retain) AMCustomerInfoRequest * request;
@property (nonatomic, retain) AMCustomerInfoResult * objects;
@property (nonatomic, retain) NSString * buyerId;



@property (nonatomic, retain) IBOutlet UIButton * mButton;

//@property (nonatomic, retain) AliLoadingDataView * mLoadingView;

- (IBAction)actionGotoTalk:(id)sender;




-(UILabel *) getSubjectLabel:(NSString *)subject;

- (id)initWithBuyerId:(NSString *)buyerId ;
- (void)loadObjectsFromRemote;

@end

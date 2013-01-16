//
//  AMGuessListViewController.h
//  AlibabaMobile
//
//  Created by  xiaowen on 12-6-5.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import <QuartzCore/QuartzCore.h>
#import "AliTabContentViewController.h"
#import "AMCompanyTabViewController.h"

#import "AliCommonTableView.h"
#import "AliTableView.h"
@class AMGuessResult;
@class AMGuestRequest;
@class HJObjManager;

//@interface AMGuessListViewController : AliTabContentViewController <UITableViewDelegate, UITableViewDataSource, RKObjectLoaderDelegate>
@interface AMGuessListViewController : AliCommonTableView <AliTableViewDelegate, UITableViewDataSource, RKObjectLoaderDelegate>
{
    AMGuestRequest *_requset;
    NSMutableArray * _objects;
    bool isLoading;
}

@property (nonatomic, retain) IBOutlet UITableView * mTableView;
@property (nonatomic, retain) AMGuessResult * mOfferResult;
@property (nonatomic, retain) AMGuestRequest * request;
@property (nonatomic, retain) NSMutableArray * objects;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) NSString * parentTitle; 

- (void)loadObjectsFromRemote;

@end

//
//  AMCompanyOfferListViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import <QuartzCore/QuartzCore.h>
#import "AliTabContentViewController.h"
#import "AMCompanyTabViewController.h"


@class AMOfferResult;
@class AMCompanyProductRequest;
@class HJObjManager;

@interface AMCompanyOfferListViewController : AliTabContentViewController <UITableViewDelegate, UITableViewDataSource, RKObjectLoaderDelegate>
{
    AMCompanyProductRequest *_requset;
    NSMutableArray * _objects;
    int pageSize;
    int beginPage;
    int totalNum;
    int nowNum;
    bool isLoading;
}

@property (nonatomic, retain) IBOutlet UITableView * mTableView;
@property (nonatomic, retain) NSString * mMemberId;
@property (nonatomic, retain) AMOfferResult * mOfferResult;
@property (nonatomic, retain) AMCompanyProductRequest * request;
@property (nonatomic, retain) NSMutableArray * objects;
@property (nonatomic,retain) HJObjManager *objMan;

- (id) initWithData:(NSMutableDictionary *)data navigationController:(UINavigationController *)navigationController;
- (void)loadObjectsFromRemote;

@end

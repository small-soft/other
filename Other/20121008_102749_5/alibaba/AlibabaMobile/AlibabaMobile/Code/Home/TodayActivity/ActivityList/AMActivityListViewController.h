//
//  AMActivityViewController.h
//  AlibabaMobile
//
//  Created by mardin partytime on 12-8-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#define ACTIVITY_INDUSTRY_ID_OF_CLOTHING @"fuzhuangfushi"
#define ACTIVITY_INDUSTRY_ID_OF_HOME @"jiajubaihuo"

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import <QuartzCore/QuartzCore.h>

#import "AliCommonTableView.h"
#import "AliTableView.h"
#import "AliLoadingDataView.h"

@class AMActivityListRequest;
@class AMActivityListResult;
@class HJObjManager;

@interface AMActivityListViewController : AliCommonTableView <AliTableViewDelegate, UITableViewDataSource, RKObjectLoaderDelegate>
{
    AMActivityListRequest *_requset;
    NSMutableArray * _objects;
    bool isLoading;
    NSString *_industryId;
}

@property (nonatomic, retain) IBOutlet UITableView * mTableView;
@property (nonatomic, retain) AMActivityListResult * mOfferResult;
@property (nonatomic, retain) AMActivityListRequest * request;
@property (nonatomic, retain) NSMutableArray * objects;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) NSString * parentTitle; 
@property (nonatomic, retain) NSString * industryId; 
//@property (nonatomic, retain) AliLoadingDataView * mLoadingView;


- (void)loadObjectsFromRemote;


@end

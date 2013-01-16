//
//  AMSubpageCommonViewController.h
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMGroupTableViewController.h"
#import <RestKit/RestKit.h>
#import "AMHomepageDressRequest.h"
#import "AMSubpageRequest.h"
#import "AliNavigationBackButton.h"
#import "AliLoadingDataView.h"
@interface AMSubpageCommonViewController : AMGroupTableViewController<RKObjectLoaderDelegate,AliNavigationBackDelegate>

@property (nonatomic, retain) AMSubpageRequest * subpageRequest;

@property (nonatomic, retain) NSMutableArray * subpageChildrenData;

@property (nonatomic, retain) AliLoadingDataView * mLoadingView; 
@property (nonatomic, copy) NSString * categoryName;
-(void)loadSubPageChildrenFromRemote;
//-(void) rotateExpandBtn:(BOOL)isExpand withIndexPath:(NSIndexPath*)indexPath;
@end


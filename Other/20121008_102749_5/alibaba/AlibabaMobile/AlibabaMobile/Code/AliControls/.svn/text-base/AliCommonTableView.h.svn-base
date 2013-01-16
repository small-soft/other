//
//  AliCommonTableView.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliNavigationBackButton.h"
#import "AliNavigationButton.h"
#import "AliSegmentedControl.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
#import "AliRightBarButtonItem.h"
//#import "OceanClientViewController.h"
#import "AliLoadingDataView.h"
@interface AliCommonTableView :  UIViewController <UITableViewDataSource,UITableViewDelegate,RKObjectLoaderDelegate,AliNavigationBackDelegate,AliNavigationButtonDelegate,AliSegmentedDelegate,UIAlertViewDelegate,AliRightBarButtonItemDelegate>{
    RKReachabilityObserver *_observer;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;


- (void)loadObjectsFromRemote;
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects;
-(NSString*)commonTableViewBackButtonTitle;
-(NSString*)commonTableViewOptionButtonTitle;
-(NSString*)commonTableViewNavigationTitle;
-(UIView*)commonTableViewNavigationTitleView;
-(NSArray*)commonTableViewSegmentTitle;
-(NSArray*)commonTableViewRightButtonTitles;

- (void) segmentValueChanged:(int)nowIndex;
-(int)loadingStartY;
-(CGFloat)segmentStartY;
@property (nonatomic, retain) RKReachabilityObserver *observer;
@property (readwrite)BOOL isReload;
@property (nonatomic,retain) AliLoadingDataView * mLoadingView;
- (void) commonTableViewOptionButtonClick;
- (void) changeSegmentIndex:(int)nowIndex;
- (void) showNodataMessage;
- (BOOL) showBackButton;
@end



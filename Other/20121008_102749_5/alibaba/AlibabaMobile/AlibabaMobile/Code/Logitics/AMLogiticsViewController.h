//
//  AMLogiticsViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

//#import "AliCommonTableView.h"
#import "AMCommonTableForOceanClientViewController.h"
#import "AliNavigationBackButton.h"
#import "ZBarSDK.h"



@interface AMLogiticsViewController : AMCommonTableForOceanClientViewController <ZBarReaderDelegate>
@property (retain, nonatomic) IBOutlet UITableView *contentTable;
@property (retain, nonatomic) IBOutlet UITableView *historyTable;
@property (retain, nonatomic) IBOutlet UIButton *queryButton;
@property (retain, nonatomic) IBOutlet UIView *expressQueryView;
@property (retain, nonatomic) IBOutlet UIView *myOrderView;
@property (retain, nonatomic) IBOutlet UITableView *myOrderTabel;
@property (retain, nonatomic) IBOutlet UIButton *loginButton;
@property (retain, nonatomic) IBOutlet UIView *noLoginView;
@property (retain, nonatomic) IBOutlet UILabel *errorMessage;

@property (retain, nonatomic) NSString * parentTitle;

@end

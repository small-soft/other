//
//  AMAppCenterViewController.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliNavigationButton.h"
#import <RestKit/RestKit.h>
@interface AMAppCenterViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,RKObjectLoaderDelegate>
@property (retain, nonatomic) IBOutlet UITableView *contentTable;
@property (retain, nonatomic) IBOutlet UIButton *infoButton;
@property (retain, nonatomic) IBOutlet UIButton *infoButtonUp;

@property (retain, nonatomic) IBOutlet UIView *infoView;
@property (retain, nonatomic) IBOutlet UIControl *showInfoView;
@property (retain, nonatomic) IBOutlet UILabel *currentUserLabel;
@property (retain, nonatomic) IBOutlet UIButton *loginButton;
@property (retain, nonatomic) IBOutlet UIButton *registerButton;
@end

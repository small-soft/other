//
//  AMMoreViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import <Foundation/Foundation.h>
#import "AliNavigationButton.h"
#import "AliNavigationBackButton.h"

@interface AMMoreViewController : UIViewController<UITableViewDataSource,UITextFieldDelegate,UITableViewDelegate,RKObjectLoaderDelegate,AliNavigationBackDelegate,AliNavigationButtonDelegate>

@property (retain, nonatomic) IBOutlet UITableView *topTableView;
@property (retain, nonatomic) IBOutlet UITableView *middleTableView;
@property (retain,nonatomic)  IBOutlet UIButton	*logoutButton;
@end

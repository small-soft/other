//
//  IndustrySelectHomeViewController.h
//  AlibabaMobile
//
//  Created by alimobile on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMIndustrySelectPickView.h"

@interface AMIndustrySelectHomeViewController : UIViewController<UITableViewDataSource,UITableViewDelegate,AMIndustrySelectPickViewDelegate>
{
    NSString *industrySelectName;
}

@property (retain, nonatomic) IBOutlet UIView          *headerView;
@property (retain, nonatomic) IBOutlet UITableView     *tableView;
@property (nonatomic, retain) IBOutlet UINavigationBar *myNavigationBar;
@property (nonatomic, retain) IBOutlet UINavigationItem*myNavigationItem;
@property (retain, nonatomic) AMIndustrySelectPickView *industrySelectPickView;
@end

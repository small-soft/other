//
//  MyWaybillViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-30.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MyWaybillView : UIView

@property (nonatomic,retain) IBOutlet UILabel *logiticsLabel;
@property (nonatomic,retain) IBOutlet UITextField *orderNumberEditField;

@property (nonatomic,retain) IBOutlet UITableView *queryHistoryTableView;

-(IBAction)logiticsSelectButtonPressed;
-(IBAction)queryButtonPressed;


@end

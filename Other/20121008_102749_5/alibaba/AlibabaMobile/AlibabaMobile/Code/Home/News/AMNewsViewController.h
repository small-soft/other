//
//  AMNewsViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AliCommonTableView.h"
#import "AliTableView.h"
@interface AMNewsViewController : AliCommonTableView 
@property (retain, nonatomic) IBOutlet AliTableView *hotNewContentTable;
@property (retain, nonatomic) IBOutlet UIView *categoryView;
@property (retain, nonatomic) IBOutlet UITableView *categoryContentTable;
@property (retain, nonatomic) IBOutlet AliTableView *commonNewTable;
@property (retain, nonatomic) NSString *parentTitle;
-(IBAction)clickOutOfCategoryView:(id)sender;
@end

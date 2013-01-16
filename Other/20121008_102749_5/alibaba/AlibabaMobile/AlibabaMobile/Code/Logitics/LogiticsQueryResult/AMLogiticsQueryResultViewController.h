//
//  AMLogiticsQueryResultViewController.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "AliCommonTableView.h"
#import "AMCorporation.h"
#import "AliTableView.h"
@interface AMLogiticsQueryResultViewController : AliCommonTableView
@property (retain, nonatomic) IBOutlet UITableView *contentGroupTable;
@property (retain, nonatomic) IBOutlet AliTableView *contenDetailTable;
@property (retain, nonatomic) IBOutlet UIView * noInfoView;
@property (retain, nonatomic) AMCorporation* company;
@property (retain, nonatomic) NSString* number;
@property (retain, nonatomic) NSString* logisticsID;
@property (retain, nonatomic) NSString* parentTitle;
@end

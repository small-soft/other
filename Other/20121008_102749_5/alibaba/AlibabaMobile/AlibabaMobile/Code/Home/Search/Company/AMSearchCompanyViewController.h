//
//  AMSearchCompanyViewController.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "AliCommonTableView.h"
#import "AMHotArea.h"
#import <CoreLocation/CoreLocation.h>
#import "AliTableView.h"
#import "AliSearchResultView.h"
#import "AliRegionFilter.h"
#import "AliAroundFilter.h"
#import "AliBizTypeFilter.h"
@interface AMSearchCompanyViewController : AliCommonTableView <AliTableViewDelegate,AliTableViewDelegate,AliRegionFilterDelegate,AliAroundFilterDelegate,AliBizTypeFilterDelegate>
@property (retain, nonatomic) IBOutlet AliSearchResultView *resultView;
@property (retain, nonatomic) IBOutlet AliTableView *contentTable;

@property (nonatomic, retain) NSString *keyWords;
@property (retain, nonatomic) NSString *parentTitle;
@property (retain,nonatomic)NSString *categoryId;


@end

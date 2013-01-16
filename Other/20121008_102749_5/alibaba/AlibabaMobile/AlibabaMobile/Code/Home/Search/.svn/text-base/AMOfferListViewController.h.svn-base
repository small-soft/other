//
//  AMOfferListViewController.h
//  AlibabaMobile
//
//  Created by  on 11-12-21.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliCommonTableView.h"
#import "AliTableView.h"
#import "AMHotArea.h"
#import "AliSearchResultView.h"
#import <CoreLocation/CoreLocation.h>
#import "AliCategoryFilter.h"
#import "AliRegionFilter.h"
#import "AliAroundFilter.h"

@interface AMOfferListViewController : AliCommonTableView <AliTableViewDelegate,AliCategoryFilterDelegate,AliRegionFilterDelegate,AliAroundFilterDelegate>

@property (retain, nonatomic) IBOutlet AliSearchResultView *resultView;
@property (retain, nonatomic) IBOutlet AliTableView *contentTable;

@property (nonatomic)NSUInteger categoryFilterSelectedItem;
@property (nonatomic, copy) NSString *keyWords;
@property (nonatomic, copy) NSString *catId;
@property (nonatomic, copy) NSString *parentCatId;
@property (nonatomic, copy) NSString *catName;
@property (nonatomic, copy) NSString *parentTitle;
@property (nonatomic, copy) NSString *navigationCategoryId;
@end

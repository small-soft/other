//
//  AliCategoryFilter.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTableView.h"
#import "AliCommonTableView.h"
@class AliCategoryFilter;
@protocol AliCategoryFilterDelegate
-(void)AliCategoryFilter:(NSString*)catId catName:(NSString *)catName selectedItem:(NSUInteger)selectedItem;
@end

@interface AliCategoryFilter : AliCommonTableView
@property (retain, nonatomic) IBOutlet AliTableView *contentTable;
@property (retain, nonatomic) NSString *parentTitle;
@property (retain,nonatomic)NSString *keyWords;
@property (nonatomic,retain)NSString *catId;
@property (nonatomic,retain)NSString *catName;
@property (nonatomic)NSUInteger selectedItem;
@property (nonatomic,retain) NSObject<AliCategoryFilterDelegate>*delegate;
@end

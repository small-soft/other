//
//  AliBizTypeFilter.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliCommonTableView.h"
#import "AliTableView.h"
@class AliBizTypeFilter;
@protocol AliBizTypeFilterDelegate
-(void)AliBizTypeFilter:(NSString*)type selectedItem:(NSUInteger)selectedItem;
@end
@interface AliBizTypeFilter : AliCommonTableView
@property (retain, nonatomic) IBOutlet AliTableView *contentTable;
@property (nonatomic)NSUInteger selectedItem;
@property (retain, nonatomic) NSString *parentTitle;
@property (nonatomic,retain) NSObject<AliBizTypeFilterDelegate>*delegate;
@end

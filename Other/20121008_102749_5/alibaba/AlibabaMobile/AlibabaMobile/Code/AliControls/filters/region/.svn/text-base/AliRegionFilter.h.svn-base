//
//  AliRegionFilter.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliCommonTableView.h"
#import "AliTableView.h"
#import "AMHotArea.h"
@class AliRegionFilter;
@protocol AliRegionFilterDelegate
-(void)AliRegionFilter:(AMHotArea*)area segment:(int)segmentSelected selectedItem:(NSUInteger)selectedItem;
@end

@interface AliRegionFilter : AliCommonTableView
@property (retain, nonatomic) IBOutlet AliTableView *contentTable;

@property (retain, nonatomic) NSString *parentTitle;
@property (nonatomic,retain)NSObject<AliRegionFilterDelegate>*delegate;
@property (nonatomic)int lastSegmentSelected;
@property (nonatomic)NSUInteger selectedItem;
@end

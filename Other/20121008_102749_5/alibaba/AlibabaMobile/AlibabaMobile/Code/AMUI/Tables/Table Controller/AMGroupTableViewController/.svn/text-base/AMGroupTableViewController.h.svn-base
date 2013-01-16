//
//  AMGroupTableViewController.h
//  NAMenu
//
//  Created by  on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJObjManager.h"

@class AMGroupCell,AMMenuItemView;
@interface AMGroupTableViewController : UIViewController{
    //用于多个下拉同时存在
    NSMutableDictionary *_expandedIndexes;
    //用于单个下拉
    NSIndexPath * _expandedIndexPath;
    int _mainItemsCount;
    IBOutlet UITableView * _tableView;
    BOOL _isSupportMultiExpanded;
    
    //用于计算变化的高度
//    int _subItemColumnCount;
//    CGSize _subItemSize;
//    NSInteger _menuViewTopPadding;
//    NSInteger _menuViewBottomPadding;
//    NSInteger _menuViewYpadding;
}
@property (nonatomic,retain) HJObjManager *objMan;
@property (nonatomic,retain) UITableView * tableView;
@property (nonatomic,retain) NSIndexPath * expandedIndexPath;
#pragma mark - To be implemented in subclasses

- (NSInteger) mainTable:(UITableView *)mainTable numberOfItemsInSection:(NSInteger)section;
- (NSInteger) mainTable:(UITableView *)mainTable numberOfSubItemsforItemAtIndexPath:(NSIndexPath *)indexPath;
- (void) mainTable:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (AMGroupCell *) mainTable:(UITableView *)mainTable itemForRowAtIndexPath:(NSIndexPath *)indexPath;
- (AMMenuItemView *) inGroupCellIndexPath:(NSIndexPath*)groupCellIndexPath subItemForRowAtIndex:(NSInteger)index;

-(AMGroupCell*) mainTable:(UITableView*)mainTable setItem:(AMGroupCell*)cell forRowAtIndexPath:(NSIndexPath*)indexPath;
#pragma mark - Internal

- (CGFloat) tableView:(UITableView *)tableView heightForGroupCellBackGroundViewAtIndexPath:(NSIndexPath *)indexPath;
- (void) collapsableButtonTapped: (UIControl *)button withEvent: (UIEvent *)event;
- (void) groupCellIndexPath:(NSIndexPath*)groupCellIndexPath didSelectSubItem:(AMMenuItemView *)subItem withIndex: (NSInteger)index;
@end

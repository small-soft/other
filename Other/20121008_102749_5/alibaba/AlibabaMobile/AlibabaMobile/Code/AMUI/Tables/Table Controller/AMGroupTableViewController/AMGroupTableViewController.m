//
//  AMGroupTableViewController.m
//  NAMenu
//
//  Created by  on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMGroupTableViewController.h"
#import "AMGroupCell.h"
#import "ConstDef.h"

@interface AMGroupTableViewController (){

}
@end

@implementation AMGroupTableViewController
@synthesize objMan= _objMan;
@synthesize tableView = _tableView;
@synthesize expandedIndexPath = _expandedIndexPath;
- (id) init
{
    if (self = [self initWithNibName:@"AMGroupTableView" bundle:nil])
    {
    }
    return self;
}

- (id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]))
    {
        _isSupportMultiExpanded = NO;
//        _subItemSize = CGSizeMake(80, 80);
//        _subItemColumnCount = 4;
//        _menuViewTopPadding = 0;
//        _menuViewBottomPadding = 0;
//        _menuViewYpadding = -1;
    }
    
    return self;
}

-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:10 memCacheSize:20];
        
        NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
        HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
        _objMan.fileCache = fileCache;
        // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
        fileCache.fileCountLimit = 100;
        fileCache.fileAgeLimit = 60*60*24*7; //1 week
        [fileCache trimCacheUsingBackgroundThread];
        
    }
    return _objMan;
    
}

#pragma mark - 主table的事件 请实现
- (NSInteger) mainTable:(UITableView *)mainTable numberOfItemsInSection:(NSInteger)section{
    return 0;
}

- (AMGroupCell *) mainTable:(UITableView *)mainTable itemForRowAtIndexPath:(NSIndexPath *)indexPath{
    return nil;
}
-(AMGroupCell*) mainTable:(UITableView*)mainTable setItem:(AMGroupCell*)cell forRowAtIndexPath:(NSIndexPath*)indexPath{
    return cell;
}

- (void) mainTable:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
}

//GroupCell的BackGroundView的宽度。
- (CGFloat) tableView:(UITableView *)tableView heightForGroupCellBackGroundViewAtIndexPath:(NSIndexPath *)indexPath{
    return 50.0;
}

#pragma mark - 下拉的menuView的方法 请实现

- (NSInteger) mainTable:(UITableView *)mainTable numberOfSubItemsforItemAtIndexPath:(NSIndexPath *)indexPath{
    return 0;
}

- (void) groupCellIndexPath:(NSIndexPath*)groupCellIndexPath didSelectSubItem:(AMMenuItemView *)subItem withIndex:(NSInteger)index
{
    
}

- (AMMenuItemView *) inGroupCellIndexPath:(NSIndexPath*)groupCellIndexPath subItemForRowAtIndex:(NSInteger)index{
    return nil;
}

- (void) collapsableButtonTapped: (UIControl *) button withEvent: (UIEvent *) event
{
    UITableView *tableView = self.tableView;
    NSIndexPath * indexPath = [tableView indexPathForRowAtPoint: [[[event touchesForView: button] anyObject] locationInView: tableView]];
    if ( indexPath == nil )
        return;
    
    // reset cell expanded state in array
//	BOOL isExpanded = ![[_expandedIndexes objectForKey:indexPath] boolValue];
//	NSNumber *expandedIndex = [NSNumber numberWithBool:isExpanded];
//	[_expandedIndexes setObject:expandedIndex forKey:indexPath];
//    
//    [self.tableView beginUpdates];
//    [self.tableView endUpdates];
}

#pragma mark - Table view data source

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    _mainItemsCount = [self mainTable:tableView numberOfItemsInSection:section];

    return _mainItemsCount;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AMGroupCell *cell = [tableView dequeueReusableCellWithIdentifier:@"GroupCell"];
    
    if (!cell) {
        cell = [self mainTable:tableView itemForRowAtIndexPath:indexPath] ;
        cell.parentTableController = self;
    }
    cell = [self mainTable:tableView setItem:cell forRowAtIndexPath:indexPath];
    
    
    NSNumber *count = [NSNumber numberWithInt:[self mainTable:tableView numberOfSubItemsforItemAtIndexPath:indexPath]];
    
    cell.subItemsCount = [count intValue];
    
//    BOOL isExpanded = [[_expandedIndexes objectForKey:indexPath] boolValue];
//    cell.isExpanded = isExpanded;
    
//    _subItemColumnCount = cell.menuView.columnCount;
//    _subItemSize = cell.menuView.itemSize;
//    _menuViewTopPadding = cell.menuView.topPadding;
//    _menuViewBottomPadding = cell.menuView.bottomPadding;
    if (!_isSupportMultiExpanded) {
        if ([self.expandedIndexPath isEqual:indexPath]) {
            self.objMan.loadingHandlers = [HJCircularBuffer bufferWithCapacity: cell.subItemsCount + 10];
//            if (!cell.isLoaded) {
                [cell.menuView reloadDataWithGroupCellIndexPath:indexPath];
//            }
            
            cell.bottomLine.hidden = YES;
            [cell rotateExpandBtn:YES];
//            cell.isLoaded = YES;
        }else {
//            if (cell.isLoaded&&self.expandedIndexPath) {
//                cell.isLoaded = NO;
//            }
            cell.bottomLine.hidden = NO;
            [cell rotateExpandBtn:NO];

        }
    }else {
        BOOL isExpanded = [[_expandedIndexes objectForKey:indexPath] boolValue];
        if (isExpanded) {
            self.objMan.loadingHandlers = [HJCircularBuffer bufferWithCapacity: cell.subItemsCount + 10];
            [cell.menuView reloadDataWithGroupCellIndexPath:indexPath];
            cell.bottomLine.hidden = YES;
            [cell rotateExpandBtn:YES];
        }else {
            cell.bottomLine.hidden = NO;
            [cell rotateExpandBtn:NO];
        }
    }
    return cell;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self mainTable:tableView didSelectRowAtIndexPath:indexPath];
}

- (CGFloat) tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AMGroupCell *cell;
    //使用retain以保证不会在autorelease时挂掉但是这么搞有可能有内存泄露
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
    {
        cell = [(AMGroupCell*)[self tableView:tableView cellForRowHeightAtIndexPath:indexPath] retain];

    }else {
        cell = (AMGroupCell*)[self tableView:tableView cellForRowHeightAtIndexPath:indexPath];
    }
    //    int count = [[NSNumber numberWithInt:[self mainTable:tableView numberOfSubItemsforItemAtIndexPath:indexPath]] intValue];
    CGFloat indexPathHeight = 0.0;
    if (_isSupportMultiExpanded) {
        BOOL isExpanded = [[_expandedIndexes objectForKey:indexPath] boolValue];
        if(isExpanded)
        {
//            CGFloat padding = roundf((320 - (_subItemSize.width * _subItemColumnCount)) / (_subItemColumnCount + 1));
//            NSUInteger numRows = count % _subItemColumnCount == 0 ? (count / _subItemColumnCount) : (count / _subItemColumnCount) + 1;
//            CGFloat yPadding = padding;
//            if (_menuViewYpadding>=-1) {
//                yPadding = _menuViewYpadding;
//            }
//            CGFloat totalHeight = ((_subItemSize.height + yPadding) * numRows) + yPadding;
//            return [self tableView:tableView heightForGroupCellBackGroundViewAtIndexPath:indexPath] + totalHeight + _menuViewTopPadding + _menuViewBottomPadding;
            indexPathHeight = [self tableView:tableView heightForGroupCellBackGroundViewAtIndexPath:indexPath] + cell.menuView.contentSize.height;
            return indexPathHeight;
        }
        indexPathHeight = [self tableView:tableView heightForGroupCellBackGroundViewAtIndexPath:indexPath]; 
        return indexPathHeight;
    }else {
        
        if ([indexPath isEqual:self.expandedIndexPath]) {
//            CGFloat padding = roundf((320 - (_subItemSize.width * _subItemColumnCount)) / (_subItemColumnCount + 1));
//            NSUInteger numRows = count % _subItemColumnCount == 0 ? (count / _subItemColumnCount) : (count / _subItemColumnCount) + 1;
//            CGFloat yPadding = padding;
//            if (_menuViewYpadding>=-1) {
//                yPadding = _menuViewYpadding;
//            }
//            CGFloat totalHeight = ((_subItemSize.height + yPadding) * numRows) + yPadding;
//            return [self tableView:tableView heightForGroupCellBackGroundViewAtIndexPath:indexPath] + totalHeight + _menuViewTopPadding + _menuViewBottomPadding;
            indexPathHeight = [self tableView:tableView heightForGroupCellBackGroundViewAtIndexPath:indexPath] + cell.menuView.contentSize.height;
//            [cell release];
            return indexPathHeight;
        }
        indexPathHeight = [self tableView:tableView heightForGroupCellBackGroundViewAtIndexPath:indexPath];
//        [cell release];
        return indexPathHeight;
    }
    
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowHeightAtIndexPath:(NSIndexPath *)indexPath
{
    AMGroupCell *cell = [self mainTable:tableView itemForRowAtIndexPath:indexPath] ;
    
    NSNumber *count = [NSNumber numberWithInt:[self mainTable:tableView numberOfSubItemsforItemAtIndexPath:indexPath]];
    
    cell.subItemsCount = [count intValue];
    return cell;

}
- (void)dealloc
{
    AM_RELEASE_SAFELY(_expandedIndexes);
    AM_RELEASE_SAFELY(_objMan);
    AM_RELEASE_SAFELY(_tableView);
    AM_RELEASE_SAFELY(_expandedIndexPath);
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	_expandedIndexes = [[NSMutableDictionary alloc] init];
    
}
- (void)viewDidUnload{
    [super viewDidUnload];
    AM_RELEASE_SAFELY(_expandedIndexes);
    _tableView =nil;

    
}
@end

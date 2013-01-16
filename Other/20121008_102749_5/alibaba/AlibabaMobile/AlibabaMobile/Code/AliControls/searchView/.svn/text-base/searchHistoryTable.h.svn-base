//
//  searchHistoryTable.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class searchHistoryTable;
@protocol SearchHistoryTableDelegate <NSObject>

- (void)searchHistoryTable:(searchHistoryTable *)tableView didSelectRow:(NSString *)content;
@optional
- (void)searchHistoryTable:(searchHistoryTable *)tableView rowEdit:(NSString *)content;
@end

@interface searchHistoryTable : UIView<UITableViewDataSource>

@property (retain, nonatomic) IBOutlet UITableView *contentTable;
+(id)createView;
#warning mengxixi
@property (nonatomic,assign) id <SearchHistoryTableDelegate> delegate;
-(void)handleSearchForTerm:(NSString *)searchTerm;
-(void)reloadResultData;
@end

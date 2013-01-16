//
//  searchHistoryTable.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "searchHistoryTable.h"
#import "AMSearchResultData.h"
#import "AliTableViewCellSearchHistory.h"

@interface searchHistoryTable() 

@property (nonatomic,retain) AMSearchResultData*searchResultData;
@property (nonatomic,retain) NSMutableArray *searchResultCopy;
@property (nonatomic,retain) NSMutableArray *searchResultSource;
@end
@implementation searchHistoryTable
@synthesize contentTable = _contentTable;
@synthesize searchResultData=_searchResultData;
@synthesize searchResultCopy=_searchResultCopy;
@synthesize delegate=_delegate;
@synthesize searchResultSource = _searchResultSource;
-(void)dealloc
{
    [_searchResultData release];
    [_searchResultCopy release];
    [_contentTable release];
    //[_delegate release];
    [_searchResultSource release];
    [super dealloc];
}

-(NSMutableArray*)searchResultCopy
{
    if (_searchResultCopy==nil) {
        _searchResultCopy = [[NSMutableArray alloc] init];
    }
    return _searchResultCopy;
}
-(NSMutableArray*)searchResultSource
{
    if (_searchResultSource==nil) {
        _searchResultSource = [[NSMutableArray alloc] init];
    }
    return _searchResultSource;
}
-(AMSearchResultData*)searchResultData
{
    if (_searchResultData==nil) {
        _searchResultData = [[AMSearchResultData alloc]init];
    }
    return _searchResultData;
}
-(void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    self.contentTable.frame =CGRectMake(0.0, 0.0, frame.size.width, frame.size.height);
}
+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"searchHistoryTable" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[searchHistoryTable class]])
        {
            searchHistoryTable *obj = (searchHistoryTable *)oneObject;
            [obj reloadResultData];
            return  obj;
        }
    }
    return nil;
}
-(void)resetSearch
{
    [self.searchResultCopy removeAllObjects];
    [self.searchResultCopy addObjectsFromArray:self.searchResultSource];
}
-(void)reloadResultData
{
    [self.searchResultSource removeAllObjects];
    [self.searchResultSource addObjectsFromArray:self.searchResultData.resultData];
}
-(void)handleSearchForTerm:(NSString *)searchTerm
{      
    
    if ((searchTerm==nil||searchTerm.length==0)&&[self.searchResultSource count]>0) {
        
         self.hidden = NO;
        [self resetSearch];
        [self.contentTable resignFirstResponder];
        [self.contentTable reloadData];

    }
    if (searchTerm&&searchTerm.length>0) {
        [self resetSearch];
        NSMutableArray *remove =[[NSMutableArray alloc]init];
        for (NSString *result in self.searchResultCopy)
        {
            if ([result rangeOfString:searchTerm options:NSCaseInsensitiveSearch].location==NSNotFound)
            {
                [remove addObject:result];
            }
        }
        [self.searchResultCopy removeObjectsInArray:remove];
        [remove release];
        [self.contentTable reloadData];
 
    }
       
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.searchResultCopy count];
}
-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    [self.contentTable resignFirstResponder];
    return indexPath;
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellSearchHistory cellHeight];;
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AliTableViewCellSearchHistory *cell = (AliTableViewCellSearchHistory *)[tableView 
                                                            dequeueReusableCellWithIdentifier: [AliTableViewCellSearchHistory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellSearchHistory createCell];
        [cell.editButton addTarget:self action:@selector(cellEditButtonTapped:) forControlEvents:UIControlEventTouchUpInside];    
    }
    NSUInteger row = [indexPath row];
    cell.title.text = [self.searchResultCopy objectAtIndex: [self.searchResultCopy count]-row-1];
//    cell.title.
    //cell.editButton.tag = row;
    cell.editButton.tag = [self.searchResultCopy count]-row-1;
    
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    int size = self.searchResultCopy.count;
     NSUInteger row = [indexPath row];
    NSString *text = [self.searchResultCopy objectAtIndex:size - 1 -row];
    
    if ([self.delegate respondsToSelector:@selector(searchHistoryTable:didSelectRow:)]) {
        [self.delegate searchHistoryTable:self didSelectRow:text];
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

-(IBAction)cellEditButtonTapped:(UIButton*)sender
{
    if ([self.delegate respondsToSelector:@selector(searchHistoryTable:rowEdit:)]) {
        [self.delegate searchHistoryTable:self rowEdit: [self.searchResultCopy objectAtIndex:sender.tag]];
    }
}

@end

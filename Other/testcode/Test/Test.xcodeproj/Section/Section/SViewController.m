//
//  SViewController.m
//  Section
//
//  Created by 佳 刘 on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SViewController.h"
#import "NSString+StringUtils.h"

@interface SViewController ()

@end

@implementation SViewController
@synthesize keys = _keys;
@synthesize names = _names;
@synthesize searchResult = _searchResult;
@synthesize table = _table;
@synthesize search = _search;

#pragma - mark
#pragma mark vc lifecycle
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSString *path = [[NSBundle mainBundle] pathForResource:@"sortednames" ofType:@"plist"];
    
    NSDictionary *dict = [[[NSDictionary alloc] initWithContentsOfFile:path]autorelease];
    self.names = dict;
    self.keys = [[dict allKeys]sortedArrayUsingSelector:@selector(compare:)]; 
}

- (void)viewDidUnload
{
    names = nil;
    keys = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

#pragma - mark
#pragma mark table view delegate
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"section"];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"section"]autorelease];
    }
    
//    NSLog(@"======keys type:%@",self.keys);
//    NSLog(@"======names type:%@",self.names);
    
    if (self.searchResult == nil) {
        cell.textLabel.text = [[self.names objectForKey:[self.keys objectAtIndex:indexPath.section]] objectAtIndex:indexPath.row];
    }else {
        cell.textLabel.text = [self.searchResult objectAtIndex:indexPath.row];
    }
    
    
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.searchResult == nil ?[[self.names objectForKey:[self.keys objectAtIndex:section]] count]:[self.searchResult count];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.searchResult == nil ?[self.keys count]:1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
//    NSLog(@"======%@",[keys class]);
    return self.searchResult == nil ?[self.keys objectAtIndex:section]:@"查询结果";
}

-(NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView {
    return self.searchResult == nil ? self.keys:nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self.search resignFirstResponder];
    [tableView reloadData];
}

#pragma - mark
#pragma mark search bar delegate
-(void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    [self searchForKeyword:searchText];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar {
    [self cancelSearch];
    [searchBar resignFirstResponder];
}

-(void)searchBarSearchButtonClicked:(UISearchBar *)searchBar {
    NSString *searchText = [searchBar text];
    [self searchForKeyword:searchText];
    [self.search resignFirstResponder];
}

#pragma - mark
#pragma mark private methods
-(void) cancelSearch {
    self.searchResult = nil;
    
    [self.table performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:YES];
}

-(void) searchForKeyword:(NSString *)searchText {
    if (searchText.length == 0) {
        [self cancelSearch];
        
        return;
    }
    
    NSString *startChar = [searchText substringToIndex:1];
    NSArray *namesOfSameKey = [self.names objectForKey:[startChar uppercaseString]];
    
    if (self.searchResult) {
        [self.searchResult removeAllObjects];
    } else {
        self.searchResult = [NSMutableArray arrayWithCapacity:100];
    }
    
    for (NSString *str in namesOfSameKey) {
        if (str.length < searchText.length) {
            continue;
        }
        
        NSString *subStr = [str substringToIndex:(searchText.length)];
        
        if ([subStr compareIgnoreCase:searchText]) {
            [self.searchResult addObject:str];
        }
    }
    
    [self.table performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:YES];
}
@end

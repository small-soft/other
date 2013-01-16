//
//  AliBizTypeFilter.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliBizTypeFilter.h"
#import "AliTableViewCellCategory.h"
@interface AliBizTypeFilter ()
@property (nonatomic, retain) NSArray* searchBizModel;
@end

@implementation AliBizTypeFilter

@synthesize contentTable = _contentTable;
@synthesize selectedItem=_selectedItem;
@synthesize delegate=_delegate;
@synthesize searchBizModel = _searchBizModel;
@synthesize parentTitle=_parentTitle;
-(void)dealloc
{
    [_delegate release];
    [_contentTable release];
    [_searchBizModel release];
    [_parentTitle release];
    [super dealloc];
}

-(NSArray*)searchBizModel
{
    if (!_searchBizModel) {
        _searchBizModel = [[NSArray alloc] initWithObjects:@"所有模式",@"生产加工", @"经销批发",
                           @"招商代理", @"商业服务",  nil];
    }
    return _searchBizModel;
}

- (void)viewDidUnload {
    [self setContentTable:nil];
    [super viewDidUnload];
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"经营模式";
}
#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellCategory cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    
    return [self.searchBizModel count];
}
- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];
    }  
    NSUInteger row = [indexPath row];
    
    cell.title.text = [self.searchBizModel objectAtIndex:row];
    if (row==self.selectedItem) {
        cell.identifyImage.image = [UIImage imageNamed:@"icon_list_Checkmark"]; 
    }
    else {
        cell.identifyImage.image = nil;
    }

    return cell;
}
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if ([self.delegate respondsToSelector:@selector(AliBizTypeFilter:selectedItem:)]) 
    {
        NSUInteger row = [indexPath row];
        if (row==0) {
            [self.delegate AliBizTypeFilter:nil selectedItem:0];
        }
        else {
            [self.delegate AliBizTypeFilter:[self.searchBizModel objectAtIndex:row] selectedItem:row];
        }
        
    }
    [self.navigationController popViewControllerAnimated:YES];
}

@end

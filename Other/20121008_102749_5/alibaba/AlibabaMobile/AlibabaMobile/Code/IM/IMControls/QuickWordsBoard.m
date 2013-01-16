//
//  QuickWordsBoard.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-5-4.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "QuickWordsBoard.h"
#import "UIHelp.h"
#import "StringUtils.h"
#import "AMIMUserDefault.h"
#import "AMIMDefaultStorageHelper.h"
#import "QuickWordsBoardCell.h"

@interface QuickWordsBoard()
{
}

@property (nonatomic, retain) AMIMUserDefault * user;
@property (nonatomic, retain)  UITableView * tableView;
@property (nonatomic, retain)  UIButton * addBtn;

@end

@implementation QuickWordsBoard

@synthesize tableView = _tableView;
@synthesize addBtn = _addBtn;
@synthesize user = _user;


- (id)init
{
    self = [super init];
    if (self) {
        [self hideQuickWordBoard];
        
        //init tableView
        _tableView = [[UITableView alloc] init];
        _tableView.frame = self.frame;
        _tableView.backgroundColor = [UIColor clearColor];
        _tableView.delegate = self;
        _tableView.dataSource = self;
        
        [self addSubview:_tableView];
        
        //init addbtn
        _addBtn = [[UIButton alloc] init];
        _addBtn.frame = CGRectMake(275, 170, 40, 40);
        _addBtn.backgroundColor = [UIHelp colorWithHexString:@"424242"];
        [_addBtn setImage:[UIImage imageNamed:@"icon_aliww_add"] forState:UIControlStateNormal];
        [_addBtn addTarget:self action:@selector(showAddWordsView) forControlEvents:UIControlEventTouchUpInside];
        
        [self addSubview:_addBtn];
        
        _user = [AMIMDefaultStorageHelper getLastLoginedUser];
        [_tableView reloadData];
    }
    
    return self;
}

- (void)dealloc
{
    [_tableView release];
    [_addBtn release];
    
    [super dealloc];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    return 44;
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    
    return nil;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(_user != nil && _user.quickWords != nil){
        return _user.quickWords.count;
    }
    
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSInteger row = [indexPath row];
    
    QuickWordsBoardCell *cell = (QuickWordsBoardCell *)[tableView 
                                                        dequeueReusableCellWithIdentifier:@"QuickWordsBoardCell"];
    
    if (cell == nil)  
    {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"QuickWordsBoardCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[QuickWordsBoardCell class]])
                cell = (QuickWordsBoardCell *)oneObject;
        
        
        [cell.textLabel setAdjustsFontSizeToFitWidth:NO];
        
        UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
        UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
        bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
        cellBackBtn.image =bkImage;
        
        cell.selectedBackgroundView = cellBackBtn;
        [cellBackBtn release];
    }
    
    if(_user != nil 
       && _user.quickWords != nil
       && _user.quickWords.count > row){
        cell.quickWordsLabel.text = (NSString *)[_user.quickWords objectAtIndex:row];
    }
    
    return cell;
}

- (void) reloadTableData
{
    self.user = [AMIMDefaultStorageHelper  getLastLoginedUser];
    [_tableView reloadData];
}

- (void) showQuickWordBoard
{
    self.frame = CGRectMake(0, 219, 320, 217);
}

- (void) hideQuickWordBoard
{
    self.frame = CGRectMake(0, 436, 320, 217);
}

@end

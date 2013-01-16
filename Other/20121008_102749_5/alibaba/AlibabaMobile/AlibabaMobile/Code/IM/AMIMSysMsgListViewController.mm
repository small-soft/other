//
//  AMIMSysMsgListViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>

#import "AMIMSysMsgListViewController.h"

#import "AMIMCoreDataHelper.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMUserModel.h"
#import "AMIMRecentContactCell.h"
#import "StringUtils.h"
#import "AMIMTalkViewController.h"
#import "AMIMMessageModel.h"
#import "AMIMSysMsgCell.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

@interface AMIMSysMsgListViewController ()
{
    NSFetchedResultsController * _fetchedResultsController;
    UINavigationController * mNavigationController;
}

@property (nonatomic, retain) IBOutlet UITableView * tableView;
@property (nonatomic,retain) HJObjManager *objMan;

@end

@implementation AMIMSysMsgListViewController

@synthesize tableView = _tableView;
@synthesize objMan = _objMan;

- (void) dealloc
{
    [_tableView release];
    [_fetchedResultsController release];
    [mNavigationController release];
    
    [super dealloc];
}

- (id)initWithNavigation:(UINavigationController *)navigation
{
    self = [super init];
    if (self) {
        mNavigationController = navigation;
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _tableView.delegate = self;
    _tableView.dataSource = self;
    
    _fetchedResultsController = [[[AMIMCoreDataHelper getInstance] getSysMsgFetchControllerWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]] retain];
    _fetchedResultsController.delegate = self;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_QUITWANGWANG object:nil];
    
}

- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller
{
    [_tableView reloadData];
    
}

#pragma table
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    return 62;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    
    return nil;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{ 
    if(_fetchedResultsController){
        return [[_fetchedResultsController sections] count];
    }
    return 0;
    
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(_fetchedResultsController != nil){
        return [[[_fetchedResultsController sections] objectAtIndex:section] numberOfObjects];
    }   
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [AMLogUtils appendLog:APP_WANGWANG_SYSMSG_TWO];
    
    //NSInteger row = [indexPath row];
    if(_fetchedResultsController != nil && [[_fetchedResultsController sections] count]>0){
        AMIMUserModel * user = (AMIMUserModel *)[_fetchedResultsController objectAtIndexPath:indexPath];
        
        
        
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithUser:user.uid];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [mNavigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
    
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    //NSInteger row = [indexPath row];
    if(_fetchedResultsController != nil && [[_fetchedResultsController sections] count]>0){
        AMIMMessageModel * msg = (AMIMMessageModel *)[_fetchedResultsController objectAtIndexPath:indexPath];
        //NSString *uid = [AMIMDefaultStorageHelper getLastLoginedUserId];
        
        AMIMSysMsgCell * cell = nil;
        if (cell == nil)  
        {
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMSysMsgCell" 
                                                         owner:self options:nil];
            for (id oneObject in nib)
                if ([oneObject isKindOfClass:[AMIMSysMsgCell class]])
                    cell = (AMIMSysMsgCell *)oneObject;
            
            [cell.titleLabel setAdjustsFontSizeToFitWidth:NO];
            [cell.timeLabel setAdjustsFontSizeToFitWidth:NO];
            [cell.msgLabel setAdjustsFontSizeToFitWidth:NO];
            
            UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
            UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
            bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
            cellBackBtn.image =bkImage;
            
            cell.selectedBackgroundView = cellBackBtn;
            [cellBackBtn release];
        }
        
        if(msg.msgType.intValue == TEXT_MSG_CONTACT){
            cell.titleLabel.text = @"添加请求";
        }
        [cell setMsg:msg.msgContent];
        cell.timeLabel.text = [StringUtils getDateStrLong:msg.msgTime.doubleValue ];

        
        return cell;
    }        
    
    
    return nil;
}

- (void)quitWangWang
{
    if(_fetchedResultsController){
        [_fetchedResultsController release];
        _fetchedResultsController = nil;
        [_tableView reloadData];
    }
    
}

@end

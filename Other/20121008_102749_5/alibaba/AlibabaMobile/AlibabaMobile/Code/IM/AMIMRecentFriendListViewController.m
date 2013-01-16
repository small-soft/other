//
//  AMRecentFriendListViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMRecentFriendListViewController.h"

#import "AMIMCoreDataHelper.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMUserModel.h"
#import "AMIMRecentContactCell.h"
#import "StringUtils.h"
#import "AMIMTalkViewController.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "LoginToken.h"

@interface AMIMRecentFriendListViewController ()
{
    NSFetchedResultsController * _fetchedResultsController;
    UINavigationController * mNavigationController;
}

@property (nonatomic, retain) IBOutlet UITableView * tableView;
@property (nonatomic,retain) HJObjManager *objMan;

@end

@implementation AMIMRecentFriendListViewController

@synthesize tableView = _tableView;
@synthesize objMan = _objMan;

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_tableView release];
    [_fetchedResultsController release];
    [_objMan release];
    [mNavigationController release];
    
    [super dealloc];
}

- (id)initWithNavigation:(UINavigationController *)navigation
{
    self = [super init];
    if (self) {
        mNavigationController = navigation;
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_COUNTMSG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_HAS_READ object:nil];
        
        //监听添加好友
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_QUITWANGWANG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_LOGOUT object:nil];
        
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _tableView.delegate = self;
    _tableView.dataSource = self;
    
    [self objManInit];
    
    if([LoginToken isWangWangLogined]){
        [self loginSucc];
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

-(void) viewDidUnload
{
    [_objMan release];
    _objMan = nil;
    [super viewDidUnload];
}

- (void) loginSucc {
    [self quitWangWang];
    [self performSelectorOnMainThread:@selector(refreshUI) withObject:nil waitUntilDone:NO];
}

- (void)quitWangWang {
    if(_fetchedResultsController){
        [_fetchedResultsController release];
        _fetchedResultsController = nil;
        [_tableView reloadData];
    }
}

- (void)recvNewMsg {
    [self performSelectorOnMainThread:@selector(refreshUI) withObject:nil waitUntilDone:NO];
}

- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    [self performSelectorOnMainThread:@selector(refreshUI) withObject:nil waitUntilDone:NO];
}

- (void) refreshUI {
    if(_fetchedResultsController){
        [_fetchedResultsController release];
    }
    
     _fetchedResultsController = [[[AMIMCoreDataHelper getInstance] getRecentContactFetchControllerWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]] retain];
    [_tableView reloadData];
}

#pragma table
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    //return 84;
    return 80; //need more checking
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    return nil;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView { 
    if(_fetchedResultsController){
        return [[_fetchedResultsController sections] count];
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if(_fetchedResultsController != nil){
        return [[[_fetchedResultsController sections] objectAtIndex:section] numberOfObjects];
    }   
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSInteger row = [indexPath row];
    if(_fetchedResultsController != nil && [[_fetchedResultsController sections] count]>0){
        AMIMUserModel * user = (AMIMUserModel *)[_fetchedResultsController objectAtIndexPath:indexPath];
        //NSString *uid = [AMIMDefaultStorageHelper getLastLoginedUserId];

        AMIMRecentContactCell * cell = nil;
        if (cell == nil) {
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMRecentContactCell" owner:self options:nil];
            for (id oneObject in nib) {
                if ([oneObject isKindOfClass:[AMIMRecentContactCell class]]) {
                    cell = (AMIMRecentContactCell *)oneObject;
                }
            }
                
//            cell.headImg.layer.masksToBounds = YES;
//            cell.headImg.layer.cornerRadius = 5.0;
            cell.headImg.imageView.layer.borderColor = [UIColor whiteColor].CGColor;
            cell.headImg.imageView.layer.borderWidth = 2.0f;
                
            [cell.nameLabel setAdjustsFontSizeToFitWidth:NO];
            [cell.signLabel setAdjustsFontSizeToFitWidth:NO];
            [cell.timeLabel setAdjustsFontSizeToFitWidth:NO];
            
            [cell.bkImgView setBackgroundImage:[UIImage imageNamed:@"bg_aliww_recentlist_p"] forState:UIControlStateHighlighted];
        }
            
        cell.headImg.url = [StringUtils getWwHeadImageWithUid:user.uid];
        [_objMan manage:cell.headImg];
        cell.nameLabel.text = user.nickname;
        cell.signLabel.text = user.signature;
        cell.timeLabel.text = [StringUtils getDateStrLong:user.contactTime.doubleValue];
        cell.bkImgView.tag = row;
        [cell.bkImgView addTarget:self action:@selector(talkAction:) forControlEvents:UIControlEventTouchUpInside];
        
        [cell setNewMsgNum:[[AMIMCoreDataHelper getInstance] getNewMsgNumWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] friendId:user.uid]];
            
        return cell;
    }        
    return nil;
}

- (IBAction)talkAction:(id)sender {
    [AMLogUtils appendLog:APP_WANGWANG_TALKING_ONE];
    
    int row = ((UIButton *)sender).tag;
    if(_fetchedResultsController != nil && [[_fetchedResultsController sections] count]>0){
        AMIMUserModel * user = (AMIMUserModel *)[_fetchedResultsController.fetchedObjects objectAtIndex:row];
        
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithUser:user.uid];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [mNavigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

-(void)objManInit {
    self.objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
}

@end

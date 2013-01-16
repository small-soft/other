
//  AMIMFriendListViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMFriendListViewController.h"
#import "CallBackTool.h"
#import "LoginToken.h"
#import "AMIMFriendListGroupView.h"
#import "AMIMFriendListItemCell.h"
#import "StringUtils.h"
#import "UIHelp.h"
#import "AMIMUser.h"
#import "SignatureDownloadOperation.h"
#import "pinyin.h"
#import "AMIMUserDetailViewController.h"
#import "AMIMHomeViewController.h"
#import "AliToastView.h"
#import "AMIMSearchFriendViewController.h"
#import "AMIMCoreDataHelper.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMTalkViewController.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AMIMUserModel.h"
#import "AMIMGroupModel.h"
#import "AMIMUserDefault.h"
#import "AMIMFriendSearchListItemCell.h"

@interface AMIMFriendListViewController ()
{
    NSArray *groups;
    NSArray * users;

    NSMutableArray * searchResult;
    
    NSThread *downLoadThread;
    
    UINavigationController * mNavigationController;
    
    NSString * mCurSearchText;
}

@property (nonatomic,retain) AliLoadingDataView * mLoadingView;
@property (nonatomic, retain) IBOutlet UITableView * friendListTable;
@property (nonatomic, retain) IBOutlet UITableView * searchResultTable;

@property (nonatomic, retain) IBOutlet UIButton * searchCancelBtn;
@property (nonatomic, retain) IBOutlet UITextField * searchTextField;
@property (nonatomic, retain) IBOutlet UIImageView * searchBgImgView;

@property (nonatomic, retain) IBOutlet UIButton * addNewFriendBtn;

@property (nonatomic,retain) HJObjManager *objMan;

@end

@implementation AMIMFriendListViewController

@synthesize friendListTable = _friendListTable;
@synthesize searchResultTable = _searchResultTable;
@synthesize searchCancelBtn = _searchCancelBtn;
@synthesize searchTextField = _searchTextField;
@synthesize addNewFriendBtn = _addNewFriendBtn;
@synthesize  searchBgImgView = _searchBgImgView;
@synthesize mLoadingView = _mLoadingView;

@synthesize  objMan = _objMan;


- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    [_friendListTable reloadData];
}

-(void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_friendListTable release];
    [_searchResultTable release];
    [_searchCancelBtn release];
    [_searchTextField release];
    [_addNewFriendBtn release];
    [_searchBgImgView release];
//    [_mLoadingView release];
    self.mLoadingView = nil;

    [groups release];
    [users release];
    [downLoadThread release];
    [_objMan release];

    [searchResult release];
    
    [mNavigationController release];
    [mCurSearchText release];
    
    [super dealloc];
}

- (id)initWithNavigation:(UINavigationController *)navigation {
    self = [super init];
    if (self) {
        mNavigationController = navigation;

        [[NSUserDefaults standardUserDefaults] setBool:FALSE forKey:@"ww_contact_data_ready"];
        [[NSUserDefaults standardUserDefaults] synchronize];
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        //[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setDataReady) name:NOTIFICATION_WW_LOGIN_DATAREADY object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(initData) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(getGroupsNotification:) name:NOTIFICATION_GROUPLIST object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(getUsersNotification:) name:NOTIFICATION_CONTACTLIST object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(getUserStateNotification:) name:NOTIFICATION_CONTACTSTATUSLIST object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(getUserChangeStateNotification:) name:NOTIFICATION_CONTACTSTATUSCHANGED object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(getUserSignatureNotification:) name:NOTIFICATION_SIGNATUREDOWNLOADED object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(getUserChangeSignatureNotification:) name:NOTIFICATION_SIGNATURECHANGED object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_QUITWANGWANG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_LOGOUT object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_NETWORKERROR object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_FORCEDISCONNECT object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleAppGoBackground) name:NOITFICATION_APPGOBACKGROUND object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewWWMsg) name:NOTIFICATION_COUNTMSG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewWWMsg) name:NOTIFICATION_MSG_HAS_READ object:nil];
    }
    return self;
}

- (void)viewDidLoad {
    
    [super viewDidLoad];

    [self objManInit];
    
    _searchResultTable.hidden=true;
    
    _searchCancelBtn.hidden=true;
    _addNewFriendBtn.hidden=true;
    _searchCancelBtn.frame = CGRectMake(270, 6, 40, 32);
    _addNewFriendBtn.frame = CGRectMake(270, 6, 40, 32);
    
    UIImage * bkImg = [UIImage imageNamed:@"Aliww_button"];
    bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height/2];
    [_addNewFriendBtn setBackgroundImage:bkImg forState:UIControlStateNormal];
    [_searchCancelBtn setBackgroundImage:bkImg forState:UIControlStateNormal];
    
    UIImage * bkImgPressed = [UIImage imageNamed:@"Aliww_button_press"];
    bkImgPressed = [bkImgPressed stretchableImageWithLeftCapWidth:bkImgPressed.size.width/2 topCapHeight:bkImgPressed.size.height/2];
    [_addNewFriendBtn setBackgroundImage:bkImgPressed forState:UIControlStateHighlighted];
    [_searchCancelBtn setBackgroundImage:bkImgPressed forState:UIControlStateHighlighted];

    [_searchCancelBtn addTarget:self action:@selector(searchModeEnd:) forControlEvents:UIControlEventTouchUpInside];
    
    [_addNewFriendBtn addTarget:self action:@selector(searchNewFriend:) forControlEvents:UIControlEventTouchUpInside];
    
    self.friendListTable.showsVerticalScrollIndicator = NO;
    self.searchResultTable.showsVerticalScrollIndicator = NO;
    self.friendListTable.delegate = self;
    self.friendListTable.dataSource = self;
    
    self.searchResultTable.delegate = self;
    self.searchResultTable.dataSource = self;
    
    if([LoginToken isWangWangLogined]){
        [self initData];
    }
    
//    NSLog(@"frame height of table view : %f", self.friendListTable.frame.size.height);
//    self.friendListTable.frame = CGRectMake(self.friendListTable.frame.origin.x, self.friendListTable.frame.origin.y, self.friendListTable.frame.size.width, 282);
}

-(void) viewDidUnload
{
    [_objMan release];
    _objMan = nil;
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    self.friendListTable = nil;
    self.searchResultTable = nil;
    [super viewDidUnload];
}

- (IBAction)searchNewFriend:(id)sender {
    AMIMSearchFriendViewController * searchNewFriendViewController = [[AMIMSearchFriendViewController alloc] init];
    [mNavigationController pushViewController:searchNewFriendViewController animated:YES];
}

- (void) initData {
    [self performSelectorOnMainThread:@selector(showLoadingView) withObject:nil waitUntilDone:YES];
    [self performSelectorOnMainThread:@selector(initSearchPage) withObject:nil waitUntilDone:YES];
    
    //by tom.lih
 //   [LoginToken setWangWangLogined:YES];
    
    [[AMIMCoreDataHelper getInstance] initFriendStatusWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
    
    if((![AMIMDefaultStorageHelper getLastLoginedUser].groupListUpdated) ||(groups ==nil)){
        // 下载grouplist
        [self performSelectorInBackground:@selector(GetGroupListThread) withObject:nil];
    }
    else{
        // 获取本地grouplist
        [self getGroupsNotification:nil];
    }
}

// 监听获取grouplist的事件
- (void) getGroupsNotification:(NSNotification *)_notification {
    
	if(![LoginToken isWangWangLogined]){
        [self performSelectorOnMainThread:@selector(endLoadingView) withObject:nil waitUntilDone:YES];
        return;
    }
    
    [self performSelectorOnMainThread:@selector(refreshDataAndFriendTable) withObject:nil waitUntilDone:YES];
    // tom.lih
    if((![AMIMDefaultStorageHelper  getLastLoginedUser].friendListUpdated) ||(users==nil)){
        // 下载联系人
        [self performSelectorInBackground:@selector(GetContactListThread) withObject:nil];
    }else{
        // 获取本地联系人
        [self getUsersNotification:nil];
        downLoadThread = nil;
    }
}

// 获取所有联系人的事件
- (void) getUsersNotification:(NSNotification *)_notification {

    if (downLoadThread != nil) {
		[downLoadThread cancel];
		[downLoadThread release];
        downLoadThread = nil;
	}
       
  
    [self performSelectorOnMainThread:@selector(refreshDataAndFriendTable) withObject:nil waitUntilDone:YES];

    // 下载签名
    AMAppDelegate * appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(!appDelegate.isWwReLogined){
        // 如果是断线重新login就不下载了
        [self performSelectorInBackground:@selector(downSignatureThread) withObject:nil];
        
    }
    appDelegate.isWwReLogined = NO;
    [self performSelectorOnMainThread:@selector(endLoadingView) withObject:nil waitUntilDone:YES];

}

// 获取状态事件
- (void) getUserStateNotification:(NSNotification *)_notification {
	if(![LoginToken isWangWangLogined]){
        return;
    }
    
    [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];
}

// 获取状态改变
- (void) getUserChangeStateNotification:(NSNotification *)_notification {
    if(![LoginToken isWangWangLogined]){
        return;
    }
    
    [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];
}

- (void) handleAppGoBackground {
/*    [[InternetDataTool create].operationQueue cancelAllOperations];
    CallBackTool *tool = [CallBackTool create];
    [tool logOff];
    [tool stop];
    [tool reset];
*/
}

- (void) GetGroupListThread {
    int iCount=0;
    while ( (![[NSUserDefaults standardUserDefaults] boolForKey:@"ww_contact_data_ready"]) && (iCount < 1000) ) {
        [NSThread sleepForTimeInterval:0.02];
        iCount++;
    }
    
    [[NSUserDefaults standardUserDefaults] setBool:FALSE forKey:@"ww_contact_data_ready"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [[CallBackTool create] startGetGroupList];
}

- (void) GetContactListThread {
    
    [[CallBackTool create] startGetContactList];
}

// 交给主线程下载和签名
- (void) downSignatureThread {
    AMAppDelegate * appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.isBackground){
        return ;
    }
    //by tom.lih
    @synchronized(users) {
        if(users != nil && users.count >0){
            int size = users.count;
            for(int i=0; i<size; i++){
                AMIMUserModel * user = [users objectAtIndex:i];
                // 下载联系人签名
                SignatureDownloadOperation *sOp = [[SignatureDownloadOperation alloc] initWithUID:user.uid :1];
                [[InternetDataTool create].operationQueue addOperation:sOp];
                [sOp release];
            }
        }
       
    }
    
}

// 获取用户更改签名事件
- (void) getUserChangeSignatureNotification:(NSNotification *)_notification {
    if(![LoginToken isWangWangLogined]){
        return;
    }
    
    NoticationItem *item = [_notification object];
    NSString *uid = (NSString *)[item.data objectForKey:@"user_uid"];
    
    [[AMIMCoreDataHelper getInstance] changeUserSignatureWithUid:uid ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId] signature:[item.data objectForKey:@"newSignature"]];
    [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];
    
}

// 获取用户签名事件
- (void) getUserSignatureNotification:(NSNotification *)_notification {
    if(![LoginToken isWangWangLogined]){
        return;
    }
    
	NoticationItem *item = [_notification object];
    NSString *uid = (NSString *)[item.data objectForKey:@"uid"];
    
    [[AMIMCoreDataHelper getInstance] changeUserSignatureWithUid:uid ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId] signature:[item.data objectForKey:@"signature"]];
    if([uid isEqualToString:[AMIMDefaultStorageHelper getLastLoginedUserId]]){
        [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];
    }
}

- (int) getUser:(NSString *) uid
{
    if(users!=nil && users.count >0 && uid !=nil){
        int size = users.count;
        for(int i=0;i<size;i++){
            AMIMUserModel * user = [users objectAtIndex:i];
            if([user.uid isEqualToString:uid]){
                return i;
            }
        }
    }
    
    return -1;
}

- (void) quitWangWang {
//by tom.lih
    @synchronized(groups){
        [groups release];
        groups = nil;
    }
    
    @synchronized(users){
        [users release];
        users = nil;
    }

#ifdef SINGLE_WW_APP
    [self performSelectorOnMainThread:@selector(clearFriendTable) withObject:nil waitUntilDone:NO];
#else
    [self performSelectorOnMainThread:@selector(clearFriendTable) withObject:nil waitUntilDone:NO];
    //[self performSelectorOnMainThread:@selector(refreshDataAndFriendTable) withObject:nil waitUntilDone:NO];
#endif
   
}

- (void) resetDataContext
{
    [[AMIMCoreDataHelper getInstance] reset];
}

#pragma table

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    if(tableView == _friendListTable){
        return 44;
    }
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    if(tableView == _friendListTable){
        if(groups != nil
           && groups.count > section
           && section >=0){
            AMIMGroupModel * group = [groups objectAtIndex:section];
            
            AMIMFriendListGroupView * titleView = [[AMIMFriendListGroupView alloc] init];
            [titleView setTitle:group.groupName num:[NSString stringWithFormat:@"(%d/%d)", [self getGroupOnlineUserNum:group.groupId ], [self getGroupUserNum:group.groupId ]]];
            titleView.groupBtn.tag = 0;
            
            //NSString * groupId = group.groupId;
            BOOL nowStatus = group.opened.boolValue;
            if(nowStatus){
                titleView.arrowImageView.image = [UIImage imageNamed:@"icon_aliww_list02"];
            }else{
                titleView.arrowImageView.image = [UIImage imageNamed:@"icon_aliww_list01"];
            }
            
            titleView.groupBtn.tag = section;
            [titleView.groupBtn addTarget:self action:@selector(groupBtnClick:) forControlEvents:UIControlEventTouchUpInside];
            
            return  titleView;
        }
    }
    
    
    return nil;
}

- (IBAction)groupBtnClick:(id)sender
{
    int index = ((UIButton *)sender).tag;
    //by tom.lih
    AMIMGroupModel * group=nil;
    @synchronized(groups){
       group = [groups objectAtIndex:index];
    }
 
    NSString * groupId = group.groupId;
    BOOL nowStatus = group.opened.boolValue;
    nowStatus = !nowStatus;
    group.opened = [NSNumber numberWithBool: nowStatus];
    [[AMIMCoreDataHelper getInstance] changeGroupOpenState:nowStatus ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId] groupId:groupId];
    
//    [self.friendListTable reloadData];
    
    [self performSelectorOnMainThread:@selector(refreshDataAndFriendTable) withObject:nil waitUntilDone:NO];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{ 
    if(tableView == _friendListTable){
        if(groups != nil){
            return groups.count;
        }else{
            return 0;
        }
    }else if(tableView == _searchResultTable){
        if(searchResult != nil){
            return 1;
        }
    }
 
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(tableView == _friendListTable){
        if(groups != nil 
           && groups.count > section
           && section >=0
           ){
            AMIMGroupModel * group = [groups objectAtIndex:section];
            //NSString * groupId = group.groupId;
            BOOL nowStatus = group.opened.boolValue;
            
            if(nowStatus){
                return [self getGroupUserNum:group.groupId];
                
            }
        }
    }else{
        if(searchResult != nil){
            return  searchResult.count;
        }
    }
    
    
    return 0;
}

- (int) getGroupUserNum:(NSString *) groupId
{
    int groupUserNum = 0;
    @synchronized(users){
        if(users != nil && users.count > 0){
            int size = users.count;
        
            for(int i=0; i<size; i++){
                AMIMUserModel * user = [users objectAtIndex:i];
                if([user.groupId isEqualToString:groupId]){
                    groupUserNum ++;
                }
            }
        }
    }
    
    return groupUserNum;
}

- (int) getGroupOnlineUserNum:(NSString *) groupId
{
    int groupUserNum = 0;
    @synchronized(users){
        if(users != nil && users.count >0 ){
            int size = users.count;
        
            for(int i=0; i<size; i++){
                AMIMUserModel * user = [users objectAtIndex:i];
                if (user!=nil && user.groupId!=nil && user.status!=nil) {
                    if([user.groupId isEqualToString:groupId] && [self isStatusVisible:(EnDetailStatus)(user.status.intValue)]){
                        groupUserNum ++;
                    }
                } 
            }
        }
    }
    return groupUserNum;
}

- (BOOL) isStatusVisible:(EnDetailStatus)status
{
    if(status == IMPREDEFSTATUS_FREE
       || status == IMPREDEFSTATUS_BUSY
       || status == IMPREDEFSTATUS_AWAY
       || status == IMPREDEFSTATUS_INCALL
       || status == IMPREDEFSTATUS_OUTFORDINNER
       || status == IMPREDEFSTATUS_WAIT
       || status == IMPREDEFSTATUS_OFFLINELOGON
       || status == IMPREDEFSTATUS_FAKEONLINE
       || status == IMPREDEFSTATUS_MOBILEONLINE
       || status == IMPREDEFSTATUS_MOBILE_FREE_1
       || status == IMPREDEFSTATUS_MOBILE_FREE_2
       || status == IMPREDEFSTATUS_MOBILE_BUSY
       || status == IMPREDEFSTATUS_MOBILE_AWAY
       || status == IMPREDEFSTATUS_MOBILE_INCALL
       || status == IMPREDEFSTATUS_MOBILE_OUTFORDINNER
       || status == IMPREDEFSTATUS_MOBILE_WAIT
       || status == IMPREDEFSTATUS_MOBILE_OFFLINELOGON
       || status == IMPREDEFSTATUS_MOBILE_SELFDEF){
        return YES;
    }
    return NO;
   
}

- (AMIMUserModel *) getGroupUser:(NSString *)groupId index:(int) userIndex
{
    @synchronized(users){
        if(users != nil && users.count > userIndex){
            int size = users.count;
            int tempIndex = -1;
            for(int i=0; i<size; i++){
                AMIMUserModel * user = [users objectAtIndex:i];
                if([user.groupId isEqualToString:groupId]){
                    tempIndex ++;
                
                    if(tempIndex == userIndex)
                        return  user;
                }
            }
        }
    }
    
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int section = [indexPath section];
    int row = [indexPath row];
    
    if(tableView == _friendListTable && groups != nil && groups.count > section){
        [AMLogUtils appendLog:APP_WANGWANG_TALKING_ONE];
        
        AMIMGroupModel * group = [groups objectAtIndex:section];
        AMIMUserModel * user = [self getGroupUser:group.groupId index:row];
        if(user != nil){  

            AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithUser:user.uid];
            [talkViewController setHidesBottomBarWhenPushed:YES];
            [mNavigationController pushViewController:talkViewController animated:YES];
        }
        
    }else if(tableView == _searchResultTable && searchResult != nil && searchResult.count >row){
        AMIMUserModel * user = [searchResult objectAtIndex:row];
        if(user != nil){
            AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithUser:user.uid];
            [talkViewController setHidesBottomBarWhenPushed:YES];
            [mNavigationController pushViewController:talkViewController animated:YES];
        }
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int section = [indexPath section];
    int row = [indexPath row];
//    AMIMFriendListItemCell * cell = nil;
//    if (cell == nil)  
//    {
//        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMFriendListItemCell" 
//                                                     owner:self options:nil];
//        for (id oneObject in nib)
//            if ([oneObject isKindOfClass:[AMIMFriendListItemCell class]])
//                cell = (AMIMFriendListItemCell *)oneObject;
//        
////        cell.headImg.layer.masksToBounds = YES;
////        cell.headImg.layer.cornerRadius = 5.0;
//        cell.headImg.imageView.layer.borderColor = [UIColor whiteColor].CGColor;
//        cell.headImg.imageView.layer.borderWidth = 2.0f;
//        
//        [cell.nameLabel setAdjustsFontSizeToFitWidth:NO];
//        [cell.signLabel setAdjustsFontSizeToFitWidth:NO];
//        
//        UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
//        UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
//        bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
//        cellBackBtn.image =bkImage;
//        
//        cell.selectedBackgroundView = cellBackBtn;
//        [cellBackBtn release]; 
//    }

    if(tableView == _friendListTable  && groups != nil && groups.count > section){
        AMIMGroupModel * group = [groups objectAtIndex:section];
        AMIMUserModel * user = [[self getGroupUser:group.groupId index:row] retain];
        if(user != nil){

            AMIMFriendListItemCell * cell = nil;
            if (cell == nil)  
            {
                NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMFriendListItemCell" 
                                                             owner:self options:nil];
                for (id oneObject in nib)
                    if ([oneObject isKindOfClass:[AMIMFriendListItemCell class]])
                        cell = (AMIMFriendListItemCell *)oneObject;
                
                //        cell.headImg.layer.masksToBounds = YES;
                //        cell.headImg.layer.cornerRadius = 5.0;
                cell.headImg.imageView.layer.borderColor = [UIColor whiteColor].CGColor;
                cell.headImg.imageView.layer.borderWidth = 2.0f;
                
                [cell.nameLabel setAdjustsFontSizeToFitWidth:NO];
                [cell.signLabel setAdjustsFontSizeToFitWidth:NO];
                
                UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
                UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
                bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
                cellBackBtn.image =bkImage;
                
                cell.selectedBackgroundView = cellBackBtn;
                [cellBackBtn release]; 
            }
            
            cell.nameLabel.text = user.nickname;
            if(user.signature != nil)
                cell.signLabel.text = user.signature;
            
            cell.headImg.url = [StringUtils getWwHeadImageWithUid:user.uid];
            [_objMan manage:cell.headImg];
            if(![self isStatusVisible:(EnDetailStatus)(user.status.intValue)]){
                [cell setHeadInvisible];
            }else{
                NSString * statusImgPath = [self getStatusImgPath:user.status.intValue];
                cell.statusImg.image = [UIImage imageNamed:statusImgPath];
            }

            cell.detailBtn.param = user.uid;
            [cell.detailBtn addTarget:self action:@selector(userDetailAction:) forControlEvents:UIControlEventTouchUpInside];
            
            
            [cell setNewMsgNum:[[AMIMCoreDataHelper getInstance] getNewMsgNumWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] friendId:user.uid]];
            
            [user release];
            
            return cell;
        }

    }else if(tableView == _searchResultTable && searchResult != nil && searchResult.count >row){
        if(searchResult != nil && row < searchResult.count){
            AMIMUserModel * user = [[searchResult objectAtIndex:row] retain];
            
            if(user != nil){
                
                AMIMFriendSearchListItemCell * cell = nil;
                if (cell == nil)  
                {
                    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMFriendSearchListItemCell" 
                                                                 owner:self options:nil];
                    for (id oneObject in nib)
                        if ([oneObject isKindOfClass:[AMIMFriendSearchListItemCell class]])
                            cell = (AMIMFriendSearchListItemCell *)oneObject;
                    
                    //        cell.headImg.layer.masksToBounds = YES;
                    //        cell.headImg.layer.cornerRadius = 5.0;
                    cell.headImg.imageView.layer.borderColor = [UIColor whiteColor].CGColor;
                    cell.headImg.imageView.layer.borderWidth = 2.0f;
                    
                    [cell.nameLabel setAdjustsFontSizeToFitWidth:NO];
                    [cell.signLabel setAdjustsFontSizeToFitWidth:NO];
                    
                    UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
                    UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
                    bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
                    cellBackBtn.image =bkImage;
                    
                    cell.selectedBackgroundView = cellBackBtn;
                    [cellBackBtn release]; 
                }
                
                                
//                UIView *v = [[UIView alloc] initWithFrame:cell.frame];
//                if(row % 2 ){
//                    v.backgroundColor = [UIHelp colorWithHexString:@"0xe8f5ff"]; 
//                }else{
//                    v.backgroundColor = [UIColor whiteColor];
//                }
//                cell.backgroundView = v;
//                [v release];
                
                cell.nameLabel.text = user.nickname;
                if(user.signature != nil)
                    cell.signLabel.text = user.signature;
                
                cell.headImg.url = [StringUtils getWwHeadImageWithUid:user.uid];
                [_objMan manage:cell.headImg];
                if(![self isStatusVisible:(EnDetailStatus)(user.status.intValue)]){
                    [cell setHeadInvisible];
                }else{
                    NSString * statusImgPath = [self getStatusImgPath:user.status.intValue];
                    cell.statusImg.image = [UIImage imageNamed:statusImgPath];
                }
                cell.detailBtn.param = user.uid;
                [cell.detailBtn addTarget:self action:@selector(userDetailAction:) forControlEvents:UIControlEventTouchUpInside];
                
                [user release];
                return cell;
            }
        }
    }
        
    return nil;
    
}

- (IBAction)userDetailAction:(id)sender
{
    [AMLogUtils appendLog:APP_WANGWANG_LIST_TWO];
    
    NSString * uid = ((AliParamButton *)sender).param;
    
    int index  = [self getUser:uid];
    if(index >=0){
        AMIMUser * user=nil;
        @synchronized(users){
            user = [users objectAtIndex:index];
        }
        
        if(user != nil){
            AMIMUserDetailViewController * userDetailViewController = [[AMIMUserDetailViewController alloc] initWithUser:user.uid relation:USER_RELATION_FRIEND];
            
            [userDetailViewController setHidesBottomBarWhenPushed:YES];
            [mNavigationController pushViewController:userDetailViewController animated:YES];
            
        }
    }
    
}

- (NSString *) getStatusImgPath:(int) status{
    if(status == IMPREDEFSTATUS_BUSY
       || status == IMPREDEFSTATUS_INCALL){
        return @"icon_aliww_busy01";
    }else if(status == IMPREDEFSTATUS_AWAY
              || status == IMPREDEFSTATUS_OUTFORDINNER
             || status == IMPREDEFSTATUS_WAIT){
        return @"icon_aliww_outing01";
    }
       
    return nil;
}



-(void)objManInit
{
    self.objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
}

#pragma search
- (IBAction)searchModeBegin:(id)sender {
    [UIView beginAnimations:@"hide" context:NULL];                                                                                  
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];                                                                                                                                                                                                                                     
    [UIView setAnimationDuration:0.3]; 
    
    _friendListTable.hidden=true;
    _searchResultTable.hidden=false;
    
    _searchCancelBtn.hidden = NO;
    
    _searchTextField.frame  = CGRectMake(20, 10, 240, 25);
    _searchBgImgView.frame = CGRectMake(10, 0, 250, 44);
    
    [UIView commitAnimations];
 
    [mNavigationController setNavigationBarHidden:YES animated:YES];
}

- (void) initSearchPage {
    
    _searchCancelBtn.hidden = YES;
    
    _friendListTable.hidden=false;
    _searchResultTable.hidden=true;
    
    _searchTextField.text = @"";
    [_searchTextField resignFirstResponder];
    
    _searchTextField.frame  = CGRectMake(20, 10, 290, 25);
    _searchBgImgView.frame = CGRectMake(10, 0, 300, 44);
    
    [searchResult release];
    searchResult = nil;
    [self performSelectorOnMainThread:@selector(refreshSearchResultTable) withObject:nil waitUntilDone:NO];

}

- (void) doSearchModeEnd {
    [UIView beginAnimations:@"hide" context:NULL];                                                                                  
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];                                                                                                                                                                                                                                    
    [UIView setAnimationDuration:0.3];                                                                                              
    [self initSearchPage];
    [UIView commitAnimations];
//    [mNavigationController setNavigationBarHidden:NO animated:YES];
}

-(IBAction)searchModeEnd:(id)sender {
    [self doSearchModeEnd];
}

- (IBAction)hideKeyboard:(id)sender
{
    [self doSearchModeEnd];
}

- (IBAction)textEditing {
    mCurSearchText = [NSString stringWithFormat:@"%@", _searchTextField.text];
    //[NSThread detachNewThreadSelector:@selector(localSearchThread) toTarget:self withObject:nil];
    [self doLocalSearch];
}

- (void) doLocalSearch {
    if(searchResult == nil) {
        searchResult = [[NSMutableArray alloc] init ];
    }else{
        [searchResult removeAllObjects];
    }
    
    if (mCurSearchText == nil || mCurSearchText.length <= 0 || users == nil || users.count <= 0) {
        [self refreshSearchResultTable];
        return ;
    }
    
    int size = users.count;
    for(int i=0; i<size; i++){
        AMIMUserModel *user = [users objectAtIndex:i];
        if (user == nil ) {
            continue;
        }
        
        NSString * uid = [user.uid substringFromIndex:8];
        NSString * nickname = user.nickname;
        NSString * uidPy = py_lookup([user.uid substringFromIndex:8]);
        NSString * nicknamePy = py_lookup(user.nickname);
        
        if (uid != nil && uid.length > 0) {
            NSRange range = [uid rangeOfString:mCurSearchText];
            if(range.location != NSNotFound){
                [searchResult addObject:user];
                continue;
            }
        }
        
        if (nickname != nil && nickname.length > 0) {
            NSRange range = [nickname rangeOfString:mCurSearchText];
            if(range.location != NSNotFound){
                [searchResult addObject:user];
                continue;
            }
        }
        
        if (uidPy != nil && uidPy.length > 0) {
            NSRange range = [uidPy rangeOfString:mCurSearchText];
            if(range.location != NSNotFound){
                [searchResult addObject:user];
                continue;
            }
        }
        
        if (nicknamePy != nil && nicknamePy.length > 0) {
            NSRange range = [nicknamePy rangeOfString:mCurSearchText];
            if(range.location != NSNotFound){
                [searchResult addObject:user];
                continue;
            }
        }
    }
    
    [self refreshSearchResultTable];
}

- (void) localSearchThread {
    @synchronized(searchResult){
        NSString * text = mCurSearchText;
        NSLog(@"+++++++++++++++++++++++++search text: %@", text);
        NSLog(@"text.length: %d", text.length);
        if (text == nil || text.length <= 0) {
            return ;
        }
        
        if(searchResult == nil) {
            searchResult = [[NSMutableArray alloc] init ];
        }else{
            [searchResult removeAllObjects];
        }
        
        if(users == nil || users.count <= 0) {
            return ;
        }
        
        int size = users.count;
        BOOL isFound = NO;
        for(int i=0; i<size; i++){
            isFound = NO;
            AMIMUserModel *user = [users objectAtIndex:i];
            if (user == nil ) {
                continue;
            }
            
            NSString * uid = [user.uid substringFromIndex:8];
            NSString * nickname = user.nickname;
            NSString * uidPy = py_lookup([user.uid substringFromIndex:8]);
            NSString * nicknamePy = py_lookup(user.nickname);
            
            //NSLog(@"uid: %@ nickname:%@", uid, nickname);
            if (uid != nil && uid.length > 0) {
                NSRange range = [uid rangeOfString:text];
                if(range.location != NSNotFound){
                    isFound = YES;
                }
            }
            
            if (nickname != nil && nickname.length > 0) {
                NSRange range = [nickname rangeOfString:text];
                if(range.location != NSNotFound){
                    isFound = YES;
                }
            }
            
            if (uidPy != nil && uidPy.length > 0) {
                NSRange range = [uidPy rangeOfString:text];
                if(range.location != NSNotFound){
                    isFound = YES;
                }
            }
            
            if (nicknamePy != nil && nicknamePy.length > 0) {
                NSRange range = [nicknamePy rangeOfString:text];
                if(range.location != NSNotFound){
                    isFound = YES;
                }
            }

            if (isFound) {
                [searchResult addObject:user];
            }
        }
        [self performSelectorOnMainThread:@selector(refreshSearchResultTable) withObject:nil waitUntilDone:NO];
    }
}

- (void)recvNewWWMsg {
    [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];
}

- (void) refreshFriendTable {
    @synchronized(_friendListTable) {
        [_friendListTable reloadData];
    }
}

- (void) clearFriendTable {
    @synchronized(groups) {
        if(groups != nil){
            [groups release];
            groups = nil;
        }
     }
    
    @synchronized(users) {
        if(users != nil) {
            [users release];
            users = nil;
        }
    }
        
    [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];

}

- (void) refreshDataAndFriendTable {
    
    @synchronized(groups) {
        if(groups != nil){
            [groups release];
            groups = nil;
        }
        groups = [[[AMIMCoreDataHelper getInstance] getGroupListWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]] retain];
    }
    
    @synchronized(users) {
        if(users != nil) {
            [users release];
            users = nil;
        }
        users = [[[AMIMCoreDataHelper getInstance] getFriendListWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]] retain];
    }
    
    [self performSelectorOnMainThread:@selector(refreshFriendTable) withObject:nil waitUntilDone:NO];
    
}

- (void) refreshSearchResultTable {
    @synchronized(_searchResultTable) {
         [_searchResultTable reloadData];
    }
}

-(UIView*)mLoadingView {
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib) {
            if ([oneObject isKindOfClass:[AliLoadingDataView class]]) {
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
            }
        }

        [self.view addSubview:self.mLoadingView];
        [_mLoadingView setHidden:NO];
//        [self.mLoadingView showLoadingView];
    }
    return _mLoadingView;
}

- (void) showLoadingView {
//    if(self.view.frame.size.height == 480){
//        self.mLoadingView.frame = CGRectMake(self.mLoadingView.frame.origin.x, self.mLoadingView.frame.origin.y + 44, self.mLoadingView.frame.size.width, self.mLoadingView.frame.size.height);
//    }
    //[self.mLoadingView setHidden:NO];
    [self.mLoadingView showLoadingView];
}

//去除加载进度
-(void) endLoadingView {
    //[self.mLoadingView setHidden:YES];
    [self.mLoadingView endLoadingView];
}


@end
//
//  AMIMSearchFriendViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-15.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMSearchFriendViewController.h"
#import "AMIMSearchNewFriendCell.h"
#import "UIHelp.h"
#import "AliToastView.h"
#import "CallBackTool.h"
#import "StringUtils.h"
#import "HJObjManager.h"
#import "HJManagedImageV.h"
#import "AMIMUserDetailViewController.h"

#import "AMAuthMessageViewController.h"

@interface AMIMSearchFriendViewController ()

@property (nonatomic, retain) NSArray * searchResult;
@property (nonatomic, retain) NSDictionary * searchResultDic;

@property (nonatomic,retain) HJObjManager *objMan;
@property (nonatomic,retain)  NSString *fid;

@property (nonatomic, retain) IBOutlet UITextField * textField;
@property (nonatomic, retain) IBOutlet UIButton * searchBtn;
@property (nonatomic, retain) IBOutlet UITableView * searchTable;

@end

@implementation AMIMSearchFriendViewController

@synthesize  textField = _textField;
@synthesize  searchBtn = _searchBtn;
@synthesize  searchTable = _searchTable;
@synthesize objMan = _objMan;
@synthesize fid = _fid;
@synthesize searchResult = _searchResult;
@synthesize searchResultDic = _searchResultDic;

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_fid release];
    [_textField release];
    [_searchTable release];
    [_searchBtn release];
    [_searchResult release];
    [_searchResultDic release];
    [_objMan release];
    
    [super dealloc];
}

- (id)init
{
    self = [super init];
    if (self) {

        [[NSNotificationCenter defaultCenter] removeObserver:self];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setFriendsArray:) 
                                                     name:NOTIFICATION_SEARCHFRIENDSRESULT object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(addFriendResult:) 
                                                     name:NOTIFICATION_ADDFRIENDRESULT object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(needAuthCode:) 
                                                     name:NOTIFICATION_NEEDAUTHCODE object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(addStrangerToFriend:) name:NOTIFICATION_ADDSTRANGERTOFRIEND object:nil];
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = @"添加好友";
    
    [self objManInit];
    
    _searchTable.delegate = self;
    _searchTable.dataSource = self;
    
    UIImage * bgNormal = [UIImage imageNamed:@"btn_ct_orange"];
    bgNormal = [bgNormal stretchableImageWithLeftCapWidth:bgNormal.size.width/2 topCapHeight:bgNormal.size.height/2 ];
    UIImage * bgTap =  [UIImage imageNamed:@"btn_ct_orange_tap"];
    bgTap = [bgTap stretchableImageWithLeftCapWidth:bgTap.size.width/2 topCapHeight:bgTap.size.height/2 ];
    [_searchBtn setBackgroundImage:bgNormal forState:UIControlStateNormal];
    [_searchBtn setBackgroundImage:bgTap forState:UIControlStateHighlighted];
    [_searchBtn addTarget:self action:@selector(searchAction:) forControlEvents:UIControlEventTouchUpInside];
    
    [_textField becomeFirstResponder];
}

- (void) getfriendInfo {
    
}

- (void) addFriendResult:(NSNotification *) notification {
	NoticationItem *dic = [notification object];
    NSLog(@"add friend result: %@", dic.data);
    if (dic.errorCode == eMSG_TYPE_CONTACT_ADD_OK) {
        
//        [[[[NSThread alloc] initWithTarget:self selector:@selector(getfriendInfo) object:nil] autorelease] start];

//        NSString *uid = (NSString *)[dic.data objectForKey:@"user_uid"];
//        
//        [[CallBackTool create] getSignature: uid :1];
//        [[CallBackTool create] startGetContactStatusList];
        
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"添加好友成功！"] show];
    }else {
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"添加好友失败！"] show];
    }
    
}

- (void) startAuth {
    AMAuthMessageViewController * authViewController = [[AMAuthMessageViewController alloc] initWithFid: _fid];
    [self.navigationController pushViewController:authViewController animated:YES];  
    [authViewController release];
}

- (void) needAuthCode:(NSNotification *) notification {
	NoticationItem *dic = [notification object];
    _fid = (NSString *)[dic.data objectForKey:@"user_uid"]; 
   [self performSelectorOnMainThread:@selector(startAuth) withObject:nil waitUntilDone:YES];
}

- (void) setFriendsArray:(NSNotification *) notification {
	NoticationItem *dic = [notification object];
    NSLog(@"search friend result: %@", dic.data);
    
//    if(_searchResult == nil){
//        _searchResult = [[NSMutableArray alloc] init];
//    }else{
//        [_searchResult removeAllObjects];
//    }
//    
//    for(NSString *key in  dic.data){
//        NSString * uid = key;
//        
//        if(key.length > 8){
//            NSString * sitePrefix = [key substringToIndex:8];
//            if([sitePrefix isEqualToString:@"cnalichn"] 
//               || [sitePrefix isEqualToString:@"enaliint"]
//               || [sitePrefix isEqualToString:@"cntaobao"]){
//                
//                NSDictionary * valueDict = [dic.data objectForKey:key];
//                AMIMUserModel * user = [[AMIMUserModel alloc] init];
//                user.uid = uid;
//                user.nickname = [valueDict objectForKey:@"name"];
//                user.status = ((NSNumber *)[valueDict objectForKey:@"status"]);
//                [_searchResult addObject:user];
//                [user release];
//            }
//
//        }
// 
//    }
    
    if(dic.data.count == 0){
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"没有符合条件用户！"] show];
    }else{
        self.searchResult = dic.data.allKeys;
        self.searchResultDic = dic.data;
    }
    
    [self performSelectorOnMainThread:@selector(refreshSearchResultTable) withObject:nil waitUntilDone:YES];

}

- (void) refreshSearchResultTable
{
    [_searchTable reloadData];
}

-(IBAction)searchAction:(id)sender
{
    NSString * keyWord = [_textField.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    if(keyWord != nil && ![keyWord isEqualToString:@""]){
        [[CallBackTool create] searchFriends:keyWord];
    }else{
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"请输入有效关键字"] show];
    } 
}

#pragma table
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
return 45;

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
    
    if(_searchResult != nil && _searchResult.count >0){
            return 1;
    }
    
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{

    if(_searchResult != nil && _searchResult.count >0){
        return _searchResult.count;
    }
    
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    NSString *uid=nil;
    int section = [indexPath section];
    int row = [indexPath row];
    uid = (NSString *)[self.searchResult objectAtIndex:row];

    if(uid != nil){  
        
        AMIMUserDetailViewController * userDetailViewController = [[AMIMUserDetailViewController alloc] initWithUser:uid relation:USER_RELATION_FRIEND];
        [self.navigationController pushViewController:userDetailViewController animated:YES]; 
        [userDetailViewController release];
    }
         
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    //int section = [indexPath section];
    int row = [indexPath row];
    
    if(_searchResult != nil && _searchResult.count > row){
        NSString *uid = (NSString *)[self.searchResult objectAtIndex:row];
        if(uid != nil){
            AMIMSearchNewFriendCell *cell = (AMIMSearchNewFriendCell *)[tableView 
                                                                        dequeueReusableCellWithIdentifier:@"im_search_new_friend_cell"];
     
            if (cell == nil)  
            {
                NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMSearchNewFriendCell" 
                                                             owner:self options:nil];
                for (id oneObject in nib)
                    if ([oneObject isKindOfClass:[AMIMSearchNewFriendCell class]])
                        cell = (AMIMSearchNewFriendCell *)oneObject;
                
//                cell.headImg.layer.masksToBounds = YES;
//                cell.headImg.layer.cornerRadius = 5.0;
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
            cell.headImg.url = nil;
            cell.headImg.image = nil;
            cell.signLabel.text = @"";
            cell.textLabel.text = @"";
            
            NSDictionary * valueDict = [self.searchResultDic objectForKey:uid];
            
            cell.headImg.url = [StringUtils getWwHeadImageWithUid:uid];
            [_objMan manage:cell.headImg];
            cell.nameLabel.text = [valueDict objectForKey:@"name"];
            cell.signLabel.text = [self getSiteName:[uid substringToIndex:8]];
            if([self isStatusVisible:(EnDetailStatus)(((NSNumber *)[valueDict objectForKey:@"status"]).intValue)]){
                cell.headMaskImg.hidden = YES;
            }else{
                cell.headMaskImg.hidden = NO;
            }
            [cell.addBtn addTarget:self action:@selector(addNewFriend:event:) forControlEvents:UIControlEventTouchUpInside];
         
            return  cell;
        }
    }

        
    return nil;
}

- (void)addNewFriend:(id)sender event:(id)event
{
    NSSet *touches = [event allTouches];
    UITouch *touch = [touches anyObject];
    CGPoint currentTouchPosition = [touch locationInView:self.searchTable];
    NSIndexPath *indexPath = [self.searchTable indexPathForRowAtPoint:currentTouchPosition];
    if(indexPath != nil)
    {
        int row = [indexPath row];
        NSString *uid = (NSString *)[self.searchResult objectAtIndex:row];
        [[CallBackTool create] addFriend :uid];
    }
}

- (NSString *) getSiteName:(NSString *)prefix
{
    if([prefix isEqualToString:@"cnalichn"]){
        
        return @"阿里巴巴中文站";
    }else if([prefix isEqualToString:@"enaliint"]){
        
        return @"阿里巴巴国际站";
    }else if([prefix isEqualToString:@"cntaobao"]){
        return @"淘宝网";
    }
    
    return @"";
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

- (IBAction)hideKeyboard:(id)sender
{
    [_textField resignFirstResponder];
}


@end

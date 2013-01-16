//
//  AMIMHomeViewController.m
//  AlibabaMobile
//
//  Created by  on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>

#import "AMIMHomeViewController.h"
#import "CallBackTool.h"
#import "LoginToken.h"
#import "SignatureDownloadOperation.h"
#import "AliToastView.h"
#import "HJObjManager.h"
#import "HJManagedImageV.h"
#import "StringUtils.h"
#import "UIHelp.h"
#import "WwStatePickView.h"
#import "AMIMFriendListViewController.h"
#import "AMIMSysMsgListViewController.h"
#import "AMIMRecentFriendListViewController.h"
#import "AMIMUserDetailViewController.h"
#import "AMIMUser.h"
#import "AMIMCoreDataHelper.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "MessageCenterButtonView.h"
#import "AMIMUserDefault.h"
#import "WwNoticePickView.h"

#define COREDATA_CURRENT_CONTEXT @"CurrentCoreDataContext"

#define TAB_CONTENT_FRIENDLIST 0
#define TAB_CONTENT_RECENT_FRIENDLIST 1
#define TAB_CONTENT_SYS_MSGLIST 2

@interface AMIMHomeViewController()
{
    NSArray *  _stateArray;
    UIView * currentView;
}

@property (nonatomic, retain) AMIMUser * selfUser;

@property (nonatomic, retain) NSMutableDictionary * dataDict;

@property (nonatomic,retain) HJObjManager *objMan;

@property (nonatomic, retain) IBOutlet HJManagedImageV * mHeadImage;
@property (nonatomic, retain) IBOutlet UILabel * mNameLabel;
@property (nonatomic, retain) IBOutlet UIButton * mStatePickerBtn;
@property (nonatomic, retain) IBOutlet WwStatePickView * mWwStatePickView;
@property (nonatomic, retain) IBOutlet WwNoticePickView * mWwNotickPickView;

@property (nonatomic, retain) IBOutlet UIImageView * stateBkImgView;
@property (nonatomic, retain) IBOutlet UIButton * stateBtn;

@property (nonatomic, retain) IBOutlet UIButton * mRecentFriendListBtn;
@property (nonatomic, retain) IBOutlet UIButton * mFriednListBtn;
@property (nonatomic, retain) IBOutlet UIButton * mSysMsgListBtn;

@property (nonatomic, retain) IBOutlet UIButton * mSettingBtn;

@property (nonatomic, retain) IBOutlet UIImageView * mTopBkImg;

@property (nonatomic, retain) AMIMFriendListViewController * mFriendListViewController;
@property (nonatomic, retain) AMIMRecentFriendListViewController * mRecentFriendListViewController;
@property (nonatomic, retain) AMIMSysMsgListViewController * mSysMsgListViewController;

@end

@implementation AMIMHomeViewController

@synthesize selfUser = _selfUser;
@synthesize dataDict = _dataDict;

@synthesize objMan = _objMan;
@synthesize mHeadImage = _mHeadImage;
@synthesize mNameLabel = _mNameLabel;
@synthesize mStatePickerBtn = _mStatePickerBtn;
@synthesize mWwStatePickView = _mWwStatePickView;
@synthesize mWwNotickPickView = _mWwNotickPickView;
@synthesize mTopBkImg =_mTopBkImg;

@synthesize stateBtn = _stateBtn;
@synthesize stateBkImgView = _stateBkImgView;

@synthesize  mRecentFriendListBtn = _mRecentFriendListBtn;
@synthesize mFriednListBtn = _mFriednListBtn;
@synthesize mSysMsgListBtn = _mSysMsgListBtn;

@synthesize mSettingBtn = _mSettingBtn;

@synthesize mFriendListViewController = _mFriendListViewController;
@synthesize mRecentFriendListViewController = _mRecentFriendListViewController;
@synthesize mSysMsgListViewController = _mSysMsgListViewController;

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_objMan release];
    [_mHeadImage release];
    [_mNameLabel release];
    [_mStatePickerBtn release];
    [_mWwStatePickView release];
    [_mWwNotickPickView release];
    [_stateArray release];
    [currentView release];
    
    [_mTopBkImg release];
    
    [_stateBkImgView release];
    [_stateBtn release];
    
    [_mRecentFriendListBtn release];
    [_mFriednListBtn release];
    [_mSysMsgListBtn release];
    
    [_mSettingBtn release];
    
    [_mFriendListViewController release];
    [_mRecentFriendListViewController release];
    [_mSysMsgListViewController release];
    
    [super dealloc];
}

- (id)init
{
    self = [super initWithNibName:@"AMIMHomeViewController" bundle:nil];
    if (self) {
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_aliww"];        
        self.tabBarItem.title=NSLocalizedString(@"ImTitle", @"");
        
        _stateArray = [NSArray arrayWithObjects:
                       [NSNumber numberWithInt:IMPREDEFSTATUS_FREE],
                       [NSNumber numberWithInt:IMPREDEFSTATUS_BUSY],
                       [NSNumber numberWithInt:IMPREDEFSTATUS_INVISIBLE],
                       [NSNumber numberWithInt:IMPREDEFSTATUS_OUTFORDINNER],
                       [NSNumber numberWithInt:IMPREDEFSTATUS_INCALL],
                       [NSNumber numberWithInt:IMPREDEFSTATUS_WAIT],
                       nil];
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(wangwangLoginNotice) name:NOTIFICATION_WW_START_LOGIN object:nil];
        ///监听注销事件
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_QUITWANGWANG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_LOGOUT object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_NETWORKERROR object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_FORCEDISCONNECT object:nil];
        
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mergeContextChangesForNotification:) name:NSManagedObjectContextDidSaveNotification object:nil]; 
    }
    return self;
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
  
    [self setLogo];
    [self objManInit];
    
    [self initContentViews];
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    if(appDelegate.isWwLogined){
        [self loginSucc];
    }
}

- (void)viewDidUnload
{
    self.objMan = nil;
    [super viewDidUnload];
}

- (void)doLoginNotice
{
    UILabel * label = [[UILabel alloc] init];
    label.backgroundColor = [UIColor clearColor];
    label.font = [UIFont boldSystemFontOfSize:16.0f];
    label.textColor = [UIColor whiteColor];
    label.text = @"（连接中...）";
    
    UIBarButtonItem * item = [[UIBarButtonItem alloc] init];
    item.customView = label;
    self.navigationItem.leftBarButtonItem = item;
    [item release];
    [label release];
}

- (void)wangwangLoginNotice
{
    [self performSelectorOnMainThread:@selector(doLoginNotice) withObject:nil waitUntilDone:NO ];
}

- (void) setLogo
{
    UIImageView * logoImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"logo_topbar"]];
    self.navigationItem.titleView = logoImg;
    [logoImg release];
}

- (void)mergeContextChangesForNotification:(NSNotification *)aNotification 
{ 
    [self performSelectorOnMainThread:@selector(mergeOnMainThread:) withObject:aNotification waitUntilDone:YES]; 
}

- (void)mergeOnMainThread:(NSNotification *)aNotification 
{ 
    NSManagedObjectContext * thisContext = [[[NSThread currentThread] threadDictionary] objectForKey:COREDATA_CURRENT_CONTEXT];
    if(thisContext){
        [thisContext mergeChangesFromContextDidSaveNotification:aNotification]; 
    } 
} 

- (void)loginOut
{
    self.navigationItem.rightBarButtonItem = nil;
    [self quitWangWang];
}

- (IBAction) userDetailAction
{
    [AMLogUtils appendLog:APP_WANGWANG_MAIN_ONE];
    
    AMIMUserDetailViewController * userDetailViewController = [[[AMIMUserDetailViewController alloc] initWithUser:_selfUser.uid  relation:USER_RELATION_SEFL ] autorelease];
    
    [userDetailViewController setHidesBottomBarWhenPushed:YES];
    [self.navigationController pushViewController:userDetailViewController animated:YES];   
    [self.navigationController setNavigationBarHidden:NO animated:NO];
}

- (void) initContentViews
{
    _mFriendListViewController = [[AMIMFriendListViewController alloc] initWithNavigation:self.navigationController];
    _mRecentFriendListViewController = [[AMIMRecentFriendListViewController alloc] initWithNavigation:self.navigationController];
    _mSysMsgListViewController = [[AMIMSysMsgListViewController alloc] initWithNavigation:self.navigationController];
    
    currentView = nil;
//    [self.view insertSubview:_mRecentFriendListViewController.view atIndex:0];
//    [self.view insertSubview:_mSysMsgListViewController.view atIndex:0];
    
      
    _mFriednListBtn.tag = TAB_CONTENT_FRIENDLIST;
    _mRecentFriendListBtn.tag = TAB_CONTENT_RECENT_FRIENDLIST;
    _mSysMsgListBtn.tag = TAB_CONTENT_SYS_MSGLIST;
    
    [_mFriednListBtn setImage:[UIImage imageNamed:@"icon_aliww_talk_t"] forState:UIControlStateHighlighted];
    [_mRecentFriendListBtn setImage:[UIImage imageNamed:@"icon_aliwwhistory_t"] forState:UIControlStateHighlighted];
    [_mSysMsgListBtn setImage:[UIImage imageNamed:@"icon_toast_info_t"] forState:UIControlStateHighlighted];
    
    [_mFriednListBtn addTarget:self action:@selector(changeTabContent:) forControlEvents:UIControlEventTouchDown];
    [_mRecentFriendListBtn addTarget:self action:@selector(changeTabContent:) forControlEvents:UIControlEventTouchDown];
    [_mSysMsgListBtn addTarget:self action:@selector(changeTabContent:) forControlEvents:UIControlEventTouchDown];
    
    [self  switchTabContent:TAB_CONTENT_FRIENDLIST];
}

- (IBAction)changeTabContent:(id)sender
{
    int index = ((UIButton *)sender).tag;
    [self switchTabContent:index];
}

- (void) switchTabContent:(int)index
{
    UIView * nextView = nil;;
    switch (index) {
        case TAB_CONTENT_FRIENDLIST:
            [AMLogUtils appendLog:APP_WANGWANG_LIST_ONE];
            
            _mFriendListViewController.view.hidden = NO;
            _mRecentFriendListViewController.view.hidden = YES;
            _mSysMsgListViewController.view.hidden = YES;
            
            nextView = _mFriendListViewController.view;
            
            [_mFriednListBtn setImage:[UIImage imageNamed:@"icon_aliww_talk_t"] forState:UIControlStateNormal];
            [_mRecentFriendListBtn setImage:[UIImage imageNamed:@"icon_aliwwhistory_n"] forState:UIControlStateNormal];
            [_mSysMsgListBtn setImage:[UIImage imageNamed:@"icon_toast_info_n"] forState:UIControlStateNormal];
            break;
        case TAB_CONTENT_RECENT_FRIENDLIST:
            [AMLogUtils appendLog:APP_WANGWANG_RECENT_ONE];
            
            _mFriendListViewController.view.hidden = YES;
            _mRecentFriendListViewController.view.hidden = NO;
            _mSysMsgListViewController.view.hidden = YES;
            
            nextView = _mRecentFriendListViewController.view;
            
            [_mFriednListBtn setImage:[UIImage imageNamed:@"icon_aliww_talk_n"] forState:UIControlStateNormal];
            [_mRecentFriendListBtn setImage:[UIImage imageNamed:@"icon_aliwwhistory_t"] forState:UIControlStateNormal];
            [_mSysMsgListBtn setImage:[UIImage imageNamed:@"icon_toast_info_n"] forState:UIControlStateNormal];
            break;
        case TAB_CONTENT_SYS_MSGLIST:
            [AMLogUtils appendLog:APP_WANGWANG_SYSMSG_ONE];
            
            _mFriendListViewController.view.hidden = YES;
            _mRecentFriendListViewController.view.hidden = YES;
            _mSysMsgListViewController.view.hidden = NO;
            
            nextView = _mSysMsgListViewController.view;
            
            [_mFriednListBtn setImage:[UIImage imageNamed:@"icon_aliww_talk_n"] forState:UIControlStateNormal];
            [_mRecentFriendListBtn setImage:[UIImage imageNamed:@"icon_aliwwhistory_n"] forState:UIControlStateNormal];
            [_mSysMsgListBtn setImage:[UIImage imageNamed:@"icon_toast_info_t"] forState:UIControlStateNormal];
            break;
        default:
            break;
    }
    
    if(nextView != nil && nextView != currentView){
        [currentView removeFromSuperview];
        [self.view insertSubview:nextView atIndex:0];
        currentView = nextView;
    }
}

- (void) statePicked:(int) state
{
    if(state == _selfUser.status){
        return;        
    }

    switch (state) {
        case IMPREDEFSTATUS_FREE:
            [_mStatePickerBtn setBackgroundImage: [UIImage imageNamed:@"icon_aliww_online"] forState:UIControlStateNormal] ;
            break;
        case IMPREDEFSTATUS_BUSY:
            [_mStatePickerBtn setBackgroundImage: [UIImage imageNamed:@"icon_aliww_busy"] forState:UIControlStateNormal] ;
            break;
        case IMPREDEFSTATUS_INVISIBLE:
            [_mStatePickerBtn setBackgroundImage: [UIImage imageNamed:@"icon_aliww_hide"] forState:UIControlStateNormal] ;
            break;
        case IMPREDEFSTATUS_OUTFORDINNER:
            [_mStatePickerBtn setBackgroundImage: [UIImage imageNamed:@"icon_aliww_dealing"] forState:UIControlStateNormal] ;
            break;
        case IMPREDEFSTATUS_INCALL:
            [_mStatePickerBtn setBackgroundImage: [UIImage imageNamed:@"icon_aliww_phone"] forState:UIControlStateNormal] ;
            break;
        case IMPREDEFSTATUS_AWAY:
            [_mStatePickerBtn setBackgroundImage: [UIImage imageNamed:@"icon_aliww_outing"] forState:UIControlStateNormal] ;
            break;
        default:
            state = _selfUser.status;
            break;
    }
    _selfUser.status = (EnDetailStatus)state;
    
    [[CallBackTool create] changeSelfStatus:(EnDetailStatus)state];
    [AMIMDefaultStorageHelper changeSelfState:state];
    [[AMIMCoreDataHelper getInstance] changeUserStatusWithUid:[AMIMDefaultStorageHelper getLastLoginedUserId] status:state ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
}

- (void) loginSucc
{
     self.navigationItem.leftBarButtonItem.customView.hidden = YES;
    //by tom.lih
    //[self quitWangWang];
  
    if(_selfUser != nil){
        [_selfUser release];
        _selfUser = nil;
    }
 
    _selfUser = [[AMIMUser alloc] init];
    _selfUser.uid = [NSString stringWithFormat:@"%@%@",ACCOUNT_SITE, [LoginToken getLoginUserName] ];
    _selfUser.nickname = [LoginToken getLoginUserName];

    [self setUserHeader];
    [self setUsername];
    [self setStatePicker];
    [self setSettingBtn];
   
    
//    CallBackTool *callBack = [CallBackTool create];
//    [callBack getUserDetail:[NSString stringWithFormat:@"%@%@", @"cnalichn", [LoginToken getLoginUserName]]];
   
}

- (void) setSettingBtn
{
    UIImage * bkImg = [UIImage imageNamed:@"Aliww_button_press"];
    bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height/2];
    [_mSettingBtn setBackgroundImage:bkImg forState:UIControlStateHighlighted];
    [_mSettingBtn addTarget:self action:@selector(settingBtnClick) forControlEvents:UIControlEventTouchUpInside];
}

- (void) setUserHeader
{
//    _mHeadImage.layer.masksToBounds = YES;
//    _mHeadImage.layer.cornerRadius = 5.0;
    
    _mHeadImage.imageView.layer.borderWidth = 2.0f;
    _mHeadImage.imageView.layer.borderColor = [UIColor whiteColor].CGColor;
    _mHeadImage.userInteractionEnabled = NO;
    
    _mHeadImage.url =  [StringUtils getWwHeadImageWithUid: [NSString stringWithFormat:@"%@%@",ACCOUNT_SITE, [LoginToken getLoginUserName] ]];
    _mHeadImage.image=nil;
    [self.objMan manage:_mHeadImage];

    _mHeadImage.userInteractionEnabled = YES;
    UITapGestureRecognizer * clickRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userDetailAction)];
    [_mHeadImage addGestureRecognizer:clickRecognizer];
    [clickRecognizer release];

}

- (void) setUsername
{
    _mNameLabel.text = [LoginToken getLoginUserName];
   // _mNameLabel.shadowColor = [UIColor blackColor];
    [_mNameLabel setAdjustsFontSizeToFitWidth:NO];
  //  _mNameLabel.shadowOffset = CGSizeMake(0, -1);
    int nameLabelWidth = [UIHelp getLabelSizeWithFont:_mNameLabel.font labelString:_mNameLabel.text labelHeight:20].width;
    nameLabelWidth = (nameLabelWidth > 160 ? 160:nameLabelWidth);
    _mNameLabel.frame = CGRectMake(_mNameLabel.frame.origin.x, _mNameLabel.frame.origin.y, nameLabelWidth, 20);
    _stateBtn.frame = CGRectMake(_stateBtn.frame.origin.x, _stateBtn.frame.origin.y, _mNameLabel.frame.origin.x+_mNameLabel.frame.size.width+10-_stateBtn.frame.origin.x, _stateBtn.frame.size.height);

    _stateBkImgView.frame = CGRectMake(_stateBtn.frame.origin.x, _stateBtn.frame.origin.y, _stateBtn.frame.size.width, _stateBtn.frame.size.height);
    _stateBkImgView.contentMode = UIViewContentModeScaleToFill;
//    UIImage * bkImg = [UIImage imageNamed:@"Aliww_button"];
//    bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height/2];
    _stateBkImgView.image = nil;
    
    [_stateBtn addTarget:self action:@selector(showStatePicker) forControlEvents:UIControlEventTouchUpInside];
    [_stateBtn addTarget:self action:@selector(stateBtnPressed) forControlEvents:UIControlEventTouchDown];
    [_stateBtn addTarget:self action:@selector(stateBtnPressedUpOutside) forControlEvents:UIControlEventTouchUpOutside];
    [_stateBtn addTarget:self action:@selector(stateBtnPressedUpOutside) forControlEvents:UIControlEventTouchCancel];

}

- (IBAction)settingBtnClick {
    [UIView setAnimationDuration:0.7];
    [UIView beginAnimations:@"show" context:nil];
    _mWwNotickPickView.alpha = 1.0f;
    [UIView commitAnimations];
    [_mFriendListViewController doSearchModeEnd];
}

-(void)noticePickedMusic:(bool)music shake:(bool)shake
{
    [AMIMDefaultStorageHelper changeSelfNotickWithMusic:music shake:shake];
    [self changeNoticBtnImageWith:music shake:shake];
}

- (void)changeNoticBtnImageWith:(bool)music shake:(bool)shake
{
    if(music){
        if(shake){
            [_mSettingBtn setImage:[UIImage imageNamed:@"icon_aliww_zdl"] forState:UIControlStateNormal];
        }else{
            [_mSettingBtn setImage:[UIImage imageNamed:@"icon_aliww_music"] forState:UIControlStateNormal];
        }
    }else{
        if(shake){
            [_mSettingBtn setImage:[UIImage imageNamed:@"icon_aliww_zd"] forState:UIControlStateNormal];
        }else{
           [_mSettingBtn setImage:[UIImage imageNamed:@"icon_aliww_jy"] forState:UIControlStateNormal]; 
        }
    }
}

- (IBAction)stateBtnPressed
{
    UIImage * bkImg = [UIImage imageNamed:@"Aliww_button_press"];
    bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height/2];
    _stateBkImgView.image = bkImg;
    
    [_mFriendListViewController doSearchModeEnd];
}

- (IBAction)stateBtnPressedUpOutside
{
    _stateBkImgView.image = nil;
}


- (void) setStatePicker
{
//    _mStatePickerBtn.frame = CGRectMake(_mNameLabel.frame.origin.x + _mNameLabel.frame.size.width + 10, _mStatePickerBtn.frame.origin.y, _mStatePickerBtn.frame.size.width, _mStatePickerBtn.frame.size.height);
    AMIMUserDefault * user = [AMIMDefaultStorageHelper getLastLoginedUser];
    [self statePicked:user.status];
    
    _mWwStatePickView = [[WwStatePickView alloc] initWithState:user.status ];
//    _mWwStatePickView.frame =  CGRectMake(_mStatePickerBtn.frame.origin.x+ _mStatePickerBtn.frame.size.width/2 - _mWwStatePickView.frame.size.width/2, 44, _mWwStatePickView.frame.size.width, _mWwStatePickView.frame.size.height);
    _mWwStatePickView.alpha = 0.0f;
    //_mWwStatePickView.hidden=YES;
    _mWwStatePickView.delegate = self;
    
    _mWwNotickPickView = [[WwNoticePickView alloc] initWithMusic:user.soundNotice shake:user.shakeNotice];
    _mWwNotickPickView.alpha = 0.0f;
    _mWwNotickPickView.delegate = self;
    [self changeNoticBtnImageWith:user.soundNotice shake:user.shakeNotice];
    
    UIWindow * window = [[UIApplication sharedApplication].windows objectAtIndex:0];

    [window addSubview:_mWwStatePickView];
    [window addSubview:_mWwNotickPickView];
//    [self.view addSubview:_mWwStatePickView];
    
    [_mStatePickerBtn addTarget:self action:@selector(showStatePicker) forControlEvents:UIControlEventTouchUpInside];
}

- (IBAction)showStatePicker 
{
//    UIImage * bkImg = [UIImage imageNamed:@"Aliww_button"];
//    bkImg = [bkImg stretchableImageWithLeftCapWidth:bkImg.size.width/2 topCapHeight:bkImg.size.height/2];
    _stateBkImgView.image = nil;
    
    [UIView setAnimationDuration:0.7];
    [UIView beginAnimations:@"show" context:nil];
    _mWwStatePickView.alpha = 1.0f;
    [UIView commitAnimations];

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

- (void)viewWillAppear:(BOOL)animated
{
//    self.navigationController.navigationBarHidden = YES;
//    self.mTopBkImg.frame = CGRectMake(0, 0, 320, 44);
//    self.mTopBkImg.backgroundColor = [UIColor redColor];
//    self.mTopBkImg.frame = CGRectMake(0, 0, 320, 44);
//    self.mTopBkImg.image = [UIImage imageNamed:@"bg_topbar"];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    
}

- (void)viewWillDisappear:(BOOL)animated
{
    self.navigationController.navigationBarHidden = NO;
    [self.navigationController setNavigationBarHidden:NO animated:NO];
    
}

- (void) quitWangWang {
    _mHeadImage.image = nil;
    _mNameLabel.text = @"";
    //hide the pick
    _mWwStatePickView.alpha = 0.0f;
    _mWwNotickPickView.alpha = 0.0f;
    [self switchTabContent:TAB_CONTENT_FRIENDLIST];
}



@end

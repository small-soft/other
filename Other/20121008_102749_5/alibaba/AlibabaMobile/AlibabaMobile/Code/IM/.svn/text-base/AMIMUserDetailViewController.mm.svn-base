//
//  AMIMUserDetailViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-14.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMUserDetailViewController.h"
#import "AliToastView.h"
#import "HJObjManager.h"
#import "HJManagedImageV.h"
#import "StringUtils.h"
#import "UIHelp.h"
#import "CallBackTool.h"
#import "AMIMUserModel.h"
#import "AMIMUserInfoTableCell.h"
#import "AMIMModifySignViewController.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMCoreDataHelper.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AMIMTalkViewController.h"
#import "AMIMSearchFriendViewController.h"
#import "AMIMFriendListViewController.h"

enum USER_INFO_TYPE {
    USER_INFO_UID = 0,
    USER_INFO_NICKNAME,
    USER_INFO_NAME,
    USER_INFO_GENDER,
    USER_INFO_BIRTHDAY,
    USER_INFO_ZODIAC,
    USER_INFO_YEAROF,
    USER_INFO_COUNTRY,
    USER_INFO_PROVINCE,
    USER_INFO_CITY,
    USER_INFO_CELLPHONE,
    USER_INFO_TELEPHONE,
    USER_INFO_EMAIL,
    USER_INFO_OCCUPATION,
    USER_INFO_SCHOOL,
    USER_INFO_HOMEPAGE
    
} ;


@interface AMIMUserDetailViewController ()
{
    AMIMUserModel * _user;
    NSString * _uid;
    int _relation;    
}

@property (nonatomic,retain)  HJObjManager *objMan;
@property (nonatomic, retain) IBOutlet HJManagedImageV * headImgView;
@property (nonatomic, retain) IBOutlet UIImageView * headMaskImg;

@property (nonatomic, retain) IBOutlet UILabel * nameLabel;
@property (nonatomic, retain) IBOutlet UILabel * signLabel;
@property (nonatomic, retain) IBOutlet UIView * signView;
@property (nonatomic, retain) IBOutlet UILabel * selfSignLabel;

@property (nonatomic, retain) IBOutlet UIButton * addFriendBtn;
@property (nonatomic, retain) IBOutlet UIButton * talkBtn;
@property (nonatomic, retain) IBOutlet UIButton * modifyBtn;

@property (nonatomic, retain) IBOutlet UIScrollView * scrollView;
@property (nonatomic, retain) IBOutlet UIView * infoView;

@end

@implementation AMIMUserDetailViewController

@synthesize headImgView = _headImgView;
@synthesize objMan = _objMan;
@synthesize headMaskImg = _headMaskImg;

@synthesize nameLabel = _nameLabel;
@synthesize signLabel = _signLabel;
@synthesize signView = _signView;
@synthesize selfSignLabel = _selfSignLabel;

@synthesize addFriendBtn = _addFriendBtn;
@synthesize talkBtn = _talkBtn;
@synthesize modifyBtn = _modifyBtn;

@synthesize scrollView = _scrollView;
@synthesize infoView = _infoView;


-(void)dealloc
{
    [_objMan release];
    [_headImgView release];
    [_nameLabel release];
    [_signLabel release];
    [_addFriendBtn release];
    [_talkBtn release];

    [_scrollView release];
    [_headImgView release];
    [_modifyBtn release];
    
    [_user release];
    
    [_signView release];
    [_selfSignLabel release];
    
    [_infoView release];
    [_uid release];
    
    [super dealloc];
}

- (id)initWithUser:(NSString *)userId relation:(int)relation
{
    self = [super init];
    if (self) {
        _relation = relation;
        _uid = userId; 
       
    }
    return self;
}

- (void) navigationBack
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super navigationBack];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    _headMaskImg.hidden = YES;
    self.title = @"";
    [self.mLoadingView showLoadingView];
    [self initSubViews];
    [self objManInit];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changeSelfSignatureSucc:) name:NOTIFICATION_CHANGESELFIGNATURE object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setUserDetail:) name:NOTIFICATION_GETUSERDETAIL object:nil];
    
    [self getDetailData];

}

- (void) initSubViews
{
    _headImgView.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"tx_aliww_detail"]];
    //    _headImgView.layer.masksToBounds = YES;
    //    _headImgView.layer.cornerRadius = 5.0;
    _headImgView.layer.borderWidth = 2.0f;
    _headImgView.layer.borderColor = [UIColor whiteColor].CGColor;
    
    [_nameLabel setAdjustsFontSizeToFitWidth:NO];
    [_signLabel setAdjustsFontSizeToFitWidth:NO];
    
    
    UIImage * bgNormal = [UIImage imageNamed:@"btn_ct_nor"];
    bgNormal = [bgNormal stretchableImageWithLeftCapWidth:bgNormal.size.width/2 topCapHeight:bgNormal.size.height/2 ];
    UIImage * bgTap =  [UIImage imageNamed:@"btn_ct_p"];
    bgTap = [bgTap stretchableImageWithLeftCapWidth:bgTap.size.width/2 topCapHeight:bgTap.size.height/2 ];
    
    [_addFriendBtn setBackgroundImage:bgNormal forState:UIControlStateNormal];
    [_addFriendBtn setBackgroundImage:bgTap forState:UIControlStateHighlighted];
    
    
    [_addFriendBtn addTarget:self action:@selector(addNewFriend:) forControlEvents:UIControlEventTouchUpInside];
    _addFriendBtn.hidden = YES;
    
    [_talkBtn setBackgroundImage:bgNormal forState:UIControlStateNormal];
    [_talkBtn setBackgroundImage:bgTap forState:UIControlStateHighlighted];
    
    [_modifyBtn setBackgroundImage:bgNormal forState:UIControlStateNormal];
    [_modifyBtn setBackgroundImage:bgTap forState:UIControlStateHighlighted];
    
    if(_relation == USER_RELATION_SEFL){
        _talkBtn.hidden = YES;
        //_addFriendBtn.hidden = YES;
        _modifyBtn.hidden = NO;
        _signLabel.hidden = YES;
        _signView.hidden = NO;
        _signView.layer.borderColor = [UIHelp colorWithHexString:@"0xCBCBCB"].CGColor;
        _signView.layer.borderWidth = 1.0f;
        
        _infoView.frame = CGRectMake(_infoView.frame.origin.x, 178, _infoView.frame.size.width, _infoView.frame.size.height);
        
        [_modifyBtn addTarget:self action:@selector(modifySign:) forControlEvents:UIControlEventTouchUpInside];
        
    }else if(_relation == USER_RELATION_FRIEND){
        _talkBtn.hidden = NO;
        //_addFriendBtn.hidden = NO;
        _modifyBtn.hidden = YES;
        _addFriendBtn.enabled = NO;
        _signLabel.hidden = NO;
        _signView.hidden = YES;
        
        [_talkBtn addTarget:self action:@selector(talkToFriend:) forControlEvents:UIControlEventTouchUpInside];
    }else if(_relation == USER_RELATION_STRANGER){
        _talkBtn.hidden = NO;
        //_addFriendBtn.hidden = NO;
        _modifyBtn.hidden = YES;
        _addFriendBtn.enabled = YES;
        _signLabel.hidden = NO;
        _signView.hidden = YES;
        
        [_talkBtn addTarget:self action:@selector(talkToFriend:) forControlEvents:UIControlEventTouchUpInside];
    }
    
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

- (void) setUserDetail:(NSNotification *) notification {
    NoticationItem *dic=[notification object];
    NSDictionary *userDetail = dic.data;
    NSLog(@"user detail: %@",userDetail);
    
    [[AMIMCoreDataHelper getInstance] changeUserDetailWithUid:_uid ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId] data:dic.data];

    [self performSelectorOnMainThread:@selector(setContentData) withObject:nil waitUntilDone:NO];
}

- (void) getDetailData
{
//    if(    (_user.name ==nil )    && (_user.gender ==nil ) 
//        && (_user.birthday ==nil) && (_user.zodiac ==nil) 
//        && (_user.yearof ==nil)   && (_user.country ==nil) 
//        && (_user.province ==nil) && (_user.city ==nil) 
//        && (_user.cellphone ==nil)&& (_user.telephone ==nil) 
//        && (_user.email ==nil)    && (_user.occupation ==nil) 
//        && (_user.school ==nil)   && (_user.homepage ==nil)
//       ) {
//        
//        [[[[NSThread alloc] initWithTarget:self selector:@selector(doGetDetailData) object:nil] autorelease] start];
//        
//    }else {    
//        NSLog(@"have got detailed information !"); 
//        [self setContentData];
//        [[[[NSThread alloc] initWithTarget:self selector:@selector(doGetDetailData) object:nil] autorelease] start];
//                
//    }
    [self performSelector:@selector(timeOut) withObject:nil afterDelay:5.0];
    [self performSelectorInBackground:@selector(doGetDetailData) withObject:nil];

}

- (void) timeOut
{
    if (self.mLoadingView.hidden ==NO) {
        [self.mLoadingView endLoadingView];
        [self setContentData];
    }
}

- (void) doGetDetailData
{
    [[CallBackTool create] getUserDetail:_uid];
}

- (void) setContentData
{

    NSString * nickname;
    NSString * sign;
    int status;
    
    _user = [[[AMIMCoreDataHelper getInstance] getFriendWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] uid:_uid] retain];
    
    if(_user == nil){
        nickname = [_uid substringFromIndex:8];
        sign = @"";
        status = 0;
    }else{
        nickname = _user.nickname;
        sign = _user.signature;
        status = _user.status.intValue;
    }

    _headImgView.url = [StringUtils getWwHeadImageWithUid:_uid];
    [_objMan manage:_headImgView];
    if([self isStatusVisible:(EnDetailStatus)status]){
        _headMaskImg.hidden = YES;
    }else {
        _headMaskImg.hidden = NO;
    }
    
    if(_relation == USER_RELATION_SEFL){
        self.title = @"个人资料";
        _selfSignLabel.numberOfLines = 0;
        _selfSignLabel.text = sign;
        _selfSignLabel.lineBreakMode = (UILineBreakMode)(UILineBreakModeWordWrap | UILineBreakModeTailTruncation);  
        int signLabelHeight = [UIHelp getLabelSizeWithFont:_selfSignLabel.font labelString:_selfSignLabel.text labelWidth:_selfSignLabel.frame.size.width].height;
        signLabelHeight =( signLabelHeight >  32? 32:signLabelHeight);
        _selfSignLabel.frame = CGRectMake(_selfSignLabel.frame.origin.x, _selfSignLabel.frame.origin.y, _selfSignLabel.frame.size.width, signLabelHeight);
    }else{
        self.title = nickname;
        _signLabel.numberOfLines = 0;
        _signLabel.text = sign;
        _signLabel.lineBreakMode = (UILineBreakMode)(UILineBreakModeWordWrap | UILineBreakModeTailTruncation);  
        int signLabelHeight = [UIHelp getLabelSizeWithFont:_signLabel.font labelString:_signLabel.text labelWidth:_signLabel.frame.size.width].height;
        signLabelHeight =( signLabelHeight >  32? 32:signLabelHeight);
        _signLabel.frame = CGRectMake(_signLabel.frame.origin.x, _signLabel.frame.origin.y, _signLabel.frame.size.width, signLabelHeight);
    }
    _nameLabel.text = nickname;
    [self.mLoadingView endLoadingView];
    [self performSelectorOnMainThread:@selector(refreshUI) withObject:nil waitUntilDone:NO];
}

-(void) refreshUI
{
    int startX  = 0;
    int startY = 0;
    int lineHeight = 45;
    int lineWidth = 300;
    
    _infoView.backgroundColor = [UIColor whiteColor];
    _infoView.layer.borderWidth = 1.0f;
    _infoView.layer.borderColor = [UIHelp colorWithHexString:@"0xCBCBCB"].CGColor;
    for(int i=0; i<15;i++){
        int row = i;
        UIView * cell = [[UIView alloc] init ];
        cell.backgroundColor = [UIColor clearColor];
        
        cell.frame = CGRectMake(startX, startY + i * lineHeight, lineWidth, lineHeight);
        
        UILabel * keyLabel = [[UILabel alloc] init];
        keyLabel.frame = CGRectMake(6, 14, 69, 16);
        keyLabel.font = [UIFont boldSystemFontOfSize:16.0f];
        keyLabel.textColor = [UIHelp colorWithHexString:@"0x666666"];
        keyLabel.textAlignment = UITextAlignmentRight;
        
        UILabel * valueLabel = [[UILabel alloc] init];
        valueLabel.frame = CGRectMake(88, 14, 198, 16);
        valueLabel.font = [UIFont boldSystemFontOfSize:16.0f];
        valueLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
        
        switch (row) {
            case USER_INFO_UID:
                keyLabel.text = @"会员名:";
                valueLabel.text = [_user.uid substringFromIndex:8];
                break;
            case USER_INFO_NICKNAME:
                keyLabel.text = @"显示名:";
                valueLabel.text = _user.nickname;
                break;
            case USER_INFO_NAME:
                keyLabel.text = @"姓名:";
                valueLabel.text = _user.name;
                break;
            case USER_INFO_GENDER:
                keyLabel.text = @"性别:";
                valueLabel.text = _user.gender;
                break;
            case USER_INFO_BIRTHDAY:
                keyLabel.text = @"生日:";
                valueLabel.text = _user.birthday;
                break;
            case USER_INFO_ZODIAC:
                keyLabel.text = @"星座:";
                valueLabel.text = _user.zodiac;
                break;
            case USER_INFO_YEAROF:
                keyLabel.text = @"生肖:";
                valueLabel.text = _user.yearof;
                break;
            case USER_INFO_COUNTRY:
                keyLabel.text = @"国家:";
                valueLabel.text = _user.country;
                break;
            case USER_INFO_PROVINCE:
                keyLabel.text = @"省份:";
                valueLabel.text = _user.province;
                break;
            case USER_INFO_CITY:
                keyLabel.text = @"城市:";
                valueLabel.text = _user.city;
                break;
            case USER_INFO_CELLPHONE:
                keyLabel.text = @"手机号码:";
                valueLabel.text = _user.cellphone;
                break;
            case USER_INFO_TELEPHONE:
                keyLabel.text = @"电话:";
                valueLabel.text = _user.telephone;
                break;
            case USER_INFO_EMAIL:
                keyLabel.text = @"邮箱:";
                valueLabel.text = _user.email;
                break;
            case USER_INFO_OCCUPATION:
                keyLabel.text = @"职业:";
                valueLabel.text = _user.occupation;
                break;
            case USER_INFO_SCHOOL:
                keyLabel.text = @"毕业院校:";
                valueLabel.text = _user.school;
                break;
            case USER_INFO_HOMEPAGE:
                keyLabel.text = @"个人主页:";
                valueLabel.text = _user.homepage;
                break;
            default:
                break;
        }
        
        
        [cell addSubview:keyLabel];
        [keyLabel release];
        
        [cell addSubview:valueLabel];
        [valueLabel release];
        
        UIView * lineView = [[UIView alloc] init];
        lineView.frame = CGRectMake(0, i * lineHeight, 300, 1);
        lineView.backgroundColor = [UIHelp colorWithHexString:@"0xCBCBCB"];
        
        [_infoView addSubview:lineView];
        [lineView release];
        
        [_infoView addSubview:cell];
        [cell release];
        
        
    }
    
    _scrollView.contentSize = CGSizeMake(320, _infoView.frame.origin.y + _infoView.frame.size.height);
    
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

- (void) changeSelfSignatureSucc:(NSNotification *)_notification {
    
	NoticationItem * item = [_notification object];
    if(item.errorCode == RESULT_OKEY){
        
        NSString * newSign = [[NSUserDefaults standardUserDefaults] objectForKey:@"im_new_signature"];
        
        [[AMIMCoreDataHelper getInstance] changeUserSignatureWithUid:[AMIMDefaultStorageHelper getLastLoginedUserId] ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId] signature:newSign];
        
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"修改签名成功！"] show];
        
        [self performSelectorOnMainThread:@selector(setContentData) withObject:nil waitUntilDone:NO];
    }else {
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"修改签名失败！"] show];
        
    }
}

- (void)addNewFriend:(id)sender
{
    if(_uid != nil)
    {
        [[CallBackTool create] addFriend :_uid];
    }
}

- (IBAction)talkToFriend:(id)sender
{
       
    if ([ [self.navigationController.viewControllers objectAtIndex: ([self.navigationController.viewControllers count] -2)] isKindOfClass:[AMIMTalkViewController class]]) {
        
        [self.navigationController popViewControllerAnimated:YES];
        
    } else {
        if(_user != nil) {
            AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithUser:_uid];
            [talkViewController setHidesBottomBarWhenPushed:YES];
            [self.navigationController pushViewController:talkViewController animated:YES];
        }
  
    }

}

- (IBAction)modifySign:(id)sender
{
    [AMLogUtils appendLog:APP_WANGWANG_ACCOUNT_DETAIL_ONE];
    
    AMIMModifySignViewController * modifySignViewController = [[AMIMModifySignViewController alloc] initWithUser:_uid];
    [self.navigationController pushViewController:modifySignViewController animated:YES];
}


@end

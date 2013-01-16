//
//  AMIMTalkViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-21.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMTalkViewController.h"
#import "AMIMUser.h"
#import "AliNavigationButton.h"
#import "AMIMUserDetailViewController.h"
#import "FaceKeyboardView.h"
#import "AMIMCoreDataHelper.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMMessageModel.h"
#import "AMIMMsgCell.h"
#import "AMIMMsgToCell.h"
#import "StringUtils.h"
#import "CallBackTool.h"
#import "UIHelp.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "NSAttributedString+HTML.h"
#import "AMIMUserModel.h"
#import "QuickWordsBoard.h"
#import "AliToastView.h"

#define	BREAKSTRING				@"\\T"
#define	MAX_MSG_LENGTH			1000

NSString * const ACCOUNT_TOKEN_CNANONYM = @"cnanonym";
NSString * const ACCOUNT_TOKEN_CNALICHN= @"cnalichn";

@interface AMIMTalkViewController () {
    AMIMUserModel* mUser;
    BOOL faceKeyboardOpen;
    BOOL quickWordBoardOpen;
    
    AMIMCoreDataHelper * _coreDataHelper;
    NSFetchedResultsController * _fetchedResultsController;
    int keyboardHeight;
    NSString * mFriendUid;
    
    BOOL mIsPrecisionTalk;
    NSString * mShowName;
    BOOL mIsUseVisitorId;
}

@property (nonatomic, retain) QuickWordsBoard * quickWordsBoard;
@property (nonatomic, retain) IBOutlet UIView * inputView;
@property (nonatomic, retain) IBOutlet UITableView * msgTable;
@property (nonatomic, retain) IBOutlet UITextField * inputField;
@property (nonatomic, retain) IBOutlet UIButton * faceBtn;

@property (nonatomic, retain) FaceKeyboardView * faceKeyboardView;
@property (nonatomic, retain) IBOutlet UIButton * sendBtn;

@property (nonatomic, retain) IBOutlet UIButton * quickWordsBtn;

@property (nonatomic,retain) HJObjManager *objMan;

@end

@implementation AMIMTalkViewController

@synthesize inputView = _inputView;
@synthesize msgTable = _msgTable;
@synthesize inputField = _inputField;
@synthesize faceBtn = _faceBtn;
@synthesize sendBtn = _sendBtn;
@synthesize quickWordsBtn = _quickWordsBtn;
@synthesize quickWordsBoard = _quickWordsBoard;

@synthesize objMan = _objMan;

@synthesize faceKeyboardView = _faceKeyboardView;

- (id)initWithUser:(NSString *)userId {
    self = [super init];
    if (self) {
        mIsPrecisionTalk = NO;
        mIsUseVisitorId = NO;
        keyboardHeight = 0;
        mFriendUid = userId;
        
        mUser = [[AMIMCoreDataHelper getInstance] getFriendWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] uid:userId];
        mShowName = mUser.nickname;
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_REVMSG object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_QUITWANGWANG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_LOGOUT object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_NETWORKERROR object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_FORCEDISCONNECT object:nil];
        
    }
    return self;
}

- (id)initWithParam:(BOOL)isPrecision:(BOOL)isHandShake:(NSString *)visitorId:(NSString *)friendId:(NSString *)showName {
    self = [super init];
    if (self) {
        mIsPrecisionTalk = isPrecision;
        mShowName = showName;
        mFriendUid = friendId;
        mIsUseVisitorId = NO;
        
        if (isPrecision) {
            if(visitorId == nil || visitorId.length <= 0) {
                return self;
            }

            NSString * fullVisitorId = visitorId;
            if (![fullVisitorId hasPrefix:ACCOUNT_TOKEN_CNANONYM]) {
                fullVisitorId = [ACCOUNT_TOKEN_CNANONYM stringByAppendingString:visitorId];
            }
            
            if (isHandShake) {
                if (friendId == nil || friendId.length <= 0) {
                    mFriendUid = fullVisitorId;
                    mIsUseVisitorId = YES;
                }
            } else {
                mFriendUid = fullVisitorId;
                mIsUseVisitorId = YES;
            }
        } else {
            if (![mFriendUid hasPrefix:ACCOUNT_TOKEN_CNALICHN]) {
                mFriendUid = [ACCOUNT_TOKEN_CNALICHN stringByAppendingString:mFriendUid];
            }
        }
        
        keyboardHeight = 0;
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_REVMSG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_QUITWANGWANG object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_LOGOUT object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_NETWORKERROR object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(quitWangWang) name:NOTIFICATION_FORCEDISCONNECT object:nil];
        
    }
    return self;
}

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_inputView release];
    [_msgTable release];
    [_inputField release];
    [_faceBtn release];
    [_fetchedResultsController release];
    [_coreDataHelper release];
    
    [_sendBtn release];
    
    [_faceKeyboardView release];
    
    [_objMan release];

    [mShowName release];
    [mUser release];
    [mFriendUid release];
    [super dealloc];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    if (mShowName == nil) {
        self.title = mFriendUid;
    } else {
        self.title = mShowName;
    }

    AliNavigationButton * rightBtn = [[AliNavigationButton alloc] initWithTitle:@"详情" style:NAV_BTN_STYLE_COMMON];
    rightBtn.navigationButtonDelegate = self;
    self.navigationItem.rightBarButtonItem = rightBtn;
    [rightBtn release];
    
    _msgTable.delegate = self;
    _msgTable.dataSource = self;
    UITapGestureRecognizer * clickRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(msgTableClick)];
    
    
    _inputField.returnKeyType = UIReturnKeySend;
    _inputField.delegate = self;
    
    _faceKeyboardView = [[FaceKeyboardView alloc] init];
    _faceKeyboardView.kDelegate = self;
    
    faceKeyboardOpen = NO;
     [_faceBtn setImage:[UIImage imageNamed:@"icon_toast_face"] forState:UIControlStateNormal];

    _quickWordsBoard = [[QuickWordsBoard alloc] init];
    quickWordBoardOpen = NO;

    [self refreshMsgTable];
    
    [self objManInit];

    [self scrollToBottom];
    keyboardHeight = 0;
    
    [_msgTable addGestureRecognizer:clickRecognizer];
    [clickRecognizer release];
    
    [_faceBtn addTarget:self action:@selector(faceBtnAction:) forControlEvents:UIControlEventTouchDown];
    
    [_sendBtn addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventTouchUpInside];
    
    [_quickWordsBtn addTarget:self action:@selector(quickWordsBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    
//    [self setupSendBtn];
}

//- (void) setupSendBtn{
//    UIImage * normalBackgroundImage = [UIImage imageNamed:@"Aliww_button.png"] ;
//    [normalBackgroundImage stretchableImageWithLeftCapWidth:self.sendBtn.frame.size.width/4 topCapHeight:self.sendBtn.frame.size.height/4];
//    [self.sendBtn setBackgroundImage:normalBackgroundImage forState:UIControlStateNormal];
//    UIImage * selectBackgroundImage = [UIImage imageNamed:@"Aliww_button_press.png"] ;
//    [selectBackgroundImage stretchableImageWithLeftCapWidth:self.sendBtn.frame.size.width/4 topCapHeight:self.sendBtn.frame.size.height/4];
//    [self.sendBtn setBackgroundImage:selectBackgroundImage forState:UIControlStateSelected];
//    
//    [normalBackgroundImage release];
//    [selectBackgroundImage release];
//}

- (void) refreshMsgTable {
//    if(_coreDataHelper != nil){
//        [_coreDataHelper release];
//    }
//    _coreDataHelper = [[AMIMCoreDataHelper alloc] init];
    _fetchedResultsController = [[[AMIMCoreDataHelper getInstance] getMsgFetchControllerWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] friendId:mFriendUid] retain];
    
    [_msgTable reloadData];
    [self scrollToBottom];
}


- (void) recvNewMsg {
    [self performSelectorOnMainThread:@selector(refreshMsgTable) withObject:nil waitUntilDone:NO ];
}

- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    [_msgTable reloadData];
    [self scrollToBottom];
}

- (IBAction)faceBtnAction:(id)sender {
    if(!faceKeyboardOpen){
        faceKeyboardOpen = YES;
        [_faceBtn setImage:[UIImage imageNamed:@"icon_toast_face_p"] forState:UIControlStateNormal];
        [_faceKeyboardView showKeyBoard:_inputField]; 
    }else{
        faceKeyboardOpen = NO;
        [_faceBtn setImage:[UIImage imageNamed:@"icon_toast_face"] forState:UIControlStateNormal];
        [_faceKeyboardView reKeyBoard];
    }
}

- (void) onReturnKeyboardInput:(NSString *)_str {
    [AMLogUtils appendLog:APP_WANGWANG_SYSMSG_TWO];
    
	NSString *str = [NSString stringWithFormat:@"%@%@",_inputField.text,_str];
	_inputField.text = str;
   
    faceKeyboardOpen = NO;
     [_faceBtn setImage:[UIImage imageNamed:@"icon_toast_face"] forState:UIControlStateNormal];
	[_faceKeyboardView reKeyBoard];
	
}

- (IBAction)quickWordsBtnAction:(id)sender {
    if(!quickWordBoardOpen) {
        quickWordBoardOpen = YES;
        [_quickWordsBtn setImage:[UIImage imageNamed:@"icon_aliww_kj-271"] forState:UIControlStateNormal];
        [self faceBtnAction:nil];
        [_quickWordsBoard showQuickWordBoard];
    } else {
        quickWordBoardOpen = NO;
        [self faceBtnAction:nil];
        [_quickWordsBtn setImage:[UIImage imageNamed:@"icon_aliww_kj"] forState:UIControlStateNormal];
        [_quickWordsBoard hideQuickWordBoard];
    }
}

- (IBAction)msgTableClick {
    [self performSelectorOnMainThread:@selector(hideKeyboardAndFace) withObject:nil waitUntilDone:NO ];
}

- (void) sendMessage:(NSString *) msgStr {
    
    [AMLogUtils appendLog:APP_WANGWANG_TALKING_TWO];
    
    NSString *str=nil;
    NSString* strHead=@"\\C0\\S0xa.0xc8\\F宋体\\T";
    
    str= [msgStr stringByReplacingOccurrencesOfString:@"\\" withString:@"\\\\"];
    str = [self returnSendMessageString:str];
    str=[strHead stringByAppendingString:str];
    
    CallBackTool *tool = [CallBackTool create];
    [self refreshUser];
    if(mFriendUid == nil) {
        return ;
    }
    [tool sendMessage:str uid:mFriendUid];
    
    NSNumber * time = [NSNumber numberWithInt:[[NSDate date] timeIntervalSince1970]];
    
    if (![str isEqualToString:@"\\T"] ) {
        str = [str stringByReplacingOccurrencesOfString:@"\\\\" withString:@"\\"];   
    }
    str=[str substringFromIndex:[strHead length]];
    
    NSString * uid = [AMIMDefaultStorageHelper getLastLoginedUserId];
    [[AMIMCoreDataHelper getInstance] insertNewMsgWithOwnerId:uid msgFrom:uid msgTo:mFriendUid msgType:[NSNumber numberWithInt:TEXT_MSG_NORMAL_TEXT] msgContent:str hasRead:[NSNumber numberWithBool:YES] msgTime:time msgSequence:[NSNumber numberWithInt:-1]];
    
    [[AMIMCoreDataHelper getInstance] modifyContactTimeWithOwner:uid friendId:mFriendUid msgTime:time];
    [[AMIMCoreDataHelper getInstance] saveData];
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_COUNTMSG object:nil];
    [self performSelectorOnMainThread:@selector(refreshMsgTable) withObject:nil waitUntilDone:NO ];
}

- (NSString *) returnSendMessageString:(NSString *)_string {
	
	NSArray *rAry = [NSArray arrayWithArray:[InternetDataTool create].facesCharArray];
	NSString *replaceStr;
	NSString *imageStr;
	NSString *returnStr = _string;
    
    //by tom.lih 可以尝试进一步优化
	for (int i = 0; i < [rAry count]; i++) {
		
		TextViewExItem *dicItem = [rAry objectAtIndex:i];
		imageStr = dicItem.imagePath;
  
        replaceStr = [NSString stringWithFormat:@"%@%@%@",BREAKSTRING,imageStr,BREAKSTRING];
		returnStr = [returnStr stringByReplacingOccurrencesOfString:imageStr withString:replaceStr];	
	}
    
    returnStr = [returnStr stringByReplacingOccurrencesOfString:@"\\T\\T\/\:" withString:@"\\T\/\:"];
    
	//将\T\T/:O\T=O\T变回\T/:O=O\T
	imageStr = [NSString stringWithFormat:@"%@%@/:O%@=O%@",BREAKSTRING,BREAKSTRING,BREAKSTRING,BREAKSTRING];
	replaceStr = [NSString stringWithFormat:@"%@/:O=O%@",BREAKSTRING,BREAKSTRING];
	returnStr = [returnStr stringByReplacingOccurrencesOfString:imageStr withString:replaceStr];
    
    
    BOOL bTemp;
	bTemp=[returnStr hasSuffix:@"\\T"];
	if (bTemp && ([returnStr length] > 3)) {
        returnStr=[returnStr substringToIndex:[returnStr length]-2];
    }
    
	return returnStr;
}

- (void) refreshUser {
    if (mFriendUid == nil) {
        return ;
    }
    
    //_user = [[AMIMCoreDataHelper getInstance] getFriendWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] uid:mFriendUid];
}

- (void) navigationButtonClick {
    [self refreshUser];
    
    if(mFriendUid != nil) {
        AMIMUserDetailViewController * userDetailViewController = [[[AMIMUserDetailViewController alloc] initWithUser:mFriendUid relation:USER_RELATION_FRIEND] autorelease];
        
        [userDetailViewController setHidesBottomBarWhenPushed:YES];
        [self.navigationController pushViewController:userDetailViewController animated:YES];
    }
}

- (void) navigationBack
{
    [self msgTableClick];
    [super navigationBack];
}

//没有被调用?
- (void) viewWillDisappear:(BOOL)animated {
    [self msgTableClick];
}

-(void) keyboardWillShow:(NSNotification *)note {
    CGRect keyboardBounds;
    [[note.userInfo valueForKey:UIKeyboardBoundsUserInfoKey] getValue: &keyboardBounds];
    
//    _msgTable.frame = CGRectMake(0, 0, 320, 372);
//    _inputView.frame = CGRectMake(0, 372, 320, 44);
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationBeginsFromCurrentState:YES];
    [UIView setAnimationDuration:0.2f];

    int keyBoardHeightChange = keyboardBounds.size.height - (416 - _inputView.frame.origin.y - _inputView.frame.size.height);
    
    _msgTable.frame = CGRectMake(_msgTable.frame.origin.x, _msgTable.frame.origin.y, _msgTable.frame.size.width, _msgTable.frame.size.height-keyBoardHeightChange);
    _inputView.frame = CGRectMake(_inputView.frame.origin.x, _inputView.frame.origin.y-keyBoardHeightChange, _inputView.frame.size.width, _inputView.frame.size.height);

    [UIView commitAnimations];
    [self scrollToBottom];
}

- (void) hideKeyboard {
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationBeginsFromCurrentState:YES];
    [UIView setAnimationDuration:0.2f];
    
    [_faceKeyboardView hideKeyBoard];
    faceKeyboardOpen = NO;
     [_faceBtn setImage:[UIImage imageNamed:@"icon_toast_face"] forState:UIControlStateNormal];
    _msgTable.frame = CGRectMake(0, 0, 320, 372);
    _inputView.frame = CGRectMake(0, 372, 320, 44);
    
    [UIView commitAnimations];
    
    [self scrollToBottom];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    NSString * msg = _inputField.text;
    //NSLog(@"Msg: %@", _inputField.text);
    
    if (msg.length > MAX_MSG_LENGTH) {
       [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"消息长度不能超过1000个字符"] show]; 
    }else {
        _inputField.text = @"";
        [_inputField becomeFirstResponder];
        
        if(msg != nil && ![[msg stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] isEqualToString:@""]){
            //[[[[NSThread alloc] initWithTarget:self selector:@selector(sendMessage:) object:msg] autorelease] start];
            [self performSelectorInBackground:@selector(sendMessage:) withObject:msg];
        }
    }
    
    return YES;
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

- (void) scrollToBottom {
    if(_fetchedResultsController && [[_fetchedResultsController sections] count] > 0
       && [[[_fetchedResultsController sections] objectAtIndex:0] numberOfObjects]>0){
        NSIndexPath *lastRow = [NSIndexPath indexPathForRow:[[[_fetchedResultsController sections] objectAtIndex:0] numberOfObjects]-1 inSection:0];
        [_msgTable scrollToRowAtIndexPath:lastRow atScrollPosition:UITableViewScrollPositionBottom animated:YES];
    }
}

#pragma table
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    //NSInteger row = [indexPath row];
    if(_fetchedResultsController != nil && [[_fetchedResultsController sections] count]>0){
        AMIMMessageModel * msg = (AMIMMessageModel *)[_fetchedResultsController objectAtIndexPath:indexPath];
        
        AMIMMsgLabel * label =[[[AMIMMsgLabel alloc] init] autorelease];
        // rocky.wen: 这个地方算了一次label高度，别的地方也算了一次，有优化空间
        int viewHeight = [label setContentStr:msg.msgContent].height + 52;
        viewHeight = (viewHeight > 72?viewHeight:72);
        return viewHeight;
    }
    return 72;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    return nil;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{ 
    if(_fetchedResultsController != nil){
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
   
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}



- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    //NSInteger row = [indexPath row];
    if(_fetchedResultsController != nil && [[_fetchedResultsController sections] count]>0){
        AMIMMessageModel * msg = (AMIMMessageModel *)[_fetchedResultsController objectAtIndexPath:indexPath];
        if(!msg.hasRead.boolValue){
            [[AMIMCoreDataHelper getInstance] changeMsgReadStateWithMsgObj:msg];
           [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_HAS_READ object:nil];
        }
        
        
        
        NSString *uid = [AMIMDefaultStorageHelper getLastLoginedUserId];
        if([msg.msgFrom isEqualToString:uid]){
            AMIMMsgToCell * cell = nil;
            if (cell == nil)  
            {
                NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMMsgToCell" 
                                                             owner:self options:nil];
                for (id oneObject in nib)
                    if ([oneObject isKindOfClass:[AMIMMsgToCell class]])
                        cell = (AMIMMsgToCell *)oneObject;
                
                cell.headImg.layer.borderColor  = [UIColor whiteColor].CGColor;
                cell.headImg.layer.borderWidth = 2.0f;
                
                [cell.textLabel setAdjustsFontSizeToFitWidth:NO];
            }
            
            cell.headImg.url = [StringUtils getWwHeadImageWithUid:uid];
            [_objMan manage:cell.headImg];
            [cell setText:msg.msgContent];
            cell.timeLabel.text = [StringUtils getDateStrLong: msg.msgTime.doubleValue];
            
            return cell;
        }else {
            AMIMMsgCell * cell = nil;
            if (cell == nil)  
            {
                NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIMMsgCell" 
                                                             owner:self options:nil];
                for (id oneObject in nib)
                    if ([oneObject isKindOfClass:[AMIMMsgCell class]])
                        cell = (AMIMMsgCell *)oneObject;
                
                cell.headImg.layer.borderColor  = [UIColor whiteColor].CGColor;
                cell.headImg.layer.borderWidth = 2.0f;
                
                [cell.textLabel setAdjustsFontSizeToFitWidth:NO];
            }
            
            cell.headImg.url = [StringUtils getWwHeadImageWithUid:msg.msgFrom];
            [_objMan manage:cell.headImg];
            [cell setText: msg.msgContent];
            cell.timeLabel.text = [StringUtils getDateStrLong: msg.msgTime.doubleValue];

            
            return cell;
        }

    }
        
    return nil;
}

- (NSString *) returnRevMessageString:(NSString *)_string {
	NSArray *rAry = [NSArray arrayWithArray:[InternetDataTool create].facesCharArray];
	NSString *replaceStr;
	NSString *returnStr = _string;
	
	for (int i = 0; i < [rAry count]; i++) {
		
		TextViewExItem *dicItem = [rAry objectAtIndex:i];
		NSString *imageStr = dicItem.imagePath;
		
		replaceStr = [NSString stringWithFormat:@"%@%@%@",BREAKSTRING,imageStr,BREAKSTRING ];
		returnStr = [returnStr stringByReplacingOccurrencesOfString:imageStr withString:replaceStr];
		
	}
	
	return returnStr;
}

- (void) hideKeyboardAndFace {
    [_faceBtn resignFirstResponder];
    [_inputField resignFirstResponder];
    [self hideKeyboard];
}

- (void) quitWangWang {
    [self performSelectorOnMainThread:@selector(hideKeyboardAndFace) withObject:nil waitUntilDone:NO ];
    
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



@end

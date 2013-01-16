//
//  AMMoreViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "AMMoreViewController.h"
#import "AMSimpleCell.h"
#import "UIHelp.h"
#import "LoginToken.h"
#import "AMIMViewController.h"
#import "AMAbout.h"
#import "AMFeedback.h"
#import "AMCopyRight.h"
#import "LogoutRequest.h"
#import "ConstDef.h"
#import "AliToastView.h"
#import "AMAppDelegate.h"
#import "LoginToken.h"
#import "InternetDataTool.h"
#import "CallBackTool.h"
#import "SystemUtils.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AMBannerContentDetailViewController.h"

#define DEFAULT_MORE_BACKGROUND_CORLOR      @"0xf0f0f0"

@interface AMMoreViewController() 
@property (retain,nonatomic)AMSimpleCell *aboutCell;
@property (retain,nonatomic)AMSimpleCell *feedbackCell;
@property (retain,nonatomic)AMSimpleCell *copyRightCell;
@property (retain,nonatomic)AMSimpleCell *accountCell;
@property (retain,nonatomic)AMSimpleCell *appraiseCell;
@property (retain,nonatomic)AMSimpleCell *appSuggestCell;
@property (retain,nonatomic)LogoutRequest *logoutRequset;
@property (retain,nonatomic)AliNavigationBackButton *button;
@end

@implementation AMMoreViewController
@synthesize aboutCell=_aboutCell;
@synthesize feedbackCell=_feedbackCell;
@synthesize copyRightCell=_copyRightCell;
@synthesize accountCell=_accountCell;
@synthesize appraiseCell=_appraiseCell;
@synthesize topTableView=_topTableView;
@synthesize middleTableView=_middleTableView;
@synthesize logoutButton=_logoutButton; 
@synthesize logoutRequset=_logoutRequset; 
@synthesize button=_button;
@synthesize appSuggestCell = _appSuggestCell;

-(AliNavigationBackButton*)button {
    if (!_button) {
         _button = [[AliNavigationBackButton alloc] initWithTitle:@"返回"];
        _button.navigationBackDelegate = self;
    }
    return _button;
}

-(AMSimpleCell*)aboutCell
{
    if (_aboutCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMSimpleCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMSimpleCell class]])
                _aboutCell = (AMSimpleCell *)oneObject;
        
    }
    return _aboutCell;
}

-(AMSimpleCell*)feedbackCell
{
    if (_feedbackCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMSimpleCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMSimpleCell class]])
                _feedbackCell = (AMSimpleCell *)oneObject;
        
    }
    return _feedbackCell;
}

-(AMSimpleCell*)copyRightCell
{
    if (_copyRightCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMSimpleCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMSimpleCell class]])
                _copyRightCell = (AMSimpleCell *)oneObject;
        
    }
    return _copyRightCell;
}

-(AMSimpleCell*)accountCell
{
    if (_accountCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMSimpleCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMSimpleCell class]])
                _accountCell = (AMSimpleCell *)oneObject;
        
    }
    return _accountCell;
}

-(AMSimpleCell*)appraiseCell
{
    if (_appraiseCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMSimpleCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib) {
            if ([oneObject isKindOfClass:[AMSimpleCell class]]){
                _appraiseCell = (AMSimpleCell *)oneObject;
            }
        }
    }
    return _appraiseCell;
}

-(AMSimpleCell *)appSuggestCell {
    if (_appSuggestCell == nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMSimpleCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib) {
            if ([oneObject isKindOfClass:[AMSimpleCell class]]){
                _appSuggestCell = (AMSimpleCell *)oneObject;
            }
        }
    }
    
    return _appSuggestCell;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.navigationItem.title = NSLocalizedString(@"More", @"");
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_more"];
        self.tabBarItem.title=NSLocalizedString(@"More", @"");
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onLoginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    }
    
    return self;
}

- (void)dealloc {    
    [_aboutCell release];
    [_feedbackCell release];
    [_accountCell release];
    [_copyRightCell release];   
    [_appraiseCell release];
    [_appSuggestCell release];
    [_topTableView release];
    [_middleTableView release];
    self.logoutButton = nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}
- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    //  [self.navigationController setNavigationBarHidden:YES];
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.topTableView.backgroundColor=[UIColor clearColor];
    self.topTableView.backgroundView.backgroundColor=[UIHelp colorWithHexString : DEFAULT_MORE_BACKGROUND_CORLOR];
    self.middleTableView.backgroundColor=[UIColor clearColor];
    self.middleTableView.backgroundView.backgroundColor=[UIHelp colorWithHexString : DEFAULT_MORE_BACKGROUND_CORLOR];    
    self.view.backgroundColor=[UIHelp colorWithHexString : DEFAULT_MORE_BACKGROUND_CORLOR];

    UIImage * imgMsgNormal = [UIImage imageNamed:@"btn_ct_orange"];
    imgMsgNormal = [imgMsgNormal stretchableImageWithLeftCapWidth:imgMsgNormal.size.width/4 topCapHeight:imgMsgNormal.size.height/4];
    [self.logoutButton setBackgroundImage:imgMsgNormal forState:UIControlStateNormal];
    
    UIImage * imgMsgPressed = [UIImage imageNamed:@"btn_ct_orange_tap"];
    imgMsgPressed = [imgMsgPressed stretchableImageWithLeftCapWidth:imgMsgPressed.size.width/4 topCapHeight:imgMsgPressed.size.height/4];
    [self.logoutButton setBackgroundImage:imgMsgPressed forState:UIControlStateHighlighted];
    
    self.navigationItem.leftBarButtonItem = self.button;
}

- (void)viewDidUnload {

#warning 修改人 孟希羲   
    /*
    AM_RELEASE_SAFELY(_aboutCell);
    AM_RELEASE_SAFELY(_feedbackCell);
    AM_RELEASE_SAFELY(_accountCell);
    AM_RELEASE_SAFELY(_copyRightCell);
    AM_RELEASE_SAFELY(_logoutButton);
    AM_RELEASE_SAFELY(_topTableView);
    AM_RELEASE_SAFELY(_middleTableView); 
     */
    _accountCell = nil;
    _feedbackCell = nil;
    _aboutCell = nil;
    _copyRightCell = nil;
    self.middleTableView = nil;
    self.topTableView = nil;
    _appraiseCell = nil;
    _appSuggestCell = nil;
    self.logoutRequset = nil;
    [_button release];
    _button = nil;

    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [_middleTableView reloadData];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {


    if (tableView == _topTableView) {
        if (0 == indexPath.row) {
            AMSimpleCell *cell = (AMSimpleCell *)[tableView 
                            dequeueReusableCellWithIdentifier: [AMSimpleCell cellIdentifer]];
            if (cell==nil) {
                cell = self.aboutCell;
            }
            cell.leftLabel.text=@"关于";
            
            NSString *shortVersion = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
            cell.rightLabel.text = [NSString stringWithFormat:@"%@ 版本", shortVersion];   
            return cell;
			
		}else if (1 == indexPath.row){
            AMSimpleCell *cell = (AMSimpleCell *)[tableView 
                            dequeueReusableCellWithIdentifier: [AMSimpleCell cellIdentifer]];
            if (cell==nil) {
                cell = self.feedbackCell;
            }
            cell.leftLabel.text=@"意见反馈";
            cell.rightLabel.text=@"";
            return cell;
        }else if (2 == indexPath.row){
            AMSimpleCell *cell = (AMSimpleCell *)[tableView 
                              dequeueReusableCellWithIdentifier: [AMSimpleCell cellIdentifer]];
            if (cell==nil) {
                cell = self.copyRightCell;
            }
            cell.leftLabel.text=@"版权信息";
            cell.rightLabel.text=@"";
            return cell;
        }else if (3 == indexPath.row){
            AMSimpleCell *cell = (AMSimpleCell *)[tableView 
                                                  dequeueReusableCellWithIdentifier: [AMSimpleCell cellIdentifer]];
            if (cell==nil) {
                cell = self.appraiseCell;
            }
            cell.leftLabel.frame = CGRectMake(15, 10, 240, 21);
            cell.leftLabel.text=@"喜欢请打分鼓励一下";
            cell.middleLabel.hidden = YES;
            cell.rightLabel.hidden = YES;
            return cell;
        }else if (4 == indexPath.row){
            AMSimpleCell *cell = (AMSimpleCell *)[tableView 
                                                  dequeueReusableCellWithIdentifier: [AMSimpleCell cellIdentifer]];
            if (cell==nil) {
                cell = self.appSuggestCell;
            }
            cell.leftLabel.frame = CGRectMake(15, 10, 240, 21);
            cell.leftLabel.text=@"精品应用推荐";
            cell.middleLabel.hidden = YES;
            cell.rightLabel.hidden = YES;
            return cell;
        }
        
	}
    
    if (tableView == _middleTableView) {
       
        if (0 == indexPath.row) {
            AMSimpleCell *cell = (AMSimpleCell *)[tableView 
                                                  dequeueReusableCellWithIdentifier: [AMSimpleCell cellIdentifer]];
            if (cell==nil) {
                cell = self.accountCell;
            }
           /*
            //cell.selectionStyle =UITableViewCellSelectionStyleBlue;       
            UIView *selectedView = [[UIView alloc] initWithFrame:cell.contentView.frame];
            selectedView.layer.cornerRadius=10.0;
            selectedView.backgroundColor = [UIHelp colorWithHexString : @"0xfdfdd9"];
            cell.selectedBackgroundView = selectedView;
            [selectedView release];
            */

            cell.leftLabel.text=@"切换用户";
            NSString *loginUserName=nil;
            loginUserName=[LoginToken getLoginUserName];
            if([loginUserName length] > 3) {
                
                cell.rightLabel.text=loginUserName;  
                _logoutButton.hidden=NO;
            }else{
                cell.leftLabel.text=@"用户登录";
                cell.rightLabel.text=@""; 
                _logoutButton.hidden=YES;
            }
            return cell;
        }
	}   
    
    return nil;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
	if (tableView == _topTableView) {
		return 5;
	}
    if (tableView == _middleTableView) {   
        return 1;
	}
    
    return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AMSimpleCell cellHeight];
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{

    if (tableView == _topTableView) {
        if (0 == indexPath.row) {
            [AMLogUtils appendLog:APP_MENU_THREE];
            
            AMAbout *controller = (AMAbout *)[[AMAbout alloc]
                                    initWithNibName:@"AMAbout" bundle:nil];
            controller.hidesBottomBarWhenPushed=YES;
            [self.navigationController pushViewController:controller animated:YES]; 
#warning 修改人孟希羲
            [controller release];
           			
		}else if (1 == indexPath.row) {
            [AMLogUtils appendLog:APP_MENU_FOUR];
            AMFeedback *controller = (AMFeedback *)[[AMFeedback alloc]
                                                    initWithNibName:@"AMFeedback" bundle:nil];
            controller.hidesBottomBarWhenPushed=YES;
            [self.navigationController pushViewController:controller animated:YES]; 
            [controller release];
        }else if (2 == indexPath.row) {
            [AMLogUtils appendLog:PAGE_TWENTY_THREE];
            AMCopyRight *controller = (AMCopyRight *)[[AMCopyRight alloc]
                                initWithNibName:@"AMCopyRight" bundle:nil] ;
            controller.hidesBottomBarWhenPushed=YES;
            [self.navigationController pushViewController:controller animated:YES]; 
            
            [controller release];
        }
        else if (3 == indexPath.row) {
            [AMLogUtils appendLog:APP_MENU_SEVEN];
            //邀请用户进行评论
            NSString *urlValue = @"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=507097717";
            [SystemUtils openBrowserWithUrl:urlValue];
            
        }
        else if (4 == indexPath.row) {
//            [AMLogUtils appendLog:APP_MENU_SEVEN];
            //邀请用户进行评论
            
            AMBannerContentDetailViewController *controller = (AMBannerContentDetailViewController *)[[[AMBannerContentDetailViewController alloc] init] autorelease];
            controller.url = @"http://m.1688.com/touch/appsug/iosAppSug";
            controller.hidesBottomBarWhenPushed=YES;
            controller.navigationTitle = @"精品应用推荐";
            [self.navigationController pushViewController:controller animated:YES]; 
            
        }
        [self.topTableView deselectRowAtIndexPath:indexPath animated:NO]; 
        
	}
    if (tableView == _middleTableView) {
        /*
        NSString *loginUserName=nil;
        loginUserName=[LoginToken getLoginUserName];
        if([loginUserName length] > 3){  
            
            UIViewController *nextController;
            nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
            nextController.hidesBottomBarWhenPushed=YES;   
            [self.navigationController pushViewController:nextController animated:YES];    
            
        }else{
            //[AliToast showWithText:@"您还未登录！" duration:1]; 
            //[_middleTableView reloadData]; 
        }   
        */
        if (_logoutButton.enabled==true) {
            [AMLogUtils appendLog:APP_MENU_FIVE];
            UIViewController *nextController;
            nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
            nextController.hidesBottomBarWhenPushed=YES;   
            [self.navigationController pushViewController:nextController animated:YES]; 
            [nextController release];
        }
        
        [self.middleTableView deselectRowAtIndexPath:indexPath animated:NO]; 
	}
 
}


#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"Loaded objects: %@", objects);    
    [LoginToken setLoginParameter :0 :@"" :@"" :@"" :@"" :@""]; 
    if (_logoutButton.enabled==false) {
        _logoutButton.enabled=true;
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"注销成功"] show];
    }
    
    [_middleTableView reloadData];
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
	NSLog(@"Hit error: %@", error);    

    if (_logoutButton.enabled==false) {
        _logoutButton.enabled=true;
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"注销失败"] show];
    }
}

- (void)logOutCNA {
    if ([LoginToken isAppLogined]) {
        //检查accesstoken是否过期
        [LoginToken checkAccessTokenExpired];
    
        // Load the object model via RestKit	
        RKObjectManager* objectManager = [RKObjectManager sharedManager];
        objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
        [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_LOGOUT usingBlock:^(RKObjectLoader* loader) {
            // Change Method to POST
            loader.delegate = self;
            loader.method = RKRequestMethodPOST;
            loader.params = self.logoutRequset;
        }];
    }
}

inline void sig_do_nothing(int signo)
{
	return ;
}

- (void)logOutWW
{
    if([LoginToken isWangWangLogined]){
        //by tom.lih
        [LoginToken setWangWangLogined:NO];
        
        [[InternetDataTool create].operationQueue cancelAllOperations];
        CallBackTool *tool = [CallBackTool create];
        
        [tool logOff];
        
        sigset_t newmask;
        sigset_t oldmask;
        signal(SIGPIPE, sig_do_nothing);
        sigemptyset(&newmask);
        sigaddset(&newmask, SIGPIPE);
        sigprocmask(SIG_BLOCK, &newmask, &oldmask);

        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_QUITWANGWANG object:nil];
    }
    
    
}

- (void)userlogOut
{   
    [self logOutWW];
    [self logOutCNA];
}

- (IBAction) logoutButtonOnClick:(id)sender {

    if (nil == self.logoutRequset) {
        self.logoutRequset = [[LogoutRequest alloc] init]; 
    }
    self.logoutRequset.requestURL=OCEAN_API_URL_LOGOUT;
    self.logoutRequset.accessToken=[LoginToken getAccessToken]; 
    UIDevice * device = [UIDevice currentDevice];
    self.logoutRequset.appId = AMCONST_APP_ID;
    self.logoutRequset.terminalId=device.uniqueIdentifier;
    
    NSString *loginUserName=[LoginToken getLoginUserName];
    if (loginUserName && loginUserName.length>0) {
        _logoutButton.enabled=false;
        [self performSelectorInBackground:@selector(userlogOut) withObject:nil];

    }
}

- (void) onLoginSucc {
    [_middleTableView reloadData]; 
}

@end

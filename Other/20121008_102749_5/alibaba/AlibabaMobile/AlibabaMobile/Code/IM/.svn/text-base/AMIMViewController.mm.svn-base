//
//  AMIMViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "AMIMViewController.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import "LoginToken.h"
#import "LoginResult.h"
#import "LoginRequest.h"
#import "UIHelp.h"
#import "AliNavigationButton.h"
#import "AliNavigationBackButton.h"
#import "AMDeviceRegistRequest.h"
#import "AMAppDelegate.h"
#import "UIHelp.h"
#import "CallBackTool.h"
#import "NoticationItem.h"
#import "AMIMUserDefault.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMCoreDataHelper.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AESCrypto.h"
#import "AMRegisterViewController.h"

#define PHONENUM_REGEX  @"\\b(1)[358][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]\\b"//手机号正则表达式
#define EMAIL_REGEX     @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}" //旺旺正则表达式

@implementation AMIMViewController

@synthesize _loginRequset;
@synthesize navigationBackButton;
@synthesize _object;
@synthesize mLoadingView = _mLoadingView;
@synthesize loginWangwang = _loginWangwang;
@synthesize enterWangwang = _enterWangwang;
@synthesize logoutRequset = _logoutRequset;

-(LogoutRequest*)logoutRequset
{
    if (!_logoutRequset) {
        _logoutRequset = [[LogoutRequest alloc] init]; 
        _logoutRequset.requestURL=OCEAN_API_URL_LOGOUT;
    }
    
    _logoutRequset.accessToken=[LoginToken getAccessToken]; 
    UIDevice * device = [UIDevice currentDevice];
    _logoutRequset.appId=AMCONST_APP_ID;
    _logoutRequset.terminalId=device.uniqueIdentifier;
    return _logoutRequset;
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    return _mLoadingView;
}

- (void) showLoadingView
{
    [self.mLoadingView setHidden:NO];
}

-(void) endLoadingView
{
    [self.mLoadingView setHidden:YES];
}

- (void) saveAccount {
    NSString * username = _object.mResourceOwnerId;
    NSString * passwd = nil;
    BOOL autoLogin = [rememberPwdButton isOn];
    
    NSString * uid = [NSString stringWithFormat:@"%@%@", ACCOUNT_SITE, username];
    AMIMUserDefault *user = [AMIMDefaultStorageHelper getLoginedUser:uid];
    if(user == nil){
        user = [[AMIMUserDefault alloc] init];
    }else{
        [user retain];
    }
    
    if ([pwdTextField.text length] == 16) {
        user.isSpecialPassWord = YES;
        passwd = [NSString stringWithFormat:@"%@i",pwdTextField.text];
    } else {
        user.isSpecialPassWord = NO;
        passwd = pwdTextField.text;
    }
    
    NSData * password;
    AESCrypto * crypto = [[AESCrypto alloc] init];
//    if(autoLogin){
//        password = [crypto encryptText:passwd];
//    }else{
//        password = [crypto encryptText:@""]; 
//    }
    password = [crypto encryptText:passwd];
    
    user.uid = uid;
    user.passwd = password;
    user.autoLogin = autoLogin;
    
    [AMIMDefaultStorageHelper addLoginedUser:user];
    [AMIMDefaultStorageHelper changeLastLoginedUser:uid];
    [user release];
    
    [[AMIMCoreDataHelper getInstance] addOwnerWithUid:uid paswd:@"" autoLogin:autoLogin];
    [[AMIMCoreDataHelper getInstance] addUsesrWithUid:uid nickname:[uid substringFromIndex:8] groupId:[NSNumber numberWithInt:-2].stringValue ownerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
}

//by lih
- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL4OAUTH];
    
    /*!
     Map to a target object class -- just as you would for a non-persistent class. The entity is resolved
     for you using the Active Record pattern where the class name corresponds to the entity name within Core Data.
     */
    RKObjectMapping* loginMapping = [RKObjectMapping mappingForClass:[LoginResult class]];
    
    [loginMapping mapKeyPath:@"accessToken" toAttribute:@"mAccessToken"]; 
    [loginMapping mapKeyPath:@"refreshToken" toAttribute:@"mRefreshToken"];
    [loginMapping mapKeyPath:@"accessTokenTimeout" toAttribute:@"mAccessTokenTimeout"];
    [loginMapping mapKeyPath:@"refreshTokenTimeout" toAttribute:@"mRefreshTokenTimeout"];
    [loginMapping mapKeyPath:@"resourceOwnerId" toAttribute:@"mResourceOwnerId"]; 
    [loginMapping mapKeyPath:@"uid" toAttribute:@"mUid"];

    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: loginMapping];
    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_LOGIN usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[LoginResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self._loginRequset;
    }];
}

- (void)registDeviceToRemote {
    AMDeviceRegistRequest * registRequest = [[AMDeviceRegistRequest alloc] init];
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    registRequest.terminateId = appDelegate.terminateId;
    registRequest.model = appDelegate.model;
    registRequest.system  = appDelegate.system;
    registRequest.version  = appDelegate.version;
    registRequest.deviceTokenStr  = appDelegate.deviceTokenStr;
    registRequest.appId  = AMCONST_APP_ID;
    registRequest.appVersion = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    NSLog(@"device token: %@", appDelegate.deviceTokenStr);
//lih
    registRequest.currentUserId  = nameTextField.text;
//    registRequest.currentUserId  = [LoginToken getLoginUserName];
    registRequest.transactionType = AMTRANSACTION_TYPE_DEVICE_REGIST;
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_DEVICE_REGIST usingBlock:^(RKObjectLoader* loader) {
        loader.delegate = self;    
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = registRequest;
    }];
    
    [registRequest release];
}   

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload:%@" ,[response bodyAsString]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    if (isLogoutRequest) {
        isLogoutRequest=false;
        [self performSelectorOnMainThread:@selector(startLogin) withObject:nil waitUntilDone:YES];
        return;
    }
    
    [self endLoadingView];
    NSLog(@"Loaded objects: %@", objects);    
	//[_object release];
    
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = (NSInteger)[(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if (transactionType == AMTRANSACTION_TYPE_DEVICE_REGIST){
            return;
        }
    }else{
        //log中提示有crash 因此增加边界条件
        if([objects count]==0){
            return;
        }
        self._object = [objects objectAtIndex:0];
        [self performSelectorOnMainThread:@selector(refreshUI:) withObject:nil waitUntilDone:YES];		
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    if (isLogoutRequest) {
        isLogoutRequest = false;
        [self performSelectorOnMainThread:@selector(startLogin) withObject:nil waitUntilDone:YES];
        return;
    } 

    [self endLoadingView];
    
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        UIAlertView *alert = [[UIAlertView alloc]
                              initWithTitle:NSLocalizedString(@"网络不可用，请检查网络设置是否正确！", nil)
                              message: nil
                              delegate:self 
                              cancelButtonTitle:NSLocalizedString(@"确定", nil) 
                              otherButtonTitles:nil];
        [alert show];
        [alert release];
    } else {
        UIAlertView *alert = [[UIAlertView alloc]
                              initWithTitle:NSLocalizedString(@"帐户名或者密码错误.", nil)
                              message: nil
                              delegate:self 
                              cancelButtonTitle:NSLocalizedString(@"确定", nil) 
                              otherButtonTitles:nil];
        [alert show];
        [alert release];
    }

    self.navigationItem.rightBarButtonItem.enabled=true;
    self.navigationItem.leftBarButtonItem.enabled=true;
}

- (void) refreshUI:(NSMutableDictionary *)_sender {
	[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(timeOut) object:nil];
   
    [self saveAccount];

    [LoginToken setLoginParameter :rememberPwdButton.isOn :_object.mResourceOwnerId :self._object.mAccessToken :self._object.mAccessTokenTimeout :self._object.mRefreshToken :self._object.mRefreshTokenTimeout]; 
    
    
    [self registDeviceToRemote];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICAGION_LOGIN_SUCC object:self];
    if(self.loginWangwang){
        if (self.enterWangwang) {
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ENTER_WW object:self];
        }else {
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:self];            
        }
    }

    if ([self.navigationController.viewControllers count]>1) {
        [self.navigationController popViewControllerAnimated:YES];
    }
    
    self.navigationItem.rightBarButtonItem.enabled=true;
    self.navigationItem.leftBarButtonItem.enabled=true;
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
        [LoginToken setWangWangLogined:NO];
        [[InternetDataTool create].operationQueue cancelAllOperations];
        CallBackTool *tool = [CallBackTool create];
        //by tom.lih
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

- (void)currentUserlogOut
{  
    [self logOutWW];
    [self logOutCNA];
}

- (void) loginButtonClick {
	/*
     NetworkStatus st = [[Reachability sharedReachability] internetConnectionStatus];
     BOOL isOnline = (st == NotReachable)?NO : YES;
     if (isOnline == YES) {
     */
    self.navigationItem.rightBarButtonItem.enabled=false;
    self.navigationItem.leftBarButtonItem.enabled=false;
    
    isLogoutRequest=false;
    nameTextField.text = [nameTextField.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
    pwdTextField.text = [pwdTextField.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
    
    NSString *loginedUserName=nil;
    loginedUserName=[LoginToken getLoginUserName];
    if ([loginedUserName isEqualToString:nameTextField.text] ) {
        
        if ([self.navigationController.viewControllers count]>1) {
            [self.navigationController popViewControllerAnimated:YES];
        }

        self.navigationItem.rightBarButtonItem.enabled=true;
        self.navigationItem.leftBarButtonItem.enabled=true;
        return;
    }
    [self showLoadingView];
    if(loginedUserName && loginedUserName.length > 3){
        isLogoutRequest=true;
        [self performSelectorInBackground:@selector(currentUserlogOut) withObject:nil];
    }else {
        [self startLogin];
    }
}

- (void) startLogin {
    
    if ([nameTextField.text length] > 0 && [pwdTextField.text length] > 0) {

        //by tom.lih
        self._loginRequset.account =nameTextField.text;
        self._loginRequset.password =pwdTextField.text;
        NSString * loginIdType = [self getLoginNameType:self._loginRequset.account];
        if(![loginIdType isEqualToString: LOGIN_ID]){
            self._loginRequset.loginIdType = loginIdType;
        }
        
        if (rememberPwdButton.isOn) {
            self._loginRequset.needRefreshToken =@"true";
        }else {
            self._loginRequset.needRefreshToken =@"false";
        }
        
        [self loadObjectsFromRemote];
        
        if ([nameTextField isFirstResponder] || [pwdTextField isFirstResponder]) {
            [nameTextField resignFirstResponder];
            [pwdTextField resignFirstResponder];
            
        }
        
    } else {
        if ([nameTextField.text length] == 0) {
            [self endLoadingView];
            UIAlertView *alert = [[UIAlertView alloc] 
                                  initWithTitle:NSLocalizedString(@"用户名不能为空!", nil)
                                  message: nil
                                  delegate:self 
                                  cancelButtonTitle:NSLocalizedString(@"确定", nil) 
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
            [nameTextField becomeFirstResponder];
        } else if ([pwdTextField.text length] == 0) {
            [self endLoadingView];
            UIAlertView *alert = [[UIAlertView alloc] 
                                  initWithTitle:NSLocalizedString(@"密码不能为空!", nil)
                                  message: nil
                                  delegate:self 
                                  cancelButtonTitle:NSLocalizedString(@"确定", nil) 
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
            [pwdTextField becomeFirstResponder];
        }
        
        self.navigationItem.rightBarButtonItem.enabled=true;
        self.navigationItem.leftBarButtonItem.enabled=true;
    }

    
    /*  
     } else {
     UIAlertView *alert = [[UIAlertView alloc] 
     initWithTitle:NSLocalizedString(@"Network error!", nil)
     message: nil
     delegate:self 
     cancelButtonTitle:NSLocalizedString(@"OK", nil) 
     otherButtonTitles:nil];
     [alert show];
     [alert release];
     }
     */
    
}

- (NSString *) getLoginNameType:(NSString *)loginName
{
    NSPredicate * phonePre = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", PHONENUM_REGEX];
    NSPredicate * emailPre = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", EMAIL_REGEX];
    if([phonePre evaluateWithObject:loginName]){
        return  MOBILE;
    }else if([emailPre evaluateWithObject:loginName]){
        return  EMAIL;
    }else {
        return  LOGIN_ID;
    }
}

- (void) navigationBack
{
    if (!self.navigationItem.rightBarButtonItem.enabled) {
        return;
    }

    if ([self.navigationController.viewControllers count]>1) {
        [self.navigationController popViewControllerAnimated:YES];
    }
    else {
         [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CANCELLOGIN object:self];
    }
       
}

- (void) navigationButtonClick
{
    [AMLogUtils appendLog: APP_WANGWANG_LOGIN_TWO];
    [self loginButtonClick];
}

-(void)setRightButton
{    
    AliNavigationButton * rightButton = [[AliNavigationButton alloc] initWithTitle:@"登录"  style:NAV_BTN_STYLE_MAIN];
    rightButton.navigationButtonDelegate = self;
    self.navigationItem.rightBarButtonItem = rightButton;
    [rightButton release];
    self.navigationItem.rightBarButtonItem.enabled=true;
}

-(void)setBackButton
{    
    AliNavigationBackButton * backButton = [[AliNavigationBackButton alloc] initWithTitle:@"取消" ];
    backButton.navigationBackDelegate=self;
    self.navigationItem.leftBarButtonItem = backButton;
    [backButton release];
    self.navigationItem.leftBarButtonItem.enabled=true;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        self.navigationItem.title = NSLocalizedString(@"IM", @"");
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_aliww"];
        self.tabBarItem.title=NSLocalizedString(@"IM", @"");
        
        self.loginWangwang = NO;
        self.enterWangwang = NO;
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    //  [self.navigationController setNavigationBarHidden:YES];
    [super viewDidLoad];
    
    [self setBackButton];
    [self setRightButton];
    //[nameTextField becomeFirstResponder];
    //[pwdTextField becomeFirstResponder];
    pwdTextField.secureTextEntry =YES;
    
    self._loginRequset = [[LoginRequest alloc] init];
    
    [self.view addSubview:accountTableView];//显示

    AMIMUserDefault * lastUser = [AMIMDefaultStorageHelper getLastLoginedUser];
	if (lastUser) {
		
		nameTextField.text = [lastUser.uid substringFromIndex:8];
        if ([nameTextField.text length] ==0) {
            [nameTextField becomeFirstResponder];
            
        }else{
            [pwdTextField becomeFirstResponder];
        }
        
        BOOL isRememberPwd= lastUser.autoLogin;
        [rememberPwdButton setOn:isRememberPwd animated:YES];

		if (rememberPwdButton.isOn) {
            AESCrypto * crypto = [[AESCrypto alloc] init];
            
            NSString * password = [crypto decryptText: lastUser.passwd];
            if ([password length] == 17 && lastUser.isSpecialPassWord) {
				pwdTextField.text = [password substringToIndex:[password length]-1];
			} else {
				pwdTextField.text = password;
			}
		}		

	} else {
        [nameTextField becomeFirstResponder];
        
	}
    	
    
    if ([nameTextField.text length] ==0) {
        delButton.hidden=YES;
    }else{
        delButton.hidden=FALSE;
    }
    if ([pwdTextField.text length] ==0) {
        delPWDButton.hidden=YES;
    }else{
        delPWDButton.hidden=FALSE;
    }   
    
}

- (void)viewDidUnload
{
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    self._loginRequset = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated {
    if (pwdTextField != nil && [pwdTextField.text length] > 0 ) {
        [pwdTextField becomeFirstResponder];
    } else {
        [nameTextField becomeFirstResponder];
    }
    
    // 重新载入切换用户列表
    [self resetAccountTable];
    [accountTableView reloadData];
    
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
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


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
	if (tableView == loginTableView) {
		return 2;
	}
    
    if (tableView == rememberPwdTableView) {
		return 2;
	} 
    

	if (tableView == accountTableView) {
		NSInteger userCount= [AMIMDefaultStorageHelper getLoginedUserNum];;
        if(userCount < 1){
            nameButton.enabled=FALSE;
        }else {           
            nameButton.enabled=TRUE;
        }
        return userCount;
	}
    
    return 0;
}

- (IBAction)editname:(id)sender
{
    accountTableView.alpha = 0.0f;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	UITableViewCell *cell;
	
	if (tableView == loginTableView) {
		switch (indexPath.row) {
			
			case 0:
				cell = nameCell;
				break;			
			case 1:
				cell = pwdCell;
				break;			
            
            default:
				cell = nil;
				break;
		}
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	} 
  
    if (tableView == rememberPwdTableView) {
		switch (indexPath.row) {
                
			case 0:
				cell = rememberPwdCell;
				break;		
                
			case 1:
				cell = registerCell;
//                cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
//                cell.accessoryType = UITableViewCellAccessoryNone;
//                cell.imageView.image = [UIImage imageNamed:@"icon_listarrow"];
                cell.accessoryView = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_listarrow.png"]] autorelease];
				break;	
                
            default:
				cell = nil;
				break;
		}
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	} 

    if (tableView == accountTableView) {
        
		cell = [accountTableView dequeueReusableCellWithIdentifier:@"AccountTableIdentifier"];
		if (cell == nil) {
			cell = [[[UITableViewCell alloc] 
                     initWithStyle:UITableViewCellStyleDefault
                     reuseIdentifier:@"AccountTableIdentifier"] autorelease];
		}
        
        
        AMIMUserDefault * user = [NSKeyedUnarchiver unarchiveObjectWithData:[[AMIMDefaultStorageHelper getLoginedUserList] objectAtIndex:[indexPath row]]];
        
        cell.textLabel.text =[user.uid substringFromIndex:8];
		cell.textLabel.font = [UIFont systemFontOfSize:14];
        cell.textLabel.textAlignment =UITextAlignmentCenter;
        cell.backgroundColor = [UIHelp colorWithHexString : @"0xfdfdfd"];
        
		cell.editingAccessoryType = ([cell.textLabel.text isEqualToString:nameTextField.text]) ? 
		UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        
	}

	return cell;
}



//编辑cell，删除
- (void)tableView:(UITableView *)tableView 
commitEditingStyle:(UITableViewCellEditingStyle)editingStyle 
forRowAtIndexPath:(NSIndexPath *)indexPath {
	if (tableView == accountTableView) {
        NSString * uid = [AMIMDefaultStorageHelper getLoginedUserWithIndex:[indexPath row]].uid;
        if(uid != nil && [uid isEqualToString:[AMIMDefaultStorageHelper getLastLoginedUserId]]){
            [AMIMDefaultStorageHelper changeLastLoginedUser:@""];
            nameTextField.text = @"";
            pwdTextField.text = @"";
            [rememberPwdButton setOn:NO];
        }
        
        [AMIMDefaultStorageHelper deleteUserWithIndex:[indexPath row] ];
        [tableView reloadData];
       
        
    }
	
}


//选择行
- (NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath{

    return indexPath;
}

//单击行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
   //NSString *registerPath = ALIBABA_CHINA_WEB_SITE;
    
    if (tableView == rememberPwdTableView) {
		if (indexPath.row ==1) {
            [AMLogUtils appendLog:APP_WANGWANG_LOGIN_ONE];
            
            AMRegisterViewController * registerControl = [[AMRegisterViewController alloc]init ];
            registerControl.backController = self;
            [self.navigationController pushViewController:registerControl animated:YES];
//            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:registerPath]];
				
		}
	
	} else if (tableView == accountTableView) {
        [AMLogUtils appendLog:APP_WANGWANG_LOGIN_THREE];
        
        
        UITableViewCell *newCell = [tableView cellForRowAtIndexPath:indexPath];

		newCell.editingAccessoryType = UITableViewCellAccessoryCheckmark;
		
        AMIMUserDefault * user = [AMIMDefaultStorageHelper getLoginedUserWithIndex:[indexPath row]];
        
        BOOL isRememberPwd= user.autoLogin;
        [rememberPwdButton setOn:isRememberPwd animated:YES];
        nameTextField.text = newCell.textLabel.text;
		if (isRememberPwd) {

            NSString *password;
            AESCrypto * crypto = [[AESCrypto alloc] init];
            
            password = [crypto decryptText:user.passwd];

			if ([password length] == 17 && user.isSpecialPassWord) {
				pwdTextField.text = [password substringToIndex:[password length]-1];
			} else {
				pwdTextField.text = password;
			}
		} else {
			pwdTextField.text = nil;
		}
        
		NSIndexPath * prevIndexPath = [NSIndexPath indexPathForRow:lastAccountRow inSection:0];
		UITableViewCell *oldCell = [tableView cellForRowAtIndexPath:prevIndexPath];
		oldCell.editingAccessoryType = UITableViewCellAccessoryNone;
		lastAccountRow = [indexPath row];
 
		//accountTableView.center = CGPointMake(160, 10);

        accountTableView.alpha = 0.0f;
//lih        
        if ([nameTextField.text length] ==0) {
            delButton.hidden=YES;
        }else{
            delButton.hidden=FALSE;
        }
        if ([pwdTextField.text length] ==0) {
            delPWDButton.hidden=YES;
        }else{
            delPWDButton.hidden=FALSE;
        } 

	} 
 
}

//删除
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
	if (tableView == accountTableView) {
		return UITableViewCellEditingStyleDelete;
	}
	return UITableViewCellEditingStyleNone;
	
}
- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath {
	return NSLocalizedString(@"Delete", nil);
}

							   
- (IBAction) nameButtonOnClick:(id)sender {
	[accountTableView reloadData];


    accountTableView.alpha = 1.0f;
}



- (IBAction) rememberPwdButtonOnClick:(id)sender {
 
    BOOL isRememberPwd = !rememberPwdButton.isOn;
	[rememberPwdButton setOn:isRememberPwd animated:YES];
}

- (IBAction) delButtonOnClick:(id)sender { 
    [AMLogUtils appendLog:APP_WANGWANG_LOGIN_FOUR];
    
    nameTextField.text = nil;
	pwdTextField.text = nil;
    delButton.hidden=TRUE;
    delPWDButton.hidden =YES;
    [nameTextField becomeFirstResponder];
}

- (IBAction) delPWDButtonOnClick:(id)sender {  
    [AMLogUtils appendLog:APP_WANGWANG_LOGIN_FIVE];
    
    pwdTextField.text = nil;	
    delPWDButton.hidden=TRUE;
}

//return button
- (IBAction) textFieldDoneEditing:(id)sender {

	[UIView beginAnimations:nil context:nil];
    [self loginButtonClick];
	[UIView setAnimationDuration:0.3f];
	[UIView commitAnimations];
    [nameTextField resignFirstResponder];
    [pwdTextField resignFirstResponder];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
	if (textField == nameTextField) {
      
        if (([nameTextField.text length] == 0) &&(range.location == 0)) {
            delButton.hidden=FALSE;
        }
        if (([nameTextField.text length] == 1) &&(range.location == 0)) {
            delButton.hidden=TRUE;
        }
        
		if (range.location == 120) {
			UIAlertView *alert = [[UIAlertView alloc] 
								  initWithTitle:NSLocalizedString(@"用户名不能多于120个字符.", nil)
								  message:nil
								  delegate:self 
								  cancelButtonTitle:NSLocalizedString(@"确定", nil) 
								  otherButtonTitles:nil];
			[alert show];
			[alert release];
            [nameTextField becomeFirstResponder];
			return NO;
		}
	} else if (textField == pwdTextField) {
        
        if (([pwdTextField.text length] == 0) &&(range.location == 0)) {
            delPWDButton.hidden=FALSE;
        }
        if (([pwdTextField.text length] == 1) &&(range.location == 0)) {
            delPWDButton.hidden=TRUE;
        }
        
		if (range.location == 24) {
			UIAlertView *alert = [[UIAlertView alloc] 
								  initWithTitle:NSLocalizedString(@"密码不能长于24个字符.", nil)
								  message:nil
								  delegate:self 
								  cancelButtonTitle:NSLocalizedString(@"确定", nil) 
								  otherButtonTitles:nil];
			[alert show];
			[alert release];
            [pwdTextField becomeFirstResponder];
			return NO;
		}
	}
    
	return YES;
}

-(void) resetAccountTable {
    // 重新载入切换用户列表
    BOOL isHaveUserList = [AMIMDefaultStorageHelper hasLoginedUser];
    accountTableView.alpha = 0.0f;
    nameButton.enabled=FALSE;
	if (isHaveUserList == YES) {
        nameButton.enabled=TRUE;
        accountTableView.editing = YES;
        accountTableView.allowsSelectionDuringEditing = YES;
        
        accountTableView.backgroundColor=[UIHelp colorWithHexString : @"0xeeeeee"];        
        accountTableView.layer.borderColor=[[UIHelp colorWithHexString : @"0xd0d0d0"] CGColor];
        accountTableView.layer.borderWidth=2;
	}
}

- (void)dealloc {
    
    [loginData release];
    [nameCell release];
    [pwdCell release];
    [rememberPwdCell release];
    [registerCell release];
    [loginTableView release];
    [rememberPwdTableView release];
    [accountTableView release]; 
    [nameTextField release];
    [pwdTextField release];
    [loginButton release];
    [autoLoginButton release];
    [delButton release];
    [rememberPwdButton release];
    [nameButton release];
    [sitePrefixList release];
    [accountDictionary release];
    [loginView release];
    [navigationBackButton release];
    [_loginRequset release];
    [_loginRequset release];
    [_object release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [delPWDButton release];
    [super dealloc];
}

@end

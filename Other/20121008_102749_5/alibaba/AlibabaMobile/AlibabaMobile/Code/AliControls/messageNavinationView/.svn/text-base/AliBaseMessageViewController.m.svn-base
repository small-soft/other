//
//  AliBaseMessageViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliBaseMessageViewController.h"
#import "AMAppDelegate.h"
#import "MessageCenterButtonView.h"
#import "LoginToken.h"
#import "AMIMViewController.h"
#import "MessageCenterListViewController.h"
#import "AMLogUtils.h"

@interface AliBaseMessageViewController ()

@end

@implementation AliBaseMessageViewController

-(void)initNavigationTitle {

    UIImageView * logoImageView = [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"logo_topbar"]];
    self.navigationItem.titleView = logoImageView;
    [logoImageView release];


    MessageCenterButtonView * msgButton;
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3)
    {
    
        AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:[appDelegate getUnReadMsgNum]];
  
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_RECV object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_READ object:nil];
    }
    else
    {
        msgButton = [[MessageCenterButtonView alloc] initWithState:NO num:0];
    }

    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    [msgButton release];

    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_LOGOUT object:nil];
}

- (void) loginSucc {  
    self.navigationItem.rightBarButtonItem = nil;
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
   
    MessageCenterButtonView *  msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:[appDelegate getUnReadMsgNum]];
    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];
    [msgButton release];
}

- (void)loginOut
{
    self.navigationItem.rightBarButtonItem = nil;
    MessageCenterButtonView *msgButton = [[MessageCenterButtonView alloc] initWithState:NO num:0];    //    [msgButton setMsgNum:0];
    //    [msgButton changeLoginState:YES];
    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];
    [msgButton release];
    
}

- (IBAction)msgBtnAction:(id)sender
{
    // Add log trace point here
    [AMLogUtils appendLog: APP_HOME_PAGE_SIX];
    
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){ 
        
        [self openMsgList];
        
    }else{
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_RECV object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_READ object:nil];
        
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;   
        [self.navigationController pushViewController:nextController animated:YES];            
    } 
    
}
-(void)openMsgList{
    MessageCenterListViewController * msgViewController = [[MessageCenterListViewController alloc] init];
    msgViewController.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:msgViewController animated: YES];
    [msgViewController release];
}

- (void) recvNewMsg
{
    NSString * loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){  
        AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        
        int newMsgNum =  [appDelegate getUnReadMsgNum];
        self.navigationItem.rightBarButtonItem = nil;
        MessageCenterButtonView * msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:newMsgNum];
        [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
        
        self.navigationItem.rightBarButtonItem = rightItem;
        [rightItem release];
        [msgButton release];
        
    }
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}



- (void)viewDidLoad {
    [super viewDidLoad];
    [self initNavigationTitle];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [super dealloc];
}

@end

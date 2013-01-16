//
//  AMAbout.m
//  AlibabaMobile
//
//  Created by lih on 12-2-24.
//  Modify by xiaowen on 12-5-23
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAbout.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "AMVersionCheck.h"

@interface AMAbout()
@property (nonatomic, retain) IBOutlet UIImageView *versionPicture;
@property (nonatomic, retain) AMVersionCheck *versionCheck;
@end

@implementation AMAbout
@synthesize updateButton = _updateButton;
@synthesize versionPicture=_versionPicture;
@synthesize versionCheck = _versionCheck;

-(AMVersionCheck*)versionCheck
{
    if (!_versionCheck) {
        _versionCheck = [[AMVersionCheck alloc]init];
    }
    return _versionCheck;
}


- (IBAction)updateClicked:(id)sender {
    [self.versionCheck loadObjectsFromRemote];//检查更新
    updateAlertFirst = YES;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"关于", @"");
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)setBackButton
{    
    AliNavigationBackButton * backButton = [[AliNavigationBackButton alloc] initWithTitle:@"更多" ];
    backButton.navigationBackDelegate=self;
    self.navigationItem.leftBarButtonItem = backButton;
    [backButton release];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{    
    [super viewDidLoad];
    [self setBackButton];
//    updateAlertFirst = YES;
    //注册是否有更新监听
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(noUpdate) name:NOTIFICATION_NO_UPDATE_CHECK object:nil];
}

- (void) noUpdate
{  
    if(updateAlertFirst){
        NSString *msg = [[NSString alloc]initWithFormat:@"亲，您的版本已经是最新了哦"];
        UIAlertView *alert = [[UIAlertView alloc] 
                              initWithTitle:@"" 
                              message:msg 
                              delegate:self    
                              cancelButtonTitle:@"好"                          
                              otherButtonTitles:nil ,
                              nil]; 
        [alert show]; 
        [msg release];
        [alert release];
        updateAlertFirst = NO;
    }
    
}
- (void)viewDidUnload
{
    [self setUpdateButton:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {   
    [_versionPicture release];
    [_updateButton release];
    [super dealloc];
}

@end

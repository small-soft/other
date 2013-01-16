//
//  AMFeedback.m
//  AlibabaMobile
//
//  Created by lih on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMFeedback.h"
#import <QuartzCore/QuartzCore.h>
#import "UIHelp.h"
#import "ConstDef.h"
#import "LoginToken.h"
#import "AliToastView.h"

@implementation AMFeedback
@synthesize feedbackContent=_feedbackContent;
@synthesize thanksLabel=_thanksLabel;
@synthesize feedbackRequset=_feedbackRequset;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"意见反馈", @"");
        self.view.backgroundColor=[UIHelp colorWithHexString : @"0xf0f0f0"];
        self.feedbackContent.layer.cornerRadius=10.0; 
        self.feedbackContent.layer.borderWidth = 1;
        self.feedbackContent.layer.borderColor=[[UIHelp colorWithHexString : @"0x999999"] CGColor];
        self.feedbackContent.backgroundColor=[UIColor whiteColor];
        
        
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)callRemoteAPI {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_FEEDBACK usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
		
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.feedbackRequset;
    }];
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"Loaded objects: %@", objects);    
    self.feedbackContent.text=@"";
    self.navigationItem.rightBarButtonItem.enabled=TRUE;
    [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"提交建议成功"] show];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
	NSLog(@"Hit error: %@", error);    
    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"提交建议失败"] show];
    self.navigationItem.rightBarButtonItem.enabled=TRUE;
}


- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) sendUserSuggestion 
{
    if (nil == self.feedbackRequset) {
        self.feedbackRequset = [[AMFeedbackRequest alloc] init]; 
    }
    self.feedbackRequset.requestURL=OCEAN_API_URL_FEEDBACK;
    self.feedbackRequset.memberId=[LoginToken getLoginUserName]; 
    self.feedbackRequset.content=_feedbackContent.text;
    self.feedbackRequset.source=@"iOS";  
    self.feedbackRequset.type=@"common";
    [self callRemoteAPI]; 
    
}

- (void) navigationButtonClick
{
    if([self.feedbackContent.text length] == 0 ){
       // [AliToast showWithText:@"请填写您的意见！" topOffset:140 duration:1];
        return;
    }
    
    [self sendUserSuggestion]; 
    self.navigationItem.rightBarButtonItem.enabled=FALSE;
}

-(void)setRightButton
{    
    AliNavigationButton * rightButton = [[AliNavigationButton alloc] initWithTitle:@"提交"  style:NAV_BTN_STYLE_COMMON];
    rightButton.navigationButtonDelegate = self;
    self.navigationItem.rightBarButtonItem = rightButton;
    [rightButton release];
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
    // Do any additional setup after loading the view from its nib.
    [self setBackButton];
    [self setRightButton];
    [_feedbackContent becomeFirstResponder];
}

- (void)viewDidUnload
{
    self.feedbackContent=nil;
    self.thanksLabel=nil;
    self.feedbackRequset=nil;
    [_feedbackContent resignFirstResponder];
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
    [_feedbackContent release];
    [_thanksLabel release];
    [_feedbackRequset release];
    [super dealloc];
}

@end

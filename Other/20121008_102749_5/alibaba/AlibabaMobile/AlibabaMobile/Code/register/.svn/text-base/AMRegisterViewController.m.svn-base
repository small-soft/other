//
//  AMRegisterViewController.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMRegisterViewController.h"
#import "AliToastView.h"
#import "AMWapRegisterViewController.h"

#import "AMOrderDetailViewController.h"

@implementation AMRegisterViewController

@synthesize backController=_backController;
@synthesize btnMsgReg = _btnMsgReg;
@synthesize btnManulReg = _btnManulReg;

@synthesize button1;
@synthesize button2;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    UIImage * imgMsgNormal = [UIImage imageNamed:@"btn_ct_orange"];
    imgMsgNormal = [imgMsgNormal stretchableImageWithLeftCapWidth:imgMsgNormal.size.width/4 topCapHeight:imgMsgNormal.size.height/4];
    [_btnMsgReg setBackgroundImage:imgMsgNormal forState:UIControlStateNormal];

    UIImage * imgMsgPressed = [UIImage imageNamed:@"btn_ct_orange_tap"];
    imgMsgPressed = [imgMsgPressed stretchableImageWithLeftCapWidth:imgMsgPressed.size.width/4 topCapHeight:imgMsgPressed.size.height/4];
    [_btnMsgReg setBackgroundImage:imgMsgPressed forState:UIControlStateHighlighted];
    
    UIImage * imgManulNormal = [UIImage imageNamed:@"btn_ct_nor"];
    imgManulNormal = [imgManulNormal stretchableImageWithLeftCapWidth:imgManulNormal.size.width/4 topCapHeight:imgManulNormal.size.height/4];
    [_btnManulReg setBackgroundImage:imgManulNormal forState:UIControlStateNormal];
    
    UIImage * imgManulPressed = [UIImage imageNamed:@"btn_ct_p"];
    imgManulPressed = [imgManulPressed stretchableImageWithLeftCapWidth:imgManulPressed.size.width/4 topCapHeight:imgManulPressed.size.height/4];
    [_btnManulReg setBackgroundImage:imgManulPressed forState:UIControlStateHighlighted];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    UIImage * bgImg1 = [UIImage imageNamed:@"btn_ct_orange.png"];
    bgImg1 = [bgImg1 stretchableImageWithLeftCapWidth:bgImg1.size.width/8 topCapHeight:0];
    [self.button1 setBackgroundImage:bgImg1 forState:UIControlStateNormal];
    
    UIImage * bgImg2 = [UIImage imageNamed:@"btn_ct_nor.png"];
    bgImg2 = [bgImg2 stretchableImageWithLeftCapWidth:bgImg2.size.width/8 topCapHeight:0];
    [self.button2 setBackgroundImage:bgImg2 forState:UIControlStateNormal];
    
    UIImage * bgImg3 = [UIImage imageNamed:@"btn_ct_orange_tap.png"];
    bgImg3 = [bgImg3 stretchableImageWithLeftCapWidth:bgImg3.size.width/8 topCapHeight:0];
    [self.button1 setBackgroundImage:bgImg3 forState:UIControlStateHighlighted];
    
    UIImage * bgImg4 = [UIImage imageNamed:@"btn_ct_p.png"];
    bgImg4 = [bgImg4 stretchableImageWithLeftCapWidth:bgImg4.size.width/8 topCapHeight:0];
    [self.button2 setBackgroundImage:bgImg4 forState:UIControlStateHighlighted];
    
    
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(NSString*)commonTableViewNavigationTitle {
    return @"免费注册";
}

//-(NSString*)commonTableViewBackButtonTitle {
//    return @"应用中心";
//}

-(IBAction)registerBySMS:(id)sender
{
    NSLog(@"registering by short message!");
    [self sendSMS];
}

-(IBAction)registerByWAP:(id)sender
{
    NSLog(@"registering by WAP!");
//    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:ALIBABA_CHINA_WEB_SITE]];
    
    AMWapRegisterViewController * controller = [[[AMWapRegisterViewController alloc] init]autorelease];
    
    controller.backController = self;
    if ( self.backController != nil )
    {
        controller.loginController = self.backController;
    }
    [self.navigationController pushViewController:controller animated:YES];
    
//    AMOrderDetailViewController * con = [[AMOrderDetailViewController alloc ] init];
//    
//    [self.navigationController pushViewController:con animated:YES];
    
}

-(void) sendSMS {
    NSString * content = @"ZC";
    NSMutableArray * recipients = [[NSMutableArray alloc]init ];
    [recipients addObject:@"106909991688"];
    
    MFMessageComposeViewController * controller = [[[MFMessageComposeViewController alloc]init] autorelease];
    
    if ([MFMessageComposeViewController canSendText]) {
        controller.body = content;
        controller.recipients = recipients;
        controller.messageComposeDelegate = self;
        [self presentModalViewController:controller animated:YES];
    }
}

-(void) messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result {
    [self dismissModalViewControllerAnimated:YES];
    if(result == MessageComposeResultCancelled){
        NSLog(@"cancelled");
    }else if(result == MessageComposeResultSent){
        NSLog(@"sent");
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"发送成功！"] show];
    }else {
        NSLog(@"failed");
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"发送失败！"] show];
    }    
}

- (void) dealloc {
    AM_RELEASE_SAFELY(_backController);
    AM_RELEASE_SAFELY(_btnManulReg);
    AM_RELEASE_SAFELY(_btnMsgReg);
    
    [super dealloc];
}

@end

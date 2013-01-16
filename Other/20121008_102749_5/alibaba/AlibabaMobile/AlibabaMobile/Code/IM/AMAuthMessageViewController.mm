//
//  AMAuthMessageViewController.m
//  AlibabaMobile
//
//  Created by tom.lih on 12-7-16.
//  Copyright (c) 2012年 abc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "AMAuthMessageViewController.h"
#import "UIHelp.h"
#import "ConstDef.h"
#import "AliToastView.h"
#import "CallBackTool.h"

@interface AMAuthMessageViewController ()
{
    NSString * _fid;
}

@property (nonatomic, retain) IBOutlet UILabel    *authLabel;
@property (nonatomic, retain) IBOutlet UITextView *msgTextView;
@end

@implementation AMAuthMessageViewController
@synthesize authLabel=_authLabel;
@synthesize msgTextView=_msgTextView;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (id)initWithFid:(NSString *)friendId 
{
    self = [super init];
    if (self) {    
        _fid = [[NSString alloc] initWithString:friendId];
        
    }
    
    return self;
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) navigationButtonClick
{
    if([self.msgTextView.text length] == 0 ){
        return;
    }
    CallBackTool *tool = [CallBackTool create];
	[tool sendAuthMessage:_fid message:_msgTextView.text];
    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"已提交您的添加申请，等待对方确认"] show];
    self.navigationItem.rightBarButtonItem.enabled=FALSE;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    self.title = NSLocalizedString(@"申请添加", @"");
    self.view.backgroundColor=[UIHelp colorWithHexString : @"0xf0f0f0"];
    self.msgTextView.layer.cornerRadius=10.0; 
    self.msgTextView.layer.borderWidth = 1;
    self.msgTextView.layer.borderColor=[[UIHelp colorWithHexString : @"0x999999"] CGColor];
    self.msgTextView.backgroundColor=[UIColor whiteColor];
    NSString* str1=@"将添加 ";
    NSString* str2=[str1 stringByAppendingString:[_fid substringFromIndex:8]];
    NSString* str3=@" 为好友";
    NSString* str4=[str2 stringByAppendingString:str3];
    _authLabel.text=str4; 
    _msgTextView.text=@"验证信息";
    
    AliNavigationButton * rightBtn = [[AliNavigationButton alloc] initWithTitle:@"完成" style:NAV_BTN_STYLE_COMMON];
    rightBtn.navigationButtonDelegate = self;
    self.navigationItem.rightBarButtonItem = rightBtn;
    [rightBtn release];
    
}

- (void)viewDidUnload
{
    self.msgTextView=nil;
    self.authLabel=nil;
    [_msgTextView resignFirstResponder];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

#pragma mark textView delegate
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)texting {
	if (textView == _msgTextView) {
        
        if (range.length != 1 && [texting isEqualToString:@"\n"]) {
            if([self.msgTextView.text length] != 0 ){
                CallBackTool *tool = [CallBackTool create];
                [tool sendAuthMessage:_fid message:_msgTextView.text];
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"已提交您的添加申请，等待对方确认"] show];
            }
            
        }else if (range.location == 15) {
			UIAlertView *alert = [[UIAlertView alloc] 
								  initWithTitle:NSLocalizedString(@"You are limited to 15 characters.", nil)
								  message:nil
								  delegate:self 
								  cancelButtonTitle:NSLocalizedString(@"OK", nil) 
								  otherButtonTitles:nil];
			[alert show];
			[alert release];
			return NO;
		}
	} 
	return YES;
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    _msgTextView.text=@"";
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    NSLog(@"textViewDidEndEditing");
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)dealloc {   
    [_msgTextView release];
    [_authLabel release];
    [_fid release];
    [super dealloc];
}

@end

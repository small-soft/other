//
//  AMIMModifySignViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-14.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMModifySignViewController.h"
#import "AliNavigationButton.h"
#import "AliToastView.h"
#import "AMIMUserModel.h"
#import "CallBackTool.h"
#import "AMIMDefaultStorageHelper.h"
#import "AMIMCoreDataHelper.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

#define MAX_INPUT_LENGTH 64

@interface AMIMModifySignViewController ()
{
    AMIMUserModel * _user;
}

@property (nonatomic, retain) IBOutlet UITextView * textView;
@property (nonatomic, retain) IBOutlet UILabel * numLabel;

@end

@implementation AMIMModifySignViewController

@synthesize textView = _textView;
@synthesize numLabel = _numLabel;

- (void) dealloc
{
    [_textView release];
    [_numLabel release];
    
    [_user release];
    
    [super dealloc];
}

- (id)initWithUser:(NSString *)userId
{
    self = [super init];
    if (self) {
        _user = [[[AMIMCoreDataHelper getInstance] getFriendWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId] uid:userId] retain];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = @"修改个性签名";
    
//    _textView.layer.masksToBounds = YES;
//    _textView.layer.cornerRadius = 10.0;
    _textView.layer.borderWidth = 1;
    _textView.layer.borderColor = [UIColor lightGrayColor].CGColor;
    _textView.delegate = self;
    _textView.text = _user.signature;
    [_textView becomeFirstResponder];
    
    AliNavigationButton * completeBtn = [[AliNavigationButton alloc] initWithTitle:@"完成" style:NAV_BTN_STYLE_MAIN];
    completeBtn.navigationButtonDelegate = self;
    self.navigationItem.rightBarButtonItem = completeBtn;
    [completeBtn release];
}


- (void) navigationButtonClick;
{
    [self modifySign];
}

-(void) modifySign
{
    [AMLogUtils appendLog:APP_WANGWANG_EDIT_SIGNATURE_ONE];
    
    NSString * signStr = _textView.text;
    //_textView.text = @"";
    
    _user.signature = [signStr retain];

    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setValue:_user.signature forKey:@"im_new_signature"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [[CallBackTool create] changeSelfSignature:_user.signature];
    [self.navigationController popViewControllerAnimated:YES];
    
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
//    [self modifySign];
}

- (void)textViewDidChange:(UITextView *)textView
{
    NSString * text = textView.text;
    int length = text.length;
    if(text.length > MAX_INPUT_LENGTH){
        text = [text substringToIndex:MAX_INPUT_LENGTH];
        textView.text = text;
        length = MAX_INPUT_LENGTH;
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"您已输满64个字了哦！"] show];
    }
    
    _numLabel.text = [NSString stringWithFormat:@"%d/%d", length, MAX_INPUT_LENGTH];
}

@end

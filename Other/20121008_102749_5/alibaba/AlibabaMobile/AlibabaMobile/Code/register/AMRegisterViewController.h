//
//  AMRegisterViewController.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCommonTableView.h"
#import <MessageUI/MFMessageComposeViewController.h>

@interface AMRegisterViewController : AliCommonTableView<MFMessageComposeViewControllerDelegate>

@property (retain,nonatomic) UIViewController * backController;

@property (retain,nonatomic) IBOutlet UIButton * button1;
@property (retain,nonatomic) IBOutlet UIButton * button2;

//鞠磊请病假，提交的代码有问题，小文代为修复一些问题以便能编译通过
@property (retain,nonatomic) IBOutlet UIButton * btnMsgReg;
@property (retain,nonatomic) IBOutlet UIButton * btnManulReg;

@end

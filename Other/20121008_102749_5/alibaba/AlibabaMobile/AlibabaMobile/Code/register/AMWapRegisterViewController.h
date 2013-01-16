//
//  AMWapRegisterViewController.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliWebViewController.h"

@interface AMWapRegisterViewController : AliWebViewController

@property (retain, nonatomic) IBOutlet UIWebView *contentWebView;
@property (retain,nonatomic)NSString *url;

@property (retain, nonatomic ) UIViewController * backController;
@property (retain, nonatomic ) UIViewController * loginController;

@end

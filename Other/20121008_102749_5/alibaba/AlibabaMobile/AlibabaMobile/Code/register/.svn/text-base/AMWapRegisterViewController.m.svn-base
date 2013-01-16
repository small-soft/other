//
//  AMWapRegisterViewController.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMWapRegisterViewController.h"

#import "AMIMViewController.h"

@interface AMWapRegisterViewController ()

@end

@implementation AMWapRegisterViewController

@synthesize contentWebView=_contentWebView;
@synthesize url=_url;
@synthesize backController=_backController;
@synthesize loginController=_loginController;

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
}

-(void)viewWillAppear:(BOOL)animated
{
//    [super viewWillAppear:animated];
//    if (self.firstLoadData) 
//    {
        [super viewWillAppear:animated];
        NSMutableURLRequest     *request;
        if (!self.url) {
            self.url = @"http://m.1688.com/touch/member/appRegister.htm";
            
//            self.url = @"http://m.1688.com/touch/member/appRegisterSuccess.htm";
//            self.url = @"http://m.1688.com/touch/member/appRegisterError.htm";


        }
        
        
        request = [[ NSMutableURLRequest alloc ] initWithURL: [NSURL URLWithString:self.url] ];
    
    
    
        [self.contentWebView loadRequest: request ];

        [ request release ];
//        self.firstLoadData=NO;
//    }
//    else {
//        if ([self needReloadView]) {
//            [self.contentWebView reload];
//        }
//    }
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

-(NSString*)webViewNavigationTitle
{
    return @"手动注册";
}

-(void) webViewDidFinishLoad:(UIWebView *)webView
{
    NSString * cur = [ webView stringByEvaluatingJavaScriptFromString:@"document.documentElement.innerHTML"];
    
    
    NSLog(@"current :%@", cur);
}



- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSString* url = request.URL.absoluteString;
    NSLog(@"%@",url);
    
    //
//    NSString *OFFER_DETAIL_URL =  @"http://wap.baidu.com";
//    NSRange range = [url rangeOfString:OFFER_DETAIL_URL]; 
//    
//    NSString *OFFER_DETAIL_URL1 =  @"1688.com";
//    NSRange range1 = [url rangeOfString:OFFER_DETAIL_URL1]; 
//    
//    NSString *OFFER_DETAIL_URL2 =  @"alibaba.com";
//    NSRange range2 = [url rangeOfString:OFFER_DETAIL_URL2]; 
//    
//    NSString *OFFER_DETAIL_URL3 =  @"m.baidu.com";
//    NSRange range3 = [url rangeOfString:OFFER_DETAIL_URL3]; 
//    
//    if (range.length>0 || range3.length>0) {
//        if (range.length>0 || range1.length>0 || range2.length>0 || range3.length>0) {

//                return YES;
//    }
//    else {
//        if (range1.length>0 || range2.length>0) {
            //            [self.navigationController popViewControllerAnimated:YES ];
//            AMIMViewController * con= [[AMIMViewController alloc ] init ];
//            [self.navigationController pushViewController: con animated:YES];
            
//            
//            UIViewController *nextController;
//            nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
//            nextController.hidesBottomBarWhenPushed=YES;   
            
//            [self.navigationController popToViewController:self.loginController animated:YES];
//        }
//
//        
//        NSLog(@"other pages? no way!");
//
//        return NO;
//            
//    }
    
    //注册页面点返回
    NSString *goBack =  @"m.1688.com/touch/member/register/ios/back";
    NSRange range1 = [url rangeOfString:goBack];
    
    //注册失败页面点返回
    NSString *goBack1 =  @"m.1688.com/touch/member/registerError/ios/back";
    NSRange range2 = [url rangeOfString:goBack1];
    
    //注册成功页面点返回
    NSString *goBack2 =  @"m.1688.com/touch/member/registerSuccess/ios/back";
    NSRange range3 = [url rangeOfString:goBack2];
    
    //注册成功页面点登陆
    NSString *goLogin =  @"m.1688.com/touch/member/registerSuccess/ios/login";
    NSRange range4 = [url rangeOfString:goLogin];
    
    if( range1.length>0 ||  range2.length>0 ||  range3.length>0)
    {
        [self.navigationController popToViewController:self.backController animated:YES];
        return NO;
    }
    else  if( range4.length>0 ){
        [self.navigationController popToViewController:self.loginController animated:YES];
        return NO;
    }
    
    return YES;

  

}

@end

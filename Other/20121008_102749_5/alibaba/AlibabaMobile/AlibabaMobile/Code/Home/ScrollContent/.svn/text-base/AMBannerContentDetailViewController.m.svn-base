//
//  AMBannerContentDetailViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBannerContentDetailViewController.h"
#import "SystemUtils.h"

@interface AMBannerContentDetailViewController()
@property (readwrite, nonatomic) BOOL firstLoadData;
@end


@implementation AMBannerContentDetailViewController
@synthesize contentWebView=_contentWebView;
@synthesize url=_url;
@synthesize lastButton = _lastButton;
@synthesize nextButton = _nextButton;
@synthesize homeButton = _homeButton;
@synthesize noDataView = _noDataView;
@synthesize loadingView = _loadingView;
@synthesize refreshButton = _refreshButton;
@synthesize firstLoadData=_firstLoadData;
@synthesize navigationTitle=_navigationTitle;
@synthesize showToolBar=_showToolBar;
@synthesize toolBarView = _toolBarView;
@synthesize parentTitle=_parentTitle;
- (void)dealloc {
    [_contentWebView release];
    [_url release];
    [_lastButton release];
    [_nextButton release];
    [_homeButton release];
    [_refreshButton release];
    [_noDataView release];
    [_loadingView release];
    [_navigationTitle release];
    [_toolBarView release];
    [_parentTitle release];
    [super dealloc];
}
- (void)viewDidUnload {
  
    [self setContentWebView:nil];
//    _url = nil;
    [self setLastButton:nil];
    [self setNextButton:nil];
    [self setHomeButton:nil];
    [self setRefreshButton:nil];
    [self setNoDataView:nil];
    [self setLoadingView:nil];
    [self setToolBarView:nil];
    [super viewDidUnload];
   }

-(void)viewDidLoad
{  
    self.firstLoadData=YES;

    [self.lastButton setEnabled:NO];
    [self.nextButton setEnabled:NO];
   
    if (self.showToolBar) {
        [self.toolBarView setHidden:NO];
        self.contentWebView.frame = CGRectMake(0.0, 0.0, 320.0, 365.0);
    }
    else {
        [self.toolBarView setHidden:YES];
         self.contentWebView.frame = CGRectMake(0.0, 0.0, 320.0, 416.0);

    }
  [self.navigationController setNavigationBarHidden:NO animated:YES];
    if (!self.url) {
        self.showToolBar = YES;
    }
    [super viewDidLoad];
}
-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    if (self.firstLoadData) 
    {
        NSMutableURLRequest     *request;
        if (!self.url) {
            self.url = @"http://m.1688.com/touch/club/index/";
        }
        
      
        request = [[ NSMutableURLRequest alloc ] initWithURL: [NSURL URLWithString:self.url] ];
        [self.contentWebView loadRequest: request ];
        [ request release ];
        self.firstLoadData=NO;
    }
    else {
        if ([self needReloadView]) {
            [self.contentWebView reload];
        }
    }
}

-(NSString*)webViewBackButtonTitle
{
    return self.parentTitle;
     
}
- (void) showLoadingView
{
 
    [self.loadingView setHidden:NO];
    [self.noDataView setHidden:YES];
    
}
- (void) showNodataMessage
{
    [self.loadingView setHidden:YES];
    [self.noDataView setHidden:NO];
}
//去除加载进度
-(void) endLoadingView
{
    [self.loadingView setHidden:YES];
    [self.noDataView setHidden:YES];
}
-(NSString*)webViewNavigationTitle
{
    if (self.navigationTitle) {
        return self.navigationTitle;
    }
    else {
        return @"论坛";
    }
    
}
- (IBAction)gogoLast { 
    if ([self.contentWebView canGoBack]) {
        [self.contentWebView goBack];
    }
}
- (IBAction)gotoNext {
    if ([self.contentWebView canGoForward]) {
        [self.contentWebView goForward];
    }
}
- (IBAction)gotoHome {
    NSMutableURLRequest     *request;
    self.url = @"http://m.1688.com/touch/club/index/";
    request = [[ NSMutableURLRequest alloc ] initWithURL: [NSURL URLWithString:self.url] ];
    [self.contentWebView loadRequest: request ];
    [ request release ];
}
- (IBAction)gotoRefresh:(id)sender {
    [self.contentWebView reload];

}


- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    [super webViewDidFinishLoad:webView];
    if ([self.contentWebView canGoBack]) {
        [self.lastButton setEnabled:YES];
    }
    else {
        [self.lastButton setEnabled:NO];
    }
    if ([self.contentWebView canGoForward]) {
        [self.nextButton setEnabled:YES];
    }
    else {
        [self.nextButton setEnabled:NO];
    }
}
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    NSLog(@"didFailLoadWithError %@",error);
    if (error.code!=102) {
           [self showNodataMessage];
    }
 
    if ([self.contentWebView canGoBack]) {
        [self.lastButton setEnabled:YES];
    }
    else {
        [self.lastButton setEnabled:NO];
    }
    if ([self.contentWebView canGoForward]) {
        [self.nextButton setEnabled:YES];
    }
    else {
        [self.nextButton setEnabled:NO];
    }

}

-(BOOL) webView:(UIWebView *)inWeb shouldStartLoadWithRequest:(NSURLRequest *)inRequest navigationType:(UIWebViewNavigationType)inType {
    
    
    // open iphone app store
    if (inType == UIWebViewNavigationTypeLinkClicked ) {
        NSURL *srcUrl = inRequest.URL;
        NSRange range = [srcUrl.absoluteString rangeOfString:@"itunes.apple.com" options:NSCaseInsensitiveSearch];
        
        if (range.length > 0) {

            [SystemUtils openBrowserWithUrl:srcUrl.absoluteString];
            
            return NO;
            
        }
        
        
    }
    
    
    return [super webView:inWeb shouldStartLoadWithRequest:inRequest navigationType:inType];
}


@end

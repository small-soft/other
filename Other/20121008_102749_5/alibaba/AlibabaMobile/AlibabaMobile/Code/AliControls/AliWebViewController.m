//
//  AliWebViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliWebViewController.h"
#import "AMIMViewController.h"
#import "AliDesEncode.h"
#import "LoginToken.h"
#import "AMOfferTabViewController.h"
#import "AMCompanyTabViewController.h"
#import "AMNewsDetailViewController.h"
#import "AMOfferListViewController.h"
#import "AMSubCategoryViewController.h"
#import "AMSearchCompanyViewController.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AliWebViewController()
@property (nonatomic,retain) AliNavigationBackButton *backButton;
//@property (nonatomic,retain) AliLoadingDataView * mLoadingView;
@property (nonatomic) BOOL needReloadWebContent;

-(NSString*) getExtraCookie;
-(BOOL)checkLogin:(NSString *)url;
-(BOOL)checkRegister:(NSString *)url;
- ( void )reloadWebview: (UIWebView*)webView  webViewUrl: (NSString *)stringUrl;
@end

@implementation AliWebViewController 
@synthesize backButton=_backButton;
//@synthesize mLoadingView=_mLoadingView;
@synthesize needReloadWebContent=_needReloadWebContent;
-(NSString*)webViewBackButtonTitle
{
    return nil;
}

-(NSString*)webViewNavigationTitle
{
    return nil;
}
-(NSString*)webViewOptionButtonTitle
{
    return nil;
}
-(UIView*)webViewNavigationTitleView
{
    return nil;
}



-(BOOL)showBackButton
{
    return YES;
}
-(AliNavigationBackButton*)backButton
{
    if (!_backButton) {
        NSString *title = [self webViewBackButtonTitle];
        if (!title) {
            title = @"返回";
        }
        _backButton = [[AliNavigationBackButton alloc] initWithTitle:title];
        _backButton.navigationBackDelegate = self;
        
    }
    return _backButton;
}

-(void)dealloc
{
    [_backButton release];
//    [_mLoadingView release];
//    self.mLoadingView = nil;
    [super dealloc];
}
- (void)viewDidUnload {
    //[_backButton release];
    //_backButton = nil;
//    _mLoadingView = nil;
//    self.mLoadingView = nil;
    [super viewDidUnload];
}
-(void)viewDidLoad
{
    if ([self showBackButton]) {
        self.navigationItem.leftBarButtonItem = self.backButton;
    }
    
    self.view.backgroundColor =RGB(0xf0,0xf0,0xf0);
    UIView *titleView = [self webViewNavigationTitleView];
    if (titleView) {
        self.navigationItem.titleView = titleView;
    }
    else {
        self.navigationItem.title=[self webViewNavigationTitle];
    }
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_LOGOUT object:nil];
    [super viewDidLoad];
}

- (void) loginSucc
{  
   
    self.needReloadWebContent = YES;
}
- (void)loginOut
{
    self.needReloadWebContent = YES;    
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self configCookies];
}
-(void)viewDidAppear:(BOOL)animated
{
    self.needReloadWebContent = NO;    
}
- ( void )reloadWebview: (UIWebView*)webView  webViewUrl: (NSString *)stringUrl
{
    NSURL *url = [NSURL URLWithString:stringUrl];
    NSMutableURLRequest     *request;
   
    request = [[ NSMutableURLRequest alloc ] initWithURL: url ];
      /*
    
    NSDictionary *cookieProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                      @"m.1688.com", NSHTTPCookieDomain,
                                      @"\\", NSHTTPCookiePath,  
                                      @"_app_extra", NSHTTPCookieName,
                                      [self getExtraCookie], NSHTTPCookieValue,
                                                                            nil];
    NSHTTPCookie *cookie = [NSHTTPCookie cookieWithProperties:cookieProperties];
    NSArray* cookieArray = [NSArray arrayWithObjects: cookie, nil];
    NSDictionary * headers = [NSHTTPCookie requestHeaderFieldsWithCookies:cookieArray];
    [request setAllHTTPHeaderFields:headers];
    */
    
    [webView loadRequest: request ];
    [ request release ];
}
-(void)configCookies
{
    NSHTTPCookie *cookie;
    NSHTTPCookieStorage *storage = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for (cookie in [storage cookies]) {
        [storage deleteCookie:cookie];
    }
    [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookieAcceptPolicy:NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain];

    [self configExtraCookie ];
    [self configMemberIdCookie];
    [self configRefreshTokenCookie];
    [self configAccessTokenCookie];
   

}
-(void)configExtraCookie
{
    NSDictionary *cookieProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                      @"m.1688.com", NSHTTPCookieDomain,
                                      @"m.1688.com", NSHTTPCookieOriginURL,
                                      @"/", NSHTTPCookiePath,
                                      //[[NSDate date] dateByAddingTimeInterval:2629743], NSHTTPCookieExpires,
                                      //@"0", NSHTTPCookieVersion,
                                      @"_app_extra", NSHTTPCookieName,
                                      [self getExtraCookie], NSHTTPCookieValue,
                                      nil];
    
    NSHTTPCookie *cookie = [NSHTTPCookie cookieWithProperties:cookieProperties];
    [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:cookie];
    
}
-(void)configMemberIdCookie
{
    
    NSString *memberId=[LoginToken getLoginUserName];
    if (memberId&&[memberId length]>0)
    {
    NSDictionary *cookieProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                      @"m.1688.com", NSHTTPCookieDomain,
                                      @"m.1688.com", NSHTTPCookieOriginURL,
                                      @"/", NSHTTPCookiePath,
                                      @"_tmp_ck_m", NSHTTPCookieName,
                                      [self encrypte:memberId], NSHTTPCookieValue,
                                      nil];
    
    NSHTTPCookie *cookie = [NSHTTPCookie cookieWithProperties:cookieProperties];
    [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:cookie];
    }
}
-(void)configRefreshTokenCookie
{
    NSString *rToken=[LoginToken getRefreshToken];
    if (rToken&&[rToken length]>0)
    {
    NSDictionary *cookieProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                      @"m.1688.com", NSHTTPCookieDomain,
                                      @"m.1688.com", NSHTTPCookieOriginURL,
                                      @"/", NSHTTPCookiePath,
                                      @"_rtoken_", NSHTTPCookieName,
                                      [self encrypte:rToken], NSHTTPCookieValue,
                                      nil];
    
    NSHTTPCookie *cookie = [NSHTTPCookie cookieWithProperties:cookieProperties];
    [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:cookie];
    }
}
-(void)configAccessTokenCookie
{
    NSString *rToken=[LoginToken getAccessToken];
    if (rToken&&[rToken length]>0)
    {
    NSDictionary *cookieProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                      @"m.1688.com", NSHTTPCookieDomain,
                                      @"m.1688.com", NSHTTPCookieOriginURL,
                                      @"/", NSHTTPCookiePath,
                                      @"_atoken_", NSHTTPCookieName,
                                      [self encrypte:rToken], NSHTTPCookieValue,
                                      nil];
    
    NSHTTPCookie *cookie = [NSHTTPCookie cookieWithProperties:cookieProperties];
    [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:cookie];
    }
}


- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}
-(NSString*) getExtraCookie
{
    return [NSString stringWithFormat:@"%@|IOS|",[[UIDevice currentDevice] uniqueIdentifier]];
}
-(NSString*) getmemberId
{
    return @"";
}
-(void) endLoadingView
{
    
}
-(void) showLoadingView
{
    
}
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    //为了修复点击wap上日期会弹出呼叫对话框问题
    webView.dataDetectorTypes = UIDataDetectorTypeLink; 
    /*---------------------------------*/
    NSString* url = request.URL.absoluteString;
        if ([self checkLogin:url]) {
        [self endLoadingView];
        [AMLogUtils appendLog: FORUM_DETAIL_SEVEN];

        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;   
        [self.navigationController pushViewController:nextController animated:YES];
            [nextController release];
        return NO;
    }
    else if ([self checkOfferDetail:url])
    {
        [self gotoOfferDetail:url];
        return NO;
    }
    else if ([self checkCompanyDetail:url])
    {
        [self gotoCompanyDetail:url];
        return NO;
    }
    else if ([self checkNewsDetail:url])
    {
         [self gotoNewsDetail:url];
        
        return NO;
    }
    else if ([self checkOfferList:url])
    {
        [self gotoOfferList:url];
        return NO;
    }    
    else if ([self checkCompanyList:url])
    {
        [self gotoCompanyList:url];
        return NO;
    }    
    
    else{
     
        return YES;
    }

}
-(void)webViewDidStartLoad:(UIWebView *)webView
{

      
       [self showLoadingView];

}
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    
    NSString* url = webView.request.URL.absoluteString;
    
    if ([url isEqualToString:@"http://m.1688.com/touch/club/index/"]|| [self checkForumDetail:url]) {
        self.navigationItem.title=@"论坛";
    }
    else
    {
        self.navigationItem.title=[self webViewNavigationTitle];
    }
   [self endLoadingView];
}
-(BOOL)checkRegister:(NSString *)url
{

    NSString *DO_REGISTER_URL_PATTERN =  @"/touch/member/register";
    
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", DO_REGISTER_URL_PATTERN];
    
    return [emailTest evaluateWithObject:url];
    
}
-(BOOL)checkLogin:(NSString *)url
{
    
    NSString *DO_LOGIN_URL_PATTERN =  @"^\\S*/touch/member/login\\S*$";
    
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", DO_LOGIN_URL_PATTERN];
    
    return [emailTest evaluateWithObject:url];   
}
-(BOOL)checkCategoryList:(NSString *)url
{
    
    NSString *FORUM_CATEGORY_LIST =  @"http://m.1688.com/touch/club/cate/";
    
    NSRange range = [url rangeOfString:FORUM_CATEGORY_LIST]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(BOOL)checkCategoryDetail:(NSString *)url
{
    
    NSString *FORUM_CATEGORY_DETAIL =  @"/touch/club/list/";
    
    NSRange range = [url rangeOfString:FORUM_CATEGORY_DETAIL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(BOOL)checkForumDetail:(NSString *)url
{
    
    NSString *FORUM_DETAIL =  @"/touch/club/detail/";
    
    NSRange range = [url rangeOfString:FORUM_DETAIL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(BOOL)checkNewPage:(NSString *)url
{
    
    NSString *FORUM_NEW_PAGE =  @"/touch/club/new/";
    
    NSRange range = [url rangeOfString:FORUM_NEW_PAGE]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(BOOL)checkNewsDetail:(NSString *)url
{
    NSString *NEWS_DETAIL_URL =  @"touch/news/detail";
    
    NSRange range = [url rangeOfString:NEWS_DETAIL_URL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(BOOL)checkFourmDetail:(NSString *)url
{
    NSString *FORUM_DETAIL_URL =  @"/touch/club/detail/";
    
    NSRange range = [url rangeOfString:FORUM_DETAIL_URL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}


-(void)gotoNewsDetail:(NSString*)url
{
    NSString *newsId = [self getKeyValue:url key:@"id"];
    AMNewsDetailViewController *Controller = [[AMNewsDetailViewController alloc] initWithNibName:@"AMNewsDetailViewController" bundle:nil];
    Controller.hidesBottomBarWhenPushed=YES;
    
    NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
    [f setNumberStyle:NSNumberFormatterDecimalStyle];
    
    Controller.categoryId=[f numberFromString:newsId];
    [f release];
     
    [self.navigationController pushViewController:Controller animated:YES];
#warning 修改人孟希羲
    [Controller release];
}



-(BOOL)checkCompanyDetail:(NSString *)url
{
    
    NSString *COMPANY_DETAIL_URL =  @"touch/company/detail";
    
    NSRange range = [url rangeOfString:COMPANY_DETAIL_URL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(void)gotoCompanyDetail:(NSString*)url
{
    NSString *memberId = [self getKeyValue:url key:@"memberId"];
    
    AMCompanyTabViewController * companyTabViewController = [[AMCompanyTabViewController alloc] initWithMemberId:memberId companyName:nil preViewName:nil];
    [self.navigationController pushViewController:companyTabViewController animated:YES];
    [companyTabViewController release];

}
-(BOOL)checkCompanyList:(NSString *)url
{
    
    NSString *COMPANY_LIST_URL =  @"search/companylist";
    
    NSRange range = [url rangeOfString:COMPANY_LIST_URL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(void)gotoCompanyList:(NSString*)url
{
    
    
    NSString *keyWord = [self getKeyValue:url key:@"k"];
    keyWord = [keyWord stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    if (keyWord) {
        
        AMSearchCompanyViewController *Controller = [[AMSearchCompanyViewController alloc] initWithNibName:@"AMSearchCompanyViewController" bundle:nil];
        Controller.hidesBottomBarWhenPushed=YES;
        Controller.keyWords = keyWord;
        Controller.parentTitle = self.navigationItem.title;
        [self.navigationController pushViewController:Controller animated:YES];
        [Controller release];
    }
    else
    {
        NSString *kid = [self getKeyValue:url key:@"c"];
        NSString *cn = [self getKeyValue:url key:@"cn"];
        AMSearchCompanyViewController *sub = [[AMSearchCompanyViewController alloc] initWithNibName:@"AMSearchCompanyViewController" bundle:nil];
        
        sub.categoryId=kid;
        sub.parentTitle = cn;
        sub.parentTitle = self.navigationItem.title;
        sub.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:sub animated:YES];
        [sub release];
        
    }
}

-(BOOL)checkOfferDetail:(NSString *)url
{
    
    NSString *OFFER_DETAIL_URL =  @"touch/offer/detail";
    
    NSRange range = [url rangeOfString:OFFER_DETAIL_URL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(void)gotoOfferDetail:(NSString*)url
{
        
    NSString *ofid = [self getKeyValue:url key:@"ofid"];
    
    
    AMOfferTabViewController * controller = [[AMOfferTabViewController alloc] initWithOfferId:ofid offerName:nil preViewName:@"AliWebViewController"];
    
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES]; 
    [controller release];
}

-(BOOL)checkOfferList:(NSString *)url
{
    
    NSString *OFFER_LIST_URL =  @"search/offerlist";
    
    NSRange range = [url rangeOfString:OFFER_LIST_URL]; 
    if (range.length>0) {
        return YES;
    }
    else {
        return NO;
    }
}
-(void)gotoOfferList:(NSString*)url
{
    
    
    NSString *keyWord = [self getKeyValue:url key:@"k"];
    keyWord = [keyWord stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    if (keyWord) {
        
        AMOfferListViewController *Controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
        Controller.hidesBottomBarWhenPushed=YES;
        Controller.keyWords = keyWord;
          Controller.parentTitle = self.navigationItem.title;
        [self.navigationController pushViewController:Controller animated:YES];
        [Controller release];
    }
    else
    {
        NSString *kid = [self getKeyValue:url key:@"c"];
        NSString *cn = [self getKeyValue:url key:@"cn"];
        AMSubCategoryViewController *sub = [[AMSubCategoryViewController alloc] initWithNibName:@"AMSubCategoryViewController" bundle:nil];
        
        sub.categoryId=kid;
        sub.navigationTitle = cn;
        sub.parentTitle = self.navigationItem.title;
        sub.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:sub animated:YES];
        [sub release];

    }
}

-(NSString*)getKeyValue:(NSString*)url key:(NSString*)key{
    
    NSString *subString = url;
    
    while (1) {
        
        NSRange range= [subString rangeOfString:@"/"]; 
        if (range.length>0)
        {
            
            subString = [subString substringFromIndex: range.location+1];
        }
        else {
            break;
        }
    } 
    NSRange range= [subString rangeOfString:@"."]; 

    subString = [subString substringToIndex: range.location];
    NSArray* paramPairs = [subString componentsSeparatedByString:@"_"];
  //  NSMutableDictionary *dic = [[NSMutableDictionary alloc]init];
    for (NSString *item in paramPairs) {
        NSArray* itemPairs = [item componentsSeparatedByString:@"-"];
        if ([[itemPairs objectAtIndex:0] isEqualToString:key]) {
            return [itemPairs objectAtIndex:1];
        }
       // [dic setObject:[itemPairs objectAtIndex:1] forKey:[itemPairs objectAtIndex:0]];
    }
    return nil;
}

-(BOOL)needReloadView
{
    return self.needReloadWebContent;
}
-(NSString*)encrypte:(NSString*)src
{
    NSDate *date = [[NSDate alloc]init];
    
    NSString *rawData = [NSString stringWithFormat:@"%@#%.0f000",src,[date timeIntervalSince1970]];
    [date release];
    return [AliDesEncode encode:rawData];
}
@end

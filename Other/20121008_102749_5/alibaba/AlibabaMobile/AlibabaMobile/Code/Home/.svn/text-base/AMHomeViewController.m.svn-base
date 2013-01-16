//
//  AMHomeViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import "AMHomeViewController.h"
#import "AMContentRequest.h"
#import "AMHomeContent.h"
#import "ConstDef.h"

#import "AMNewsViewController.h"
#import "AMMarketpriceViewController.h"
#import "AMCategoryViewController.h"
#import "AMSingleLineWithIconCell.h"
#import "AMSearchCompanyViewController.h"
#import "AMOfferListViewController.h"
#import "AMSearchPriceViewController.h"
#import "AMSearchResultData.h"
#import "ImageMagazineDetailViewController.h"
#import "ImageMagazineCategoryViewController.h"
#import "MessageCenterButtonView.h"
#import "AMIMViewController.h"
#import "MessageCenterListViewController.h"
#import "LoginToken.h"
#import "AMAppDelegate.h"
#import "UIHelp.h"
#import "AMBannerContentDetailViewController.h"
#import "AMIMCoreDataHelper.h"
#import "AMLogUtils.h"
#import "searchViewDef.h"
#import "AMHotRankViewController.h"
#import "AMHotRankOfferViewController.h"
#import "AMNewProductsCategoryViewController.h"

#import "AliBannerTableViewCell.h"
#import "AliOperationTableViewCell.h"
#import "AliChannelTableViewCell.h"
#import "AliChannelCellBlock.h"
NSInteger const HOME_LISTITEM_NEWS = 0;
NSInteger const HOME_LISTITEM_QUOTATIONS = 1;
NSInteger const HOME_LISTITEM_CATEGORIES = 2;
NSInteger const HOME_LISTITEM_MAGAZINE = 3;
NSInteger const HOME_LISTITEM_HOTRANK = 4;//热销排行-->add by xiaowen
NSInteger const HOME_LISTITEM_NEWPRODUCTS = 5;//新品专区-->add by xiaowen


@interface AMHomeViewController()
@property (nonatomic,retain) NSMutableArray *tableListControllers;
@property (nonatomic,retain)AliChannel *channel;
@property (nonatomic,retain) AliAdvView *bannerView;
@property (nonatomic,retain) AliOperation1 *operation1;
@property (nonatomic,retain) AliOperation2 *operation2;


@end

@implementation AMHomeViewController
@synthesize channel=_channel;
@synthesize bannerView=_bannerView;
@synthesize operation1=_operation1;
@synthesize operation2=_operation2;
@synthesize observer = _observer;
@synthesize searchView = _searchView;

@synthesize tableListControllers=_tableListControllers;

@synthesize funcListTable = _funcListTable;

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_observer release];  
    [_channel release];
    [_tableListControllers release];
    
    [_operation1 release];
    [_operation2 release];
    [_funcListTable release];
    [_searchView release];
    [_bannerView release];
    [super dealloc];
}

-(AliChannel*)channel
{
    if (!_channel) {
        _channel = [[AliChannel alloc]init];
    }
    return _channel;
}

-(UIViewController*)superController
{
    return self;
}
-(NSString*)superControllerName
{
    return @"首页";
}

-(void)searchBarEditViewEditBegin:(AliSearchView*)searchBarView
{
//    [self.navigationController setNavigationBarHidden:YES animated:YES];
     [self.navigationController setNavigationBarHidden:NO animated:YES];
}

-(void)searchBarEditViewDidEnd:(AliSearchView *)searchView content:(NSString *)content selected:(NSUInteger)selected
{
    [AMLogUtils appendLog:APP_HOME_PAGE_FOUR];

    switch (selected) {
        case SEARCH_COMPANY:
        {
            AMSearchCompanyViewController *Controller = [[AMSearchCompanyViewController alloc] initWithNibName:@"AMSearchCompanyViewController" bundle:nil];
            Controller.keyWords = content;
            Controller.parentTitle = @"搜索";
            Controller.hidesBottomBarWhenPushed=YES;   
            [self.navigationController pushViewController:Controller animated:YES];
            [Controller release];
        }
            break;
        case SEARCH_PRICE:
        {
            AMSearchPriceViewController *Controller = [[AMSearchPriceViewController alloc] initWithNibName:@"AMSearchPriceViewController" bundle:nil];
            Controller.keyWords=content;
            Controller.hidesBottomBarWhenPushed=YES;
            Controller.parentTitle = @"搜索";
            [self.navigationController pushViewController:Controller animated:YES];   
            [Controller release];
        }
            break;
        case SEARCH_PRODUCT:   
        default:
        {
            AMOfferListViewController *Controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
            Controller.keyWords = content;
            Controller.parentTitle = @"搜索";
            Controller.hidesBottomBarWhenPushed=YES;
            [self.navigationController pushViewController:Controller animated:YES];
            [Controller release];
        }
            
            break;
    }
    
}
-(void)searchBarEditCancel:(AliSearchView*)searchBarView
{
    [self.navigationController setNavigationBarHidden:NO animated:YES];
}

-(void)scroolViewContendLoad
{
    if ([self.bannerView.bannerData count]==0) {
        [self.bannerView loadObjectsFromRemote];
    }
    if ([self.operation1.contentData count]==0) {
        [self.operation1 loadObjectsFromRemote];
    }
    if ([self.operation2.contentData count]==0) {
        [self.operation2 loadObjectsFromRemote];
    }
    if ([self.channel.contentData count]==0) {
        [self.channel loadObjectsFromRemote];
    }
    
}
- (void)reachabilityChanged:(NSNotification *)notification {
    RKReachabilityObserver* observer = (RKReachabilityObserver *) [notification object];
    
    RKLogCritical(@"AMHomeViewController - Received reachability update: %@", observer);
    
    if ([observer isNetworkReachable]) {
        if ([observer isConnectionRequired]) {
            return;
        }            
        
        if (RKReachabilityReachableViaWiFi == [observer networkStatus]) {
            // Online via WiFi
            NSLog(@"Online via WiFi...");
            
        } else if (RKReachabilityReachableViaWWAN == [observer networkStatus]) {
            // Online via 3G or Edge
            NSLog(@"Online via 3G or Edge...");
        }
        
        [self performSelectorOnMainThread:@selector(scroolViewContendLoad) withObject:self waitUntilDone:NO];
    } else {
        // Network unreachable!
        NSLog(@"Network unreachable!");
    }
}




- (void)viewDidUnload {

    //self.tableListControllers=nil;
    //_tableListControllers = nil;
    //[_observer release];
    //_channel = nil;
    /*
    UIView *searchPick =(UIView *)[self.view viewWithTag:11];
    UIView *searchHistory =(UIView *)[self.view viewWithTag:12]; 
    if (searchPick) {
        [searchPick removeFromSuperview];
    }
    if (searchHistory) {
       [searchHistory removeFromSuperview];
    }
     */
    self.searchView.delegate = nil;
    _searchView = nil;
    _funcListTable = nil;
    self.bannerView = nil;
    self.operation1 = nil;
    self.operation2 = nil;
    [_channel release];
    _channel = nil;
    
    self.observer = nil;
    //_bannerView = nil;

    //self.observer = nil;

    [super viewDidUnload];
    
}

- (void)viewWillAppear:(BOOL)animated
{
    self.navigationController.navigationBar.hidden = NO;
    [self.view bringSubviewToFront:self.searchView];
   
}

-(void)viewWillDisappear:(BOOL)animated
{

    [super viewWillDisappear:animated];
    [self.navigationController setNavigationBarHidden:NO animated:YES];

}
- (void)viewDidLoad
{
    self.searchView.delegate = self;
    self.channel.delegate = self;
    self.channel.coltrollerDelegate = self;
    [self.channel loadObjectsFromRemote];
    
    [super viewDidLoad];
    
    self.observer = [[RKReachabilityObserver alloc] initWithHost:AMCONST_HOST];	
    
    // Register for notifications
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reachabilityChanged:)
                                                 name:RKReachabilityDidChangeNotification
                                               object:_observer];
    
}


#pragma  synthesize start
-(NSMutableArray*)tableListControllers
{
    if (_tableListControllers==nil) {
        _tableListControllers = [[NSMutableArray alloc] init];
        
        // Hot news
        AMNewsViewController *newsListController  = [[AMNewsViewController alloc] initWithNibName:@"AMNewsViewController" bundle:nil];
        newsListController.parentTitle = @"首页";

        [_tableListControllers insertObject:newsListController atIndex: HOME_LISTITEM_NEWS];
        [newsListController release];
        
        // Price quotations
        AMMarketpriceViewController *marketpriceListController  = [[AMMarketpriceViewController alloc] initWithNibName:@"AMMarketpriceViewController" bundle:nil];
        marketpriceListController.parentTitle = @"首页";

        [_tableListControllers insertObject:marketpriceListController atIndex:HOME_LISTITEM_QUOTATIONS];
        [marketpriceListController release];
        
        // Browse offers by categories
        AMCategoryViewController *categoryListController  = [[AMCategoryViewController alloc] initWithNibName:@"AMCategoryViewController" bundle:nil];
        categoryListController.parentTitle = @"首页";

        [_tableListControllers insertObject:categoryListController atIndex:HOME_LISTITEM_CATEGORIES];
        [categoryListController release];
        
        // Pictorials
        ImageMagazineCategoryViewController *imageMagazineCategoryViewController = [[ImageMagazineCategoryViewController alloc] init];
        imageMagazineCategoryViewController.parentTitle = @"首页";
        [_tableListControllers insertObject:imageMagazineCategoryViewController atIndex:HOME_LISTITEM_MAGAZINE];
        [imageMagazineCategoryViewController release];
        
        //热销排行
        
        AMHotRankViewController *hotRankViewController = [[AMHotRankViewController alloc] initWithNibName:@"AMHotRankViewController" bundle:nil];
        hotRankViewController.parentTitle = @"首页";
        [_tableListControllers insertObject:hotRankViewController atIndex:HOME_LISTITEM_HOTRANK];
        [hotRankViewController release];
        
        //新品专区
        
        AMNewProductsCategoryViewController *newProductsCategoryViewController = [[AMNewProductsCategoryViewController alloc] initWithNibName:@"AMNewProductsCategoryViewController" bundle:nil];
        newProductsCategoryViewController.parentTitle = @"首页";
        [_tableListControllers insertObject:newProductsCategoryViewController atIndex:HOME_LISTITEM_NEWPRODUCTS];
        [newProductsCategoryViewController release];
    }
    
    return _tableListControllers;
}
#pragma  synthesize end



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.navigationItem.title=NSLocalizedString(@"HomeTitle", @"");
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_home"];        
        self.tabBarItem.title=NSLocalizedString(@"HomeTitle", @"");
        
        UIImageView * logoImageView = [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"logo_topbar"]];
        self.navigationItem.titleView = logoImageView;
        [logoImageView release];
        
         
        MessageCenterButtonView * msgButton;
        NSString *loginUserName=nil;
        loginUserName=[LoginToken getLoginUserName];
        if([loginUserName length] > 3){
            AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
            msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:[appDelegate getUnReadMsgNum]];
            
        }else{
            msgButton = [[MessageCenterButtonView alloc] initWithState:NO num:0];
        }
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_RECV object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_READ object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(gotoMessageCenter) name:NOTIFICATION_MSG_GOTO_MESSAGE_CENTER object:nil];
        
//        [msgButton changeLoginState:NO];
        [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
        [msgButton release];
        
        self.navigationItem.rightBarButtonItem = rightItem;
        [rightItem release];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginOut) name:NOTIFICATION_LOGOUT object:nil];
        
    }
    return self;
}

- (void)loginOut
{
    self.navigationItem.rightBarButtonItem = nil;
    MessageCenterButtonView *msgButton = [[MessageCenterButtonView alloc] initWithState:NO num:0];    //    [msgButton setMsgNum:0];
    //    [msgButton changeLoginState:YES];
    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];
    //修改人 孟希羲
    [msgButton release];
}

- (void)gotoMessageCenter {
    // Add log trace point here
    [AMLogUtils appendLog: APP_HOME_PAGE_SIX];
    
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){ 
        [self openMsgList];
    }else{
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;   
        [self.navigationController pushViewController:nextController animated:YES];            
    } 
}

- (IBAction)msgBtnAction:(id)sender
{
    [self gotoMessageCenter];
}

- (void) recvNewMsg
{
    NSString * loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){  
        AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        
       int newMsgNum =  [appDelegate getUnReadMsgNum];
        self.navigationItem.rightBarButtonItem = nil;
        MessageCenterButtonView * msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:newMsgNum];
//        [msgButton changeLoginState:YES];
//        [msgButton setMsgNum:newMsgNum];
        [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
        
        self.navigationItem.rightBarButtonItem = rightItem;
        [rightItem release];
        [msgButton release];
    }
}

- (void) loginSucc
{  
    self.navigationItem.rightBarButtonItem = nil;
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    
    int newMsgNum =  [appDelegate getUnReadMsgNum];
    MessageCenterButtonView * msgButton = [[MessageCenterButtonView alloc] initWithState:YES num:newMsgNum];

    [msgButton addTarget:self action:@selector(msgBtnAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem  * rightItem = [[UIBarButtonItem alloc]  initWithCustomView:msgButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    [rightItem release];
    [msgButton release];
}

-(void)openMsgList{
    MessageCenterListViewController * msgViewController = [[MessageCenterListViewController alloc] init];
    msgViewController.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:msgViewController animated: YES];
    [msgViewController release];
}

#pragma  scroll end

#pragma mark Table View Data Source Methods

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    switch (row) {
        case 0:
            return [AliBannerTableViewCell cellHeight];
            break;
        case 1:
            return [AliOperationTableViewCell cellHeight];
            break;    
        default:
            return [AliChannelTableViewCell cellHeight];

            break;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section
{
    NSUInteger count = [self.channel.contentData count]/2;
    if ([self.channel.contentData count]%2) {
        count+=1;
    }
    return 2+count;
}
-(void)operationTouchUp:(id)sender
{
    if ([sender isKindOfClass:[AliOperation2 class]]) {
        if([self.operation2.contentData count]){
            AMHomeContent *operation2Content = [self.operation2.contentData objectAtIndex:0];
            NSString *operation2ClickId = operation2Content.clickId;
            [AMLogUtils appendLog: operation2ClickId];
            AMHotRankViewController *hotRankViewController =[[AMHotRankViewController alloc] initWithNibName:@"AMHotRankViewController" bundle:nil];
            hotRankViewController.parentTitle = @"首页";
            [self.navigationController pushViewController:hotRankViewController animated:YES];
            [hotRankViewController release];
        }
    }
    else {
        if([self.operation1.contentData count]){
            AMHomeContent *operation1Content = [self.operation1.contentData objectAtIndex:0];
            NSString *operation1ClickId = operation1Content.clickId;
            [AMLogUtils appendLog: operation1ClickId];
            AMNewProductsCategoryViewController *newProductsCategoryViewController = [[AMNewProductsCategoryViewController alloc] initWithNibName:@"AMNewProductsCategoryViewController" bundle:nil];
            newProductsCategoryViewController.parentTitle = @"首页";
            [self.navigationController pushViewController:newProductsCategoryViewController animated:YES];
            [newProductsCategoryViewController release];
        }
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
 
    
    NSUInteger row = [indexPath row];
    
    
    switch (row) {
        case 0:
        {
            AliBannerTableViewCell *cell = (AliBannerTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AliBannerTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AliBannerTableViewCell createCell];
                cell.bannerView.delegate = self;
                self.bannerView = cell.bannerView;
            }   
            return cell;

        }
            break;
        case 1:
        {
            AliOperationTableViewCell *cell = (AliOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AliOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AliOperationTableViewCell createCell];
                self.operation1 = cell.operation1;
                self.operation2 = cell.operation2;
               
            }   
            
            [cell.operation1 addTarget:self action:@selector(operationTouchUp:)  forControlEvents:UIControlEventTouchUpInside];           
            [cell.operation2 addTarget:self action:@selector(operationTouchUp:) forControlEvents:UIControlEventTouchDown];
            return cell;
            
        }
            break;
        default:
        {
            AliChannelTableViewCell *cell = (AliChannelTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AliChannelTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AliChannelTableViewCell createCell];
            }   
            NSUInteger index = (row -2)*2;
           // AMHomeContent *data = [self.channel.contentData objectAtIndex:index];
            cell.cellBlock1.title.text = [self.channel getTitle:index];// data.operationDesc;
            cell.cellBlock1.tag = index;
            [cell.cellBlock1 addTarget:self action:@selector(blockUpAction:)  forControlEvents:UIControlEventTouchUpInside];    
            [cell.cellBlock1 addTarget:self action:@selector(blockDownAction:) forControlEvents:UIControlEventTouchDown];   
            [cell.cellBlock1 addTarget:self action:@selector(blockUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside]; 
            index++;
            if (index>=[self.channel.contentData count]) {
                cell.cellBlock2.hidden = YES;
            }
            else {
                cell.cellBlock2.hidden = NO;
               // AMHomeContent *data2 = [self.channel.contentData objectAtIndex:index];
                cell.cellBlock2.title.text = [self.channel getTitle:index];//data2.operationDesc;

                [cell.cellBlock2 addTarget:self action:@selector(blockUpAction:)  forControlEvents:UIControlEventTouchUpInside];    
                [cell.cellBlock2 addTarget:self action:@selector(blockDownAction:) forControlEvents:UIControlEventTouchDown];   
                [cell.cellBlock2 addTarget:self action:@selector(blockUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside]; 
                cell.cellBlock2.tag = index;

            }
            return cell;
        }
            break;
    }
    
    return nil;

}
-(void)blockDownAction:(AliChannelCellBlock*)sender
{
    sender.backgroundColor = RGB(0xe1, 0xe1, 0xe1);
}
-(void)blockUpAction:(AliChannelCellBlock*)sender
{
  //  NSDictionary *data = [self.blockBoxData objectAtIndex:sender.tag]; 
   // [self performSelector:NSSelectorFromString([data objectForKey:DATD_KEYWORD_SELECTOR])];
    [self.channel doSelector:sender.tag];
    sender.backgroundColor = [UIColor clearColor]; 
}

-(void)blockUpOutsideAction:(AliChannelCellBlock*)sender
{
    sender.backgroundColor = [UIColor clearColor];
}


-(void)AliChannelReloadData
{
    [self.funcListTable reloadData];
}
#pragma mark Table View Data Source Methods end

#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
        NSUInteger row = [indexPath row];
    switch (row) {
        case 0:
            
            break;
            
        default:
            break;
    }
/*
        UIViewController *nextController = [self.tableListControllers objectAtIndex:row];
        nextController.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:nextController animated:YES];
        
        // begin to add log trace point here
        switch (row) {
            case HOME_LISTITEM_NEWS:
                [AMLogUtils appendLog: APP_HOME_PAGE_SEVEN];
                break;
                
            case HOME_LISTITEM_QUOTATIONS:
                [AMLogUtils appendLog: APP_HOME_PAGE_EIGHT];
                break;
                
            case HOME_LISTITEM_CATEGORIES:
                [AMLogUtils appendLog: APP_HOME_PAGE_NINE];
                break;
                
            case HOME_LISTITEM_MAGAZINE:
                [AMLogUtils appendLog: APP_HOME_PAGE_TEN];
                break;
                
            default:
                break;
        }

    [self.funcListTable deselectRowAtIndexPath:indexPath animated:NO];*/
}

@end

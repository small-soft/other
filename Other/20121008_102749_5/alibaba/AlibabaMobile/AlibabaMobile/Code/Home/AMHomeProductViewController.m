//
//  AMHomeProductViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-28.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomeProductViewController.h"
#import "AMBannerTableViewCell.h"
#import "AliOperationTableViewCell.h"
#import "AMHotRankViewController.h"
#import "AMHotRankOfferViewController.h"
#import "AMNewProductsCategoryViewController.h"
#import "AMNewsViewController.h"
#import "AMMarketpriceViewController.h"
#import "AMCategoryViewController.h"
#import "AMSingleLineWithIconCell.h"
#import "AMSearchCompanyViewController.h"
#import "AMOfferListViewController.h"
#import "AMContentRequest.h"
#import "AMHomepageDressResult.h"
#import "AMHomepageDressEvent1Result.h"
#import "AMHomepageDressRequest.h"
#import "AMHomeContent.h"
#import "ImageMagazineCategoryViewController.h"
#import "AMIndustrySelectHomeViewController.h"
#import "AMOperationView.h"
#import "AMOperationTableViewCell.h"
#import "AMChannelTableViewCell.h"
#import "AMMenuView.h"
#import "AMAdvView.h"
#import "AMChannel.h"
#import "AMOperationItemView.h"
#import "AMOperationItemView2.h"
#import "AMActivityDetailViewController.h"
#import "Utils.h"

#import "AMSubpageWithMenuViewController.h"

#import "AMBeginerNavigateViewControl.h"
@interface AMHomeProductViewController ()
@property (nonatomic,retain) AMChannel      *channelView;
@property (nonatomic,retain) AMMenuView     *menuView;
@property (nonatomic,retain) AMAdvView      *bannerView;
@property (nonatomic,retain) AMOperationView*operationView;
@property (nonatomic,retain) AliOperation1  *operation1;
@property (nonatomic,retain) AliOperation2  *operation2;
@property (nonatomic,retain) AMOperationItemView *operationItemView1;
@property (nonatomic,retain) AMOperationItemView *operationItemView2;
@property (nonatomic,retain) AMOperationItemView2 *operationItemView;

@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) HJObjManager *objMan;
@end

@implementation AMHomeProductViewController
@synthesize channelView = _channelView;
@synthesize bannerView=_bannerView;
@synthesize operationView = _operationView;
@synthesize operation1=_operation1;
@synthesize operation2=_operation2;
@synthesize menuView = _menuView;
@synthesize contentData = _contentData;
@synthesize objMan = _objMan;
@synthesize operationItemView1 = _operationItemView1;
@synthesize operationItemView2 = _operationItemView2;
@synthesize operationItemView = _operationItemView;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    [self changePickFrame:7 yframe:0];
    UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"bg_topbar_black"]];
    self.navBgImgeView  =  imageViewTmp;
    [imageViewTmp release];
    
//    [self.industrySelectPickView.mSelectTypeButtonUp setImage:[UIImage imageNamed:@"h_com_drop01_nor"] forState:UIControlStateNormal];
//    [self.industrySelectPickView.mSelectTypeButtonDown setImage:[UIImage imageNamed:@"h_com_drop_nor"] forState:UIControlStateNormal];
//    self.industrySelectPickView.mSelectTypeButtonUp.hidden = YES;
    
    //调用本地信息，不再调用服务器数据
//    self.channelView = [[AMChannel alloc] init];
//    self.channelView.request.industryId = AMCONST_HOME_COMMODITY;
//    self.channelView.request.summary    = AMCONST_HOME_SUMMARY;
//    self.channelView.request.configName = AMCONST_HOME_CATEGORIES;
//    self.channelView.delegate = self;
//    [self.channelView loadObjectsFromRemote];
    
}

- (void)viewDidUnload
{
    self.channelView = nil;
    self.operationView = nil;
    self.operation1 = nil;
    self.operation2 = nil;
    self.menuView = nil;
    self.bannerView = nil;
    self.contentData = nil;
    self.objMan = nil;
    self.operationItemView1 = nil;
    self.operationItemView2 = nil;
    self.operationItemView = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [UserDataUtils setNavigationHomeBar:YES];
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"h_com_navbar"] forBarMetrics:UIBarMetricsDefault];
//        [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"com_navbar"] forBarMetrics:UIBarMetricsDefault];
    }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"h_com_navbar"].CGImage;
    }
    
    //self.navigationController.navigationBar.backgroundColor = [UIColor clearColor]; 
    
    self.navigationController.navigationBar.hidden = NO;
    
}

-(void)viewDidAppear:(BOOL)animated
{
}

-(void)viewWillDisappear:(BOOL)animated
{
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"bg_topbar"] forBarMetrics:UIBarMetricsDefault];
    }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"bg_topbar"].CGImage;
    }

    [super viewWillDisappear:animated];
    [self.navigationController setNavigationBarHidden:NO animated:YES];
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_channelView release];
    [_operationView release];
    [_operation1 release];
    [_operation2 release];
    [_bannerView release];
    [_menuView release];
    [_contentData release];
    [_objMan release];
    [_operationItemView1 release];
    [_operationItemView2 release];
    [_operationItemView release];
    
    [super dealloc];
}
#pragma mark setmethod

-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [Utils createObjManagerDefault];
    }
    return _objMan;
    
}

-(NSArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc] init];
        for (NSDictionary *data in self.sourceData) {
            AMMenuItemView *menuItemViewTmp = [[AMMenuItemView alloc] init];
            menuItemViewTmp.label.text = [data objectForKey:@"name"];
            [menuItemViewTmp.imageView clear];
            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x, menuItemViewTmp.imageView.frame.origin.y + 4, menuItemViewTmp.imageView.frame.size.width, 50);
//            menuItemViewTmp.imageViewBackground.image = [UIImage imageNamed:[data objectForKey:@"imageName"]];
            menuItemViewTmp.imageView.image = [UIImage imageNamed:[data objectForKey:@"imageName"]];
            [menuItemViewTmp setLabelyPadding:-10 xPadding:0];
            menuItemViewTmp.label.font = [UIFont fontWithName:@"Arial-BoldMT" size:14.0f];
            menuItemViewTmp.label.textColor = [UIHelp colorWithHexString:@"0x333333"];
            menuItemViewTmp.button.adjustsImageWhenHighlighted = YES;
            menuItemViewTmp.layer.masksToBounds=YES;   
            //    menuItemView.layer.cornerRadius=1.0;   
            menuItemViewTmp.layer.borderWidth=0.5;   
            menuItemViewTmp.layer.borderColor=[[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor]; 
            

            //menuItemViewTmp.imageView.mode = UIViewContentModeScaleToFill;
//            [self.objMan manage:menuItemViewTmp.imageView];
            NSDictionary *viewMapping = [NSDictionary dictionaryWithObjectsAndKeys:menuItemViewTmp, @"view",nil];
            [_contentData addObject:viewMapping];
            [menuItemViewTmp release];
        }
    }
    return _contentData;
}

-(NSArray*)sourceData
{
    if (!_sourceData) {
        _sourceData = [[NSArray alloc]initWithObjects:
                       [NSDictionary dictionaryWithObjectsAndKeys:@"玩具", @"name",@"wanju", @"ID",@"h_com_list01", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"礼品", @"name",@"lipin", @"ID",@"h_com_list02", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"饰品", @"name",@"shipin", @"ID",@"h_com_list03", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"办公文教", @"name",@"bangongwenjiao", @"ID",@"h_com_list04", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"3C数码", @"name",@"3cshuma", @"ID",@"h_com_list05", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"汽车用品", @"name",@"qicheyongpin", @"ID",@"h_com_list06", @"imageName",nil],nil];

    }
    return _sourceData;
}

#pragma mark restkit received update
- (void)reachabilityChanged:(NSNotification *)notification {
    RKReachabilityObserver* observer = (RKReachabilityObserver *) [notification object];
    
    RKLogCritical(@"AMHomeBaseViewController - Received reachability update: %@", observer);
    
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
        if([self isViewLoaded]){
            [self performSelectorOnMainThread:@selector(scrolViewContendLoad) withObject:self waitUntilDone:NO];
        }
    } else {
        // Network unreachable!
        NSLog(@"Network unreachable!");
    }
}

-(void) scrolViewContendLoad
{
    if ([self.bannerView.bannerData count]==0) {
        self.bannerView.request.industryId = AMCONST_HOME_COMMODITY;
        self.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
        self.bannerView.request.configName = AMCONST_HOME_BANNERS;
        [self.bannerView loadObjectsFromRemote];
    }
    if ([self.operationView.contentData count] == 0) {
        self.operationView.request.industryId = AMCONST_HOME_COMMODITY;
        self.operationView.request.summary    = AMCONST_HOME_SUMMARY;
        self.operationView.request.configName = AMCONST_HOME_EVENT1;
        self.operationView.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT1_LIST;
        [self.operationView loadObjectsFromRemote];
    }
    if ([self.operation1.contentData count]==0) {
        self.operation1.request.industryId = AMCONST_HOME_COMMODITY;
        self.operation1.request.summary    = AMCONST_HOME_SUMMARY;
        self.operation1.request.configName = AMCONST_HOME_EVENT2;
        self.operation1.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT2_LIST;
        [self.operation1 loadObjectsFromRemote];
    }
    if ([self.operation2.contentData count]==0) {
        self.operation2.request.industryId = AMCONST_HOME_COMMODITY;
        self.operation2.request.summary    = AMCONST_HOME_SUMMARY;
        self.operation2.request.configName = AMCONST_HOME_EVENT3;
        self.operation2.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT3_LIST;
        [self.operation2 loadObjectsFromRemote];
    }
//    if ([self.channelView.contentData count]==0) {
//        [self.channelView loadObjectsFromRemote];
//    }
}

#pragma mark Home Common Methods
-(NSString*)commonHomeViewBackButtonTitle
{
    return @"小商品";
}

#pragma mark Table View Data Source Methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    switch (row) {
        case 0:
            return [AMBannerTableViewCell cellHeight];
            break;
        case 1:
            return AMCONST_HOME_COMMODITY_OPERATIONEVENT1_HEIGHT;
            break;
        case 2:
            return AMCONST_HOME_COMMODITY_OPERATION_HEIGHT;
            break;  
        default:
            return AMCONST_HOME_COMMODITY_CHANNEL_HEIGHT * menuViewCount;
            
            break;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section
{
    //    NSUInteger count = [self.channel.contentData count]/2;
    //    if ([self.channel.contentData count]%2) {
    //        count+=1;
    //    }
//    menuViewCount = [self.channelView.contentData count]/AMCONST_HOME_COMMODITY_MENUVIEW_COLUMNE;
//    if ([self.channelView.contentData count]%AMCONST_HOME_COMMODITY_MENUVIEW_COLUMNE) {
//        menuViewCount+=1;
//    }
    menuViewCount = 2;
    return 4;
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
    NSUInteger row = [indexPath row];
    
    
    switch (row) {
        case 0:
        {
            AMBannerTableViewCell *cell = (AMBannerTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMBannerTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMBannerTableViewCell createCell];
                cell.bannerView.delegate = self;
                self.bannerView = cell.bannerView;
                cell.bannerView.request.industryId = AMCONST_HOME_COMMODITY;
                cell.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.bannerView.request.configName = AMCONST_HOME_BANNERS;
                
                [cell.bannerView loadObjectsFromRemote];

            }   
            cell.backgroundColor = [UIColor clearColor];
            cell.layer.borderWidth = 0;
            return cell;
            
        }
            break;
        case 1:
        {
            AMOperationTableViewCell *cell = (AMOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMOperationTableViewCell createCell];
                //调整cell位置大小以及两个operation的位置尺寸
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_COMMODITY_OPERATIONEVENT1_HEIGHT);
                cell.operationView.frame = CGRectMake(cell.operationView.frame.origin.x, cell.operationView.frame.origin.y, cell.operationView.frame.size.width, AMCONST_HOME_COMMODITY_OPERATIONEVENT1_HEIGHT);
                self.operationView = cell.operationView;
                //网络申请数据
                cell.operationView.request.industryId = AMCONST_HOME_COMMODITY;
                cell.operationView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operationView.request.configName = AMCONST_HOME_EVENT1;
                [cell.operationView loadObjectsFromRemote];
                
                //加载AMOperationItemView2 用于展示今天特价
                AMOperationItemView2 *operationItemView = [[AMOperationItemView2 alloc] init];
                operationItemView.backgroundColor = [UIHelp colorWithHexString:@"0xF9F9F9"];
                operationItemView.imageView1.image = [UIImage imageNamed:@"h_com_tejia"];
                operationItemView.imageView2.image = [UIImage imageNamed:@"h_com_tj_banner"];
                [operationItemView addTarget:self action:@selector(operationViewEvent1TouchUp:)  forControlEvents:UIControlEventTouchUpInside]; 
                [operationItemView addTarget:self action:@selector(blockDownAction:) forControlEvents:UIControlEventTouchDown];   
                [operationItemView addTarget:self action:@selector(blockUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside]; 
                [cell.operationView setHideImageUrl:YES];
                [cell.operationView addSubview:operationItemView];
                self.operationItemView = operationItemView;
                [operationItemView release];
                
            }   
            cell.backgroundColor = [UIColor clearColor];
            cell.layer.borderWidth = 0;
            return cell;
        }
            break;
        case 2:
        {
            AliOperationTableViewCell *cell = (AliOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AliOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AliOperationTableViewCell createCell];
                //调整cell位置大小以及两个operation的位置尺寸
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_COMMODITY_OPERATION_HEIGHT);        
                cell.operation1.frame= CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width/2, cell.frame.size.height);
                cell.operation2.frame= CGRectMake(cell.frame.origin.x + cell.frame.size.width/2, cell.frame.origin.y, cell.frame.size.width/2, cell.frame.size.height);
                self.operation1 = cell.operation1;
                self.operation2 = cell.operation2;
                //网络申请数据
                cell.operation1.request.industryId = AMCONST_HOME_COMMODITY;
                cell.operation1.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operation1.request.configName = AMCONST_HOME_EVENT2;         
                cell.operation2.request.industryId = AMCONST_HOME_COMMODITY;
                cell.operation2.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operation2.request.configName = AMCONST_HOME_EVENT3;           
                [cell.operation1 loadObjectsFromRemote];
                [cell.operation2 loadObjectsFromRemote];
                cell.operation1.delegate = self;
                cell.operation2.delegate = self;
                //隐藏背景图片
                cell.operation1.defaultImage.image = nil;
                cell.operation2.defaultImage.image = nil;
                [cell.operation1 setHideImageUrl:YES];
                [cell.operation2 setHideImageUrl:YES];
                //加载特殊格式图片
                AMOperationItemView *operationItemView1 = [[AMOperationItemView alloc] init];
                AMOperationItemView *operationItemView2 = [[AMOperationItemView alloc] init];
                operationItemView1.backgroundColor = [UIHelp colorWithHexString:@"0xF9F9F9"];
                operationItemView2.backgroundColor = [UIHelp colorWithHexString:@"0xF9F9F9"];
                operationItemView1.imageView.image = [UIImage imageNamed:@"h_com_buy"];
                operationItemView2.imageView.image = [UIImage imageNamed:@"h_com_top"];
                operationItemView2.label1.text = [NSString stringWithString:@"热销排行"];
                operationItemView2.label2.text = [NSString stringWithString:@"热销货源排行版"];
                operationItemView1.layer.borderWidth = 0.5;
                operationItemView1.layer.borderColor = [[UIHelp colorWithHexString:@"0xdadada"] CGColor];
                operationItemView2.layer.borderWidth = 0.5;
                operationItemView2.layer.borderColor = [[UIHelp colorWithHexString:@"0xdadada"] CGColor];
                [operationItemView1 addTarget:self action:@selector(operationTouchUpItemView1:)  forControlEvents:UIControlEventTouchUpInside];           
                [operationItemView2 addTarget:self action:@selector(operationTouchUpItemView2:) forControlEvents:UIControlEventTouchDown];
                [cell.operation1 insertSubview:operationItemView1 atIndex:0];
                [cell.operation2 insertSubview:operationItemView2 atIndex:0];
                self.operationItemView1 = operationItemView1;
                self.operationItemView2 = operationItemView2;
                [operationItemView1 release];
                [operationItemView2 release];
                
//                cell.backgroundColor = [UIColor clearColor];
//                cell.layer.borderWidth = 0.5;
//                cell.layer.masksToBounds=YES;
                
            }   
             
            return cell;
        }
            break;
        default:
        {
            AMChannelTableViewCell *cell = (AMChannelTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMChannelTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMChannelTableViewCell createCell];
                cell.menuView.menuDelegate = self;
                cell.menuView.columnCount = AMCONST_HOME_COMMODITY_MENUVIEW_COLUMNE;
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_COMMODITY_CHANNEL_HEIGHT * menuViewCount);
                self.menuView = cell.menuView;
                cell.menuView.scrollEnabled = NO;
                cell.menuView.itemSize = CGSizeMake(108, 73);
                cell.menuView.yPadding = 0;
                cell.menuView.topPadding = 0;
                cell.menuView.bottomPadding = -5;
                cell.menuView.layer.masksToBounds=YES;   
                //    menuItemView.layer.cornerRadius=1.0;   
                cell.menuView.layer.borderWidth=0.5;   
                cell.menuView.layer.borderColor=[[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor]; 
            }   
            [cell.menuView reloadData];
            return cell;
        }
            break;
    }
    
    return nil;
    
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
}

#pragma mark functions for clicked

-(void)operationTouchUpItemView2:(id)sender
{
    [AMLogUtils appendLog:INDUSTRIAL_SMALLWARE_PAGE_THREE];
    AMHotRankViewController *hotRankViewController =[[AMHotRankViewController alloc] initWithNibName:@"AMHotRankViewController" bundle:nil];
    hotRankViewController.parentTitle = @"首页";
    [self.navigationController pushViewController:hotRankViewController animated:YES];
    [hotRankViewController release];
}

//小商品的创业进货
-(void)operationTouchUpItemView1:(id)sender
{
    [AMLogUtils appendLog:INDUSTRIAL_SMALLWARE_PAGE_TWO];
    AMActivityDetailViewController * detailView = [[AMActivityDetailViewController alloc] initWithNibName:@"AMActivityDetailViewController" bundle:nil];
    detailView.activityId = [NSNumber numberWithInt:104355];
    detailView.activityTitle = @"创业进货";
    detailView.businessType = AM_ACTIVITY_PRICE_TYPE_STOCK;
    [self.navigationController pushViewController:detailView animated:YES];

}

//小商品的特价促销
-(void)operationViewEvent1TouchUp:(id)sender
{
    [AMLogUtils appendLog:INDUSTRIAL_SMALLWARE_PAGE_ONE];
    AMActivityDetailViewController * detailView = [[AMActivityDetailViewController alloc] initWithNibName:@"AMActivityDetailViewController" bundle:nil];
    detailView.activityTitle = @"特价促销";
    detailView.industryId = @"smart";
    detailView.businessType = AM_ACTIVITY_PRICE_TYPE_PRICE_SMART;
    [self.navigationController pushViewController:detailView animated:YES];
    [detailView release];
    AMOperationItemView *operationItemView = sender;
    operationItemView.backgroundColor = [UIHelp colorWithHexString:@"0xf9f9f9"];
}

-(void)blockDownAction:(AMOperationItemView *)sender
{
    sender.backgroundColor = [UIHelp colorWithHexString:@"0xf2f2f2"];
}

-(void)blockUpOutsideAction:(AMOperationItemView *)sender
{
    sender.backgroundColor = [UIHelp colorWithHexString:@"0xf9f9f9"];
}
#pragma mark AliChannel Delegate Methods
-(void)AliChannelReloadData
{
    [self.funcListTable reloadData];
}
#pragma mark AliAdv Delegate Methods
-(UIViewController*)superController;
{
    return self;
}
-(NSString*)superControllerName
{
    return @"小商品";
}
//将获取到的数据传递给前端的特价专场以及今日活动
-(void)dataReload
{
    if ([self.operation1.contentData count]>0) {
        AMHomepageDressEvent1 *homepageDressEvent1 = [self.operation1.contentData objectAtIndex:0];
        self.operationItemView1.label2.text = homepageDressEvent1.description;
    }
    if ([self.operation2.contentData count]>0) {
        AMHomepageDressEvent1 *homepageDressEvent2 = [self.operation2.contentData objectAtIndex:0];
        self.operationItemView2.label2.text = homepageDressEvent2.description;
    }
    if ([self.operationView.contentData count]>0) {
        AMHomepageDressEvent1 *homepageDressEvent1 = [self.operationView.contentData objectAtIndex:0];
        if (homepageDressEvent1.imageUrl) {
//            self.operationItemView.imageView2.hidden = YES;
            [self.operationItemView.imageView clear];
            self.operationItemView.imageView.url = [NSURL URLWithString:homepageDressEvent1.imageUrl];
            self.operationItemView.imageView.mode = UIViewContentModeScaleToFill;
            [self.objMan manage:self.operationItemView.imageView];
        }
    }
}
#pragma mark MenuView Delegate Methods
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView
{
//    return [self.channelView.contentData count];
    return [self.contentData count];
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index
{
//    NSDictionary *data = [self.channelView.contentData objectAtIndex:index];
//    NSString *homepageDressId = [data objectForKey:@"ID"];
//    NSString *homepageDressName = [data objectForKey:@"name"];
//    NSString *homepageDressImageUrl = [data objectForKey:@"imageUrl"];
    [AMLogUtils appendLog:INDUSTRIAL_SMALLWARE_PAGE_FOUR];
    NSString *homepageDressId = [[self.sourceData objectAtIndex:index ] objectForKey:@"ID"];
    NSString *homepageDressName = [[self.sourceData objectAtIndex:index ] objectForKey:@"name"];
    
//    NSLog(@"homepageDressChilden.id: %@,homepageDressName:%@,homepageDressImageUrl: %@",homepageDressId,homepageDressName,homepageDressImageUrl);
    AMSubpageWithMenuViewController *subpageViewController = [[AMSubpageWithMenuViewController alloc] init];
//    subpageViewController.homepageDressRequest.industryId =AMCONST_HOME_COMMODITY;
    subpageViewController.subpageRequest.industryId = AMCONST_HOME_COMMODITY;
    subpageViewController.subpageRequest.categoryId = homepageDressId;
    subpageViewController.categoryName = homepageDressName;
//    subpageViewController.indexPath = [NSIndexPath indexPathForRow:index inSection:0];
    [self.navigationController pushViewController:subpageViewController animated:YES];
    [subpageViewController release];
    
}

- (AMMenuItemView *)menuView:(AMMenuView *)menuView ItemViewForRowAtIndex:(NSInteger)index
{
    //调用本地信息，不再调用服务器数据
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    
    return menuItemView;
    //调用服务器数据
//    if ([self.channelView.contentData count] > 0) {
//        AMMenuItemView *menuItemView = [[self.channelView.contentData objectAtIndex:index] objectForKey:@"view"];
//        if (index <=  [self.sourceData count]) {
//            menuItemView.imageView.image = [UIImage imageNamed:[[self.sourceData objectAtIndex:index ] objectForKey:@"imageName"]];
//        }
//        return menuItemView;
//    }
//    else {
//        [self.channelView loadObjectsFromRemote];
//    }
    return nil;
}

@end

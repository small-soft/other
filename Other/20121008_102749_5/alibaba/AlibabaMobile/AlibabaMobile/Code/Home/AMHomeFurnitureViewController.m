//
//  AMHomeFurnitureViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-28.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomeFurnitureViewController.h"
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
#import "AMSubpageWithMenuViewController.h"
#import "AMOperationItemView1.h"
#import "AMActivityDetailViewController.h"
#import "AMActivityListViewController.h"
#import "Utils.h"

@interface AMHomeFurnitureViewController ()
@property (nonatomic,retain) AMChannel      *channelView;
@property (nonatomic,retain) AMMenuView     *menuView;
@property (nonatomic,retain) AMAdvView      *bannerView;
@property (nonatomic,retain) AliOperation1  *operation1;
@property (nonatomic,retain) AliOperation2  *operation2;
@property (nonatomic,retain) AMOperationItemView1 *operationItemView1;
@property (nonatomic,retain) AMOperationItemView1 *operationItemView2;

@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) HJObjManager *objMan;
@end

@implementation AMHomeFurnitureViewController
@synthesize channelView = _channelView;
@synthesize bannerView = _bannerView;
@synthesize operation1 = _operation1;
@synthesize operation2 = _operation2;
@synthesize menuView = _menuView;
@synthesize contentData = _contentData;
@synthesize objMan = _objMan;
@synthesize operationItemView1 = _operationItemView1;
@synthesize operationItemView2 = _operationItemView2;

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
    
    
    UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"h_furniture_navbar"]];
    self.navBgImgeView  =  imageViewTmp;
    [imageViewTmp release];
    
    self.funcListTable.backgroundColor = [UIHelp colorWithHexString:@"0xEDE9DA"];
    
    [self.industrySelectPickView.mSelectTypeButtonUp setImage:[UIImage imageNamed:@"h_com_drop01_nor"] forState:UIControlStateNormal];
    [self.industrySelectPickView.mSelectTypeButtonDown setImage:[UIImage imageNamed:@"h_com_drop_nor"] forState:UIControlStateNormal];
    self.industrySelectPickView.mSelectTypeButtonUp.hidden = YES;
    self.industrySelectPickView.lableTitle.frame = CGRectMake(self.industrySelectPickView.lableTitle.frame.origin.x - 4, self.industrySelectPickView.lableTitle.frame.origin.y, self.industrySelectPickView.lableTitle.frame.size.width, self.industrySelectPickView.lableTitle.frame.size.height);
    self.industrySelectPickView.lableTitle.textColor = [UIHelp colorWithHexString:@"0x4e2704"];
    self.industrySelectPickView.mSelectTypeButtonUp.frame = CGRectMake(self.industrySelectPickView.mSelectTypeButtonUp.frame.origin.x + 13, self.industrySelectPickView.mSelectTypeButtonUp.frame.origin.y, self.industrySelectPickView.mSelectTypeButtonUp.frame.size.width, self.industrySelectPickView.mSelectTypeButtonUp.frame.size.height);
    self.industrySelectPickView.mSelectTypeButtonDown.frame = CGRectMake(self.industrySelectPickView.mSelectTypeButtonDown.frame.origin.x + 13, self.industrySelectPickView.mSelectTypeButtonDown.frame.origin.y, self.industrySelectPickView.mSelectTypeButtonDown.frame.size.width, self.industrySelectPickView.mSelectTypeButtonDown.frame.size.height);
    //调用本地信息，不再调用服务器数据
//    self.channelView = [[AMChannel alloc] init];
//    self.channelView.request.industryId = AMCONST_HOME_FURNITURE;
//    self.channelView.request.summary    = AMCONST_HOME_SUMMARY;
//    self.channelView.request.configName = AMCONST_HOME_CATEGORIES;
//    self.channelView.delegate = self;
//    [self.channelView loadObjectsFromRemote];
    
}

- (void)viewDidUnload
{
    self.channelView = nil;
    self.operation1 = nil;
    self.operation2 = nil;
    self.menuView = nil;
    self.bannerView = nil;
    self.contentData = nil;
    self.objMan = nil;
    self.operationItemView1 = nil;
    self.operationItemView2 = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [UserDataUtils setNavigationHomeBar:YES];
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"h_furniture_navbar"] forBarMetrics:UIBarMetricsDefault];
//        [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"bg_topbar_black"] forBarMetrics:UIBarMetricsDefault];
    }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"h_furniture_navbar"].CGImage;
    }
    
    //self.navigationController.navigationBar.backgroundColor = [UIColor clearColor]; 
    
    self.navigationController.navigationBar.hidden = NO;
    
}

-(void)viewDidAppear:(BOOL)animated
{
//    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
//        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"bg_topbar_black"] forBarMetrics:UIBarMetricsDefault];
//    }
//    else {
//        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"bg_topbar_black"].CGImage;
//    }
}

-(void)viewWillDisappear:(BOOL)animated
{
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"bg_topbar"] forBarMetrics:UIBarMetricsDefault];
    }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"bg_topbar"].CGImage;
    }
    //[(UIView*)[self.navigationController.navigationBar.subviews objectAtIndex:0] removeFromSuperview];
    //self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"bg_topbar"];
    //self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"bg_topbar"].CGImage;
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
    [_operation1 release];
    [_operation2 release];
    [_bannerView release];
    [_menuView release];
    [_contentData release];
    [_objMan release];
    [_operationItemView1 release];
    [_operationItemView2 release];
    
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
            menuItemViewTmp.imageView.image = [UIImage imageNamed:[data objectForKey:@"imageName"]];
//            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x, menuItemViewTmp.imageView.frame.origin.y, 70, 70);
            //menuItemViewTmp.imageView.mode = UIViewContentModeScaleToFill;
//            [self.objMan manage:menuItemViewTmp.imageView];
            menuItemViewTmp.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x, menuItemViewTmp.imageView.frame.origin.y, 108, 96);
            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x + 15, menuItemViewTmp.imageView.frame.origin.y, 70, 70);
            [menuItemViewTmp setLabelyPadding:2 xPadding:0];
            menuItemViewTmp.label.font = [UIFont fontWithName:@"Arial-BoldMT" size:14.0f];
            menuItemViewTmp.label.textColor = [UIHelp colorWithHexString:@"0x884a21"];
            menuItemViewTmp.button.adjustsImageWhenHighlighted = YES;
            menuItemViewTmp.layer.masksToBounds=YES;  
            
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
                       [NSDictionary dictionaryWithObjectsAndKeys:@"日用百货", @"name",@"riyongbaihuo", @"ID",@"h_furniture_list01", @"imageName",@"h_furniture_list01_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"布艺家纺", @"name",@"buyijiafang", @"ID",@"h_furniture_list02", @"imageName",@"h_furniture_list02_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"运动休闲", @"name",@"yundongxiuxian", @"ID",@"h_furniture_list06", @"imageName",@"h_furniture_list06_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"家装建材", @"name",@"jiazhuangjiancai", @"ID",@"h_furniture_list03", @"imageName",@"h_furniture_list03_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"美容护肤", @"name",@"meironghufu", @"ID",@"h_furniture_list04", @"imageName",@"h_furniture_list04_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"母婴用品", @"name",@"muyingyongpin", @"ID",@"h_furniture_list05", @"imageName",@"h_furniture_list05_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"食品饮料", @"name",@"shipinyinliao", @"ID",@"h_furniture_list07", @"imageName",@"h_furniture_list07_p", @"imagePressName",nil],nil];
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
        self.bannerView.request.industryId = AMCONST_HOME_FURNITURE;
        self.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
        self.bannerView.request.configName = AMCONST_HOME_BANNERS;
        [self.bannerView loadObjectsFromRemote];
    }
    if ([self.operation1.contentData count]==0) {
        self.operation1.request.industryId = AMCONST_HOME_FURNITURE;
        self.operation1.request.summary    = AMCONST_HOME_SUMMARY;
        self.operation1.request.configName = AMCONST_HOME_EVENT1;
        self.operation1.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT1_LIST;
        [self.operation1 loadObjectsFromRemote];
    }
    if ([self.operation2.contentData count]==0) {
        self.operation2.request.industryId = AMCONST_HOME_FURNITURE;
        self.operation2.request.summary    = AMCONST_HOME_SUMMARY;
        self.operation2.request.configName = AMCONST_HOME_EVENT2;
        self.operation2.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT2_LIST;
        [self.operation2 loadObjectsFromRemote];
    }
//    if ([self.channelView.contentData count]==0) {
//        [self.channelView loadObjectsFromRemote];
//    }
}

#pragma mark Home Common Methods
-(NSString*)commonHomeViewBackButtonTitle
{
    return @"家居百货";
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
            return AMCONST_HOME_FURNITURE_OPERATION_HEIGHT;
            break;  
        default:
            return AMCONST_HOME_FURNITURE_CHANNEL_HEIGHT * menuViewCount;
            
            break;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section
{
//    menuViewCount = [self.channelView.contentData count]/AMCONST_HOME_FURNITURE_MENUVIEW_COLUMNE;
//    if ([self.channelView.contentData count]%AMCONST_HOME_FURNITURE_MENUVIEW_COLUMNE) {
//        menuViewCount+=1;
//    }
    menuViewCount = 3;
    return 3;
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
                cell.bannerView.request.industryId = AMCONST_HOME_FURNITURE;
                cell.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.bannerView.request.configName = AMCONST_HOME_BANNERS;
                
                [cell.bannerView loadObjectsFromRemote];
            }   
            
            cell.selectionStyle=UITableViewCellSelectionStyleNone; 
            cell.backgroundColor = [UIColor clearColor];
            cell.layer.borderWidth = 0;
            return cell;
            
        }
            break;
        case 1:
        {
            AliOperationTableViewCell *cell = (AliOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AliOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AliOperationTableViewCell createCell];
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_FURNITURE_OPERATION_HEIGHT);

                cell.operation1.frame= CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width/2, AMCONST_HOME_FURNITURE_OPERATION_HEIGHT);
                cell.operation2.frame= CGRectMake(cell.frame.origin.x + cell.frame.size.width/2, cell.frame.origin.y, cell.frame.size.width/2, AMCONST_HOME_FURNITURE_OPERATION_HEIGHT);
                self.operation1 = cell.operation1;
                self.operation2 = cell.operation2;
                //向服务器申请数据
                cell.operation1.request.industryId = AMCONST_HOME_FURNITURE;
                cell.operation1.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operation1.request.configName = AMCONST_HOME_EVENT1;
                cell.operation1.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT1_LIST;
                
                
                cell.operation2.request.industryId = AMCONST_HOME_FURNITURE;
                cell.operation2.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operation2.request.configName = AMCONST_HOME_EVENT2;
                cell.operation2.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT2_LIST;
                
                [cell.operation1 loadObjectsFromRemote];
                [cell.operation2 loadObjectsFromRemote];
                cell.operation1.delegate = self;
                cell.operation2.delegate = self;
                //隐藏operation1的默认图片
                cell.operation1.defaultImage.image = nil;
                cell.operation2.defaultImage.image = nil;
                [cell.operation1 setHideImageUrl:YES];
                [cell.operation2 setHideImageUrl:YES];
                //加入特价专场与今日活动两个UI图
                AMOperationItemView1 *operationItemView1Tmp = [[AMOperationItemView1 alloc] init];
                AMOperationItemView1 *operationItemView2Tmp = [[AMOperationItemView1 alloc] init];
                operationItemView1Tmp.backgroundColor = [UIHelp colorWithHexString:@"0xEBE1CD"];
                operationItemView2Tmp.backgroundColor = [UIHelp colorWithHexString:@"0xEBE1CD"];
                operationItemView1Tmp.imageView1.image = [UIImage imageNamed:@"h_furniture_jr"];
                operationItemView1Tmp.imageView2.image = [UIImage imageNamed:@"h_furniture_voice"];
                operationItemView2Tmp.imageView1.image = [UIImage imageNamed:@"h_furniture_tj"];
                operationItemView2Tmp.imageView2.image = [UIImage imageNamed:@"h_furniture_day"];
                operationItemView2Tmp.label.text = [NSString stringWithString:@"8月网货订货会；美妆..."];
                [operationItemView1Tmp addTarget:self action:@selector(operationTouchUpItemView1:)  forControlEvents:UIControlEventTouchUpInside];           
                [operationItemView2Tmp addTarget:self action:@selector(operationTouchUpItemView2:) forControlEvents:UIControlEventTouchUpInside];
                [operationItemView1Tmp addTarget:self action:@selector(operationTouchDownItemView:)  forControlEvents:UIControlEventTouchDown];           
                [operationItemView2Tmp addTarget:self action:@selector(operationTouchDownItemView:) forControlEvents:UIControlEventTouchDown];
                [operationItemView1Tmp addTarget:self action:@selector(operationTouchUpOutsideItemView:)  forControlEvents:UIControlEventTouchUpOutside];           
                [operationItemView2Tmp addTarget:self action:@selector(operationTouchUpOutsideItemView:) forControlEvents:UIControlEventTouchUpOutside];
                [cell.operation1 insertSubview:operationItemView1Tmp atIndex:0];
                [cell.operation2 insertSubview:operationItemView2Tmp atIndex:0];
                self.operationItemView1 = operationItemView1Tmp;
                self.operationItemView2 = operationItemView2Tmp;
                [operationItemView1Tmp release];
                [operationItemView2Tmp release];
                //加入竖直图片
                UIImageView *imageHLine = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"h_furniture_line_s"]];
                imageHLine.frame = CGRectMake(cell.operation1.frame.origin.x + 159.0, cell.operation1.frame.origin.y + 10.0, 2, AMCONST_HOME_FURNITURE_OPERATION_HEIGHT - 20.0);
                [cell addSubview:imageHLine];
                [imageHLine release];
                
            }   
            cell.selectionStyle=UITableViewCellSelectionStyleNone; 
            cell.backgroundColor = [UIColor clearColor];
            cell.layer.borderWidth = 0;
            return cell;
        }
            break;
        default:
        {
            AMChannelTableViewCell *cell = (AMChannelTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMChannelTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMChannelTableViewCell createCell];
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_FURNITURE_CHANNEL_HEIGHT * menuViewCount);
                //cell.menuView.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, cell.frame.size.height);
                cell.menuView.menuDelegate = self;
                cell.menuView.columnCount = AMCONST_HOME_FURNITURE_MENUVIEW_COLUMNE;
                cell.menuView.itemSize = CGSizeMake(108, 96);
                self.menuView = cell.menuView;
                //设置类目的menuView的属性
                cell.menuView.scrollEnabled = NO;
                cell.selectionStyle=UITableViewCellSelectionStyleNone; 
                cell.menuView.backgroundColor = [UIHelp colorWithHexString:@"0xEDE9DA"];
                cell.menuView.yPadding = 11;
                cell.backgroundColor = [UIHelp colorWithHexString:@"0xEDE9DA"];
                //加入背景图片，一共三幅
                UIImage *imageTmp = [UIImage imageNamed:@"h_furniture_bg"];
                UIImageView *imageViewTmp = [[UIImageView alloc] initWithFrame:CGRectMake(cell.frame.origin.x, cell.frame.origin.y + 73, imageTmp.size.width, imageTmp.size.height)];  
                UIImageView *imageViewTmp1 = [[UIImageView alloc] initWithFrame:CGRectMake(cell.frame.origin.x, cell.frame.origin.y + 180, imageTmp.size.width, imageTmp.size.height)]; 
                UIImageView *imageViewTmp2 = [[UIImageView alloc] initWithFrame:CGRectMake(cell.frame.origin.x, cell.frame.origin.y + 287, imageTmp.size.width, imageTmp.size.height)]; 
                imageViewTmp.image = imageTmp;
                imageViewTmp1.image = imageTmp;
                imageViewTmp2.image = imageTmp;
                [cell.menuView insertSubview:imageViewTmp atIndex:0];
                [cell.menuView insertSubview:imageViewTmp1 atIndex:0];
                [cell.menuView insertSubview:imageViewTmp2 atIndex:0];         
                [imageViewTmp release];
                [imageViewTmp1 release];
                [imageViewTmp2 release];
                //加载类目数据
            }   
            
            [cell.menuView reloadData];
            cell.backgroundColor = [UIColor clearColor];
            cell.layer.borderWidth = 0;
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
    [self.funcListTable deselectRowAtIndexPath:indexPath animated:NO];
}

#pragma mark functions for clicked
//按下后背景颜色变化，按下后移开背景颜色变回原样
-(void)operationTouchDownItemView:(AMOperationItemView1 *)sender
{
    sender.backgroundColor = [UIHelp colorWithHexString:@"0xE7D9BE"];
}
-(void)operationTouchUpOutsideItemView:(AMOperationItemView1 *)sender
{
    sender.backgroundColor = [UIHelp colorWithHexString:@"0xEBE1CD"];
}

//家具百货的今日活动
-(void)operationTouchUpItemView2:(AMOperationItemView1 *)sender
{
    
//    if([self.operation2.contentData count]){
        [AMLogUtils appendLog:INDUSTRIAL_HOUSEHOLD_PAGE_TWO];
        AMActivityListViewController *industrySelectController = [[AMActivityListViewController alloc] initWithNibName:@"AMActivityListViewController" bundle:nil ];
        industrySelectController.industryId = ACTIVITY_INDUSTRY_ID_OF_HOME;
//        industrySelectController.title = @"家具百货创业进货";
        industrySelectController.title = @"创业进货";
        [self.navigationController pushViewController:industrySelectController animated:YES];
        [industrySelectController release];
//    }
    sender.backgroundColor = [UIHelp colorWithHexString:@"0xEBE1CD"];
}

//家具百货的特价专场
-(void)operationTouchUpItemView1:(AMOperationItemView1 *)sender
{
//    if([self.operation1.contentData count]){
        [AMLogUtils appendLog:INDUSTRIAL_HOUSEHOLD_PAGE_ONE];
        AMActivityDetailViewController * detailView = [[AMActivityDetailViewController alloc] initWithNibName:@"AMActivityDetailViewController" bundle:nil];
        detailView.activityTitle = @"特价促销";
        detailView.industryId = @"home";
        detailView.businessType = AM_ACTIVITY_PRICE_TYPE_PRICE;
        [self.navigationController pushViewController:detailView animated:YES];
        [detailView release];

//    }
    sender.backgroundColor = [UIHelp colorWithHexString:@"0xEBE1CD"];
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
    return @"家居百货";
}
//将获取到的数据传递给前端的特价专场以及今日活动
-(void)dataReload
{
    if ([self.operation1.contentData count]>0) {
        AMHomepageDressEvent1 *homepageDressEvent1 = [self.operation1.contentData objectAtIndex:0];
        self.operationItemView1.label.text = homepageDressEvent1.description;
    }
    if ([self.operation2.contentData count]>0) {
        AMHomepageDressEvent1 *homepageDressEvent2 = [self.operation2.contentData objectAtIndex:0];
        self.operationItemView2.label.text = homepageDressEvent2.description;
    }
}
#pragma mark MenuView Delegate Methods
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView
{
    //    return [self.channelView.contentData count]
    return [self.contentData count];
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index
{
//    NSDictionary *data = [self.channelView.contentData objectAtIndex:index];
    [AMLogUtils appendLog:INDUSTRIAL_HOUSEHOLD_PAGE_THREE];
    NSString *homepageDressId = [[self.sourceData objectAtIndex:index ] objectForKey:@"ID"];
    NSString *homepageDressName = [[self.sourceData objectAtIndex:index ] objectForKey:@"name"];
//    NSString *homepageDressImageUrl = [data objectForKey:@"imageUrl"];
    
    
//    NSLog(@"homepageDressChilden.id: %@,homepageDressName:%@,homepageDressImageUrl: %@",homepageDressId,homepageDressName,homepageDressImageUrl);
    AMSubpageWithMenuViewController *subpageViewController = [[AMSubpageWithMenuViewController alloc] init];
//    subpageViewController.homepageDressRequest.industryId =AMCONST_HOME_FURNITURE;
    subpageViewController.subpageRequest.industryId = AMCONST_HOME_FURNITURE;
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
//
//        return menuItemView;
//    }
//    else {
//        [self.channelView loadObjectsFromRemote];
//    }
//    return nil;
}
//更换类目点击时的背景
- (void)menuView:(AMMenuView*)menuView  ItemPressedDownAtIndex:(NSInteger)index
{
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    menuItemView.imageView.image = [UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey: @"imagePressName"]];
}
- (void)menuView:(AMMenuView*)menuView  ItemPressedAtIndex:(NSInteger)index
{
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    menuItemView.imageView.image = [UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey: @"imageName"]];
}
- (void)menuView:(AMMenuView*)menuView  ItemPressedUpOutsideActionAtIndex:(NSInteger)index
{
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    menuItemView.imageView.image = [UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey: @"imageName"]];
}

@end

//            imageTmp = [imageTmp stretchableImageWithLeftCapWidth:imageTmp.size.width*1/2 topCapHeight:imageTmp.size.height/2];
//            CGSize itemSize = CGSizeMake(imageViewTmp.frame.size.width, imageViewTmp.frame.size.height);
//            UIGraphicsBeginImageContext(itemSize);
//            CGRect imageRect = CGRectMake(imageViewTmp.frame.origin.x, imageViewTmp.frame.origin.y, cell.frame.size.width, imageTmp.size.height);
//            [imageTmp drawInRect:imageRect];
//            imageViewTmp.image = UIGraphicsGetImageFromCurrentImageContext();
//            UIGraphicsEndImageContext();
////            imageViewTmp.image = imageTmp;

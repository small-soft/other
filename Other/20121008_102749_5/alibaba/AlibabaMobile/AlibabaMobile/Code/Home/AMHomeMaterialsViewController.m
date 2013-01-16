//
//  AMHomeDressViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomeMaterialsViewController.h"
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
#import "AMMarketpriceViewController.h"
#import "AMSubpageWithMenuViewController.h"
#import "Utils.h"

extern NSInteger const HOME_LISTITEM_NEWS;
extern NSInteger const HOME_LISTITEM_QUOTATIONS;
extern NSInteger const HOME_LISTITEM_CATEGORIES;
extern NSInteger const HOME_LISTITEM_MAGAZINE;
extern NSInteger const HOME_LISTITEM_HOTRANK;//热销排行-->add by xiaowen
extern NSInteger const HOME_LISTITEM_NEWPRODUCTS;//新品专区-->add by xiaowen

@interface AMHomeMaterialsViewController ()

@property (nonatomic,retain) AMChannel      *channelView;
@property (nonatomic,retain) AMMenuView     *menuView;
@property (nonatomic,retain) AMAdvView      *bannerView;
@property (nonatomic,retain) AMOperationView*operationView;
@property (nonatomic,retain) AliOperation1  *operation1;
@property (nonatomic,retain) AliOperation2  *operation2;

@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) HJObjManager *objMan;
@end

@implementation AMHomeMaterialsViewController
@synthesize channelView = _channelView;
@synthesize bannerView=_bannerView;
@synthesize operation1=_operation1;
@synthesize operation2=_operation2;
@synthesize operationView = _operationView;
@synthesize menuView = _menuView;
@synthesize contentData = _contentData;
@synthesize objMan = _objMan;

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
    menuViewCount = 0;
   
    self.funcListTable.backgroundColor = [UIHelp colorWithHexString:@"0xDEE4E8"];
    UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"bg_topbar_black"]];
    self.navBgImgeView  =  imageViewTmp;
    [imageViewTmp release];
    [self changePickFrame:7 yframe:0];
//调用本地信息，不再调用服务器数据
//    self.channelView = [[AMChannel alloc] init];
//    self.channelView.request.industryId = AMCONST_HOME_MATERIAL;
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
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [UserDataUtils setNavigationHomeBar:YES];
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
     [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"h_material_navbar"] forBarMetrics:UIBarMetricsDefault];
//    [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"bg_topbar_black"] forBarMetrics:UIBarMetricsDefault];
     }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"h_material_navbar"].CGImage;
    }
    
    //self.navigationController.navigationBar.backgroundColor = [UIColor clearColor]; 
    
    self.navigationController.navigationBar.hidden = NO;
    
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
    [_operationView release];
    [_bannerView release];
    [_menuView release];
    [_contentData release];
    [_objMan release];
    
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
            menuItemViewTmp.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x, menuItemViewTmp.imageView.frame.origin.y, 107, 87);
            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.frame.origin.x - 5, menuItemViewTmp.frame.origin.y, 100, 77);
            [menuItemViewTmp setLabelyPadding:-8 xPadding:0];
            menuItemViewTmp.label.font = [UIFont fontWithName:@"Arial-BoldMT" size:14.0f];
            menuItemViewTmp.label.textColor = [UIHelp colorWithHexString:@"0x333333"];
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
                       [NSDictionary dictionaryWithObjectsAndKeys:@"橡胶", @"name",@"xiangsu", @"ID",@"h_material_list01", @"imageName",@"h_material_list01_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"精细化学品", @"name",@"jingxihuaxuepin", @"ID",@"h_material_list02", @"imageName",@"h_material_list02_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"化工", @"name",@"huagong", @"ID",@"h_material_list03", @"imageName",@"h_material_list03_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"纺织", @"name",@"fangzhipige", @"ID",@"h_material_list04", @"imageName",@"h_material_list04_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"包装", @"name",@"baozhuang", @"ID",@"h_material_list05", @"imageName",@"h_material_list05_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"农业", @"name",@"nongye", @"ID",@"h_material_list06", @"imageName",@"h_material_list06_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"冶金", @"name",@"yejinkuangchan", @"ID",@"h_material_list07", @"imageName",@"h_material_list07_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"能源", @"name",@"nengyuan", @"ID",@"h_material_list08", @"imageName",@"h_material_list08_p", @"imagePressName",nil],nil];
    }
    return _sourceData;
}

#pragma mark Home Common Methods
-(NSString*)commonHomeViewBackButtonTitle
{
    return @"原材料";
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
        self.bannerView.request.industryId = AMCONST_HOME_MATERIAL;
        self.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
        self.bannerView.request.configName = AMCONST_HOME_BANNERS;
        [self.bannerView loadObjectsFromRemote];
    }
    if ([self.operationView.contentData count] == 0) {
//        self.operationView.request.industryId = AMCONST_HOME_MATERIAL;
//        self.operationView.request.summary    = AMCONST_HOME_SUMMARY;
//        self.operationView.request.configName = AMCONST_HOME_PRICE;
//        self.operationView.request.transactionType = AMTRANSACTION_TYPE_HOME_PRICE_LIST;
//        [self.operationView loadObjectsFromRemote];
    }
//    if ([self.channelView.contentData count]==0) {
//        [self.channelView loadObjectsFromRemote];
//    }
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
            return AMCONST_HOME_MATERIAL_OPERATION_HEIGHT;
            break;
        default:
            return AMCONST_HOME_MATERIAL_CHANNEL_HEIGHT * menuViewCount;
            
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
//    menuViewCount = [self.channelView.contentData count]/AMCONST_HOME_MATERIAL_MENUVIEW_COLUMNE;
//    if ([self.channelView.contentData count]%AMCONST_HOME_MATERIAL_MENUVIEW_COLUMNE) {
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
                cell.bannerView.request.industryId = AMCONST_HOME_MATERIAL;
                cell.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.bannerView.request.configName = AMCONST_HOME_BANNERS;
                
                [cell.bannerView loadObjectsFromRemote];
            }   
            
            return cell;
            
        }
            break;
        case 1:
        {
           AMOperationTableViewCell *cell = (AMOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMOperationTableViewCell createCell];
                //设置cell尺寸
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_MATERIAL_OPERATION_HEIGHT);
                cell.operationView.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, cell.frame.size.height);
                cell.operationView.opertationView.frame = cell.operationView.frame ;
                self.operationView = cell.operationView;
                //设置网络请求
//                cell.operationView.request.industryId = AMCONST_HOME_MATERIAL;
//                cell.operationView.request.summary    = AMCONST_HOME_SUMMARY;
//                cell.operationView.request.configName = AMCONST_HOME_PRICE;   
//                cell.operationView.request.transactionType = AMTRANSACTION_TYPE_HOME_PRICE_LIST;
//                [cell.operationView loadObjectsFromRemote];
                //设置cell的UI界面属性
                cell.backgroundColor = [UIHelp colorWithHexString:@"0xDEE4E8"];
                cell.operationView.opertationView.image = [UIImage imageNamed:@"h_material_jiage"];
                //注册点击响应函数
                [cell.operationView addTarget:self action:@selector(operationViewEvent1TouchUp:)  forControlEvents:UIControlEventTouchUpInside];  
                [cell.operationView  addTarget:self action:@selector(operationViewEvent1TouchDown:) forControlEvents:UIControlEventTouchDown];
                [cell.operationView  addTarget:self action:@selector(operationViewEvent1TouchUpOutside:)  forControlEvents:UIControlEventTouchUpOutside]; 
                [cell.operationView  addTarget:self action:@selector(operationViewEvent1TouchUpOutside:)  forControlEvents:UIControlEventTouchCancel]; 
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
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_MATERIAL_CHANNEL_HEIGHT * menuViewCount);
                cell.menuView.menuDelegate = self;
                cell.menuView.columnCount = AMCONST_HOME_MATERIAL_MENUVIEW_COLUMNE;
                cell.menuView.scrollEnabled = NO;
                cell.menuView.backgroundColor = [UIHelp colorWithHexString:@"0xDEE4E8"];
                cell.menuView.itemSize = CGSizeMake(107, 87);
                cell.menuView.yPadding = 1;
                cell.menuView.topPadding = -1;
                self.menuView = cell.menuView;
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
-(void)operationViewEvent1TouchUp:(id)sender
{
    [AMLogUtils appendLog:INDUSTRIAL_MATERIAL_PAGE_ONE];
    AMMarketpriceViewController *industrySelectController = [[AMMarketpriceViewController alloc] initWithNibName:@"AMMarketpriceViewController" bundle:nil ];
    [self.navigationController pushViewController:industrySelectController animated:YES];
    [industrySelectController release];

    self.operationView.opertationView.image = [UIImage imageNamed:@"h_material_jiage"];
}
//按下后背景颜色变化，按下后移开背景颜色变回原样
-(void)operationViewEvent1TouchDown:(AMOperationView *)sender
{
    self.operationView.opertationView.image = [UIImage imageNamed:@"h_material_jiage_p"];
}
-(void)operationViewEvent1TouchUpOutside:(AMOperationView *)sender
{
    self.operationView.opertationView.image = [UIImage imageNamed:@"h_material_jiage"];
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
    return @"原材料";
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
//    NSString *homepageDressId = [data objectForKey:@"id"];
//    NSString *homepageDressName = [data objectForKey:@"name"];
//    NSString *homepageDressImageUrl = [data objectForKey:@"imageUrl"];  
//    NSLog(@"homepageDressChilden.id: %@,homepageDressName:%@,homepageDressImageUrl: %@",homepageDressId,homepageDressName,homepageDressImageUrl);
    [AMLogUtils appendLog:INDUSTRIAL_MATERIAL_PAGE_TWO];
    NSString *homepageDressId = [[self.sourceData objectAtIndex:index ] objectForKey:@"ID"];
    NSString *homepageDressName = [[self.sourceData objectAtIndex:index ] objectForKey:@"name"];
    
    AMSubpageWithMenuViewController *subpageViewController = [[AMSubpageWithMenuViewController alloc] init];
    subpageViewController.subpageRequest.industryId = AMCONST_HOME_MATERIAL;
    subpageViewController.subpageRequest.categoryId = homepageDressId;
    subpageViewController.categoryName = homepageDressName;
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

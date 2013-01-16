//
//  AMHomeDressViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomeDressViewController.h"
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
#import "AMActivityListViewController.h"
#import "AMOperationView.h"
#import "AMOperationTableViewCell.h"
#import "AMChannelTableViewCell.h"
#import "AMAdvView.h"
#import "AMChannel.h"
#import "AMSubpageDressViewController.h"
#import "AMNewProductsZoneViewController.h"
#import "Utils.h"

extern NSInteger const HOME_LISTITEM_NEWS;
extern NSInteger const HOME_LISTITEM_QUOTATIONS;
extern NSInteger const HOME_LISTITEM_CATEGORIES;
extern NSInteger const HOME_LISTITEM_MAGAZINE;
extern NSInteger const HOME_LISTITEM_HOTRANK;//热销排行-->add by xiaowen
extern NSInteger const HOME_LISTITEM_NEWPRODUCTS;//新品专区-->add by xiaowen

@interface AMHomeDressViewController ()
@property (nonatomic,retain) AMChannel      *channelView;
@property (nonatomic,retain) AMMenuView     *menuView;
@property (nonatomic,retain) AMAdvView      *bannerView;
@property (nonatomic,retain) AMOperationView*operationView;
@property (nonatomic,retain) AliOperation1  *operation1;
@property (nonatomic,retain) AliOperation2  *operation2;

@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) HJObjManager *objMan;
@end

@implementation AMHomeDressViewController
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
    menuViewCount = 2;
    self.funcListTable.backgroundColor = [UIHelp colorWithHexString:@"0xfcfaf7"];
    [self changePickFrame:-3 yframe:0];
//    self.funcListTable.separatorColor = [UIHelp colorWithHexString:@"0xe6e8e9"];
    UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"bg_topbar_black"]];
    self.navBgImgeView  =  imageViewTmp;
    [imageViewTmp release];

//    self.channelView = [[AMChannel alloc] init];
//    self.channelView.request.industryId = AMCONST_HOME_DRESS;
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
    self.objMan = nil;
    self.contentData = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [UserDataUtils setNavigationHomeBar:YES];
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"h_clothing_navbar"] forBarMetrics:UIBarMetricsDefault];
//        [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"colthing_navbar"] forBarMetrics:UIBarMetricsDefault];
    }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"h_clothing_navbar"].CGImage;
    }
    
    //self.navigationController.navigationBar.backgroundColor = [UIColor clearColor]; 
    
    self.navigationController.navigationBar.hidden = NO;
    
}

-(void)viewDidAppear:(BOOL)animated
{
//    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
//        [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"colthing_navbar"] forBarMetrics:UIBarMetricsDefault];
//    }
//    else {
//        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:@"colthing_navbar"].CGImage;
//    }
}

-(void)viewWillDisappear:(BOOL)animated
{
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
     [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"bg_topbar.png"] forBarMetrics:UIBarMetricsDefault];
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
    [_objMan release];
    [_contentData release];
    
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
            menuItemViewTmp.frame = CGRectMake(menuItemViewTmp.frame.origin.x, menuItemViewTmp.frame.origin.y, 80, 70);
            menuItemViewTmp.label.text = [data objectForKey:@"name"];
            [menuItemViewTmp.imageView clear];
//            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x + 3, menuItemViewTmp.imageView.frame.origin.y, 60, 50);
            menuItemViewTmp.imageView.image = [UIImage imageNamed:[data objectForKey:@"imageName"]];
            
            
            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x, menuItemViewTmp.imageView.frame.origin.y , menuItemViewTmp.imageView.frame.size.width, menuItemViewTmp.imageView.frame.size.height);
            [menuItemViewTmp setLabelyPadding:-8 xPadding:0];
            menuItemViewTmp.label.font = [UIFont fontWithName:@"Arial-BoldMT" size:14.0f];
            menuItemViewTmp.label.textColor = [UIHelp colorWithHexString:@"0x333333"];
            menuItemViewTmp.button.adjustsImageWhenHighlighted = YES;
            menuItemViewTmp.layer.masksToBounds=YES;   
            //    menuItemView.layer.cornerRadius=1.0;   
            menuItemViewTmp.layer.borderWidth=0.5;   
            menuItemViewTmp.layer.borderColor=[[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor]; 
//            menuItemViewTmp.imageViewBackground.image = [UIImage imageNamed:[data objectForKey:@"imageName"]];
//            menuItemViewTmp.imageView.backgroundColor = [UIColor clearColor];
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
                       [NSDictionary dictionaryWithObjectsAndKeys:@"女装", @"name",@"nvzhuang", @"ID",@"h_clothing_list01", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"男装", @"name",@"nanzhuang", @"ID",@"h_clothing_list02", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"童装", @"name",@"tongzhuang", @"ID",@"h_clothing_list03", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"内衣", @"name",@"neiyi", @"ID",@"h_clothing_list04", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"运动", @"name",@"yundong", @"ID",@"h_clothing_list05", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"箱包", @"name",@"xiangbao", @"ID",@"h_clothing_list06", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"配饰", @"name",@"peishi", @"ID",@"h_clothing_list07", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"鞋靴", @"name",@"xiexue", @"ID",@"h_clothing_list08", @"imageName",nil],nil];
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
        [self.bannerView loadObjectsFromRemote];
    }
    if ([self.operationView.contentData count] == 0) {
        [self.operationView loadObjectsFromRemote];
    }
    if ([self.operation1.contentData count]==0) {
        [self.operation1 loadObjectsFromRemote];
    }
    if ([self.operation2.contentData count]==0) {
        [self.operation2 loadObjectsFromRemote];
    }
//    if ([self.channelView.contentData count]==0) {
//        [self.channelView loadObjectsFromRemote];
//    }
}

#pragma mark Home Common Methods
-(NSString*)commonHomeViewBackButtonTitle
{
    return @"服装服饰";
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
            return [AMOperationTableViewCell cellHeight];
            break;
        case 2:
            return [AliOperationTableViewCell cellHeight];
            break;  
        default:
            return AMCONST_HOME_DRESS_CHANNEL_HEIGHT * menuViewCount;
            
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
//    menuViewCount = [self.channelView.contentData count]/AMCONST_HOME_DRESS_MENUVIEW_COLUMNE;
//    if ([self.channelView.contentData count]%AMCONST_HOME_DRESS_MENUVIEW_COLUMNE) {
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
                cell.bannerView.request.industryId = AMCONST_HOME_DRESS;
                cell.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.bannerView.request.configName = AMCONST_HOME_BANNERS;
                [cell.bannerView loadObjectsFromRemote];
                
            }   
            
            cell.selectionStyle=UITableViewCellSelectionStyleNone; 
            return cell;
            
        }
            break;
        case 1:
        {
           AMOperationTableViewCell *cell = (AMOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMOperationTableViewCell createCell];
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_DRESS_OPERATION_HEIGHT + 2);
                cell.operationView.frame = CGRectMake(cell.frame.origin.x + 2, cell.frame.origin.y + 2, cell.frame.size.width - 4, AMCONST_HOME_DRESS_OPERATION_HEIGHT);
                cell.operationView.defaultImage.frame = CGRectMake(cell.operationView.defaultImage.frame.origin.x, cell.operationView.defaultImage.frame.origin.y, cell.operationView.frame.size.width, cell.operationView.frame.size.height);
                cell.operationView.opertationView.frame = CGRectMake(cell.operationView.opertationView.frame.origin.x, cell.operationView.opertationView.frame.origin.y, cell.operationView.frame.size.width, cell.operationView.frame.size.height);
                cell.operationView.maskImage.frame = CGRectMake(cell.operationView.maskImage.frame.origin.x, cell.operationView.maskImage.frame.origin.y, cell.operationView.frame.size.width, cell.operationView.frame.size.height);
                
                cell.operationView.request.industryId = AMCONST_HOME_DRESS;
                cell.operationView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operationView.request.configName = AMCONST_HOME_EVENT1;
                [cell.operationView loadObjectsFromRemote];
                cell.operationView.defaultImage.image = [UIImage imageNamed:@"h_clothing_bar"];
                [cell.operationView addTarget:self action:@selector(operationViewEvent1TouchUp:)  forControlEvents:UIControlEventTouchUpOutside];
                [cell.operationView addTarget:self action:@selector(operationViewEvent1TouchDown:)  forControlEvents:UIControlEventTouchDown];
                [cell.operationView addTarget:self action:@selector(operationViewEvent1TouchUpInside:)  forControlEvents:UIControlEventTouchUpInside];
                [cell.operationView addTarget:self action:@selector(operationViewEvent1TouchUp:) forControlEvents:UIControlEventTouchCancel];
                self.operationView = cell.operationView;
                UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, 1)];
                imageView.backgroundColor = [UIHelp colorWithHexString:@"0x9da3a9"];
                imageView.alpha = 0.5;
                [cell addSubview:imageView];
                [imageView release];
                cell.backgroundColor = [UIHelp colorWithHexString:@"0xf0f0f0"];
                
            }   
            
//            cell.operationView.request.transactionType = AMTRANSACTION_TYPE_HOME_EVENT1_LIST;
              
            cell.selectionStyle=UITableViewCellSelectionStyleNone; 
            return cell;
        }
            break;
        case 2:
        {
            AliOperationTableViewCell *cell = (AliOperationTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AliOperationTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AliOperationTableViewCell createCell];
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, 90);
                cell.operation1.frame= CGRectMake(cell.operation1.frame.origin.x, cell.frame.origin.y + 2, cell.operation1.frame.size.width, cell.frame.size.height - 5);
                cell.operation2.frame= CGRectMake(cell.operation2.frame.origin.x, cell.frame.origin.y + 2, cell.operation2.frame.size.width, cell.frame.size.height - 5);
                cell.operation1.request.industryId = AMCONST_HOME_DRESS;
                cell.operation1.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operation1.request.configName = AMCONST_HOME_EVENT2;
                cell.operation1.defaultImage.image = [UIImage imageNamed:@"h_clothing_new"];
                
                cell.operation2.request.industryId = AMCONST_HOME_DRESS;
                cell.operation2.request.summary    = AMCONST_HOME_SUMMARY;
                cell.operation2.request.configName = AMCONST_HOME_EVENT3;
                cell.operation2.defaultImage.image = [UIImage imageNamed:@"h_clothing_top"];
                
                [cell.operation1 loadObjectsFromRemote];
                [cell.operation2 loadObjectsFromRemote];
                
                [cell.operation1 addTarget:self action:@selector(operationTouchUp:)  forControlEvents:UIControlEventTouchUpInside];           
                [cell.operation2 addTarget:self action:@selector(operationTouchUp:) forControlEvents:UIControlEventTouchUpInside];
                [cell.operation1 addTarget:self action:@selector(operationTouchUpOutside:)  forControlEvents:UIControlEventTouchUpOutside];           
                [cell.operation2 addTarget:self action:@selector(operationTouchUpOutside:) forControlEvents:UIControlEventTouchUpOutside];
                [cell.operation1 addTarget:self action:@selector(operationTouchUpOutside:) forControlEvents:UIControlEventTouchCancel];
                [cell.operation2 addTarget:self action:@selector(operationTouchUpOutside:) forControlEvents:UIControlEventTouchCancel];
                [cell.operation1 addTarget:self action:@selector(operationTouchDown:)  forControlEvents:UIControlEventTouchDown];           
                [cell.operation2 addTarget:self action:@selector(operationTouchDown:) forControlEvents:UIControlEventTouchDown];
                self.operation1 = cell.operation1;
                self.operation2 = cell.operation2;
//                cell.operation1.backgroundColor = [UIHelp colorWithHexString:@"0xf0f0f0"];
//                cell.operation2.backgroundColor = [UIHelp colorWithHexString:@"0xf0f0f0"];
                cell.backgroundColor = [UIHelp colorWithHexString:@"0xf0f0f0"];
                
            }   
            
            
           
            cell.selectionStyle=UITableViewCellSelectionStyleNone; 
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
                cell.menuView.columnCount = AMCONST_HOME_DRESS_MENUVIEW_COLUMNE;
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_DRESS_CHANNEL_HEIGHT * menuViewCount);
                cell.menuView.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_DRESS_CHANNEL_HEIGHT * menuViewCount);
                self.menuView = cell.menuView;
                cell.menuView.scrollEnabled = NO;
//                cell.menuView.itemSize = CGSizeMake(80, 75);
                cell.menuView.yPadding = 0;
                cell.menuView.backgroundColor = [UIHelp colorWithHexString:@"0xfcfaf7"];
                cell.backgroundColor = [UIHelp colorWithHexString:@"0xfcfaf7"];
//                cell.menuView.topPadding = -10;
//                cell.menuView.bottomPadding = -5;
                cell.menuView.layer.masksToBounds=YES;   
                //    menuItemView.layer.cornerRadius=1.0;   
                cell.menuView.layer.borderWidth=1.0;   
                cell.menuView.layer.borderColor=[[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor]; 
            }    
            [cell.menuView reloadData];
            cell.selectionStyle=UITableViewCellSelectionStyleNone; 
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
-(void)operationTouchUp:(id)sender
{
    if ([sender isKindOfClass:[AliOperation2 class]]) {
//        if([self.operation2.contentData count]){
//            AMHomepageDressEvent1 *homepageDressEvent2 = [self.operation2.contentData objectAtIndex:0];
//            NSString *operation2ClickId = homepageDressEvent2.type;
//            [AMLogUtils appendLog: operation2ClickId];
        [AMLogUtils appendLog:INDUSTRIAL_DRESS_PAGE_FOUR];
            AMHotRankViewController *hotRankViewController =[[AMHotRankViewController alloc] initWithNibName:@"AMHotRankViewController" bundle:nil];
            hotRankViewController.parentTitle = @"首页";
            [self.navigationController pushViewController:hotRankViewController animated:YES];
            [hotRankViewController release];
            self.operation2.maskImage.alpha = 0.0f;
//        }
    }
    else {
//        if([self.operation1.contentData count]){
//            AMHomepageDressEvent1 *homepageDressEvent3 = [self.operation1.contentData objectAtIndex:0];
//            NSString *operation1ClickId = homepageDressEvent3.type;
//            [AMLogUtils appendLog: operation1ClickId];
        [AMLogUtils appendLog:INDUSTRIAL_DRESS_PAGE_THREE];
        AMNewProductsZoneViewController * newProductController = [[AMNewProductsZoneViewController alloc] initWithNibName:@"AMNewProductsZoneViewController" bundle:nil];
        [self.navigationController pushViewController:newProductController animated:YES];
        [newProductController release];
        self.operation1.maskImage.alpha = 0.0f;
//        }
    }
}
-(void)operationTouchUpOutside:(id)sender
{
    if ([sender isKindOfClass:[AliOperation2 class]]) {
        self.operation2.maskImage.alpha = 0.0f;
    }
    else {
        self.operation1.maskImage.alpha = 0.0f;
    }
}
-(void)operationTouchDown:(id)sender
{
    if ([sender isKindOfClass:[AliOperation2 class]]) {
        self.operation2.maskImage.alpha = 0.3f;
    }
    else {
        self.operation1.maskImage.alpha = 0.3f;
    }
}

-(void)operationViewEvent1TouchUp:(id)sender
{
    self.operationView.maskImage.alpha = 0.0f;
}
-(void)operationViewEvent1TouchUpInside:(id)sender
{
    [AMLogUtils appendLog:INDUSTRIAL_DRESS_PAGE_TWO];
    AMActivityListViewController *industrySelectController = [[AMActivityListViewController alloc] initWithNibName:@"AMActivityListViewController" bundle:nil ];
    industrySelectController.industryId = ACTIVITY_INDUSTRY_ID_OF_CLOTHING;
    [self.navigationController pushViewController:industrySelectController animated:YES];
    [industrySelectController release];
    self.operationView.maskImage.alpha = 0.0f;
}
-(void)operationViewEvent1TouchDown:(id)sender
{
    self.operationView.maskImage.alpha = 0.3f;
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
    return @"服装服饰";
}
#pragma mark MenuView Delegate Methods
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView
{
    //    return [self.channelView.contentData count]
    return [self.contentData count];
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index
{
    //用于从网络读取类目信息，用于以后扩展
//    NSDictionary *data = [self.channelView.contentData objectAtIndex:index];
//    NSString *homepageDressId = [data objectForKey:@"ID"];
//    NSString *homepageDressName = [data objectForKey:@"name"];
//    NSString *homepageDressImageUrl = [data objectForKey:@"imageUrl"];  
//    NSLog(@"homepageDressChilden.id: %@,homepageDressName:%@,homepageDressImageUrl: %@",homepageDressId,homepageDressName,homepageDressImageUrl);
    //以下代码表示直接从本地写死代码读取数据
    [AMLogUtils appendLog:INDUSTRIAL_DRESS_PAGE_FIVE];
    NSString *homepageDressId = [[self.sourceData objectAtIndex:index ] objectForKey:@"ID"];
    NSString *homepageDressName = [[self.sourceData objectAtIndex:index ] objectForKey:@"name"];
    AMSubpageDressViewController *subpageViewController = [[AMSubpageDressViewController alloc] init];
    subpageViewController.categoryName = homepageDressName;
    [self.navigationController pushViewController:subpageViewController animated:YES];
    [subpageViewController release];

}

- (AMMenuItemView *)menuView:(AMMenuView *)menuView ItemViewForRowAtIndex:(NSInteger)index
{
    //调用本地信息，不再调用服务器数据
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    
    return menuItemView;
    //调用网络信息，用于以后扩展
//    if ([self.channelView.contentData count] > 0) {
//        AMMenuItemView *menuItemView = (AMMenuItemView *)[[self.channelView.contentData objectAtIndex:index] objectForKey:@"view"];
//        
//        if (index <=  [self.sourceData count]) {
//            menuItemView.imageView.image = [UIImage imageNamed:[[self.sourceData objectAtIndex:index ] objectForKey:@"imageName"]];
//        }
////        menuItemView.imageView.image
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
    menuItemView.backgroundColor = [UIHelp colorWithHexString:@"0xf2f2f2"];
}
- (void)menuView:(AMMenuView*)menuView  ItemPressedAtIndex:(NSInteger)index
{
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    menuItemView.backgroundColor = [UIHelp colorWithHexString:@"0xfcfaf7"];
}
- (void)menuView:(AMMenuView*)menuView  ItemPressedUpOutsideActionAtIndex:(NSInteger)index
{
    AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
    menuItemView.backgroundColor = [UIHelp colorWithHexString:@"0xfcfaf7"];
}


@end

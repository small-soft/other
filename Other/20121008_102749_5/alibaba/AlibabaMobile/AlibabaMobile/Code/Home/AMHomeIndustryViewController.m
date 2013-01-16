//
//  AMHomeDressViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomeIndustryViewController.h"
#import "AMBannerTableViewCell.h"
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
#import "AMChannelTableViewCell.h"
#import "AMMenuView.h"
#import "AMAdvView.h"
#import "AMChannel.h"
#import "AMMarketpriceViewController.h"
#import "AMSubpageWithMenuViewController.h"
#import "AMBrandsViewController.h"
#import "AMRecommendBrandsDataLoader.h"
#import "AMMainSubViewCell.h"
#import "UIView+UIViewUtil.h"
#import "Utils.h"

extern NSInteger const HOME_LISTITEM_NEWS;
extern NSInteger const HOME_LISTITEM_QUOTATIONS;
extern NSInteger const HOME_LISTITEM_CATEGORIES;
extern NSInteger const HOME_LISTITEM_MAGAZINE;
extern NSInteger const HOME_LISTITEM_HOTRANK;//热销排行-->add by xiaowen
extern NSInteger const HOME_LISTITEM_NEWPRODUCTS;//新品专区-->add by xiaowen

@interface AMHomeIndustryViewController ()

@property (nonatomic,retain) AMChannel      *channelView;
@property (nonatomic,retain) AMMenuView     *menuView;
@property (nonatomic,retain) AMAdvView      *bannerView;
@property (nonatomic,retain) AMRecommendBrandsDataLoader *brandsLoader;
@property (nonatomic,retain) AMMenuView *brandsView;

@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) HJObjManager *objMan;
@end

@implementation AMHomeIndustryViewController
@synthesize channelView = _channelView;
@synthesize bannerView=_bannerView;
@synthesize menuView = _menuView;
@synthesize contentData = _contentData;
@synthesize objMan = _objMan;
@synthesize brandsLoader = _brandsLoader;
@synthesize brandsView = _brandsView;

#pragma - mark
#pragma mark vc lifecycle
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
    menuViewCount = 4;

    [self changePickFrame:7 yframe:0];
    [self setUpFuncListTable];
    [self loadBrandsData];
}

- (void)viewDidUnload
{
    self.channelView = nil;
    self.menuView = nil;
    self.bannerView = nil;
    self.contentData = nil;
    self.objMan = nil;
    self.brandsView = nil;
    self.brandsLoader = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
    // 设置导航栏
    [super viewWillAppear:animated];
    [UserDataUtils setNavigationHomeBar:YES];
    [self setupNavBarWithImageName:@"h_industrial_navbar"];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [self setupNavBarWithImageName:@"bg_topbar"];
    [super viewWillDisappear:animated];
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_channelView release];
    [_bannerView release];
    [_menuView release];
    [_contentData release];
    [_objMan release];
    [_brandsView release];
    [_brandsLoader release];
    
    [super dealloc];
}

#pragma - mark
#pragma mark attrs setter&getter
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
            
            menuItemViewTmp.imageView.frame = CGRectMake(1, 9, 72, 58);
            menuItemViewTmp.label.font = [UIFont boldSystemFontOfSize:14];
            menuItemViewTmp.label.textAlignment = UITextAlignmentCenter;
            menuItemViewTmp.label.textColor = RGB(0x33, 0x33, 0x33);
            menuItemViewTmp.label.frame = CGRectMake(0, [menuItemViewTmp.imageView endY] + 4, menuItemViewTmp.frame.size.width, 14);
            menuItemViewTmp.label.textAlignment = UITextAlignmentCenter;
//            menuItemViewTmp.imageView.frame = CGRectMake(menuItemViewTmp.imageView.frame.origin.x, menuItemViewTmp.imageView.frame.origin.y + 1, menuItemViewTmp.imageView.frame.size.width, menuItemViewTmp.imageView.frame.size.height);
//            menuItemViewTmp.label.frame = CGRectMake(menuItemViewTmp.label.frame.origin.x, menuItemViewTmp.label.frame.origin.y + 10, menuItemViewTmp.label.frame.size.width, menuItemViewTmp.label.frame.size.height);
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
                       [NSDictionary dictionaryWithObjectsAndKeys:@"机械及行业设备", @"name",@"jixiejihangyeshebei", @"ID",@"h_industrial_list01", @"imageName",@"h_industrial_list01_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"电工电器", @"name",@"diangongdianqi", @"ID",@"h_industrial_list02", @"imageName",@"h_industrial_list02_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"电子元器件", @"name",@"dianziyuanqijian", @"ID",@"h_industrial_list03", @"imageName",@"h_industrial_list03_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"五金工具", @"name",@"wujingongju", @"ID",@"h_industrial_list04", @"imageName",@"h_industrial_list04_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"照明工业", @"name",@"zhaominggongye", @"ID",@"h_industrial_list05", @"imageName",@"h_industrial_list05_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"安全防护", @"name",@"anquanfanghu", @"ID",@"h_industrial_list06", @"imageName",@"h_industrial_list06_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"仪器仪表", @"name",@"yiqiyibiao", @"ID",@"h_industrial_list07", @"imageName",@"h_industrial_list07_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"传媒广电", @"name",@"chuanmeiguangdian", @"ID",@"h_industrial_list08", @"imageName",@"h_industrial_list08_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"汽摩及配件", @"name",@"qimojipeijian", @"ID",@"h_industrial_list09", @"imageName",@"h_industrial_list09_p", @"imagePressName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"通信产品", @"name",@"tongxinchanpin", @"ID",@"h_industrial_list10", @"imageName",@"h_industrial_list10_p", @"imagePressName",nil],nil];
    }
    return _sourceData;
}

#pragma - mark
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
        self.bannerView.request.industryId = AMCONST_HOME_PRODUCT;
        self.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
        self.bannerView.request.configName = AMCONST_HOME_BANNERS;
        [self.bannerView loadObjectsFromRemote];
    }
    if ([self.brandsLoader.contentData count]==0) {
        self.brandsLoader.request.industryId = AMCONST_HOME_PRODUCT;
        self.brandsLoader.request.summary    = AMCONST_HOME_SUMMARY;
        self.brandsLoader.request.configName = @"brandsios";
        [self.brandsLoader loadObjectsFromRemote];
    }
}

#pragma mark Home Common Methods
-(NSString*)commonHomeViewBackButtonTitle
{
    return @"工业品";
}

#pragma - mark
#pragma mark Table View Data Source Methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    switch (row) {
        case 0:
            return [AMBannerTableViewCell cellHeight];
            break;
        case 1:
            return 86.;
            break;
        default:
            return AMCONST_HOME_INDUSTRY_CHANNEL_HEIGHT * 4;
            
            break;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section
{
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
                cell.bannerView.request.industryId = AMCONST_HOME_PRODUCT;
                cell.bannerView.request.summary    = AMCONST_HOME_SUMMARY;
                cell.bannerView.request.configName = AMCONST_HOME_BANNERS;
                
                [cell.bannerView loadObjectsFromRemote];
            }   
           
            return cell;
            
        }
            break;
        case 1:
        {
            // 品牌推荐banner
            AMMainSubViewCell *brandsCell = (AMMainSubViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMMainSubViewCell cellIdentifer]];
            if (brandsCell == nil)  
            {
                brandsCell =  [AMMainSubViewCell createCell];
                // 设置背景
                UIView *cellBgView = [[[UIView alloc]init]autorelease];
                cellBgView.backgroundColor = RGB(0xc1, 0xc9, 0xd0);
                brandsCell.backgroundView = cellBgView;
                
                UIImage *img = [UIImage imageNamed:@"h_industrial_bg.png"];
                UIImageView *bgView = [[UIImageView alloc]init];
                bgView.frame = CGRectMake(70, 5, 249, 81);
                bgView.image = [img stretchableImageWithLeftCapWidth:img.size.width/2 topCapHeight:0];
                [brandsCell insertSubview:bgView belowSubview:brandsCell.subView];
                [bgView release];
                
                // 设置左侧主视图
                brandsCell.mainView.backgroundColor = RGB(0xc1, 0xc9, 0xd0);
                brandsCell.mainView.frame = CGRectMake(3, 5, 67, 81);
                brandsCell.mainView.layer.borderWidth = 0;
                
                UIImageView *imageView = [[[UIImageView alloc]init]autorelease];
                imageView.image = [UIImage imageNamed:@"h_industrial_more_n"];
                imageView.highlightedImage = [UIImage imageNamed:@"h_industrial_more_p"];
                
                imageView.frame = CGRectMake(0, 0, brandsCell.mainView.frame.size.width, brandsCell.mainView.frame.size.height);
                [brandsCell.mainView insertSubview:imageView atIndex:0];           
                [brandsCell.mainView addTarget:self action:@selector(showMoreBrands:)  forControlEvents:UIControlEventTouchUpInside];
                [brandsCell.mainView  addTarget:self action:@selector(brandMainTouchDown:) forControlEvents:UIControlEventTouchDown];
                [brandsCell.mainView  addTarget:self action:@selector(brandMainTouchUpOutside:)  forControlEvents:UIControlEventTouchUpOutside]; 
                
                // 设置右侧子视图
                brandsCell.subView.menuDelegate = self;
                self.brandsView = brandsCell.subView;
                self.brandsLoader.menuView = brandsCell.subView;
                brandsCell.subView.frame = CGRectMake(67, 5, 247, 81);
                brandsCell.subView.scrollEnabled = NO;
                brandsCell.subView.itemSize = CGSizeMake(57, 30);
                brandsCell.subView.columnCount = 4;  
                brandsCell.subView.backgroundColor = RGB(0xc1, 0xc9, 0xd0);
                brandsCell.subView.yPadding = 4;
                brandsCell.subView.topPadding = 4;
                brandsCell.subView.leftPadding = 0;
            }
            
           
            [brandsCell.subView reloadData];
            
            return brandsCell;

        }
            break;
        default:
        {
            AMChannelTableViewCell *cell = (AMChannelTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMChannelTableViewCell cellIdentifer]];
            if (cell == nil)  
            {
                cell = [AMChannelTableViewCell createCell];
                cell.frame = CGRectMake(cell.frame.origin.x, cell.frame.origin.y, cell.frame.size.width, AMCONST_HOME_INDUSTRY_CHANNEL_HEIGHT * menuViewCount);
                cell.menuView.menuDelegate = self;
                self.menuView = cell.menuView;
                
                cell.menuView.scrollEnabled = NO;
                cell.menuView.columnCount = AMCONST_HOME_INDUSTRY_MENUVIEW_COLUMNE;
                cell.menuView.itemSize = CGSizeMake(95, 88);
                cell.menuView.yPadding = 0;
                cell.menuView.backgroundColor = RGB(0xc1, 0xc9, 0xd0);
                
                // 设置背景
                int height = 88;
                UIImage *imageTmp = [UIImage imageNamed:@"h_industrial_list_bg"];
                for (int i = 0; i<[self.contentData count]/cell.menuView.columnCount + 1 ; i++) {
                    UIImageView *imageViewTmp = [[UIImageView alloc] initWithFrame:CGRectMake(cell.frame.origin.x, cell.frame.origin.y + 6 + height * i, cell.frame.size.width, height)];
                    imageViewTmp.image = imageTmp;
                    [cell.menuView insertSubview:imageViewTmp atIndex:0];
                    [imageViewTmp release];
                }

            } 

            [cell.menuView reloadData];
            return cell;
        }
            break;
    }
    
    return nil;
    
}

#pragma - mark
#pragma mark event action
-(void)showMoreBrands:(UIView *)sender
{
    
    AMBrandsViewController * con = [[[AMBrandsViewController alloc ] init] autorelease];
    [self.navigationController pushViewController:con animated:YES];
    
    [self setHighLighted:NO forView:sender];
}

//按下后背景颜色变化，按下后移开背景颜色变回原样
-(void)brandMainTouchDown:(UIControl *)sender
{
    [self setHighLighted:YES forView:sender];

}
-(void)brandMainTouchUpOutside:(UIControl *)sender
{
    [self setHighLighted:NO forView:sender];
}

-(void)setHighLighted:(BOOL)highLighted forView:(UIView *)uiView {
    for (UIView *obj in uiView.subviews) {
        if ([obj isKindOfClass:[UIImageView class]]) {
            ((UIImageView *)obj).highlighted = highLighted;
        }
    }
}

#pragma - mark
#pragma mark private methods
-(void) setUpFuncListTable {
    UIView *bg = [[UIView alloc]init];
    bg.backgroundColor = RGB(0xc1, 0xc9, 0xd0);
    self.funcListTable.backgroundView = bg;
    self.funcListTable.backgroundColor = RGB(0xc1, 0xc9, 0xd0);
    self.funcListTable.separatorStyle = UITableViewCellSeparatorStyleNone;
    UIImageView *imageViewTmp= [[UIImageView alloc] initWithImage: [UIImage imageNamed:@"bg_topbar_black"]];
    self.navBgImgeView  =  imageViewTmp;
    [imageViewTmp release];
}

-(void) loadBrandsData {
    self.brandsLoader = [[AMRecommendBrandsDataLoader alloc]init];
    self.brandsLoader.request.industryId = AMCONST_HOME_PRODUCT;
    self.brandsLoader.request.summary    = AMCONST_HOME_SUMMARY;
    self.brandsLoader.request.configName = @"brandsios";
    self.brandsLoader.delegate = self; 
    self.brandsLoader.menuView = self.brandsView;
    [self.brandsLoader loadObjectsFromRemote];
}

-(void) setupNavBarWithImageName:(NSString *)imageName {
    if([UINavigationBar respondsToSelector:@selector(appearance)]) {
        [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:imageName] forBarMetrics:UIBarMetricsDefault];
    }
    else {
        self.navigationController.navigationBar.layer.contents = (id)[UIImage imageNamed:imageName].CGImage;
    }
    
    [self.navigationController setNavigationBarHidden:NO animated:YES];
}

#pragma - mark
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

#pragma - mark
#pragma mark AliChannel Delegate Methods
-(void)AliChannelReloadData
{
    [self.funcListTable reloadData];
}

#pragma - mark
#pragma mark AliAdv Delegate Methods
-(UIViewController*)superController;
{
    return self;
}
-(NSString*)superControllerName
{
    return @"工业品";
}

#pragma - mark
#pragma mark MenuView Delegate Methods
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView
{
    //    return [self.channelView.contentData count];
    return menuView == self.brandsView ? [self.brandsLoader.contentData count]:[self.contentData count];
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index
{
    if (((AMMainSubViewCell*)[self.funcListTable cellForRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0]]).subView == menuView) {
        //        NSInteger brandId = sender.tag;
        
        //以brandId为参数，进入下一个viewController
        //        NSLog(@"BrandId:%d ; BrandName:%@", brandId, sender.boxTitle.text);
        [AMLogUtils appendLog:INDUSTRIAL_PRODUCTER_PAGE_ONE];
        NSString *name = [[self.brandsLoader.contentData objectAtIndex:index] objectForKey:@"name"];
        
        AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
        //        controller.catId = homepageDressId;
        //        controller.catName = @"工业品";
        controller.parentTitle = self.navigationItem.title;
        //controller.parentCatId= subpageRecommendOrHistoryChildren.ID;
        //    controller.categoryFilterSelectedItem = index;
        controller.keyWords = name;
        controller.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:controller animated:YES];
        [controller release];
        
    } else {
        
        if(((AMChannelTableViewCell*)[self.funcListTable cellForRowAtIndexPath:[NSIndexPath indexPathForRow:2 inSection:0]]).menuView == menuView){
            [AMLogUtils appendLog:INDUSTRIAL_PRODUCTER_PAGE_TWO];
            NSString *homepageDressId = [[self.sourceData objectAtIndex:index ] objectForKey:@"ID"];
            NSString *homepageDressName = [[self.sourceData objectAtIndex:index ] objectForKey:@"name"];
            
            AMSubpageWithMenuViewController *subpageViewController = [[AMSubpageWithMenuViewController alloc] init];
            //    subpageViewController.homepageDressRequest.industryId =AMCONST_HOME_PRODUCT;
            subpageViewController.subpageRequest.industryId = AMCONST_HOME_PRODUCT;
            subpageViewController.subpageRequest.categoryId = homepageDressId;
            subpageViewController.categoryName = homepageDressName;
            //    subpageViewController.indexPath = [NSIndexPath indexPathForRow:index inSection:0];
            [self.navigationController pushViewController:subpageViewController animated:YES];
            [subpageViewController release];
        }
    }


}

- (AMMenuItemView *)menuView:(AMMenuView *)menuView ItemViewForRowAtIndex:(NSInteger)index
{
    if (menuView == self.brandsView) {
        if ([self.brandsLoader.contentData count] > 0) {
            AMMenuItemView *menuItemView = [[self.brandsLoader.contentData objectAtIndex:index] objectForKey:@"view"];
            // 设置背景
            UIImage* imageBackground = [UIImage imageNamed:@"h_industrial_morelist_n.png"];
            menuItemView.imageViewBackground.image = imageBackground;
            
            // 设置蒙板
            menuItemView.maskImageView.image = [UIImage imageNamed:@"h_industrial_morelist_p"];
            menuItemView.maskImageView.frame = menuItemView.imageViewBackground.frame;
            
            return menuItemView;
        }
        
        
    } else {
        //调用本地信息，不再调用服务器数据
        AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
//        menuItemView.imageView.frame = CGRectMake(7, 8, 80, 64);
//        menuItemView.label.font = [UIFont boldSystemFontOfSize:14];
//        menuItemView.label.textAlignment = UITextAlignmentCenter;
//        menuItemView.label.textColor = RGB(0x33, 0x33, 0x33);
//        menuItemView.label.frame = CGRectMake(0, [menuItemView.imageView endY] + 5, menuItemView.frame.size.width, 14);
//        menuItemView.label.textAlignment = UITextAlignmentCenter;
        
        
        
        return menuItemView;
    }
    
    return nil;
}

//更换类目点击时的背景
- (void)menuView:(AMMenuView*)menuView  ItemPressedDownAtIndex:(NSInteger)index
{
    if ([menuView isEqual:(self.menuView)]) {
        AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
        menuItemView.imageView.image = [UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey: @"imagePressName"]];
    } else if ([menuView isEqual:(self.brandsView)]) {
        AMMenuItemView *menuItemView = [[self.brandsLoader.contentData objectAtIndex:index] objectForKey:@"view"];
        menuItemView.maskImageView.alpha = 0.3f;
    }
    
}
- (void)menuView:(AMMenuView*)menuView  ItemPressedAtIndex:(NSInteger)index
{
    if ([menuView isEqual:(self.menuView)]) {
        AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
        menuItemView.imageView.image = [UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey: @"imageName"]];
        
    } else if ([menuView isEqual:(self.brandsView)]) {
        AMMenuItemView *menuItemView = [[self.brandsLoader.contentData objectAtIndex:index] objectForKey:@"view"];
        menuItemView.maskImageView.alpha = 0.0f;
    }
}
- (void)menuView:(AMMenuView*)menuView  ItemPressedUpOutsideActionAtIndex:(NSInteger)index
{
    if ([menuView isEqual:(self.menuView)]) {
        AMMenuItemView *menuItemView = [[self.contentData objectAtIndex:index] objectForKey:@"view"];
        menuItemView.imageView.image = [UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey: @"imageName"]];
    } else if ([menuView isEqual:(self.brandsView)]) {
        AMMenuItemView *menuItemView = [[self.brandsLoader.contentData objectAtIndex:index] objectForKey:@"view"];
        menuItemView.maskImageView.alpha = 0.0f;
    }
}

@end

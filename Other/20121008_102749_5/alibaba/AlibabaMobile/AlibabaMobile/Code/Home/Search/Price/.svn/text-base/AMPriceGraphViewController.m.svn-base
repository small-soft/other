//
//  AMPriceGraphViewController.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//
#import "ConstDef.h"
#import "LoginToken.h"
#import "AMCUDResult.h"
#import "AMFavoriteRequest.h"
#import "AliToastView.h"
#import "AMPriceBaseItem.h"
#import "UIHelp.h"
#import "AliImageButton.h"
#import "AliImageControlFactory.h"

#import "AMPriceGraphViewController.h"
#import "GraphNodeLine.h"

#import "AMPriceGraghListResult.h"
#import "AMPriceGraghListRequest.h"
#import "AMIMViewController.h"
#import "AMNavigationBackButton.h"


@interface AMPriceGraphViewController ()

@property (nonatomic, retain) AMPriceGraghListRequest *request;
@property (nonatomic, retain) AMFavoriteRequest *addFavoriteRequset;
@property (nonatomic, assign) NSUInteger mGraphFilter;


@end

@implementation AMPriceGraphViewController
@synthesize graphView;
@synthesize mPickView;
@synthesize myNavigationBar,myNavigationItem,myRightNavigationItem;
@synthesize myView;
@synthesize lableInfo;
@synthesize graphNodeList;
@synthesize lists, gNodelists, sourceFromName ,themeId, themeName , categroyId;
@synthesize request = _request;
@synthesize themeRequstId,sourceFomeRequstId,areaRequstId;
@synthesize sourceAddressName;
@synthesize mGraphFilter;
@synthesize addFavoriteRequset = _addFavoriteRequset;
@synthesize navigateTitleName,isPriceFavorited;

//价格内容
- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];	
    
//    // Register our mappings with the provider
//	RKObjectMapping* offerResultMapping = [AMPriceGraghListResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: offerResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SEARCH_PRICE_GRAGH usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPriceGraghListResult class]];
            loader.objectMapping = [AMPriceGraghListResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
    //[super loadObjectsFromRemote];
}
//加入收藏
- (void)addPriceFavorite {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* cudResultMapping = [AMCUDResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: cudResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRICE_FAV_ADD usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCUDResult class]];
            loader.objectMapping = [AMCUDResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.addFavoriteRequset;
    }];
}
/*----------------------------
 
----------------------------*/
-(AMFavoriteRequest*)addFavoriteRequset
{
    if (_addFavoriteRequset==nil) {
        _addFavoriteRequset = [[AMFavoriteRequest alloc] init];
    }
    return _addFavoriteRequset;
}

-(AMPriceGraghListRequest*)request
{
    if (_request==nil) {
        _request = [[AMPriceGraghListRequest alloc] init];
    }
    
    _request.areaId=self.areaRequstId;
    _request.themeId=self.themeRequstId;
    _request.sourceFormId = self.sourceFomeRequstId;
    
    NSLog(@"%@",_request);
    return _request;
}
/*----------------------------
 
----------------------------*/
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
    // Do any additional setup after loading the view from its nib.
    // Initialization code
    /*if (lists == nil) {
        lists = [[NSMutableArray arrayWithCapacity:0] retain];
        NSLog(@"lists init in AmpriceGraph viewDidLoad retainCount : %d",[lists retainCount]);
    }*/
    if (gNodelists == nil) {
        gNodelists = [[NSMutableArray alloc] initWithCapacity:0];
//        gNodelists = [NSMutableArray arrayWithCapacity:0];
    }
///////////////// scrollView
    [scrollView setMinimumZoomScale:0.5f];
    [scrollView setMaximumZoomScale:5.0f];
    scrollView.decelerationRate = UIScrollViewDecelerationRateNormal;
    
    [self.mLoadingView showLoadingView];
    self.mLoadingView.frame= CGRectMake(0, 0,FRAMEWIDTH ,FRAMEHEIGHT);
    self.mLoadingView.noDataView.frame = CGRectMake(0, 0,FRAMEWIDTH ,FRAMEHEIGHT);
    self.mLoadingView.loadingView.frame = CGRectMake(0, 0,FRAMEWIDTH ,FRAMEHEIGHT);
    self.mLoadingView.loadFailedView.frame = CGRectMake(0, 0,FRAMEWIDTH ,FRAMEHEIGHT);
    [self loadObjectsFromRemote];
    lableInfo.textColor = [UIColor colorWithRed:102/255.0f green:102/255.0f blue:102/255.0f alpha:1.0f];
    lableInfo.text = [NSString stringWithFormat:@"(产品名称:未知 产地/产商:未知 单位:吨)"];
    lableInfo.backgroundColor = [UIColor colorWithRed:235/255.0f green:235/255.0f blue:235/255.0f alpha:1.0f];
///////////////// graphNodeList
    GraphNodeList *graphNodeListTmp = [GraphNodeList loadGraphInfoList:CGRectMake(0, 0,FRAMEWIDTH ,FRAMEHEIGHT )];
    self.graphNodeList = graphNodeListTmp;
    [graphNodeListTmp release];
    graphNodeList.dataSource = self;
    graphNodeList.backgroundColor = [UIColor clearColor];
	graphNodeList.drawAxisX = YES;
	graphNodeList.drawAxisY = YES;
	graphNodeList.drawGridX = YES;
	graphNodeList.drawGridY = YES;
    [graphNodeList reloadData];
/////////////////
    [scrollView setContentSize:(graphNodeList.frame).size];
    [scrollView addSubview:self.graphNodeList];
///////////////// graphView
    S7GraphView *graphViewTmp = [[S7GraphView alloc] initWithFrame:CGRectMake(scrollView.frame.origin.x, scrollView.frame.origin.y, FRAMEWIDTH ,FRAMEHEIGHT )];
	self.graphView = graphViewTmp;
    [graphViewTmp release];
	graphView.dataSource = self;
    graphView.backgroundColor = [UIColor colorWithRed:245/255.0f green:245/255.0f blue:245/255.0f alpha:1.0f];
	graphView.drawAxisX = YES;
	graphView.drawAxisY = YES;
	graphView.drawGridX = YES;
	graphView.drawGridY = YES;
    [graphView reloadData];
	[self.view addSubview:graphView];
/////////////////
    [self.view addSubview:lableInfo];
    [self.view addSubview:scrollView];
///////////////// mPickView
    AMGraphPickView *mPickViewTmp = [AMGraphPickView createView];
    self.mPickView = mPickViewTmp;
    [mPickViewTmp release];
//    self.mPickView = [AMGraphPickView createView];

    self.mPickView.dataSource = self;
    self.mPickView.backgroundColor = [UIColor clearColor];
    self.mGraphFilter = self.mPickView.mGraphFilter;
    //self.mPickView.transform = CGAffineTransformMakeRotation(3.141592656/2);
    //self.navigationItem.titleView = mPickView;
///////////////// navigationItem.rightButton
    
    //////////myNavigationBar
    self.myNavigationBar.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
    self.myNavigationItem = [[UINavigationItem alloc] initWithTitle:nil];    
    //创建一个左边按钮  
    if (navigateTitleName == nil) {
        self.navigateTitleName = @"价格行情";
    }
    AMNavigationBackButton *leftButton = [[AMNavigationBackButton alloc] initWithTitle:navigateTitleName];
    leftButton.navigationBackDelegate = self;
    //创建一个右边按钮 
    self.myRightNavigationItem = [[UIBarButtonItem alloc] init];
    [self setTitleBar:@""];
    //设置导航栏内容  
    self.myNavigationItem.titleView = mPickView;
    //把左右两个按钮添加入导航栏集合中  
    //[self.myNavigationItem setLeftBarButtonItem:self.mBackButton];  
    self.myNavigationItem.leftBarButtonItem = leftButton;
    [leftButton release];
    //[self.myNavigationItem setLeftBarButtonItem:leftButton];   
    //[navigationItem setRightBarButtonItem:rightButton];
    //把导航栏集合添加入导航栏中，设置动画关闭  
    [self.myNavigationBar pushNavigationItem:myNavigationItem animated:YES];  
    
    //把导航栏添加到视图中  
    [self.view addSubview:myNavigationBar];   
    
    //[UIView beginAnimations:nil context:nil];
    self.view.transform = CGAffineTransformMakeRotation(3.141592656/2);
    //[UIView commitAnimations];
    //[self.navigationController setNavigationBarHidden:YES animated:YES];
    //[self viewWillAppear:YES];
}

-(void)viewWillAppear:(BOOL)animated
{
    [self.mPickView viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [[UIApplication sharedApplication] setStatusBarHidden:YES animated:NO];
    /*[UIView beginAnimations:nil context:nil];
    //self.navigationItem.titleView.transform = CGAffineTransformMakeRotation(3.141592656/2);
    self.view.transform = CGAffineTransformMakeRotation(3.141592656/2);
    //self.view.frame = CGRectMake(0, 0, 220 , 480);
    //self.graphNodeList.frame = CGRectMake(0, 0, 200 , 480);
    //[graphNodeList reloadData];
    /////////////////
    //[scrollView setContentSize:CGSizeMake(220,480)];
    //scrollView.transform = CGAffineTransformMakeRotation(3.141592656/2);
    ///////////////// graphView
	//self.graphView.frame = CGRectMake(scrollView.frame.origin.x, scrollView.frame.origin.y, graphNodeList.frame.size.width , graphNodeList.frame.size.height);
    //[graphView reloadData];
    [UIView commitAnimations];*/
}

-(void)viewDidAppear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:YES animated:NO];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:NO animated:NO];
    [UIApplication sharedApplication].statusBarHidden = NO;
}

- (void)viewDidUnload
{
    [gNodelists release];
    gNodelists = nil;
    self.graphView = nil;
    self.graphNodeList = nil;
    self.mPickView = nil;
    self.myNavigationItem = nil;
    self.navigateTitleName = nil;
    self.myRightNavigationItem = nil;
    [_addFavoriteRequset release];
    _addFavoriteRequset = nil;
    [_request release];
    _request = nil;
    scrollView = nil;
    self.lableInfo = nil;
    self.myNavigationBar = nil;
    //self.lists = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)dealloc {
    [graphNodeList removeFromSuperview];
    [graphView removeFromSuperview];
    [lableInfo removeFromSuperview];
    [scrollView removeFromSuperview];
    [self.mPickView removeFromSuperview];
    self.myNavigationItem = nil;
//    [myNavigationItem release];
    [myNavigationBar release];
    [myRightNavigationItem release];
    
    [_addFavoriteRequset release];

    self.graphNodeList = nil;
    self.gNodelists = nil;
    self.mPickView = nil;
    self.graphView  =nil;
    self.lableInfo = nil;
    scrollView = nil;
    self.lists = nil;
    [_request release];
    [sourceFromName release];
    [themeId release];
    [themeName release];
    [categroyId release];
    [themeRequstId release];
    [areaRequstId release];
    [sourceFomeRequstId release];
    [navigateTitleName release];
    [super dealloc];
}
/*----------------------------*/
//rightButtonItem
/*----------------------------*/
-(void) setTitleBar:(NSString *)title
{
    
    btnBackImg = [UIImage imageNamed:@"btn_tb_normal"];
    btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
    btnBackImgPressed = [UIImage imageNamed:@"btn_tb_v"];
    btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
    
    
    if (self.isPriceFavorited) {
        [self setupTitleBarFav];
    }
    else {
        UIButton *favBtn = [[UIButton alloc] init];
        [favBtn setBackgroundImage:btnBackImg forState:UIControlStateNormal];
        [favBtn setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
        [favBtn setImage:[UIImage imageNamed:@"icon_aliww_fav_01"] forState:UIControlStateNormal];
        favBtn.frame = CGRectMake(0, 0, 44, 30);
        
        [favBtn addTarget:self action:@selector(addFavPrice) forControlEvents:UIControlEventTouchUpInside];
        self.myRightNavigationItem.customView = favBtn;
        self.myNavigationItem.rightBarButtonItem = myRightNavigationItem;
        [favBtn release];
    }
    //[super setNavigationRightItem:favBtn];

}

- (void) setupTitleBarFav
{
    //custome title label
    //[self setTitle:@"产品详情"];
    
    
    //add favorite button
    AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_SUCCESS_EXTEND_BTN];
    [favBtn setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [favBtn setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    favBtn.frame = CGRectMake(0, 0, 44, 30);
    
    [favBtn addTarget:self action:@selector(addFavPrice) forControlEvents:UIControlEventTouchUpInside];
    self.myRightNavigationItem.customView = favBtn;
    self.myNavigationItem.rightBarButtonItem = myRightNavigationItem;
    //[super setNavigationRightItem:favBtn]; 
}

- (void) navigationBack
{
    [self.navigationController setNavigationBarHidden:NO animated:YES];
    [UIApplication sharedApplication].statusBarHidden = NO;
    [super navigationBack];
}


-(void) addFavPrice {
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        [UIApplication sharedApplication].statusBarHidden = NO;
        [self.navigationController pushViewController:nextController animated:YES];
        [self.navigationController setNavigationBarHidden:NO animated:YES];
        [nextController release];
    }else{
        self.addFavoriteRequset.requestURL=OCEAN_API_URL_PRICE_FAV_ADD;
        self.addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD;
        
        self.addFavoriteRequset.themeId = [self.themeRequstId stringValue];
        self.addFavoriteRequset.sourceFromId = [self.sourceFomeRequstId stringValue];
        self.addFavoriteRequset.area = [self.areaRequstId stringValue];
        self.addFavoriteRequset.memberId=[LoginToken getLoginUserName];
        [self addPriceFavorite];
 
    }
}
/*----------------------------*/

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    ///return (interfaceOrientation == UIDeviceOrientationLandscapeLeft);
    return NO;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{

}

#pragma mark -
#pragma mark S7GraphViewDataSource

- (NSUInteger)graphViewNumberOfPlots:(UIView *)graphView {	
	/* Return the number of plots you are going to have in the view. 1+ */
	return 1;
}

- (NSArray *)graphViewXValues:(UIView *)graphView {
	
	/* An array of objects that will be further formatted to be displayed on the X-axis.
     The number of elements should be equal to the number of points you have for every plot. */
	NSMutableArray *array = [[NSMutableArray alloc] initWithCapacity:0];
    for (GraphNodeLine *gNodeLine in lists) {
        [array addObject:gNodeLine.xVlaues];
    }
    
	
	return [array autorelease];
}

- (NSArray *)graphView:(UIView *)graphView yValuesForPlot:(NSUInteger)plotIndex {
	
	/* Return the values for a specific graph. Each plot is meant to have equal number of points.
     And this amount should be equal to the amount of elements you return from graphViewXValues: method. */

    NSMutableArray *array = [[NSMutableArray alloc] initWithCapacity:0];
    for (GraphNodeLine *gNodeLine in lists) {
        [array addObject:gNodeLine.yVlaues];
    }
    
	return [array autorelease];
}

//用于返回所需的GraphNodeList列表
- (NSArray *)graphNodeList:(UIView *)graphView
{
    NSLog(@"lists in graphNodeList retainCount : %d",[lists retainCount]);
    return lists;//返回全部数据
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
    
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        
        gLastDisplayErrorTimeInterval = currentTime;
    }
}
//框架从服务器读取数据后放在objects中，函数通过对象objects进行适当转换后显示出来
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"Loaded objects: %@", objects); 
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        if (transactionType == AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD) 
        {
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // add favorite successfully
                [self setupTitleBarFav];
                //[[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavSucc", @"")] show];
                AliToastView *toastView = [AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavSucc", @"")];
                toastView.transform = CGAffineTransformMakeRotation(3.141592656/2);
                toastView.center = self.view.center;
                [toastView show];
            } else {
                
                if (result.resultCode == nil) {
                    //[[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                    AliToastView *toastView = [AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")];
                    toastView.transform = CGAffineTransformMakeRotation(3.141592656/2);
                    toastView.center = self.view.center;
                    [toastView show];
                    return ;
                }
                // Price
                if ([result.resultCode isEqualToString:FAVORITE_ADD_PRICE_EXISTS]) {
                    [self setupTitleBarFav];
                    //[[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavPrice", @"")] show];
                    AliToastView *toastView = [AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavPrice", @"")];
                    toastView.transform = CGAffineTransformMakeRotation(3.141592656/2);
                    toastView.center = self.view.center;
                    [toastView show];
                }else if([result.resultCode isEqualToString:FAVORITE_ADD_PRICE_OVER_MAXLIMITED]) {
                    //[[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedPrice", @"")] show];
                    AliToastView *toastView = [AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedPrice", @"")];
                    toastView.transform = CGAffineTransformMakeRotation(3.141592656/2);
                    toastView.center = self.view.center;
                    [toastView show];
                }else {
                    //[[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                    AliToastView *toastView = [AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")]; 
                    toastView.transform = CGAffineTransformMakeRotation(3.141592656/2);
                    toastView.center = self.view.center;
                    [toastView show];
                }
            }   
        }
    }else {
            
            /////////////
            /* 以下代码用于从服务器采集价格行情数据 */
        if ([objects count]==0) {
            NSLog(@"server no data!");
            self.lableInfo.text = [NSString stringWithFormat:@"获取价格信息失败！"];
            [self.mLoadingView showNodataMessage];
            return;
        }
        AMPriceGraghListResult *result = (AMPriceGraghListResult*)[objects objectAtIndex:0];
            
        if (result.success) { 
            NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
            [f setNumberStyle:NSNumberFormatterDecimalStyle];
            
            AMPriceGraghHistotyItem *priceGraghHistotyItem = [result.historyPrice objectAtIndex:0];
            
            self.sourceFromName = priceGraghHistotyItem.sourceFromName;
            self.themeId = [f numberFromString:priceGraghHistotyItem.themeId];
            self.themeName = priceGraghHistotyItem.themeName;
            self.categroyId = [f numberFromString:priceGraghHistotyItem.categoryId];
            
            NSUInteger index = 0;
            NSUInteger priceListCount = [priceGraghHistotyItem.priceList count];
            if (priceListCount > 0) {
                if (self.gNodelists == nil) {
                    gNodelists = [[NSMutableArray alloc] initWithCapacity:priceListCount];          
                }
                for (index = 0; index < priceListCount; index++) {
                    /*GraphNodeLine封装了uibutton，因此每个GraphNodeLine对象都能响应点击效果，GraphNodeLine对象还有xVlaues、yVlaues、lableInfo用于存储数据用于显示，绘制主要由GraphNodeList对象实现*/
                    GraphNodeLine *gNodeLine =[[GraphNodeLine alloc] initWithID:index name:self.themeName rect:CGRectMake(0, 0, 44, 44)];
                    AMPriceListItem *priceItem = [priceGraghHistotyItem.priceList objectAtIndex:index];
                    gNodeLine.yVlaues = [f numberFromString:priceItem.price];
                    gNodeLine.xVlaues = priceItem.date;
                    gNodeLine.dateWithYear = priceItem.dateWithYear;
                    gNodeLine.lableInfo = [NSString stringWithFormat:@"日期:%@\n价格:%d元",gNodeLine.xVlaues,gNodeLine.yVlaues.integerValue];
                    [gNodelists addObject:gNodeLine];
                    [gNodeLine release];
                }
                //实际读取的数据中“产地”一栏可能没有值
                if (self.sourceAddressName != nil) {
                    self.lableInfo.text = [NSString stringWithFormat:@"(产品名称:%@  产地/产商:%@  单位:元/吨)",self.themeName,self.sourceAddressName];
                }else {
                    self.lableInfo.text = [NSString stringWithFormat:@"(产品名称:%@  单位:元/吨)",self.themeName];
                }
                
                
                [self.mPickView.lableTitle setText:themeName];
                [self.mPickView sizeToFit];
                [self reloadAllView];//用于更新显示价格行情折线图
            }
            else {
                NSLog(@"the lists in the service are empty!!!");
                self.lableInfo.text = [NSString stringWithFormat:@"产品内容为空！"];
                [self.mLoadingView showNodataMessage];
//                    NSString *msg = [[NSString alloc]initWithFormat:@""];
//                    UIAlertView *alert = [[UIAlertView alloc] 
//                                          initWithTitle:@"产品内容为空！" 
//                                          message:msg 
//                                          delegate:self    
//                                          cancelButtonTitle:@"取消"                          
//                                          otherButtonTitles:@"确定" ,
//                                          nil]; 
//                    [alert show]; 
//                    [alert release];
//                    [msg release];

                } 
                [f release];
            }
        else {
            NSLog(@"json load false maybe the form is wrong");
            self.lableInfo.text = [NSString stringWithFormat:@"获取价格信息失败！"];
            [self.mLoadingView showNodataMessage];

                

//                NSString *msg = [[NSString alloc]initWithFormat:@""];
//                UIAlertView *alert = [[UIAlertView alloc] 
//                                      initWithTitle:@"获取价格信息失败！" 
//                                      message:msg 
//                                      delegate:self    
//                                      cancelButtonTitle:@"取消"                          
//                                      otherButtonTitles:@"确定" ,
//                                      nil]; 
//                [alert show]; 
//                [alert release];
//                [msg release];
        }
    }
        
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] == NSURLErrorConnectionToBeOffline) {
        if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
            NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
            
            if (transactionType == AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD) {
                AliToastView *toastView = [AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"收藏失败，请检查网络设置"]; 
                toastView.transform = CGAffineTransformMakeRotation(3.141592656/2);
                toastView.center = self.view.center;
                [toastView show];
            } 
            
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
            self.lableInfo.text = [NSString stringWithFormat:@"获取价格信息失败！"];
        }
        
        
      }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex 
{
    [self.navigationController popViewControllerAnimated:YES];
}
#pragma pickView
/*
 该函数用于获取pickView中选择的内容
 */
-(void)pickView:(UIView *)pickView mSelectType:(NSUInteger)selectIndex
{
    NSMutableArray *array = [[NSMutableArray alloc] initWithCapacity:0];
    NSMutableArray *arrayTmp = [[NSMutableArray alloc] initWithCapacity:0];
    int index = 0;
    int index2 = 0;
    NSUInteger listsCount = [gNodelists count];
    GraphNodeLine *gLastNode = [gNodelists lastObject];
    NSRange range = [gLastNode.xVlaues rangeOfString:@"/"];
    int location = range.location;
    //取出lists中最后一天的月份并转为数字格式，如07/12的07
    int gLastMonth = [[gLastNode.xVlaues substringToIndex:location] intValue];
    //取出lists中最后一天的号并转为数字格式，如07/12的12
    int gLastDay = [[gLastNode.xVlaues substringFromIndex:location+1] intValue];
    
    NSRange range2 = [gLastNode.dateWithYear rangeOfString:@"/"];
    int location2 = range2.location;
    //取出lists中最后一天的年份，如2012年
    int gLastYear = [[gLastNode.dateWithYear substringToIndex:location2] intValue];
    int gLastMonth2 = 0;
    int gLastDay2 = 0;
    int gLastYear2 = 0;
    
    int data;
    
    
    self.lists = nil;//将lists置空用于释放内存占用的内存
    mGraphFilter = selectIndex;
    
    switch (selectIndex) {
        case 0://返回一年的数据，每隔六个数据取一个值
            for (index = listsCount - 1; index >= 0; index = index - 6) {
                GraphNodeLine *gNodeLine = [gNodelists objectAtIndex:index];
                [arrayTmp addObject:gNodeLine];
            }
            for (index = 0, index2 =[arrayTmp count]-1; index < [arrayTmp count]; index++,index2--) {
                [array addObject:[arrayTmp objectAtIndex:index2]];
            }
            
            [arrayTmp release];
            self.lists = array;
            [array release];
            
            break;
        case 1://返回一季的数据，每隔二个数据取一个值，从最后一个开始向前取三个月   
            if (gLastMonth > 3) {
                data = gLastMonth - 3;
            }
            else {
                data = gLastMonth +12 - 3;
            }  
            for (index = listsCount - 1; index >= 0; index = index - 3) {
                GraphNodeLine *gNodeLine = [gNodelists objectAtIndex:index];
                gLastMonth2 = [[gNodeLine.xVlaues substringToIndex:location] intValue];
                gLastYear2 = [[gNodeLine.dateWithYear substringToIndex:location2] intValue];
                if (gLastMonth > 3 && gLastYear2 < gLastYear) {
                    break;
                }
                if ((gLastMonth > 3 && data >= gLastMonth2) || (gLastMonth < 3 && gLastMonth2 > 3 && data >= gLastMonth2)) {
                    gLastDay2 = [[gNodeLine.xVlaues substringFromIndex:location+1] intValue];
                    if (gLastDay >= gLastDay2) {
                        break;
                    }
                }  
                [arrayTmp addObject:gNodeLine];
            }
            for (index = 0, index2 =[arrayTmp count]-1; index < [arrayTmp count]; index++,index2--) {
                [array addObject:[arrayTmp objectAtIndex:index2]];
            }
            [arrayTmp release];
            self.lists = array;
            [array release];
            
            break;
        case 2://返回一月的数据，每个数据都取出来，从最后一个向前取一个月
            if (gLastMonth > 1) {
                data = gLastMonth - 1;
            }
            else {
                data = gLastMonth +12 - 1;
            }  
            for (index = listsCount - 1; index >= 0; index--) {
                GraphNodeLine *gNodeLine = [gNodelists objectAtIndex:index];
                gLastMonth2 = [[gNodeLine.xVlaues substringToIndex:location] intValue];
                gLastYear2 = [[gNodeLine.dateWithYear substringToIndex:location2] intValue];
                if (gLastMonth > 1 && gLastYear2 < gLastYear) {
                    break;
                }
                if ((gLastMonth > 1 && data >= gLastMonth2) || (gLastMonth < 1 && gLastMonth2 > 1 && data >= gLastMonth2)) {
                    gLastDay2 = [[gNodeLine.xVlaues substringFromIndex:location+1] intValue];
                    if (gLastDay >= gLastDay2) {
                        break;
                    }
                }  
                [arrayTmp addObject:gNodeLine];
            }
            for (index = 0, index2 =[arrayTmp count]-1; index < [arrayTmp count]; index++,index2--) {
                [array addObject:[arrayTmp objectAtIndex:index2]];
            }
            [arrayTmp release];
            self.lists = array;
            [array release];
            
            break;
        case 3://返回一周的数据，每个数据都取出来，从最后一个向前取一周
            if (gLastDay > 5) {
                data = gLastDay - 5;
            }
            else {
                data = gLastDay + 30 - 5;
            }
            for (index = listsCount - 1; index >= 0; index--) {
                GraphNodeLine *gNodeLine = [gNodelists objectAtIndex:index];
                gLastDay2 = [[gNodeLine.xVlaues substringFromIndex:location+1] intValue];
                if (listsCount - index > 5 || (gLastDay > 5 && gLastDay2 <= data) || (gLastDay <= 5 && gLastDay2 >= data)) {
                    break;
                }
                
                [arrayTmp addObject:gNodeLine];
            }
            for (index = 0, index2 =[arrayTmp count]-1; index < [arrayTmp count]; index++,index2--) {
                [array addObject:[arrayTmp objectAtIndex:index2]];
            }
            [arrayTmp release];
            self.lists = array;
            [array release];
            break;
        default:
            self.lists = self.gNodelists;
            [array release];
            [arrayTmp release];
            break;
    }
    CGFloat stepX = (FRAMEWIDTH - OFFSETX) / 5;//用于计算x方向间距
    self.graphNodeList.frame = CGRectMake(0, 0, stepX * ([lists count]), self.graphNodeList.frame.size.height);
    [scrollView setContentSize:(self.graphNodeList.frame).size];
    [self.view setNeedsLayout];
    [self.graphNodeList reloadData];
    [self.graphView reloadData];
    [self endLoadingView];
}

-(void)addSubview:(UIView *)subview
{
    [self.view addSubview:subview];
}
-(void)insertSubview:(UIView *)subview aboveSubview:(UIView *)subviewAbove
{
    [self.view insertSubview:subview aboveSubview:subviewAbove];
}
-(UIView *)superView
{
    return self.view;
}

-(void) reloadAllView
{
    [self pickView:self.mPickView mSelectType:mGraphFilter];
}


@end

//
//  AMOrderSelledTableViewController.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-9-14.
//
//
#import "AMOrderSelledTableViewController.h"
#import "AMOrderSelledRequest.h"
#import "AMOrderBuyedResult.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "AMMoney.h"
#import "HJObjManager.h"
#import "AMMoreLoadingCell.h"
#import "AMOfferTabViewController.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "NSAttributedString+HTML.h"
#import "AliToastView.h"
#import "AMOrderBuyed.h"
#import "AMOrderBuyedTableViewCell.h"
#import "AMOrderBuyedMoreImagesTableViewCell.h"
#import "AMOrderBuyedSingleImagesTableViewCell.h"
#import "LoginToken.h"
#import "AliParamButton.h"
#import "AMOrderDetailViewController.h"
#import "AMOrderLogisticsViewController.h"
#import "SVPullToRefresh.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
#define DEFAULT_PAGE_SIZE  6

@implementation AMOrderSelledTableViewController

#pragma synthesize start
@synthesize objMan=_objMan;
@synthesize parentTitle = _parentTitle;
@synthesize m2TableView, mOfferResult;
@synthesize request = _request;
@synthesize objects = _objects;
@synthesize mNavigationController = _mNavigationController;
@synthesize orderStateDict = _orderStateDict;
@synthesize totalCount = _totalCount;
@synthesize currentPage = _currentPage;
@synthesize headerView = _headerView;
@synthesize pickerButton = _pickerButton;
@synthesize isReceiveOrderStateNotify = _isReceiveOrderStateNotify;
@synthesize mLoadingView = _mLoadingView;
@synthesize tempCurrentPage = _tempCurrentPage;

- (id)initWithNavigation:(UINavigationController *)navigation {
    self = [super init];
    if (self) {
        self.mNavigationController = navigation;
    }
    return self;
}

- (void)viewWillAppear:(BOOL)animated
{

    if (!isLoading&&self.totalCount==0) {
        [self.mLoadingView showNodataMessage];
    }
    
    [super viewWillAppear:animated];
}

-(void)viewWillDisappear:(BOOL)animated {
//    [[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICATION_ORDER_STATE object:nil];
//    [[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICAGION_LOGIN_SUCC object:nil];
    [super viewWillDisappear:animated];
}


-(UIView*)headerView
{
    if (!_headerView) {
        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 20.0, 320.0, 15.0)];
        _headerView.backgroundColor = RGB(0xF2, 0xF2, 0xF2);
        
        CGSize labelSizePre = [@"近三个月订单(共" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(15, 30, labelSizePre.width, 15.0)];
        preLabel.font = [UIFont systemFontOfSize:12.0f];
        preLabel.numberOfLines = 1;
        preLabel.lineBreakMode = UILineBreakModeWordWrap;
        preLabel.backgroundColor = [UIColor clearColor];
        preLabel.textColor = RGB(0x66,0x66,0x66);
        preLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
        preLabel.text = @"近三个月订单(共";
        [_headerView addSubview:preLabel];
        
        
        
//        CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        NSString *totalCountString = [NSString stringWithFormat:@"%d",self.totalCount];
        CGSize labelSize = [totalCountString sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        UILabel *midLabel = [[UILabel alloc] initWithFrame:CGRectMake(15 +preLabel.frame.size.width, 30, labelSize.width, 15.0)];
        midLabel.font = [UIFont systemFontOfSize:12.0f];
        midLabel.numberOfLines = 1;
        midLabel.lineBreakMode = UILineBreakModeWordWrap;
        midLabel.backgroundColor = [UIColor clearColor];
        midLabel.textColor = RGB(0xff,0x73,0x00);
        midLabel.highlightedTextColor = RGB(0xff,0x73,0x00);
//        midLabel.text = countValue;
        midLabel.text = totalCountString;
        [_headerView addSubview:midLabel];
        
        
        
        CGSize labelSizeEnd = [@"个订单)" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        UILabel *endLabel = [[UILabel alloc] initWithFrame:CGRectMake(15+preLabel.frame.size.width+midLabel.frame.size.width, 30, labelSizeEnd.width, 15.0)];
        endLabel.font = [UIFont systemFontOfSize:12.0f];
        endLabel.numberOfLines = 1;
        endLabel.lineBreakMode = UILineBreakModeWordWrap;
        endLabel.backgroundColor = [UIColor clearColor];
        endLabel.textColor = RGB(0x66,0x66,0x66);
        endLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
        endLabel.text = @"个订单)";
        [_headerView addSubview:endLabel];
        
        self.pickerButton = [[UIButton alloc] init];
        [self.pickerButton setImage:[UIImage imageNamed:@"activity_icon_01.png"] forState:UIControlStateNormal];
        self.pickerButton.frame = CGRectMake(15+preLabel.frame.size.width+midLabel.frame.size.width+labelSizeEnd.width, 30, labelSizeEnd.width, 15.0);
        [self.pickerButton addTarget:self action:@selector(refreshOrderFilterTableview) forControlEvents:UIControlEventTouchUpInside];
        [_headerView addSubview:self.pickerButton];
        
        [preLabel release];
        [midLabel release];
        [endLabel release];
        
    }
    return _headerView;  
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height+20);
        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    return _mLoadingView;
}

- (void) refreshOrderFilterTableview
{
    NSLog(@"refreshOrderFilterTableview...");
}
    
-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"卖出货品";
}


-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	_objMan.fileCache = fileCache;
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

-(void)orderDictInit{
    
    self.orderStateDict = [NSDictionary dictionaryWithObjectsAndKeys:@"交易异常，处理中", @"EXCEPTION",@"交易异常，已处理完毕", @"EXCEPTION_END",
                           @"等待买家修改信息", @"WAIT_SELLER_MODIFY",@"等待买家付款", @"WAIT_BUYER_PAY",
                           @"等待卖家发货", @"WAIT_SELLER_SEND",@"交易异常，已处理完毕", @"EXCEPTION_END",
                           @"等待买家收货", @"WAIT_BUYER_RECEIVE",@"交易成功", @"SUCCESS",
                           @"交易成功，保证金已退回", @"SUCCESS_END",@"交易关闭", @"CANCEL",
                           @"等待卖家绑定支付宝", @"WAIT_SELLER_BIND_ALIPAY",@"等待卖家确认信息", @"WAIT_SELLER_CONFIRM",
                           @"交易成功， 已清算", @"LIQUIDATE_ALREADY",@"等待成团 (团批订单)", @"WAIT_GROUPING",
                           @"等待卖家确认团 (团批订单)", @"WAIT_SELLER_CONFIRM_GROUP",@"等待买家确认信息", @"WAIT_BUYER_CONFIRM",
                           @"等待卖家确认到账", @"WAIT_SELLER_CONFIRM_FUND",
                           nil];
}


-(void)loadRequest
{
//    isLoading = YES;
    if(!_request){
      self.request = [[AMOrderSelledRequest alloc] init];  
    }
    self.request.page = [NSNumber numberWithInt:self.currentPage];
    
    
    NSString *loginUserName=[LoginToken getLoginUserName];
    if (loginUserName && loginUserName.length > 0) {
        self.request.sellerMemberId = loginUserName;
      [self loadObjectsFromRemote];  
    }
    
    
}


- (void)loadObjectsFromRemote {
    
    isLoading = YES;
    
    if (self.currentPage>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.m2TableView.tableFooterView = moreloadingView;
        [moreloadingView release];
    }else {
        self.m2TableView.tableFooterView = nil;
        [self.mLoadingView showLoadingView];
    }
    
    
    
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    RKObjectMapping* mapping = [AMOrderBuyedResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_ORDER_SELLEDORDERS usingBlock:^(RKObjectLoader* loader) {
        loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMOrderBuyedResult  class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
//    [super loadObjectsFromRemote];
//    [self.mLoadingView showLoadingView];
    
}

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


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    if (self.objects==nil) {
        self.objects = [[NSMutableArray alloc]init];
        
    }

    id object = [objects objectAtIndex:0];
    if(object != nil){
        
        AMOrderBuyedResult * offer = object;
        
        NSArray * array = offer.modelList;
        self.totalCount = [offer.totalCount intValue];
//        [self.view addSubview:self.headerView];
        [self performSelectorOnMainThread:@selector(setTableDate:) withObject:array waitUntilDone:YES];
        
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
    isLoading = NO;
    if (self.currentPage* DEFAULT_PAGE_SIZE >= self.totalCount) {
        self.m2TableView.tableFooterView = nil;
    }
    
    
    if (self.totalCount<=0) {
        [self showNodataMessage];
    }else{
        [self endLoadingView];
    }

    [m2TableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
    //将物流状态选择置为所有
    
    
    
//    [super objectLoader:objectLoader didLoadObjects: objects];
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    
    [self.m2TableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
    
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==-1009){
//        if (isPullViewLoad) {
//            [self.myCustomerTableView.pullToRefreshView stopAnimating];
//        }
        
        if ([self.objects count]) {
            AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
            self.m2TableView.tableFooterView = errorMessageView;
            [errorMessageView release];
            if (!isPullViewLoad) {
                self.currentPage--;
            }else {
                self.currentPage = self.tempCurrentPage;
                
            }
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        isPullViewLoad = NO;
    }
    isLoading = NO;
    
}






//去除加载进度
-(void) endLoadingView
{
    [self.mLoadingView endLoadingView];
}
- (void) showNodataMessage
{
    [self.mLoadingView showNodataMessage];
    
//    [self.mLoadingView setHidden:NO];
//    [self.mLoadingView.loadingView setHidden:YES];
//    [self.mLoadingView.noDataView setHidden:NO];
    
}

- (void) setTableDate:(NSMutableArray *)date
{
    [self.objects addObjectsFromArray:date];
    [self.m2TableView reloadData];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        isLoading = NO;
        
        self.objects = [[NSMutableArray alloc] init];
        [[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICATION_ORDER_STATE object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loadRequestWithOrderSellState:) name:NOTIFICATION_ORDER_STATE object:nil];
        [[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICAGION_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginEvent:) name:NOTIFICAGION_LOGIN_SUCC object:nil];
        
    }
    return self;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
        NSUInteger row = [indexPath row];
        if(row == self.objects.count){
            return 300;
        }else{
            return [AMOrderBuyedTableViewCell cellHeight];
    
       }
    return [AMOrderBuyedTableViewCell cellHeight];
    
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(self.objects.count <= 0){
        return 0;
    }else{
        return self.objects.count;
    }
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    self.m2TableView.frame = CGRectMake(0, 40, 320, 421);
    tableView.separatorStyle = NO;
    NSUInteger row = [indexPath row];
    
    
    AMOrderBuyed *buyedOrders = (AMOrderBuyed*)[_objects objectAtIndex:row] ;
    NSArray *buyerArray = buyedOrders.orderEntries;
    if(buyerArray!=nil&&[buyerArray count]>1){
        //返回多个图片的订单
        AMOrderBuyedMoreImagesTableViewCell *cell = (AMOrderBuyedMoreImagesTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMOrderBuyedMoreImagesTableViewCell cellIdentifer]];
        
        if (cell == nil){
            cell = [AMOrderBuyedMoreImagesTableViewCell createCell];
        }
        
        
        cell.logoImage1.hidden = YES;
        cell.logoImage2.hidden = YES;
        cell.logoImage3.hidden = YES;
        cell.logoImage4.hidden = YES;
        
        
        NSDictionary *myDict = [buyedOrders.orderEntries objectAtIndex:0];
        {
            NSString *mainSummImageUrl = [myDict objectForKey:@"mainSummImageUrl"];
            cell.logoImage1.url = [NSURL URLWithString:mainSummImageUrl];
            [self.objMan manage:cell.logoImage1];
            cell.logoImage1.layer.masksToBounds = YES;
            cell.logoImage1.layer.cornerRadius= 10.0;
            cell.logoImage1.frame =CGRectMake(20, 145, 60 , 60);
            cell.logoImage1.hidden = NO;
        }
        
        if([buyerArray count ]>=2){
            NSDictionary *myDict = [buyedOrders.orderEntries objectAtIndex:1];
            NSString *mainSummImageUrl = [myDict objectForKey:@"mainSummImageUrl"];
            cell.logoImage2.url = [NSURL URLWithString:mainSummImageUrl];
            [self.objMan manage:cell.logoImage2];
            cell.logoImage2.layer.masksToBounds = YES;
            cell.logoImage2.layer.cornerRadius= 10.0;
            cell.logoImage2.frame =CGRectMake(90, 145, 60 , 60);
            cell.logoImage2.hidden = NO;
        }
        
        if([buyerArray count ]>=3){
            NSDictionary *myDict = [buyedOrders.orderEntries objectAtIndex:2];
            NSString *mainSummImageUrl = [myDict objectForKey:@"mainSummImageUrl"];
            
            cell.logoImage3.url = [NSURL URLWithString:mainSummImageUrl];
            [self.objMan manage:cell.logoImage3];
            cell.logoImage3.layer.masksToBounds = YES;
            cell.logoImage3.layer.cornerRadius= 10.0;
            cell.logoImage3.frame =CGRectMake(160, 145, 60 , 60);
            cell.logoImage3.hidden = NO;
        }
        
        if([buyerArray count ]>=4){
            NSDictionary *myDict = [buyedOrders.orderEntries objectAtIndex:3];
            NSString *mainSummImageUrl = [myDict objectForKey:@"mainSummImageUrl"];
            cell.logoImage4.url = [NSURL URLWithString:mainSummImageUrl];
            [self.objMan manage:cell.logoImage4];
            cell.logoImage4.layer.masksToBounds = YES;
            cell.logoImage4.layer.cornerRadius= 10.0;
            cell.logoImage4.frame =CGRectMake(230, 145, 60 , 60);
            cell.logoImage4.hidden = NO;
        }
        AMOrderBuyed *buyedOrders = (AMOrderBuyed*)[_objects objectAtIndex:row] ;
        //        cell.buyerCompanyNameLabel.text = buyedOrders.buyerCompanyName;
        if(!buyedOrders.buyerCompanyName)
        {
            cell.buyerCompanyNameLabel.text = [NSString stringWithFormat:@"无"];   
        }else{
            cell.buyerCompanyNameLabel.text = [NSString stringWithFormat:@"%@",buyedOrders.buyerCompanyName];
        }
        cell.buyorsale.text = [NSString stringWithFormat:@"买家"];
        
        //        NSDictionary *myDict = [buyedOrders.orderEntries objectAtIndex:0];
        
        NSNumber  *quantity =[myDict objectForKey:@"quantity"];
        cell.quantityLabel.text = [NSString stringWithFormat:@"共%@条",quantity];
        
        cell.orderIdLabel.text = [NSString stringWithFormat:@"%@",buyedOrders.identifier];
        
        //订单上部共几种产品
        cell.orderProductCount.text = [NSString stringWithFormat:@"%d",[buyedOrders.orderEntries count]];
        
        //下单时间
        NSDate *nd = [NSDate  dateWithTimeIntervalSince1970: [buyedOrders.gmtModified doubleValue]/1000 ];//时间需要除以1000
        NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
        [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm"];
        cell.gmtModifiedLabel.text = [dateFormat stringFromDate:nd];
        [dateFormat release]; 
        
        //订单上部的实付款
        cell.sumPaymentLabel.text = [NSString stringWithFormat:@"¥ %2g 元",[buyedOrders.sumPayment doubleValue]/100];
        
        //订单状态
        NSString * orderStatus = buyedOrders.status;
        cell.entryStatusLabel.text = [self convertOrderStatus:orderStatus];
        
        //判断查看物流按钮是否出现，目前只有买家等待收货和交易成功两种状态有物流
        BOOL isHaveLogistics = [AMOrderSelledTableViewController isHasLogisticsInfo:orderStatus];
        if(isHaveLogistics){
            cell.logisticsButton.hidden = NO;
            cell.logisticsButton.frame = CGRectMake(20, 220, 135, 30);
//            cell.logisticsButton.layer.cornerRadius = 5.0;
//            cell.logisticsButton.layer.masksToBounds = YES;
            cell.orderButton.frame = CGRectMake(165, 220, 135, 30);
//            cell.orderButton.layer.cornerRadius = 5.0;
//            cell.orderButton.layer.masksToBounds = YES;
        }else{
            cell.logisticsButton.hidden = YES;
            //cell.orderButton.frame = CGRectMake(20, 220, 280, 30);
            cell.orderButton.frame = CGRectMake(165, 220, 135, 30);
//            cell.orderButton.layer.cornerRadius = 5.0;
//            cell.orderButton.layer.masksToBounds = YES;
        }
        
        cell.orderButton.param = buyedOrders;
        cell.logisticsButton.param = buyedOrders;
        [cell.orderButton addTarget:self action:@selector(orderDetailAction:) forControlEvents:UIControlEventTouchUpInside];
        [cell.logisticsButton addTarget:self action:@selector(orderLogisticsAction:) forControlEvents:UIControlEventTouchUpInside];
        
        tableView.backgroundColor = [UIColor clearColor];
         UIImage *img=[UIImage imageNamed:@"or_message_bg"];
        UIImageView *imgView=[[UIImageView alloc]initWithImage:img];
        [imgView setFrame:CGRectMake(10, 10, 300, 260)];
        cell.backgroundView = imgView;
        [imgView release];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        return cell;
    }else{
        //返回单个图片的订单
        AMOrderBuyedSingleImagesTableViewCell *cell = (AMOrderBuyedSingleImagesTableViewCell *)[tableView dequeueReusableCellWithIdentifier: [AMOrderBuyedSingleImagesTableViewCell cellIdentifer]];
        
        if (cell == nil){
            cell = [AMOrderBuyedSingleImagesTableViewCell createCell];
        }
        AMOrderBuyed *buyedOrders = (AMOrderBuyed*)[_objects objectAtIndex:row] ;
//        cell.buyerCompanyNameLabel.text = buyedOrders.buyerCompanyName;
//        cell.buyerCompanyNameLabel.text = buyedOrders.sellerName;
        if(!buyedOrders.buyerCompanyName)
        {
         cell.buyerCompanyNameLabel.text = [NSString stringWithFormat:@"无"];   
        }else{
            cell.buyerCompanyNameLabel.text = [NSString stringWithFormat:@"%@",buyedOrders.buyerCompanyName];
        }
        cell.buyorsale.text = [NSString stringWithFormat:@"买家"];
        
        
        NSDictionary *myDict = [buyedOrders.orderEntries objectAtIndex:0];
        NSString *productName = [myDict objectForKey:@"productName"];
        //       NSLog(@"productName=%@",productName);
        cell.productNameLabel.text = productName;
        
        cell.orderIdLabel.text = [NSString stringWithFormat:@"%@",buyedOrders.identifier];
        
        //订单上部共几种产品
        cell.orderProductCount.text = [NSString stringWithFormat:@"%d",[buyedOrders.orderEntries count]];
        
        //下单时间
        NSDate *nd = [NSDate  dateWithTimeIntervalSince1970: [buyedOrders.gmtModified doubleValue]/1000 ];//时间需要除以1000
        NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
        [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm"];
        cell.gmtModifiedLabel.text = [dateFormat stringFromDate:nd];
        [dateFormat release]; 
        
        //订单上部的实付款
        cell.sumPaymentLabel.text = [NSString stringWithFormat:@"¥ %2g 元",[buyedOrders.sumPayment doubleValue]/100];
        
        //订单状态
        NSString * orderStatus = buyedOrders.status;
        cell.entryStatusLabel.text = [self convertOrderStatus:orderStatus];
        
        //下部分订单中的数量--（共多少条，多少件）
        NSNumber  *quantity =[myDict objectForKey:@"quantity"];
        NSString *unit =  [myDict objectForKey:@"unit"];
        cell.quantityLabel.text = [NSString stringWithFormat:@"(共%@%@)",quantity,unit];
        
        
        //订单下部实付款  discountprice*quantiry+disountLong -entryCouponAmountLong
        
        //获得价格
        NSNumber *entryDiscountPrice = [myDict objectForKey:@"discountPrice"];
        //获得折扣价
        NSNumber *entryDiscount = [myDict objectForKey:@"entryDiscount"];
        //获得抵用券
        NSNumber *entryCouponAmount = [myDict objectForKey:@"entryCouponAmount"];
        if(entryCouponAmount<0){
            entryCouponAmount = 0;
        }
        
        //实付款
        int actPrice = [entryDiscountPrice intValue]*[quantity intValue] + [entryDiscount intValue] - [entryCouponAmount intValue];
        NSNumber * actPriceNumber = [NSNumber numberWithInt:actPrice];
        cell.amountLabel.text = [NSString stringWithFormat:@"实付款：%2g元",[actPriceNumber doubleValue]/100];
        
        //判断查看物流按钮是否出现，目前只有买家等待收货和交易成功两种状态有物流
        BOOL isHaveLogistics = [AMOrderSelledTableViewController isHasLogisticsInfo:orderStatus];
        if(isHaveLogistics){
            cell.logisticsButton.hidden = NO;
            cell.logisticsButton.frame = CGRectMake(20, 220, 135, 30);
//            cell.logisticsButton.layer.cornerRadius = 5.0;
//            cell.logisticsButton.layer.masksToBounds = YES;
            cell.orderButton.frame = CGRectMake(165, 220, 135, 30);
//            cell.orderButton.layer.cornerRadius = 5.0;
//            cell.orderButton.layer.masksToBounds = YES;
        }else{
            cell.logisticsButton.hidden = YES;
//            cell.orderButton.frame = CGRectMake(20, 220, 280, 30);
            cell.orderButton.frame = CGRectMake(165, 220, 135, 30);
//            cell.orderButton.layer.cornerRadius = 5.0;
//            cell.orderButton.layer.masksToBounds = YES;
        }
        
        cell.orderButton.param = buyedOrders;
        cell.logisticsButton.param = buyedOrders;
        [cell.orderButton addTarget:self action:@selector(orderDetailAction:) forControlEvents:UIControlEventTouchUpInside];
        [cell.logisticsButton addTarget:self action:@selector(orderLogisticsAction:) forControlEvents:UIControlEventTouchUpInside];
        
        [cell.logoImage1 setImage:nil];
        cell.bkImage.layer.masksToBounds = YES;
        cell.bkImage.layer.cornerRadius= 2.0;
        [cell.logoImage1 setImage:nil];
        cell.logoImage1.url = [NSURL URLWithString:[myDict objectForKey:@"mainSummImageUrl"]];
        [self.objMan manage:cell.logoImage1];
        cell.logoImage1.layer.cornerRadius= 10.0;
        cell.logoImage1.layer.masksToBounds = YES;

        
        tableView.backgroundColor = [UIColor clearColor];
        UIImage *img=[UIImage imageNamed:@"or_message_bg"];
        UIImageView *imgView=[[UIImageView alloc]initWithImage:img];
        [imgView setFrame:CGRectMake(10, 10, 300, 260)];
        cell.backgroundView = imgView;
        [imgView release];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        return cell;
        
    } 
    
        
}

- (IBAction)orderDetailAction:(id)sender {

    AMOrderBuyed * orderModel = ((AliParamButton *)sender).param;
    if (orderModel == nil) {
        return ;
    }
    NSString *memberId=[LoginToken getLoginUserName];
    AMOrderDetailViewController *viewController = [[[AMOrderDetailViewController alloc] init] autorelease];
    viewController.orderId = [NSString stringWithFormat:@"%@",orderModel.identifier];
    viewController.memberId = memberId;
    [self.mNavigationController pushViewController:viewController animated:YES]; 

}

- (IBAction)orderLogisticsAction:(id)sender {
    
    AMOrderBuyed * orderModel = ((AliParamButton *)sender).param;
    if (orderModel == nil) {
        return ;
    }
    AMOrderLogisticsViewController *viewController = [[[AMOrderLogisticsViewController alloc] init] autorelease];
    viewController.orderId = [NSString stringWithFormat:@"%@",orderModel.identifier];
    viewController.parentTitle = @"卖出货品";
    [self.mNavigationController pushViewController:viewController animated:YES]; 
    
}

+ (BOOL) isHasLogisticsInfo:(NSString *)orderStates
{
    if ([orderStates isEqualToString:@"WAIT_BUYER_RECEIVE"]||[orderStates isEqualToString:@"SUCCESS"]) {
        return YES;
    } else {
        return NO;
    }
}



- (NSString *) convertOrderStatus:(NSString *)orderEnglish
{
    NSString *orderStateString = [_orderStateDict objectForKey:orderEnglish];
    if(!orderStateString){
        return @"状态未知";
    }else{
        return orderStateString;
    }
}


- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    if(maximumOffset>0&&currentOffset>=0){
        if ((maximumOffset - currentOffset <= 30.0)) {
            
            if (self.objects.count < self.totalCount)
            {
                if (!isLoading) {
                    self.currentPage++;
                    [self loadRequest];   
                    
                }
            }  
        }   
    }
}



#pragma mark - View lifecycle

- (void) dealloc
{
    [[NSNotificationCenter  defaultCenter] removeObserver:self ];
    //[[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICATION_ORDER_STATE object:nil];
    //[[NSNotificationCenter  defaultCenter] removeObserver:self  name:NOTIFICAGION_LOGIN_SUCC object:nil];
    
    [m2TableView release];
    [mOfferResult release];
    [_request release];
    [_objects release];
    [_objMan release];
    [_mNavigationController release];
    [_orderStateDict release];
    [_headerView release];
    [_pickerButton release];
    [_mLoadingView release];
    
    [super dealloc];
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self objManInit];
     self.currentPage = 1;
    [self loadRequest];
    [self orderDictInit];
    
    [self.m2TableView addPullToRefreshWithActionHandler:^{
        NSLog(@"refresh dataSource");
        m2TableView.pullToRefreshView.lastUpdatedDate = [NSDate date];
        
        self.m2TableView.tableFooterView = nil;
        self.tempCurrentPage = self.currentPage;
        self.currentPage = 1;
        
        [self.objects removeAllObjects];
        self.objects = nil;
        self.request.orderStatusSet = @"";//下拉请求全部状态的结果
        [self loadRequest];
        isPullViewLoad = YES;
        //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
        if(self.mLoadingView.loadingView.hidden==NO){
            self.mLoadingView.loadingView.hidden = YES;
        }
//        isFirstStateObjectLoad = YES;
        
    }];
    
}


-(void) clearData{
    if([self.objects count]>0){
      [self.objects removeAllObjects];
        self.objects = nil;
        [m2TableView reloadData];
        
    }
//    [self.m2TableView reloadData];
    self.currentPage = 1;
    self.totalCount = 0;
}

-(void)loadRequestWithOrderSellState:(id)sender{
    if(self.isReceiveOrderStateNotify){
        [self clearData];
        NSString *requestKey = [sender object];
        self.request.orderStatusSet = requestKey;
        [self loadRequest];
    }
    
}

-(void)loginEvent:(id)sender{
    [self clearData];
    [self loadRequest];
    //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
    if(self.mLoadingView.loadingView.hidden==YES){
        self.mLoadingView.loadingView.hidden = NO;
    }
    
}

@end


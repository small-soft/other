//
//  AMOrderDetailViewController.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

 

#import "AMOrderDetailViewController.h"
#import "AMProductDetailView.h"
#import "UIHelp.h"
#import "LoginToken.h"
#import "AMOrderDetailRequest.h"
#import "AMOrderDetailResult.h"
#import "AMOrderBillView.h"
#import "AMBuyerSellerInfoView.h"
#import "AMOrderEntryModel.h"
#import "HJMOFileCache.h"
#import "AMOrderProtocolView.h"


#import "ImageMagazineDetailViewController.h"


#define CONTENT_WIDTH 300


@interface AMOrderDetailViewController ()

@end

@implementation AMOrderDetailViewController

@synthesize request =_request;
@synthesize result = _result;

@synthesize showAllProducts=_showAllProducts;
@synthesize isSoldOrderInfo=_isSoldOrderInfo;

@synthesize mContentView;

@synthesize memberId=_memberId;
@synthesize orderId=_orderId;

@synthesize objMan;

@synthesize isTalkAfterWwLogin;

@synthesize countOfKinds;

@synthesize basicInfoSubiew;
@synthesize productsDetailSubview;
@synthesize buyerSellerInfoSubview;
@synthesize receiverInfoSubview;
@synthesize logisticsInfoSubview;

@synthesize buyerFeedbackSubview;
@synthesize protocalSubview;

@synthesize invoiceInfoSubview;

@synthesize basicAndProducts;

@synthesize showOrHide;
@synthesize showOrHideBig;



-(void) dealloc
{
    [_result release];
    [_request release];
    [mContentView release];
    [_memberId release];
    [_orderId release];
    [objMan release];
    
    [basicInfoSubiew release];
    [productsDetailSubview release];
    [buyerSellerInfoSubview release];
    [receiverInfoSubview release];
    [logisticsInfoSubview release];
    
    [buyerFeedbackSubview release];
    [protocalSubview release];
    
    [invoiceInfoSubview release];
    [basicAndProducts release];
    [showOrHide release];
    
    [super dealloc];
}

- (void)viewDidUnload
{
    self.request = nil;
    self.result = nil;
    self.mContentView = nil;
    self.memberId = nil;
    self.orderId = nil;
    self.objMan = nil;
    self.basicInfoSubiew = nil;
    self.productsDetailSubview = nil;
    self.buyerSellerInfoSubview = nil;
    self.receiverInfoSubview = nil;
    self.logisticsInfoSubview = nil;
    self.buyerFeedbackSubview = nil;
    self.protocalSubview = nil;
    
    self.invoiceInfoSubview = nil;
    self.basicAndProducts = nil;
    self.showOrHide = nil;
    
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


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
    [self setTitle:@"订单详情"];

    NSLog(@"订单详情进入");
    
    //当收到消息跳转至公司详情
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(goToCompanyDetail) name:NOTIFICATION_ORDER_TO_COMPANYDETAIL object:nil];
    //当收到旺旺登陆成功地消息切换到聊天页面
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    self.isTalkAfterWwLogin = NO;

    
    self.showAllProducts = NO;
    
    [self objManInit];
    [self loadOrderDetailRequest];
    
}

-(void)objManInit
{
    objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}




- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


#pragma mark - request and restkit delegate methods


-(void) loadOrderDetailRequest{
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    
    //登陆状态下才能发出订单详情请求
    if ([loginUserName length] > 3) {
        self.request = [[[AMOrderDetailRequest alloc] init] autorelease];
        self.request.orderid = self.orderId;
        
        [self loadObjectsFromRemote];

    }
}

- (void)loadObjectsFromRemote {
    
    [self.mLoadingView showLoadingView];
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* mapping = [AMOrderDetailResult sharedObjectMapping];
    
    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_ORDER_DETAIL usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMOrderDetailResult  class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
    
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {  
    
    NSLog(@"hello");
    
    id object = [objects objectAtIndex:0];
    if(object != nil){
        AMOrderDetailResult * obj = object;
        self.result = obj;
        

       

        NSLog(@"数据mapping成功");
        [self draw ];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    [self.mLoadingView endLoadingView];
    
    NSLog(@"loading errorcode %d", [error code]);
    
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }

}



#pragma mark - draw methods

-(void)draw
{
    [self.mLoadingView endLoadingView];
    
    //订单行（产品）数，影响详情显示
    self.countOfKinds = [self.result.orderModel.orderEntries count];
    
    
    for (UIView * view in self.mContentView.subviews)
    {
        [view removeFromSuperview];
    }
    
    int tempY = 10;
    
    //基本信息和产品详情最后是放在一个大的圆角View里面
    //1.开始绘制基本信息
    [self drawBasicInfo];
    self.basicInfoSubiew.frame = CGRectMake(0, tempY, self.basicInfoSubiew.frame.size.width, self.basicInfoSubiew.frame.size.height);
    
    //2.产品详情
    [self drawProducts];
    

    
    CGFloat y = self.basicInfoSubiew.frame.size.height ;
    self.productsDetailSubview.frame = CGRectMake(0, y, self.productsDetailSubview.frame.size.width, self.productsDetailSubview.frame.size.height);
    
    CGFloat heightOfBasicAndProducts = self.basicInfoSubiew.frame.size.height + self.productsDetailSubview.frame.size.height;
    
    
    
    
    //伸缩按钮
    if (countOfKinds != 1) {
        self.showOrHide = [[[UIButton alloc]init] autorelease] ;
//        [self.showOrHide setBackgroundImage:[UIImage imageNamed:@"bg_topbar.png"] forState:UIControlStateNormal];
        
//        [self.showOrHide addTarget:self action:@selector(switchShowAndHide) forControlEvents:UIControlEventTouchUpInside];
        
//        self.showOrHide.frame= CGRectMake(0, heightOfBasicAndProducts, CONTENT_WIDTH, 12   );
        
        self.showOrHide.frame= CGRectMake(0, 30, CONTENT_WIDTH, 12   );
        self.showOrHide.backgroundColor = [UIHelp colorWithHexString:@"0xd6d6d6"];
        UIImageView * imageView = [[UIImageView alloc]init ];
        imageView.frame = CGRectMake(145, 3, 10, 6);
        imageView.image = [UIImage imageNamed:@"icon_app_drown"];
        [self.showOrHide addSubview:imageView];
        [imageView release];
        
        self.showOrHideBig = [[[UIButton alloc]init] autorelease] ;
        self.showOrHideBig.frame= CGRectMake(0, heightOfBasicAndProducts - 30, CONTENT_WIDTH, 12 + 30   );
        [self.showOrHideBig addTarget:self action:@selector(switchShowAndHide) forControlEvents:UIControlEventTouchUpInside];
        [self.showOrHideBig addSubview: self.showOrHide];
        
    }
    
    self.basicAndProducts = [[[UIView alloc ] init] autorelease] ;
    [self.basicAndProducts setBackgroundColor: [UIColor clearColor]];
    self.basicAndProducts.frame = CGRectMake((320 - CONTENT_WIDTH)/2, tempY, CONTENT_WIDTH, heightOfBasicAndProducts );
    
    if (countOfKinds != 1) {
        self.basicAndProducts.frame = CGRectMake((320 - CONTENT_WIDTH)/2, tempY, CONTENT_WIDTH, heightOfBasicAndProducts + self.showOrHide.frame.size.height );//这30是按钮的高度
    }
    
    [self.basicAndProducts setBackgroundColor:[self getContentViewBackgroundColor]];
    [self.basicAndProducts.layer setCornerRadius:10.0];
    [self.basicAndProducts.layer setBorderColor: [[self getBorderColor] CGColor]];
    [self.basicAndProducts.layer setBorderWidth:1.0];
    self.basicAndProducts.clipsToBounds = YES ;
    
    [self.basicAndProducts addSubview:self.basicInfoSubiew];
    [self.basicAndProducts addSubview:self.productsDetailSubview];
    if (countOfKinds != 1) {
        [self.basicAndProducts addSubview:self.showOrHideBig];
    }
    
    [self.mContentView addSubview:self.basicAndProducts];
    
    
    tempY += self.basicAndProducts.frame.size.height + 10;
    
    
    
    //3.买家/卖家信息
    [self drawBuyerSellerInfo];
    self.buyerSellerInfoSubview.frame = CGRectMake(0, tempY, 320, self.buyerSellerInfoSubview.frame.size.height);
    [self.mContentView addSubview:self.buyerSellerInfoSubview];
    
    tempY += self.buyerSellerInfoSubview.frame.size.height ;
    tempY += 10;
    
        
    //4.收货地址
    [self drawReceiverInfo];
    self.receiverInfoSubview.frame = CGRectMake((320 - CONTENT_WIDTH)/2, tempY, CONTENT_WIDTH, self.receiverInfoSubview.frame.size.height);
    [self.mContentView addSubview:self.receiverInfoSubview];
    
    tempY += self.receiverInfoSubview.frame.size.height  ;
    tempY += 10;

        
    //5.物流查询
    if ([self.result.orderModel.status isEqualToString:@"WAIT_BUYER_RECEIVE"] || [self.result.orderModel.status isEqualToString:@"SUCCESS"]) {
        
        [self drawLogistics];
        self.logisticsInfoSubview.frame = CGRectMake(0, tempY, self.logisticsInfoSubview.frame.size.width, self.logisticsInfoSubview.frame.size.height);
        [self.mContentView addSubview:self.logisticsInfoSubview];
        
        tempY += self.logisticsInfoSubview.frame.size.height + 10 ;
    }
    
   
    //6.买家留言
    [self drawBuyerFeedback];
    self.buyerFeedbackSubview.frame = CGRectMake((320 - CONTENT_WIDTH)/2, tempY, CONTENT_WIDTH, self.buyerFeedbackSubview.frame.size.height);
    [self.mContentView addSubview:self.buyerFeedbackSubview];
    
    tempY += self.buyerFeedbackSubview.frame.size.height ;
    tempY += 10 ;
    
    //7.保障协议
    if (self.result.orderModel.orderProtocalModel != nil) {
        [self drawProtocolInfo];
        self.protocalSubview.frame = CGRectMake(0, tempY, 320, self.protocalSubview.frame.size.height);
        [self.mContentView addSubview:self.protocalSubview];
        
        tempY += self.protocalSubview.frame.size.height;
        tempY += 10 ;
    }
    
    
        
    //8.发票地址
    if (self.result.orderModel.orderInvoiceModel != nil) {
        [self drawInvoiceInfo];
        self.invoiceInfoSubview.frame = CGRectMake(0, tempY, self.invoiceInfoSubview.frame.size.width, self.invoiceInfoSubview.frame.size.height);
        [self.mContentView addSubview:self.invoiceInfoSubview];
        
        tempY += self.invoiceInfoSubview.frame.size.height ;
        tempY += 10 ;
    }
    
    
    self.mContentView.contentSize = CGSizeMake(320, tempY);    
    
    
    
}

-(void)drawBasicInfo
{
    if (self.basicInfoSubiew == nil) {
        self.basicInfoSubiew = [[[UIView alloc]init ] autorelease]  ;
        [self.basicInfoSubiew setBackgroundColor: [UIColor clearColor]];
        
    }
    self.basicInfoSubiew.frame = CGRectMake(0, 0, CONTENT_WIDTH, 0);
    int tempY = 0;
    
    UILabel * label1 = [[UILabel alloc] init];
    label1.text = @"订单状态：";
    label1.backgroundColor = [UIColor clearColor];
    label1.frame = CGRectMake(10, tempY, 100, 20);
    label1.font = [UIFont  systemFontOfSize:14.0f];
    label1.textColor = [UIHelp colorWithHexString:@"0x666666"];
    [self.basicInfoSubiew addSubview:label1];
    
    UILabel * contentLabel1 = [[UILabel alloc] init];
    contentLabel1.text =  [self getOrderStatus: self.result.orderModel.status];
//    contentLabel1.text = @"等待卖家确认团 (团批订单)";
 
    contentLabel1.backgroundColor = [UIColor clearColor];
    contentLabel1.frame = CGRectMake(80, tempY, 200, 20);
    contentLabel1.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel1.textColor = [UIHelp colorWithHexString:@"0xff7300"];
    [self.basicInfoSubiew addSubview:contentLabel1];
    
    
    tempY += label1.frame.size.height + 10;
    [self.basicInfoSubiew addSubview:label1];
    [label1 release];
    [contentLabel1 release];
    

    
    UILabel * label2 = [[UILabel alloc] init];
    label2.text = @"订单号：";
    label2.backgroundColor = [UIColor clearColor];
    label2.frame = CGRectMake(10, tempY, 100, 20);
    label2.font = [UIFont  systemFontOfSize:14.0f];
    label2.textColor = [UIHelp colorWithHexString:@"0x666666"];
    [self.basicInfoSubiew addSubview:label2];
    
    UILabel * contentLabel2 = [[UILabel alloc] init];
    contentLabel2.text = self.orderId;
    contentLabel2.backgroundColor = [UIColor clearColor];
    contentLabel2.frame = CGRectMake(80, tempY, 200, 20);
    contentLabel2.font = [UIFont  systemFontOfSize:14.0f];
//    contentLabel2.textColor = [UIHelp colorWithHexString:@"0xff7300"];
    [self.basicInfoSubiew addSubview:contentLabel2];
    
    CGSize size2 = [contentLabel2.text sizeWithFont:contentLabel2.font constrainedToSize:CGSizeMake(MAXFLOAT, contentLabel2.frame.size.height)];
    
    UILabel * contentLabel2x1 = [[UILabel alloc] init];
    contentLabel2x1.text = @"(共";
    contentLabel2x1.backgroundColor = [UIColor clearColor];
    contentLabel2x1.frame = CGRectMake(80 + size2.width + 10, tempY, 200, 20);
    contentLabel2x1.font = [UIFont  systemFontOfSize:14.0f];
    [self.basicInfoSubiew addSubview:contentLabel2x1];
    
    CGSize size3 = [contentLabel2x1.text sizeWithFont:contentLabel2x1.font constrainedToSize:CGSizeMake(MAXFLOAT, contentLabel2x1.frame.size.height)];
    
    UILabel * contentLabel2x2 = [[UILabel alloc] init];
    contentLabel2x2.text = [NSString stringWithFormat:@"%d", countOfKinds];
    contentLabel2x2.backgroundColor = [UIColor clearColor];
    contentLabel2x2.frame = CGRectMake(80 + size2.width + size3.width + 10, tempY, 200, 20);
    contentLabel2x2.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel2x2.textColor = [UIHelp colorWithHexString:@"0xff7300"];
    [self.basicInfoSubiew addSubview:contentLabel2x2];
    
    CGSize size4 = [contentLabel2x2.text sizeWithFont:contentLabel2x2.font constrainedToSize:CGSizeMake(MAXFLOAT, contentLabel2x2.frame.size.height)];
    
    UILabel * contentLabel2x3 = [[UILabel alloc] init];
    contentLabel2x3.text = [NSString stringWithFormat:@"件商品)", countOfKinds];
    contentLabel2x3.backgroundColor = [UIColor clearColor];
    contentLabel2x3.frame = CGRectMake(80 + size2.width + size3.width + size4.width + 10 , tempY, 200, 20);
    contentLabel2x3.font = [UIFont  systemFontOfSize:14.0f];
    [self.basicInfoSubiew addSubview:contentLabel2x3];
    
    tempY += label2.frame.size.height + 10;
    [label2 release];
    [contentLabel2 release];
    [contentLabel2x1 release];
    [contentLabel2x2 release];
    [contentLabel2x3 release];
    
    
    UILabel * label3 = [[UILabel alloc] init];
    label3.text = @"下单时间：";
    label3.backgroundColor = [UIColor clearColor];
    label3.frame = CGRectMake(10, tempY, 100, 20);
    label3.font = [UIFont  systemFontOfSize:14.0f];
    label3.textColor = [UIHelp colorWithHexString:@"0x666666"];
    [self.basicInfoSubiew addSubview:label3];
    
    UILabel * contentLabel3 = [[UILabel alloc] init];
    NSDate *nd = [NSDate  dateWithTimeIntervalSince1970: [self.result.orderModel.gmtCreate doubleValue]/1000 ];//时间需要除以1000
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSString *dateString = [dateFormat stringFromDate:nd];
    [dateFormat release];
    contentLabel3.text = dateString;
    contentLabel3.backgroundColor = [UIColor clearColor];
    contentLabel3.frame = CGRectMake(80, tempY, 200, 20);
    contentLabel3.font = [UIFont  systemFontOfSize:14.0f];
    [self.basicInfoSubiew addSubview:contentLabel3];
    
    tempY += label3.frame.size.height + 10;
    [label3 release];
    [contentLabel3 release];
    
    UILabel * label4 = [[UILabel alloc] init];
    label4.text = @"实付款：";
    label4.backgroundColor = [UIColor clearColor];
    label4.frame = CGRectMake(10, tempY, 100, 20);
    label4.font = [UIFont  systemFontOfSize:14.0f];
    label4.textColor = [UIHelp colorWithHexString:@"0x666666"];
    [self.basicInfoSubiew addSubview:label4];
    
    UILabel * contentLabel4 = [[UILabel alloc] init];
    contentLabel4.text =  [NSString stringWithFormat:@"￥%.2f", self.result.orderModel.sumPayment.intValue / 100.00  ];
    contentLabel4.backgroundColor = [UIColor clearColor];
    contentLabel4.frame = CGRectMake(80, tempY, 200, 20);
    contentLabel4.font = [UIFont  boldSystemFontOfSize:14.0f];
    contentLabel4.textColor = [UIHelp colorWithHexString:@"0xcc0000"];
    [self.basicInfoSubiew addSubview:contentLabel4];
    
    CGSize size1 = [contentLabel4.text sizeWithFont:contentLabel4.font constrainedToSize:CGSizeMake(MAXFLOAT, contentLabel4.frame.size.height)];
    
    UILabel * contentLabel4x = [[UILabel alloc] init];
    contentLabel4x.text =  [NSString stringWithFormat:@"(含运费%.2f元)", self.result.orderModel.carriage.intValue /  100.00 ];
    contentLabel4x.backgroundColor = [UIColor clearColor];
    contentLabel4x.frame = CGRectMake(80 + size1.width + 10, tempY, 200, 20);
    contentLabel4x.font = [UIFont  systemFontOfSize:14.0f];
    [self.basicInfoSubiew addSubview:contentLabel4x];

    
    tempY += label4.frame.size.height + 10;
    [self.basicInfoSubiew addSubview:label4];
    [label4 release];
    [contentLabel4 release];
    [contentLabel4x release];
    
    
    //分割线
    UIImageView * sep = [[UIImageView alloc]init];
    sep.frame = CGRectMake(0, tempY,CONTENT_WIDTH, 2);
    sep.image = [UIImage imageNamed:@"line_bg"];
    [self.basicInfoSubiew addSubview:sep];
    [sep release];
    
    tempY += 12;
    
   
    self.basicInfoSubiew.frame = CGRectMake(0, 0, self.basicInfoSubiew.frame.size.width, tempY);
}


-(void)drawProducts
{
    if (self.productsDetailSubview == nil) {
        self.productsDetailSubview = [[[UIView alloc] init ] autorelease] ;
        [self.productsDetailSubview setBackgroundColor: [UIColor clearColor]];
        
    }
    
    for (UIView * view in self.productsDetailSubview.subviews)
    {
        [view removeFromSuperview];
    }

    self.productsDetailSubview.frame = CGRectMake(0, 0, CONTENT_WIDTH, 0);
    int tempY = 0; 
    
    //如果只有一个产品，直接显示详情
    if ( self.countOfKinds == 1 )
    {
        NSLog(@"%@",[self.result.orderModel.orderEntries description]);
        AMOrderEntryModel* entry = (AMOrderEntryModel*)[self.result.orderModel.orderEntries objectAtIndex:0];
        NSLog(@"productName : %@",entry.productName);
        AMProductDetailView * product = [[AMProductDetailView alloc ] initWithEntry:entry];
        product.frame = CGRectMake(product.frame.origin.x , tempY, product.frame.size.width,  product.frame.size.height);
        
        
        [self.objMan manage:product.icon];
        [self.productsDetailSubview addSubview:product];
        
        tempY += product.frame.size.height ;
        [product release];
        
        
        
    }
    //如果有多个产品，要显示各产品图片，并实现伸缩式展示
    else {
        int tempX = 10, counter = 0;
        tempY = 10;
        
        for(AMOrderEntryModel * entry in self.result.orderModel.orderEntries )
        {
            //保证最多只显示四个产品
            if (counter >= 4) {
                UILabel * label = [[UILabel alloc]initWithFrame:CGRectMake(tempX, tempY + 20, 20, 20)];
                label.text = @"···";
                [self.productsDetailSubview addSubview:label];
                [label release];
                break;
            }
            
            
            UIImageView *  nodata = [[[UIImageView alloc ]init ] autorelease];
            nodata.frame = CGRectMake(tempX, tempY, 60, 60);
            nodata.layer.masksToBounds = YES;
            nodata.layer.cornerRadius = 10.0;
//            nodata.backgroundColor = [UIColor clearColor]; 
            nodata.backgroundColor = [UIColor grayColor];
            nodata.image = [UIImage imageNamed:@"nodata_pic.png"];
            
            [self.productsDetailSubview addSubview:nodata];
            
            if (entry.mainSummImageUrl!=nil && ![entry.mainSummImageUrl isEqualToString:@""])
            {
                nodata.hidden = YES;
                
                HJManagedImageV * icon = [[[HJManagedImageV alloc ]init ] autorelease];
                icon.image = nil;
                icon.url = [NSURL URLWithString:entry.mainSummImageUrl];
                icon.frame = CGRectMake(tempX, tempY, 60, 60);
                icon.layer.masksToBounds = YES;
                icon.layer.cornerRadius = 10.0;
                //            icon.backgroundColor = [UIColor clearColor]; 
                icon.backgroundColor = [UIColor grayColor]; 
                
                [self.productsDetailSubview addSubview:icon];
                
                [self.objMan manage:icon];
                
            }
                        
            tempX += 65;
            
            counter ++;
        }
        
               
        tempY += 70;
        
        UIImageView * sep = [[UIImageView alloc]init];
        sep.frame = CGRectMake(0, tempY,300, 2);
        sep.image = [UIImage imageNamed:@"line_bg"];
        [self.productsDetailSubview addSubview:sep];
        [sep release];
        
        tempY += 2;
        
        for(AMOrderEntryModel * entry in self.result.orderModel.orderEntries )
        {
            
            NSLog(@"productName : %@",entry.productName);
            AMProductDetailView * product = [[AMProductDetailView alloc ] initWithEntry:entry];
            product.frame = CGRectMake(product.frame.origin.x , tempY, product.frame.size.width,  product.frame.size.height);
            
            
            [self.objMan manage:product.icon];
            [self.productsDetailSubview addSubview:product];
            
           
            NSLog(@"product height:%f",product.frame.size.height);
            tempY += product.frame.size.height ;
            
            UIImageView * sep = [[UIImageView alloc]init];
            sep.frame = CGRectMake(0, tempY,300, 2);
            sep.image = [UIImage imageNamed:@"line_bg"];
            [self.productsDetailSubview addSubview:sep];
            [sep release];
            
            tempY += 2;
            
            [product release];
            
        }

        
        if (!self.showAllProducts)
        {
            tempY -=  2;   
            tempY -= countOfKinds * 82 ;                        
        }
        
        self.productsDetailSubview.clipsToBounds = YES;
        

        
    }
    
    self.productsDetailSubview.frame = CGRectMake(0, 0, self.productsDetailSubview.frame.size.width, tempY);
    
    

}


-(void)drawBuyerSellerInfo
{
    if (self.buyerSellerInfoSubview == nil) {
        self.buyerSellerInfoSubview = [[[UIView alloc]init ] autorelease] ;
        [self.buyerSellerInfoSubview setBackgroundColor: [UIColor clearColor]];

    }
    
    self.buyerSellerInfoSubview.frame = CGRectMake(0, 0, 320, 0);
    int tempY = 0; 

    
    
    UILabel * infoTitle = [[UILabel alloc ] init];
    if (![self.memberId isEqualToString:self.result.orderModel.buyerMemberId])
    {
        infoTitle.text = @"买家信息";
        self.isSoldOrderInfo = NO;
    }else {
        infoTitle.text = @"卖家信息";
        self.isSoldOrderInfo = YES;
    }
    
    infoTitle.backgroundColor = [UIColor clearColor];
    infoTitle.frame = CGRectMake(10, 0, 150, 20);
    
    [self.buyerSellerInfoSubview addSubview:infoTitle];
    
    tempY += infoTitle.frame.size.height ;
    tempY += 5;
    [infoTitle release];

    
    NSLog(@"buyerMemberId:%@, sellerMemberId:%@,buyerAlipayLoginId:%@,sellerAlipayLoginId:%@",self.result.orderModel.buyerMemberId,self.result.orderModel.sellerMemberId,self.result.orderModel.buyerAlipayLoginId, self.result.orderModel.sellerAlipayLoginId);
    
    
    AMBuyerSellerInfoView * infoView = [[AMBuyerSellerInfoView alloc ] init ];
    infoView.memberContactDelegate = self;
   
    
    [infoView setNavigationController:self.navigationController];
    
    [infoView setData:self.result withMemberId:self.memberId ];
    [infoView reloadData];
    
    
    
    infoView.frame = CGRectMake(0, tempY, infoView.frame.size.width, infoView.frame.size.height);
    
    [self.buyerSellerInfoSubview addSubview:infoView];
    
    tempY += infoView.frame.size.height ;
//    tempY += 10;
    [infoView release];
    
    
    self.buyerSellerInfoSubview.frame = CGRectMake(0, 0, self.buyerSellerInfoSubview.frame.size.width, tempY);

}


-(void)drawReceiverInfo
{
    if (self.receiverInfoSubview == nil) {
        self.receiverInfoSubview = [[[UIView alloc]init ] autorelease];
        [self.receiverInfoSubview setBackgroundColor: [UIColor clearColor]];

    }
    
    self.receiverInfoSubview.frame = CGRectMake(0, 0, 320, 0);
    int tempY = 0; 
        
    UILabel * receiverTitle = [[UILabel alloc ] init];
    receiverTitle.text = @"收货地址";
    receiverTitle.backgroundColor = [UIColor clearColor];
    receiverTitle.frame = CGRectMake(0, 0, 100, 20);
    
    
    [self.receiverInfoSubview addSubview:receiverTitle];
    
    tempY += receiverTitle.frame.size.height;
    tempY += 5;
    [receiverTitle release];

    
    UILabel * receiverAddr = [[UILabel alloc] init];
    NSString * addr = @"";
    if (self.result.orderModel.buyerName != nil && ![self.result.orderModel.buyerName isEqualToString:@""]) {
        addr=[addr stringByAppendingString:self.result.orderModel.buyerName];
    }
    if (self.result.orderModel.buyerMobile != nil && ![self.result.orderModel.buyerMobile isEqualToString:@""]) {
        addr=[addr stringByAppendingFormat:@",%@",self.result.orderModel.buyerMobile];
    }
    if (self.result.orderModel.buyerPhone != nil && ![self.result.orderModel.buyerPhone isEqualToString:@""]) {
        addr=[addr stringByAppendingFormat:@",%@",self.result.orderModel.buyerPhone];
    }
    if (self.result.orderModel.toArea != nil && ![self.result.orderModel.toArea isEqualToString:@""]) {
        addr=[addr stringByAppendingFormat:@",%@",self.result.orderModel.toArea];
    }
    receiverAddr.text = addr;
    receiverAddr.numberOfLines = 0;
    receiverAddr.lineBreakMode = UILineBreakModeCharacterWrap;
    receiverAddr.backgroundColor = [UIColor clearColor];
    receiverAddr.frame = CGRectMake(10, 11, 280, 100);
    receiverAddr.font = [UIFont  systemFontOfSize:14.0f];
    CGSize size1 = [receiverAddr.text sizeWithFont:receiverAddr.font constrainedToSize:CGSizeMake(280,MAXFLOAT)];
    
    if (size1.height < 21) {
        receiverAddr.frame = CGRectMake(10, 11, 280, 21);
        
    }else {
        receiverAddr.frame = CGRectMake(10, 11, 280, size1.height);
        
    }
        
    
    UIView * receiverInfo = [[UIView alloc] init ];
    receiverInfo.frame = CGRectMake(0, tempY, CONTENT_WIDTH, receiverAddr.frame.size.height + 22);
    [receiverInfo addSubview:receiverAddr];
    [receiverInfo.layer setBorderColor:[[self getBorderColor] CGColor]];
    [receiverInfo.layer setBorderWidth:1.0];
    [receiverInfo.layer setCornerRadius:10.0];
    [receiverInfo setBackgroundColor: [self getContentViewBackgroundColor]];
    
    
    [self.receiverInfoSubview addSubview:receiverInfo];
    [receiverAddr release];
    [receiverInfo release];
    
    
    tempY += receiverInfo.frame.size.height ;
    
    
    self.receiverInfoSubview.frame = CGRectMake(0, 0, self.receiverInfoSubview.frame.size.width, tempY);

    
}


-(void)drawLogistics
{
    if (self.logisticsInfoSubview == nil) {
        self.logisticsInfoSubview = [[[UIView alloc]init ] autorelease] ;
        [self.logisticsInfoSubview setBackgroundColor: [UIColor clearColor]];

    }
    
    self.logisticsInfoSubview.frame = CGRectMake(0, 0, 300, 0);
    int tempY = 0; 
    
    if ([self.result.orderModel.status isEqualToString:@"WAIT_BUYER_RECEIVE"] || [self.result.orderModel.status isEqualToString:@"SUCCESS"]) {
        
        CGRect frame = CGRectMake(10, tempY, 300, 40);
        UIButton * button = [[[UIButton alloc]init] autorelease];
        button.frame = frame;
        
        [button.titleLabel  setFont:[UIFont boldSystemFontOfSize:16.0f]];
        [button setTitle:@"查看物流信息" forState:UIControlStateNormal];
        [button setTitleColor:([UIColor blackColor]) forState:UIControlStateNormal];
        [button setTitleColor:([UIColor whiteColor]) forState:UIControlStateHighlighted];
        
        UIImage * bgImgNormal = [UIImage imageNamed:@"btn_ct_nor.png"];
        bgImgNormal = [bgImgNormal stretchableImageWithLeftCapWidth:bgImgNormal.size.width/8 topCapHeight:0];
        [button setBackgroundImage:bgImgNormal forState:UIControlStateNormal];
        UIImage * bgImgPressed = [UIImage imageNamed:@"btn_ct_p.png"];
        bgImgPressed = [bgImgPressed stretchableImageWithLeftCapWidth:bgImgPressed.size.width/8 topCapHeight:0];
        [button setBackgroundImage:bgImgPressed forState:UIControlStateHighlighted];
        
        button.backgroundColor = [UIColor clearColor];
        
        [button addTarget:self action:@selector(logisticsClicked) forControlEvents:(UIControlEventTouchUpInside)];
        
        [self.logisticsInfoSubview addSubview:button];
        
        tempY += frame.size.height ;
//        tempY += 20;
        
        
    }
    
    self.logisticsInfoSubview.frame = CGRectMake(0, 0, self.logisticsInfoSubview.frame.size.width, tempY);

}

-(void)drawBuyerFeedback
{
    if (self.buyerFeedbackSubview == nil) {
        self.buyerFeedbackSubview = [[[UIView alloc]init ] autorelease] ;
        [self.buyerFeedbackSubview setBackgroundColor: [UIColor clearColor]];
        

        
    }
    
    self.buyerFeedbackSubview.frame = CGRectMake(0, 0, 320, 0);
    int tempY = 0; 
    
    UILabel * feedbackTitle = [[UILabel alloc ] init];
    feedbackTitle.text = @"买家留言";
    feedbackTitle.backgroundColor = [UIColor clearColor];
    feedbackTitle.frame = CGRectMake(0, 0, 100, 20);
    
    
    [self.buyerFeedbackSubview addSubview:feedbackTitle];
    
    tempY += feedbackTitle.frame.size.height + 5;
    [feedbackTitle release];
    
    
    UILabel * feedback = [[UILabel alloc] init];
    NSString * content = @"无";
    if (self.result.orderModel.buyerFeedback != nil && ![self.result.orderModel.buyerFeedback isEqualToString:@""]) {
        content=self.result.orderModel.buyerFeedback;
    }

    feedback.text = content;
    feedback.numberOfLines = 0;
    feedback.lineBreakMode = UILineBreakModeCharacterWrap;
    feedback.backgroundColor = [UIColor clearColor];
    feedback.frame = CGRectMake(10, 11, 280, 100);
    feedback.font = [UIFont  systemFontOfSize:14.0f];
    CGSize size1 = [feedback.text sizeWithFont:feedback.font constrainedToSize:CGSizeMake(280,MAXFLOAT)];
    
    if (size1.height < 21) {
        feedback.frame = CGRectMake(10, 11, 280, 21);
    }else {
        feedback.frame = CGRectMake(10, 11, 280, size1.height);
        
    }
    
    
    UIView * feedbackInfo = [[UIView alloc] init ];
    feedbackInfo.frame = CGRectMake(0, tempY, CONTENT_WIDTH, feedback.frame.size.height + 22);
    [feedbackInfo addSubview:feedback];
    [feedbackInfo.layer setBorderColor:[[self getBorderColor] CGColor]];
    [feedbackInfo.layer setBorderWidth:1.0];
    [feedbackInfo.layer setCornerRadius:10.0];
    [feedbackInfo setBackgroundColor: [self getContentViewBackgroundColor]];
    
    
    [self.buyerFeedbackSubview addSubview:feedbackInfo];
    [feedback release];
    [feedbackInfo release];
    
    
    tempY += feedbackInfo.frame.size.height ;
    
    
    self.buyerFeedbackSubview.frame = CGRectMake(0, 0, self.buyerFeedbackSubview.frame.size.width, tempY); 
}


-(void)drawProtocolInfo
{
    if (self.protocalSubview == nil) {
        self.protocalSubview = [[[UIView alloc]init ] autorelease];
        [self.protocalSubview setBackgroundColor: [UIColor clearColor]];
        

    }
    
    self.protocalSubview.frame = CGRectMake(0, 0, 320, 0);
    int tempY = 0; 
    
    
    
    UILabel * infoTitle = [[UILabel alloc ] init];
    infoTitle.text = @"保障协议";    
    infoTitle.backgroundColor = [UIColor clearColor];
    infoTitle.frame = CGRectMake(10, 0, 150, 20);
    
    [self.protocalSubview addSubview:infoTitle];
    
    tempY += infoTitle.frame.size.height + 5;
    [infoTitle release];
    
    
    AMOrderProtocolView * infoView = [[AMOrderProtocolView alloc ] init ];
    
        
    
    [infoView setNavigationController:self.navigationController];
    
    [infoView setData:self.result withMemberId:self.memberId ];
    [infoView reloadData];
    
    
    
    infoView.frame = CGRectMake(0, tempY, infoView.frame.size.width, infoView.frame.size.height);
    
    [self.protocalSubview addSubview:infoView];
    
    tempY += infoView.frame.size.height ;
    [infoView release];
    
    
    self.protocalSubview.frame = CGRectMake(0, 0, self.protocalSubview.frame.size.width, tempY);
}


-(void)drawInvoiceInfo
{
    if (self.invoiceInfoSubview == nil) {
        self.invoiceInfoSubview = [[[UIView alloc]init ] autorelease];
        [self.invoiceInfoSubview setBackgroundColor: [UIColor clearColor]];
        
    }
    
    self.invoiceInfoSubview.frame = CGRectMake(0, 0, 320, 0);
    int tempY = 0; 
    
    
    
    UILabel * infoTitle = [[UILabel alloc ] init];
    infoTitle.text = @"发票信息";    
    infoTitle.backgroundColor = [UIColor clearColor];
    infoTitle.frame = CGRectMake(10, 0, 150, 20);
    
    [self.invoiceInfoSubview addSubview:infoTitle];
    
    tempY += infoTitle.frame.size.height + 5;
    [infoTitle release];
    
    
    AMOrderBillView * infoView = [[AMOrderBillView alloc ] init ];
    
    
    
    [infoView setNavigationController:self.navigationController];
    
    [infoView setData:self.result withMemberId:self.memberId ];
    [infoView reloadData];
    
    
    
    infoView.frame = CGRectMake(0, tempY, infoView.frame.size.width, infoView.frame.size.height);
    
    [self.invoiceInfoSubview addSubview:infoView];
    
    tempY += infoView.frame.size.height + 10;
    [infoView release];
    
    
    self.invoiceInfoSubview.frame = CGRectMake(0, 0, self.invoiceInfoSubview.frame.size.width, tempY);

}


//产品详情伸缩重绘
-(void) switchShowAndHide
{
    int diff = countOfKinds * 82 ;
    
    if (!self.showAllProducts) {
        
        [UIView beginAnimations:@"showall" context:nil];
        [UIView setAnimationDuration:0.3];
        
        
        //1
        self.productsDetailSubview.frame = CGRectMake(self.productsDetailSubview.frame.origin.x ,self.productsDetailSubview.frame.origin.y,self.productsDetailSubview.frame.size.width,self.productsDetailSubview.frame.size.height + diff);
        //2
        self.basicAndProducts.frame = CGRectMake(self.basicAndProducts.frame.origin.x ,self.basicAndProducts.frame.origin.y,self.basicAndProducts.frame.size.width,self.basicAndProducts.frame.size.height + diff);
        //3
//        self.showOrHide.frame = CGRectMake(self.showOrHide.frame.origin.x,self.showOrHide.frame.origin.y + diff ,self.showOrHide.frame.size.width,self.showOrHide.frame.size.height);
        self.showOrHideBig.frame = CGRectMake(self.showOrHideBig.frame.origin.x,self.showOrHideBig.frame.origin.y + diff ,self.showOrHideBig.frame.size.width,self.showOrHideBig.frame.size.height);
        
        //4
        self.buyerSellerInfoSubview.frame = CGRectMake(self.buyerSellerInfoSubview.frame.origin.x,self.buyerSellerInfoSubview.frame.origin.y + diff,self.buyerSellerInfoSubview.frame.size.width,self.buyerSellerInfoSubview.frame.size.height);
        //5
        self.receiverInfoSubview.frame = CGRectMake(self.receiverInfoSubview.frame.origin.x,self.receiverInfoSubview.frame.origin.y + diff,self.receiverInfoSubview.frame.size.width,self.receiverInfoSubview.frame.size.height);
        //6
        self.logisticsInfoSubview.frame = CGRectMake(self.logisticsInfoSubview.frame.origin.x,self.logisticsInfoSubview.frame.origin.y + diff,self.logisticsInfoSubview.frame.size.width,self.logisticsInfoSubview.frame.size.height);
        
        //7
        self.buyerFeedbackSubview.frame = CGRectMake(self.buyerFeedbackSubview.frame.origin.x,self.buyerFeedbackSubview.frame.origin.y + diff,self.buyerFeedbackSubview.frame.size.width,self.buyerFeedbackSubview.frame.size.height);
        //8
        self.protocalSubview.frame = CGRectMake(self.protocalSubview.frame.origin.x,self.protocalSubview.frame.origin.y + diff,self.protocalSubview.frame.size.width,self.protocalSubview.frame.size.height);
        
        //9
        self.invoiceInfoSubview.frame = CGRectMake(self.invoiceInfoSubview.frame.origin.x,self.invoiceInfoSubview.frame.origin.y + diff,self.invoiceInfoSubview.frame.size.width,self.invoiceInfoSubview.frame.size.height);
        
        //10
        self.mContentView.contentSize = CGSizeMake(320, self.mContentView.contentSize.height + diff);    
        
        
        [UIView commitAnimations];
        
        for (UIView * view in [self.showOrHide subviews]) {
            [view removeFromSuperview];
        }
        UIImageView * imageView = [[UIImageView alloc]init ];
        imageView.frame = CGRectMake(145, 3, 10, 6);
        imageView.image = [UIImage imageNamed:@"icon_app_up"];
        [self.showOrHide addSubview:imageView];
        [imageView release];
        
        self.showAllProducts = YES;
    }else {
        [UIView beginAnimations:@"hide" context:nil];
        [UIView setAnimationDuration:0.3];
        //1
        self.productsDetailSubview.frame = CGRectMake(self.productsDetailSubview.frame.origin.x ,self.productsDetailSubview.frame.origin.y,self.productsDetailSubview.frame.size.width,self.productsDetailSubview.frame.size.height - diff);
        //2
        self.basicAndProducts.frame = CGRectMake(self.basicAndProducts.frame.origin.x ,self.basicAndProducts.frame.origin.y,self.basicAndProducts.frame.size.width,self.basicAndProducts.frame.size.height - diff);
        //3
//        self.showOrHide.frame = CGRectMake(self.showOrHide.frame.origin.x,self.showOrHide.frame.origin.y - diff ,self.showOrHide.frame.size.width,self.showOrHide.frame.size.height);
        self.showOrHideBig.frame = CGRectMake(self.showOrHideBig.frame.origin.x,self.showOrHideBig.frame.origin.y - diff ,self.showOrHideBig.frame.size.width,self.showOrHideBig.frame.size.height);

        //4
        self.buyerSellerInfoSubview.frame = CGRectMake(self.buyerSellerInfoSubview.frame.origin.x,self.buyerSellerInfoSubview.frame.origin.y - diff,self.buyerSellerInfoSubview.frame.size.width,self.buyerSellerInfoSubview.frame.size.height);
        //5
        self.receiverInfoSubview.frame = CGRectMake(self.receiverInfoSubview.frame.origin.x,self.receiverInfoSubview.frame.origin.y - diff,self.receiverInfoSubview.frame.size.width,self.receiverInfoSubview.frame.size.height);
        //6
        self.logisticsInfoSubview.frame = CGRectMake(self.logisticsInfoSubview.frame.origin.x,self.logisticsInfoSubview.frame.origin.y - diff,self.logisticsInfoSubview.frame.size.width,self.logisticsInfoSubview.frame.size.height);
        
        //7
        self.buyerFeedbackSubview.frame = CGRectMake(self.buyerFeedbackSubview.frame.origin.x,self.buyerFeedbackSubview.frame.origin.y - diff,self.buyerFeedbackSubview.frame.size.width,self.buyerFeedbackSubview.frame.size.height);
        //8
        self.protocalSubview.frame = CGRectMake(self.protocalSubview.frame.origin.x,self.protocalSubview.frame.origin.y - diff,self.protocalSubview.frame.size.width,self.protocalSubview.frame.size.height);
        //9
        self.invoiceInfoSubview.frame = CGRectMake(self.invoiceInfoSubview.frame.origin.x,self.invoiceInfoSubview.frame.origin.y - diff,self.invoiceInfoSubview.frame.size.width,self.invoiceInfoSubview.frame.size.height);
        
        //10
        self.mContentView.contentSize = CGSizeMake(320, self.mContentView.contentSize.height - diff);    
        
        [self.mContentView setContentOffset:CGPointMake(0, 0) animated:YES];
        
        
        [UIView commitAnimations];
        
        for (UIView * view in [self.showOrHide subviews]) {
            [view removeFromSuperview];
        }
        UIImageView * imageView = [[UIImageView alloc]init ];
        imageView.frame = CGRectMake(145, 3, 10, 6);
        imageView.image = [UIImage imageNamed:@"icon_app_drown"];
        [self.showOrHide addSubview:imageView];
        [imageView release];
        
        self.showAllProducts = NO;
    }
//    [self draw];
}

#pragma mark - util methods

-(NSString*) getOrderStatus:(NSString*) status
{
    NSString * result = [[NSString alloc]init];
    if ([status isEqualToString:@"EXCEPTION"]) {
        result = @"交易异常，处理中";
    }
    if ([status isEqualToString:@"EXCEPTION_END"]) {
        result = @"交易异常，已处理完毕";
    }
    if ([status isEqualToString:@"WAIT_SELLER_MODIFY"]) {
        result = @"等待买家修改信息";
    }
    if ([status isEqualToString:@"WAIT_BUYER_PAY"]) {
        result = @"等待买家付款";
    }
    if ([status isEqualToString:@"WAIT_SELLER_SEND"]) {
        result = @"等待卖家发货";
    }
    if ([status isEqualToString:@"WAIT_BUYER_RECEIVE"]) {
        result = @"等待买家收货";
    }
    if ([status isEqualToString:@"SUCCESS"]) {
        result = @"交易成功";
    }
    if ([status isEqualToString:@"SUCCESS_END"]) {
        result = @"交易成功，保证金已退回";
    }
    if ([status isEqualToString:@"CANCEL"]) {
        result = @"交易关闭";
    }
    if ([status isEqualToString:@"WAIT_SELLER_BIND_ALIPAY"]) {
        result = @"等待卖家绑定支付宝";
    }
    if ([status isEqualToString:@"WAIT_SELLER_CONFIRM"]) {
        result = @"等待卖家确认信息";
    }
    if ([status isEqualToString:@"LIQUIDATE_ALREADY"]) {
        result = @"交易成功， 已清算";
    }
    if ([status isEqualToString:@"WAIT_GROUPING"]) {
        result = @"等待成团 (团批订单)";
    }
    if ([status isEqualToString:@"WAIT_SELLER_CONFIRM_GROUP"]) {
        result = @"等待卖家确认团 (团批订单)";
    }
    if ([status isEqualToString:@"WAIT_BUYER_CONFIRM"]) {
        result = @"等待买家确认信息";
    }
    if ([status isEqualToString:@"WAIT_SELLER_CONFIRM_FUND"]) {
        result = @"等待卖家确认到账";
    }
    
    return [result autorelease];
}


-(UIColor*) getBorderColor
{
    return [UIHelp colorWithHexString:@"0xc9c9c9"];
}

-(UIColor*) getContentViewBackgroundColor
{
    return [UIColor whiteColor];
}




#pragma mark - go to other view controllers

//跳转到公司详情页
-(void)goToCompanyDetail
{
    AMCompanyTabViewController * offerViewController = [[AMCompanyTabViewController alloc] initWithMemberId:(self.isSoldOrderInfo)?self.result.orderModel.sellerMemberId:self.result.orderModel.buyerMemberId companyName:(self.isSoldOrderInfo)?self.result.orderModel.sellerCompanyName:self.result.orderModel.buyerCompanyName preViewName:nil];
    [self.navigationController pushViewController:offerViewController animated:YES];
    [offerViewController release];
}

//当可以查看物流时，物流列表页
-(void)logisticsClicked
{
    AMOrderLogisticsViewController *viewController = [[[AMOrderLogisticsViewController alloc] init] autorelease];
    viewController.orderId = [NSString stringWithFormat:@"%@",self.result.orderModel.Id];
    viewController.parentTitle = @"订单详情";
    [self.navigationController pushViewController:viewController animated:YES]; 
}

#pragma mark - WW login

- (void) onWwLoginSucc {
    if (isTalkAfterWwLogin) {
        [self enterTalk];
        isTalkAfterWwLogin = NO;
    }
}

- (void) enterTalk {
    NSString * memberId = @"";
    NSString * name = @"";
    
    if (self.isSoldOrderInfo) {
        memberId = self.result.orderModel.sellerMemberId;
        name= self.result.orderModel.sellerMemberId;
    }else {
        memberId = self.result.orderModel.buyerMemberId;
        name= self.result.orderModel.buyerMemberId;

    }
    
    if (memberId && name) {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:memberId : name];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.navigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

-(void)wangWangDidSelected {
    if([LoginToken isWangWangLogined]) {
        [self enterTalk];
    } else {
        isTalkAfterWwLogin = YES;
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
    }
}






@end

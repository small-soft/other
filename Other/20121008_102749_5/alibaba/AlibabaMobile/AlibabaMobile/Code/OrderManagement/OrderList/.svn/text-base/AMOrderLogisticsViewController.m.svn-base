//
//  AMOrderLogisticsViewController.m
//  AlibabaMobile
//
//  Created by amon on 12-9-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderLogisticsViewController.h"
#import "HJObjManager.h"
#import "ConstDef.h"
#import "AMOrderDetailRequest.h"
#import "AMOrderDetailResult.h"
#import "AMHotRankResult.h"
#import "AliTableViewCellCategory.h"
#import "AMOrderLogisticsViewController.h"
#import "LoginToken.h"
#import "UIHelp.h"
#import "AMOrderLogCell.h"
#import "AMLogiticsQueryResultViewController.h"
#import "AliToastView.h"

@interface AMOrderLogisticsViewController ()
@property (nonatomic,retain) HJObjManager *objMan;

@property (retain, nonatomic)UIActivityIndicatorView *loadingIndicator;
@property (nonatomic,retain) AMOrderDetailRequest *dataRequest;
@property (nonatomic,retain) NSMutableArray *contentData;

- (void)loadObjectsFromRemote ;
@end

@implementation AMOrderLogisticsViewController
@synthesize objMan = _objMan;
@synthesize loadingIndicator = _loadingIndicator;
@synthesize dataRequest = _dataRequest;
@synthesize contentTable = _contentTable;
@synthesize parentTitle = _parentTitle;
@synthesize contentData = _contentData;
@synthesize orderId = _orderId;
@synthesize result = _result;
@synthesize headerView = _headerView;
@synthesize totalCount = _totalCount;
//@synthesize mTableView = _mTableView;

-(void)dealloc{
    [_objMan release];
    [_loadingIndicator release];
    [_dataRequest release];
    [_contentTable release];
    [_parentTitle release];
    [_contentData release];
    [_orderId release];
    [_result release];
    [_headerView release];
//    [_mTableView release];
    [super dealloc];
}

-(UIView*)headerView
{
    if (!_headerView) {
        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 40.0)];
//        _headerView.backgroundColor = RGB(0xff, 0xfd, 0xe9);
        
        NSString * preString = [NSString stringWithFormat:@"订单%@共包含",self.orderId]; 
        CGSize labelSizePre = [preString sizeWithFont:[UIFont systemFontOfSize:14.0f]];
        UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 0, labelSizePre.width, 40.0)];
        preLabel.font = [UIFont systemFontOfSize:14.0f];
        preLabel.numberOfLines = 1;
        preLabel.lineBreakMode = UILineBreakModeWordWrap;
        preLabel.backgroundColor = [UIColor clearColor];
        preLabel.textColor = RGB(0x33,0x33,0x33);
        preLabel.highlightedTextColor = RGB(0x33,0x33,0x33);
        preLabel.text = preString;
        [_headerView addSubview:preLabel];
        
        
        
        //        CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        NSString *totalCountString = [NSString stringWithFormat:@"%d",self.totalCount];
        CGSize labelSize = [totalCountString sizeWithFont:[UIFont systemFontOfSize:14.0f]];
        UILabel *midLabel = [[UILabel alloc] initWithFrame:CGRectMake(10 +preLabel.frame.size.width, 0, labelSize.width, 40.0)];
        midLabel.font = [UIFont systemFontOfSize:14.0f];
        midLabel.numberOfLines = 1;
        midLabel.lineBreakMode = UILineBreakModeWordWrap;
        midLabel.backgroundColor = [UIColor clearColor];
        midLabel.textColor = RGB(0xff,0x73,0x00);
        midLabel.highlightedTextColor = RGB(0xff,0x73,0x00);
        //        midLabel.text = countValue;
        midLabel.text = totalCountString;
        [_headerView addSubview:midLabel];
        
        
        
        CGSize labelSizeEnd = [@"个运单" sizeWithFont:[UIFont systemFontOfSize:14.0f]];
        UILabel *endLabel = [[UILabel alloc] initWithFrame:CGRectMake(10+preLabel.frame.size.width+midLabel.frame.size.width, 0, labelSizeEnd.width, 40.0)];
        endLabel.font = [UIFont systemFontOfSize:14.0f];
        endLabel.numberOfLines = 1;
        endLabel.lineBreakMode = UILineBreakModeWordWrap;
        endLabel.backgroundColor = [UIColor clearColor];
        endLabel.textColor = RGB(0x33,0x33,0x33);
        endLabel.highlightedTextColor = RGB(0x33,0x33,0x33);
        endLabel.text = @"个运单)";
        [_headerView addSubview:endLabel];

        [preLabel release];
        [midLabel release];
        [endLabel release];
        
    }
    return _headerView;  
}


-(AMOrderDetailRequest*)dataRequest
{
    if (!_dataRequest) {
        _dataRequest = [[AMOrderDetailRequest alloc]init];
    }
           
    return _dataRequest;

}

-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc]init];
    }
    return _contentData;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)viewWillAppear:(BOOL)animated {
    
    [super viewWillAppear:animated];
    
    if ([[self contentData ] count] <= 0) {
        NSString *loginUserName=nil;
        loginUserName=[LoginToken getLoginUserName];
        if ([loginUserName length] > 3) {
            self.dataRequest.orderid = self.orderId;
            [self loadObjectsFromRemote];
        } 
    }
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"订单物流";
}

- (void)viewDidLoad
{

//    self.contentTable.separatorColor = [UIColor clearColor];
//    self.contentTable.separatorColor = [UIColor grayColor];
    
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [_dataRequest release];
    _dataRequest = nil;
    [_contentData release];
    _contentData = nil;
    self.contentTable = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
        
        NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
        HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
        _objMan.fileCache = fileCache;
        // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
        fileCache.fileCountLimit = 100;
        fileCache.fileAgeLimit = 60*60*24*7; //1 week
        [fileCache trimCacheUsingBackgroundThread];
        
    }
    return _objMan;
    
}


- (void)loadObjectsFromRemote {
    
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
        loader.params = self.dataRequest;
    }];
    
//    [super loadObjectsFromRemote];
}


- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {  
    
    id object = [objects objectAtIndex:0];
    if(object != nil){
        
        AMOrderDetailResult * obj = object;
        
//        _result.orderModel.logisticsOrderList;
        self.result = obj;
        NSArray *orderLogisticsArray = _result.orderModel.logisticsOrderList;
        self.totalCount = [orderLogisticsArray count];
        [self.contentData removeAllObjects];
        [self.contentData addObjectsFromArray:orderLogisticsArray];
        [self.contentTable reloadData];
        [self.view addSubview:self.headerView];
        [super objectLoader:objectLoader didLoadObjects:objects];

    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
    
    
}


#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AMOrderLogCell cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    return [self.contentData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    AMOrderLogCell *cell = (AMOrderLogCell *)[tableView dequeueReusableCellWithIdentifier: [AMOrderLogCell cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AMOrderLogCell createCell];        
    }
    
    
    cell.backgroundColor = [UIColor clearColor];
    cell.backgroundColor = [UIColor whiteColor];
    
    NSUInteger row = [indexPath row];
    
    AMOrderLogisticsModel *content = (AMOrderLogisticsModel*)[self.contentData objectAtIndex:row];
    AMOrderLogisticsCompanyModel *logisticsCompanyModel = content.logisticsCompany;
    cell.logisticsName.text =[NSString stringWithFormat:@"%@",logisticsCompanyModel.companyName];
    cell.logisticsNo.text = content.logisticsBillNo;
    cell.toContact = [NSString stringWithFormat:@"%@",content.toContact];
    return cell;
}

#pragma mark -
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {

    //是否让跳转，信息不全限制跳转
    
    
    NSUInteger row = [indexPath row];
    AMOrderLogisticsModel *logisticsModel = (AMOrderLogisticsModel*)[self.contentData objectAtIndex:row];
    AMOrderLogisticsCompanyModel *logisticsCompanyModel = logisticsModel.logisticsCompany;

    AMLogiticsQueryResultViewController *result = [[[AMLogiticsQueryResultViewController alloc] initWithNibName:@"AMLogiticsQueryResultViewController" bundle:nil] autorelease];
//    NSUInteger index = row*4;
    AMCorporation* company = [[AMCorporation alloc]init];
    
    //物流测试数据
//    company.name = @"远成物流";
//    company.code = @"YCGWL";
//    result.company = company;
//    result.number = @"111121";  
//    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"物流测试数据跳转"] show];

    //真实跳转
    
    company.name = logisticsCompanyModel.companyName;
    company.code = logisticsCompanyModel.companyNo;
    result.company = company;
    result.number = logisticsModel.logisticsBillNo;
    
    result.parentTitle = @"订单物流";
    
    if(company.name==nil||company.code==nil||result.number==nil){
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"物流信息不全，无法查询"] show];
        [self.contentTable deselectRowAtIndexPath:indexPath animated:YES]; 
    }else{
        result.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:result animated:YES];
        [company release];
        [self.contentTable deselectRowAtIndexPath:indexPath animated:YES];  
    }
    
}

@end


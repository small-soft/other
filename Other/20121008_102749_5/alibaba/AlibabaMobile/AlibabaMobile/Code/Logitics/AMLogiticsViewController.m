//
//  AMLogiticsViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import "AMLogiticsViewController.h"
#import "AMLogiticsQueryResultViewController.h"
#import "AMCompanySelectViewController.h"
#import "AMLogiticsData.h"
#import "AMExpressName.h"
#import "AMExpressNumber.h"
#import "AMExpressHistory.h"
#import "AMExpressHistoryTitle.h"
#import "AliToastView.h"
#import "AliTitleCellView.h"
#import "ConstDef.h"
#import "AMMyLogisticsOrderRequest.h"
#import "AMMylogisticsOrderResult.h"
#import "AMMyLogiticsOrderCell.h"
//#import "AMMoreLoadingCell.h"
#import "AMMylogisticsOrder.h"
#import "LoginToken.h"
#import "AMIMViewController.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"
#define DEFAULT_EXPRESS_NAME @"请选择物流公司"

@interface AMLogiticsViewController()
@property (readonly,nonatomic)AMLogiticsData *logiticsData;
@property (readonly, nonatomic) AMExpressName *expressNameCell;
@property (readonly, nonatomic) AMExpressNumber *expressNumberCell;
@property (readwrite,nonatomic) BOOL queryButtonState;
@property (nonatomic, readonly) NSArray* segmentTitle;
@property (readwrite,nonatomic)int selectedTabItem;
@property (readonly,nonatomic) AMMyLogisticsOrderRequest*queryRequest;
@property (nonatomic, retain) NSMutableArray* resultList;
@property (readwrite) int orderListTotal;
@property (readwrite) BOOL isLoading;
@property (readwrite) int currentPage;
@property (retain,nonatomic)NSString *loginUserName;
-(IBAction)expressNumberDidAndExit:(UIButton*)sender;
@end
@implementation AMLogiticsViewController


@synthesize contentTable=_contentTable;
@synthesize historyTable = _historyTable;
@synthesize queryButton = _queryButton;
@synthesize expressQueryView = _expressQueryView;
@synthesize myOrderView = _myOrderView;
@synthesize myOrderTabel = _myOrderTabel;
@synthesize loginButton = _loginButton;
@synthesize noLoginView = _noLoginView;
@synthesize errorMessage = _errorMessage;
@synthesize logiticsData=_logiticsData;
@synthesize expressNameCell = _expressNameCell;
@synthesize expressNumberCell = _expressNumberCell;
@synthesize queryButtonState=_queryButtonState;
@synthesize segmentTitle=_segmentTitle;
@synthesize selectedTabItem=_selectedTabItem;
@synthesize queryRequest=_queryRequest;
@synthesize resultList=_resultList;
@synthesize orderListTotal=_orderListTotal;
@synthesize isLoading=_isLoading;
@synthesize currentPage=_currentPage;
@synthesize loginUserName=_loginUserName;

@synthesize parentTitle = _parentTitle;

-(AMLogiticsData*)logiticsData
{
    if (_logiticsData==nil) {
        _logiticsData = [[AMLogiticsData alloc]init];
    }
    return _logiticsData;
}

-(AMExpressName*)expressNameCell
{
    if (_expressNameCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMExpressName" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMExpressName class]])
                _expressNameCell = (AMExpressName *)oneObject;
        
        [_expressNameCell.button addTarget:self action:@selector(expressNameButtonTapped:) forControlEvents:UIControlEventTouchUpInside];  
        [_expressNameCell.contentButton addTarget:self action:@selector(expressNameButtonTapped:) forControlEvents:UIControlEventTouchUpInside];  
    }
    return _expressNameCell;
}

-(AMExpressNumber*)expressNumberCell
{
    if (_expressNumberCell==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMExpressNumber" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMExpressNumber class]])
                _expressNumberCell = (AMExpressNumber *)oneObject;
        
        [_expressNumberCell.button addTarget:self action:@selector(expressNumberButtonTapped:) forControlEvents:UIControlEventTouchUpInside];    
        [_expressNumberCell.content addTarget:self action:@selector(expressNumberDidAndExit:) forControlEvents:UIControlEventEditingDidEndOnExit];  
        [_expressNumberCell.content addTarget:self action:@selector(expressNumberEditChanged:) forControlEvents:UIControlEventEditingChanged];  
    }
    return _expressNumberCell;
}

-(void)setQueryButtonState:(BOOL)queryButtonState
{
    _queryButtonState = queryButtonState;
    if (queryButtonState) {
        [self.queryButton setEnabled:YES];
    }
    else
    {
        [self.queryButton setEnabled:NO];
    }
}

-(NSString*)commonTableViewBackButtonTitle {
    return _parentTitle;
}

-(void)setSelectedTabItem:(int)selectedTabItem
{
    if (_selectedTabItem==selectedTabItem) {
        return;
    }
    
    _selectedTabItem = selectedTabItem;
    
    if (selectedTabItem<0||selectedTabItem>1) {
        return;
    }
   
    switch (_selectedTabItem) {
        case 0:
        {
            self.myOrderTabel.hidden = NO;
            [self.myOrderView setHidden:NO];
            [self.expressQueryView setHidden:YES];
            if([[LoginToken getLoginUserName] length] > 3){ 
                [self.noLoginView setHidden:YES];
                if(![self.loginUserName isEqualToString:[LoginToken getLoginUserName]])
                {
                    [self.loginUserName release];
                    self.loginUserName=[LoginToken getLoginUserName];
                self.orderListTotal=0;
                [self.resultList removeAllObjects];
                [self.myOrderTabel reloadData];
                [self loadObjectsFromRemote];
                }
                else {
                    if ([self.resultList count]==0) {
                        [self showNodataMessage];
                    }
                }
                
            }else{
                [self.loginUserName release];
                self.loginUserName = nil;
                [self showNoLogInMessage];
     
            } 
        }
            break;
        case 1:
        {
            if (!self.mLoadingView.noDataView.hidden) {
                [self.mLoadingView endLoadingView];
            }
            else {
//                [self.view sendSubviewToBack:self.mLoadingView];
                self.mLoadingView.hidden = YES;
            }

            [self.myOrderView setHidden:YES];
            [self.expressQueryView setHidden:NO];
            [self.noLoginView setHidden:YES];
            if (self.logiticsData.data.name==nil||self.logiticsData.data.name==0) {
                self.expressNameCell.content.text = DEFAULT_EXPRESS_NAME;
            }
            else
            {
                self.expressNameCell.content.text = self.logiticsData.data.name;
            }
            [self refreshQueryButtonState];
            if ([self.logiticsData.historyData count]) {
                [self.historyTable reloadData];
                [self.historyTable setHidden:NO];
            }
            else {
                [self.historyTable setHidden:YES];
            }


        }
            break;
        default:
            break;
    }
}

- (void) segmentValueChanged:(int)nowIndex
{
    if (nowIndex==0) {
         [AMLogUtils appendLog: APP_LOGISTICS_ONE]; 
    }
    else {
         [AMLogUtils appendLog: APP_LOGISTICS_TWO]; 
    }
    self.selectedTabItem = nowIndex;
}

-(AMMyLogisticsOrderRequest*)queryRequest
{
    if (_queryRequest==nil) {
        _queryRequest = [[AMMyLogisticsOrderRequest alloc] init];
    }
    
    _queryRequest.pageIndex=[NSNumber numberWithInt:self.currentPage];
    _queryRequest.pageSize= [NSNumber numberWithInt:9];
    return _queryRequest;
}

-(NSMutableArray*)resultList
{
    if (_resultList==nil) {
        _resultList = [[NSMutableArray alloc] init];
    }
    return _resultList;
}

-(void)refreshQueryButtonState
{
    BOOL state = NO;
    if ([self.expressNumberCell.content.text length]==0||[self.expressNameCell.content.text length]==0||[self.expressNameCell.content.text isEqualToString: DEFAULT_EXPRESS_NAME]) {
        state = NO;
    }
    else
    {
        state = YES;
    }
    if (state!=self.queryButtonState) {
        self.queryButtonState = state;
    }
}

-(IBAction)expressNumberDidAndExit:(id)sender
{
    [self.expressNumberCell.content resignFirstResponder];
}

-(IBAction)expressNumberEditChanged:(id)sender
{
    [self refreshQueryButtonState];
}

- (IBAction)loginButtonPressed {
    UIViewController *nextController;
    nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
    nextController.hidesBottomBarWhenPushed=YES;   
    [self.navigationController pushViewController:nextController animated:YES]; 
}

- (void)dealloc {
    [_contentTable release];
    [_historyTable release];
    [_logiticsData release];
    [_expressNameCell release];
    [_expressNumberCell release];
    [_queryButton release];
    [_segmentTitle release];

    [_expressQueryView release];
    [_myOrderView release];
    [_queryRequest release];
    [_resultList release];
    [_myOrderTabel release];
    [_loginButton release];
    [_noLoginView release];
    [_errorMessage release];
    [_loginUserName release];
    [_parentTitle release];
    [super dealloc];
}

- (void)viewDidUnload {
    [self setContentTable:nil];
    [self setHistoryTable:nil];
    [_logiticsData release];
    _logiticsData = nil;
    _expressNumberCell = nil;
    _expressNameCell = nil;
    [_segmentTitle release];
    _segmentTitle = nil;
    [_queryRequest release];
    _queryRequest =nil;
    [_resultList release];
    _resultList = nil;
    _loginUserName = nil;
    [self setQueryButton:nil];
    [self setExpressQueryView:nil];
    [self setMyOrderView:nil];
    [self setMyOrderTabel:nil];
    [self setLoginButton:nil];
    [self setNoLoginView:nil];
    [self setErrorMessage:nil];
      self.currentPage=0;
    [super viewDidUnload];
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    self.queryButtonState = NO; 
    self.historyTable.showsVerticalScrollIndicator = NO;
    self.historyTable.bounces = NO;
    self.selectedTabItem = -1;
    self.currentPage=0;
    
}

-(BOOL)showBackButton
{
    return YES;
}

-(NSArray*)segmentTitle
{
    if (!_segmentTitle) {
        _segmentTitle = [[NSArray alloc]initWithObjects:@"我的运单",@"物流查询",nil];
    }
    return _segmentTitle;
}

-(NSArray*)commonTableViewSegmentTitle
{
    return self.segmentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"物流查询";
}
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.navigationItem.title = NSLocalizedString(@"Logitics", @"");
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_express"];
        self.tabBarItem.title=NSLocalizedString(@"Logitics", @"");        
    }
    return self;
}
- (void)viewWillAppear:(BOOL)animated
{
     int select = self.selectedTabItem;
    if (![self.loginUserName isEqualToString:[LoginToken getLoginUserName]]) {
       
        if (select ==-1) {
            select = 0;
            
        }
       
        self.currentPage=1;
    }
        _selectedTabItem = -1;
        self.selectedTabItem = select;
   
    
       [super viewWillAppear:animated];

}
- (void)loadObjectsFromRemote {
    //检查accesstoken是否过期
//    [LoginToken checkAccessTokenExpired];
    self.isLoading = YES;
    if (self.currentPage>1) {
        AMMoreLoadingView * moreLoadingView = [[AMMoreLoadingView alloc]init];
        self.myOrderTabel.tableFooterView = moreLoadingView;
        [moreLoadingView release];
    }else {
        [self.mLoadingView showLoadingView];
    }
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* logisticsOrderResultMapping = [AMMylogisticsOrderResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: logisticsOrderResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_TRADE_SALE_REQUEST_URL usingBlock:^(RKObjectLoader* loader)  {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMMylogisticsOrderResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.queryRequest;
    }];
//    [super loadObjectsFromRemote];
}
- (void) showNodataMessage
{
    [self.noLoginView setHidden:NO];
    self.errorMessage.text = @"您暂时没有运单信息喔！";
    [self.loginButton setHidden:YES];
    self.myOrderTabel.hidden = YES;
}
- (void) showNoLogInMessage
{
    [self.noLoginView setHidden:NO];
     self.errorMessage.text = @"您暂时还未登录";
    [self.loginButton setHidden:NO];
    self.myOrderTabel.hidden = YES;
}
#pragma mark RKObjectLoaderDelegate methods
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
     self.isLoading = NO;
    if (self.currentPage*[self.queryRequest.pageSize intValue]>=self.orderListTotal) {
        self.myOrderTabel.tableFooterView = nil;
    }
    if ([objects count]==0) {
        [self showNodataMessage];
//        [super objectLoader:objectLoader didLoadObjects:objects];
        
        return;
    }
    AMMylogisticsOrderResult *result = (AMMylogisticsOrderResult*)[objects objectAtIndex:0];
    if ([self.resultList count]==0) {
        [self.myOrderTabel reloadData];
    }
    
    [self.resultList addObjectsFromArray:result.resultList];
    self.orderListTotal= [result.totalCount intValue];
	[self.myOrderTabel reloadData] ;
//    [super objectLoader:objectLoader didLoadObjects:objects];
    [self.mLoadingView endLoadingView];
}

- (IBAction)queryButtonPressed {
     [AMLogUtils appendLog: APP_LOGISTICS_SEVEN];
    [self.expressNumberCell.content resignFirstResponder];
    if ([self.expressNameCell.content.text length]==0||[self.expressNameCell.content.text isEqualToString: DEFAULT_EXPRESS_NAME]) {
       [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"请选择物流公司"] show];
    }
    else if ([self.expressNumberCell.content.text length]==0)
    {
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"请输入运单号"] show];
    }
    else
    {
        
        AMLogiticsQueryResultViewController *result = [[[AMLogiticsQueryResultViewController alloc] initWithNibName:@"AMLogiticsQueryResultViewController" bundle:nil] autorelease];
        result.parentTitle = @"物流";
        result.company = self.logiticsData.data;
        result.number = self.expressNumberCell.content.text; 
        [self.logiticsData saveHistoryData:self.logiticsData.data orderNumber:self.expressNumberCell.content.text];
        result.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:result animated:YES];
        
    }
}


-(IBAction)expressNameButtonTapped:(UIButton*)sender
{
       [AMLogUtils appendLog: APP_LOGISTICS_FIVE]; 
    [self.expressNumberCell.content resignFirstResponder];
    AMCompanySelectViewController *company = [[[AMCompanySelectViewController alloc] initWithNibName:@"AMCompanySelectViewController" bundle:nil] autorelease];
    company.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:company animated:YES];
}
-(IBAction)expressNumberButtonTapped:(UIButton*)sender
{
    [AMLogUtils appendLog: APP_LOGISTICS_SIX]; 
      [self.expressNumberCell.content resignFirstResponder];
    // ADD: present a barcode reader that scans from the camera feed
    ZBarReaderViewController *reader = [ZBarReaderViewController new];
    reader.readerDelegate = self;
    reader.supportedOrientationsMask = ZBarOrientationMaskAll;
    
    ZBarImageScanner *scanner = reader.scanner;
    // TODO: (optional) additional reader configuration here
    
    // EXAMPLE: disable rarely used I2/5 to improve performance
    [scanner setSymbology: ZBAR_I25
                   config: ZBAR_CFG_ENABLE
                       to: 0];
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_HIDETABBAR object:self];
    // present and release the controller
    [self presentModalViewController: reader
                            animated: YES];
    [reader release];
    
    
}
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [picker dismissModalViewControllerAnimated: YES]; 
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_UNHIDETABBAR object:self];
}
- (void) imagePickerController: (UIImagePickerController*) reader
 didFinishPickingMediaWithInfo: (NSDictionary*) info
{
    // ADD: get the decode results
    id<NSFastEnumeration> results =
    [info objectForKey: ZBarReaderControllerResults];
    ZBarSymbol *symbol = nil;
    for(symbol in results)
        // EXAMPLE: just grab the first barcode
        break;
    
    // EXAMPLE: do something useful with the barcode data
      
    self.expressNumberCell.content.text=symbol.data;
    // ADD: dismiss the controller (NB dismiss from the *reader*!)
 
    [reader dismissModalViewControllerAnimated: YES];
     [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_UNHIDETABBAR object:self];

}

#pragma mark Table View Data Source Methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView==self.myOrderTabel) {
        return [AMMyLogiticsOrderCell cellHeight];
    }
    else if (tableView==self.contentTable) {
        return [AMExpressName cellHeight];
    }
    else
    {
        return [AMExpressHistory cellHeight];
    }
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section
{
    if (tableView==self.myOrderTabel) {
//          if ([self.resultList count]!=self.orderListTotal)
//        return [self.resultList count]+1;
//          else {
              return [self.resultList count];
//          }
    }
    else if (tableView==self.contentTable)
    {
        return 2;
    }
    else
    {
        return [self.logiticsData.historyData count]/4;
    }
}
- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
    NSUInteger row = [indexPath row];

    if (tableView==self.myOrderTabel) {
        
        
//        if ([self.resultList count]!=self.orderListTotal) { 
//            if ([indexPath row]==[self.resultList count]) {
//                AMMoreLoadingCell *cell = (AMMoreLoadingCell *)[tableView 
//                                                                dequeueReusableCellWithIdentifier: [AMMoreLoadingCell cellIdentifer]];
//                if (cell == nil)  
//                {
//                    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMMoreLoadingCell" 
//                                                                 owner:self options:nil];
//                    for (id oneObject in nib)
//                        if ([oneObject isKindOfClass:[AMMoreLoadingCell class]])
//                            cell = (AMMoreLoadingCell *)oneObject;
//                }
//                return cell;
//                
//            }
//        }
        
        AMMyLogiticsOrderCell *cell = (AMMyLogiticsOrderCell *)[tableView 
                                                    
                                                    dequeueReusableCellWithIdentifier: [AMMyLogiticsOrderCell cellIdentifer]];
        if (cell == nil)  
        {
            cell = [AMMyLogiticsOrderCell createCell];
        }
        
        NSUInteger row = [indexPath row];
        AMMylogisticsOrder* order = [self.resultList objectAtIndex:row];
        cell.name.text = order.receiverName;

        cell.content.text = [NSString stringWithFormat:@"%@:%@",(order.logisticsCorpName==nil?@"":order.logisticsCorpName),(order.mailNo==nil?@"":order.mailNo)];
 
        return cell;
    }
    else if (tableView==self.contentTable)
    {
                if (row==0) {
            AMExpressName *cell = (AMExpressName *)[tableView 
                                                    dequeueReusableCellWithIdentifier: [AMExpressName cellIdentifer]];
            if (cell == nil)  
            {
                cell = self.expressNameCell;
            }
                    if (self.logiticsData.data.name==nil||self.logiticsData.data.name==0) {
                        cell.content.text = DEFAULT_EXPRESS_NAME;
                    }
                    else
                    {
                        cell.content.text = self.logiticsData.data.name;
                    }


            return cell;

        }
        else
        {
            AMExpressNumber *cell = (AMExpressNumber *)[tableView 
                                                    dequeueReusableCellWithIdentifier: [AMExpressNumber cellIdentifer]];
            if (cell == nil)  
            {
               
                cell = self.expressNumberCell;
            }
            
            
            return cell;

        }
        
                
    }
    else
    {
        AMExpressHistory *cell = (AMExpressHistory *)[tableView 
                                                    dequeueReusableCellWithIdentifier: [AMExpressHistory cellIdentifer]];
        if (cell == nil)  
        {
            
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMExpressHistory" 
                                                         owner:self options:nil];
            for (id oneObject in nib)
                if ([oneObject isKindOfClass:[AMExpressHistory class]])
                    cell = (AMExpressHistory *)oneObject;
            UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
            UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
            bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
            cellBackBtn.image =bkImage;
            
            cell.selectedBackgroundView = cellBackBtn;
            [cellBackBtn release]; 

        }
        NSUInteger index = row*4;
        NSString *name = [self.logiticsData.historyData objectAtIndex:index];
        NSString *number = [self.logiticsData.historyData objectAtIndex:index+3];
        cell.content.text = [NSString stringWithFormat:@"%@: %@",name,number];
        return cell;
    }
}
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger row = [indexPath row];
    if(tableView == self.historyTable){
        [AMLogUtils appendLog: APP_LOGISTICS_EIGHT]; 

        
        AMLogiticsQueryResultViewController *result = [[[AMLogiticsQueryResultViewController alloc] initWithNibName:@"AMLogiticsQueryResultViewController" bundle:nil] autorelease];
        NSUInteger index = row*4;
        AMCorporation* company = [[AMCorporation alloc]init];
        company.name = [self.logiticsData.historyData objectAtIndex:index];
        company.code = [self.logiticsData.historyData objectAtIndex:index+1];
        company.pinyin = [self.logiticsData.historyData objectAtIndex:index+2];
        result.parentTitle = @"物流";
        result.company = company;
        result.number = [self.logiticsData.historyData objectAtIndex:index+3];
       
        result.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:result animated:YES];
        [company release];
        
        [self.historyTable deselectRowAtIndexPath:indexPath animated:YES];
    }
    else if (tableView==self.myOrderTabel){
         [AMLogUtils appendLog: APP_LOGISTICS_THREE]; 
        if ([self.resultList count]!=self.orderListTotal) { 
            if ([indexPath row]==[self.resultList count])
            {
                return;
            }
        }
              AMMylogisticsOrder* order = [self.resultList objectAtIndex:row];
        AMCorporation* company = [[AMCorporation alloc]init];
        company.name = order.logisticsCorpName;
        company.code = order.logisticsCompanyid;
        if (company.name==nil||company.code==nil||order.mailNo==nil) {
            
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"物流信息不全，无法查询"] show];
        [company release];
            return;
        }

        AMLogiticsQueryResultViewController *result = [[[AMLogiticsQueryResultViewController alloc] initWithNibName:@"AMLogiticsQueryResultViewController" bundle:nil] autorelease];
        result.company = company;
        result.number = order.mailNo; 
        result.parentTitle = @"物流";
        [company release];
        [self.logiticsData saveHistoryData:self.logiticsData.data orderNumber:self.expressNumberCell.content.text];
        result.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:result animated:YES];

    }
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    if(tableView == self.historyTable){
        return 25;
    }
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    if(tableView == self.historyTable){
        AliTitleCellView * titleView = [[[AliTitleCellView alloc] initWithFrame:CGRectMake(0, 0, 320, 25)] autorelease];
        [titleView setPaddingLeft:10];
        
        [titleView setTitle:@"物流查询历史"];
        return  titleView;
    }
    return nil;
    
}
- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 10.0)
    {
        if (scroll==self.myOrderTabel)
        {
//            if ([self.resultList count]!=self.orderListTotal)
            if (self.currentPage*[self.queryRequest.pageSize intValue] < self.orderListTotal) 
            {
                if (!self.isLoading) 
                {
                    self.currentPage++;
                    [self loadObjectsFromRemote];
                } 
            }
         }
    }
}

- (void)OceanClient:(RKOceanClient *)oceanClient didRefreshTokenOutOfDate:(RKResponse *)response{
    [super OceanClient:oceanClient didRefreshTokenOutOfDate:response];
    [self.mLoadingView showNodataMessage];
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"鉴权失败"] show]; 
    
    UIViewController *nextController;
    nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
    nextController.hidesBottomBarWhenPushed=YES;
    
    [self.navigationController pushViewController:nextController animated:YES];
}

- (void)OceanClient:(RKOceanClient *)oceanClient didDonotLogin:(RKResponse *)response{
    [super OceanClient:oceanClient didDonotLogin:response];
    [self.mLoadingView showNodataMessage];
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"请您重新登陆"] show]; 
}
-(void)objectLoader:(RKObjectLoader *)objectLoader didFailWithError:(NSError *)error{
    [self.mLoadingView endLoadingView];
    if ([error code]==RKRequestBaseURLOfflineError||[error code]==RKRequestConnectionTimeoutError||[error code]==NSURLErrorConnectionToBeOffline) {
        if ([self.resultList count]) {
            AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
            self.myOrderTabel.tableFooterView = errorMessageView;
            [errorMessageView release];
            self.currentPage--;
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
    }
    self.isLoading = NO;
}

@end

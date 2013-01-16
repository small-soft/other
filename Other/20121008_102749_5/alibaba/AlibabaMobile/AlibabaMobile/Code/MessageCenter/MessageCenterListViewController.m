//
//  MessageCenterListViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MessageCenterListViewController.h"
#import "AMMessageRequest.h"
#import "HJObjManager.h"
#import "UIHelp.h"
#import "ConstDef.h"
#import "LoginToken.h"
#import "StringUtils.h"
#import "AMMobileMessageQueryResult.h"
#import "AliTitleCellView.h"
#import "MessageListCell.h"
#import "MessageTypeListCell.h"
#import "AMMobileMessage.h"
#import "AMOperationMessageParam.h"
#import "KeyValueObject.h"
#import "UIHelp.h"
#import "StringUtils.h"
#import "MessageCenterButtonView.h"
#import "UIHelp.h"
#import "AMAppDelegate.h"
#import "AliToastView.h"
#import "AMNewProductsCategoryViewController.h"
#import "AMHotRankViewController.h"
#import "AMFavoritesViewController.h"
#import "AMLogiticsQueryResultViewController.h"
#import "AMBannerContentDetailViewController.h"
#import "AMNewsDetailViewController.h"
#import "AliNavigationViewController.h"
#import "AMOfferListViewController.h"
#import "AMCustomerAndPrecisionHomeViewController.h"
#import "AMLogiticsViewController.h"
#import "SVPullToRefresh.h"
#import "AMNewsViewController.h"
#import "AMPriceGraphViewController.h"
#import "AMMappingUtil.h"
#import "ImageMagazineCategoryViewController.h"
#import "ImageMagazineListViewController.h"
#import "ImageMagazineDetailViewController.h"
#import "AMFavoriteOfferPriceChangeMessage.h"
#import "AMOfferTabViewController.h"
#import "AliToastView.h"
#import "AMOrderDetailViewController.h"
#import "AMOrderMessage.h"
@interface MessageCenterListViewController()

@property (nonatomic, retain) AMMessageRequest * mReadRequest;
@property (nonatomic, retain) NSMutableArray * mMsgResult;
@property (nonatomic, retain) NSMutableArray * mMsgGroupDict;
@property (nonatomic, retain) NSString * mMsgFilter;

@property (nonatomic, retain) IBOutlet UITableView * mTableView;
@property (nonatomic, retain) IBOutlet UIView * mMsgTypeSelectionView;
@property (nonatomic, retain) IBOutlet UITableView * mMsgTypeTableView;
@property (nonatomic, retain) IBOutlet UIView * mTipsView;
@property (nonatomic, retain) IBOutlet UILabel * mMessageTypeLabel;
@property (nonatomic, retain) IBOutlet UIButton * mSelectMsgTypeButtonUp;
@property (nonatomic, retain) IBOutlet UIButton * mSelectMsgTypeButtonDown;
@property (nonatomic, retain) AliRightBarButtonItem * buttonsItem;
@property (nonatomic,assign) BOOL isAppear;
- (void)recvNewMsg;
- (IBAction)onSelectMsgType: (id)sender;

@end


@implementation MessageCenterListViewController

@synthesize mTableView = _mTableView;
@synthesize mMsgTypeSelectionView = _mMsgTypeSelectionView;
@synthesize mMsgTypeTableView = _mMsgTypeTableView;
@synthesize mTipsView = _mTipsView;
@synthesize mMessageTypeLabel = _mMessageTypeLabel;
@synthesize mSelectMsgTypeButtonUp = _mSelectMsgTypeButtonUp;
@synthesize mSelectMsgTypeButtonDown = _mSelectMsgTypeButtonDown;

@synthesize mReadRequest = _mReadRequest;
@synthesize mMsgResult = _mMsgResult;
@synthesize mMsgGroupDict = _mMsgGroupDict;
@synthesize mMsgFilter = _mMsgFilter;
@synthesize buttonsItem = _buttonsItem;
@synthesize isAppear =_isAppear;
- (id)init {
    self = [super init];
    if (self) {  
        self.mMsgFilter = AMSourceName_All;
    }
    return self;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [_mTableView release];
    [_mMsgTypeTableView release];
    [_mMsgResult release];
    [_mMsgGroupDict release];
    [_mReadRequest release];
    [_mTipsView release];
    [_buttonsItem release];
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setTitle:@"消息中心"];
    [self setBackButtonText:@"返回"];
    self.mSelectMsgTypeButtonUp.hidden = YES;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvNewMsg) name:NOTIFICATION_MSG_RECV object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(recvFailedMsg) name:NOTIFICATION_MSG_RECV_FAILED object:nil];
    [self.mTableView setSeparatorColor:[UIHelp colorWithHexString:@"0xe0e0e0"]];
    [self.mMsgTypeTableView setSeparatorColor:[UIHelp colorWithHexString:@"0xe0e0e0"]];
    [self recvNewMsg];
    //增加针对拉动的句柄
    [self.mTableView addPullToRefreshWithActionHandler:^{
        if (self.mTableView && self.mTableView.pullToRefreshView) {
            self.mTableView.pullToRefreshView.lastUpdatedDate = [NSDate date];
            
            AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
            [appDelegate reLoadMsgList];
            self.mSelectMsgTypeButtonDown.enabled = NO;
        }
    }];
    self.navigationItem.rightBarButtonItem = self.buttonsItem;
}

- (void)viewDidUnload
{
    _buttonsItem.delegate = nil;
    _buttonsItem = nil;
    self.mTableView = nil;
    self.mMsgTypeTableView = nil;
    [super viewDidUnload];
}


-(void)viewDidAppear:(BOOL)animated{
    self.isAppear = YES;
    [super viewDidAppear:animated];
}

-(void)viewDidDisappear:(BOOL)animated{
    self.isAppear = NO;
    [super viewDidDisappear:animated];
}
- (void)recvNewMsg
{
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    self.mMsgResult = appDelegate.mMsgResult;
    
    self.mMsgGroupDict = nil;
    self.mMsgGroupDict = [[NSMutableArray alloc] initWithArray: appDelegate.mMsgGroupDict];
    
    if(self.mMsgResult != nil
        && self.mMsgResult.count >0){
        [self showMessageListView:YES];
    }else{
        [self showMessageListView: NO];
    }
    
    //停止下拉刷新
//    [self.mTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
    [self.mTableView.pullToRefreshView stopAnimating];
    self.mSelectMsgTypeButtonDown.enabled = YES;
}
-(void)recvFailedMsg{
    
    if (self.isAppear) {
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:NSLocalizedString(@"Failed to connect with server", nil)] show];
    }



    [self.mTableView.pullToRefreshView stopAnimating];
    self.mSelectMsgTypeButtonDown.enabled = YES;
}
- (void)showEmptyView: (BOOL)show {
    if ( show ) {
        self.mTipsView.frame = CGRectMake(0, 42, self.mTipsView.frame.size.width, self.mTipsView.frame.size.height);
        [self.view addSubview: self.mTipsView];
    }else {
        [self.mTipsView removeFromSuperview];
    }
}

- (void)showMessageListView: (BOOL)show {
    if ( show ) {
        [self showEmptyView: NO];
        
        self.mTableView.frame = CGRectMake(0, 44, self.mTableView.frame.size.width, self.mTableView.frame.size.height);
        [self.view addSubview: self.mTableView];
        self.mTableView.delegate = self;
        self.mTableView.dataSource = self;
        [self.mTableView reloadData];
    }else {
        [self.mTableView removeFromSuperview];
        
        [self showEmptyView: YES];
    }
}

- (void)reachabilityChanged:(NSNotification *)notification {
    RKReachabilityObserver* observer = (RKReachabilityObserver *) [notification object];
    RKLogCritical(@"AliBaseViewController - Received reachability update: %@", observer);
    
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

        AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        if(appDelegate.mMsgResult == nil || [appDelegate.mMsgResult count] <= 0 || self.mMsgResult == nil || [self.mMsgResult count] <=0) {
            [appDelegate reLoadMsgList];
        }
        
    } else {
        NSLog(@"Network unreachable!");
    }
}

- (void)showMessageTypeList: (BOOL)show {
    if (show) {
        self.mMsgTypeSelectionView.frame = CGRectMake(0, 42, self.mMsgTypeSelectionView.frame.size.width, self.mMsgTypeSelectionView.frame.size.height);
        [self.view addSubview: self.mMsgTypeSelectionView];
        self.mMsgTypeTableView.frame = CGRectMake(10, 42, self.mMsgTypeTableView.frame.size.width, [self.mMsgGroupDict count] < 5 ? [self.mMsgGroupDict count] * 45 : self.mMsgTypeTableView.frame.size.height);
        [self.view insertSubview:self.mMsgTypeTableView aboveSubview:self.mMsgTypeSelectionView];
        self.mMsgTypeTableView.delegate = self;
        self.mMsgTypeTableView.dataSource = self;
        [self.mMsgTypeTableView reloadData];
        
        self.mSelectMsgTypeButtonDown.hidden = YES;
        self.mSelectMsgTypeButtonUp.hidden   = NO;
    } else {
        [self.mMsgTypeTableView removeFromSuperview];
        [self.mMsgTypeSelectionView removeFromSuperview];
        
        self.mSelectMsgTypeButtonDown.hidden = NO;
        self.mSelectMsgTypeButtonUp.hidden   = YES;
    }
}

- (IBAction)onSelectMsgType: (id)sender {
    if (self.mSelectMsgTypeButtonDown == sender) { 
        [self showMessageTypeList:YES];
    } else {
        [self showMessageTypeList:NO];
    }
}

#pragma 

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
    NSLog(@"Loaded objects: %@", objects);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    NSLog(@"didFailWithError, error: %@", error);
}

- (id)objectByRowIndex: (NSInteger)row {
    if(self.mMsgResult == nil
       || self.mMsgResult.count == 0) {
        return nil;
    }
    
    NSUInteger count = self.mMsgResult.count;
    NSUInteger index = 0;
    
    if ( [self.mMsgFilter isEqualToString: AMSourceName_All] ) {
        return [self.mMsgResult objectAtIndex:row];
    }
    
    if ( [self.mMsgFilter isEqualToString: AMSourceName_New] ) {
        for(int i=0; i< count; i++){
            AMMobileMessage * msg = ((AMMobileMessage *)[self.mMsgResult objectAtIndex:i]);
            if( ![msg hasRead].boolValue ){
                if(index == row){
                    return msg;
                }else{
                    index ++;
                }
            }
        }
    }
    
    for(int i=0; i< count; i++){
        AMMobileMessage * msg = ((AMMobileMessage *)[self.mMsgResult objectAtIndex:i]);
        if([[msg sourceDisplayName] isEqualToString:self.mMsgFilter]){
            if(index == row){
                return msg;
            }else{
                index ++;
            }
        }
    }
    
    return nil;
}

- (NSInteger)countByMessageType {
    if(self.mMsgResult ==  nil
       || self.mMsgResult.count == 0) {
        return 0;
    }
    
    NSUInteger count = self.mMsgResult.count;
    NSUInteger countByType = 0;
    
    if ( [self.mMsgFilter isEqualToString: AMSourceName_All] ) {
        return count;
    }
    
    if ( [self.mMsgFilter isEqualToString: AMSourceName_New] ) {
        for(int i=0; i< count; i++){
            AMMobileMessage * msg = ((AMMobileMessage *)[self.mMsgResult objectAtIndex:i]);
            if( ![msg hasRead].boolValue ){
                countByType ++;
            }
        }
    }
    
    for(int i=0; i< count; i++){
        AMMobileMessage * msg = ((AMMobileMessage *)[self.mMsgResult objectAtIndex:i]);
        if([[msg sourceDisplayName] isEqualToString:self.mMsgFilter]){
            countByType ++;
        }
    }
    
    return countByType;
}

- (void)requestReadMsgToRemote {

    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];

    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MESSAGE_READ usingBlock:^(RKObjectLoader* loader) {
		loader.delegate = self;
        loader.method = RKRequestMethodPOST;
        loader.params = self.mReadRequest;
    }];
}

-(void)setReadRequest:(NSNumber *)msgId
{
    self.mReadRequest = [[AMMessageRequest alloc] init];  
    self.mReadRequest.memberId = [LoginToken getLoginUserName];
    self.mReadRequest.messageId = msgId;
    self.mReadRequest.requestURL = OCEAN_API_URL_MESSAGE_READ;
    
    [self requestReadMsgToRemote];
} 


#pragma table

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (tableView.tag) {
        case 1: // Message table view
        {
            AMMobileMessage * msg = (AMMobileMessage *)[self objectByRowIndex:indexPath.row];
            return [MessageListCell getCellHeightWithSubject:[StringUtils removeHtmlLabelsAndBlanksFromString: msg.textData ]];
        }
            
        case 2: // Message Type table view
            return 45;
            
        default:
            break;
    }
    
    return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    //return 25;
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    switch (tableView.tag) {
        case 1: // Message table view
            break;
            
        case 2: // Message Type table view
            break;
            
        default:
            break;
    }
    
    return nil;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    switch (tableView.tag) {
        case 1: // Message table view
            break;
            
        case 2: // Message Type table view
            break;
            
        default:
            break;
    }
    
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    switch (tableView.tag) {
        case 1: // Message table view
            if ( [self countByMessageType] > 0 ) {
                [self showEmptyView: NO];
            }else {
                [self showEmptyView: YES];
            }
            
            return [self countByMessageType];
            
        case 2: // Message Type table view
            return self.mMsgGroupDict.count;
            
        default:
            break;
    }
    
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int row = [indexPath row];
    
    switch (tableView.tag) {
        case 1: // Message table view
        {
            if(self.mMsgResult !=  nil
               && self.mMsgResult.count >0){
                MessageListCell *cell = (MessageListCell *)[tableView dequeueReusableCellWithIdentifier:@"MessageListCell"];
                if (cell == nil)  
                {
                    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"MessageListCell" owner:self options:nil];
                    for (id oneObject in nib)
                        if ([oneObject isKindOfClass:[MessageListCell class]])
                            cell = (MessageListCell *)oneObject;
                    UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
                    UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
                    bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
                    cellBackBtn.image =bkImage;
                    
                    cell.selectedBackgroundView = cellBackBtn;
                    [cellBackBtn release]; 
                }
                AMMobileMessage * msg = (AMMobileMessage *)[self objectByRowIndex:row];
               
                NSString * timeStr =  [StringUtils getDateStrLong:msg.gmtOccured.doubleValue/1000];
                cell.mDateLabel.text = timeStr;  
                cell.mTypeLabel.text = [msg sourceDisplayName];

                if(msg.hasRead.boolValue){
                    cell.mSubjectLabel.textColor = [UIHelp colorWithHexString:@"0x666666"];
                    cell.mSubjectLabel.font = [UIFont systemFontOfSize:16.0f];
                    cell.mDateLabel.textColor = [UIHelp colorWithHexString:@"0x666666"];
                    cell.mDateLabel.font = [UIFont systemFontOfSize:14.0f];
                    cell.mTypeLabel.textColor = [UIHelp colorWithHexString:@"0x666666"];
                    cell.mTypeLabel.font = [UIFont systemFontOfSize:14.0f];
                    
                    cell.mNewMessageIcon.hidden = YES;
                }else{
                    cell.mSubjectLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    cell.mSubjectLabel.font = [UIFont boldSystemFontOfSize:16.0f];
                    cell.mDateLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    cell.mDateLabel.font = [UIFont systemFontOfSize:14.0f];
                    cell.mTypeLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    cell.mTypeLabel.font = [UIFont systemFontOfSize:14.0f];
                    
                    cell.mNewMessageIcon.hidden = NO;
                }
                 [cell setSubject: [StringUtils removeHtmlLabelsAndBlanksFromString: msg.textData ]];
                return cell;
            }
        
            return nil;
        }
            
        case 2: // Message Type table view
        {
            if(self.mMsgGroupDict !=  nil
               && self.mMsgGroupDict.count >0){
                MessageTypeListCell *cell = (MessageTypeListCell *)[tableView 
                                                                    dequeueReusableCellWithIdentifier:@"MessageTypeListCell"];
                if (cell == nil)  
                {
                    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"MessageTypeListCell" 
                                                                 owner:self options:nil];
                    for (id oneObject in nib)
                        if ([oneObject isKindOfClass:[MessageTypeListCell class]])
                            cell = (MessageTypeListCell *)oneObject;
                    UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
                    UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
                    bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
                    cellBackBtn.image =bkImage;
                    
                    cell.selectedBackgroundView = cellBackBtn;
                    [cellBackBtn release]; 
                }
                
                [cell setTitle: (NSString *)((KeyValueObject *)[self.mMsgGroupDict objectAtIndex:row]).key];
                
                return cell;
            }
            
            return nil;
        }
            
        default:
            break;
    }
    
    return  nil;

}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    //NSUInteger section = [indexPath section];
    NSUInteger row = [indexPath row];
    BOOL showMessageReadHint = NO;
    
    switch (tableView.tag) {
        case 1: // Message table view
        {
            AMMobileMessage * msg = (AMMobileMessage *)[self objectByRowIndex:row];
            if(![msg hasRead].boolValue){
                msg.hasRead = [NSNumber numberWithBool: YES];
                showMessageReadHint = YES;
                [self.mTableView reloadData];
                [self setReadRequest:msg.identifier];
                
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MSG_READ object:self];
            }
            
            // 解析运营跳转参数
            AMOperationMessageParam * operationParam = nil;
            if (msg.jsonData != nil && [msg.jsonData length] > 0) {
                NSError* error = nil;
                id<RKParser> parser = [[RKParserRegistry sharedRegistry] parserForMIMEType:RKMIMETypeJSON];
                id parsedData = [parser objectFromString:(NSString*)msg.jsonData error:&error];
                if (parsedData && !error) {
                    // Setup object mapping
                    RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
                    [mappingProvider setMapping:[AMOperationMessageParam sharedObjectMapping] forKeyPath:@""];
                    
                    RKObjectMapper* mapper = [RKObjectMapper mapperWithObject:parsedData mappingProvider:mappingProvider];
                    RKObjectMappingResult* result = [mapper performMapping];
                    if (result) {
                        operationParam = [result asObject];
                    }
                }
            } 
            
            [self.mTableView deselectRowAtIndexPath:indexPath animated:NO];

            // 消息中心跳转逻辑处理
            
            // 我的运单，运单状态提醒
            if ([msg.type isEqualToString:@"ALI56_custm_odstatus_change"]
                || [msg.type isEqualToString:@"ALI56_custm_odstatus_finish"]
                || [msg.type isEqualToString:@"ALI56_custm_odvalue_change"]
                || [msg.type isEqualToString:@"ALI56_custm_order_change"]
                || [msg.type isEqualToString:@"ALI56_corp_complaint"]) 
            {
                if ( operationParam == nil || operationParam.logisticsId == nil ) {
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"运单信息暂时无法查询！"] show];
                    break;
                }
                
                AMLogiticsQueryResultViewController *result = [[[AMLogiticsQueryResultViewController alloc] initWithNibName:@"AMLogiticsQueryResultViewController" bundle:nil] autorelease];
                
                result.logisticsID = operationParam.logisticsId;
                result.parentTitle = @"消息中心";
                [self.navigationController pushViewController:result animated:YES];
                
                break;
            }
            
            // 我的运单，未受理运单提醒，跳转到我的运单
            if ([msg.type isEqualToString:@"ALI56_corp_unaccept"])
            {
                [AMLogUtils appendLog: APP_CENTER_ONE]; 
                AMLogiticsViewController *viewCtr = [[AMLogiticsViewController alloc] initWithNibName:@"AMLogiticsViewController_iPhone" bundle:nil];    
                viewCtr.parentTitle = @"消息中心";
                [self.navigationController pushViewController:viewCtr animated:YES];
                
                break;
            }

            // 内嵌WAP跳转 
            if ([msg.type isEqualToString:@"to_wap"]) 
            {
                if ( operationParam == nil || operationParam.wap_url == nil ) {
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"你访问的页面无法打开！"] show];
                    break;
                }
                
                AMBannerContentDetailViewController *detail = [[[AMBannerContentDetailViewController alloc] initWithNibName:@"AMBannerContentDetailViewController" bundle:nil] autorelease];
                detail.url = operationParam.wap_url;
                detail.navigationTitle = msg.title;
                detail.parentTitle = @"消息中心";
                detail.showToolBar=NO;
                [self.navigationController pushViewController:detail animated:YES];
                
                break;
            }

            // 资讯详情跳转
            if ([msg.type isEqualToString:@"to_news_detail"]) 
            {
                if ( operationParam == nil || operationParam.newsId == nil ) {
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"该资讯信息不存在！"] show];
                    break;
                }
                
                AMNewsDetailViewController *Controller = [[[AMNewsDetailViewController alloc] initWithNibName:@"AMNewsDetailViewController" bundle:nil] autorelease];
                
                NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
                [f setNumberStyle:NSNumberFormatterDecimalStyle];
                
                Controller.categoryId = [f numberFromString:operationParam.newsId];
                Controller.navigationTitle = msg.title;   
                Controller.parentTitle = @"消息中心";
                [self.navigationController pushViewController:Controller animated:YES];
                [f release];
                
                break;
            }

            // 新品专场，直接跳转到一级类目页
            if ([msg.type isEqualToString:@"to_new_operation_offer_category"])
            {
                AMNewProductsCategoryViewController *newProductsCategoryViewController = [[[AMNewProductsCategoryViewController alloc] initWithNibName:@"AMNewProductsCategoryViewController" bundle:nil] autorelease];
                newProductsCategoryViewController.parentTitle = @"消息中心";
                newProductsCategoryViewController.hidesBottomBarWhenPushed=YES;
                [self.navigationController pushViewController:newProductsCategoryViewController animated:YES]; 
                
                break;
            }
            
            // 交易排行，直接跳转到类目选择页
            if ([msg.type isEqualToString:@"to_rank_list"])
            {
                AMHotRankViewController *hotRankViewController = [[[AMHotRankViewController alloc] initWithNibName:@"AMHotRankViewController" bundle:nil] autorelease];
                hotRankViewController.parentTitle = @"消息中心";
                hotRankViewController.hidesBottomBarWhenPushed=YES;
                [self.navigationController pushViewController:hotRankViewController animated:YES]; 
                
                break;
            }
            
            // 首页，直接跳转到我们APP首页
            if ([msg.type isEqualToString:@"to_home"]) 
            {
                [self.navigationController popViewControllerAnimated:YES];
                
                break;
            }
            
            // 价格行情，直接跳转到价格行情收藏
            if ([msg.type isEqualToString:@"Price_change_detail"]) 
            {
                AMPriceItem *priceItem = [AMMappingUtil performMappingWithMapping:[AMPriceItem sharedObjectMapping] forJsonString:msg.jsonData];

                AMPriceGraphViewController *priceGraphViewController = [[AMPriceGraphViewController alloc] initWithNibName:@"AMPriceGraphViewController" bundle:nil];
                NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
                [f setNumberStyle:NSNumberFormatterDecimalStyle];
                
                priceGraphViewController.themeRequstId = [f numberFromString:priceItem.themeId];
                priceGraphViewController.sourceFomeRequstId = [f numberFromString:priceItem.sourceFromId];
                priceGraphViewController.areaRequstId = [f numberFromString:priceItem.areaId];
//                priceGraphViewController.sourceAddressName = [operationParam.attributes objectForKey:@"原产地"];
                priceGraphViewController.isPriceFavorited = YES;
                priceGraphViewController.navigateTitleName = @"消息中心";
                [self.navigationController pushViewController:priceGraphViewController animated:YES];
                break;
            }
            if([msg.type isEqualToString:@"Price_change_notify"]){
                [self.navigationController popViewControllerAnimated:YES];
                //1 先发送广播，将click item置为price
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_MESSAGE_FORWARD_FAV_PRICE object:self];
                //2 跳转
                
                [AMLogUtils appendLog: APP_CENTER_TWO]; 
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FAV object:self];
                break;
            }
            
            // 直接跳转到offer搜索界面
            if ([msg.type isEqualToString:@"to_search_offer"]) 
            {
                // 带参数keyword： operationParam.keyword
                AMOfferListViewController *Controller = [[[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil] autorelease];
                Controller.keyWords = operationParam.keyword;
                Controller.parentTitle = @"消息中心";
                Controller.hidesBottomBarWhenPushed=YES;
                [self.navigationController pushViewController:Controller animated:YES];
                break;
            }
            
            // 精准营销
            if ([msg.type isEqualToString:@"pm_insite_notify_msg"] || [msg.type isEqualToString:@"pm_webim_msg_to_mobile"]) {
                AMCustomerAndPrecisionHomeViewController *viewCtr  = [[[AMCustomerAndPrecisionHomeViewController alloc] initWithNibName:@"AMCustomerAndPrecisionHomeViewController" bundle:nil]autorelease];
                viewCtr.businessType = @"precision";
                viewCtr.parentTitle = @"消息中心";
                [self.navigationController pushViewController:viewCtr animated:YES];
                break;
            }
            
            // 询盘管理
            if ([msg.type isEqualToString:@"eq_newEnquiry"]) {
                AMCustomerAndPrecisionHomeViewController *viewCtr  = [[[AMCustomerAndPrecisionHomeViewController alloc] initWithNibName:@"AMCustomerAndPrecisionHomeViewController" bundle:nil]autorelease];
                viewCtr.businessType = @"customer";
                viewCtr.parentTitle = @"消息中心";
                [self.navigationController pushViewController:viewCtr animated:YES];
                break;
            }
            
            // 询盘管理-推荐客户
            if ([msg.type isEqualToString:@"eq_newBuyerLeads"]) {
                AMCustomerAndPrecisionHomeViewController *viewCtr  = [[[AMCustomerAndPrecisionHomeViewController alloc] initWithNibName:@"AMCustomerAndPrecisionHomeViewController" bundle:nil]autorelease];
                viewCtr.businessType = @"leads";
                viewCtr.parentTitle = @"消息中心";
                [self.navigationController pushViewController:viewCtr animated:YES];
                break;
            }
            //跳转热门资讯列表
            if ([msg.type isEqualToString:@"to_news_hot_list"])
            {
                AMNewsViewController *newsListController  = [[[AMNewsViewController alloc] initWithNibName:@"AMNewsViewController" bundle:nil]autorelease];
                newsListController.parentTitle = @"消息中心";
                [self.navigationController pushViewController:newsListController animated:YES];
                
                break;
            }
            //画报home
            if ([msg.type isEqualToString:@"to_image_magazine_home"])
            {
                ImageMagazineCategoryViewController *magazineHomeController  = [[[ImageMagazineCategoryViewController alloc] initWithNibName:@"ImageMagazineCategoryViewController" bundle:nil]autorelease];
                magazineHomeController.parentTitle = @"消息中心";
                [self.navigationController pushViewController:magazineHomeController animated:YES];
                
                break;
            }
            //画报list
            if ([msg.type isEqualToString:@"to_image_magazine_list"])
            {
                ImageMagazineListViewController *magazineListController  = [[[ImageMagazineListViewController alloc]initWithId:operationParam.categoryId title:operationParam.categorydisplayName]autorelease];
                magazineListController.parentTitle = @"消息中心";
                [self.navigationController pushViewController:magazineListController animated:YES];
                
                break;
            }
            //画报detail
            if ([msg.type isEqualToString:@"to_image_magazine_detail"])
            {
                ImageMagazineDetailViewController *magazineDetailController  = [[[ImageMagazineDetailViewController alloc]initWithNewsId:operationParam.pictureNewsId preTitle:@"消息中心"]autorelease];
                [self.navigationController pushViewController:magazineDetailController animated:YES];
                
                break;
            }
            if ([msg.type isEqualToString:@"favorite_offer_price_change"]) 
            {
//                NSString * testString = @"{\"offerId\":\"936354895\",\"favoriteId\":\"74361439\",\"newPrice\":5900.0,\"oldPrice\":5800,\"newPriceDate\":1347448138107}";
                AMFavoriteOfferPriceChangeMessage *favoriteOfferPriceChangeMessage = [AMMappingUtil performMappingWithMapping:[AMFavoriteOfferPriceChangeMessage sharedObjectMapping] forJsonString:msg.jsonData];
                NSString *strOfferId=favoriteOfferPriceChangeMessage.offerId;
                NSString *strOfferName=@"";
                //现阶段针对老的数据中对不规范的json进行解析不了的问题进行解决 只是暂时的解决方案。
                if (nil==strOfferId) {
                    NSArray *tempjsonArray = [msg.jsonData componentsSeparatedByString:@","];
//                    NSArray *tempjsonArray = [@"{offerId:1175150541}" componentsSeparatedByString:@","];
                    for (NSString * dicJson in tempjsonArray) {
                        if ([dicJson rangeOfString:@"offerId"].length!=0) {
                            NSArray* dicJsonArray = [dicJson componentsSeparatedByString:@":"];
                            NSString * tempOfferId = [dicJsonArray objectAtIndex:1];
                            
                            if ([tempjsonArray count]>1) {
                                if ([[tempOfferId substringToIndex:1] isEqualToString:@"'"]||[[tempOfferId substringToIndex:1] isEqualToString:@"\""]) {
                                    strOfferId = [[tempOfferId substringToIndex:tempOfferId.length-1] substringFromIndex:1];
                                }else {
                                    strOfferId = tempOfferId;
                                }
                            }else {
                                if ([[tempOfferId substringToIndex:1] isEqualToString:@"'"]||[[tempOfferId substringToIndex:1] isEqualToString:@"\""]) {
                                    strOfferId = [[tempOfferId substringToIndex:tempOfferId.length-2] substringFromIndex:1];
                                }else {
                                    strOfferId = [tempOfferId substringToIndex:tempOfferId.length-1];
                                } 
                            }
                            

                            break;
                        }
                    }
                }
                AMOfferTabViewController * controller = [[[AMOfferTabViewController alloc] initWithOfferId:strOfferId offerName:strOfferName preViewName:@"AMFavoritesViewController"] autorelease];
                controller.hidesBottomBarWhenPushed=YES;
                [self.navigationController pushViewController:controller animated:YES];
                break;
            }
            if ([msg.type isEqualToString:@"alibaba_close_trade"]||[msg.type isEqualToString:@"buyer_close_trade"]||[msg.type isEqualToString:@"buyer_confirm_order"]||[msg.type isEqualToString:@"buyer_confirm_receive_goods"]||[msg.type isEqualToString:@"buyer_make_order"]||[msg.type isEqualToString:@"buyer_pay_order"]||[msg.type isEqualToString:@"seller_announce_send_goods"]||[msg.type isEqualToString:@"seller_close_trade"]||[msg.type isEqualToString:@"seller_confirm_order"]||[msg.type isEqualToString:@"seller_extend_receive_goods"]||[msg.type isEqualToString:@"seller_make_order"]||[msg.type isEqualToString:@"seller_modify_order_price"]) {
                AMOrderMessage *orderMessage = [AMMappingUtil performMappingWithMapping:[AMOrderMessage sharedObjectMapping] forJsonString:msg.jsonData];
                NSString *memberId=[LoginToken getLoginUserName];
                AMOrderDetailViewController *viewController = [[[AMOrderDetailViewController alloc] init] autorelease];
                viewController.orderId = orderMessage.orderId;
                viewController.memberId = memberId;
                [self.navigationController pushViewController:viewController animated:YES]; 
                break;
            }
            // 暂时不支持跳转的，一律直接提示已读即可
            if ( showMessageReadHint ) {
                [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"标记为已读"] show];
            }
            
            break;
        }
            
        case 2: // Message Type table view
        {
            self.mMsgFilter = (NSString *)((KeyValueObject *)[self.mMsgGroupDict objectAtIndex:row]).key;
            [self.mMsgTypeTableView deselectRowAtIndexPath:indexPath animated:NO];
            [self showMessageTypeList:NO];
            self.mMessageTypeLabel.text = self.mMsgFilter;
            
            [self.mTableView reloadData];
            break;
        }
            
        default:
            break;
    }
}

-(AliRightBarButtonItem*)buttonsItem
{
    if (!_buttonsItem) {
        _buttonsItem = [AliRightBarButtonItem createView: [NSArray arrayWithObject:@"刷新"]];
        _buttonsItem.delegate = self;
    }
    return _buttonsItem;
}


-(void)AliRightBarButtonItem:(NSInteger)selectedButton{
    [self showMessageTypeList:NO];
    [self.mTableView.pullToRefreshView triggerRefresh];
    [self.mLoadingView endLoadingView];
}
@end

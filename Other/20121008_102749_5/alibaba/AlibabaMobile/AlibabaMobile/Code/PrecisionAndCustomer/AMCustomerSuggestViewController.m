//
//  AMFavoritesViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "AMCustomerSuggestViewController.h"
#import "AMCompanyTabViewController.h"
#import "AMIMViewController.h"
#import "LoginToken.h"
#import "AliTabViewController.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliImageControlFactory.h"
#import "UIHelp.h"
#import "AMMoreLoadingCell.h"
#import "AliTableViewCellAllVisitor.h"
#import "AMCustomerSuggestListMainModel.h"
#import "AliTableViewCellCompanyDetail.h"
#import "AliTableViewCellPriceDetail.h"
#import "NSAttributedString+HTML.h"
#import "ConstDef.h"
#import "AMCUDResult.h"
#import "AMCustomerSuggestListResult.h"
#import "AMFavoriteOffer.h"
#import "AMPriceResult.h"
#import "AMMoney.h"
#import "AliToastView.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
#import "NSAttributedString+HTML.h"
#import "AMRequestDelegate.h"
#import "AliTableViewCellSuggest.h"
#import "AMCustomerSuggestStatRequest.h"
#import "AMCustomerSuggestStatResult.h"
#import "AMCustomerMyCustomerRequest.h"
#import "AMCustomerMyCustomerResult.h"
#import "AMCustomerMyCustomerListModel.h"
#import "AMCustomerInfoViewController.h"
#import "AliTableViewCellMyCustomer.h"
#import "NoticationItem.h"
#import "AMCustomerSuggestAddResult.h"
#import "SVPullToRefresh.h"
#import "AMIMTalkViewController.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
#define DEFAULT_PAGE_SIZE  9

#define HADE_SUBVIEW_TAG_EMPTY 11
#define HADE_SUBVIEW_TAG_ONE  22
#define HADE_SUBVIEW_TAG_TWO  33

NSString * const STATUS_CAN_ADD = @"1";
NSString * const STATUS_IS_MYCUSTOMER = @"2";
NSString * const STATUS_INVALIDATION_CUSTOMER = @"3";

NSString * const ADD_ERROR_CODE_USER_NOT_EXIST = @"USER_NOT_EXIST"; //"被添加用户不存在" ;
NSString * const ADD_ERROR_CODE_FREE_UPPER_LIMIT = @"FREE_UPPER_LIMIT"; //本月可添加的客户数已达到上限，请线上购买询盘管理付费版" ;
NSString * const ADD_ERROR_CODE_LEADS_USED = @"LEADS_USED"; // 已拥有该leads
NSString * const ADD_ERROR_CODE_LEADS_BUYER_EXIST = @"LEADS_BUYER_EXIST"; // "买家已存在"
NSString * const ADD_ERROR_CODE_LEADS_ENQUIRIES_FAILURE = @"LEADS_ENQUIRIES_FAILURE"; //创建询盘失败

@interface AMCustomerSuggestViewController()
@property (nonatomic,copy)NSString *loginUserName;
//当下拉网络请求失败的时候才使用 记录上一次下拉的页数。
@property (nonatomic,assign) NSInteger tempCurrentPage; 
@end

@implementation AMCustomerSuggestViewController

@synthesize suggestTableView;

@synthesize suggestListObjects = _suggestListObjects;
@synthesize suggestStatObjects = _suggestStatObjects;
@synthesize suggestListRequest = _suggestListRequest;
@synthesize suggestStatRequest = _suggestStatRequest;
@synthesize objMan;
@synthesize mLoadingView = _mLoadingView;
@synthesize loginUserName=_loginUserName;
@synthesize mNavigationController = _mNavigationController;
@synthesize headerView = _headerView;
@synthesize addRequest = _addRequest;
@synthesize isFirstLoadView = _isFirstLoadView;

@synthesize isFirstLoad;
@synthesize isRefresh;
@synthesize tempCurrentPage = _tempCurrentPage;

-(UIView*)mLoadingView {
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
//        _mLoadingView.delegate = self;
    }
    return _mLoadingView;
}

//- (void) showLoadingView {
//    [self.mLoadingView setHidden:NO];
//    [self.mLoadingView.loadingView setHidden:NO];
//    [self.mLoadingView.noDataView setHidden:YES];
//}
//
//-(void) endLoadingView {
//    [self.mLoadingView setHidden:YES];
//}

- (void) showNoDataMessage {
    [self.mLoadingView setHidden:NO];
    [self.mLoadingView.loadingView setHidden:YES];
    [self.mLoadingView.noDataView setHidden:NO];
}

- (id)initWithNavigation:(UINavigationController *)navigation {
    self = [super init];
    if (self) {
        self.mNavigationController = navigation;
        self.isFirstLoadView = YES;
    }
    return self;
}

-(UIView*)headerView {
    
    if (!_headerView) {
//        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 50.0)];
         _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 60.0)];
        _headerView.backgroundColor = RGB(0xff, 0xfd, 0xe9);
        mUpdateHeader = YES;
    }
    
    if (mUpdateHeader) {
        mUpdateHeader = NO;

        UILabel * emptyLabel = (UILabel *)[_headerView viewWithTag:HADE_SUBVIEW_TAG_EMPTY];
    
        if (emptyLabel != nil) {
            [emptyLabel removeFromSuperview];
        }
    
        if(self.suggestStatObjects == nil){

            emptyLabel = [[UILabel alloc]initWithFrame:CGRectMake(10.0, 10.0, 310.0, 20.0)];

            emptyLabel.backgroundColor = [UIColor clearColor];
            emptyLabel.text = [NSString stringWithFormat:@"询盘数据正在统计中......"];
            emptyLabel.textColor = RGB(0x66,0x66,0x66);
            emptyLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
            emptyLabel.font = [UIFont systemFontOfSize:12.0];
            emptyLabel.textAlignment = UITextAlignmentCenter;
            emptyLabel.tag = HADE_SUBVIEW_TAG_EMPTY;
            [_headerView addSubview:emptyLabel];
            [emptyLabel release];

        } else {
            if(isFirstLoadHeader){
                [self setLatentCustomerProperty:[NSString stringWithFormat:@"%d",[(self.suggestStatObjects.potentialEnquiryCount) intValue ]]];
                [self setOverdueProperty:[NSString stringWithFormat:@"%d",[(self.suggestStatObjects.unPotentialEnquiryCount) intValue]]] ;
                isFirstLoadHeader = NO;
            }
        }
    }
    return _headerView;  
}

- (void) setLatentCustomerProperty:(NSString *)countValue{
    

    CGSize labelSizePre = [@"最近7天您已经成功添加潜在询盘" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(50, 10, labelSizePre.width, 20)];
    preLabel.font = [UIFont systemFontOfSize:12.0f];
    preLabel.numberOfLines = 1;
    preLabel.lineBreakMode = UILineBreakModeWordWrap;
    preLabel.backgroundColor = [UIColor clearColor];
    preLabel.textColor = RGB(0x66,0x66,0x66);
    preLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    preLabel.text = @"最近7天您已经成功添加潜在询盘";
    [_headerView addSubview:preLabel];
    
    
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    UILabel *midLabel = [[UILabel alloc] initWithFrame:CGRectMake(50 +preLabel.frame.size.width, 10, labelSize.width, 20)];
    midLabel.font = [UIFont systemFontOfSize:12.0f];
    midLabel.numberOfLines = 1;
    midLabel.lineBreakMode = UILineBreakModeWordWrap;
    midLabel.backgroundColor = [UIColor clearColor];
    midLabel.textColor = RGB(0xff,0x73,0x00);
    midLabel.highlightedTextColor = RGB(0xff,0x73,0x00);
    midLabel.text = countValue;
    [_headerView addSubview:midLabel];
    
    
    
    CGSize labelSizeEnd = [@"个" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    UILabel *endLabel = [[UILabel alloc] initWithFrame:CGRectMake(50+preLabel.frame.size.width+midLabel.frame.size.width, 10, labelSizeEnd.width, 20)];
    endLabel.font = [UIFont systemFontOfSize:12.0f];
    endLabel.numberOfLines = 1;
    endLabel.lineBreakMode = UILineBreakModeWordWrap;
    endLabel.backgroundColor = [UIColor clearColor];
    endLabel.textColor = RGB(0x66,0x66,0x66);
    endLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    endLabel.text = @"个";
    [_headerView addSubview:endLabel];
    
    [preLabel release];
    [midLabel release];
    [endLabel release];
    
    
}

- (void) setOverdueProperty:(NSString *)countValue{
    
    CGSize labelSizePre = [@"有" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(45, 30, labelSizePre.width, 20)];
    preLabel.font = [UIFont systemFontOfSize:12.0f];
    preLabel.numberOfLines = 1;
    preLabel.lineBreakMode = UILineBreakModeWordWrap;
    preLabel.backgroundColor = [UIColor clearColor];
    preLabel.textColor = RGB(0x66,0x66,0x66);
    preLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    preLabel.text = @"有";
    [_headerView addSubview:preLabel];
    
    
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    UILabel *midLabel = [[UILabel alloc] initWithFrame:CGRectMake(45 +preLabel.frame.size.width, 30, labelSize.width, 20)];
    midLabel.font = [UIFont systemFontOfSize:12.0f];
    midLabel.numberOfLines = 1;
    midLabel.lineBreakMode = UILineBreakModeWordWrap;
    midLabel.backgroundColor = [UIColor clearColor];
    midLabel.textColor = RGB(0xff,0x73,0x00);
    midLabel.highlightedTextColor = RGB(0xff,0x73,0x00);
    midLabel.text = countValue;
    [_headerView addSubview:midLabel];
    
    
    
    CGSize labelSizeEnd = [@"个被同行抢走或过期，下次勤奋点哦!" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    UILabel *endLabel = [[UILabel alloc] initWithFrame:CGRectMake(45+preLabel.frame.size.width+midLabel.frame.size.width, 30, labelSizeEnd.width, 20)];
    endLabel.font = [UIFont systemFontOfSize:12.0f];
    endLabel.numberOfLines = 1;
    endLabel.lineBreakMode = UILineBreakModeWordWrap;
    endLabel.backgroundColor = [UIColor clearColor];
    endLabel.textColor = RGB(0x66,0x66,0x66);
    endLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    endLabel.text = @"个被同行抢走或过期，下次勤奋点哦!";
    [_headerView addSubview:endLabel];
    
    [preLabel release];
    [midLabel release];
    [endLabel release];
    
}


- (void)didReceiveMemoryWarning {
//    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

- (void)loadObjectsFromRemoteSuggestList {
    
//    if(isPullViewLoad){
//        isPullViewLoad = NO;
//    }else{
//        if(self.mLoadingView.loadingView.hidden==YES){
//            self.mLoadingView.loadingView.hidden = NO;
//        }
        if (currentSuggestPage>1) {
            AMMoreLoadingView * more = [[AMMoreLoadingView alloc ]init ];
            self.suggestTableView.tableFooterView = more;
            [more release];
            
            
        }else {
            self.suggestTableView.tableFooterView = nil;
            [self.mLoadingView showLoadingView];
        }        
        
//    }
    
    isLoading = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* customerSuggestListMapping = [AMCustomerSuggestListResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: customerSuggestListMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CUSTOMER_SUGGEST_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCustomerSuggestListResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.suggestListRequest;
    }];
}

- (void)loadObjectsFromRemoteSuggestStat {
    isLoading = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* customerSuggestStatMapping = [AMCustomerSuggestStatResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: customerSuggestStatMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CUSTOMER_SUGGEST_STAT usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCustomerSuggestStatResult class]];
            loader.objectMapping = [AMCustomerSuggestStatResult sharedObjectMapping];
            
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.suggestStatRequest;
    }];
}

- (void)loadObjectsFromRemoteAdd {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* caddMapping = [AMCustomerSuggestAddResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: caddMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CUSTOMER_SUGGEST_ADD usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCustomerSuggestAddResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.addRequest;
    }];
}

#pragma mark RKObjectLoaderDelegate methods

//- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
//    NSLog(@"Loaded payload: %@", [response bodyAsString]);
//}
//
//extern NSInteger gLastDisplayErrorTimeInterval;
//- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
//    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
//    
//    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
//    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
//        
//        gLastDisplayErrorTimeInterval = currentTime;
//    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
//        
//        gLastDisplayErrorTimeInterval = currentTime;
//    }
//}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    if (objectLoader == nil || objectLoader.params == nil || objects == nil || !([objectLoader.params respondsToSelector:@selector(transactionType)])) {
        return ;
    }
    
    NSLog(@"Loaded objects: %@", objects);  
    
    [self.mLoadingView endLoadingView];
    
    NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
    if (transactionType == AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_STATE) {
        if(self.suggestStatObjects == nil){
            self.suggestStatObjects = [[AMCustomerSuggestStatResult alloc]init];
        }
        self.suggestStatObjects = (AMCustomerSuggestStatResult*)[objects objectAtIndex:0];
        mUpdateHeader = YES;
        NSLog(@"suggestStatObjects");
        isLoading = NO;
        
        if(isFirstStateObjectLoad){
            [self.view addSubview:self.headerView];
            isFirstStateObjectLoad = NO;
        }
        self.suggestTableView.tableHeaderView=self.headerView;
        
        
    }else if(transactionType == AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_LIST){
        
        if (self.isFirstLoad) {
            self.isFirstLoad = NO;
            [self.mLoadingView endLoadingView];
        }
        
        AMCustomerSuggestListResult *result = (AMCustomerSuggestListResult*)[objects objectAtIndex:0];
        
        if (self.suggestListObjects==nil) {
            self.suggestListObjects = [[NSMutableArray alloc]init];
            
        }
        
        if ([self.suggestListObjects count]==0) {
            [self.suggestTableView reloadData];
        }
        
        suggestTotalCount =[result.totalCount intValue];
        if(result){
            if (isRefresh) {
                [self.suggestListObjects removeAllObjects];
            }
            [self.suggestListObjects addObjectsFromArray:result.resultList];
        }else{
            [self showNoDataMessage];
        }
        
        [suggestTableView reloadData];
        [suggestTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
        if (suggestTotalCount<=0) {
            [self showNoDataMessage];
        }
        else {
//            [self endLoadingView];
            [self.mLoadingView endLoadingView];
        }
        isLoading = NO;
        if (currentSuggestPage*[self.suggestListRequest.pageSize intValue]>suggestTotalCount) {
            self.suggestTableView.tableFooterView = nil;
        }
        self.isRefresh = NO;
    } else if(transactionType == AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_ADD){
        AMCustomerSuggestAddResult *result = (AMCustomerSuggestAddResult*)[objects objectAtIndex:0];
        if (result == nil || result.resultCode == nil || result.success == nil) {
            return ;
        }
        
        if (![[result success] boolValue]) {
            NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
            if ([result.resultCode isEqualToString:ADD_ERROR_CODE_USER_NOT_EXIST]) {
                errorMsg = NSLocalizedString(@"ADD_ERROR_CODE_USER_NOT_EXIST", nil);
            } else if ([result.resultCode isEqualToString:ADD_ERROR_CODE_FREE_UPPER_LIMIT]){
                errorMsg = NSLocalizedString(@"ADD_ERROR_CODE_FREE_UPPER_LIMIT", nil);                
            } else if ([result.resultCode isEqualToString:ADD_ERROR_CODE_LEADS_USED]){
                errorMsg = NSLocalizedString(@"ADD_ERROR_CODE_LEADS_USED", nil);   
            } else if ([result.resultCode isEqualToString:ADD_ERROR_CODE_LEADS_BUYER_EXIST]){
                errorMsg = NSLocalizedString(@"ADD_ERROR_CODE_LEADS_BUYER_EXIST", nil);
            } else if ([result.resultCode isEqualToString:ADD_ERROR_CODE_LEADS_ENQUIRIES_FAILURE]){
                errorMsg = NSLocalizedString(@"ADD_ERROR_CODE_LEADS_ENQUIRIES_FAILURE", nil);
            }
            [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show];
            return ;
        }
        
        mCurCostomer.status = STATUS_IS_MYCUSTOMER;
        [suggestTableView reloadData];
        
        if (mIsUserTalk) {
            if([LoginToken isWangWangLogined]) {
                [self enterTalk];
            } else {
                isTalkAfterWwLogin = YES;
                [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
                [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
                
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
            }
        }
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	[self.mLoadingView endLoadingView];

    NSLog(@"loading errorcode %d", [error code]);
    
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        
//        if (isFirstLoad) {
//            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
//        }else {
//            
//            
//            if (isRefresh) {
//                [suggestTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];//停止下拉刷新;
//            }else {
//                if([self.suggestListObjects count]){
//                    AMErrorMessageView * errorView = [[AMErrorMessageView alloc]init];
//                    self.suggestTableView.tableFooterView = errorView;
//                    [errorView release];
//                    currentSuggestPage--;
//                }
//            }
//        }
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        if (transactionType == AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_LIST) {
            if (isRefresh) {
                [suggestTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
            }
            if ([self.suggestListObjects count]) {
                AMErrorMessageView * errorView = [[AMErrorMessageView alloc]init];
                self.suggestTableView.tableFooterView = errorView;
                [errorView release];
                if (!isRefresh) {
                    currentSuggestPage--;
                }else {
                    currentSuggestPage = self.tempCurrentPage;
                }

            }else {
                [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
            }
            isRefresh = NO;
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }

    }
    isLoading = NO;


}

- (void) onWwLoginSucc {
    if (isTalkAfterWwLogin) {
        [self enterTalk];
        isTalkAfterWwLogin = NO;
    }
}

- (void) enterTalk {
    if (mCurCostomer) {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:mCurCostomer.customerMemberId : mCurCostomer.name];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.mNavigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

#pragma mark - View lifecycle

-(void)loadRequest {
    //检查accesstoken是否需要更新
//    [LoginToken checkAccessTokenExpired];
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    
    //请求询盘统计
    if(self.suggestStatRequest==nil){
        self.suggestStatRequest = [[AMCustomerSuggestStatRequest alloc] init];
    }
    self.suggestStatRequest.transactionType = AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_STATE;
    self.suggestStatRequest.requestURL = OCEAN_API_URL_CUSTOMER_SUGGEST_STAT;
    [self loadObjectsFromRemoteSuggestStat];
    
    self.loginUserName = loginUserName;
    if ([loginUserName length] > 3) {
//        [self showLoadingView];
//        [self.mLoadingView showLoadingView];
        if(self.suggestListRequest ==nil){
            self.suggestListRequest = [[AMCustomerSuggestListRequest alloc] init];
        }
        self.suggestListRequest.requestURL = OCEAN_API_URL_CUSTOMER_SUGGEST_LIST;
        self.suggestListRequest.transactionType = AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_LIST;
        self.suggestListRequest.pageIndex = [NSNumber numberWithInt: currentSuggestPage];
        [self loadObjectsFromRemoteSuggestList];
        
    }
}

-(void) addToMyCustomer:(NSString *) customerMemberId: (NSString *)leadsId{
//    [LoginToken checkAccessTokenExpired];
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if ([loginUserName length] > 3) {
        if (nil == self.addRequest) {
            self.addRequest = [[AMCustomerSuggestAddRequest alloc] init]; 
        }
        self.addRequest.requestURL = OCEAN_API_URL_CUSTOMER_SUGGEST_ADD;
        self.addRequest.customerMemberId = customerMemberId;
        self.addRequest.leadsId = leadsId;
        self.addRequest.transactionType = AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_ADD;
        [self loadObjectsFromRemoteAdd];
    }
}

-(void)objManInit {
    objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcachecustomer/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;

    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 10.0) {
        if (!isLoading) {
            if(currentSuggestPage* DEFAULT_PAGE_SIZE < suggestTotalCount) {
                currentSuggestPage++;
                [self loadRequest]; 
            }
        }
    }
}

- (void) onLoginSucc {
    
    [self clearData];
    isFirstLoadHeader = YES;

    //清掉headerview，防止重载
//    if (isLastCustomerSuggestStatLoaded) {
//        isLastCustomerSuggestStatLoaded = NO;
//        for (UIView*view in self.headerView.subviews )  {
//            [view removeFromSuperview];
//        }            
//    }
    if(_headerView){
        [_headerView removeFromSuperview];
        self.headerView = nil;
    }
    [self clearData];
    [self loadRequest];
    //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
    if(self.mLoadingView.loadingView.hidden==YES){
        self.mLoadingView.loadingView.hidden = NO;
    }
//    [self showLoadingView];
    
    [self.mLoadingView showLoadingView];
    
}

- (void) clearData {
    currentSuggestPage = 1;
    suggestTotalCount = 0;
    if (self.suggestListObjects != nil) {
        [self.suggestListObjects removeAllObjects];
        self.suggestListObjects = nil;
        [suggestTableView reloadData];
//        suggestTableView.tableFooterView =nil;
    }
//    [suggestTableView reloadData];
}

#pragma mark - View lifecycle

- (void)viewDidLoad { 
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    [self objManInit];
    
    isTalkAfterWwLogin = NO;
    
    currentSuggestPage = 1;
    suggestTotalCount = 0;
    
    isFirstLoadHeader = YES;
    isRefresh = NO;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onLoginSucc) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    
    [self.suggestTableView addPullToRefreshWithActionHandler:^{
        NSLog(@"refresh dataSource");
        suggestTableView.pullToRefreshView.lastUpdatedDate = [NSDate date]; 
        //        [suggestTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil afterDelay:2];
        
    
//        [self clearData];
        isFirstStateObjectLoad = YES;
        isFirstLoadHeader = YES;
        isRefresh = YES;
//        isFirstLoad = YES;
        
        if(_headerView){
            [_headerView removeFromSuperview];
            self.headerView = nil;
        }
        self.suggestTableView.tableFooterView = nil;
//        [self clearData];
        self.tempCurrentPage = currentSuggestPage;
        currentSuggestPage = 1;
//        suggestTotalCount = 0;
        
        [self loadRequest];
        //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
        if(self.mLoadingView.loadingView.hidden==NO){
            self.mLoadingView.loadingView.hidden = YES;
        }
        //        [self showLoadingView];
//        isPullViewLoad = YES;
        isFirstStateObjectLoad = YES;
//        self.suggestTableView.tableHeaderView=self.headerView;

        
    }];
    
    self.isFirstLoad = YES;
}

- (void)viewDidUnload {
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    self.suggestListRequest = nil;
    self.suggestStatRequest = nil;
    self.suggestTableView = nil;
    self.suggestStatObjects = nil;
    self.addRequest = nil;
    self.objMan = nil;
    if(_headerView){
        [_headerView removeFromSuperview];
        self.headerView = nil;
    }
    if (self.suggestListObjects != nil) {
        [self.suggestListObjects removeAllObjects];
        self.suggestListObjects = nil;
    }
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self loadRequestForFirstTime];

//    self.suggestTableView.tableHeaderView=self.headerView;
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

//这个方法告诉表格第section个分组有多少行
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return [self.suggestListObjects count];
}

//设置cell高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath { 
    return [AliTableViewCellSuggest cellHeight];  
}

//- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
//    return 60.0;
//}
//
//- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
//    isLastCustomerSuggestStatLoaded = YES;
//    return self.headerView;
//}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    NSUInteger row = [indexPath row];
    
    
    AliTableViewCellSuggest *cell = (AliTableViewCellSuggest *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellSuggest cellIdentifer]];
    
    if (cell == nil) {
        cell = [AliTableViewCellSuggest createCell];
    }
    
    if (row >= [self.suggestListObjects count]) {
        return cell;
    }
    
    tableView.backgroundColor = [UIColor clearColor];
    UIImage *img=[UIImage imageNamed:@"list_bg.png"];
    UIImageView *imgView=[[UIImageView alloc]initWithImage:img];
    [imgView setFrame:CGRectMake(10, 10, 300, 200)];
    cell.backgroundView = imgView;
    [imgView release];

    UIImageView *imgViewBack=[[UIImageView alloc]initWithImage:img];
    [imgViewBack setFrame:CGRectMake(10, 10, 300, 200)];
    cell.selectedBackgroundView = imgViewBack;
    [imgViewBack release];
    
    
    AMCustomerSuggestListMainModel *suggestModel = (AMCustomerSuggestListMainModel*)[self.suggestListObjects objectAtIndex:row ] ;
    cell.name.text = suggestModel.name;
    cell.province.text = suggestModel.province;
    cell.mainBiz.text = suggestModel.mainBiz;
    
    NSString *interestInfoConvert = [NSString stringWithFormat:@"关　注 : %@ 【 %@ 】",suggestModel.interestInfo,suggestModel.visitDate];
    cell.interestInfo.text = interestInfoConvert;
    
    if([suggestModel.intent isEqualToString:@"2"]){
        cell.intent.text = @"意向度 : 中";
    }else{
        cell.intent.text = [NSString stringWithFormat:@"意向度 : %@",suggestModel.intent];
    }
    
    if (suggestModel.status != nil) {
        if ([suggestModel.status isEqualToString:STATUS_CAN_ADD]) {
            cell.overdueDays.text = [NSString stringWithFormat:@"%@",suggestModel.overdueDays];
            [cell.addBtn setHidden:NO];
            [cell.addBtnPre setHidden:NO];
        } else if  ([suggestModel.status isEqualToString:STATUS_IS_MYCUSTOMER]) {
            cell.overdueDays.hidden = YES;
            cell.overdueDaysEnd.text = @"已经是您的客户了";
            [cell.addBtn setHidden:YES];
            [cell.addBtnPre setHidden:YES];
        } else if  ([suggestModel.status isEqualToString:STATUS_INVALIDATION_CUSTOMER]) {
            cell.overdueDays.hidden = YES;
            cell.overdueDaysEnd.text = @"该客户已经被抢走";
            [cell.addBtnPre setHidden:YES];
            [cell.addBtn setHidden:YES];
        }
    }
    
    NSArray *temp = suggestModel.buyItems;
    NSString *buyItemsConvert = [[NSString alloc ]initWithFormat:@"最想买 : "];
    if(temp&&[temp count]>0){
        
        for(int i=0;i<[temp count];i++){
            if(i==0){
                buyItemsConvert = [buyItemsConvert stringByAppendingFormat:@"%@",[temp objectAtIndex:i]];  
            }else{
                buyItemsConvert = [buyItemsConvert stringByAppendingFormat:@",%@",[temp objectAtIndex:i]];  
            }
        }
    }
    cell.buyItems.text = buyItemsConvert;
    //[buyItemsConvert release];
    
    //图片请求相关
    cell.bkImage.layer.masksToBounds = YES;
    cell.bkImage.layer.cornerRadius= 2.0;
    [cell.headImg setImage:nil];
    NSString *headImg = [NSString stringWithFormat:@"%@",suggestModel.headImage.mobileImageURI];
    cell.headImg.url = [NSURL URLWithString:headImg];
    [self.objMan manage:cell.headImg];
    cell.headImg.layer.masksToBounds = YES;
    
    cell.headImg.layer.cornerRadius= 10.0;
//    cell.headImg.frame =CGRectMake(10, 10, 75 , 75);

    cell.talkBtn.param = suggestModel;
    [cell.talkBtn addTarget:self action:@selector(talkAction:) forControlEvents:UIControlEventTouchUpInside];
    
    cell.addBtn.param = suggestModel;
    [cell.addBtn addTarget:self action:@selector(addAction:) forControlEvents:UIControlEventTouchUpInside];

    cell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击
    return cell;
}

- (IBAction)talkAction:(id)sender {
    [AMLogUtils appendLog:CUSTOMERMANAGER_LEADSCUSTOMER_ONE];
    AMCustomerSuggestListMainModel * costomerMode = ((AliParamButton *)sender).param;
    if (costomerMode == nil) {
        return ;
    }
    mIsUserTalk = YES;
    mCurCostomer = costomerMode;
    
    [self addToMyCustomer:mCurCostomer.customerMemberId: mCurCostomer.leadsId];
}

- (IBAction)addAction:(id)sender {
    [AMLogUtils appendLog:CUSTOMERMANAGER_LEADSCUSTOMER_TWO];
    AMCustomerSuggestListMainModel * costomerMode = ((AliParamButton *)sender).param;
    if (costomerMode == nil) {
        return ;
    }
    
    mIsUserTalk = NO;
    mCurCostomer = costomerMode;
    
    [self addToMyCustomer:mCurCostomer.customerMemberId: mCurCostomer.leadsId];
}

//单击行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    [self.suggestTableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [suggestTableView release];
    [_suggestListObjects release];
    [_suggestListRequest release];
    [_suggestStatRequest release];
    [objMan release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [_loginUserName release];
    [_suggestStatObjects release];
    [_addRequest release];
    [mCurCostomer release];
    
    [super dealloc];
}

- (void)OceanClient:(RKOceanClient *)oceanClient didRefreshTokenOutOfDate:(RKResponse *)response{
    [super OceanClient:oceanClient didRefreshTokenOutOfDate:response];
    [self.mLoadingView showNodataMessage];
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"鉴权失败"] show]; 
    
    UIViewController *nextController;
    nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
    nextController.hidesBottomBarWhenPushed=YES;
    
    [self.mNavigationController pushViewController:nextController animated:YES];
}

- (void)OceanClient:(RKOceanClient *)oceanClient didDonotLogin:(RKResponse *)response{
    [super OceanClient:oceanClient didDonotLogin:response];
    [self.mLoadingView showNodataMessage];
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"请您重新登陆"] show]; 
}

-(void)loadRequestForFirstTime
{
    if (self.isFirstLoadView) {
        NSString *name = [LoginToken getLoginUserName];
        if(name!=nil&&[name length]>3){
            [self loadRequest];
            self.isFirstLoadView = NO;
        }
    }
}

-(void)request:(RKRequest *)request didFailLoadWithError:(NSError *)error{
    [super request:request didFailLoadWithError:error];
//    if ([error code] == RKRequestBaseURLOfflineError) {
//        [self.mLoadingView showLoadFailedMessageForRequest:request];
//    }
    
}



//-(void)reloadLoadingData{
//    [self loadRequest];
//}
@end

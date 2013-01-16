//
//  AMFavoritesViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "AMFavoritesViewController.h"
#import "AMOfferTabViewController.h"
#import "AMCompanyTabViewController.h"
#import "AMIMViewController.h"
#import "LoginToken.h"
#import "AliTabViewController.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliImageControlFactory.h"
#import "AMMoreLoadingCell.h"
#import "AliTableViewCellOfferDetail.h"
#import "AliTableViewCellCompanyDetail.h"
#import "AliTableViewCellPriceDetail.h"
#import "NSAttributedString+HTML.h"
#import "ConstDef.h"
#import "AMFavoriteRequest.h"
#import "AMCUDResult.h"
#import "AMOfferFavoriteListResult.h"
#import "AMFavoriteCompany.h"
#import "AMCompanyFavoriteListResult.h"
#import "AMFavoriteOffer.h"
#import "AMPriceResult.h"
#import "AMMoney.h"
#import "AliToastView.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
#import "NSAttributedString+HTML.h"
#import "AMRequestDelegate.h"
#import "AMPriceGraphViewController.h"
#import "ConstDef.h"
#import "LoginTokenHelper.h"
#import "AMErrorMessageView.h"
#import "AMMoreLoadingView.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
#define DEFAULT_PAGE_SIZE  9


@interface AMFavoritesViewController()
@property (nonatomic,copy)NSString *loginUserName;
//初始化时的index 一共就只有0 1 2 代表产品 公司 价格
//@property (nonatomic,assign)NSInteger startIndex;
@property (nonatomic,assign) NSInteger tempCurrentProPage;
@property (nonatomic,assign) NSInteger tempCurrentComPage;

@property (nonatomic,assign) BOOL isRefresh;
@end
@implementation AMFavoritesViewController
@synthesize favorites;
@synthesize controllers;
@synthesize favoritesView;
@synthesize offerTableView;
@synthesize companyTableView;
@synthesize priceTableView;
@synthesize _proObjects;
@synthesize _comObjects;
@synthesize _priObjects;
@synthesize favOfferRequest = _favOfferRequest;
@synthesize favComanyRequest = _favComanyRequest;
@synthesize favPriceRequest = _favPriceRequest;
@synthesize objMan;
@synthesize delFavOfferRequset = _delFavOfferRequset;
@synthesize delFavComanyRequest = _delFavComanyRequest;
@synthesize delFavPriceRequest = _delFavPriceRequest;
@synthesize rowToDel=_rowToDel;

@synthesize loginUserName=_loginUserName;
@synthesize mSegmentedControl = _mSegmentedControl;
@synthesize mLoadingView = _mLoadingView;
//@synthesize startIndex = _startIndex;
@synthesize tempCurrentProPage = _tempCurrentProPage;
@synthesize tempCurrentComPage = _tempCurrentComPage;
@synthesize isRefresh = _isRefresh;
-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib){
            if ([oneObject isKindOfClass:[AliLoadingDataView class]]){
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
                break;
            }
        }

        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
//        _mLoadingView.delegate = self;
    }
    
    return _mLoadingView;
}

-(AMFavoriteRequest*)delFavOfferRequset
{
    if (_delFavOfferRequset==nil) {
        _delFavOfferRequset = [[AMFavoriteRequest alloc] init];
        _delFavOfferRequset.requestURL=OCEAN_API_URL_OFFER_FAV_DEL;
        _delFavOfferRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST_DELETE;
    }
    return _delFavOfferRequset;
}

-(AMFavoriteRequest*)delFavComanyRequest
{
    if (_delFavComanyRequest==nil) {
        _delFavComanyRequest = [[AMFavoriteRequest alloc] init];
        _delFavComanyRequest.requestURL=OCEAN_API_URL_COMPANY_FAV_DEL;
        _delFavComanyRequest.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST_DELETE;
    }
    return _delFavComanyRequest;
}

-(AMFavoriteRequest*)delFavPriceRequest
{
    if (_delFavPriceRequest==nil) {
        _delFavPriceRequest = [[AMFavoriteRequest alloc] init];
        _delFavPriceRequest.requestURL=OCEAN_API_URL_PRICE_FAV_DEL;
        _delFavPriceRequest.transactionType = AMTRANSACTION_TYPE_FAVORITE_PRICE_DELETE;
    }
    return _delFavPriceRequest;
}

-(AMFavoriteRequest*)favOfferRequest{
    if (_favOfferRequest==nil) {
        _favOfferRequest = [[AMFavoriteRequest alloc] init];
        _favOfferRequest.requestURL=OCEAN_API_URL_OFFER_FAV;
        _favOfferRequest.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST;
    }
    return _favOfferRequest;
}
-(AMFavoriteRequest*)favComanyRequest{
    if (_favComanyRequest==nil) {
        _favComanyRequest = [[AMFavoriteRequest alloc] init];
        _favComanyRequest.requestURL=OCEAN_API_URL_COMPANY_FAV;
        _favComanyRequest.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST;
    }
    return _favComanyRequest;
}
-(AMFavoriteRequest*)favPriceRequest{
    if (_favPriceRequest==nil) {
        _favPriceRequest = [[AMFavoriteRequest alloc] init];
        _favPriceRequest.requestURL=OCEAN_API_URL_PRICE_FAV;
        _favPriceRequest.transactionType = AMTRANSACTION_TYPE_FAVORITE_PRICE_LIST;
    }
    return _favPriceRequest;
}



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.navigationItem.title = NSLocalizedString(@"Favorites", @"");
        self.tabBarItem.image = [UIImage imageNamed:@"icon_toolbar_fav"];
        self.tabBarItem.title=NSLocalizedString(@"Favorites", @"");
        //            [self customTabbarArea]; 此时可能view还未能出来，从而有时出现segment未能显示的问题
        selectItem = 0;
        //注册监听，是否是消息中心向价格收藏跳转
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(setSelectItem) name:NOTIFICATION_MESSAGE_FORWARD_FAV_PRICE object:nil];
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

- (void)loadObjectsFromRemoteProduct {
    isLoading = YES;
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
//	RKObjectMapping* favResultMapping = [AMOfferFavoriteListResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: favResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_OFFER_FAV usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) 
        {
            //建议这么写，可以放置provder无限被充大。
            RKObjectMapping* favResultMapping = [AMOfferFavoriteListResult sharedObjectMapping];
            loader.objectMapping = favResultMapping;
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMOfferFavoriteListResult class]];
            
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.favOfferRequest;
    }];
}

- (void)loadObjectsFromRemoteCompany {
    isLoading = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* favResultMapping = [AMCompanyFavoriteListResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: favResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_COMPANY_FAV usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate =self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCompanyFavoriteListResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.favComanyRequest;
    }];
}

- (void)loadObjectsFromRemotePrice {
    isLoading = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* favPriceMapping = [AMPriceItem sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: favPriceMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRICE_FAV usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPriceItem class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.favPriceRequest;
    }];
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    //    self.tokenState = AMTokenStateNormal;
    //    self.isRequestSucess = YES;
    
    NSLog(@"Loaded objects: %@", objects);    
    
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        if (transactionType == AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST_DELETE) {
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // del favorite successfully
                [self._proObjects removeObjectAtIndex:self.rowToDel];
                productTotalCount--;
                [offerTableView reloadData];
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏成功"] show]; 
                
            } else {
                // failed to del
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏失败"] show];
            }
            if (productTotalCount<=0) {
                [self.mLoadingView showNodataMessage];
            }
            else {
                [self.mLoadingView endLoadingView];
            }
        } else if (transactionType == AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST_DELETE){
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // del favorite successfully
                [self._comObjects removeObjectAtIndex:self.rowToDel];
                companyTotalCount--;
                [companyTableView reloadData];
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏成功"] show]; 
                
            } else {
                // failed to del
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏失败"] show]; 
                
            }
            if (companyTotalCount<=0) {
                [self.mLoadingView showNodataMessage];
            }
            else {
                [self.mLoadingView endLoadingView];
            }
            
        } else if (transactionType == AMTRANSACTION_TYPE_FAVORITE_PRICE_DELETE){
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // del favorite successfully
                [self._priObjects removeObjectAtIndex:self.rowToDel];
                priceTotalCount--;
                [priceTableView reloadData];
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏成功"] show];
                
            } else {
                // failed to del
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏失败"] show];
            }
            if (priceTotalCount<=0) {
                [self.mLoadingView showNodataMessage];
            }
            else {
                [self.mLoadingView endLoadingView];
            }
            
        } else if(transactionType==AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST){
            
            AMOfferFavoriteListResult *result = (AMOfferFavoriteListResult*)[objects objectAtIndex:0];
            
            if (self._proObjects==nil) {
                self._proObjects = [[NSMutableArray alloc]init];
                
            }
            else
            { 
                if(isSegmentChanged)
                {
                    [_proObjects removeAllObjects];
                    [offerTableView reloadData];
                    isSegmentChanged=FALSE;
//                    isFromDetail=FALSE;
                }
            }
            if([result.resultList count]> 0){
                if (self.isRefresh) {
                    [self._proObjects removeAllObjects];
                    self.offerTableView.ContentOffset = CGPointMake(0, 0);
                    self.isRefresh = NO;
                }
                
                for(int i=0; i<result.resultList.count; i++){
                    AMFavoriteOffer *favOffer = (AMFavoriteOffer*)[result.resultList objectAtIndex:i ] ;
                    if(favOffer.valid.boolValue){
                        [self._proObjects addObject:favOffer];
                    }
                }
                
            }
            
            productTotalCount =[[result totalCount] intValue];
            [offerTableView reloadData];
            if (productTotalCount<=0) {
                [self.mLoadingView showNodataMessage];
            }
            else {
                [self.mLoadingView endLoadingView];
            }
            
        } else if(transactionType==AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST){
            
            AMCompanyFavoriteListResult *result = (AMCompanyFavoriteListResult*)[objects objectAtIndex:0];
            
            if (self._comObjects==nil) {
                self._comObjects = [[NSMutableArray alloc]initWithArray:result.resultList];
                
            }
            else
            {
                if(isSegmentChanged){
                    [_comObjects removeAllObjects];
                    [companyTableView reloadData];
                    isSegmentChanged=FALSE;
//                    isFromDetail=FALSE;
                }
                if([result.resultList count]> 0){
                    if (self.isRefresh) {
                        [self._comObjects removeAllObjects];
                        self.isRefresh = NO;
                        self.companyTableView.ContentOffset = CGPointMake(0, 0);
                    }
                    [self._comObjects addObjectsFromArray:result.resultList];
                }
                
            }
            
            
            companyTotalCount=[[result totalCount] intValue];
            [companyTableView reloadData];
            if (companyTotalCount<=0) {
                [self.mLoadingView showNodataMessage];
            }
            else {
                [self.mLoadingView endLoadingView];
            }
        } else if(transactionType==AMTRANSACTION_TYPE_FAVORITE_PRICE_LIST){
            
            if (self.isRefresh) {
                self.priceTableView.ContentOffset = CGPointMake(0, 0);
                self.isRefresh = NO;
            }
            self._priObjects = objects; 
            
            priceTotalCount = [objects count];
            [priceTableView reloadData];
            if (priceTotalCount<=0) {
                [self.mLoadingView showNodataMessage];
            }
            else {
                [self.mLoadingView endLoadingView];
            }
            
        }
        isLoading = NO;
        self.mSegmentedControl.button.enabled = YES;
        if(currentProPage*DEFAULT_PAGE_SIZE >= productTotalCount) {
            self.offerTableView.tableFooterView =nil ;
        }
        if (currentComPage*DEFAULT_PAGE_SIZE >= companyTotalCount) {
            
            self.companyTableView.tableFooterView = nil;
        }
//        if (currentPriPage*DEFAULT_PAGE_SIZE >= priceTotalCount) {
//            
//            self.priceTableView.tableFooterView = nil;
//        }

    } 
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        if (transactionType == AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST) {
            if ([_proObjects count]) {
                self.offerTableView.tableFooterView = errorMessageView;
            }
            if (!self.isRefresh) {
                currentProPage--;
            }else {
                self.offerTableView.contentOffset = CGPointMake(0, 0);
                currentProPage = self.tempCurrentProPage;
            }
            self.isRefresh = NO;
        }else if(transactionType == AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST) {
            if ([_comObjects count]) {
                self.companyTableView.tableFooterView = errorMessageView;
            }
            if (!self.isRefresh) {
                currentComPage --;
            }else {
                self.companyTableView.ContentOffset = CGPointMake(0, 0);
                currentComPage = self.tempCurrentComPage;
            }
            self.isRefresh = NO;
        }else if (transactionType == AMTRANSACTION_TYPE_FAVORITE_PRICE_LIST) {
            if (self.isRefresh) {
                self.priceTableView.contentOffset = CGPointMake(0, 0);
            }
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        
//        if (selectItem == 0 &&[_proObjects count] != 0) {
//            //            [self.offerTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:[_proObjects count] inSection:0]];
//            self.offerTableView.tableFooterView = errorMessageView;
//            currentProPage--;
//        }else if (selectItem == 1 && [_comObjects count]!=0) {
//            self.companyTableView.tableFooterView = errorMessageView;
////        }else if (selectItem == 2 && [_priObjects count]!=0) {
////            self.priceTableView.tableFooterView = errorMessageView;
//            currentComPage--;
//        }else {
//            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
//        }
        [errorMessageView release];
    }
    isLoading = NO;
    self.mSegmentedControl.button.enabled = YES;
//    if(currentProPage*DEFAULT_PAGE_SIZE >= productTotalCount) {
//        self.offerTableView.tableFooterView =nil ;
//    }
//    if (currentComPage*DEFAULT_PAGE_SIZE >= companyTotalCount) {
//        
//        self.companyTableView.tableFooterView = nil;
//    }
}

#pragma mark - View lifecycle
-(void)loadRequest
{
    //    if(isLoading){
    //        return;
    //    }
    //检查accesstoken是否需要更新
    //    [LoginToken checkAccessTokenExpired];
    self.mSegmentedControl.button.enabled = NO;
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    self.loginUserName = loginUserName;
    if ([loginUserName length] > 3) {

        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        //[_objects removeAllObjects];      
        
        if(selectItem ==0){
            self.favOfferRequest.memberid = loginUserName;
            self.favOfferRequest.pageSize = [NSNumber numberWithInt: DEFAULT_PAGE_SIZE]; 
            self.favOfferRequest.beginPage = [NSNumber numberWithInt: currentProPage];
            if (currentProPage>1) {
                self.offerTableView.tableFooterView = moreloadingView;
            }else {
                [self.mLoadingView showLoadingView];
            }
            if (currentProPage==1) {
                self.offerTableView.tableFooterView = nil;
            }
            [self loadObjectsFromRemoteProduct];
            
        }else if(selectItem ==1){
            self.favComanyRequest.memberid = loginUserName;
            self.favComanyRequest.pageSize = [NSNumber numberWithInt: DEFAULT_PAGE_SIZE];
            self.favComanyRequest.beginPage = [NSNumber numberWithInt: currentComPage];
            if (currentComPage>1) {
                self.companyTableView.tableFooterView = moreloadingView;
            }else {
                [self.mLoadingView showLoadingView];
            }
            if (currentComPage==1) {
                self.companyTableView.tableFooterView = nil;
            }
            [self loadObjectsFromRemoteCompany];
            
        }  else if(selectItem ==2){
            self.favPriceRequest.memberid = loginUserName;
            self.favPriceRequest.pageSize = [NSNumber numberWithInt: DEFAULT_PAGE_SIZE];
            self.favPriceRequest.beginPage = [NSNumber numberWithInt: currentPriPage];
            if (currentPriPage==1) {
                self.priceTableView.tableFooterView = nil;
            }
            [self.mLoadingView showLoadingView];
            [self loadObjectsFromRemotePrice];
        } 
        [moreloadingView release];
    }else {
        isFavCallLogin=TRUE;
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;
        //[UIView setAnimationTransition:UIViewAnimationTransitionCurlUp forView: nextController.view  cache:YES];
        [self.navigationController pushViewController:nextController animated:YES];
        
    }
    
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

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 10.0) {
        if (!isLoading) {
            if (scroll==self.offerTableView){
                if(currentProPage*DEFAULT_PAGE_SIZE < productTotalCount) {
                    currentProPage++;
                    [self loadRequest];
                } 
            } else if (scroll == self.companyTableView){
                if(currentComPage* DEFAULT_PAGE_SIZE < companyTotalCount) {
                    currentComPage++;
                    [self loadRequest]; 
                }
            }
            
            
        }
    }
}

#pragma mark - View lifecycle


-(void) customTabbarArea
{
    _mSegmentedControl = [[AMSegmentedCtlWithButton alloc] initWithFrame:CGRectMake(0, 0, 320, 40)];
    self.mSegmentedControl.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
    //第一套方案，自己写的AMFavSegmentedControl，更灵活些
    
    [self.mSegmentedControl insertSegmentWithTitle:@"产品" atIndex:0 animated:YES];
    [self.mSegmentedControl insertSegmentWithTitle:@"公司" atIndex:1 animated:YES];
    [self.mSegmentedControl insertSegmentWithTitle:@"价格" atIndex:2 animated:YES];

//    self.mSegmentedControl.mSegmentedControl.delegate = self;
    [self.mSegmentedControl setDelegate:self];
    [self.mSegmentedControl setItemsHidden:UISegmentedControlHidden Hidden:YES];
    //第二套方案，用自带的NSSegmentedControl
//    [self.mSegmentedControl insertSegmentWithTitle:@"产品收藏" atIndex:0 animated:YES];
//    [self.mSegmentedControl insertSegmentWithTitle:@"公司收藏" atIndex:1 animated:YES];
//    [self.mSegmentedControl insertSegmentWithTitle:@"价格收藏" atIndex:2 animated:YES];
//    self.mSegmentedControl.segmentedControl.selectedSegmentIndex = 0;//设置默认选择项索引    
//    self.mSegmentedControl.segmentedControl.segmentedControlStyle = UISegmentedControlStyleBar; 
//    self.mSegmentedControl.segmentedControl.momentary = NO; 
//    self.mSegmentedControl.segmentedControl.multipleTouchEnabled=NO; 
//    self.mSegmentedControl.segmentedControl.tintColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];  
//    [self.mSegmentedControl.segmentedControl addTarget:self action:@selector(Selectbutton:) forControlEvents:UIControlEventValueChanged]; 
//    [self.mSegmentedControl setItemsHidden:UIAMFavSegmentedControlHidden Hidden:YES];

    

    /* AliImageButton * lineImg = [[AliImageControlFactory sharedInstance] getImageButtonWithType:LINE_DIVIDED];
        lineImg.frame = CGRectMake(0, 40, 320, 2);
        [self.view addSubview:lineImg];    
    */
    
    [self.mSegmentedControl.button addTarget:self action:@selector(updateAtction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.mSegmentedControl];

    
    
    
}
//
//-(void)Selectbutton:(id)sender{
//    UISegmentedControl *myUISegmentedControl=(UISegmentedControl *)sender;
//
////    [self.mSegmentedControl ChangeSegmentFont:self.mSegmentedControl.segmentedControl]; 
//    isSegmentChanged  = TRUE;
//    selectItem = myUISegmentedControl.selectedSegmentIndex;
//    currentProPage =1;
//    currentComPage=1;
//    currentPriPage=1;
//    switch (myUISegmentedControl.selectedSegmentIndex) {
//        case 0:
//            [AMLogUtils appendLog: APP_FAVORITE_ONE];
//            [_proObjects removeAllObjects];
//            [self.offerTableView reloadData];
//            [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
//            [self.favoritesView insertSubview:self.offerTableView atIndex:0];
//            break;
//        case 1:
//            [AMLogUtils appendLog: APP_FAVORITE_TWO];
//            [_comObjects removeAllObjects];
//            [self.companyTableView reloadData];
//            [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
//            [self.favoritesView insertSubview:self.companyTableView atIndex:0];
//            break;
//        case 2:
//            [AMLogUtils appendLog: APP_FAVORITE_THREE];
//            [_priObjects removeAllObjects];
//            [self.priceTableView reloadData];
//            [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
//            [self.favoritesView insertSubview:self.priceTableView atIndex:0];
//            break;
//        default:
//            break;
//    }
//    [self loadRequest];
//}

-(void)updateAtction:(id) sender
{
    if (selectItem ==0) {
        self.isRefresh = YES;
        self.offerTableView.tableFooterView = nil;
        self.tempCurrentProPage = currentProPage;
        currentProPage = 1;
        
//        [self._proObjects removeAllObjects];
//        [self.offerTableView reloadData];
        
    }else if(selectItem==1){
        self.isRefresh = YES;
        self.companyTableView.tableFooterView = nil;
        self.tempCurrentComPage = currentComPage;
        currentComPage = 1;
//        [self._comObjects removeAllObjects];
//        [self.companyTableView reloadData];
    }else{
        self.isRefresh = YES;
    }
    [self loadRequest];
//    [self segmentValueChanged:selectItem];
//    isFromDetail=TRUE;
}
- (void) segmentValueChanged:(int)nowIndex
{     
    //    if(isLoading){
    //        //记住现在的状态，并等待didLoad后做出判断。
    //        return;    
    //    }
    
    isSegmentChanged  = TRUE;
    selectItem =nowIndex;
    currentProPage =1;
    currentComPage=1;
    currentPriPage=1;
    //由于点tab跳转以后offset还会保留 因此会引发scroll的事件 进而自动增加页面。。造成currentpage会自动加1 数据从而变少一页。。。内牛满面啊！！
    [self.offerTableView setContentOffset:CGPointMake(0, 0)];
    [self.companyTableView setContentOffset:CGPointMake(0, 0)];
    [self.priceTableView setContentOffset:CGPointMake(0, 0)];
    if (selectItem == 0){
        [AMLogUtils appendLog: APP_FAVORITE_ONE];
        [_proObjects removeAllObjects];
        [self.offerTableView reloadData];
        [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
        [self.favoritesView insertSubview:self.offerTableView atIndex:0];
    }else if (selectItem == 1){
        [AMLogUtils appendLog: APP_FAVORITE_TWO];
        [_comObjects removeAllObjects];
        [self.companyTableView reloadData];
        [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
        [self.favoritesView insertSubview:self.companyTableView atIndex:0];
        
    }else {
        [AMLogUtils appendLog: APP_FAVORITE_THREE];
        [_priObjects removeAllObjects];
        [self.priceTableView reloadData];
        [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
        [self.favoritesView insertSubview:self.priceTableView atIndex:0];
        
    }
    [self loadRequest];
    
    
}

-(void)loginEvent:(id)sender{
    
    
    if([self.loginUserName isEqualToString:[LoginToken getLoginUserName]])
    {
        if(isFavCallLogin == TRUE){
            isFavCallLogin = FALSE;        
            [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"登录成功"] show];
            [_proObjects removeAllObjects];
            [_comObjects removeAllObjects];
            [_priObjects removeAllObjects];
            [offerTableView reloadData];
            [companyTableView reloadData];
            [priceTableView reloadData];
            [self loadRequest];    
        }
    }
    else {
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"登录成功"] show];
        [_proObjects removeAllObjects];
        [_comObjects removeAllObjects];
        [_priObjects removeAllObjects];
        [offerTableView reloadData];
        [companyTableView reloadData];
        [priceTableView reloadData];
        [self loadRequest];
        
        
    }
    
    
    
    if(isFavCallLogin == TRUE){
        isFavCallLogin = FALSE;        
        [[AliToastView MakeToastWithType:TOAST_STYLE_SUCC info:@"登录成功"] show];
        [self loadRequest];    
    }
}

-(void)cancelEvent:(id)sender{
    forceLoginCount=0;
    isFavCallLogin =FALSE;
}

//-(void)updateFavRecordEvent:(id)sender{
//    if (!isLoading) {
//        [self loadRequest];
//        isFromDetail=TRUE;
//    }
//    
//}


- (void)viewDidLoad
{ 
    [super viewDidLoad];
    
    //    self.tokenState = AMTokenStateNormal;
    
    // Do any additional setup after loading the view from its nib.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginEvent:) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    //    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cancelEvent:) name:NOTIFICATION_CANCELLOGIN object:nil];
    
    [self customTabbarArea];
    

    
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateFavRecordEvent:) name:NOTIFICATION_FROM_DETAIL object:nil];
    
    UISwipeGestureRecognizer *swipeGesture = [[[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipe:)] autorelease];
    [swipeGesture setDirection:(UISwipeGestureRecognizerDirectionRight | UISwipeGestureRecognizerDirectionLeft)];
    [self.offerTableView addGestureRecognizer:swipeGesture];
    
    UISwipeGestureRecognizer *swipeGesture2 = [[[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipe:)] autorelease];
    [swipeGesture2 setDirection:(UISwipeGestureRecognizerDirectionRight | UISwipeGestureRecognizerDirectionLeft)];
    [self.companyTableView addGestureRecognizer:swipeGesture2];
    
    UISwipeGestureRecognizer *swipeGesture3 = [[[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipe:)] autorelease];
    [swipeGesture3 setDirection:(UISwipeGestureRecognizerDirectionRight | UISwipeGestureRecognizerDirectionLeft)];
    [self.priceTableView addGestureRecognizer:swipeGesture3];
    
    [self objManInit];

    currentProPage=1;
    currentComPage=1;
    currentPriPage=1;
    productTotalCount=0;
    companyTotalCount=0;
    priceTotalCount=0;
    
    isFavCallLogin =FALSE;
    forceLoginCount=0;

//    [[self.favoritesView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
//    [self.favoritesView insertSubview:self.offerTableView atIndex:0];
    
    //[self loadRequest];
    isFromDetail=FALSE;
}


- (void)viewDidUnload
{
    [self retain];
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    self.favoritesView = nil;
    self.offerTableView = nil;
    self.companyTableView = nil;
    self.priceTableView = nil;
    self._proObjects = nil;
    self._comObjects = nil;
    self._priObjects = nil;
    self.objMan = nil;
//    self.mSegmentedControl.mSegmentedControl.delegate = nil;
    self.mSegmentedControl = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    NSString *name = [LoginToken getLoginUserName];
    
    if([self.loginUserName isEqualToString:name])
    {
        if (!self.oceanClient.isRequestSucess) {
            [self loadRequest];
        }
    }else {
        [self loadRequest];
        
    }
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    if (!isFromDetail) {
        if (selectItem == 1) {
            [self.mSegmentedControl setSelectedIndex:1];
            [self  segmentValueChanged:1];
            //        [self Selectbutton:self.mSegmentedControl.segmentedControl]; 
        }else if (selectItem == 2) {
            [self.mSegmentedControl setSelectedIndex:2];
            [self  segmentValueChanged:2];
            //        [self Selectbutton:self.mSegmentedControl.segmentedControl];
        }else{
            [self.mSegmentedControl setSelectedIndex:0];
            [self  segmentValueChanged:0];
            //        [self Selectbutton:self.mSegmentedControl.segmentedControl];
        }
        isFromDetail = NO;
    }
    
}

-(void) setSelectItem{
//    [self.mSegmentedControl.mSegmentedControl setSelectedIndex:2];
    selectItem = 2;

}
-(void) setSelectedSegmentIndex:(NSUInteger)index{
    [self.mSegmentedControl.mSegmentedControl setSelectedIndex:index];
    [self.mSegmentedControl.segmentedControl setSelectedSegmentIndex:index];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:NO animated:NO];
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    if (tableView==offerTableView){   
        
        return [self._proObjects count];
        
    } else if (tableView==companyTableView) {
        
        return [self._comObjects count];
        
    }else if(tableView==priceTableView){
        
        return [self._priObjects count];
    }
    return 0;
}

//设置cell高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    if (tableView==offerTableView){
        return [AliTableViewCellOfferDetail cellHeight]-19;
    }
    else if (tableView==companyTableView){
        return [AliTableViewCellCompanyDetail cellHeight];
        
    }
    else if(tableView==priceTableView){
        
        return [AliTableViewCellPriceDetail cellHeight];
        
    }
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    NSUInteger row = [indexPath row];
    if (tableView==offerTableView) {  
        AliTableViewCellOfferDetail *cell = (AliTableViewCellOfferDetail *)[tableView 
                                                                            
                                                                            dequeueReusableCellWithIdentifier: [AliTableViewCellOfferDetail cellIdentifer]];
        if (cell == nil)  {
            cell = [AliTableViewCellOfferDetail createCell];
            cell.frame = CGRectMake(0.0, 0.0, 320, [AliTableViewCellOfferDetail cellHeight]-19);
            
        }
        
        AMFavoriteOffer *favOffer = (AMFavoriteOffer*)[_proObjects objectAtIndex:row ] ;
        NSLog(@"offer objects: %@", favOffer);    
        [cell cellSetData:cell favOffer:favOffer];
        [self.objMan manage:cell.icon];
        
        return cell;
        
    }
    
    else if (tableView==companyTableView)
    {   
        AliTableViewCellCompanyDetail *cell = (AliTableViewCellCompanyDetail *)[tableView 
                                                                                dequeueReusableCellWithIdentifier: [AliTableViewCellCompanyDetail cellIdentifer]];
        if (cell == nil)  
        {
            cell = [AliTableViewCellCompanyDetail createCell];
        }
        AMFavoriteCompany *company = (AMFavoriteCompany*)[_comObjects objectAtIndex:row ];
        [cell cellSetData:cell amFavCompany:company];
        [self.objMan manage:cell.icon];
        return cell;
        
    }
    else if (tableView==priceTableView) {
        
        AliTableViewCellPriceDetail *cell = (AliTableViewCellPriceDetail *)[tableView 
                                                                            dequeueReusableCellWithIdentifier: [AliTableViewCellPriceDetail cellIdentifer]];
        if (cell == nil)  
        {
            cell = [AliTableViewCellPriceDetail createCell];       
        }
        
        NSUInteger row = [indexPath row];
        AMPriceItem *priceItem = (AMPriceItem*)[_priObjects objectAtIndex:row] ;   
        [cell cellSetData:priceItem];
        return cell;
    }
    return nil;
}

//单击行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    isFromDetail = YES;
    if (tableView==offerTableView){ 
        
        [AMLogUtils appendLog: APP_FAVORITE_FOUR]; 
        
        AMFavoriteOffer* offer = [_proObjects objectAtIndex:indexPath.row ];
        NSString *strOfferId=offer.offerid;
        NSString *strOfferName=@"";
        
        AMOfferTabViewController * controller = [[[AMOfferTabViewController alloc] initWithOfferId:strOfferId offerName:strOfferName preViewName:@"AMFavoritesViewController"] autorelease];
        
        controller.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:controller animated:YES]; 
        [self.navigationController setNavigationBarHidden:NO animated:YES];
        [self.offerTableView deselectRowAtIndexPath:indexPath animated:NO]; 
    }
    if (tableView==companyTableView){ 
        [AMLogUtils appendLog: APP_FAVORITE_FIVE]; 
        
        NSString *strMemberId=[[_comObjects objectAtIndex:indexPath.row ] memberId];
        
        NSString *strCompanyName=[[_comObjects objectAtIndex:indexPath.row ] name];
        
        AMCompanyTabViewController * companyTabViewController = [[AMCompanyTabViewController alloc] initWithMemberId:strMemberId companyName:strCompanyName preViewName:@"AMFavoritesViewController"];
        
        
        [self.navigationController pushViewController:companyTabViewController animated:YES];
        [self.navigationController setNavigationBarHidden:NO animated:YES];
        [companyTabViewController release];
        
        [self.companyTableView deselectRowAtIndexPath:indexPath animated:NO]; 
    }
    
    if (tableView==priceTableView){
        
        AMPriceItem *priceItem = (AMPriceItem*)[_priObjects objectAtIndex:indexPath.row] ;   
        AMPriceGraphViewController *priceGraphViewController = [[AMPriceGraphViewController alloc] initWithNibName:@"AMPriceGraphViewController" bundle:nil];
        NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
        [f setNumberStyle:NSNumberFormatterDecimalStyle];
        
        priceGraphViewController.themeRequstId = [f numberFromString:priceItem.themeId];
        priceGraphViewController.sourceFomeRequstId = [f numberFromString:priceItem.sourceFromId];
        priceGraphViewController.areaRequstId = [f numberFromString:priceItem.areaId];
        priceGraphViewController.sourceAddressName = [priceItem.attributes objectForKey:@"原产地"];
        priceGraphViewController.isPriceFavorited = true;//收藏为真表示已经收藏
        priceGraphViewController.navigateTitleName = @"返回";
        if (priceGraphViewController.sourceAddressName == nil) {   
            NSString *subString = @"产地";
            for (id key in priceItem.attributes)
            {
                
                NSRange range = [key rangeOfString:subString];
                if (range.location == NSNotFound) {
                    continue;
                }else {
                    priceGraphViewController.sourceAddressName = [priceItem.attributes objectForKey:key];
                }
                
            }
            if (priceGraphViewController.sourceAddressName == nil) {
                priceGraphViewController.sourceAddressName = priceItem.areaName;
            }
        }
        priceGraphViewController.hidesBottomBarWhenPushed=YES;
        [f release];
        [self.navigationController pushViewController:priceGraphViewController animated:YES]; 
        [priceGraphViewController release];
        [self.priceTableView deselectRowAtIndexPath:indexPath animated:NO];
    }
    
    
}

- (void)deleteFavoriteRecord:(NSString *)OceanApiUrl {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* cudResultMapping = [AMCUDResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: cudResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OceanApiUrl usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCUDResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        
        if ([OceanApiUrl isEqualToString:OCEAN_API_URL_OFFER_FAV_DEL]) {
            loader.params = self.delFavOfferRequset;
        }else if([OceanApiUrl isEqualToString:OCEAN_API_URL_COMPANY_FAV_DEL]){
            loader.params = self.delFavComanyRequest;
        }else if([OceanApiUrl isEqualToString:OCEAN_API_URL_PRICE_FAV_DEL]){
            loader.params = self.delFavPriceRequest;
        }
        
    }];
}

- (void)didSwipe:(UIGestureRecognizer *)gestureRecognizer {
    if (gestureRecognizer.state == UIGestureRecognizerStateEnded) {
        
        CGPoint swipeLocation;
        NSIndexPath *swipedIndexPath;
        BOOL effectiveClick=FALSE;
        
        if (selectItem == 0){
            swipeLocation = [gestureRecognizer locationInView:self.offerTableView];
            swipedIndexPath = [self.offerTableView indexPathForRowAtPoint:swipeLocation];
            AliTableViewCellOfferDetail* Cell =(AliTableViewCellOfferDetail *)[self.offerTableView cellForRowAtIndexPath:swipedIndexPath];
            if ([Cell isKindOfClass:[AliTableViewCellOfferDetail class]]) {
                effectiveClick=TRUE;
            }
        } else if (selectItem == 1){
            swipeLocation = [gestureRecognizer locationInView:self.companyTableView];
            swipedIndexPath = [self.companyTableView indexPathForRowAtPoint:swipeLocation];
            AliTableViewCellCompanyDetail* Cell =(AliTableViewCellCompanyDetail *)[self.companyTableView cellForRowAtIndexPath:swipedIndexPath];
            if ([Cell isKindOfClass:[AliTableViewCellCompanyDetail class]]) {
                effectiveClick=TRUE;
            }
        }else if (selectItem == 2){
            swipeLocation = [gestureRecognizer locationInView:self.priceTableView];
            swipedIndexPath = [self.priceTableView indexPathForRowAtPoint:swipeLocation];
            AliTableViewCellPriceDetail* Cell =(AliTableViewCellPriceDetail *)[self.priceTableView cellForRowAtIndexPath:swipedIndexPath];
            if ([Cell isKindOfClass:[AliTableViewCellPriceDetail class]]) {
                effectiveClick=TRUE;
            }
        }
        
        if (effectiveClick==TRUE) {
            
            NSString *loginUserName=nil;
            loginUserName=[LoginToken getLoginUserName];
            if([loginUserName length] <= 3){  
                isFavCallLogin=TRUE;
                
                UIViewController *nextController;
                nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
                nextController.hidesBottomBarWhenPushed=YES;
                
                [self.navigationController pushViewController:nextController animated:YES];
            }else{
                self.rowToDel =[swipedIndexPath row];
                NSString *msg = [[NSString alloc]initWithFormat:@"从收藏夹中删除？"];
                UIAlertView *alert = [[UIAlertView alloc] 
                                      initWithTitle:@"" 
                                      message:msg 
                                      delegate:self    
                                      cancelButtonTitle:@"取消"                          otherButtonTitles:@"确定" ,
                                      nil]; 
                [alert show]; 
                [alert release];
                [msg release];
            }
            
        }  
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex ==  0) {  
        NSLog(@"取消删除");
    }
    else {    
        NSLog(@"删除收藏记录");
        //del fav request here        
        if (selectItem == 0){
            AMFavoriteOffer *itemToDel =(AMFavoriteOffer*)[self._proObjects objectAtIndex:self.rowToDel]; 
            self.delFavOfferRequset.memberid =itemToDel.company.memberId;
            self.delFavOfferRequset.offerids = [NSArray arrayWithObjects:itemToDel.offerid, nil];
            
            [self deleteFavoriteRecord:OCEAN_API_URL_OFFER_FAV_DEL];
            //self.rowToAdd = -1;
        } else if (selectItem == 1){
            AMFavoriteCompany *itemToDel =(AMFavoriteCompany*)[self._comObjects objectAtIndex:self.rowToDel]; 
            
            self.delFavComanyRequest.memberid =itemToDel.memberId;
            self.delFavComanyRequest.companyids = [NSArray arrayWithObjects:itemToDel.companyid, nil];
            [self deleteFavoriteRecord:OCEAN_API_URL_COMPANY_FAV_DEL];
            //self.rowToAdd = -1;
            
        }else if (selectItem == 2){
            AMPriceItem *itemToDel =(AMPriceItem*)[self._priObjects objectAtIndex:self.rowToDel]; 
            
            self.delFavPriceRequest.themeId =itemToDel.themeId;
            self.delFavPriceRequest.sourceFromId = itemToDel.sourceFromId;
            self.delFavPriceRequest.area = itemToDel.areaId;
            
            self.delFavPriceRequest.memberId=[LoginToken getLoginUserName];
            [self deleteFavoriteRecord:OCEAN_API_URL_PRICE_FAV_DEL];
            //self.rowToAdd = -1;
        }
        
    }
}

//-(void)loginTokenHelperDidUpdateAccessToken{
//    [self loadRequest];
//}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [controllers release];
    [favorites release];
    [favoritesView release];
    
    [offerTableView release];
    [companyTableView release];
    [priceTableView release];
    
    [_mSegmentedControl release];   
    [_proObjects release];
    [_comObjects release];
    [_priObjects release];
    [objMan release];
    
    [_favOfferRequest release];
    [_favComanyRequest release];
    [_favPriceRequest release];
    [_delFavOfferRequset release];
    [_delFavComanyRequest release];
    [_delFavPriceRequest release];
    
    [_loginUserName release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [super dealloc];
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

-(void)request:(RKRequest *)request didFailLoadWithError:(NSError *)error{
    [super request:request didFailLoadWithError:error];
    
}

//-(void)reloadLoadingData{
//    [self loadRequest];
//}
@end

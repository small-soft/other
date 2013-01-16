//
//  AMHotRankOfferViewController.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankOfferViewController.h"
#import "UIHelp.h"
#import "AMHotRankOfferRequest.h"
#import "ConstDef.h"
#import "AMHotRankOfferResult.h"
#import "AMHotRankOfferCell.h"
#import "AMHotRankCompanyCell.h"
#import "AMMoreLoadingCell.h"
#import "HJObjManager.h"
#import "AMHotRankOffer.h"
#import "AMOfferTabViewController.h"
#import "AMCompanyTabViewController.h"
#import "AMHotRankCompanyRequest.h"
#import "AMHotRankCompanyResult.h"
#import "AMHotRankCompany.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"
#import "AliLoadingDataView.h"

#define BUTTON_UP 0
#define BUTTON_HOT 1
@interface AMHotRankOfferViewController()
//@property (nonatomic,retain) NSMutableArray *offersData;
@property (nonatomic,retain) NSMutableArray *contentsData;

@property (nonatomic,retain) NSMutableArray *companiesData;
@property (readwrite) int offerTotal;
@property (readwrite) int companyTotal;
@property (readwrite) NSInteger rowToAdd;
@property (readwrite) int offerCurrentPage;
@property (readwrite) int companyCurrentPage;

@property (readwrite) BOOL isOfferLoading;
@property (readwrite) BOOL isCompanyLoading;
@property (nonatomic, retain) HJObjManager *objMan;
//@property (nonatomic,retain) AMNavigationTitleView *navigationTitle;
@property (nonatomic,retain)AMHotRankOfferRequest *offersRequest;
@property (nonatomic, readonly) NSArray* segmentTitle;

@property (nonatomic,retain)AMHotRankCompanyRequest *companyiesRequest;


- (void)loadObjectsFromRemoteOffer;
- (void)loadObjectsFromRemoteCompany;
@end


@implementation AMHotRankOfferViewController

#pragma synthesize start
@synthesize contentTable=_contentTable;
@synthesize offersRequest = _offersRequest;
//@synthesize navigationTitle=_navigationTitle;
@synthesize contentsData=_contentsData;
@synthesize offerTotal = _offerTotal;
@synthesize companyTotal = _companyTotal;
@synthesize rowToAdd = _rowToAdd;
@synthesize offerCurrentPage = _offerCurrentPage;
@synthesize companyCurrentPage = _companyCurrentPage;
@synthesize isOfferLoading = _isOfferLoading;
@synthesize isCompanyLoading = _isCompanyLoading;
@synthesize objMan=_objMan;
@synthesize parentTitle = _parentTitle;
@synthesize cateTitle = _cateTitle;
@synthesize catIds = _cateIds;
@synthesize cateId = _cateId;
@synthesize segmentTitle=_segmentTitle;

@synthesize hotRankMode = _hotRankMode;
@synthesize hotOrUpMode = _hotOrUpMode;

@synthesize companyiesRequest = _companyiesRequest;
//@synthesize navigationTitle=_navigationTitle;
@synthesize companiesData=_companiesData;
@synthesize pageId = _pageId;
@synthesize headerView = _headerView;

@synthesize upButton = _upButton;
@synthesize hotButton = _hotButton;
@synthesize segmentLoadingView = _segmentLoadingView;

-(NSMutableArray*)segment
{
    
    if (_contentsData==nil) {
        _contentsData = [[NSMutableArray alloc] init];
    }
    return _contentsData;
}

-(NSArray*)segmentTitle
{
    if (!_segmentTitle) {
        _segmentTitle = [[NSArray alloc]initWithObjects:@"产品",@"公司",nil];
    }
    return _segmentTitle;
}

-(NSArray*)commonTableViewSegmentTitle
{
    return self.segmentTitle;
}


-(AMHotRankOfferRequest*)offersRequest
{
    if (_offersRequest==nil) {
        _offersRequest = [[AMHotRankOfferRequest alloc] init];
        _offersRequest.transactionType = AMTRANSACTION_TYPE_HOTRANK_OFFER_LIST;
    }

    _offersRequest.beginPage=[NSNumber numberWithInt:self.offerCurrentPage];
    _offersRequest.cateIds = [NSString stringWithFormat:self.catIds];
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSNumber *hotOrUpModeNumber = [defaults objectForKey:@"hotOrUpMode"];
    if(!hotOrUpModeNumber){
        _offersRequest.listMode = @"U";
    }else{
        if([hotOrUpModeNumber intValue]==0){
            _offersRequest.listMode = @"U";
        }else{
            _offersRequest.listMode = @"H";
        }
    }
    
//    if(self.hotOrUpMode==0){
//        _offersRequest.listMode = @"U";
//    }else{
//        _offersRequest.listMode = @"H";
//    }
    return _offersRequest;

}

-(AMHotRankCompanyRequest*)companyiesRequest
{
    if (_companyiesRequest==nil) {
        _companyiesRequest = [[AMHotRankCompanyRequest alloc] init];
        _companyiesRequest.transactionType = AMTRANSACTION_TYPE_HOTRANK_COMPANY_LIST;
    }
    
    _companyiesRequest.page=[NSNumber numberWithInt:self.companyCurrentPage];
    _companyiesRequest.cateId = [NSString stringWithFormat:self.cateId];
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSNumber *hotOrUpModeNumber = [defaults objectForKey:@"hotOrUpMode"];
    if(!hotOrUpModeNumber){
        _companyiesRequest.listMode = @"U";
    }else{
        if([hotOrUpModeNumber intValue]==0){
            _companyiesRequest.listMode = @"U";
        }else{
            _companyiesRequest.listMode = @"H";
        }
    }
    //    if(self.hotOrUpMode==0){
    //        _companyiesRequest.listMode = @"U";
    //    }else{
    //         _companyiesRequest.listMode = @"H";
    //    }
    return _companyiesRequest;
}

-(NSMutableArray*)contentsData
{
    
    if (_contentsData==nil) {
        _contentsData = [[NSMutableArray alloc] init];
    }
    return _contentsData;
}

-(NSMutableArray*)companiesData
{
    
    if (_companiesData==nil) {
        _companiesData = [[NSMutableArray alloc] init];
    }
    return _companiesData;
}

-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:20 memCacheSize:20];
        
        NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcacheamon1/"] ;
        HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
        _objMan.fileCache = fileCache;
        // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
        fileCache.fileCountLimit = 100;
        fileCache.fileAgeLimit = 75*75*24*7; //1 week
        [fileCache trimCacheUsingBackgroundThread];
        
    }
    return _objMan;
    
}

- (void)dealloc {
    [_offersRequest release];
    [_contentTable release];
    [_contentsData release];
    [_objMan release];
    [_cateIds release];
    [_cateTitle release];
    [_companiesData release];
    [_companyiesRequest release];
//    [_companyiesRequest release];
    [_headerView release];
    [_hotButton release];
    [_upButton release];
    [_segmentLoadingView release];
    [_segmentTitle release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setContentTable:nil];
    [_offersRequest release];
    _offersRequest=nil;
    [_companyiesRequest release];
    _companyiesRequest=nil;
    [_objMan release];
    _objMan =nil;
    [_companiesData release];
    _companiesData=nil;
    [_contentsData release];
    _contentsData =nil;
    [_segmentTitle release];
    _segmentTitle = nil;
    [super viewDidUnload];
    
}

-(void) viewDidLoad
{
    self.isReload = YES;
    
    [super viewDidLoad];
    self.rowToAdd =-1;
    if(_hotRankMode==1){
        self.companyCurrentPage = 1;
    }else{
        self.offerCurrentPage = 1;
    }
    NSString *clickId = [NSString stringWithFormat:@"1-%@-%d-%@",self.pageId,1,self.pageId];
    [AMLogUtils appendLog:clickId];
    [self.view addSubview:self.headerView];
    
}

-(UIView*)segmentLoadingView
{
    if(!_segmentLoadingView){
        _segmentLoadingView = [[UIView alloc] initWithFrame:CGRectMake(0.0,0.0,320.0,80.0)];
        _segmentLoadingView.backgroundColor = [UIColor clearColor];
    }
    return _segmentLoadingView;
}

-(UIView*)headerView
{
    if (!_headerView) {
        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 40.0, 320.0, 40.0)];
        _headerView.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"tab_bag"]];
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        NSNumber *hotOrUpModeNumber = [defaults objectForKey:@"hotOrUpMode"];
        if(hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==1){
            mCurrentIndex = 1;
        }else{
            mCurrentIndex = 0;
        }

//        if(self.hotOrUpMode==0){
//            
//            CGSize labelSize = [@"上升榜" sizeWithFont:[UIFont boldSystemFontOfSize:14.0f]];
//            self.upButton = [[UIButton alloc]initWithFrame:CGRectMake(40, 4.0, labelSize.width+16, labelSize.height+4)];
//            [_upButton setTitle:@"上升榜" forState:UIControlStateNormal];
//            _upButton.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
//            [_upButton setBackgroundColor:[UIColor grayColor]];
//            _upButton.tag = BUTTON_UP;
//            upButtonState = YES;
//            [_headerView addSubview:_upButton];
//            
//            self.hotButton = [[UIButton alloc]initWithFrame:CGRectMake(220, 4.0, labelSize.width+16, labelSize.height+4)];
//            [_hotButton setTitle:@"热销榜" forState:UIControlStateNormal];
//            _hotButton.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
//            
//            [_hotButton setBackgroundColor:[UIColor clearColor]];
//            _hotButton.tag  = BUTTON_HOT;
//            hotButtonState = NO;
//            [_upButton addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
//            [_hotButton addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
//            [_headerView addSubview:_hotButton]; 
//            
//        }else 
            
//            if(self.hotOrUpMode==1){
        if(hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==1){
            
            CGSize labelSize = [@"上升榜" sizeWithFont:[UIFont boldSystemFontOfSize:14.0f]];
            self.upButton = [[UIButton alloc]initWithFrame:CGRectMake(40, 7.0, labelSize.width+24, labelSize.height+8)];
            [_upButton setTitle:@"上升榜" forState:UIControlStateNormal];
            _upButton.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
            _upButton.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
            [_upButton setBackgroundColor:[UIColor clearColor]];
            _upButton.tag = BUTTON_UP;
            upButtonState = NO;
            [_headerView addSubview:_upButton];
            
            self.hotButton = [[UIButton alloc]initWithFrame:CGRectMake(220, 7.0, labelSize.width+24, labelSize.height+8)];
            [_hotButton setTitle:@"热销榜" forState:UIControlStateNormal];
            _hotButton.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
            _hotButton.titleLabel.textColor = [UIColor whiteColor];
            [_hotButton setBackgroundColor:[UIColor grayColor]];
            _hotButton.tag  = BUTTON_HOT;
            hotButtonState = YES;
            [_upButton addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
            [_hotButton addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
            [_headerView addSubview:_hotButton];
            
        }else{
            CGSize labelSize = [@"上升榜" sizeWithFont:[UIFont boldSystemFontOfSize:14.0f]];
            self.upButton = [[UIButton alloc]initWithFrame:CGRectMake(40, 7.0, labelSize.width+24, labelSize.height+8)];
            [_upButton setTitle:@"上升榜" forState:UIControlStateNormal];
            _upButton.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
            _upButton.titleLabel.textColor = [UIColor whiteColor];
            [_upButton setBackgroundColor:[UIColor grayColor]];
            _upButton.tag = BUTTON_UP;
            upButtonState = YES;
            [_headerView addSubview:_upButton];
            
            self.hotButton = [[UIButton alloc]initWithFrame:CGRectMake(220, 7.0, labelSize.width+24, labelSize.height+8)];
            [_hotButton setTitle:@"热销榜" forState:UIControlStateNormal];
            _hotButton.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
            _hotButton.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
            [_hotButton setBackgroundColor:[UIColor clearColor]];
            _hotButton.tag  = BUTTON_HOT;
            hotButtonState = NO;
            [_upButton addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
            [_hotButton addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
            [_headerView addSubview:_hotButton]; 
        }
        
        
    }
    return _headerView;  
}

-(void)setHotOrUpMode:(int)hotOrUpMode
{
//    if (_hotOrUpMode==hotOrUpMode) {
//        return;
//    }
    
    _hotOrUpMode=hotOrUpMode;
    
    if (hotOrUpMode<0||hotOrUpMode>1) {
        return;
    }
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    NSNumber *hotOrUpModeNumber = [NSNumber numberWithInt:hotOrUpMode];
    [defaults setValue:hotOrUpModeNumber forKey:@"hotOrUpMode"];
    [[NSUserDefaults standardUserDefaults] synchronize];    
    
    if(_hotRankMode==1){
        self.companyTotal=0;
        self.companyCurrentPage=1;
        [self.companiesData removeAllObjects]; 
        [self.contentTable reloadData];
        [self loadObjectsFromRemoteCompany];
    }else{
        self.offerTotal=0;
        self.offerCurrentPage=1;
        [self.contentsData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemoteOffer];
    }
    
    NSLog(@"hotOrUpMode=%d",[[defaults objectForKey:@"hotOrUpMode"] intValue]);

    
}

-(void)setHotRankMode:(int)hotRankMode
{
    if (_hotRankMode==hotRankMode) {
        return;
    }
    
    _hotRankMode = hotRankMode;
    
    if (hotRankMode<0||hotRankMode>1) {
        return;
    }
     NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSNumber *hotRankModeNumber = [NSNumber numberWithInt:hotRankMode];
    [defaults setValue:hotRankModeNumber forKey:@"hotRankMode"];
    [[NSUserDefaults standardUserDefaults] synchronize];    
    
    if(_hotRankMode==1){
        self.companyTotal=0;
        self.companyCurrentPage=1;
        [self.companiesData removeAllObjects]; 
        [self.contentTable reloadData];
        [self loadObjectsFromRemoteCompany];
    }else{
        self.offerTotal=0;
        self.offerCurrentPage=1;
        [self.contentsData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemoteOffer];
    }
    
     NSLog(@"hotRankMode=%d",[[defaults objectForKey:@"hotRankMode"] intValue]);
    
}

- (void) segmentValueChanged:(int)nowIndex
{
    NSString *clickId = [NSString stringWithFormat:@"1-%@-%d-%@",self.pageId,nowIndex+1,self.pageId];
    [AMLogUtils appendLog:clickId];
    self.hotRankMode = nowIndex;
}

- (IBAction)changeState:(id)sender
{
    int index = ((UIButton *)sender).tag;
    if(index!=mCurrentIndex){
        switch (index) {
            case 0:
            {
                if(upButtonState){
                    [_upButton setBackgroundColor:[UIColor clearColor]];
                    _upButton.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    [_hotButton setBackgroundColor:[UIColor grayColor]];
                    _hotButton.titleLabel.textColor = [UIColor whiteColor];
                    upButtonState = NO;
                    hotButtonState = YES;
                    
                }else{
                    [_upButton setBackgroundColor:[UIColor grayColor]];
                    _upButton.titleLabel.textColor = [UIColor whiteColor];
                    [_hotButton setBackgroundColor:[UIColor clearColor]];
                    _hotButton.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    upButtonState = YES;
                    hotButtonState = NO;
                }
                
                self.hotOrUpMode = 0;
                
            }
                break;
            case 1:
            {
                if(!hotButtonState){
                    [_hotButton setBackgroundColor:[UIColor grayColor]];
                    _hotButton.titleLabel.textColor = [UIColor whiteColor];
                    [_upButton setBackgroundColor:[UIColor clearColor]];
                    _upButton.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    hotButtonState = YES;
                    
                    upButtonState = NO;
                }else{
                    [_hotButton setBackgroundColor:[UIColor clearColor]];
                    _hotButton.titleLabel.textColor = [UIColor whiteColor];
                    [_upButton setBackgroundColor:[UIColor grayColor]];
                    _upButton.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
                    hotButtonState = NO;
                    
                    upButtonState = YES;
                }
                self.hotOrUpMode = 1;
            }
                break;
            default:
                break;
        }   
    }
    mCurrentIndex = index;
}

-(void)viewWillAppear:(BOOL)animated
{
    if (self.isReload) {
        self.rowToAdd =-1;
        self.companyCurrentPage = 1;
        self.companyTotal = 0;
        
        self.offerCurrentPage = 1;
        self.offerTotal = 0;

       
//        self.hotRankMode=-1;
//        [self changeSegmentIndex:0];
//        self.hotRankMode=0;  
        
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        NSNumber *hotRankModeNumber = [defaults objectForKey:@"hotRankMode"];
        if(!hotRankModeNumber){
            self.hotRankMode=-1;
            [self changeSegmentIndex:0];
            self.hotRankMode=0;  
        }else{
            if([hotRankModeNumber intValue]==0){
                self.hotRankMode=-1;
                [self changeSegmentIndex:0];
                self.hotRankMode=0;  
            }else{
                self.hotRankMode=-1;
                [self changeSegmentIndex:1];
                self.hotRankMode=1;  
            }
        }
//        if(self.hotRankMode==0){
//            self.hotRankMode=-1;
//            [self changeSegmentIndex:0];
//            self.hotRankMode=0;  
//        }else if(self.hotRankMode==1){
//            self.hotRankMode=-1;
//            [self changeSegmentIndex:1];
//            self.hotRankMode=1;  
//        }
        
    }
    [super viewWillAppear:animated];
    self.isReload = NO;
}

-(NSString*)commonTableViewBackButtonTitle
{
    return @"热销排行";
}
-(NSString*)commonTableViewNavigationTitle
{
    NSString *cateTitleTotal = [NSString stringWithFormat:@"%@热销榜",self.cateTitle];
    return cateTitleTotal;
}

- (void)loadObjectsFromRemoteOffer {
    
    self.isOfferLoading = YES;
    if (self.offerCurrentPage>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.contentTable.tableFooterView = moreloadingView;
        [moreloadingView release];
    }
    
    
    //    self.isOfferLoading = YES;
    [self.view addSubview:self.segmentLoadingView];
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    //    // Register our mappings with the provider
    //	RKObjectMapping* offerMapping = [AMHotRankOfferResult sharedObjectMapping];
    //    [objectManager.mappingProvider addObjectMapping: offerMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_HOT_RANK_OFFER_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            //    loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMHotRankOfferResult class]];
            loader.objectMapping = [AMHotRankOfferResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.offersRequest;
    }];
    
    if (self.offerCurrentPage==1) {
        self.contentTable.tableFooterView = nil;
        [super loadObjectsFromRemote];
    }
}

- (void)loadObjectsFromRemoteCompany {
    
    self.isCompanyLoading = YES;
    if (self.companyCurrentPage>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.contentTable.tableFooterView = moreloadingView;
        [moreloadingView release];
    }
    
    
//    self.isCompanyLoading = YES;
    [self.view addSubview:self.segmentLoadingView];
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* companyMapping = [AMHotRankCompanyResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: companyMapping];
    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_HOT_RANK_COMPANY_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMHotRankCompanyResult class]];
            loader.objectMapping = [AMHotRankCompanyResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.companyiesRequest;
    }];    
    
    if (self.companyCurrentPage==1) {
        self.contentTable.tableFooterView = nil;
        [super loadObjectsFromRemote];
    }
}


#pragma mark RKObjectLoaderDelegate methods



- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"xxxxxojbects:%@",objects);
    
    if(self.segmentLoadingView){
      [self.segmentLoadingView removeFromSuperview];  
    }
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        if (transactionType==AMTRANSACTION_TYPE_HOTRANK_COMPANY_LIST) {
            self.isCompanyLoading = NO;
            if (self.companyCurrentPage*[self.companyiesRequest.count intValue] >= self.companyTotal) {
                self.contentTable.tableFooterView = nil;
            }
            
            if([objects count]==0){
                //            [self showNodataMessage];
                //            [self hiddenSingleLoadingView];
                [self showNodataMessage];
            }else{
                AMHotRankCompanyResult *result = (AMHotRankCompanyResult*)[objects objectAtIndex:0];
                
                if ([self.companiesData count]==0) {
                    [self.contentTable reloadData];
                }
                if(result){
                    [self.companiesData addObjectsFromArray:result.rankList];
                    self.companyTotal = [result.total intValue];   
                }else{
                    [self showNodataMessage];
                }
                self.isCompanyLoading = NO;
                [self.contentTable reloadData];
                
                if (!self.companyTotal) {
                    [self showNodataMessage];
                } else {
                    [super objectLoader:objectLoader didLoadObjects:objects];
                }
            }
        }else if(transactionType == AMTRANSACTION_TYPE_HOTRANK_OFFER_LIST){
            self.isOfferLoading = NO;
            if (self.offerCurrentPage*[self.offersRequest.pageSize intValue] >= self.offerTotal) {
                self.contentTable.tableFooterView = nil;
            }
            if([objects count]==0){
                [self showNodataMessage];
                
            }else{
                AMHotRankOfferResult *result = (AMHotRankOfferResult*)[objects objectAtIndex:0];
                
                if ([self.contentsData count]==0) {
                    [self.contentTable reloadData];
                }
                [self.contentsData addObjectsFromArray:result.offerList];
                self.offerTotal = [result.total intValue]; 
                self.isOfferLoading = NO;
                
                
                [self.contentTable reloadData];
                
                if (!self.offerTotal) {
                    [self showNodataMessage];
                } else {
                    [super objectLoader:objectLoader didLoadObjects:objects];
                }   
            }
        }
    }

}

-(void) objectLoader:(RKObjectLoader *)objectLoader didFailWithError:(NSError *)error{
//    [self.mLoadingView endLoadingView];
    
    //NSURLErrorDomain Code=-1009 "The Internet connection appears to be offline
    
    if(_hotRankMode==1){
        if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==-1009){
            if ([self.companiesData count]) {
                AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
                self.contentTable.tableFooterView = errorMessageView;
                [errorMessageView release];
            }else {
                [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
            }
        }
        self.isCompanyLoading = NO;
    }else{
        if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==-1009){
            if ([self.contentsData count]) {
                AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
                self.contentTable.tableFooterView = errorMessageView;
                [errorMessageView release];
            }else {
               [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
            }
        }
        self.isOfferLoading = NO;
    }
    
    if(self.segmentLoadingView){
        [self.segmentLoadingView removeFromSuperview];
    }
}

-(void)resetData
{   
    if(_hotRankMode==1){
        [self.companiesData removeAllObjects];  
    }else{
        [self.contentsData removeAllObjects];  
    }
    [self.contentTable reloadData];
}

#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(_hotRankMode==1){
//        if ([self.companiesData count]!=self.companyTotal) { 
//            if ([indexPath row]==[self.companiesData count])
//            {
//                return [AMMoreLoadingCell cellHeight];
//            }
//        }
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        NSNumber *hotOrUpModeNumber = [defaults objectForKey:@"hotOrUpMode"];
        if(hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==1){
             return 173; 
        }else{
            return AM_HOT_RANK_COMPANY_CELL_HEIGHT;
        }

    }else{
//        if ([self.contentsData count]!=self.offerTotal) { 
//            if ([indexPath row]==[self.contentsData count])
//            {
//                return [AMMoreLoadingCell cellHeight];
//            }
//        }
        
        return AM_HOT_RANK_OFFER_CELL_HEIGHT;
    }

}

- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    if(_hotRankMode==1){
//        if ([self.companiesData count]==0) {
//            return 0;
//        }
//        if ([self.companiesData count]==self.companyTotal) {
//            return [self.companiesData count];
//        }
//        
//        return [self.companiesData count]+1;
        return [self.companiesData count];
    }else{
//        if ([self.contentsData count]==0) {
//            return 0;
//        }
//        if ([self.contentsData count]==self.offerTotal) {
//            return [self.contentsData count];
//        }
//        
//        return [self.contentsData count]+1;
        return [self.contentsData count];
    }
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    
    if(_hotRankMode==1){
        
//        if ([self.companiesData count]!=self.companyTotal) { 
//            if ([indexPath row]==[self.companiesData count]) {
//                AMMoreLoadingCell *cell = (AMMoreLoadingCell *)[tableView 
//                                                                dequeueReusableCellWithIdentifier: [AMMoreLoadingCell cellIdentifer]];
//                if (cell == nil)  
//                {
//                    cell = [AMMoreLoadingCell createCell];
//                }
//                return cell;
//                
//            }
//        }
        
        static NSString *hotRankCompanyIdentifier = @"AMHotRankCompanyCellIdentifier ";
        
        AMHotRankCompanyCell *cell = (AMHotRankCompanyCell *)[tableView 
                                                              dequeueReusableCellWithIdentifier: hotRankCompanyIdentifier];
        if (cell == nil)  
        {
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMHotRankCompanyCell" 
                                                         owner:self options:nil];
            for (id oneObject in nib)
                if ([oneObject isKindOfClass:[AMHotRankCompanyCell class]])
                    cell = (AMHotRankCompanyCell *)oneObject;
            
            UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
            UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
            bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
            cellBackBtn.image =bkImage;
            
            cell.selectedBackgroundView = cellBackBtn;
            [cellBackBtn release]; 
            
        }
        
        NSUInteger row = [indexPath row];
        AMHotRankCompany *company = (AMHotRankCompany*)[self.companiesData objectAtIndex:row] ;
        if(row==1||row==2||row==0){
            
//            if(hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==1){
                
            cell.iconImage.frame = CGRectMake(0, 3, 18 , 15);
            cell.iconImage.backgroundColor = [UIColor clearColor];
            switch (row) {
                case 0:{
                    cell.iconImage.image = [UIImage imageNamed:@"tips_1.png"];
                }
                    break;
                
                case 1:{
                    cell.iconImage.image = [UIImage imageNamed:@"tips_2.png"];  
                }
                    break;
                case 2:{
                    cell.iconImage.image = [UIImage imageNamed:@"tips_3.png"];
                }
                    break;
                    default:
                    break;
            }
            cell.companyNameLabel.frame = CGRectMake(10, 9, 254, 21);
            cell.companyNameLabel.text = @"";
            cell.companyNameLabel.backgroundColor = [UIColor clearColor];
            cell.companyNameLastLabel.frame = CGRectMake(29, 0, 254, 21);
            [cell.companyNameLabel addSubview:cell.iconImage];
            [cell.companyNameLabel addSubview:cell.companyNameLastLabel]; 
            cell.iconImage.hidden = NO;
        }else{
            cell.iconImage.hidden = YES;
            cell.companyNameLabel.text = @"";
            cell.companyNameLabel.backgroundColor = [UIColor clearColor];
            cell.companyNameLastLabel.frame = CGRectMake(10, 9, 283, 21);
            
        }
        cell.companyNameLastLabel.text=[NSString stringWithFormat:@"%@",company.companyName];
        cell.cityNameLabel.text = [NSString stringWithFormat:@"%@",company.cityName];
        cell.companyPaymentGMVLabel.text = [NSString stringWithFormat:@"￥%@",company.companyPaymentGMV];
        
        
        //    [self.objMan manage:cell.registerImage];*/
        cell.bkImage.layer.masksToBounds = YES;
        cell.bkImage.layer.cornerRadius= 2.0;
        [cell.logoImage1 setImage:nil];
        
        
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        NSNumber *hotOrUpModeNumber = [defaults objectForKey:@"hotOrUpMode"];
//        if(!hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==0){
//            _companyiesRequest.listMode = @"U";
//        }else{
//            _companyiesRequest.listMode = @"H";
//        }

        
//        if(_hotOrUpMode==0){
        
        cell.logoImage1.hidden = YES;
        cell.logoImage2.hidden = YES;
        cell.logoImage3.hidden = YES;
        cell.logoImage4.hidden = YES;
        
       if(hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==1){
            cell.rankRiseNumFrontLabel.hidden = YES;
            cell.rankRiseNumLabel.hidden = YES;
            cell.satisfiedRateFrontLabel.frame = CGRectMake(10, 81, 84 , 18);
            cell.satisfiedRateLabel.frame = CGRectMake(91, 81, 230, 15);
            cell.satisfiedRateLabel.text = [NSString stringWithFormat:@"%2g%%",[company.satisfiedRate doubleValue]];
           
            if([company.offerPicUrl count ]>=1){
                cell.logoImage1.hidden = NO;
                NSString *url1 = [company.offerPicUrl objectAtIndex:0];
                cell.logoImage1.url = [NSURL URLWithString:url1];
                [self.objMan manage:cell.logoImage1];
                cell.logoImage1.layer.masksToBounds = YES;
                cell.logoImage1.layer.cornerRadius= 10.0;
                cell.logoImage1.frame =CGRectMake(10, 105, 60 , 60);   
            }
            
            if([company.offerPicUrl count ]>=2){
                cell.logoImage2.hidden = NO;
                NSString *url2 = [company.offerPicUrl objectAtIndex:1];
                cell.logoImage2.url = [NSURL URLWithString:url2];
                [self.objMan manage:cell.logoImage2];
                cell.logoImage2.layer.masksToBounds = YES;
                cell.logoImage2.layer.cornerRadius= 10.0;
                cell.logoImage2.frame =CGRectMake(90, 105, 60 , 60);   
            }
            
            if([company.offerPicUrl count ]>=3){
                cell.logoImage3.hidden = NO;
                NSString *url3 = [company.offerPicUrl objectAtIndex:2];
                cell.logoImage3.url = [NSURL URLWithString:url3];
                [self.objMan manage:cell.logoImage3];
                cell.logoImage3.layer.masksToBounds = YES;
                cell.logoImage3.layer.cornerRadius= 10.0;
                cell.logoImage3.frame =CGRectMake(170, 105, 60 , 60);
            }
            
            if([company.offerPicUrl count ]>=4){
                cell.logoImage4.hidden = NO;
                NSString *url4 = [company.offerPicUrl objectAtIndex:3];
                cell.logoImage4.url = [NSURL URLWithString:url4];
                [self.objMan manage:cell.logoImage4];
                cell.logoImage4.layer.masksToBounds = YES;
                cell.logoImage4.layer.cornerRadius= 10.0;
                cell.logoImage4.frame =CGRectMake(250, 105, 60 , 60);   
            }
        }  else{
            cell.satisfiedRateLabel.text = [NSString stringWithFormat:@"%2g%%",[company.satisfiedRate doubleValue]];
            cell.rankRiseNumLabel.text = [NSString stringWithFormat:@"%@",company.rankRiseNum];
            if([company.offerPicUrl count ]>=1){
                cell.logoImage1.hidden = NO;
                NSString *url1 = [company.offerPicUrl objectAtIndex:0];
                cell.logoImage1.url = [NSURL URLWithString:url1];
                [self.objMan manage:cell.logoImage1];
                cell.logoImage1.layer.masksToBounds = YES;
                cell.logoImage1.layer.cornerRadius= 10.0;
                cell.logoImage1.frame =CGRectMake(10, 127, 60 , 60);   
            }
            
            if([company.offerPicUrl count ]>=2){
                cell.logoImage2.hidden = NO;
                NSString *url2 = [company.offerPicUrl objectAtIndex:1];
                cell.logoImage2.url = [NSURL URLWithString:url2];
                [self.objMan manage:cell.logoImage2];
                cell.logoImage2.layer.masksToBounds = YES;
                cell.logoImage2.layer.cornerRadius= 10.0;
                cell.logoImage2.frame =CGRectMake(90, 127, 60 , 60);   
            }
            
            if([company.offerPicUrl count ]>=3){
                cell.logoImage3.hidden = NO;
                NSString *url3 = [company.offerPicUrl objectAtIndex:2];
                cell.logoImage3.url = [NSURL URLWithString:url3];
                [self.objMan manage:cell.logoImage3];
                cell.logoImage3.layer.masksToBounds = YES;
                cell.logoImage3.layer.cornerRadius= 10.0;
                cell.logoImage3.frame =CGRectMake(170, 127, 60 , 60);
            }
            
            if([company.offerPicUrl count ]>=4){
                cell.logoImage4.hidden = NO;
                NSString *url4 = [company.offerPicUrl objectAtIndex:3];
                cell.logoImage4.url = [NSURL URLWithString:url4];
                [self.objMan manage:cell.logoImage4];
                cell.logoImage4.layer.masksToBounds = YES;
                cell.logoImage4.layer.cornerRadius= 10.0;
                cell.logoImage4.frame =CGRectMake(250, 127, 60 , 60);   
            }
        }        

        return cell;

    }else {
//        if ([self.contentsData count]!=self.offerTotal) { 
//            if ([indexPath row]==[self.contentsData count]) {
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
        
        static NSString *hotRankOfferIdentifier = @"AMHotRankOfferCellIdentifier ";
        
        AMHotRankOfferCell *cell = (AMHotRankOfferCell *)[tableView 
                                                          dequeueReusableCellWithIdentifier: hotRankOfferIdentifier];
        if (cell == nil)  
        {
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMHotRankOfferCell" 
                                                         owner:self options:nil];
            for (id oneObject in nib)
                if ([oneObject isKindOfClass:[AMHotRankOfferCell class]])
                    cell = (AMHotRankOfferCell *)oneObject;
            
            UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
            UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
            bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
            cellBackBtn.image =bkImage;
            
            cell.selectedBackgroundView = cellBackBtn;
            [cellBackBtn release]; 
            
        }
        
        NSUInteger row = [indexPath row];
        AMHotRankOffer *offer = (AMHotRankOffer*)[self.contentsData objectAtIndex:row] ;
        
        
        cell.subjectLabel.text = [NSString stringWithFormat:@"%@",offer.subject];
        cell.offerPaymentGMVLabel.text = [NSString stringWithFormat:@"%@",offer.offerPaymentGMV];
//        cell.tradeQuantityLabel.text = [NSString stringWithFormat:@"交易量 : %@ 件",offer.tradeQuantity];
        
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        NSNumber *hotOrUpModeNumber = [defaults objectForKey:@"hotOrUpMode"];
        if(hotOrUpModeNumber&&[hotOrUpModeNumber intValue]==1){
            cell.rankingChangeLabel.hidden = YES;
            cell.rankingChangeFrontLabel.text = [NSString stringWithFormat:@"交易量 : %@%@",offer.tradeQuantity,offer.unit]; 
        }else{
            cell.rankingChangeLabel.text = [NSString stringWithFormat:@"%@↑",offer.rankRiseNum];
        }
        
        
//        if(_hotOrUpMode==0){
//            cell.rankingChangeLabel.text = [NSString stringWithFormat:@"%@↑",offer.rankRiseNum];
//        }else{
//            cell.rankingChangeLabel.hidden = YES;
//            cell.rankingChangeFrontLabel.text = [NSString stringWithFormat:@"交易量 : %@%@",offer.tradeQuantity,offer.unit];
//        }
        cell.rankingChangeLabel.text = [NSString stringWithFormat:@"%@↑",offer.rankRiseNum];
        cell.priceLabel.text = [NSString stringWithFormat:@"产品价格 : ¥ %2g 元",[offer.price.amount doubleValue]];
        //    [self.objMan manage:cell.registerImage];*/
//        cell.bkImage.layer.masksToBounds = YES;
//        cell.bkImage.layer.cornerRadius= 2.0;
        [cell.listImg setImage:nil];
        NSString *listImg = [NSString stringWithFormat:@"%@",offer.listImgUrl];
        cell.listImg.url = [NSURL URLWithString:listImg];
        [self.objMan manage:cell.listImg];
        cell.listImg.layer.masksToBounds = YES;
//        cell.listImg.layer.cornerRadius= 10.0;
//        cell.listImg.layer.cornerRadius= 2.0;
        //imageView.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageWidth);
        cell.listImg.frame =CGRectMake(13, 15, 71 , 71);
        
        if(row==1||row==2||row==0){
            cell.iconImage.frame = CGRectMake(10, 12, 18, 15);
            cell.iconImage.backgroundColor = [UIColor clearColor];
            switch (row) {
                case 0:{
                    cell.iconImage.image = [UIImage imageNamed:@"tips_1.png"];
                }
                    break;
                    
                case 1:{
                    cell.iconImage.image = [UIImage imageNamed:@"tips_2.png"];  
                }
                    break;
                case 2:{
                    cell.iconImage.image = [UIImage imageNamed:@"tips_3.png"];
                }
                    break;
                default:
                    break;
            }

//            [cell.listImg addSubview:cell.iconImage];
//            [cell.listImg insertSubview:cell.iconImage belowSubview:cell.listImg];
            [cell insertSubview:cell.iconImage aboveSubview:cell.listImg];
            cell.iconImage.hidden = NO;
        }else{
            cell.iconImage.hidden = YES;
        }
        return cell;
    }

}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    
    NSUInteger row = [indexPath row];
    if(_hotRankMode==1){
        if ([self.companiesData count]!=self.companyTotal) { 
            if ([indexPath row]==[self.companiesData count]) {
                return;
            }
        }   
        AMHotRankCompany *data = (AMHotRankCompany*)[self.companiesData objectAtIndex:row] ;
        //打点，公司的item定义为4
        NSString *companyClickId = [NSString stringWithFormat:@"1-%@-4-%@",self.pageId,PAGE_FIVE];
        [AMLogUtils appendLog:companyClickId];
//        NSString *companyID = [NSString stringWithFormat:@"%@",data.sellerCompanyId];
        AMCompanyTabViewController * companyTabViewController = [[AMCompanyTabViewController alloc] initWithMemberId:data.sellerMemberId companyName:data.companyName preViewName:nil];
        [self.navigationController pushViewController:companyTabViewController animated:YES];
        [companyTabViewController release];
    }else{
        if ([self.contentsData count]!=self.offerTotal) { 
            if ([indexPath row]==[self.contentsData count]) {
                return;
            }
        } 
        AMHotRankOffer *data = (AMHotRankOffer*)[self.contentsData objectAtIndex:row] ;
        //打点，产品的item定义为3
        NSString *offerClickId = [NSString stringWithFormat:@"1-%@-3-%@",self.pageId,PAGE_THREE];
        [AMLogUtils appendLog:offerClickId];
        NSString *offerIdFinal = [NSString stringWithFormat:@"%@",data.offerId];
        AMOfferTabViewController * controller = [[AMOfferTabViewController alloc] initWithOfferId:offerIdFinal offerName:data.subject preViewName:nil];  
        controller.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:controller animated:YES]; 
        [controller release];
    }
    
    [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
} 


- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 30.0) {
        if(_hotRankMode==1){
            if ((self.companyCurrentPage*[self.companyiesRequest.page intValue])<self.companyTotal)
            {
                if (!self.isCompanyLoading) {
                    self.companyCurrentPage++;
                    [self loadObjectsFromRemoteCompany];   
                }
            }  
        }else {
            if (self.offerCurrentPage * [self.offersRequest.pageSize intValue]<self.offerTotal)
            {
                if (!self.isOfferLoading) {
                    self.offerCurrentPage++;
                        [self loadObjectsFromRemoteOffer];   
                    
                }
            }  
        }    
        
    }
}

@end



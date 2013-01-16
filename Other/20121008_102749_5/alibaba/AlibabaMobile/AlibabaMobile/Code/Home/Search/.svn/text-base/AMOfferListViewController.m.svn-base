//
//  AMOfferListViewController.m
//  AlibabaMobile
//
//  Created by  on 11-12-21.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#import <QuartzCore/QuartzCore.h>
#import "AMOfferListViewController.h"
#import "AMOfferResult.h"
#import "AMOffer.h"
#import "AMMemberCredit.h"
#import "AMMoney.h"
#import "AMImage.h"
#import "AMCurrency.h"
#import "AMCUDResult.h"
#import "AMMoreLoadingCell.h"
#import "ConstDef.h"
#import "AliTableViewCellOfferDetail.h"

#import "AMOfferTabViewController.h"
#import "UIHelp.h"
#import "AliNavigationButton.h"
#import "AMMoreLoadingCell.h"
#import "AMOfferRequest.h"
#import "AliToastView.h"
#import "AMAppDelegate.h"
#import "LoginToken.h"
#import "AMErrorMessageView.h"
#import "AMMoreLoadingView.h"
@interface AMOfferListViewController() 

//filter start
@property (retain, nonatomic) AMHotArea*area;
@property (retain,nonatomic)CLLocation *startingPoint;
@property (retain,nonatomic)NSString *distance;

@property (nonatomic)int regionFilterSegmentSelected;
@property (nonatomic)NSUInteger regionFilterSelectedItem;
@property (nonatomic)NSUInteger aroundFilterSelectedItem;
//filter end



@property (readwrite) int total;
@property (readwrite) int currentPage;
@property (readwrite) BOOL isLoading;
@property (retain,nonatomic) AMOfferRequest *offerListRequset;
@property (nonatomic, retain) NSMutableArray* resultData;
@property (nonatomic,retain) HJObjManager *objMan;

@property (nonatomic, retain) NSArray* segmentTitle;
@property (nonatomic, retain) NSArray* filterButtons;

@property (readwrite,nonatomic)int searchMode;
-(void)loadObjectsFromRemote;
@end

@implementation AMOfferListViewController
@synthesize resultView = _resultView;
@synthesize contentTable=_contentTable;
@synthesize keyWords=_keyWords;
@synthesize catId=_catId;
@synthesize catName=_catName;
@synthesize parentTitle=_parentTitle;
//@synthesize navigationTitle=_navigationTitle;
@synthesize total=_total;
@synthesize currentPage=_currentPage;
@synthesize isLoading=_isLoading;
@synthesize offerListRequset=_offerListRequset;
@synthesize resultData=_resultData;
@synthesize objMan=_objMan;
@synthesize regionFilterSelectedItem=_regionFilterSelectedItem;
@synthesize regionFilterSegmentSelected=_regionFilterSegmentSelected;

@synthesize searchMode=_searchMode;
@synthesize isReload = _isReload;
@synthesize parentCatId=_parentCatId;
@synthesize area=_area;
@synthesize startingPoint=_startingPoint;
@synthesize distance=_distance;
@synthesize segmentTitle=_segmentTitle;
@synthesize categoryFilterSelectedItem=_categoryFilterSelectedItem;
@synthesize aroundFilterSelectedItem=_aroundFilterSelectedItem;
@synthesize filterButtons=_filterButtons;
@synthesize navigationCategoryId = _navigationCategoryId;
- (void)dealloc {
    [_contentTable release];
    [_keyWords release];
    [_catId release];
    [_catName release];
    [_parentTitle release];
    [_offerListRequset release];
    [_resultData release];
    [_objMan release];
    [_parentCatId release];
    [_area release];
    [_startingPoint release];
    [_distance release];
    [_segmentTitle release];
    
    [_resultView release];
    [_filterButtons release];
    [super dealloc];
}
-(NSArray*)filterButtons
{
    if (!_filterButtons) {
        _filterButtons = [[NSArray alloc]initWithObjects:@"周边", @"地区",@"类目",nil];
    }
    return _filterButtons;
}
-(AMOfferRequest*)offerListRequset
{
    if (_offerListRequset==nil) {
        _offerListRequset = [[AMOfferRequest alloc] init];
    }
    if (self.keyWords!=nil&&self.keyWords.length!=0) {
        _offerListRequset.keywords=self.keyWords;
        _offerListRequset.categoryId=nil;
        _offerListRequset.categoryName=nil;
        if (self.catId!=nil) {
            _offerListRequset.categoryId=self.catId;
        }
        if (self.catName!=nil) {
            _offerListRequset.categoryName=self.catName;
        }
    }
    else
    {
        _offerListRequset.keywords=nil;
        _offerListRequset.categoryId=self.catId;
        _offerListRequset.categoryName=self.catName;
    }
    _offerListRequset.beginPage=[NSNumber numberWithInt:self.currentPage];
    _offerListRequset.pageSize= [NSNumber numberWithInt:9];
    _offerListRequset.transactionType = AMTRANSACTION_TYPE_SEZRCH_OFFER;
    switch (self.searchMode) {
        case 0://default
        {
            _offerListRequset.pop=[NSNumber numberWithBool:NO];
            _offerListRequset.descendOrder = [NSNumber numberWithBool:NO];
            _offerListRequset.sortType=nil;
        }
            break;
        case 1://popsort
        {
            _offerListRequset.pop=[NSNumber numberWithBool:YES];
            _offerListRequset.descendOrder = [NSNumber numberWithBool:NO];
            _offerListRequset.sortType=nil;
        }
            break;
        case 2://salesort
        {
            _offerListRequset.pop=[NSNumber numberWithBool:NO];
            _offerListRequset.descendOrder = [NSNumber numberWithBool:YES];
            _offerListRequset.sortType=AM_SORT_TYPE_BOOKED;
        }
            break;
        default:
            break;
    }
    _offerListRequset.distance=nil;
    _offerListRequset.latitude=nil;
    _offerListRequset.longitude = nil;
    _offerListRequset.city = nil;
    _offerListRequset.province = nil;
    if (self.startingPoint!=nil) {
        _offerListRequset.distance = self.distance;
        _offerListRequset.latitude = [NSString stringWithFormat:@"%f",self.startingPoint.coordinate.latitude];
        _offerListRequset.longitude = [NSString stringWithFormat:@"%f",self.startingPoint.coordinate.longitude];
        
    }
    else
    {
       if (self.area!=nil) 
       {
           if (self.area.province!=nil) {
               _offerListRequset.province= self.area.province;
           }
        
           if(self.area.city!=nil) 
           {
               _offerListRequset.city = self.area.city;
           }
        
       }
    }
    
    AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
    //注意。。这俩字段不太一样啊！不要看错。。
    _offerListRequset.clientId = appDelegate.terminateId;
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] > 3){
        _offerListRequset.loginId = loginUserName;
    }else {
        _offerListRequset.loginId = nil;
    }
    if (self.navigationCategoryId) {
        _offerListRequset.navigationCategoryId = self.navigationCategoryId;
    }
    
    return _offerListRequset;
}

-(NSMutableArray*)resultData
{
    
    if (_resultData==nil) {
        _resultData = [[NSMutableArray alloc] init];
    }
    return _resultData;
}
-(NSMutableArray*)segment
{
    
    if (_resultData==nil) {
        _resultData = [[NSMutableArray alloc] init];
    }
    return _resultData;
}
-(CGFloat)segmentStartY
{
    return 25.0;
}
-(NSArray*)segmentTitle
{
    if (!_segmentTitle) {
        _segmentTitle = [[NSArray alloc]initWithObjects:@"默认",@"人气",@"销量",nil];
    }
    return _segmentTitle;
}

-(NSArray*)commonTableViewSegmentTitle
{
    return self.segmentTitle;
}


-(void)setSearchMode:(int)searchMode
{
    if (_searchMode==searchMode) {
        return;
    }
    
    _searchMode = searchMode;
       
    if (searchMode<0||searchMode>2) {
        return;
    }
    [self.resultData removeAllObjects];
    [self.contentTable reloadData];
    self.total=0;
    self.currentPage=1;//默认是从第一页开始的，修复bug
    self.contentTable.tableFooterView = nil;
    [self loadObjectsFromRemote];

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

- (void)viewDidUnload {
    [self setContentTable:nil];
    [self setResultView:nil];
    //_keyWords = nil;
    //_catId = nil;
    //_catName =nil;
    //_parentTitle = nil;
    //_parentCatId = nil;
    [_offerListRequset release];
    _offerListRequset = nil;
    [_resultData release];
    _resultData = nil;
    [_objMan release];
    _objMan = nil;
    [_filterButtons release];
    _filterButtons = nil;
    self.area =nil;
    self.startingPoint =nil;
    self.distance = nil;
    [_segmentTitle release];
    _segmentTitle =nil;
    
    [super viewDidUnload];
}


-(void)viewDidLoad
{
    
    self.currentPage=1;
    self.total=0;
    self.searchMode=-1;
    [self changeSegmentIndex:0];
    self.searchMode=0;

    self.contentTable.favDelegate = self;
    [super viewDidLoad];
   
}

-(NSString*)commonTableViewBackButtonTitle
{      
    return self.parentTitle;
}

-(void)entryCategoryFilter
{
    AliCategoryFilter *chooser = [[[AliCategoryFilter alloc] initWithNibName:@"AliCategoryFilter" bundle:nil] autorelease];
    chooser.delegate = self;
    if (self.keyWords==nil) {
        chooser.parentTitle =  self.navigationItem.title ; 
        chooser.keyWords = nil;
        chooser.catId = self.parentCatId;
        chooser.selectedItem = self.categoryFilterSelectedItem;
        chooser.catName = self.catName;
    }
    else
    {
        chooser.parentTitle = self.keyWords;
        chooser.keyWords = self.keyWords;
        chooser.selectedItem = self.categoryFilterSelectedItem;
    }
    chooser.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:chooser animated:YES]; 
}
-(void)entryRegionFilter
{
    AliRegionFilter *chooser = [[[AliRegionFilter alloc] initWithNibName:@"AliRegionFilter" bundle:nil] autorelease];
    chooser.delegate = self;
    if (self.keyWords==nil) {
        chooser.parentTitle =  self.navigationItem.title ; 
    }
    else
    {
        chooser.parentTitle = self.keyWords;
    }
    chooser.lastSegmentSelected = self.regionFilterSegmentSelected;
    chooser.selectedItem = self.regionFilterSelectedItem;
    chooser.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:chooser animated:YES]; 
}
-(void)entryAroundFilter
{
    AliAroundFilter *chooser = [[[AliAroundFilter alloc] initWithNibName:@"AliAroundFilter" bundle:nil] autorelease];
    chooser.delegate = self;
    chooser.selectedItem = self.aroundFilterSelectedItem;
    if (self.keyWords==nil) {
        chooser.parentTitle =  self.navigationItem.title ; 
        chooser.selectedItem = self.aroundFilterSelectedItem;
        
    }
    else
    {
        chooser.parentTitle = self.keyWords;
        chooser.selectedItem = self.aroundFilterSelectedItem;
    }

    chooser.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:chooser animated:YES];  
}
- (void) commonTableViewOptionButtonClick
{
    [self entryRegionFilter];
}

-(NSArray*)commonTableViewRightButtonTitles
{
    return self.filterButtons;
    
}
- (void) segmentValueChanged:(int)nowIndex
{
    switch (nowIndex) {
        case 0:
            [AMLogUtils appendLog: APP_PRD_LIST_EIGHT]; 
            break;
        case 1:
            [AMLogUtils appendLog: APP_PRD_LIST_NINE]; 
            break;
        case 2:
            [AMLogUtils appendLog: APP_PRD_LIST_TEN]; 
            break;
        default:
            break;
    }
      
    self.searchMode = nowIndex;
}

- (void)loadObjectsFromRemote {
    self.isLoading = YES;
    if (self.currentPage>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.contentTable.tableFooterView = moreloadingView;
        [moreloadingView release];
    }else {
        self.contentTable.tableFooterView = nil;
        [self.mLoadingView showLoadingView];
    }
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* offerResultMapping = [AMOfferResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: offerResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SEARCH_OFFER usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMOfferResult class]];
            loader.objectMapping = [AMOfferResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.offerListRequset;
    }];
//    [super loadObjectsFromRemote];
}
#pragma mark RKObjectLoaderDelegate methods


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {

    AMOfferResult *result = (AMOfferResult*)[objects objectAtIndex:0];
    if ([self.resultData count]==0) {
        [self.contentTable reloadData];
    }
    [self.resultData addObjectsFromArray:result.offerList];
    self.total = [result.total intValue];
 
    NSString * preTitle = [NSString stringWithFormat:@"共搜到"];
    NSString * Title = [NSString stringWithFormat:@"%d",[result.total intValue]];
    [self.resultView setupData:Title pre:preTitle suf:@"件产品"];
    self.isLoading = NO;
    if (self.currentPage*[self.offerListRequset.pageSize intValue] >= self.total) {
        self.contentTable.tableFooterView = nil;
    }
//    self.contentTable.tableFooterView = nil;
    [self.contentTable reloadData];
    if (!self.total) {
        [self showNodataMessage];
    }
    else {
        [super objectLoader:objectLoader didLoadObjects:objects];
    }
}

- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"didFailLoadWithError: %@", error);   
    
}
-(void)objectLoader:(RKObjectLoader *)objectLoader didFailWithError:(NSError *)error{
    [self.mLoadingView endLoadingView];
    //NSURLErrorDomain Code=-1009 "The Internet connection appears to be offline
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline){
        if ([self.resultData count]) {
            AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
            self.contentTable.tableFooterView = errorMessageView;
            [errorMessageView release];
            self.currentPage--;
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        
    }
    self.isLoading = NO;
//    if (self.currentPage*[self.offerListRequset.pageSize intValue] >= self.total) {
//        self.contentTable.tableFooterView = nil;
//    }
}
#pragma table data source

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    if ([self.resultData count]!=self.total) { 
//        if ([indexPath row]==[self.resultData count])
//        {
//            return [AMMoreLoadingCell cellHeight];
//        }
//    }
    return [AliTableViewCellOfferDetail cellHeight];
    
}
- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section {
    
//    if ([self.resultData count]==0) {
//        return 0;
//    }
//    if ([self.resultData count]==self.total) {
//        return [self.resultData count];
//    }
//   	
//    return [self.resultData count]+1;
    return [self.resultData count];
}
- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
//    if ([self.resultData count]!=self.total) { 
//        if ([indexPath row]==[self.resultData count]) {
//            AMMoreLoadingCell *cell = (AMMoreLoadingCell *)[tableView 
//                                                            dequeueReusableCellWithIdentifier: [AMMoreLoadingCell cellIdentifer]];
//            if (cell == nil)  
//            {
//                cell = [AMMoreLoadingCell createCell];
//            }
//            return cell;
// 
//        }
//    }
    AliTableViewCellOfferDetail *cell = (AliTableViewCellOfferDetail *)[tableView 
     
                                                dequeueReusableCellWithIdentifier: [AliTableViewCellOfferDetail cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellOfferDetail createCell];
    }
    
    NSUInteger row = [indexPath row];
    AMOffer *offer = (AMOffer*)[self.resultData objectAtIndex:row] ;
    NSLog(@"offer objects: %@", offer);    
    [cell cellSetData:cell amOffer:offer];
    [self.objMan manage:cell.icon];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    
    NSUInteger row = [indexPath row];
    if ([self.resultData count]!=self.total) { 
        if ([indexPath row]==[self.resultData count]) {
            return;
        }
    } 
    [AMLogUtils appendLog: APP_PRD_LIST_SIX];
    AMOffer *data = (AMOffer*)[self.resultData objectAtIndex:row] ;
    AMOfferTabViewController * controller = [[AMOfferTabViewController alloc] initWithOfferId:[data.offerId stringValue] offerName:data.subject preViewName:nil];
    
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES]; 
    [controller release];
    [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
} 
//- (void)scrollViewDidScroll: (UIScrollView*)scroll {
//    [self.contentTable scrollViewDidScroll:scroll callback:^{
//        if ([self.resultData count]!=self.total)
//        {
//        if (!self.isLoading) {
//            self.currentPage++;
//            [AMLogUtils appendLog: APP_OFFER_NEXT_ONE]; 
//            [self loadObjectsFromRemote];
//        }
//        }
//        
//    }];
//}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 10.0) {
        if (!self.isLoading) {
            if(self.currentPage*[self.offerListRequset.pageSize intValue] < self.total) {
                    self.currentPage++;
                    [AMLogUtils appendLog: APP_OFFER_NEXT_ONE]; 
                    [self loadObjectsFromRemote];
//                if (self.currentPage*[self.offerListRequset.pageSize intValue] >= self.total) {
//                    self.contentTable.tableFooterView = nil;
//                }
            } 
        }
    }
}
-(AMOffer*)AliTableView:(AliTableView*)table addOfferToFav:(NSIndexPath*)indexPath
{
    if ([self.resultData count]!=self.total) { 
        if ([indexPath row]==[self.resultData count]) {
            return nil;
        }
    } 
    NSUInteger row = [indexPath row];
    if (row>=[self.resultData count]) {
        return nil;
    }
    else {
        return (AMOffer*)[self.resultData objectAtIndex:row ] ;
    }

}

-(void)AliCategoryFilter:(NSString*)catId catName:(NSString *)catName selectedItem:(NSUInteger)selectedItem
{
    if (self.categoryFilterSelectedItem != selectedItem) {
    
        if (catId) {
            [AMLogUtils appendLog: APP_PRD_LIST_CHILD_FOUR];    
        }
        else {
            [AMLogUtils appendLog: APP_PRD_LIST_FOUR]; 
        }
      
        self.categoryFilterSelectedItem = selectedItem;
        self.catId = catId;
        self.catName = catName;
        self.currentPage=1;
        self.total=0;
        [self.resultData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemote];

    }
}
-(void)AliRegionFilter:(AMHotArea*)area segment:(int)segmentSelected selectedItem:(NSUInteger)selectedItem
{
    if (self.regionFilterSegmentSelected!=segmentSelected||self.regionFilterSelectedItem != selectedItem) {
        if (area) {
            [AMLogUtils appendLog: APP_PRD_LIST_CHILD_FIVE]; 
        }
        else {
            [AMLogUtils appendLog: APP_PRD_LIST_FIVE]; 
        }
        self.regionFilterSegmentSelected = segmentSelected;
        self.regionFilterSelectedItem = selectedItem;
        self.startingPoint=nil;
        self.aroundFilterSelectedItem = 0;
        self.area = area;
        self.currentPage=1;
        self.total=0;
        [self.resultData removeAllObjects];
        //当与contentTable关联的数据resultData更新时记得reloadData 不然会造成contentTable内的数据为空时还调用table绘制的函数！！切记！！ christ.yuj
        [self.contentTable reloadData];
        [self loadObjectsFromRemote];
    }
}
-(void)AliAroundFilter:(CLLocation *)location distance:(NSString *)distance selectedItem:(NSUInteger)selectedItem
{
    if (self.aroundFilterSelectedItem != selectedItem) {
        self.area = nil;
        self.regionFilterSelectedItem = 0;
        self.startingPoint = location;
        self.distance = distance;
        self.aroundFilterSelectedItem = selectedItem;
        self.currentPage=1;
        self.total=0;
        [self.resultData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemote];
    }
}
-(void)AliRightBarButtonItem:(NSInteger)selectedButton
{
    switch (selectedButton) {
        case 0:
            [self entryAroundFilter];
            break;
        case 1:
            [self entryRegionFilter];
            break;
        case 2:
            [self entryCategoryFilter];
            break;
        default:
            break;
    }
}
@end

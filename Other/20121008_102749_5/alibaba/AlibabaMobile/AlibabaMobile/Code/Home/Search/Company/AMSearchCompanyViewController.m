//
//  AMSearchCompanyViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSearchCompanyViewController.h"
#import "AMCompanyResult.h"
#import "AMCompany.h"
#import "AMMemberCredit.h"
#import "ConstDef.h"
#import "NSAttributedString+HTML.h"
#import "AMMoreLoadingCell.h"
#import "AMCompanyTabViewController.h"
#import "UIHelp.h"
#import "LoginToken.h"
#import "AMIMViewController.h"
#import "AMCUDResult.h"
#import "AliToastView.h"
#import "AMCompanyRequest.h"
#import "HJObjManager.h"
#import "AliTableViewCellCompanyDetail.h"
#import "AMFavoriteRequest.h"
#import "AMErrorMessageView.h"
#import "AMMoreLoadingView.h"
@interface AMSearchCompanyViewController()
//filter start
@property (nonatomic,retain) NSString *bizType;
@property (retain, nonatomic) AMHotArea*area;
@property (retain,nonatomic)CLLocation *startingPoint;
@property (retain,nonatomic)NSString *distance;
@property (nonatomic)int regionFilterSegmentSelected;
@property (nonatomic)NSUInteger regionFilterSelectedItem;
@property (nonatomic)NSUInteger aroundFilterSelectedItem;
@property (nonatomic)NSUInteger bizTypeFilterSelectedItem;
//filter end


@property (readwrite) int total;
@property (readwrite) int currentPage;
@property (readwrite) BOOL isLoading;
@property (nonatomic,retain) AMCompanyRequest*request;
@property (nonatomic, retain) NSMutableArray* resultData;
@property (nonatomic, retain) HJObjManager*objMan;
@property (nonatomic, retain) NSArray* searchBizModel;
@property (nonatomic, retain) NSArray* searchBizType;
@property (nonatomic, retain) NSArray* filterButtons;
@end



@implementation AMSearchCompanyViewController
@synthesize regionFilterSegmentSelected=_regionFilterSegmentSelected;
@synthesize regionFilterSelectedItem=_regionFilterSelectedItem;
@synthesize aroundFilterSelectedItem = _aroundFilterSelectedItem;
@synthesize bizTypeFilterSelectedItem=_bizTypeFilterSelectedItem;
@synthesize resultView = _resultView;
@synthesize contentTable=_contentTable;
@synthesize keyWords=_keyWords;
@synthesize total=_total;
@synthesize currentPage=_currentPage;
@synthesize isLoading=_isLoading;
@synthesize request=_request;
@synthesize resultData=_resultData;
@synthesize objMan=_objMan;
@synthesize searchBizModel=_searchBizModel;
@synthesize bizType=_bizType;
@synthesize area=_area;
@synthesize startingPoint=_startingPoint;
@synthesize distance=_distance;
@synthesize isReload=_isReload;
@synthesize searchBizType = _searchBizType;
@synthesize parentTitle=_parentTitle;
@synthesize categoryId=_categoryId;
@synthesize filterButtons=_filterButtons;
- (void)dealloc {
    [_contentTable release];
    [_request release];
    [_objMan release];
    [_searchBizModel release];
    [_bizType release];
    [_area release];
    [_startingPoint release];
    [_distance release];
    [_searchBizType release];
    [_parentTitle release];
    [_categoryId release];
    [_resultView release];
    [super dealloc];
}

-(AMCompanyRequest*)request
{
    if (!_request) {
        _request = [[AMCompanyRequest alloc] init];
             
        _request.pageSize= [NSNumber numberWithInt:9];

    }
    if (self.keyWords) {
        _request.keywords=self.keyWords;
        
        _request.categoryId=nil;
    }
    else {
        _request.keywords=nil;
        _request.categoryId=self.categoryId;
    }

    if (!self.bizType) {
        _request.bizType=nil;
    }
    else
    {
        _request.bizType = [self.searchBizType objectAtIndex: [self.searchBizModel indexOfObject:self.bizType]];
        
    }

    _request.distance=nil;
    _request.latitude=nil;
    _request.longitude = nil;
    _request.city = nil;
    _request.province = nil;
    if (self.startingPoint!=nil) {
        _request.distance = self.distance;
        _request.latitude = [NSString stringWithFormat:@"%f",self.startingPoint.coordinate.latitude];
        _request.longitude = [NSString stringWithFormat:@"%f",self.startingPoint.coordinate.longitude];
        
    }
    else
    {
        if (self.area!=nil) 
        {
            if (self.area.province!=nil) {
                _request.province= self.area.province;
            }
            
            if(self.area.city!=nil) 
            {
                _request.city = self.area.city;
            }
            
        }
    }
    NSLog(@"%@---%@",_request.keywords,_request.bizType);
     _request.beginPage=[NSNumber numberWithInt:self.currentPage];
    return _request;
}

-(NSMutableArray*)resultData
{
    
    if (_resultData==nil) {
        _resultData = [[NSMutableArray alloc] init];
    }
    return _resultData;
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

-(NSArray*)searchBizModel
{
    if (!_searchBizModel) {
        _searchBizModel = [[NSArray alloc] initWithObjects:@"生产加工", @"经销批发",
                           @"招商代理", @"商业服务", @"其他", nil];
    }
    return _searchBizModel;
}
-(NSArray*)searchBizType
{
    if (!_searchBizType) {
        _searchBizType = [[NSArray alloc] initWithObjects:@"1", @"2",
                           @"3", @"4", @"5", nil];
    }
    return _searchBizType;
}
-(NSArray*)filterButtons
{
    if (!_filterButtons) {
        _filterButtons = [[NSArray alloc]initWithObjects:@"周边", @"地区",@"模式",nil];
    }
    return _filterButtons;
}

- (void)viewDidUnload {
    [self setContentTable:nil];
    _request = nil;
    _objMan =nil;
    _searchBizModel =nil;
    _bizType = nil;
    _area =nil;
    _startingPoint =nil;
    _distance = nil;
    _searchBizType =nil;
    _parentTitle = nil;
    _categoryId = nil;
    [self setResultView:nil];
    [super viewDidUnload];
}
-(void)viewDidLoad
{
    self.contentTable.favDelegate = self; 
    [super viewDidLoad];
    self.startingPoint = nil;
    self.bizType=nil;
    self.area = nil;
    self.distance = nil;
//    self.currentPage=0;
    self.currentPage=1;
    self.total=0;
    [self loadObjectsFromRemote];
        
}


-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}

-(NSArray*)commonTableViewRightButtonTitles
{
    return self.filterButtons;
    
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
//	RKObjectMapping* companyResultMapping = [AMCompanyResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: companyResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SEARCH_COMPANY usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCompanyResult class]];
            loader.objectMapping = [AMCompanyResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
//    [super loadObjectsFromRemote];
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {

    AMCompanyResult *result = (AMCompanyResult*)[objects objectAtIndex:0];
    if ([self.resultData count]==0) {
        [self.contentTable reloadData];
    }
    [self.resultData addObjectsFromArray:result.companyList];
    self.total = [result.total intValue];
    NSString * preTitle = [NSString stringWithFormat:@"共搜到"];
    NSString * Title = [NSString stringWithFormat:@"%d",[result.total intValue]];
    [self.resultView setupData:Title pre:preTitle suf:@"公司"];
    self.isLoading = NO;
    if (self.currentPage*[self.request.pageSize intValue] >= self.total) {
        self.contentTable.tableFooterView = nil;
    }
    [self.contentTable reloadData];
    if (!self.total) {
        [self showNodataMessage];
    }
    else {
        [super objectLoader:objectLoader didLoadObjects:objects];
    }
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
//    if (self.currentPage*[self.request.pageSize intValue] >= self.total) {
//        self.contentTable.tableFooterView = nil;
//    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    if ([self.resultData count]!=self.total) { 
//        if ([indexPath row]==[self.resultData count])
//        {
//            return [AMMoreLoadingCell cellHeight];
//        }
//    }
//    
    return [AliTableViewCellCompanyDetail cellHeight];
}
- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section {
    
//    if ([self.resultData count]==0) {
//        return 0;
//    }
//    if ([self.resultData count]==self.total) {
//        return [self.resultData count];
//    }
   	
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
    

    
    AliTableViewCellCompanyDetail *cell = (AliTableViewCellCompanyDetail *)[tableView 
                                                        dequeueReusableCellWithIdentifier: [AliTableViewCellCompanyDetail cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCompanyDetail createCell];
    }
    
    NSUInteger row = [indexPath row];
    AMCompany *company = (AMCompany*)[self.resultData objectAtIndex:row] ;
    [cell cellSetData:cell amCompany:company];
    if(company.creditInfo.trustLogoSmall.length>0){
      cell.icon.hidden= NO;
      cell.title.frame = CGRectMake(cell.icon.frame.size.width+13, 8, cell.title.frame.size.width, cell.title.frame.size.width);
      [self.objMan manage:cell.icon];  
    }else{
        cell.icon.hidden= YES;
        cell.title.frame = CGRectMake(10, 8, cell.title.frame.size.width, cell.title.frame.size.width);
    }
   
    
    return cell;
}
-(AMCompany*)AliTableView:(AliTableView*)table addCompanyToFav:(NSIndexPath *)indexPath
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
        return (AMCompany*)[self.resultData objectAtIndex:row ] ;
    }
    
}

//- (void)scrollViewDidScroll: (UIScrollView*)scroll {
//    [self.contentTable scrollViewDidScroll:scroll callback:^{
//         if ([self.resultData count]!=self.total)
//         {
//        if (!self.isLoading) {
//            self.currentPage++;
//            [AMLogUtils appendLog: APP_COMPANY_NEXT_TWO]; 
//            [self loadObjectsFromRemote];
//        }
//         }
//
//    } ];
//}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 10.0) {
        if (!self.isLoading) {
            if(self.currentPage*[self.request.pageSize intValue] < self.total) {
                self.currentPage++;
                [AMLogUtils appendLog: APP_COMPANY_NEXT_TWO]; 
                [self loadObjectsFromRemote];
            } 
        }
    }
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    NSUInteger row = [indexPath row];

    if ([self.resultData count]!=self.total) { 
        if ([indexPath row]==[self.resultData count]) {
            return;
        }
    }   
    [AMLogUtils appendLog: APP_COM_LIST_SIX]; 
       AMCompany *data = (AMCompany*)[self.resultData objectAtIndex:row] ;
    AMCompanyTabViewController * companyTabViewController = [[AMCompanyTabViewController alloc] initWithMemberId:data.memberId companyName:data.name preViewName:nil];
    [self.navigationController pushViewController:companyTabViewController animated:YES];
    [companyTabViewController release];
    [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
    
} 
-(void)AliBizTypeFilter:(NSString *)type selectedItem:(NSUInteger)selectedItem
{
    if (self.bizTypeFilterSelectedItem != selectedItem) {
        [AMLogUtils appendLog: APP_COM_LIST_FOUR]; 
        self.bizType = type;
        self.bizTypeFilterSelectedItem = selectedItem;
//        self.currentPage=0;
        self.currentPage=1;
        self.total=0;
        [self.resultData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemote];

    }
  
}

-(void)AliRegionFilter:(AMHotArea*)area segment:(int)segmentSelected selectedItem:(NSUInteger)selectedItem
{
    if (self.regionFilterSegmentSelected != segmentSelected||self.regionFilterSelectedItem != selectedItem) {
        if (area) {
            [AMLogUtils appendLog: APP_COM_LIST_CHILD_FIVE]; 
        }
        else {
           
            [AMLogUtils appendLog: APP_COM_LIST_FIVE]; 
        }
        self.regionFilterSegmentSelected = segmentSelected;
        self.regionFilterSelectedItem = selectedItem;
        self.startingPoint=nil;
        self.area = area;
//        self.currentPage=0;
        self.currentPage=1;
        self.total=0;
        [self.resultData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemote];
    }
}
-(void)AliAroundFilter:(CLLocation *)location distance:(NSString *)distance selectedItem:(NSUInteger)selectedItem
{
    if (self.aroundFilterSelectedItem != selectedItem) {
        self.area = nil;
        self.startingPoint = location;
        self.distance = distance;
        self.aroundFilterSelectedItem = selectedItem;
//        self.currentPage=0;
        self.currentPage=1;
        self.total=0;
        [self.resultData removeAllObjects];
        [self.contentTable reloadData];
        [self loadObjectsFromRemote];
    }
}
-(void)entryBizTypeFilter
{
    AliBizTypeFilter *chooser = [[[AliBizTypeFilter alloc] initWithNibName:@"AliBizTypeFilter" bundle:nil] autorelease];
    chooser.delegate = self;
    chooser.selectedItem = self.bizTypeFilterSelectedItem;
    if (self.keyWords==nil) {
        chooser.parentTitle =  self.navigationItem.title ; 
        
    }
    else
    {
        chooser.parentTitle = self.keyWords;
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
            [self entryBizTypeFilter];
            break;
        default:
            break;
    }
}

@end

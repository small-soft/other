//
//  AMOfferListViewController.m
//  AlibabaMobile
//
//  Created by  on 11-12-21.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "AMSearchPriceViewController.h"
#import "ConstDef.h"
#import "NSAttributedString+HTML.h"
#import "AMMoreLoadingCell.h"
#import "AliTableViewCellPriceDetail.h"
#import "AMPriceResult.h"
#import "AMPriceListRequest.h"
#import "AMMoreLoadingCell.h"
//insert the price graph
#import "AMPriceGraphViewController.h"
#import "AMErrorMessageView.h"
#import "AMMoreLoadingView.h"

#import "AliToastView.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

/////interface AMSearchPriceViewController
@interface AMSearchPriceViewController()
@property (nonatomic, retain) NSMutableArray* contentData;
@property (nonatomic, retain) AMPriceListRequest *request;
@property (nonatomic) int total;
@property (nonatomic) int currentPage;
@property (nonatomic) BOOL isLoading;


- (void)loadObjectsFromRemote;

@end

/////class AMSearchPriceViewController
@implementation AMSearchPriceViewController
@synthesize contentTable=_contentTable;
@synthesize contentData=_contentData;
@synthesize request=_request;
@synthesize keyWords=_keyWords;
@synthesize catId=_catId;
@synthesize catName=_catName;
@synthesize areaId=_areaId;
@synthesize total=_total;
@synthesize currentPage=_currentPage;
@synthesize isLoading = _isLoading;
@synthesize parentTitle=_parentTitle;


-(NSMutableArray*)contentData
{
    
    if (_contentData==nil) {
        _contentData = [[NSMutableArray alloc] init];
    }
    return _contentData;
}

-(NSNumber*)areaId
{
    if (_areaId==nil) {
        _areaId = [NSNumber numberWithInt:0];
    }
    return _areaId;
}

-(AMPriceListRequest*)request
{
    if (_request==nil) {
        _request = [[AMPriceListRequest alloc] init];
    }
    if (self.keyWords!=nil&&self.keyWords.length!=0)
    {
        _request.keywords=self.keyWords;
        _request.cateId=[NSNumber numberWithInt:0];
        _request.areaId=[NSNumber numberWithInt:0];
        
    }
    else
    {
        _request.keywords=@"";
        _request.cateId=self.catId;
        _request.areaId=self.areaId;
        _request.catName = self.catName;
    }
    _request.page=[NSNumber numberWithInt:self.currentPage];
    _request.count= [NSNumber numberWithInt:9];
        NSLog(@"%@",_request);
    return _request;
}

- (void)dealloc {
    [_contentTable release];
//    [_contentData release];
    self.contentData = nil;
    [_request release];
    [_keyWords release];
    [_catId release];
    [_catName release];
    [_areaId release];
    [_parentTitle release];
    
    [super dealloc];
}
-(void)viewWillAppear:(BOOL)animated
{
    //[UIApplication sharedApplication].statusBarHidden = NO;
}

- (void)viewDidUnload {
    [self setContentTable:nil];
//    [_contentData release];
//    _contentData=nil;
    _contentData = nil;
//    [_request release];
    _request=nil;
    /*_keyWords=nil;
    _catId=nil;
    _catName=nil;
    _areaId=nil;
    _parentTitle=nil;*/
    [super viewDidUnload];
}

-(void)viewDidLoad
{
//    self.currentPage=0;
    self.currentPage=1;
    self.contentTable.favDelegate = self;
    [self loadObjectsFromRemote];
    [super viewDidLoad];
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}

-(NSString*)commonTableViewNavigationTitle
{
    return @"价格行情";
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
//	RKObjectMapping* offerResultMapping = [AMPriceResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: offerResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SEARCH_PRICE usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPriceResult class]];
            loader.objectMapping = [AMPriceResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
//    [super loadObjectsFromRemote];
}

#pragma mark RKObjectLoaderDelegate methods



- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {

    AMPriceResult *result = (AMPriceResult*)[objects objectAtIndex:0];
        
    [self.contentData addObjectsFromArray:result.priceList];
    self.total = [result.total intValue];
    [self.contentTable reloadData];   
    self.isLoading = NO;
    if (self.currentPage*[self.request.count intValue] >= self.total) {
        self.contentTable.tableFooterView = nil;
    }
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
        if ([self.contentData count]) {
            AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
            self.contentTable.tableFooterView = errorMessageView;
            [errorMessageView release];
            self.currentPage--;
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        
    }
    self.isLoading = NO;
//    if (self.currentPage*[self.request.count intValue] >= self.total) {
//        self.contentTable.tableFooterView = nil;
//    }
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    if ([self.contentData count]!=self.total) { 
        if ([indexPath row]==[self.contentData count]) {
            return;
        }
    }
    NSUInteger row = [indexPath row];
    AMPriceGraphViewController *priceGraphViewController = [[AMPriceGraphViewController alloc] initWithNibName:@"AMPriceGraphViewController" bundle:nil];
    NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
    [f setNumberStyle:NSNumberFormatterDecimalStyle];
    
    AMPriceItem *priceItem = (AMPriceItem*)[self.contentData objectAtIndex:row] ;
    priceGraphViewController.themeRequstId = [f numberFromString:priceItem.themeId];
    priceGraphViewController.sourceFomeRequstId = [f numberFromString:priceItem.sourceFromId];
    priceGraphViewController.areaRequstId = [f numberFromString:priceItem.areaId];
    priceGraphViewController.sourceAddressName = [priceItem.attributes objectForKey:@"原产地"];
    priceGraphViewController.isPriceFavorited = false;
    priceGraphViewController.navigateTitleName = @"价格行情";
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
            
            
            //index++;
            //NSLog(@"key: %@ ,value: %@",key,[priceItem.attributes objectForKey:key]);
        }
        if (priceGraphViewController.sourceAddressName == nil) {
            priceGraphViewController.sourceAddressName = priceItem.areaName;
        }
    }
    priceGraphViewController.hidesBottomBarWhenPushed=YES;
    [f release];
    [self.navigationController pushViewController:priceGraphViewController animated:YES]; 
    [priceGraphViewController release];
    NSLog(@"priceGraphViewController : %d",[priceGraphViewController retainCount]);
    
    [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    if ([self.contentData count]<=0) {
//        return 0;
//    }
//    if ([self.contentData count]==[indexPath row]) {
//        return [AMMoreLoadingCell cellHeight];
//    }
    return [AliTableViewCellPriceDetail cellHeight];
    
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section 
{
//    if ([self.contentData count]==0) {
//        return 0;
//    }
//    if ([self.contentData count]==self.total) {
//        return [self.contentData count];
//    }
//   	
    return [self.contentData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath { 
    
//    if ([self.contentData count]!=self.total) { 
//        if ([indexPath row]==[self.contentData count]) {
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
    
    AliTableViewCellPriceDetail *cell = (AliTableViewCellPriceDetail *)[tableView 
                                                    dequeueReusableCellWithIdentifier: [AliTableViewCellPriceDetail cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellPriceDetail createCell];
    }
    
    NSUInteger row = [indexPath row];
    AMPriceItem *priceItem = (AMPriceItem*)[self.contentData objectAtIndex:row] ;
    NSLog(@"offer objects: %@", priceItem);    
    
    [cell cellSetData:priceItem];
       
    return cell;
}
-(AMPriceItem*)AliTableView:(AliTableView*)table addPriceToFav:(NSIndexPath*)indexPath
{
    NSUInteger row = [indexPath row];
    if ([self.contentData count]!=self.total) { 
        if ([indexPath row]==[self.contentData count]) {
            return nil;
        }
    } 
    
    {
        if (row>=[self.contentData count]) {
            return nil;
        }
        else {
            return (AMPriceItem*)[self.contentData objectAtIndex:row] ;
        }

    }
}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 10.0) {
        if (!self.isLoading) {
            if(self.currentPage*[self.request.count intValue] < self.total) {
                self.currentPage++;
                [AMLogUtils appendLog: APP_PRICE_NEXT_THREE]; 
                [self loadObjectsFromRemote];
            } 
        }
    }
}
@end

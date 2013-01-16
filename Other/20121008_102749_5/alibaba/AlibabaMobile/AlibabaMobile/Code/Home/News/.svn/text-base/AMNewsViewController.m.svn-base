//
//  AMNewsViewController.m
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMNewsViewController.h"
#import "AMNewsListRequest.h"
#import "ConstDef.h"
#import "AMNewsTitleItem.h"
#import "AMNewsTitle.h"
#import "AliTableViewCellSubTitle.h"
#import "AMNewsCategoryCell.h"
#import "AMNewsCategory.h"
#import "AMNavigationTileButtonView.h"
#import "AMNewsDetailViewController.h"
#import "AMNewsItemImageOffer.h"
#import "AMImage.h"
#import "AMNewsItem.h"
#import "AMNewsListResult.h"
#import "AMMoreLoadingCell.h"
#import "AliNavigationBackButton.h"
#import "NSAttributedString+HTML.h"
#import "AMRequestDelegate.h"
#import "AMErrorMessageView.h"
#import "AMMoreLoadingView.h"
@interface AMNewsViewController()

@property (nonatomic,retain) AMNavigationTileButtonView *navigationTitle;

@property (nonatomic, retain) AMNewsListRequest * hotNewsRequest;
@property (readwrite) BOOL isLoadingHotNews;
@property (nonatomic, retain) NSMutableArray* hotNewsData;
- (void)loadHotNewsFromRemote;


@property (nonatomic, retain) AMNewsListRequest * categoriesRequest;
@property (readwrite) BOOL isLoadingCategories;
@property (nonatomic, retain) NSMutableArray* categoriesData;
-(void)loadCategoriesFromRemote;

@property (nonatomic, retain) AMNewsListRequest * commonNewsRequest;
@property (readwrite) BOOL isLoadingCommonNews;
@property (nonatomic, retain) NSMutableArray* commonNewsData;
- (void)loadCommonNewsFromRemote;
@property (readwrite) int total;
@property (readwrite) int currentPage;


- (void)categoryPressed:(id)sender;
- (void) showCategoryView;
- (void) hideCategoryView;

@end

@implementation AMNewsViewController

#pragma property start
@synthesize navigationTitle=_navigationTitle;

@synthesize hotNewContentTable=_hotNewContentTable;
@synthesize categoryView = _categoryView;
@synthesize categoryContentTable = _categoryContentTable;
@synthesize commonNewTable = _commonNewTable;

@synthesize hotNewsRequest=_hotNewsRequest;
@synthesize isLoadingHotNews=_isLoadingHotNews;
@synthesize hotNewsData=_hotNewsData;

@synthesize categoriesRequest=_categoriesRequest;
@synthesize isLoadingCategories=_isLoadingCategories;
@synthesize categoriesData=_categoriesData;

@synthesize commonNewsRequest=_commonNewsRequest;
@synthesize isLoadingCommonNews=_isLoadingCommonNews;
@synthesize commonNewsData=_commonNewsData;
@synthesize total=_total;
@synthesize currentPage=_currentPage;
@synthesize parentTitle=_parentTitle;
-(AMNavigationTileButtonView*)navigationTitle
{
    if (_navigationTitle==nil) {

        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMNavigationTileButtonView" 
                                                         owner:self options:nil];
        for (id oneObject in nib){
            if ([oneObject isKindOfClass:[AMNavigationTileButtonView class]])
                self.navigationTitle = (AMNavigationTileButtonView *)oneObject;
            [_navigationTitle.titleButton addTarget:self action:@selector(categoryPressed:) forControlEvents:UIControlEventTouchUpInside];
        }
        [_navigationTitle setTitle:NSLocalizedString(@"NewsTitle", @"") ];
        [_navigationTitle.arrowButton addTarget:self action:@selector(categoryPressed:) forControlEvents:UIControlEventTouchUpInside];
       
        }
    
    
    return _navigationTitle;
}


-(AMNewsListRequest*)hotNewsRequest
{
    if (_hotNewsRequest==nil) {
        _hotNewsRequest = [[AMNewsListRequest alloc] init];
        _hotNewsRequest.transactionType = AMTRANSACTION_TYPE_HOT_NEWS;
    }
   
    return  _hotNewsRequest;
}

-(NSMutableArray*)hotNewsData
{
    
    if (_hotNewsData==nil) {
        _hotNewsData = [[NSMutableArray alloc] init];
    }
    return _hotNewsData;
}

-(AMNewsListRequest*)categoriesRequest
{
    if (_categoriesRequest==nil) {
        _categoriesRequest = [[AMNewsListRequest alloc] init];
        _categoriesRequest.transactionType = AMTRANSACTION_TYPE_NEWSCATEGORY_LIST;
    }
    
    return  _categoriesRequest;
}

-(NSMutableArray*)categoriesData
{
    
    if (_categoriesData==nil) {
        _categoriesData = [[NSMutableArray alloc] init];
    }
    return _categoriesData;
}

-(AMNewsListRequest*)commonNewsRequest
{
    if (_commonNewsRequest==nil) {
        _commonNewsRequest = [[AMNewsListRequest alloc] init];
        _commonNewsRequest.transactionType = AMTRANSACTION_TYPE_NEWS_LIST;
    }
    
    return  _commonNewsRequest;
}

-(NSMutableArray*)commonNewsData
{
    
    if (_commonNewsData==nil) {
        _commonNewsData = [[NSMutableArray alloc] init];
    }
    return _commonNewsData;
}

#pragma property end

- (void)dealloc {
    [_navigationTitle release];
    [_hotNewContentTable release];
    [_hotNewsRequest release];
    [_hotNewsData release];
    [_categoryView release];
    [_categoriesRequest release];
    [_categoriesData release];
    [_categoryContentTable release];
    [_commonNewTable release];
    [_commonNewsRequest release];
    [_commonNewsData release];
    [_parentTitle release];
    [super dealloc];
}
- (void)viewDidUnload {
    _navigationTitle=nil;
    [self setHotNewContentTable:nil];
    [_hotNewsRequest release];
    _hotNewsRequest=nil;
    [_hotNewsData release];
    _hotNewsData = nil;
    [_categoriesRequest release];
    _categoriesRequest=nil;
    [_categoriesData release];
    _categoriesData = nil;
    [_commonNewsRequest release];
    _commonNewsRequest = nil;
    [_commonNewsData release];
    _commonNewsData = nil;
    [self setCategoryView:nil];
    [self setCategoryContentTable:nil];
    [self setCommonNewTable:nil];
    [super viewDidUnload];
}
-(void)viewDidLoad
{
    [self.categoryView setHidden:NO];
    self.categoryView.alpha = 0.0f;
    [self.commonNewTable setHidden:YES];
    [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];
    [super viewDidLoad];
}
-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    NSLog(@"viewWillAppear...");
    
    if ([self.hotNewsData count ] <= 0) {
        [self loadHotNewsFromRemote];
        [self loadCategoriesFromRemote];
    }
}
-(void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    NSLog(@"viewWillDisappear...");
}
- (void)categoryPressed:(id)sender
{
    [AMLogUtils appendLog: APP_LASTEST_NEWS_TWO]; 

    
    if (self.categoryView.alpha == 0.0f) {
//        [self.categoryView  setHidden:NO];
        [self showCategoryView];
        
        [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow_up"] forState:UIControlStateNormal];
       
    }
    else
    {
//        [self.categoryView  setHidden:YES];
        [self hideCategoryView];
        
        [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];

    }
}

- (void) showCategoryView
{
    [UIView setAnimationDuration:0.7];
    [UIView beginAnimations:@"scale" context:nil];
    
    self.categoryView.alpha = 1.0f;
    
    [UIView commitAnimations];

}

- (void) hideCategoryView
{
    [UIView setAnimationDuration:0.7];
    [UIView beginAnimations:@"scale" context:nil];
    
    self.categoryView.alpha = 0.0f;
    
    [UIView commitAnimations];

}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(UIView*)commonTableViewNavigationTitleView
{
    return self.navigationTitle;;
}
#pragma mark RKObjectLoaderDelegate methods



- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);    
       
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = (NSInteger)[(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        switch (transactionType) {
            case AMTRANSACTION_TYPE_HOT_NEWS:
            {
                [self.hotNewsData removeAllObjects];
                [self.hotNewsData addObjectsFromArray:objects];
                [self.hotNewContentTable reloadData] ;                 
                self.isLoadingHotNews = NO;        
            }
                break;
            case AMTRANSACTION_TYPE_NEWSCATEGORY_LIST:
            {
                [self.categoriesData removeAllObjects];
                [self.categoriesData addObjectsFromArray:objects];
                [self.categoryContentTable reloadData] ;                 
                self.isLoadingCategories = NO;
            }
                break;
            case AMTRANSACTION_TYPE_NEWS_LIST:
            {
                AMNewsListResult *result = (AMNewsListResult*)[objects objectAtIndex:0];
                self.total = [result.total intValue];
//                if ([self.commonNewsData count]==0) {
//                   [self.commonNewTable reloadData] ;
//                }
                [self.commonNewsData addObjectsFromArray:result.newsList];
                [self.commonNewTable reloadData] ;
                if (self.currentPage*[self.commonNewsRequest.count intValue] >= self.total) {
                    self.commonNewTable.tableFooterView = nil;
                }
                
                self.isLoadingCommonNews = NO;
            }
                break;
            default:
                break;
        }
    }
    
    if (!self.isLoadingCommonNews&&!self.isLoadingCategories&&!self.isLoadingHotNews) {
        [super objectLoader:objectLoader didLoadObjects:objects];
    }

}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
            NSInteger transactionType = (NSInteger)[(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
            
            switch (transactionType) {
                case AMTRANSACTION_TYPE_HOT_NEWS:
                {               
                    [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
                    self.isLoadingHotNews = NO;        
                }
                    break;
                case AMTRANSACTION_TYPE_NEWSCATEGORY_LIST:
                {                
                    [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
                    self.isLoadingCategories = NO;
                }
                    break;
                case AMTRANSACTION_TYPE_NEWS_LIST:
                {
                    if ([self.commonNewsData count] != 0) {
                        AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
                        self.commonNewTable.tableFooterView = errorMessageView;
                        [errorMessageView release];
                        self.currentPage --;
                    }else {
                        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
                    }
                    self.isLoadingCommonNews = NO;
//                    if (self.currentPage*[self.commonNewsRequest.count intValue] >= self.total) {
//                        self.commonNewTable.tableFooterView = nil;
//                    }
                }
                    break;
                default:
                    break;
            }
        }
        
    }
    
}


#pragma mark RKObjectLoaderDelegate methods end



- (void)loadHotNewsFromRemote {
    self.isLoadingHotNews = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* newsTitleMapping = [AMNewsTitle sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: newsTitleMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_HOTNEWS_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewsTitle class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.hotNewsRequest;
    }];
    [super loadObjectsFromRemote];
    
}

- (void)loadCategoriesFromRemote {
    self.isLoadingCategories = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
     
    // Register our mappings with the provider
	RKObjectMapping* categoryMapping = [AMNewsCategory sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: categoryMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWS_CATEGORIES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewsCategory class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.categoriesRequest;
    }];
     [super loadObjectsFromRemote];
}
- (void)loadCommonNewsFromRemote{
    self.isLoadingCommonNews = YES;
    AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
    if (self.currentPage>1) {
        self.commonNewTable.tableFooterView = moreloadingView;
    }else {
        [self.mLoadingView showLoadingView];
    }
    [moreloadingView release];
    self.commonNewsRequest.page=[NSNumber numberWithInt:self.currentPage];
    self.commonNewsRequest.count= [NSNumber numberWithInt:9];
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* newsListResultMapping = [AMNewsListResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: newsListResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWS_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewsListResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.commonNewsRequest;
    }];
//     [super loadObjectsFromRemote];
    
}

#pragma Table Data Source Methods

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section {
    if (tableView==self.hotNewContentTable) 
    {
        
        if ([self.hotNewsData count]==0) 
            return 0;

        return [self.hotNewsData count];
    }
    else if (tableView == self.categoryContentTable)
    {
        return [self.categoriesData count]+1;
    }
    else if (tableView == self.commonNewTable)
    {
//        if (0==[self.commonNewsData count]) {
//            return 0;
//        }
//        if ([self.commonNewsData count]==self.total) {
//            return [self.commonNewsData count];
//        }
//        else
//        {
//            return [self.commonNewsData count]+1;
//        }
        return [self.commonNewsData count];
    }
    return 0;
}


- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
    if (tableView==self.hotNewContentTable)
    {
       
        
        AliTableViewCellSubTitle *cell = (AliTableViewCellSubTitle *)[tableView 
                                          dequeueReusableCellWithIdentifier: [AliTableViewCellSubTitle cellIdentifer]];
        if (cell == nil)  
        {
            cell = [AliTableViewCellSubTitle createCell];
        }
        NSUInteger row = [indexPath row];
        AMNewsTitle *news = (AMNewsTitle*)[self.hotNewsData objectAtIndex:row] ;
        
        NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[news.newsTitleItem.title dataUsingEncoding:NSUTF8StringEncoding]documentAttributes:NULL];
      
        cell.title.text = attributedText.plainTextString;
        //cell.content.text = news.newsTitleItem.title;
        
        cell.subTitle.text = news.newsTitleItem.publishDate;
        
        return cell;
        
    }
   else if (tableView == self.categoryContentTable)
    {
       
        
        AMNewsCategoryCell *cell = (AMNewsCategoryCell *)[tableView 
                                                          dequeueReusableCellWithIdentifier: [AMNewsCategoryCell cellIdentifer]];
        if (cell == nil)  
        {
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMNewsCategoryCell" 
                                                         owner:self options:nil];
            for (id oneObject in nib)
                if ([oneObject isKindOfClass:[AMNewsCategoryCell class]])
                    cell = (AMNewsCategoryCell *)oneObject;
            
            UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:cell.frame];
            UIImage * bkImage =  [UIImage imageNamed:@"bg_toppicker_tap"];
            bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
            cellBackBtn.image =bkImage;
            
            cell.selectedBackgroundView = cellBackBtn;
            [cellBackBtn release]; 

        }
        NSUInteger row = [indexPath row];
        if (row==0) {
            cell.content.text = @"热点";
        }
        else
        {
            AMNewsCategory *cate = (AMNewsCategory*)[self.categoriesData objectAtIndex:(row-1)] ;
            
            cell.content.text = cate.name;
            
        }    
        return cell;
        
        
    }
   else if (tableView == self.commonNewTable)
    {
        
//        if ([self.commonNewsData count]!=self.total) { 
//            if ([indexPath row]==[self.commonNewsData count]) {
//                AMMoreLoadingCell *cell = (AMMoreLoadingCell *)[tableView 
//                                                              dequeueReusableCellWithIdentifier: [AMMoreLoadingCell cellIdentifer]];
//                if (cell == nil)  
//                {
//                    cell = [AMMoreLoadingCell createCell];
//                }
//                return cell;
//            }
//        }

        
        AliTableViewCellSubTitle *cell = (AliTableViewCellSubTitle *)[tableView 
                                                      dequeueReusableCellWithIdentifier: [AliTableViewCellSubTitle cellIdentifer]];
        if (cell == nil)  
        {
            cell = [AliTableViewCellSubTitle createCell];
        }
        NSUInteger row = [indexPath row];
        AMNewsItem *cate = (AMNewsItem*)[self.commonNewsData objectAtIndex:row] ;
     
        NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[cate.title dataUsingEncoding:NSUTF8StringEncoding]documentAttributes:NULL] ;
        
        cell.title.text = attributedText.plainTextString;
        //cell.content.text = news.newsTitleItem.title;

        
       // cell.content.text = cate.title;
        cell.subTitle.text = cate.publishDate;
        
        return cell;
       }
    
    return nil;
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView == self.categoryContentTable)
    {
        return [AMNewsCategoryCell cellHeight];    
    }
    else
    {
//        if ([self.commonNewsData count]!=self.total) { 
//            if ([indexPath row]==[self.commonNewsData count])
//            {
//                return [AMMoreLoadingCell cellHeight];      
//            }
//        }
        return [AliTableViewCellSubTitle cellHeight];
    }
}

#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
//    /*fix bug
//     加入一段if语句判断，用于当用户点击菜单之外的区域时使得菜单消失
//     */
//    if (self.categoryView.alpha != 0.0f) {
//        [self hideCategoryView];
//        [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];
//    }
//    /*------------------*/
    if (tableView==self.hotNewContentTable)
    {
        
        [AMLogUtils appendLog: APP_LASTEST_NEWS_THREE]; 
        AMNewsDetailViewController *Controller = [[[AMNewsDetailViewController alloc] initWithNibName:@"AMNewsDetailViewController" bundle:nil] autorelease];
        Controller.hidesBottomBarWhenPushed=YES;
        
        AMNewsTitle *news = (AMNewsTitle*)[self.hotNewsData objectAtIndex:row] ;
        
        NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
        [f setNumberStyle:NSNumberFormatterDecimalStyle];
        
        Controller.categoryId=[f numberFromString:news.newsTitleItem.identifier];
        Controller.hotNewsIndex=row;
        Controller.navigationTitle=news.newsTitleItem.title;    
        Controller.parentTitle = self.navigationTitle.titleButton.titleLabel.text;
        Controller.hotNewsData=self.hotNewsData;
        [f release];
        [self.navigationController pushViewController:Controller animated:YES];
         [self.hotNewContentTable deselectRowAtIndexPath:indexPath animated:NO];
    }
    else  if (tableView == self.categoryContentTable)
    {
        
        if (row==0) {
            [AMLogUtils appendLog: APP_LASTEST_NEWS_ONE]; 
            [self.hotNewContentTable setHidden:NO];
            [self.commonNewTable setHidden:YES];
//            [self.categoryView setHidden:YES];
            [self hideCategoryView];
            
            [self.navigationTitle.titleButton setTitle:NSLocalizedString(@"NewsTitle", @"")  forState:UIControlStateNormal] ;
            [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];
        }
        else
        {
             [AMLogUtils appendLog: APP_LASTEST_NEWS_FIVE]; 
                       
//            [self.categoryView setHidden:YES];
            [self hideCategoryView];
            
            [self.hotNewContentTable setHidden:YES];
            [self.commonNewTable setHidden:NO];
            [self.commonNewsData removeAllObjects];
            [self.commonNewTable reloadData];
            self.currentPage = 1;
            AMNewsCategory *cate = (AMNewsCategory*)[self.categoriesData objectAtIndex:(row-1)] ;
            self.commonNewsRequest.cateId=[cate.identifier stringValue];
            [self.navigationTitle.titleButton setTitle:cate.name forState:UIControlStateNormal] ;
            [self loadCommonNewsFromRemote];
            [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];
            
        }
         [self.categoryContentTable deselectRowAtIndexPath:indexPath animated:NO];
    }
    else if(tableView == self.commonNewTable)
    {
         NSUInteger row = [indexPath row];
        if ([self.commonNewsData count]!=self.total) { 
            if ([indexPath row]==[self.commonNewsData count]) {
                return;
            }
        }   
        
        [AMLogUtils appendLog: APP_LASTEST_NEWS_FOUR];

        AMNewsDetailViewController *Controller = [[[AMNewsDetailViewController alloc] initWithNibName:@"AMNewsDetailViewController" bundle:nil] autorelease];
        Controller.hidesBottomBarWhenPushed=YES;
        
       
        AMNewsItem *cate = (AMNewsItem*)[self.commonNewsData objectAtIndex:row] ;
        Controller.categoryId=cate.identifier;
        Controller.navigationTitle=cate.title;   
        Controller.parentTitle = self.navigationTitle.titleButton.titleLabel.text;
        
        Controller.commonNewsIndex=row;   
        Controller.commonNewsData=self.commonNewsData;
        [self.navigationController pushViewController:Controller animated:YES];
         [self.commonNewTable deselectRowAtIndexPath:indexPath animated:NO];
        
    }

}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    if(scroll == self.commonNewTable)
    {
        NSInteger currentOffset = scroll.contentOffset.y;
        NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
        
        // Change 10.0 to adjust the distance from bottom
        if (maximumOffset - currentOffset <= 10.0) {
            if (!self.isLoadingCommonNews) {
                if(self.currentPage*[self.commonNewsRequest.count intValue]< self.total) {
                    self.currentPage++;
                    [self loadCommonNewsFromRemote];
                } 
            }
        }
    }
}
-(IBAction)clickOutOfCategoryView:(id)sender
{
    [self hideCategoryView];
    
    [self.navigationTitle.arrowButton  setImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];
    
}

@end

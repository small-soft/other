//
//  ImageMagazineListViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ImageMagazineListViewController.h"
#import "ConstDef.h"
#import "AMImgMagazineRequest.h"
#import "AMImgMagazineCategory.h"
#import "UIHelp.h"
#import "AliImageMagazineCategoryItem.h"
#import "AMNewsItem.h"
#import "ImageMagazineDetailViewController.h"
#import "ImageMagazineListViewController.h"
#import "AliImageMagazineItem.h"
#import "AMNewsListResult.h"
#import "ImageMagazineDetailViewController.h"
#import "AliToastView.h"

@interface ImageMagazineListViewController()
{
    AMImgMagazineRequest * _request;
    HJObjManager * _objMan;
    int sum;
    int currentNum;
    int currentRequestPage;
    BOOL isLoading;
}

@property (nonatomic, retain) NSString * categoryId;
@property (nonatomic, retain) NSString * categoryName;

@property (nonatomic, retain) NSMutableArray * magazineList;
@property (nonatomic, retain) IBOutlet UIScrollView * contentScrollView;
@property (nonatomic, retain) IBOutlet UIImageView * leftArrow;
@property (nonatomic, retain) IBOutlet UIImageView * rightArrow;
@property (nonatomic, retain) IBOutlet UILabel * pageIndactorLabel;

- (void) setContentView;
-(void)objManInit;
-(void)loadRequest:(int)page;

@end

@implementation ImageMagazineListViewController

@synthesize categoryId = _categoryId;
@synthesize categoryName = _categoryName;
@synthesize contentScrollView = _contentScrollView;
@synthesize magazineList = _magazineList;
@synthesize leftArrow = _leftArrow;
@synthesize rightArrow = _rightArrow;
@synthesize pageIndactorLabel = _pageIndactorLabel;
@synthesize parentTitle = _parentTitle;

- (id)initWithId:(NSString *)id title:(NSString *)title
{
    self = [super init];
    if (self) {
        self.categoryName = title;
        self.categoryId = id;
        currentRequestPage = 0;
        currentNum = 0;
        isLoading = NO;
    }
    return self;
}

- (void) dealloc
{
    [_categoryId release];
    [_categoryName release];
    
    [_contentScrollView release];
    [_magazineList release];
    [_objMan release];
    [_request release];
    
    [_leftArrow release];
    [_rightArrow release];
    
    [_parentTitle release];
    
    [_pageIndactorLabel release];
    
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewWillAppear:(BOOL)animated
{
    self.navigationController.navigationBar.hidden = NO;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setTitle: self.categoryName];
    
    if (self.parentTitle == nil) {
        self.parentTitle = @"返回";
    }
    [self setBackButtonText:self.parentTitle];
    
    
    [self setContentView];
    [self objManInit];
    [self loadRequest:1];
    
}

- (void)viewDidUnload {
    [_objMan release];
    _objMan = nil;
    [_request release];
    _request = nil;
    [_magazineList release];
    _magazineList = nil;
    self.leftArrow = nil;
    self.rightArrow = nil;
    self.pageIndactorLabel = nil;
    self.contentScrollView = nil;
    self.parentTitle = nil;
    [super viewDidUnload];
}

- (void) refreshArrowState:(int)index sum:(int)sumpage
{
    if (index == 1 &&index ==sumpage) {
        self.leftArrow.image = [UIImage imageNamed:@"icon_Album_arowleft_disable"];
        self.rightArrow.image = [UIImage imageNamed:@"icon_Album_arowright_disable"];
    }else if(index == 1)
    {
        self.leftArrow.image = [UIImage imageNamed:@"icon_Album_arowleft_disable"];
        self.rightArrow.image = [UIImage imageNamed:@"icon_Album_arowright"];
    }else if(index == sumpage){
        self.leftArrow.image = [UIImage imageNamed:@"icon_Album_arowleft"];
        self.rightArrow.image = [UIImage imageNamed:@"icon_Album_arowright_disable"];
    }else{
        self.leftArrow.image = [UIImage imageNamed:@"icon_Album_arowleft"];
        self.rightArrow.image = [UIImage imageNamed:@"icon_Album_arowright"];
    }
    
    self.pageIndactorLabel.text = [NSString stringWithFormat:@"%d/%d", index,sumpage];
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) setContentView
{
    //setting paged scrollview  
    self.contentScrollView.directionalLockEnabled = YES;  
    self.contentScrollView.pagingEnabled = YES;   
    self.contentScrollView.showsVerticalScrollIndicator = NO;  
    self.contentScrollView.showsHorizontalScrollIndicator = NO;  
    self.contentScrollView.delegate = self; 
    
}

- (void) appendMore:(int)beginIndex
{
    if(self.magazineList != nil
       && self.magazineList.count > 0
       && beginIndex >= 0 && beginIndex < sum){
        int size = self.magazineList.count;
        
        int tempX = 0;
        int tempY = 20;
        
        int nowPage = (beginIndex+1)/4 + ((beginIndex+1)%4>0?1:0);
        tempX = 30 + (nowPage-1) *self.contentScrollView.frame.size.width;
        
        for(int i=beginIndex; i<size; i++){
            AMNewsItem * category = [self.magazineList objectAtIndex:i];
            
            AliImageMagazineItem * categoryItem = [[AliImageMagazineItem alloc] init];
            [categoryItem setSubject:category.title];
            
            if(category.coverUrl != nil){
                [categoryItem.imageView clear];
                categoryItem.imageView.url = [NSURL URLWithString:category.coverUrl];
                [_objMan manage:categoryItem.imageView];
                
            }
            
            categoryItem.imageView.userInteractionEnabled = YES;
            
            MyUITapGestureRecognizer * clickRecognizer = [[MyUITapGestureRecognizer alloc] initWithTarget:self action:@selector(redirectToOfferDetail:)];
            clickRecognizer.param = i;
            [categoryItem.imageView addGestureRecognizer:clickRecognizer];
            [clickRecognizer release];
            
            categoryItem.frame = CGRectMake(tempX, tempY, categoryItem.frame.size.width, categoryItem.frame.size.height);
            [self.contentScrollView addSubview:categoryItem];
            [categoryItem release];
            
            if(i%4 == 0){
                tempX += (110 + 40);
            }else if(i%4 == 1){
                tempX -= (110 +40);
                tempY += (180+10);
            }else if(i%4 == 2){
                tempX += (110 + 40);
            }else{
                tempY = 20;
                tempX += (110 + 60);
            }
        }
        
        
//        int pageNum = size/4 + ((size%4)>0?1:0);
        int pageNum =  size/4 + (( size%4)>0?1:0);
        int totalpageNum = sum/4 + ((sum%4)>0?1:0);
        self.contentScrollView.contentSize = CGSizeMake(self.contentScrollView.frame.size.width * pageNum, self.contentScrollView.frame.size.height);
        
        if(self.contentScrollView.contentOffset.x == 0){
             [self refreshArrowState:1 sum:totalpageNum];
        }
        
        isLoading = NO;
        
    }
    [self endLoadingView];
        
}


- (IBAction)redirectToOfferDetail:(id)sender
{
    int index = ((MyUITapGestureRecognizer *)sender).param;
    AMNewsItem *item = [self.magazineList objectAtIndex:index];
    ImageMagazineDetailViewController * detailViewController = [[ImageMagazineDetailViewController alloc] initWithNewsId:item.identifier.stringValue preTitle:self.categoryName];
    [self.navigationController pushViewController:detailViewController animated:YES];
    [detailViewController release];
}

#pragma load data

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:20 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	_objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (void)loadObjectsFromRemote {
    
    // Load the object model via RestKit
	[self.mLoadingView showLoadingView];
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMNewsListResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MAGAZINE_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewsListResult class]];
            loader.objectMapping = [AMNewsListResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _request;
    }];
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
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
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {   
    if(objects != nil
       && objects.count > 0){
         AMNewsListResult * result = (AMNewsListResult*)[objects objectAtIndex:0];
        
        if(result != nil
           && result.newsList != nil
           && result.newsList.count >0){
            NSLog(@"total:%@ sum:%@ page:%@", result.total.stringValue,result.count.stringValue, result.page.stringValue);
            if(result.newsList != nil){
                NSLog(@"list count:%d", result.newsList.count);
            }else{
                NSLog(@"newslist null");
            }
            
            sum = result.total.intValue;
            currentRequestPage ++;
            currentNum += result.newsList.count;
            
            
            [self performSelectorOnMainThread:@selector(appendTableWith:) withObject:result waitUntilDone:YES];
//            [self appendTableWith:result];
        }
                

    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    [self.mLoadingView endLoadingView];
}

-(void) appendTableWith:(AMNewsListResult *)data 
{ 
    if(self.magazineList == nil){
        self.magazineList =  [[NSMutableArray alloc] initWithCapacity:data.total.intValue];

    }
    int beginIndex = self.magazineList.count;
    [self.magazineList addObjectsFromArray:data.newsList];
    [self appendMore:beginIndex];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    [self endLoadingView];
    isLoading = NO;
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        if ([self.magazineList count]!=0) {
            NSString *errorMsg = @"网络中断，请在网络恢复连接时向右滑动加载";
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:errorMsg] show];
            
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
//        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }
}

-(void)loadRequest:(int)page
{
    if(_request == nil){
        _request = [[AMImgMagazineRequest alloc] init];
    }
    
    _request.categoryid = self.categoryId;
    _request.page = [NSNumber numberWithInt:page];
    _request.requestURL = OCEAN_API_URL_MAGAZINE_LIST;
    
    [self.mLoadingView showLoadingView];
    [self loadObjectsFromRemote];
    
} 


#pragma scroll

- (void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView  
{  

    int pageIndex = fabs(self.contentScrollView.contentOffset.x) / self.contentScrollView.frame.size.width + 1;
//    if (pageIndex==sum) {
//        return;
//    }
    int sumPageNum = sum/4 + ((sum%4)>0?1:0);
    int pageNum = currentNum / 4 + ((currentNum%4)>0?1:0);
    if(currentNum < sum && pageIndex == pageNum && isLoading == NO){
        isLoading = YES;
        [self loadRequest:currentRequestPage+1];
    }
    [self refreshArrowState:pageIndex sum:sumPageNum];
}  

@end

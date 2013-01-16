//
//  ImageMagazineListViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsListViewController.h"
#import "ConstDef.h"
#import "AMNewProductsListRequest.h"
#import "UIHelp.h"
#import "AMNewProductsListResult.h"
#import "AMNewProductsListItem.h"
#import "ImageMagazineDetailViewController.h"
#import "AMNewProductsItem.h"
#import "AMOfferTabViewController.h"
#import "AMLogUtils.h"


@interface AMNewProductsListViewController()
{
    AMNewProductsListRequest * _request;
    HJObjManager * _objMan;
    int sum;
    int currentNum;
    int currentRequestPage;
    BOOL isLoading;
}

@property (nonatomic, retain) NSString * secondcate;;
@property (nonatomic, retain) NSString * categoryName;
@property (retain,nonatomic)AliSegmentedControl *mSegmentedControl;
@property (nonatomic, retain) NSMutableArray * magazineList;
@property (nonatomic, retain) IBOutlet UIScrollView * contentScrollView;
@property (nonatomic, retain) IBOutlet UIImageView * leftArrow;
@property (nonatomic, retain) IBOutlet UIImageView * rightArrow;
@property (nonatomic, retain) NSArray * titleAndCategoryTotal;
@property (nonatomic, retain) NSString * operationId;
@property (nonatomic, retain) NSString *pageId;//打点，表明当前打点类目id

@property (readwrite,nonatomic)int newProductsMode;

@property (nonatomic, retain) UIView *segmentLoadingView;


- (void) setContentView;
-(void)objManInit;
-(void)loadRequest:(int)page;

@end

@implementation AMNewProductsListViewController

@synthesize secondcate = _secondcate;
@synthesize categoryName = _categoryName;
@synthesize contentScrollView = _contentScrollView;
@synthesize magazineList = _magazineList;
@synthesize leftArrow = _leftArrow;
@synthesize rightArrow = _rightArrow;
@synthesize mSegmentedControl=_mSegmentedControl;
@synthesize newProductsMode = _newProductsMode;
@synthesize titleAndCategoryTotal = _titleAndCategoryTotal;
@synthesize operationId = _operationId;
@synthesize pageId = _pageId;
@synthesize segmentLoadingView = _segmentLoadingView;

-(CGFloat)segmentStartY
{
    return 0;
}

-(void)setNewProductsMode:(int)newProductsMode
{
    if (_newProductsMode==newProductsMode) {
        return;
    }
    
    _newProductsMode = newProductsMode;
   
    if(_magazineList!=nil){
        [_magazineList removeAllObjects];
    }
    if(_titleAndCategoryTotal.count>=1&&newProductsMode!=-1){
        NSString *categoryString = [_titleAndCategoryTotal objectAtIndex:newProductsMode];
        NSArray *categoryArray = [categoryString componentsSeparatedByString:@"-"];
        if(categoryArray.count==3){
            self.operationId = [categoryArray objectAtIndex:2];
            NSLog(@"opertationId=%@",_operationId);
        }
         [self loadRequest:1];
        
    }

    
}


- (id)initWithSecondcate:(NSString *)secondcate title:(NSString *)title pageId:(NSString *)pageId 
{
    self = [super init];
    if (self) {
        self.categoryName = title;
        self.secondcate = secondcate;
        self.pageId = pageId;
        currentRequestPage = 0;
        currentNum = 0;
        isLoading = NO;
    }
    return self;
}

- (void) dealloc
{
    [_secondcate release];
    [_categoryName release];
    
    [_contentScrollView release];
    [_magazineList release];
    [_objMan release];
    [_request release];
    
    [_leftArrow release];
    [_rightArrow release];
    [_pageId release];
    [_operationId release];
    [_titleAndCategoryTotal release];
    [_mSegmentedControl release];
    [_segmentLoadingView release];
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewWillAppear:(BOOL)animated
{
    self.navigationController.navigationBar.hidden = NO;
    
}


-(UIView*)segmentLoadingView
{
    if(!_segmentLoadingView){
        _segmentLoadingView = [[UIView alloc] initWithFrame:CGRectMake(0.0,0.0,320.0,40.0)];
        _segmentLoadingView.backgroundColor = [UIColor clearColor];
    }
    return _segmentLoadingView;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //一进来的默认点
    NSString *clickId = [NSString stringWithFormat:@"1-%@-%d-%@",self.pageId,1,self.pageId];
    [AMLogUtils appendLog:clickId];
    
    [self setTitle: self.categoryName];
    [self setBackButtonText:@"新品专区"];
    
    
    [self setContentView];
    [self objManInit];
    self.titleAndCategoryTotal = [self.secondcate componentsSeparatedByString:@":"];
    
    self.newProductsMode=-1;
    [self.mSegmentedControl setSelectedIndex:0];
    self.newProductsMode=0;  
    
   [self.view addSubview:self.mSegmentedControl];
    
}

- (void)viewDidUnload
{
    [_magazineList release];
    _magazineList = nil;
    [_objMan release];
    _objMan = nil;
    [_request release];
    _request = nil;
    
    self.leftArrow = nil;
    self.rightArrow = nil;
    self.contentScrollView = nil;
 
    [super viewDidUnload];
    
}
-(AliSegmentedControl*)mSegmentedControl
{
    if (_mSegmentedControl==nil) {
        _mSegmentedControl = [[AliSegmentedControl alloc] initWithFrame:CGRectMake(0, [self segmentStartY], 320, 40)];
        _mSegmentedControl.delegate = self;
        
        //      "女装-3-clothing_women:童装-3-clothing_children:男装-3-clothing_men:内衣-3-clothing_underwear"
        NSArray *titleAndCategory = [self.secondcate componentsSeparatedByString:@":"];
        if(titleAndCategory.count>=2){
            for(NSString *titleAndCategoryItem in titleAndCategory){
                NSArray *category = [titleAndCategoryItem componentsSeparatedByString:@"-"];
                if(category.count==3){
                    NSString * title = [category objectAtIndex:0];
//                    [_mSegmentedControl addItem:title];
                    [_mSegmentedControl addItemByFontSize:title];
                }
            }
            
        }
        
    }
    return _mSegmentedControl;
}

- (void) segmentValueChanged:(int)nowIndex
{
    //防止点击tab文字重影的问题
    for (UIView*view in self.contentScrollView.subviews )  {
        if ([view isKindOfClass:[AMNewProductsItem class]]) {
                    [view removeFromSuperview];
                }
            }

    currentNum = 0;
    int pageNum = currentNum / 4 + ((currentNum%4)>0?1:0);
    [self refreshArrowState:1 sum:pageNum];
    
    currentRequestPage = 0;
    self.newProductsMode = nowIndex;
    
    //拼凑打点,nowIndex从0开始(第0个点已经分配给每个item共用)，需要加1
    NSString *clickId = [NSString stringWithFormat:@"1-%@-%d-%@",self.pageId,nowIndex+1,self.pageId];
    [AMLogUtils appendLog:clickId];
}

- (void) refreshArrowState:(int)index sum:(int)sumpage
{
    if(index == 1)
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
            AMNewProductsListItem * category = [self.magazineList objectAtIndex:i];
            AMNewProductsItem * categoryItem = [[AMNewProductsItem alloc] init];
            
            [categoryItem setSubject:category.subject];
            NSString *priceConvert = [NSString stringWithFormat:@"%2g",[category.rmbPrice.amount doubleValue]];
            [categoryItem setPriceAndUnit:priceConvert setUnit:category.unit];
            
            if(category.listImgUrl != nil){
                [categoryItem.imageView clear];
                categoryItem.imageView.url = [NSURL URLWithString:category.listImgUrl];
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
            
//            if(i%4 == 0){
//                tempX += (110 + 40);
//            }else if(i%4 == 1){
//                tempX -= (110 +40);
//                tempY += (180+10);
//            }else if(i%4 == 2){
//                tempX += (110 + 40);
//            }else{
//                tempY = 20;
//                tempX += (110 + 60);
//            }
            
            if(i%4 == 0){
                tempX += (110 + 40);
            }else if(i%4 == 1){
                tempX -= (110 +40);
                tempY += (160+10);
            }else if(i%4 == 2){
                tempX += (110 + 40);
            }else{
                tempY = 20;
                tempX += (110 + 60);
            }
        }
        
        
        int pageNum = size/4 + ((size%4)>0?1:0);
        self.contentScrollView.contentSize = CGSizeMake(self.contentScrollView.frame.size.width * pageNum, self.contentScrollView.frame.size.height);
        
        if(self.contentScrollView.contentOffset.x == 0){
             [self refreshArrowState:1 sum:pageNum];
        }
        
        isLoading = NO;
        
    }
    [self endLoadingView];
        
}


- (IBAction)redirectToOfferDetail:(id)sender
{
    int index = ((MyUITapGestureRecognizer *)sender).param;
    AMNewProductsListItem *item = [self.magazineList objectAtIndex:index];
    //对每个item，共用一个打点标示0
    NSString *clickId = [NSString stringWithFormat:@"1-%@-0-%@",self.pageId,PAGE_THREE];
    [AMLogUtils appendLog:clickId];
    NSString *offerId = [NSString stringWithFormat:@"%@",item.offerId];
    AMOfferTabViewController * controller = [[[AMOfferTabViewController alloc] initWithOfferId:offerId offerName:item.subject preViewName:nil] autorelease];  
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES]; 
}

#pragma load data

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:20 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcacheamon3/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	_objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (void)loadObjectsFromRemote {
    
    [self.view addSubview:self.segmentLoadingView];
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMNewProductsListResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWPRODUCTS_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewProductsListResult class]];
            loader.objectMapping = [AMNewProductsListResult sharedObjectMapping];
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
    
    if(self.segmentLoadingView){
        [self.segmentLoadingView removeFromSuperview];  
    }
    
    if(objects != nil
       && objects.count > 0){
         AMNewProductsListResult * result = (AMNewProductsListResult*)[objects objectAtIndex:0];
        
        if(result != nil
           && result.resultList != nil
           && result.resultList.count >0){
            NSLog(@"total:%@ page:%@", result.totalCount.stringValue,result.pageSize.stringValue);
            if(result.resultList != nil){
                NSLog(@"list count:%d", result.resultList.count);
            }else{
                NSLog(@"newslist null");
            }
            
            sum = result.totalCount.intValue;
            currentRequestPage ++;
            currentNum += result.resultList.count;
            
            [self performSelectorOnMainThread:@selector(appendTableWith:) withObject:result waitUntilDone:YES];
            
        }
                

    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
}

-(void) appendTableWith:(AMNewProductsListResult *)data 
{ 
    if(self.magazineList == nil){
        self.magazineList =  [[NSMutableArray alloc] initWithCapacity:data.totalCount.intValue];

    }
    int beginIndex = self.magazineList.count;
    [self.magazineList addObjectsFromArray:data.resultList];
    [self appendMore:beginIndex];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
}

-(void)loadRequest:(int)page
{
    if(_request == nil){
        _request = [[AMNewProductsListRequest alloc] init];
    }
    
    _request.operationId = self.operationId;
    
    _request.pageIndex = [NSNumber numberWithInt:page];
    _request.requestURL = OCEAN_API_URL_NEWPRODUCTS_LIST;
    
    [self showLoadingView];
    [self loadObjectsFromRemote];
    
} 


#pragma scroll

- (void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView  
{  
    int pageIndex = fabs(self.contentScrollView.contentOffset.x) / self.contentScrollView.frame.size.width + 1;
    int sumPageNum = sum/4 + ((sum%4)>0?1:0);
    int pageNum = currentNum / 4 + ((currentNum%4)>0?1:0);
    if(currentNum < sum && pageIndex == pageNum && isLoading == NO){
        isLoading = YES;
        [self loadRequest:currentRequestPage+1];
    }
    [self refreshArrowState:pageIndex sum:sumPageNum];
}  

@end

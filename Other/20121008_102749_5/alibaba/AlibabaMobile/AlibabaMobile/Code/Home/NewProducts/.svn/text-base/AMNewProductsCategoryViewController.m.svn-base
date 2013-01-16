//
//  NewPrudoctsCategoryViewController.m
//  AlibabaMobile
//
//  Created by xiaowen  on 12-5-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsCategoryViewController.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "AMHotRankResult.h"
#import "AMNewProductsCategoryRequest.h"
#import "AliImageMagazineCategoryItem.h"

#import "ImageMagazineDetailViewController.h"
#import "AMNewProductsListViewController.h"
#import "AMLogUtils.h"

@interface AMNewProductsCategoryViewController() {
    AMNewProductsCategoryRequest * _request;
    NSMutableArray    * _magazineCateList;
    HJObjManager * _objMan;
    BOOL _isDressCatetoryOnly;
}

@property (nonatomic, retain) IBOutlet UIScrollView * contentScrollView;

-(void)objManInit;
-(void)loadRequest;

@end


@implementation AMNewProductsCategoryViewController

@synthesize contentScrollView = _contentScrollView;
@synthesize parentTitle = _parentTitle;

- (id)init
{
    [super init ];
    if (self) {
        // Custom initialization
        _isDressCatetoryOnly = YES;
        _magazineCateList = [[NSMutableArray alloc] init];
    }
    return self;
}

-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil{
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])
    {
        _isDressCatetoryOnly = YES;
        _magazineCateList = [[NSMutableArray alloc] init];
    }
    return self;
}
- (void) dealloc
{
    [_request release];
    [_magazineCateList release];
    
    [_objMan release];
    
    [_contentScrollView release];
    [_parentTitle release];
    [super dealloc];
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setTitle: @"新品专区"];
    [self setBackButtonText:self.parentTitle];
    [self objManInit];
    
    [self showLoadingView];
    [self loadRequest];
}
-(void) viewDidUnload
{
    [_objMan release];
    _objMan = nil;
    [_request release];
    _request = nil;
    [_magazineCateList release];
    _magazineCateList = nil;
    self.contentScrollView = nil;
    [super viewDidUnload];
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) setContentView
{
    if(_magazineCateList != nil
       && _magazineCateList.count > 0){
        int size = _magazineCateList.count;
        
        int tempX = 25;
        int tempY = 10;
        
        for(int i=0; i<size; i++){
            
            AMHotRankResult *category = [_magazineCateList objectAtIndex:i];//数据结构和热销排行类似，复用
            AliImageMagazineCategoryItem * categoryItem = [[AliImageMagazineCategoryItem alloc] init];
            categoryItem.titleLabel.text = category.operationDesc;

            if(category.imageUrl!=nil){
                [categoryItem.imageView clear];
                categoryItem.imageView.url = [NSURL URLWithString:category.imageUrl];
                [_objMan manage:categoryItem.imageView];

            }
            
            categoryItem.imageView.userInteractionEnabled = YES;
            
            MyUITapGestureRecognizer * clickRecognizer = [[MyUITapGestureRecognizer alloc] initWithTarget:self action:@selector(switchClickAction:)];
            clickRecognizer.param = i;
            [categoryItem.imageView addGestureRecognizer:clickRecognizer];
            [clickRecognizer release];

            categoryItem.frame = CGRectMake(tempX, tempY, categoryItem.frame.size.width, categoryItem.frame.size.height);
            [self.contentScrollView addSubview:categoryItem];
            [categoryItem release];
            
            if(i%2 == 0){
                tempX += (130 + 15);
            }else{
                tempX = 25;
                tempY += (150+10);
            }
        }
        if(size%2 == 1){
            tempY += (150 + 10);
        }
        self.contentScrollView.contentSize = CGSizeMake(self.contentScrollView.frame.size.width, tempY);
    }
    
    [self endLoadingView];
}

-(IBAction)switchClickAction:(id)sender
{
    int index = ((MyUITapGestureRecognizer *)sender).param;
    
    AMHotRankResult * cateItem = [_magazineCateList objectAtIndex:index];
    
    if(cateItem != nil){
        [AMLogUtils appendLog:cateItem.clickId];
        AMNewProductsListViewController * newProductsListViewController  = [[AMNewProductsListViewController alloc] initWithSecondcate:cateItem.appPath.params.secondcate title:cateItem.appPath.params.cateId pageId:cateItem.appPath.pageId];
        [self.navigationController pushViewController:newProductsListViewController animated:YES];
#warning 修改人孟希羲
        [newProductsListViewController release];
            
        }
}

#pragma load data

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:10 memCacheSize:20];
    
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
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* contentMapping = [AMHotRankResult sharedObjectMapping];
    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWPRODUCTS_CATEGORY usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        loader.method = RKRequestMethodPOST;
        loader.params = _request;
    }];
}


- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
    
    // Convert body to real JSON NSString
    NSRange range = {0, [[response bodyAsString] length]};
    NSString *trimmedJson1 = [[[response bodyAsString] substringWithRange: range] stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
    NSString *trimmedJson2 = [trimmedJson1 stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSString *trimmedJson = [trimmedJson2 stringByReplacingOccurrencesOfString:@"\\" withString:@""];
    
    //再截一次，先实现，后优化
    NSRange rangeFinal = {25, [trimmedJson length]-27};
    NSString *trimmedJsonFinal = [trimmedJson substringWithRange:rangeFinal];
    NSLog(@"Trimmed payload: %@", trimmedJsonFinal);
    
    [(NSMutableData*)[response body] setData: [trimmedJsonFinal dataUsingEncoding: NSUTF8StringEncoding]];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
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
	[_magazineCateList removeAllObjects];
    if (_isDressCatetoryOnly) {
        for (AMHotRankResult *category in objects) {
            if ([category.operationDesc rangeOfString:@"服装"].length>0||[category.operationDesc rangeOfString:@"服饰"].length>0) 
            {
                [_magazineCateList addObject:category];
            }
        }
        
    }else {
        [_magazineCateList addObjectsFromArray:objects];
    }

    if(_magazineCateList != nil
       && _magazineCateList.count > 0){

        [self setContentView];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
}


-(void)loadRequest
{
    _request = [[AMNewProductsCategoryRequest alloc] init];
    
    [self loadObjectsFromRemote];
    
} 


@end

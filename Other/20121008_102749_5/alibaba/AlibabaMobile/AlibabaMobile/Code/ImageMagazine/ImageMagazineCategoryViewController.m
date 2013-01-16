//
//  ImageMagazineCategoryViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ImageMagazineCategoryViewController.h"
#import "ConstDef.h"
#import "AMImgMagazineRequest.h"
#import "AMImgMagazineCategory.h"
#import "UIHelp.h"
#import "AliImageMagazineCategoryItem.h"
#import "AMNewsItem.h"
#import "ImageMagazineDetailViewController.h"
#import "ImageMagazineListViewController.h"


@interface ImageMagazineCategoryViewController() {
    AMImgMagazineRequest * _request;
    NSMutableArray    * _magazineCateList;
    HJObjManager * _objMan;
}

@property (nonatomic, retain) IBOutlet UIScrollView * contentScrollView;

-(void)objManInit;
-(void)loadRequest;

@end


@implementation ImageMagazineCategoryViewController

@synthesize contentScrollView = _contentScrollView;
@synthesize parentTitle = _parentTitle;

- (id)init
{
    [super init ];
    if (self) {
        // Custom initialization
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
    
    [self setTitle: @"画报专题"];
    [self setBackButtonText:self.parentTitle];
    [self objManInit];
    
    [self.mLoadingView showLoadingView];
    [self loadRequest];
}

- (void)viewDidUnload {
    [_request release];
    _request = nil;
    [_objMan release];
    _objMan = nil;
    _contentScrollView = nil;
    [_magazineCateList release];
    _magazineCateList = nil;
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
            AMImgMagazineCategory * category = [_magazineCateList objectAtIndex:i];
            
            AliImageMagazineCategoryItem * categoryItem = [[AliImageMagazineCategoryItem alloc] init];
            categoryItem.titleLabel.text = category.categoryName;
            if(category.listImgMagazineItem != nil
               && category.listImgMagazineItem.count > 0){
                AMNewsItem *item =  [category.listImgMagazineItem objectAtIndex:0];
                if(item.coverUrl != nil){
                    [categoryItem.imageView clear];
                    categoryItem.imageView.url = [NSURL URLWithString:item.coverUrl];
                    [_objMan manage:categoryItem.imageView];

                }
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
    
    AMImgMagazineCategory * cateItem = [_magazineCateList objectAtIndex:index];
    if(cateItem != nil
       && cateItem.categoryId != nil){
        
        ImageMagazineListViewController * magazineListViewController  = [[ImageMagazineListViewController alloc] initWithId:cateItem.categoryId title:cateItem.categoryName];
        [self.navigationController pushViewController:magazineListViewController animated:YES];
        [magazineListViewController release];
        
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
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMImgMagazineCategory sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_MAGAZINE_CATEGORIES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMImgMagazineCategory class]];
            loader.objectMapping = [AMImgMagazineCategory sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _request;
    }];
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
       NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

//extern NSInteger gLastDisplayErrorTimeInterval;
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
	[_magazineCateList release];
    
    _magazineCateList = [objects retain];
    if(_magazineCateList != nil
       && _magazineCateList.count > 0){

        [self setContentView];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    [self endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }
}


-(void)loadRequest
{
    _request = [[AMImgMagazineRequest alloc] init];
    
    [self loadObjectsFromRemote];
    
} 


@end

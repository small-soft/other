//
//  AMHotRankViewController.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankViewController.h"
#import "HJObjManager.h"
#import "ConstDef.h"
#import "AMHotRankRequest.h"
#import "AMHotRankResult.h"
#import "AliTableViewCellCategory.h"
//#import "AMNewsCategoryCell.h"
#import "AMHotRankOfferViewController.h"

@interface AMHotRankViewController ()
@property (nonatomic,retain) HJObjManager *objMan;

@property (retain, nonatomic)UIActivityIndicatorView *loadingIndicator;
@property (nonatomic,retain) AMHotRankRequest *dataRequest;
@property (nonatomic,retain) NSMutableArray *contentData;

- (void)loadObjectsFromRemote ;
@end

@implementation AMHotRankViewController
@synthesize objMan = _objMan;
@synthesize loadingIndicator = _loadingIndicator;
@synthesize dataRequest = _dataRequest;
@synthesize contentTable = _contentTable;
@synthesize parentTitle = _parentTitle;
@synthesize contentData = _contentData;

-(void)dealloc{
    [_objMan release];
    [_loadingIndicator release];
    [_dataRequest release];
    [_contentTable release];
    [_parentTitle release];
    [_contentData release];
    [super dealloc];
}
-(AMHotRankRequest*)dataRequest
{
    if (!_dataRequest) {
        _dataRequest = [[AMHotRankRequest alloc]init];
    }
    return _dataRequest;
}
-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc]init];
    }
    return _contentData;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if ([[self contentData ] count] <= 0) {
        [self loadObjectsFromRemote];
    }
}

-(NSString*)commonTableViewBackButtonTitle
{
    return @"首页";
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"热销排行";
}

- (void)viewDidLoad
{
    
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [_dataRequest release];
    _dataRequest = nil;
    [_contentData release];
    _contentData = nil;
    self.contentTable = nil;
    
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
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


- (void)loadObjectsFromRemote {
    [self.loadingIndicator startAnimating];
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* contentMapping = [AMHotRankResult sharedObjectMapping];
    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
        [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_HOT_RANK_CONTENTS usingBlock:^(RKObjectLoader* loader) {
            // Change Method to POST
            loader.delegate = self;
            loader.method = RKRequestMethodPOST;
            loader.params = self.dataRequest;
        }];
    [super loadObjectsFromRemote];
}



- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
    
    // Convert body to real JSON NSString
    NSRange range = {1, [[response bodyAsString] length] - 2};
    NSString *trimmedJson1 = [[[response bodyAsString] substringWithRange: range] stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
    NSString *trimmedJson2 = [trimmedJson1 stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSString *trimmedJson = [trimmedJson2 stringByReplacingOccurrencesOfString:@"\\" withString:@""];
    
    NSLog(@"Trimmed payload: %@", trimmedJson);
    
    [(NSMutableData*)[response body] setData: [trimmedJson dataUsingEncoding: NSUTF8StringEncoding]];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==-1009) {
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);   
    [self.contentData removeAllObjects];
    [self.contentData addObjectsFromArray:objects];
    [self.contentTable reloadData];
    [super objectLoader:objectLoader didLoadObjects:objects];
}


#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellCategory cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    return [self.contentData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];        
    }
    
    
    
    NSUInteger row = [indexPath row];
    
    AMHotRankResult *content = (AMHotRankResult*)[self.contentData objectAtIndex:row];
    cell.title.text =content.operationDesc;

    return cell;
}

#pragma mark -
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
    AMHotRankResult *data = (AMHotRankResult*)[self.contentData objectAtIndex:row];
    [AMLogUtils appendLog:data.clickId];
    AMHotRankOfferViewController *controller = [[AMHotRankOfferViewController alloc] initWithNibName:@"AMHotRankOfferViewController" bundle:nil];
    controller.catIds = data.appPath.params.cateId;
    controller.cateId = data.appPath.params.comId;
    controller.cateTitle = data.operationDesc;
    controller.pageId = data.appPath.pageId;
    
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES];
    [controller release];
    [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
    
    
    
}

@end


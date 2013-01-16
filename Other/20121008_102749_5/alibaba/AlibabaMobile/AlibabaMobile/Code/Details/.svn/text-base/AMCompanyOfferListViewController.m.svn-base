//
//  AMCompanyOfferListViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCompanyOfferListViewController.h"

#import "AMCompanyProductRequest.h"
#import "AMOfferResult.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "AMMoney.h"
#import "HJObjManager.h"
#import "AMMoreLoadingCell.h"
#import "AMCompanyDetail.h"
#import "AliTableViewCellOfferDetail.h"
#import "AMOfferTabViewController.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "NSAttributedString+HTML.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"
#import "AliLoadingDataView.h"
@interface AMCompanyOfferListViewController()
@property (nonatomic, retain) AliLoadingDataView * mLoadingView; 
@end

@implementation AMCompanyOfferListViewController

@synthesize mTableView, mMemberId, mOfferResult,objMan;
@synthesize request = _requset;
@synthesize objects = _objects;
@synthesize mLoadingView = _mLoadingView;
-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    
    return _mLoadingView;
}

- (void)viewWillAppear:(BOOL)animated
{
    [AMLogUtils appendLog:APP_COM_DETAL_SEVEN];
}

- (id) initWithData:(NSMutableDictionary *)data navigationController:(UINavigationController *)navigationController
{
    self = [super initWithData:data navigationController:navigationController];
    if(self){
        
        mMemberId = [self.dataDict objectForKey:TAB_VIEW_MEMBER_ID];
        
        pageSize = 20;
        beginPage = 1;
        totalNum = 0;
        nowNum = 0;
        
        isLoading = NO;
        
        self.objects = [[NSMutableArray alloc] init];
    }
    return self;
}

-(void)objManInit
{
    objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

-(void)loadRequest
{
    isLoading = YES;
    if (beginPage>1) {
        AMMoreLoadingView *moreLoadingView = [[AMMoreLoadingView alloc] init];
        self.mTableView.tableFooterView = moreLoadingView;
        [moreLoadingView release];
    }else {
        [self.mLoadingView showLoadingView];
    }
    self.request = [[AMCompanyProductRequest alloc] init];
    NSLog(@"companyofferlist member: %@", self.mMemberId);
    self.request.memberId = self.mMemberId;  
    self.request.pageSize = [NSNumber numberWithInt: pageSize];
    self.request.beginPage = [NSNumber numberWithInt: beginPage];

    beginPage++;
    
    [self loadObjectsFromRemote];
    
} 

- (void)loadObjectsFromRemote {
    
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMOfferResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_COMPANY_PRODUCTLIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMOfferResult  class]];
            loader.objectMapping = [AMOfferResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
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
    //	NSLog(@"Loaded objects: %@", objects);    

    id object = [objects objectAtIndex:0];
    if(object != nil){

        AMOfferResult * offer = object;
        totalNum = offer.total.intValue;
        
        NSArray * array = offer.offerList;
        
        NSLog(@"totalNum: %d", totalNum);
        NSLog(@"nowNum: %d", nowNum);
        NSLog(@"objectsNum: %d", self.objects.count);
        
        if(nowNum + offer.offerList.count <= totalNum){
            nowNum += offer.offerList.count;
        }else{
            
            array = [offer.offerList subarrayWithRange:NSMakeRange(0 , totalNum - nowNum)];
            nowNum = totalNum;
        }
          
       [self performSelectorOnMainThread:@selector(setTableDate:) withObject:array waitUntilDone:YES];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    [self.mLoadingView endLoadingView];
    isLoading = NO;
}

- (void) setTableDate:(NSMutableArray *)date
{
    [self.objects addObjectsFromArray:date];
    [self.mTableView reloadData];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {

	NSLog(@"Hit error: %@", error);
    [self.mLoadingView endLoadingView];
    //NSURLErrorDomain Code=-1009 "The Internet connection appears to be offline
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline){
        if (nowNum) {
            AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
            self.mTableView.tableFooterView = errorMessageView;
            [errorMessageView release];
            beginPage--;
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        
    }
    isLoading = NO;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil memberId:(NSString *) memberId
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.mMemberId = memberId;
        
        pageSize = 20;
        beginPage = 1;
        
        totalNum = 0;
        nowNum = 0;
        
        isLoading = NO;
        
        self.objects = [[NSMutableArray alloc] init];
    }
    return self;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    NSUInteger row = [indexPath row];
//    if(row == self.objects.count){
//        return 45;
//    }else{
        return [AliTableViewCellOfferDetail cellHeight];
        
//    }
             
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
//    if(self.objects.count <= 0){
//        return 0;
//    }else if(self.objects.count == totalNum){
//        return self.objects.count;
//    }else{
//        return self.objects.count+1;
//    }
    return self.objects.count;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    [AMLogUtils appendLog:APP_COM_DETAL_EIGHT];
    
    NSUInteger row = [indexPath row];
    if (self.objects.count!=totalNum) { 
        if ([indexPath row]==self.objects.count) {
            return;
        }
    } 
    AMOffer *offer = (AMOffer*)[_objects objectAtIndex:row] ;
    AMOfferTabViewController * offerView = [[AMOfferTabViewController alloc] initWithOfferId:offer.offerId.stringValue offerName:offer.subject preViewName:nil];
    [self.navigationController pushViewController:offerView animated:YES];
#warning  修改人孟希羲
    [offerView release];
     [self.mTableView deselectRowAtIndexPath:indexPath animated:NO];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    
//    if(self.objects.count < totalNum && row == self.objects.count){
//        
//        AMMoreLoadingCell *cell = (AMMoreLoadingCell *)[tableView 
//                                                dequeueReusableCellWithIdentifier: [AMMoreLoadingCell cellIdentifer]];
//        if (cell == nil)  
//        {
//            cell =[AMMoreLoadingCell createCell];
//        }
//        
//        return cell;
//    }
    AliTableViewCellOfferDetail *cell = (AliTableViewCellOfferDetail *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellOfferDetail cellIdentifer]];
    
    if (cell == nil){
        cell = [AliTableViewCellOfferDetail createCell];    
    }
    AMOffer *offer = (AMOffer*)[_objects objectAtIndex:row] ;
    [cell cellSetData:cell amOffer:offer];
    [self.objMan manage:cell.icon];
    
    
    return cell;
}


- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if ((maximumOffset - currentOffset <= 10.0)) {
        if(!isLoading)
            if (nowNum < totalNum) {
                [self loadRequest];
            }
    }
        
}


#pragma mark - View lifecycle

- (void) dealloc
{
    [mTableView release];
    [mMemberId release];
    [mOfferResult release];
    [_requset release];
    [_objects release];
    [objMan release];
    self.mLoadingView = nil;
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.mTableView.delegate  = self;
    self.mTableView.dataSource = self;
   
    
    [self objManInit];
    [self loadRequest];
}

- (void)viewDidUnload{
    self.mLoadingView = nil;
    [super viewDidUnload];
}
@end

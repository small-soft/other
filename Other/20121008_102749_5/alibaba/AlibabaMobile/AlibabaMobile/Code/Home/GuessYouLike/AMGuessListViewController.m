//
//  AMGuessListViewController.m
//  AlibabaMobile
//
//  Created by  xiaowen on 12-6-5.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#import "AMGuessListViewController.h"

#import "AMGuestRequest.h"
#import "AMGuessResult.h"
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
#import "AliToastView.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

@implementation AMGuessListViewController

@synthesize mTableView, mOfferResult,objMan;
@synthesize request = _requset;
@synthesize objects = _objects;
@synthesize parentTitle = _parentTitle;

- (void)viewWillAppear:(BOOL)animated
{
    
}

-(NSString*)commonTableViewNavigationTitle
{
    return @"猜您喜欢";
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
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
    self.request = [[AMGuestRequest alloc] init];
    
    [self loadObjectsFromRemote];
    
} 

- (void)loadObjectsFromRemote {
    
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMGuessResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_GUEST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMGuessResult  class]];
            loader.objectMapping = [AMGuessResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
    [super loadObjectsFromRemote];
    
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
    
    id object = [objects objectAtIndex:0];
    if(object != nil){
        
        AMGuessResult * offer = object;
        NSArray * array = offer.offerList;

        
        [self performSelectorOnMainThread:@selector(setTableDate:) withObject:array waitUntilDone:YES];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
    isLoading = NO;
    [super objectLoader:objectLoader didLoadObjects:objects];
}

- (void) setTableDate:(NSMutableArray *)date
{
    
    [self.objects addObjectsFromArray:date];
    [self.mTableView reloadData];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        isLoading = NO;
        
        self.objects = [[NSMutableArray alloc] init];
    }
    return self;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    if(row == self.objects.count){
        return 45;
    }else{
        return [AliTableViewCellOfferDetail cellHeight];
        
    }
    
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{    
    if(self.objects.count <= 0){
        return 0;
    }else{
        return self.objects.count;
    }
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    [AMLogUtils appendLog: APP_GUESS_ONE]; 
    NSUInteger row = [indexPath row];
    AMOffer *offer = (AMOffer*)[_objects objectAtIndex:row] ;
    AMOfferTabViewController * offerView = [[AMOfferTabViewController alloc] initWithOfferId:offer.offerId.stringValue offerName:offer.subject preViewName:nil];
    [self.navigationController pushViewController:offerView animated:YES];
    [self.mTableView deselectRowAtIndexPath:indexPath animated:NO];
#warning 修改人孟希羲
    [offerView release];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    
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
    if ((maximumOffset - currentOffset <= 30.0)) {
        if(!isLoading){
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"亲，没有数据了哦！"] show];
            isLoading = YES;//只提示一次无数据
        }
        
    }
    
}


#pragma mark - View lifecycle

- (void) dealloc
{
    [mTableView release];
    [mOfferResult release];
    [_requset release];
    [_objects release];
    [objMan release];
    
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self objManInit];
    [self loadRequest];
}
- (void)viewDidUnload {
    
    self.objMan = nil;
    self.request = nil;
    [super viewDidUnload];
}

@end

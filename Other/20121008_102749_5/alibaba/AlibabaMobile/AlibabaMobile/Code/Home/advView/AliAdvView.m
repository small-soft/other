//
//  AliAdvView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliAdvView.h"
#import "AMContentRequest.h"
#import "ConstDef.h"
#import "AMHomeContent.h"
#import "AliBannerView.h"
#import "HJObjManager.h"
#import "UIHelp.h"
#import <objc/runtime.h>
#import "AMLogUtils.h"
#import "ImageMagazineDetailViewController.h"
#import "AMBannerContentDetailViewController.h"
#define BUSITYPE_OFFER @"special_offer_content"
#define BUSITYPE_PICTURE_NEWS @"picture_news"
#define BUSITYPE_FORUM @"forum"


@interface AliAdvView()
@property (nonatomic,retain) AMContentRequest *dataRequest;
@property (nonatomic,retain) NSMutableArray *contentData;

@property (nonatomic,retain) AliGallaryView *gallaryView;
@property (nonatomic,retain) HJObjManager *objMan;
@property (retain, nonatomic)UIActivityIndicatorView *loadingIndicator;
@end
@implementation AliAdvView
@synthesize dataRequest=_dataRequest;
@synthesize contentData=_contentData;
@synthesize delegate = _delegate;
@synthesize gallaryView=_gallaryView;
@synthesize bannerData=_bannerData;
@synthesize objMan=_objMan;
@synthesize loadingIndicator=_loadingIndicator;

-(void)dealloc
{
    [_dataRequest release];
    [_contentData release];
    [_delegate release];
    [_gallaryView release];
    [_bannerData release];
    [_objMan release];
    [_loadingIndicator release];
    [super dealloc];
}

-(AMContentRequest*)dataRequest
{
    if (!_dataRequest) {
        _dataRequest = [[AMContentRequest alloc]init];
//        _dataRequest.name = @"home_banner_new";
        _dataRequest.name = @"ios_home_banner";
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
-(NSMutableArray*)bannerData
{
    if (!_bannerData) {
        _bannerData = [[NSMutableArray alloc]init];
    }
    return _bannerData;    
}
-(AliGallaryView*)gallaryView
{
    if (!_gallaryView) {
        _gallaryView = [[AliGallaryView alloc]init];
        _gallaryView.frame = CGRectMake(0.0,0.0, self.frame.size.width, self.frame.size.height);
        _gallaryView.showPageControl=YES;
        _gallaryView.autoScroll=YES;
        _gallaryView.delegate=self;

    }
    return _gallaryView;
}
-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
        
        NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcacheHome/"] ;
        HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
        _objMan.fileCache = fileCache;
        // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
        fileCache.fileCountLimit = 100;
        fileCache.fileAgeLimit = 60*60*24*7; //1 week
        [fileCache trimCacheUsingBackgroundThread];
        
    }
    return _objMan;
    
}
-(UIActivityIndicatorView*)loadingIndicator
{
    if (!_loadingIndicator) {
        _loadingIndicator = [[UIActivityIndicatorView alloc]init];
        _loadingIndicator.frame = CGRectMake(self.frame.size.width/2-10, 57.0, 20.0, 20.0);
        _loadingIndicator.hidesWhenStopped=YES;
        _loadingIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        NSString *systemVersion = [[UIDevice currentDevice] systemVersion];
        if ([systemVersion hasPrefix:@"4.3"] || [systemVersion hasPrefix:@"4.0"]) {
            // don't set color，no this member
        }else{
            _loadingIndicator.color = [UIColor grayColor];
        }
        
        [_loadingIndicator stopAnimating];
    }
    return _loadingIndicator;
}

-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupViews];
    [self loadObjectsFromRemote];
}
-(void)setupViews
{
    [self addSubview:self.loadingIndicator];
    [self addSubview:self.gallaryView];

}

-(void)resetBannerData
{
    [self.bannerData removeAllObjects];
    for (AMHomeContent *content in self.contentData) {
        NSDictionary*data = [NSDictionary dictionaryWithObjectsAndKeys:content.imageUrl, BANNER_PARAMS_URL,[AliBannerView createView],@"view", nil];
        [self.bannerData addObject:data];
    }
   
}

- (void)loadObjectsFromRemote {
    [self.loadingIndicator startAnimating];

    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* contentMapping = [AMHomeContent sharedObjectMapping];
    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CONTENTS usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        loader.method = RKRequestMethodPOST;
        loader.params = self.dataRequest;
    }];
}

/*
 delegate 
 */
-(void)AliGallaryView:(AliGallaryView*)gallaryView didAtIndex:(NSUInteger)itemIndex
{
    UIViewController *controller = [self.delegate superController];
    AMHomeContent *content = (AMHomeContent*)[self.contentData objectAtIndex:itemIndex];
   
    
    [AMLogUtils appendLog: content.clickId];
    if ([content.appPath.busiType isEqualToString:BUSITYPE_PICTURE_NEWS]) {
        ImageMagazineDetailViewController * detailViewController = [[ImageMagazineDetailViewController alloc] initWithNewsId:content.appPath.params.pictureNewsId preTitle:[self.delegate superControllerName]];
        detailViewController.hidesBottomBarWhenPushed = TRUE;
        [controller.navigationController pushViewController:detailViewController animated:YES];
#warning xiugairen mengxixi
        [detailViewController release];
    }
    else //if([content.appPath.busiType isEqualToString:BUSITYPE_FORUM]) 
    {
        AMBannerContentDetailViewController *detail = [[AMBannerContentDetailViewController alloc] initWithNibName:@"AMBannerContentDetailViewController" bundle:nil];
        detail.url = content.appPath.params.entry_url;
        detail.navigationTitle = content.operationDesc;
        detail.showToolBar=NO;
        detail.parentTitle = @"首页";
        detail.hidesBottomBarWhenPushed = TRUE;
        [controller.navigationController pushViewController:detail animated:YES];
        [detail release];
        
    }

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
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{

}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);   
    [self.contentData removeAllObjects];
    [self.contentData addObjectsFromArray:objects];
    [self resetBannerData];
    [self.gallaryView reloadData];
}
- (NSUInteger)numberOfSectionsInGallaryView:(AliGallaryView*)gallaryView
{
    return [self.bannerData count];
}
- (UIControl*)AliGallaryView:(AliGallaryView*)gallaryView atIndex:(NSUInteger)itemIndex
{
    NSDictionary *data = [self.bannerData objectAtIndex:itemIndex];
    AliBannerView *view = [data objectForKey:@"view"];
    view.params = data;
    [self.objMan manage:view.contentView];
    return view;
}

@end


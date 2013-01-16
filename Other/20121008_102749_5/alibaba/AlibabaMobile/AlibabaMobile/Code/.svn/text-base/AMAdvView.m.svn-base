//
//  AMAdvView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMAdvView.h"
#import "AliToastView.h"
#import "AMHomepageDressResult.h"
#import "AMHomepageDressBanner.h"
#import "ConstDef.h"
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

@interface AMAdvView()
@property (nonatomic,retain) NSMutableArray *contentData;

@property (nonatomic,retain) AliGallaryView *gallaryView;
@property (nonatomic,retain) HJObjManager *objMan;
@property (retain, nonatomic)UIActivityIndicatorView *loadingIndicator;
@end

@implementation AMAdvView
@synthesize request=_request;
@synthesize contentData=_contentData;
@synthesize delegate = _delegate;
@synthesize gallaryView=_gallaryView;
@synthesize bannerData=_bannerData;
@synthesize objMan=_objMan;
@synthesize loadingIndicator=_loadingIndicator;
@synthesize md5Checksum = _md5Checksum;
@synthesize blackView = _blackView;


-(void)dealloc
{
    [_blackView release];
    [_request release];
    [_contentData release];
    [_delegate release];
    [_gallaryView release];
    [_bannerData release];
    [_objMan release];
    [_loadingIndicator release];
    [_md5Checksum release];
    [super dealloc];
}
-(AMHomepageDressRequest*)request
{
    if (!_request) {
        _request = [[AMHomepageDressRequest alloc]init];
        //        _dataRequest.name = @"home_banner_new";
        _request.industryId = @"fuzhuangfushi";
        _request.summary = @"";
        _request.configName = @"bannersios";
    }
    return _request;
}
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
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
-(UIView*)blackView
{
    if (!_blackView) {
        _blackView = [[UIView alloc]init];
        _blackView.frame = CGRectMake(0.0,0.0, self.frame.size.width, self.frame.size.height);
        _blackView.backgroundColor = [UIColor blackColor];
        _blackView.alpha = 0.0;
        
    }
    return _blackView;
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
    //[self loadObjectsFromRemote];
}
-(void)setupViews
{
    [self addSubview:self.loadingIndicator];
    [self addSubview:self.gallaryView];
    [self addSubview:self.blackView];
    
}

-(void)resetBannerData
{
    [self.bannerData removeAllObjects];
    for (AMHomepageDressChilden *homepageDressChilden in self.contentData) {
        NSDictionary*data = [NSDictionary dictionaryWithObjectsAndKeys:homepageDressChilden.imageUrl, BANNER_PARAMS_URL,[AliBannerView createView],@"view", nil];
        [self.bannerData addObject:data];
    }
}


- (void)loadObjectsFromRemote {
    [self.loadingIndicator startAnimating];
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
//    
//    // Register our mappings with the provider
//	RKObjectMapping* contentMapping = [AMHomepageDressResult sharedObjectMapping];
//    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_INDUSTRY_CONTENTS usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMHomepageDressResult class]];
            loader.objectMapping = [AMHomepageDressResult sharedObjectMapping];
        }
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
}
/*
 delegate 
 */
-(void)AliGallaryView:(AliGallaryView*)gallaryView didAtIndex:(NSUInteger)itemIndex
{
    UIViewController *controller = [self.delegate superController];
    AMHomepageDressChilden *homepageDressChilden = (AMHomepageDressChilden *)[self.contentData objectAtIndex:itemIndex];
    
    [AMLogUtils appendLog: homepageDressChilden.clickId];
    if ([homepageDressChilden.jumpPath.busiType isEqualToString:BUSITYPE_PICTURE_NEWS]) {
        ImageMagazineDetailViewController * detailViewController = [[ImageMagazineDetailViewController alloc] initWithNewsId:homepageDressChilden.jumpPath.params.pictureNewsId preTitle:[self.delegate superControllerName]];
        detailViewController.hidesBottomBarWhenPushed = TRUE;
        [controller.navigationController pushViewController:detailViewController animated:YES];
#warning xiugairen mengxixi
        [detailViewController release];
    }
    else //if([content.appPath.busiType isEqualToString:BUSITYPE_FORUM]) 
    {
        AMBannerContentDetailViewController *detail = [[AMBannerContentDetailViewController alloc] initWithNibName:@"AMBannerContentDetailViewController" bundle:nil];
        detail.url = homepageDressChilden.jumpPath.params.entry_url;
        detail.navigationTitle = homepageDressChilden.name;
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
   /* NSRange range = {1, [[response bodyAsString] length] - 2};
    NSString *trimmedJson1 = [[[response bodyAsString] substringWithRange: range] stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
    NSString *trimmedJson2 = [trimmedJson1 stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSString *trimmedJson = [trimmedJson2 stringByReplacingOccurrencesOfString:@"\\" withString:@""];
    
    NSLog(@"Trimmed payload: %@", trimmedJson);
    
    [(NSMutableData*)[response body] setData: [trimmedJson dataUsingEncoding: NSUTF8StringEncoding]];*/
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
//        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show]; 
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
//         [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show]; 
        gLastDisplayErrorTimeInterval = currentTime;
    }
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    //NSLog(@"Loaded objects: %@", error);  
    //NSLog(@"Hit error: %@", error);
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSArray*)objects {
	NSLog(@"Loaded objects: %@", objects);   
    AMHomepageDressResult *result = (AMHomepageDressResult*)[objects objectAtIndex:0];
    
    if (result.bannersios.hasChild && [result.bannersios.type isEqualToString:@"banners"]) {
        self.md5Checksum = result.bannersios.md5Checksum;
        NSUInteger childenCount = [result.bannersios.children count];
        if (childenCount > 0) {
            [self.contentData removeAllObjects];
            [self.contentData addObjectsFromArray:result.bannersios.children];
            [self resetBannerData];
            [self.gallaryView reloadData];
        }
        else {
            [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"对不起，没有数据请稍后再试！"] show]; 
        }
    }
    else {
//        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"申请数据失败请稍后再试！"] show]; 
    }
    
//    [objectLoader.objectMapping release];
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

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end

//
//  ImageMagazineDetailViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ImageMagazineDetailViewController.h"
#import <RestKit/RestKit.h>
#import "AMNewsDetailRequest.h"
#import "AMNewsItem.h"
#import "ConstDef.h"
#import "AMNewsTitle.h"
#import "AMNewsTitleItem.h"
#import "HJManagedImageV.h"
#import "HJObjManager.h"
#import "AMImage.h"
#import "AMNewsItemImage.h"
#import <QuartzCore/QuartzCore.h>
#import "AliBackButton.h"
#import "UIHelp.h"
#import "AMOfferTabViewController.h"
#import "StringUtils.h"
#import "AliButton.h"
#import "AliToastView.h"


@implementation MyUITapGestureRecognizer

@synthesize param = _param;

- (void)dealloc
{

    [super dealloc];
}

@end

@interface ImageMagazineDetailViewController()
{
    int currentIndex;
    BOOL isFullScreen;
    BOOL infoViewOpened;
    UIImageView * focusedHoverImg;
}

@property (nonatomic, retain) AMNewsDetailRequest*detailRequest;

@property (nonatomic, retain) NSString * newsId;
@property (nonatomic, retain) AMNewsItem * newsItem;
@property (nonatomic, retain) NSString * preTitle;

@property (nonatomic, retain) IBOutlet AliBackButton * backButton;
@property (nonatomic ,retain) IBOutlet AliButton * detailButton;

@property (nonatomic, retain) IBOutlet UIView * topBarView;
@property (nonatomic, retain) IBOutlet UIView * bottomView;

@property (nonatomic, retain) IBOutlet UILabel * titleLabel;
@property (nonatomic, retain) IBOutlet UILabel * pageLabel;
@property (nonatomic, retain) IBOutlet UIButton * pickButton;
@property (nonatomic, retain) IBOutlet UILabel * infoLabel;
@property (nonatomic, retain) IBOutlet UIView * infoView;
@property (nonatomic, retain) IBOutlet UIScrollView * infoScrollView;

@property (nonatomic, retain) IBOutlet UIScrollView * galleryScrollView;
@property (nonatomic, retain) IBOutlet UIScrollView * switchScrollView;

@property (nonatomic,retain) HJObjManager *objMan;

- (void)loadObjectsFromRemote;
-(void)objManInit:(int)bufferSize;
-(void)showInfoView;
- (void) setSwitchContent;
- (void) setGalleryContent;
- (void) setInfoData;
- (void) galleryContentInitWithIndex:(int)index;
- (void) changeSwitchState:(int)nextIndex;
- (void) switchViewDragEndAction;
- (void) galleryViewDragEndAction;

@end


@implementation ImageMagazineDetailViewController

@synthesize backButton = _backButton;
@synthesize detailButton = _detailButton;
@synthesize topBarView = _topBarView;
@synthesize bottomView = _bottomView;

@synthesize newsId = _newsId;
@synthesize newsItem = _newsItem;

@synthesize detailRequest = _detailRequest;

@synthesize titleLabel = _titleLabel;
@synthesize pageLabel = _pageLabel;
@synthesize galleryScrollView = _galleryScrollView;
@synthesize switchScrollView = _switchScrollView;
@synthesize pickButton = _pickButton;
@synthesize infoLabel = _infoLabel;
@synthesize infoView = _infoView;
@synthesize infoScrollView = _infoScrollView;

@synthesize preTitle = _preTitle;

@synthesize objMan = _objMan;

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
        //        _mLoadingView.delegate = self;
    }
    
    return _mLoadingView;
}

- (id)initWithNewsId:(NSString *) newsId preTitle:(NSString *)pretitle
{
    [super initWithNibName:@"ImageMagazineDetailViewController" bundle:nil];
    if(self){
        self.newsId = newsId;
        self.preTitle = pretitle;
    }
    return self;
}

- (void)viewWillAppear:(BOOL)animated; 
{
    self.navigationController.navigationBar.hidden = YES;
}


-(void) dealloc
{
    [_preTitle release];
    
    [_topBarView release];
    [_bottomView release];
    
    [_newsId release];
    [_detailRequest release];
    
    [_pickButton release];
    [_infoView release];
    [_infoLabel release];
    [_infoScrollView release];
    
    [_newsItem release];
    [_titleLabel release];
    [_pageLabel release];
    [_galleryScrollView release];
    [_switchScrollView release];
    [_objMan release];
    [_detailButton release];
    
    [focusedHoverImg release];
    
    [super dealloc];
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.backgroundColor = [UIHelp colorWithHexString:@"0x333333"];  
    [self.navigationItem setHidesBackButton:TRUE animated:NO];
    
    self.backButton = [[AliBackButton alloc] initWithTitle:self.preTitle];
    [self.backButton setButtonImageNormal:@"btn_tb_black_back" pressed:@"btn_tb_black_back_tap"];
    self.backButton.frame = CGRectMake(5, 8, self.backButton.frame.size.width, self.backButton.frame.size.height);
    [self.backButton addTarget:self action:@selector(navigationBack) forControlEvents:UIControlEventTouchUpInside];
    [self.topBarView addSubview:self.backButton];
    self.backButton = nil;
    
    
    self.detailButton = [[AliButton alloc] initWithTitle:@"详情"];
    [self.detailButton setButtonImageNormal:@"btn_tb_black_normal" pressed:@"btn_tb_black_normal_tap"];
    self.detailButton.frame = CGRectMake(320-5-self.detailButton.frame.size.width, 8, self.detailButton.frame.size.width, self.detailButton.frame.size.height);
    [self.detailButton addTarget:self action:@selector(directToOfferDetail) forControlEvents:UIControlEventTouchUpInside];
    [self.topBarView addSubview:self.detailButton];
    self.detailButton.alpha = 0.0f;
    
    
    
    
    self.infoView.hidden = YES;
    self.bottomView.hidden = YES;
    
    [self.mLoadingView showLoadingView];
    [self loadObjectsFromRemote];
   
}

- (void)viewDidUnload
{
    self.backButton = nil;
    self.detailButton = nil;
    self.topBarView = nil;
    self.bottomView = nil;
    [_detailRequest release];
    _detailRequest = nil;
    self.pickButton = nil;
    self.infoView = nil;
    self.infoLabel = nil;
    self.infoScrollView = nil;
    self.newsItem = nil;
    self.titleLabel = nil;
    self.pageLabel = nil;
    self.galleryScrollView = nil;
    self.switchScrollView = nil;
    self.detailButton = nil;
    self.objMan = nil;
    [focusedHoverImg release];

    
    [super viewDidUnload];
     
}

-(void)navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) setContentData
{
    currentIndex = 0;
    infoViewOpened = NO;
    isFullScreen = YES;
    
    int count = self.newsItem.newsItemImages.count;
    [self objManInit:count *2];
    
    [self setSwitchContent];
    [self setGalleryContent];
    [self setInfoData];
    
    self.infoView.hidden = NO;
    self.bottomView.hidden = NO;
    [self.mLoadingView endLoadingView];
    
}

- (void) setInfoData
{
    if(self.newsItem != nil
       && self.newsItem.newsItemImages != nil
       && self.newsItem.newsItemImages.count >0){
        
        if(self.newsItem.title != nil){
            self.titleLabel.text = self.newsItem.title;
        }
        
        int size = self.newsItem.newsItemImages.count;
        self.pageLabel.text = [NSString stringWithFormat:@"%d/%d", currentIndex+1, size];
        
        AMNewsItemImage * imageItem = [self.newsItem.newsItemImages objectAtIndex:currentIndex];
        self.infoLabel.text = [StringUtils removeHtmlLabelsAndBlanksFromString: imageItem.picDesc];
        self.infoLabel.frame = CGRectMake(self.infoLabel.frame.origin.x, self.infoLabel.frame.origin.y, self.infoLabel.frame.size.width, [UIHelp getLabelSizeWithFont:self.infoLabel.font labelString:self.infoLabel.text labelWidth:self.infoLabel.frame.size.width].height);
        self.infoScrollView.contentSize = CGSizeMake(self.infoScrollView.frame.size.width, self.infoLabel.frame.size.height);
        
        [self showInfoView];
    }else{
        self.infoView.hidden = YES;
    }
    
    [self.pickButton addTarget:self action:@selector(openInfoView) forControlEvents:UIControlEventTouchUpInside];
}

- (void)openInfoView
{
    if(infoViewOpened){
        infoViewOpened = NO;
    }else{
        infoViewOpened = YES;
        
    }
    [self showInfoView];
}

-(void)showInfoView
{
    if(infoViewOpened){

        [UIView beginAnimations:@"scale" context:nil];
        [UIView setAnimationDuration:0.4];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDidStopSelector:@selector(infoViewAnimationEnd)];
        
        self.infoView.frame = CGRectMake(0, 274, 320, 106);
        [self.pickButton setBackgroundImage:[UIImage imageNamed:@"icon_arrow"] forState:UIControlStateNormal];
         
         [UIView commitAnimations];
        
        
        
    }else{
         
        [UIView setAnimationDuration:0.4];
        [UIView beginAnimations:@"scale" context:nil];
        self.infoScrollView.hidden = YES;
        self.infoView.frame = CGRectMake(0, 329, 320, 51);   
         [self.pickButton setBackgroundImage:[UIImage imageNamed:@"icon_arrow_up"] forState:UIControlStateNormal];
        [UIView commitAnimations];
        
        
    }
}

- (IBAction)infoViewAnimationEnd
{
    if(infoViewOpened){
        self.infoScrollView.hidden = NO;
    }else{
        self.infoScrollView.hidden = YES;
    }
}

- (void) setGalleryContent
{
    //setting paged scrollview  
    self.galleryScrollView.directionalLockEnabled = YES;  
    self.galleryScrollView.pagingEnabled = YES;  
    

    self.galleryScrollView.showsVerticalScrollIndicator = NO;  
    self.galleryScrollView.showsHorizontalScrollIndicator = NO;  
    self.galleryScrollView.delegate = self; 
    MyUITapGestureRecognizer * clickRecognizer = [[MyUITapGestureRecognizer alloc] initWithTarget:self action:@selector(fullScreen)];
    [self.galleryScrollView addGestureRecognizer:clickRecognizer];
    [clickRecognizer release];
    
     if(self.newsItem !=nil 
       && self.newsItem.newsItemImages != nil 
       && self.newsItem.newsItemImages.count > 0){

        int size = self.newsItem.newsItemImages.count;
        
        int pageNum = size;
        self.galleryScrollView.contentSize = CGSizeMake(self.galleryScrollView.frame.size.width*pageNum, self.galleryScrollView.frame.size.height);
        
        self.pageLabel.text = [NSString stringWithFormat:@"(1/%d)", pageNum];
        
        
        for(int i=0; i<size; i++){
            
            
            UIActivityIndicatorView * loadingView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle: UIActivityIndicatorViewStyleWhiteLarge];
            [loadingView sizeToFit];
            loadingView.frame =CGRectMake((self.galleryScrollView.frame.size.width-loadingView.frame.size.width)/2 + self.galleryScrollView.frame.size.width*i, (self.galleryScrollView.frame.size.height-loadingView.frame.size.height)/2, loadingView.frame.size.width, loadingView.frame.size.height);
            [self.galleryScrollView addSubview:loadingView];
            [loadingView startAnimating];
            [loadingView release];
        }
  
        [self galleryContentInitWithIndex:0];
    }

}

-(IBAction)fullScreenAnimationEnd
{
    if(isFullScreen){
        self.topBarView.hidden = NO;
        self.bottomView.hidden = NO;
        self.infoView.hidden = NO;
        
        
    }else{
        self.topBarView.hidden = YES;
        self.bottomView.hidden = YES;
        self.infoView.hidden = YES;
        
        isFullScreen  = YES;
    }
}

- (IBAction)fullScreen
{
    if(isFullScreen){
        [UIView beginAnimations:@"fullscreen" context:nil];
        [UIView setAnimationDuration:0.4];
//        [UIView setAnimationDelegate:self];
//        [UIView setAnimationDidStopSelector:@selector(fullScreenAnimationEnd)];
        
        self.topBarView.alpha = 0.0f;
        self.bottomView.alpha = 0.0f;
        self.infoView.alpha = 0.0f;
//        self.galleryScrollView.frame = CGRectMake(0, 0, 320, 380);
        
        [UIView commitAnimations];
        isFullScreen = NO ;

    }else{
        [UIView beginAnimations:@"nofullscreen" context:nil];
        [UIView setAnimationDuration:0.4];
//        [UIView setAnimationDelegate:self];
//        [UIView setAnimationDidStopSelector:@selector(fullScreenAnimationEnd)];
        
        self.topBarView.alpha = 1.0f;
        self.bottomView.alpha = 1.0f;
        self.infoView.alpha = 1.0f;
//        self.galleryScrollView.frame = CGRectMake(0, 50, 320, 380);

        [UIView commitAnimations];
        isFullScreen = YES;
    }
}

- (IBAction)directToOfferDetail
{
    int index = currentIndex;
    AMNewsItemImage * item = [self.newsItem.newsItemImages objectAtIndex:index];
    if(item.newsItemImageOffer.offerId != nil 
       && item.newsItemImageOffer.offerId.intValue > 0){
        AMOfferTabViewController * offerController = [[[AMOfferTabViewController alloc] initWithOfferId:item.newsItemImageOffer.offerId.stringValue offerName:item.newsItemImageOffer.title preViewName:nil] autorelease];
        
        [self.navigationController pushViewController:offerController animated:YES];
    }else{
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"暂无信息,敬请关注"] show];
    }
   
}

- (void) setSwitchContent
{
    //setting paged scrollview  
    self.switchScrollView.directionalLockEnabled = YES;  
    self.switchScrollView.pagingEnabled = NO;  
    self.switchScrollView.backgroundColor = [UIColor clearColor];  
    self.switchScrollView.showsVerticalScrollIndicator = NO;  
    self.switchScrollView.showsHorizontalScrollIndicator = NO;  
    self.switchScrollView.delegate = self; 
    

    //initData
    int startX = 5;
    int startY = 10;
    int sepertor = 10;
    int imageWidth = 60;
    int imageHeight = 60;
    
    focusedHoverImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"mask_Album_silder_tap"]];
    focusedHoverImg.frame =  CGRectMake(startX, startY-5, imageWidth, imageHeight+5);
    
    if(self.newsItem !=nil 
       && self.newsItem.newsItemImages != nil 
       && self.newsItem.newsItemImages.count > 0){

        
        int size = self.newsItem.newsItemImages.count;
               
        int pageNum = size/4 + (size%4>0?1:0);
        self.switchScrollView.contentSize = CGSizeMake(self.switchScrollView.frame.size.width*pageNum, self.switchScrollView.frame.size.height);

        for(int i=0; i<size; i++){
            
            UIImageView * logoImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"nodata_Album_silder"]];
            [logoImg sizeToFit];
            [[logoImg layer] setBorderWidth:2.0f];
            [[logoImg layer] setBorderColor:[UIColor whiteColor].CGColor];
            logoImg.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageHeight);;
            [self.switchScrollView addSubview:logoImg];
            [logoImg release];
            
            HJManagedImageV * imageView = [[HJManagedImageV alloc] init];
            
            imageView.backgroundColor = [UIColor clearColor];
//            imageView.layer.masksToBounds = YES;
//            imageView.layer.cornerRadius = 10.0;
            imageView.userInteractionEnabled = YES;
            imageView.url = [NSURL URLWithString:((AMNewsItemImage *)[self.newsItem.newsItemImages objectAtIndex:i]).surl];
            [[imageView layer] setShadowOffset:CGSizeMake(0, 4)];
            [[imageView layer] setShadowRadius:6];
            [[imageView layer] setShadowOpacity:1];
            [[imageView layer] setBorderWidth:2.0f];
            [[imageView layer] setBorderColor:[UIColor whiteColor].CGColor];
            [[imageView layer] setShadowColor:[UIColor blackColor].CGColor];
            imageView.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageHeight);
            
            imageView.userInteractionEnabled = YES;
            
            
            MyUITapGestureRecognizer * clickRecognizer = [[MyUITapGestureRecognizer alloc] initWithTarget:self action:@selector(switchClickAction:)];
            clickRecognizer.param = i;
            [imageView addGestureRecognizer:clickRecognizer];
            [clickRecognizer release];
            
            [self.switchScrollView addSubview:imageView];
            [self.objMan manage:imageView];
                       
            
            [imageView release];
        }
        
        [self.switchScrollView addSubview:focusedHoverImg];
        
    }

}

- (void) setFocusHoverImg
{
    int startX = 5;
    int startY = 5;
    int sepertor = 10;
    int imageWidth = 60;
    int imageHeight = 65;
    
    int tempX = startX + (imageWidth + sepertor) * currentIndex;
    
    focusedHoverImg.frame = CGRectMake(tempX, startY, imageWidth, imageHeight);
}

-(IBAction)switchClickAction:(id)sender
{
    int index = ((MyUITapGestureRecognizer *)sender).param;
    
    [self changeSwitchState:index];
    
    currentIndex = index;

    
    [self.galleryScrollView setContentOffset:CGPointMake(self.galleryScrollView.frame.size.width*index, 0) animated:YES];
    [self galleryContentInitWithIndex:index];
    [self setInfoData];
//    [self setFocusHoverImg];
    
}

- (void) changeSwitchState:(int)nextIndex
{
    @synchronized(self){
        int size = self.newsItem.newsItemImages.count;
        int nowOffset = self.switchScrollView.contentOffset.x;
        int pageSize = 70;
        int nowPageStartIndex = nowOffset / pageSize;
        if(nextIndex <= nowPageStartIndex 
           && nowPageStartIndex >0){
            int offset = nowOffset - pageSize;
            [self.switchScrollView setContentOffset:CGPointMake(offset, 0) animated:YES];
        }else if(nextIndex >= nowPageStartIndex + 3
                 && nowPageStartIndex < size-1){
            int offset = nowOffset + pageSize;
            [self.switchScrollView setContentOffset:CGPointMake(offset, 0) animated:YES];
        }
         [self switchViewDragEndAction];
        
        currentIndex = nextIndex;
        
        
        [self setInfoData];
        [self setFocusHoverImg];
    }
    
}

- (void)changeDetailButtonState:(int)index
{

    AMNewsItemImage * item = [self.newsItem.newsItemImages objectAtIndex:index];
    if(item.newsItemImageOffer.offerId == nil 
       || item.newsItemImageOffer.offerId.intValue <= 0){
        self.detailButton.alpha = 0.0f;
    }else{
        self.detailButton.alpha = 1.0f;
    }
}

#pragma data load
-(void)objManInit:(int)bufferSize
{
    self.objMan = [[HJObjManager alloc] initWithLoadingBufferSize:bufferSize memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
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
//	RKObjectMapping* newsItemMapping = [AMNewsItem sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: newsItemMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWS_DETAIL usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewsItem class]];
            loader.objectMapping = [AMNewsItem sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.detailRequest;
    }];
}

#pragma mark RKObjectLoaderDelegate methods

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
	NSLog(@"Loaded objects: %@", objects);    
    AMNewsItem * item = (AMNewsItem*)[objects objectAtIndex:0];
    self.newsItem = item;
    [self setContentData];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    [self endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }
}

-(AMNewsDetailRequest*)detailRequest
{
    if (_detailRequest==nil) {
        _detailRequest = [[AMNewsDetailRequest alloc] init];     
    }
    
    NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
    [formatter setNumberStyle:NSNumberFormatterDecimalStyle];
    _detailRequest.cateId =  [formatter numberFromString: self.newsId];
    [formatter release];
    
    return _detailRequest;
}

#pragma gallery
- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView
{
    if(scrollView == self.galleryScrollView){
        self.galleryScrollView.scrollEnabled = NO;
    }
}

- (void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView  
{  
    if(scrollView == self.galleryScrollView){
        int index = fabs(self.galleryScrollView.contentOffset.x )/self.galleryScrollView.frame.size.width;
        
        [self galleryContentInitWithIndex:index];
        [self galleryViewDragEndAction];
        self.galleryScrollView.scrollEnabled = YES;
    }else if(scrollView == self.switchScrollView){
        [self switchViewDragEndAction];
    }
    
}  

- (void) galleryContentInitWithIndex:(int)index
{
    //initData
    int startX = 0;
    int startY = 0;
    int sepertor = 0;
    int imageWidth = 320;
    int imageHeight = 380;
    
    if(self.newsItem !=nil 
       && self.newsItem.newsItemImages != nil 
       && self.newsItem.newsItemImages.count > 0){
        
        int size = self.newsItem.newsItemImages.count;
        
        int pageNum = size;
        self.galleryScrollView.contentSize = CGSizeMake(self.galleryScrollView.frame.size.width*pageNum, self.galleryScrollView.frame.size.height);
        
        self.pageLabel.text = [NSString stringWithFormat:@"(1/%d)", pageNum];
        
        int i= index;
                  
            HJManagedImageV * imageView = [[HJManagedImageV alloc] init];
//            imageView.contentMode = UIViewContentModeScaleAspectFit;
            imageView.backgroundColor = [UIColor clearColor];
            
            
            imageView.url = [NSURL URLWithString:((AMNewsItemImage *)[self.newsItem.newsItemImages objectAtIndex:i]).url];
            
            [self.objMan manage:imageView];
            imageView.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageHeight);
            
            imageView.userInteractionEnabled = NO;

            [self.galleryScrollView addSubview:imageView];
            [imageView release];
        
        

    }
    [self changeDetailButtonState:index];

}

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate
{
    if(scrollView == self.switchScrollView){
        [self switchViewDragEndAction];
    }else if(scrollView == self.galleryScrollView){
        [self galleryViewDragEndAction];
    }

}

- (void) galleryViewDragEndAction
{
    int index = fabs(self.galleryScrollView.contentOffset.x)/self.galleryScrollView.frame.size.width;  
    
    [self changeSwitchState:index];
}

- (void) switchViewDragEndAction
{
    int pageSize = 70;
    
    int nowOffset = self.switchScrollView.contentOffset.x;
    int extraSpace = nowOffset % pageSize;
    int offset  = (extraSpace >= (pageSize /2)?(nowOffset - extraSpace + pageSize):(nowOffset - extraSpace));
    [self.switchScrollView setContentOffset:CGPointMake(offset, 0) animated:YES];

}


@end

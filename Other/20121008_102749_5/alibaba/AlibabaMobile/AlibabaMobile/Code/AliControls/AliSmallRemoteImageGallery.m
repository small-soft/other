//
//  AliOfferDetailGallery.m
//  AlibabaMobile
//
//  Created by xiejin on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliSmallRemoteImageGallery.h"
#import "HJObjManager.h"
#import "HJManagedImageV.h"
#import <QuartzCore/QuartzCore.h>
#import "AliPageControl.h"
#import "UIHelp.h"

@interface AliSmallRemoteImageGallery ()

@property (nonatomic,retain) HJObjManager *objMan;
@property (nonatomic, retain) IBOutlet UIScrollView * mGalleryScrollView;
@property (nonatomic, retain) IBOutlet UIPageControl * mPageControl;
@property (nonatomic, retain) NSMutableArray * mImageUrlArray;

- (void) initControls;
- (void)objManInit;

@end

@implementation AliSmallRemoteImageGallery

@synthesize mPageControl = _mPageControl;
@synthesize mGalleryScrollView = _mGalleryScrollView;
@synthesize mImageUrlArray = _mImageUrlArray;
@synthesize objMan = _objMan;
@synthesize delegate = _delegate;

- (id) init
{
//    NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"AliSmallRemoteImageGallery" owner:self options:nil] ;
//    self = [nib objectAtIndex:0];
    [super initWithFrame:CGRectMake(0, 0, 320, 115 )]; 
    
    [self initControls];
    
    return self;
}

- (void) initControls
{
    UIImageView * bkImg = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
    bkImg.contentMode = UIViewContentModeScaleToFill;
    bkImg.image = [UIImage imageNamed:@"bg_slide"];
    [self addSubview:bkImg];
    [bkImg release];
    
    self.mGalleryScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
    self.mGalleryScrollView.backgroundColor = [UIHelp colorWithHexString:@"0xDDDCDC"];;
    [self addSubview:self.mGalleryScrollView];
    
    self.mPageControl = [[AliPageControl alloc ] initWithFrame:CGRectMake(141, 88, 38, 36)];
    self.mPageControl.backgroundColor = [UIColor clearColor];
    [self addSubview:self.mPageControl];
    
    //setting paged scrollview  
    self.mGalleryScrollView.directionalLockEnabled = YES;  
    self.mGalleryScrollView.pagingEnabled = YES;   
    self.mGalleryScrollView.showsVerticalScrollIndicator = NO;  
    self.mGalleryScrollView.showsHorizontalScrollIndicator = NO;  
    self.mGalleryScrollView.delegate = self; 
    
    //setting the pagecontrol
    self.mPageControl.hidesForSinglePage = NO;
    self.mPageControl.userInteractionEnabled = NO;
    self.mPageControl.currentPage = 0;
    self.mPageControl.hidden = YES;
    
    [self objManInit];
}


- (void) setImageUrls:(NSMutableArray *) array
{
    if(array  != nil 
        && array.count > 0){
        
        self.mImageUrlArray = [array retain];
       
        //initData
        int startX = 9;
        int startY = 10;
        int sepertor = 9;
        int imageWidth = 95;
 
        int size = self.mImageUrlArray.count;
        int pageNum = size /3 + (size%3>0?1:0);
        self.mGalleryScrollView.contentSize = CGSizeMake(self.mGalleryScrollView.frame.size.width*pageNum, self.mGalleryScrollView.frame.size.height);
        self.mPageControl.numberOfPages = pageNum;
            
        if(size > 3){
            self.mPageControl.hidden = NO;
        }
        
        for(int i=0; i<size; i++){
            UIImageView * logoImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"nodata_Album_silder"]];
            [logoImg sizeToFit];
            logoImg.layer.masksToBounds = YES;
            logoImg.layer.cornerRadius = 2.0;
            logoImg.layer.borderWidth = 1;
            logoImg.layer.borderColor = [UIHelp colorWithHexString:@"0x787878" andAlpha:0.7].CGColor;
            logoImg.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageWidth);;
            [self.mGalleryScrollView addSubview:logoImg];
            [logoImg release];
            
            HJManagedImageV * imageView = [[HJManagedImageV alloc] init];

            imageView.url = [self.mImageUrlArray objectAtIndex:i];
            [self.objMan manage:imageView];
            imageView.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageWidth);
            imageView.backgroundColor = [UIColor clearColor];


            imageView.layer.masksToBounds = YES;
            imageView.layer.cornerRadius = 2.0;
            imageView.layer.borderWidth = 1;
            imageView.layer.borderColor = [UIHelp colorWithHexString:@"0x787878"].CGColor;
            imageView.userInteractionEnabled = YES;
            
            UITapGestureRecognizer * clickRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(galleryClickAction)];
            [imageView addGestureRecognizer:clickRecognizer];
            [clickRecognizer release];
            
            [self.mGalleryScrollView addSubview:imageView];
            [imageView release];
            
            
        }
    }
}

- (IBAction)galleryClickAction
{
    if(self.delegate){
        [self.delegate galleryClickAction];
    }
}

- (void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView  
{  
    int index = fabs(self.mGalleryScrollView.contentOffset.x)/self.frame.size.width;  
    self.mPageControl.currentPage = index;  
}  

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
}

-(void) dealloc
{
    [_mPageControl release];
    [_mGalleryScrollView release];
    [_mImageUrlArray release];
    [_objMan release];
    [_delegate release];
    
    [super dealloc];
}

@end

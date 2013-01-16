//
//  OfferGalleryViewController.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferGalleryViewController.h"
#import "AMOfferDetail.h"

static const int TAB_BTN_PRE = 0;
static const int TAB_BTN_NEXT = 1;

@implementation AMOfferGalleryViewController

@synthesize objMan;

@synthesize mBackButton,mScrollView,mTitleLabel,mPageControl;

- (IBAction)backButtonPressed
{
    self.navigationController.navigationBar.hidden = NO;
    [self.navigationController popViewControllerAnimated:YES];
    
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil offerDetail:(AMOfferDetail *)offerDetail
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        mOfferDetail = [offerDetail retain];
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void) dealloc
{
    [mOfferDetail release];
    
    [mScrollView release];
    [mTitleLabel release];
    [mBackButton release];
    [mPageControl release];

    
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Do any additional setup after loading the view from its nib.
    self.navigationController.navigationBar.hidden = YES;
     [self.navigationItem setHidesBackButton:TRUE animated:NO];
    
    [self.mTitleLabel setAdjustsFontSizeToFitWidth:NO];
    self.mTitleLabel.text = mOfferDetail.subject;


    [self initGallery];
    self.mPageControl.numberOfPages = mOfferDetail.imageList.count;

  [self.mBackButton setTitle:@"返回"];
    [self.mBackButton setButtonImageNormal:@"btn_tb_black_back" pressed:@"btn_tb_black_back_tap"];
    
    self.mBackButton.frame = CGRectMake(5, (44- self.mBackButton.frame.size.height)/2, self.mBackButton.frame.size.width, self.mBackButton.frame.size.height);
    
      [self changeIndatorState:0 sum:mOfferDetail.imageList.count];
}


- (IBAction)tabBtnPressed:(id)sender
{
    int tag = ((UIControl *) sender).tag;
    int pageNum = (int)(self.mScrollView.contentSize.width /self.mScrollView.frame.size.width);
    int index = fabs(self.mScrollView.contentOffset.x)/self.view.frame.size.width;
    if(tag == TAB_BTN_PRE && index > 0){
    
        [self.mScrollView setContentOffset:CGPointMake(self.mScrollView.frame.size.width*(index-1), 0) animated:YES];
//        self.mTitleLabel.text = [NSString stringWithFormat:@"%d/%d", index, pageNum];
        index--;
    }else if(tag == TAB_BTN_NEXT && index < pageNum-1){
        
         [self.mScrollView setContentOffset:CGPointMake(self.mScrollView.frame.size.width*(index+1), 0) animated:YES];
//        self.mTitleLabel.text = [NSString stringWithFormat:@"%d/%d", index+2, pageNum];
        index ++;
    }else{
        
    }
    
    [self changeIndatorState:index sum:pageNum];
    
}

- (void) changeIndatorState:(int)nowpage sum:(int)sum
{
    mPageControl.currentPage = nowpage;
}

- (void) initGallery
{
    //setting paged scrollview  
    self.mScrollView.directionalLockEnabled = YES;  
    self.mScrollView.pagingEnabled = YES;  
    self.mScrollView.backgroundColor = [UIColor clearColor];  
    self.mScrollView.showsVerticalScrollIndicator = NO;  
    self.mScrollView.showsHorizontalScrollIndicator = NO;  
    self.mScrollView.delegate = self; 

    
    //initData
    int startX = 0;
    int startY = 40;
    int sepertor = 0;
    int imageWidth = 320;
    int imageHeight = 320;
    
    if(mOfferDetail !=nil 
       && mOfferDetail.imageList != nil 
       && mOfferDetail.imageList.count > 0){
        
        [self objManInit];
        
        int size = mOfferDetail.imageList.count;
        
        int pageNum = size;
        self.mScrollView.contentSize = CGSizeMake(self.mScrollView.frame.size.width*pageNum, self.mScrollView.frame.size.height);
        
//        self.mTitleLabel.text = [NSString stringWithFormat:@"1/%d", pageNum];
        
        for(int i=0; i<size; i++){
            UIImageView * logoImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg_Album_nodata"]];
            [logoImg sizeToFit];
            logoImg.frame = CGRectMake((self.mScrollView.frame.size.width-logoImg.frame.size.width)/2 + self.mScrollView.frame.size.width*i, (self.mScrollView.frame.size.height-logoImg.frame.size.height)/2, logoImg.frame.size.width, logoImg.frame.size.height);
            [self.mScrollView addSubview:logoImg];
            [logoImg release];
            
            HJManagedImageV * imageView = [[HJManagedImageV alloc] init];
            
            imageView.backgroundColor = [UIColor clearColor];
            imageView.url = [NSURL URLWithString:[((AMImage *)[mOfferDetail.imageList objectAtIndex:i]) convertSize310x310ImageURI]];
            [self.objMan manage:imageView];
            imageView.frame = CGRectMake(startX+(imageWidth+sepertor)*i, startY, imageWidth, imageHeight);

            imageView.userInteractionEnabled = YES;
                       
            [self.mScrollView addSubview:imageView];
            [imageView release];
        }
        
        
    }
 
}

- (void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView  
{  
    //int pageNum = (int)(self.mScrollView.contentSize.width /self.mScrollView.frame.size.width);
    int index = fabs(self.mScrollView.contentOffset.x)/self.view.frame.size.width;  
//    self.mTitleLabel.text = [NSString stringWithFormat:@"%d/%d", index+1, pageNum];
    
     [self changeIndatorState:index sum:mOfferDetail.imageList.count];
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


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end

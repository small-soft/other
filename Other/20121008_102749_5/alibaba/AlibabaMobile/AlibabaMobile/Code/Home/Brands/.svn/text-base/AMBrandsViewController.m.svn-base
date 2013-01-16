//
//  AMBrandsViewController.m
//  AlibabaMobile
//
//  Created by alimobile on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandsViewController.h"
#import "UIHelp.h"
#import "AMBlockBoxCell.h"
#import "AMBrandCell.h"
#import "LoginToken.h"
#import "ConstDef.h"
#import "AMBrandsCategoryResult.h"

#import "AMBrandsCategoryRequest.h"
#import "AMBrandCategory.h"

#import "AMBrandsResult.h"
#import "AMBrand.h"

#import "AMOfferListViewController.h"
#import "UserDataUtils.h"
#define DATD_KEYWORD_TITLE  (@"title")
#define DATD_KEYWORD_IMAGE  (@"image")
#define DATD_KEYWORD_FOCUSIMAGE  (@"focusImage")
#define DATD_KEYWORD_SELECTOR  (@"selector")


#define OCEAN_API_URL_BRANDS_CATEGORY ([@"/mro.queryAllCategories/" stringByAppendingString:AMCONST_APP_KEY])

#define OCEAN_API_URL_BRANDS ([@"/mro.queryBrandByCatId/" stringByAppendingString:AMCONST_APP_KEY])
#define HORIZANTAL_HEIGHT 45
#define VERTICAL_HEIGHT 371

@interface AMBrandsViewController ()

@end

@implementation AMBrandsViewController

@synthesize horizontalView;
@synthesize verticalView;


@synthesize blockBoxData;
@synthesize categoryData;

@synthesize isCateResponse;

@synthesize cateRequest;
@synthesize brandsRequest;
@synthesize currentCateId;
@synthesize currentCateName;

@synthesize originalY;
@synthesize defaultCate;


@synthesize horizontalViewHidden;


@synthesize objMan;

@synthesize isFirstLoad;
@synthesize lastMenuOffset;
@synthesize currentOffset;

//@synthesize mLoadingView=_mLoadingView;
@synthesize horizontalViewBackgroundImageView = _horizontalViewBackgroundImageView;
@synthesize arrowImageView = _arrowImageView;


-(void) dealloc
{
    [horizontalView release];
    [verticalView release];
    
    
    [blockBoxData release];
    [categoryData release];
    
    [cateRequest release];
    [brandsRequest release];
        
    [objMan release];
    
    [_horizontalViewBackgroundImageView release];
    [_arrowImageView release];
    [super dealloc];

}


-(void) hideCategory{
    
    if (self.horizontalViewHidden == NO) {
        [UIView beginAnimations:@"test" context:nil];
        [UIView setAnimationDuration:0.3];
        
        
        self.horizontalView.frame = CGRectMake(self.horizontalView.frame.origin.x, 0 - HORIZANTAL_HEIGHT, self.horizontalView.frame.size.width, self.horizontalView.frame.size.height );
        self.horizontalViewBackgroundImageView.frame = CGRectMake(self.horizontalViewBackgroundImageView.frame.origin.x, 0 - HORIZANTAL_HEIGHT, self.horizontalViewBackgroundImageView.frame.size.width, self.horizontalViewBackgroundImageView.frame.size.height);
        
        self.arrowImageView.frame = CGRectMake(self.arrowImageView.frame.origin.x, 14 - HORIZANTAL_HEIGHT, self.arrowImageView.frame.size.width, self.arrowImageView.frame.size.height);
        self.verticalView.frame = CGRectMake(self.verticalView.frame.origin.x, 0, self.verticalView.frame.size.width, VERTICAL_HEIGHT + HORIZANTAL_HEIGHT);
           
        [UIView commitAnimations];
        

    }
            
    NSLog(@"hide");
    
    self.horizontalViewHidden = YES;
}

-(void) showCategory{
    
    if ( self.horizontalViewHidden == YES)
    {
        [UIView beginAnimations:@"test" context:nil];
        [UIView setAnimationDuration:0.2];
        
        
        self.horizontalView.frame = CGRectMake(self.horizontalView.frame.origin.x, 0, self.horizontalView.frame.size.width, self.horizontalView.frame.size.height );
        
        self.horizontalViewBackgroundImageView.frame = CGRectMake(self.horizontalViewBackgroundImageView.frame.origin.x, 0, self.horizontalViewBackgroundImageView.frame.size.width, self.horizontalViewBackgroundImageView.frame.size.height);
        
        self.arrowImageView.frame = CGRectMake(self.arrowImageView.frame.origin.x, 14, self.arrowImageView.frame.size.width, self.arrowImageView.frame.size.height);
        
        self.verticalView.frame = CGRectMake(self.verticalView.frame.origin.x, HORIZANTAL_HEIGHT, self.verticalView.frame.size.width, self.verticalView.frame.size.height );
        

        
        
        [UIView commitAnimations];
        
        self.verticalView.frame = CGRectMake(self.verticalView.frame.origin.x, self.verticalView.frame.origin.y, self.verticalView.frame.size.width, VERTICAL_HEIGHT);
        

    }

    NSLog(@"show");
    
    self.horizontalViewHidden = NO;
}



-(NSString*)commonTableViewNavigationTitle {
    return @"品牌库";
}

-(NSString*)commonTableViewBackButtonTitle {
    return @"工业品";
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)objManInit
{
    objMan = [[HJObjManager alloc] initWithLoadingBufferSize:15 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/brands/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 300;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self objManInit];
    UIImage * backgroundImage = [UIImage imageNamed:@"scr_tab_bar_bg.png"];
    [self.horizontalViewBackgroundImageView setImage:[backgroundImage stretchableImageWithLeftCapWidth:backgroundImage.size.width/2 topCapHeight:backgroundImage.size.height/2]];
    
    
//    NSUserDefaults * userDefault = [NSUserDefaults standardUserDefaults];
//    NSString * stringCateId =     [userDefault objectForKey:@"defaultCategoryId"];
    NSString * stringCateId = [UserDataUtils getBrandsCateId];
    if (stringCateId == nil || [stringCateId isEqualToString:@""]) {
        //初始化当前类目Id为0，表示没有默认类目
        self.defaultCate = 0;
    }else
    {
        self.defaultCate = stringCateId.integerValue;
    }
    
    isFirstLoad = YES;
    
    self.currentOffset = 0;
    
   
    self.lastMenuOffset = [UserDataUtils getLastCateOffset];
    if ( self.lastMenuOffset < 0 )
    {
        self.lastMenuOffset = 0;
    }
    
//    self.horizontalView.frame = CGRectMake(0, 0, 320, 60);
    self.horizontalView.showsHorizontalScrollIndicator = NO;
//    self.horizontalView.backgroundColor = [UIHelp colorWithHexString:@"0x666666"];
     
    self.verticalView.scrollEnabled = YES;
    self.verticalView.showsVerticalScrollIndicator = YES;
    
    
    
    //先加载类目信息,加载成功后绘制水平View
    [self loadCategoryRequest];
    
}


//类目信息请求
-(void)loadCategoryRequest {
    
//    [self showLoadingView];
    [self.mLoadingView showLoadingView];
    
    //第一步，实例化Request对象
    if (nil == self.cateRequest) {
        self.cateRequest = [[AMBrandsCategoryRequest alloc] init]; 
    }
    
    //第二步，初始化objectManager对象，设置baseUril，设置结果映射，设置代理，并发出请求
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* resultMapping = [AMBrandsCategoryResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    self.isCateResponse = YES;
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_BRANDS_CATEGORY usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMBrandsCategoryResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.cateRequest;
    }];
    
            
}


//品牌列表请求
- (void)loadBrandRequest:(NSInteger)cateId
{
    
//    [self showLoadingView];
    [self.mLoadingView showLoadingView];
    
    
    //第一步，实例化Request对象
    if (nil == self.brandsRequest) {
        self.brandsRequest = [[AMBrandsRequest alloc] init]; 
    }
    
    self.brandsRequest.catId = cateId;
        
    //第二步，初始化objectManager对象，设置baseUril，设置结果映射，设置代理，并发出请求
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* resultMapping = [AMBrandsResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    self.isCateResponse = NO;
    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_BRANDS usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMBrandsResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.brandsRequest;
    }];
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects 
{  
    NSLog(@"Response received.............");
    if ( self.isCateResponse )
    {
        AMBrandsCategoryResult * result = [[AMBrandsCategoryResult alloc]init];
        result = (AMBrandsCategoryResult *) [objects objectAtIndex:0];
        
        int i = 0 ;
        for ( i = 0 ; i < [result.cates count] ; i ++ )
        {
            AMBrandCategory * cate =   (AMBrandCategory *) [result.cates objectAtIndex:i] ;
            NSLog(@"cateId:%@",cate.cateId);
            NSLog(@"cateName:%@",cate.cateName);
            
        }
        
        self.categoryData = result.cates;
        
        if ( defaultCate == 0 )
        {
            defaultCate = 1;
        }
        currentCateId = defaultCate;
        
        [self drawHorizontalView:self.categoryData withCateId:self.defaultCate];
    }else {
        NSLog(@"here is brand list info");
        self.isFirstLoad = NO;
        
        AMBrandsResult * result = [[AMBrandsResult alloc]init];
        result = (AMBrandsResult *) [objects objectAtIndex:0];
        
        NSLog(@"list count:%d", [result.resultList count]);
        
        int i = 0 ;
        
        for ( i = 0 ; i < [result.resultList count] ; i ++ )
        {
            AMBrand * brand =   (AMBrand *) [result.resultList objectAtIndex:i] ;
            NSLog(@"brandId:%@",brand.brandId);
            NSLog(@"brandName:%@",brand.brandName);
            NSLog(@"logo:%@",brand.logo);
            
        }
        
        self.blockBoxData = result.resultList;
        [self drawVerticalView:result ];
        
        [self.mLoadingView endLoadingView];

    }
    
//    [self endLoadingView];
    
}

- (void) drawHorizontalView:(NSMutableArray*)result withCateId:(NSInteger)cateId;
{
    for (UIView * subview in self.horizontalView.subviews) {
        [subview removeFromSuperview];
    }
    int i = 0 , tempX = 5;
    for ( i = 0 ; i < [result count] ; i ++ )
    {
        
        
        AMBrandCategory * cate =   (AMBrandCategory *) [result objectAtIndex:i] ;
        
        UIButton* button = [[UIButton alloc]init];
//        button.frame = CGRectMake (tempX, 5, 150, 30);
        [button setTitle:cate.cateName forState:UIControlStateNormal];
        button.titleLabel.font = [UIFont fontWithName:@"Heiti SC" size:14];
//        button.backgroundColor = [UIHelp colorWithHexString:@"0x666666"];
        button.backgroundColor = [UIColor clearColor];
        button.titleLabel.shadowColor = [UIHelp colorWithHexString:@"0x181818"];
        button.titleLabel.shadowOffset = CGSizeMake(1.0, 1.0);
        [button setTitleColor:[UIHelp colorWithHexString:@"0x999999"] forState:UIControlStateNormal];

        //[button setImage:[UIImage imageNamed:@"icon_toolbar_home"] forState:UIControlStateNormal];
        button.tag = cate.cateId.integerValue;
        
        
        button.frame = CGRectMake(tempX, 5,  [cate.cateName sizeWithFont:button.titleLabel.font constrainedToSize:CGSizeMake(MAXFLOAT, 40)].width+16 ,30);
        tempX += button.frame.size.width;
        
        
        if ( cate.cateId.integerValue == cateId  ) {
            UIImage * backgroundImage = [UIImage imageNamed:@"scr_tab_bar_press.png"];
            [button setBackgroundImage:[backgroundImage stretchableImageWithLeftCapWidth:backgroundImage.size.width/2 topCapHeight:backgroundImage.size.height/2] forState:UIControlStateNormal];
            [button setTitleColor:[UIHelp colorWithHexString:@"0xffffff"] forState:UIControlStateNormal];
        }
        
        [button addTarget:self action:@selector(switchCategory:) forControlEvents:UIControlEventTouchUpInside];
        [self.horizontalView addSubview:button];
        [button release];
    }
    
    self.horizontalView.contentSize = CGSizeMake(tempX, self.horizontalView.contentSize.height);
    
    if (self.lastMenuOffset > 0 && isFirstLoad ){
        CGPoint  point  = CGPointMake(self.lastMenuOffset, 0.0);
        [self.horizontalView setContentOffset:point animated:NO];
    }
    
    [self loadBrandRequest:self.currentCateId];
    
    
}


- (void)switchCategory:(id)sender
{
    UIButton * button = (UIButton*) sender;
    NSLog(@"button tag :%d", button.tag);
    
    [AMLogUtils appendLog:INDUSTRIAL_BRANDS_PAGE_ONE];
    
    self.currentCateId =   button.tag; 
    self.currentCateName = button.titleLabel.text;
    
//    [self drawHorizontalView:self.categoryData  withCateId:button.tag];
    for (UIView * subview in self.horizontalView.subviews) {
        if ([subview isKindOfClass:[UIButton class]]) {
            if (subview.tag == button.tag) {
                UIImage * backgroundImage = [UIImage imageNamed:@"scr_tab_bar_press.png"];
                [button setBackgroundImage:[backgroundImage stretchableImageWithLeftCapWidth:backgroundImage.size.width/2 topCapHeight:backgroundImage.size.height/2] forState:UIControlStateNormal];
                [button setTitleColor:[UIHelp colorWithHexString:@"0xffffff"] forState:UIControlStateNormal];
            }else {
                [(UIButton*)subview setBackgroundImage:nil forState:UIControlStateNormal];
                [(UIButton*)subview setTitleColor:[UIHelp colorWithHexString:@"0x999999"] forState:UIControlStateNormal];
            }
            
        }
    }
    
    [self loadBrandRequest:button.tag];
    [self.verticalView setContentOffset:CGPointMake(0, 0)];
}
    



- (void) drawVerticalView:(AMBrandsResult*)result
{
    [self.verticalView reloadData];
//    self.verticalView.contentSize = CGSizeMake(self.verticalView.contentSize.width, self.verticalView.contentSize.height + 20);
}

- (void)viewDidUnload
{
    self.objMan = nil;
    self.horizontalView = nil;
    self.verticalView = nil;
    self.blockBoxData = nil;
    self.categoryData = nil;
    self.cateRequest = nil;
    self.brandsRequest = nil;
    self.horizontalViewBackgroundImageView = nil;
    self.arrowImageView = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
    
//    [self endLoadingView];
    [self.mLoadingView endLoadingView];
    
    NSLog(@"loading errorcode %d", [error code]);
    
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
//        [self.mLoadingView showLoadingView];
        
        
    }
    
}

-(void)viewWillDisappear:(BOOL)animated
{
    NSString * stringCateId = [NSString stringWithFormat:@"%d", self.currentCateId];
//    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
//    [userDefault setValue:stringCateId  forKey:@"defaultCategoryId"];
//    [userDefault setInteger:self.horizontalView.contentOffset.x forKey:@"lastCateOffset"];
//    [userDefault synchronize];
    [UserDataUtils setBrandsCateId:stringCateId];
//    for (UIView * subView in self.horizontalView.subviews) {
//        if ([subView isKindOfClass:[UIButton class]] ) {
//            if(subView.tag==stringCateId.integerValue){
//                if (subView.frame.origin.x + subView.frame.size.width>self.horizontalView.contentSize.width){
//                    [UserDataUtils setLastCateOffset:self.horizontalView.contentOffset.x];                
//                }else {
//                    [UserDataUtils setLastCateOffset:subView.frame.origin.x - subView.frame.size.width/2];
//                }
//
//                break;
//            }
//        }
//    }
    
    [UserDataUtils setLastCateOffset:self.horizontalView.contentOffset.x];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 62;
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    
    
//    if (section == 0) {
//        return 0;
//    }else {
        int num= [self.blockBoxData count]/[AMBrandCell cellBoxViewArrayCount];
        
        if ([self.blockBoxData count]%[AMBrandCell cellBoxViewArrayCount]) {
            num++;
        }
        return num;
//    }

}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AMBrandCell *cell = (AMBrandCell *)[tableView dequeueReusableCellWithIdentifier: [AMBrandCell cellIdentifer]];
    
    if (cell == nil)  
    {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMBrandCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMBrandCell class]])
                cell = (AMBrandCell *)oneObject;
    }
    NSUInteger index = [indexPath row] *[AMBrandCell cellBoxViewArrayCount];
    
    for (AMBrandView *box in cell.cellBoxViewArray) {
        if (index>=[self.blockBoxData count]) {
            box.hidden = true;
            continue;
        }
        
        AMBrand *data = [self.blockBoxData objectAtIndex:index]; 
        index ++;
        
//        box.boxIcon.image = [UIImage imageNamed:[data objectForKey:DATD_KEYWORD_IMAGE]];
        box.tag = data.brandId.integerValue;
        box.icon.url = [NSURL URLWithString:data.logo];
        box.keywords = data.keyword;
        
       
        [self.objMan manage:box.icon];


        
        box.boxTitle.text = data.brandName;
        [box addTarget:self action:@selector(boxUpAction:)  forControlEvents:UIControlEventTouchUpInside];    
        [box addTarget:self action:@selector(boxDownAction:) forControlEvents:UIControlEventTouchDown];   
        [box addTarget:self action:@selector(boxUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside]; 
    }
    
    cell.selectionStyle =  UITableViewCellSelectionStyleNone;
    cell.backgroundColor = [UIColor clearColor];

    cell.backgroundColor = [UIHelp colorWithHexString:@"0x000000"];
    
    
//    UIView *bg = [[UIView alloc]init];
//    bg.backgroundColor = RGB(0xe1, 0xe1, 0xe1);
//    cell.selectedBackgroundView = bg;

    return cell;
}



-(void)boxDownAction:(AMBrandView*)sender
{
    UIImage *image = [UIImage imageNamed:@"App_icon_press"];
    sender.boxFocusIcon.image = [image stretchableImageWithLeftCapWidth:image.size.width/2 topCapHeight:image.size.height/2]; 
}
-(void)boxUpAction:(AMBrandView*)sender
{
//    NSDictionary *data = [self.blockBoxData objectAtIndex:sender.tag]; 
//    [self performSelector:NSSelectorFromString([data objectForKey:DATD_KEYWORD_SELECTOR])];
    
    NSInteger brandId = sender.tag;
    
    //以brandId为参数，进入下一个viewController
    NSLog(@"BrandId:%d ; BrandName:%@ ; Keywords:%@", brandId, sender.boxTitle.text, sender.keywords);
    
    [AMLogUtils appendLog:INDUSTRIAL_BRANDS_PAGE_TWO];

    
    AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
    controller.keyWords = sender.keywords;
    controller.catId = sender.catId;
    controller.parentCatId = sender.catId;
    controller.parentTitle = self.navigationItem.title;
    //    controller.categoryFilterSelectedItem = index;增减    
//    controller.keyWords = sender.boxTitle.text;
    controller.hidesBottomBarWhenPushed=YES;
    
    
    [self.navigationController pushViewController:controller animated:YES];
    [controller release];
    
    sender.boxFocusIcon.image = nil; 
}

-(void)boxUpOutsideAction:(AMBrandView*)sender
{
    sender.boxFocusIcon.image = nil; 
}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    if (scroll == self.verticalView) {
        CGFloat tempY = self.verticalView.contentOffset.y;
        
        @synchronized (self) {
            if ( tempY - self.currentOffset > 0 ) {
                if (self.horizontalViewHidden == NO && tempY - self.currentOffset > 2 && tempY > 0) {
                    [self hideCategory];
                }
                
            }else {
                if (self.horizontalViewHidden == YES && tempY - self.currentOffset < -2 && ((tempY + self.verticalView.frame.size.height <= self.verticalView.contentSize.height && self.verticalView.frame.size.height < self.verticalView.contentSize.height )|| (self.verticalView.frame.size.height > self.verticalView.contentSize.height && tempY < 0) )) {
                    [self showCategory];
                    
                }
                
                
            }
            
        }
        
        NSLog(@"offsetY:%f",tempY);
        NSLog(@"frame height:%f", self.verticalView.frame.size.height);
        NSLog(@"content height:%f",self.verticalView.contentSize.height);
        
      
        
        self.currentOffset = tempY ;
    }else if(scroll == self.horizontalView){
        if (scroll.contentOffset.x > 0) {
            self.arrowImageView.hidden = YES;
        }else {
            self.arrowImageView.hidden = NO;
        }
    }
    
}






@end

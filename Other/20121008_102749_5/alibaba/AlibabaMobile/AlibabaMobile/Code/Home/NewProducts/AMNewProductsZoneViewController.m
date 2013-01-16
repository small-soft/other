//
//  AMNewProductsZoneViewController.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsZoneViewController.h"

@interface AMNewProductsZoneViewController ()

@end

@implementation AMNewProductsZoneViewController

@synthesize rightArrowImg;
@synthesize horizontalBg;

//对应两个scroll view
@synthesize horizontalView;
@synthesize contentView;

@synthesize isLoadCategory; //是否是第一次请求，请求品类数据


@synthesize cateRequest;
@synthesize categoryRequest;
@synthesize productRequest;

@synthesize originCategoryList;
@synthesize categoryList;

@synthesize sum;
@synthesize currentNum;
@synthesize currentRequestPage;

@synthesize productsList;
@synthesize objMan;

@synthesize currentCateId;

@synthesize isCateSwitch;

@synthesize isLoading;

@synthesize currentOffsetY;
@synthesize topHidden;

@synthesize isFirstLoad;


-(void) dealloc
{
     [rightArrowImg release] ;
     [horizontalBg release];
     [horizontalView release];
     [contentView release];
     [cateRequest release];
     [categoryRequest release];
     [productRequest release];
     [originCategoryList release];
     [categoryList release];
     [productsList release];
     [objMan release];

     
    
    [super dealloc];
}


- (void)viewDidUnload
{
    rightArrowImg = nil ;
    horizontalBg = nil;
    horizontalView = nil;
    contentView = nil;
    cateRequest = nil;
    categoryRequest = nil;
    productRequest = nil;
    originCategoryList = nil;
    categoryList = nil;
    productsList = nil;
    objMan = nil;

    
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setTitle:@"新品推荐"];
    [self setBackButtonText:@"首页"];
    
    self.isLoadCategory = YES;
    self.isLoading = NO;
    self.isFirstLoad = YES;
    self.categoryList =  [[NSMutableArray alloc] init] ;
    self.topHidden = NO;
    self.currentOffsetY = 0;
    self.horizontalView.showsHorizontalScrollIndicator = NO;
    self.isCateSwitch = YES;
    
    UIImage * backgroundImage = [UIImage imageNamed:@"scr_tab_bar_bg.png"];
    [self.horizontalBg setImage:[backgroundImage stretchableImageWithLeftCapWidth:backgroundImage.size.width/2 topCapHeight:backgroundImage.size.height/2]];
    
    [self objManInit];
    
    
    [self loadCateRequest];
    
    
}


-(void)objManInit
{
    self.objMan = [[HJObjManager alloc] initWithLoadingBufferSize:20 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/newProducts/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	self.objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (void) loadCateRequest
{
//    [self showLoadingView];
    [self.mLoadingView showLoadingView];
    isLoading = YES;
    
    //第一步，实例化Request对象
    if (nil == self.categoryRequest) {
        self.categoryRequest = [[AMNewProductsCategoryRequest alloc] init]; 
//        self.categoryRequest.names = @"new_product_dress";
    }
    
    //第二步，初始化objectManager对象，设置baseUril，设置结果映射，设置代理，并发出请求
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* contentMapping = [AMHotRankResult sharedObjectMapping];
    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWPRODUCTS_CATEGORY usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        loader.method = RKRequestMethodPOST;
        loader.params = self.categoryRequest;
    }];    
}

- (void) loadProductRequest:(NSString *)operationId withPage:(NSInteger)page 
{
//    [self showLoadingView];
    
    isLoading = YES;
    if(isFirstLoad)
    {
        [self.mLoadingView showLoadingView];
    }else {
        AMMoreLoadingView *  more = [[AMMoreLoadingView alloc]init];
        self.contentView.tableFooterView = more;
        [more release];
    }
    
    
    //第一步，实例化Request对象
    if (nil == self.productRequest) {
        self.productRequest = [[AMNewProductsListRequest alloc] init]; 
    }
    
    self.productRequest.operationId = operationId;
    self.productRequest.pageIndex = [NSNumber numberWithInt:page];
    self.productRequest.requestURL = OCEAN_API_URL_NEWPRODUCTS_LIST;

    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* mapping = [AMNewProductsListResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NEWPRODUCTS_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMNewProductsListResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.productRequest ;
    }];}





- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}




#pragma mark - restkit delegate methods begin


- (void)objectLoader:(RKObjectLoader *)objectLoader didFailWithError:(NSError *)error
{
    NSLog(@"Fail! Load objects error!");
    
    [self.mLoadingView endLoadingView];
    
    NSLog(@"loading error code %d", [error code]);
    
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        
        if (isFirstLoad) {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }else {
            AMErrorMessageView * errorView = [[AMErrorMessageView alloc]init];
            self.contentView.tableFooterView = errorView;
            [errorView release];
        }
         
        
    }
    
    self.isLoading = NO;
    
}



- (void)objectLoader:(RKObjectLoader *)objectLoader didLoadObjects:(NSArray *)objects
{
    if ( isLoadCategory == YES)
    {
        
        for (AMHotRankResult *category in objects) {
            if ([category.operationDesc rangeOfString:@"服装"].length>0||[category.operationDesc rangeOfString:@"服饰"].length>0) 
            {
                
                NSLog(@"%@",category.appPath.params.secondcate);
                [self.originCategoryList addObject:category];
                
                NSArray *titleAndCategory = [category.appPath.params.secondcate componentsSeparatedByString:@":"];
                
                NSLog(@"count:%d", titleAndCategory.count);
                
                int i  ;
                for (i = 0 ; i <  titleAndCategory.count ; i ++) {
                    [self.categoryList addObject: [titleAndCategory objectAtIndex:i]];
                }
            }
        }

        NSLog(@"cate count:%d", self.categoryList.count);
        int i ;
        for (i = 0; i < self.categoryList.count; i ++) {
            NSString * cate = [self.categoryList objectAtIndex:i];
            NSArray *components = [cate componentsSeparatedByString:@"-"];
            NSLog(@"cateName: %@, cateOperationId: %@", [components objectAtIndex:0], [components objectAtIndex:2]);
        }
        
        
        self.currentCateId = 0;
        [self drawHorizontalView];
        
        
        isLoadCategory = NO;
        
//        [self.mLoadingView endLoadingView];
    }else {
        
        if(objects != nil
           && objects.count > 0){
            AMNewProductsListResult * result = (AMNewProductsListResult*)[objects objectAtIndex:0];
            
            if(result != nil
               && result.resultList != nil
               && result.resultList.count >0){
                NSLog(@"total:%@, pageSize:%@, page:%d", result.totalCount.stringValue,result.pageSize.stringValue, currentRequestPage + 1);
                if(result.resultList != nil){
                    NSLog(@"list count:%d", result.resultList.count);
                }else{
                    NSLog(@"newslist null");
                }
                
                sum = result.totalCount.intValue;
                currentRequestPage ++;
                currentNum += result.resultList.count;
                
                [self performSelectorOnMainThread:@selector(drawVerticalView:) withObject:result waitUntilDone:YES];
            }
            
            
        }else{
            [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
        }
        
        if(isFirstLoad){
            [self.mLoadingView endLoadingView];
            isFirstLoad = NO;
        }else {
            self.contentView.tableFooterView = nil;
        }
        
    }
//    [self endLoadingView];
    
}


- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
   
    if (self.isLoadCategory) {
        NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
        
        // Convert body to real JSON NSString
        NSRange range = {0, [[response bodyAsString] length]};
        NSString *trimmedJson1 = [[[response bodyAsString] substringWithRange: range] stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
        NSString *trimmedJson2 = [trimmedJson1 stringByReplacingOccurrencesOfString:@" " withString:@""];
        NSString *trimmedJson = [trimmedJson2 stringByReplacingOccurrencesOfString:@"\\" withString:@""];
        
        //再截一次，先实现，后优化
        NSRange rangeFinal = {25, [trimmedJson length]-27};
        NSString *trimmedJsonFinal = [trimmedJson substringWithRange:rangeFinal];
        NSLog(@"Trimmed payload: %@", trimmedJsonFinal);
        
        [(NSMutableData*)[response body] setData: [trimmedJsonFinal dataUsingEncoding: NSUTF8StringEncoding]];

    }else {
        NSLog(@"Loaded payload(Test): %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
    }
    
    
}


#pragma mark - draw views


- (void) drawHorizontalView
{
    for (UIView * subview in self.horizontalView.subviews) {
        [subview removeFromSuperview];
    }

    int i = 0 , tempX = 5;
    for ( i = 0 ; i < [self.categoryList count] ; i ++ )
    {
        NSString * cate = [self.categoryList objectAtIndex:i];
        NSArray *components = [cate componentsSeparatedByString:@"-"];
        
        NSString * title = [components objectAtIndex:0];
        
        UIButton* button = [[UIButton alloc]init];
        //预绘制
        button.frame = CGRectMake (tempX, 5, 150, 30);
        [button setTitle: title forState:UIControlStateNormal];
        button.titleLabel.font = [UIFont systemFontOfSize:14.0];
        
        button.backgroundColor = [UIColor clearColor];
        
        [button setTitleColor:[UIHelp colorWithHexString:@"0x999999"] forState:UIControlStateNormal];
        
        
        button.tag = i;
        
        //重绘制
        button.frame = CGRectMake(tempX, 5,  [title sizeWithFont:button.titleLabel.font constrainedToSize:CGSizeMake(MAXFLOAT, 20)].width + 20,30);
        [self.horizontalView addSubview:button];
        
        tempX += button.frame.size.width - 2;       //10 + 10 - 18
        
        
        if ( i == self.currentCateId   ) {
            UIImage * backgroundImage = [UIImage imageNamed:@"scr_tab_bar_press.png"];
            [button setBackgroundImage:[backgroundImage stretchableImageWithLeftCapWidth:backgroundImage.size.width/2 topCapHeight:backgroundImage.size.height/2] forState:UIControlStateNormal];

            [button setTitleColor:[UIHelp colorWithHexString:@"0xffffff"] forState:UIControlStateNormal];
            
        }
        
        [button addTarget:self action:@selector(switchCategory:) forControlEvents:UIControlEventTouchUpInside];
        
        
    }
    
    self.horizontalView.contentSize = CGSizeMake(tempX, self.horizontalView.contentSize.height);
    
//    if (self.lastMenuOffset > 0 && isFirstLoad ){
//        CGPoint  point  = CGPointMake(self.lastMenuOffset, 0.0);
//        [self.horizontalView setContentOffset:point animated:NO];
//    }
//    
    
    
    NSString * cate = [self.categoryList objectAtIndex:self.currentCateId];
    NSArray *components = [cate componentsSeparatedByString:@"-"];
    [self loadProductRequest: [components objectAtIndex:2]  withPage:1];
}


- (void) drawVerticalView:(AMNewProductsListResult *)data 
{
    if(self.productsList == nil){
        self.productsList =  [[NSMutableArray alloc] initWithCapacity:data.totalCount.intValue];
    }    
    else if( isCateSwitch ) {
        [self.productsList removeAllObjects];
        
        [self.contentView setContentOffset:CGPointMake(0, 0)];

        
    }
    
    self.isCateSwitch = NO;
    
    [self.productsList addObjectsFromArray:data.resultList];
    
    
    [self.contentView reloadData];
    isLoading = NO;
}


- (void)switchCategory:(id)sender
{
    UIButton * button = (UIButton*) sender;
    NSLog(@"button tag :%d", button.tag);
    
    self.currentCateId = button.tag;
    self.isCateSwitch = YES;
    
    //切换类目，原类目的计数全部清零
    sum = 0;
    currentRequestPage = 0;
    currentNum = 0;
    isFirstLoad  = YES;
    
    [AMLogUtils appendLog:INDUSTRIA_NEWPRODUCTS_PAGE_ONE];
    
    
    
    [self drawHorizontalView];
    isLoading = NO;
}





- (void)redirectToOfferDetail:(AMTodayActivityBoxView*)sender
{
    
    [AMLogUtils appendLog:INDUSTRIA_NEWPRODUCTS_PAGE_TWO];
    
    AMNewProductsListItem *item = [self.productsList objectAtIndex:sender.tag]; 
    NSString *offerId = [NSString stringWithFormat:@"%@",item.offerId];
    AMOfferTabViewController * controller = [[AMOfferTabViewController alloc] initWithOfferId:offerId offerName:item.subject preViewName:nil];  
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES]; 
    [controller release];

    
}





#pragma mark - New Modifications After UED Resources Given

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{

    int num= [self.productsList count]/[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
    
    if ([self.productsList count]%[AMTodayActivityBlockBoxCell cellBoxViewArrayCount]) {
        num++;
    }
    return num;

}



- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    NSUInteger row = [indexPath row];
    
    AMTodayActivityBlockBoxCell *cell = (AMTodayActivityBlockBoxCell *)[tableView dequeueReusableCellWithIdentifier: [AMTodayActivityBlockBoxCell cellIdentifer]];
    if (cell == nil)  
    {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMTodayActivityBlockBoxCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMTodayActivityBlockBoxCell class]])
                cell = (AMTodayActivityBlockBoxCell *)oneObject;
    }
    NSUInteger index = row *[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
    
    for (AMTodayActivityBoxView *box in cell.cellBoxViewArray) {
        box.hidden = NO;
        if (index>=[self.productsList count]) {
            box.hidden = YES;//避免由于count为奇数造成的另外一个box view被复用显示的bug
            break;
        }
        box.tag = index;
        //            AMSpecialPriceOffer *offer = [self.contentData objectAtIndex:index++];
        
        //取每个产品项数据
        AMNewProductsListItem * product = [self.productsList objectAtIndex:index++];
        
        //设置产品标题      
        box.subject.text = [product.subject stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
        
        //设置标题下单价
        [self setLeaveFactoryAndUnitPropertyBox:[NSString stringWithFormat:@"%2g元",[product.rmbPrice.amount doubleValue]] unit:product.unit box:box];
        
        //获取产品图片
        NSString *listImg = [NSString stringWithFormat:@"%@",product.listImgUrl];
        NSString *bigImage = [listImg stringByReplacingOccurrencesOfString:@".100x100x80x1.jpg" withString:@".220x220x80x1.jpg"];
        
        [box.listImg clear];    //解决重用显示缓存
        box.listImg.url = [NSURL URLWithString:bigImage];
        box.listImg.frame = CGRectMake(4, 4, 147, 145);
        box.listImg.layer.masksToBounds = YES;
        box.listImg.layer.cornerRadius= 10.0;
        
        [self.objMan manage:box.listImg];
        
        
        [box addTarget:self action:@selector(redirectToOfferDetail:)  forControlEvents:UIControlEventTouchUpInside];    
    }
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    return cell;
   
}



- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{

    return [AMTodayActivityBlockBoxCell cellHeight];

}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
}





- (void) setLeaveFactoryAndUnitPropertyBox:(NSString *)countValue unit:(NSString *)unitValue box:(AMTodayActivityBoxView *) boxValue{
    
    unitValue = [NSString stringWithFormat:@"/%@", unitValue];
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    boxValue.leaveFactoryPrice.text = [NSString stringWithFormat:@"%@",countValue];
    
    CGSize labelSizeEnd = [unitValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    
    boxValue.unit.frame = CGRectMake(50+labelSize.width, 173, labelSizeEnd.width, labelSizeEnd.height);
    boxValue.unit.text =  unitValue;
}


#pragma mark - Scroll handlers

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    if (scroll == self.contentView) {
        
        CGFloat tempY = self.contentView.contentOffset.y;
        
        @synchronized (self) {
            if ( tempY - self.currentOffsetY > 0 ) {
                if (self.topHidden == NO && tempY - self.currentOffsetY > 2 && tempY > 0) {
                    [self hideCategory];
                }
                
            }else {
                if (self.topHidden == YES && tempY - self.currentOffsetY < -2 && ((tempY + self.contentView.frame.size.height <= self.contentView.contentSize.height && self.contentView.frame.size.height < self.contentView.contentSize.height )|| (self.contentView.frame.size.height > self.contentView.contentSize.height && tempY < 0) )) {
                    [self showCategory];
                }
                
                
            }
            
        }
        
        self.currentOffsetY = tempY ;
        
        
        
        // UITableView only moves in one direction, y axis
        NSInteger currentOffset = scroll.contentOffset.y;
        NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
        
               
        // Change 10.0 to adjust the distance from bottom
        if (maximumOffset - currentOffset <= 30.0 && [self.productsList count] != self.sum && !self.isLoading) {
            NSString * cate = [self.categoryList objectAtIndex:self.currentCateId];
            NSArray *components = [cate componentsSeparatedByString:@"-"];
            
            NSLog(@"\n\nLoading...\n\n");
            [self loadProductRequest: [components objectAtIndex:2]  withPage: currentRequestPage + 1];
        }
        
    }else if (scroll == self.horizontalView)
    {
        if (self.horizontalView.contentOffset.x > 0) {
            self.rightArrowImg.hidden = YES;
        }else {
            self.rightArrowImg.hidden = NO;
        }
    }
}



-(void) hideCategory{
    
    if (self.topHidden == NO) {
        
        [UIView beginAnimations:@"test" context:nil];
        [UIView setAnimationDuration:0.3];
        
        
        self.horizontalView.frame = CGRectMake(self.horizontalView.frame.origin.x, 0 - HORIZANTAL_HEIGHT, self.horizontalView.frame.size.width, self.horizontalView.frame.size.height );
        self.horizontalBg.frame = CGRectMake(self.horizontalBg.frame.origin.x, 0 - HORIZANTAL_HEIGHT, self.horizontalBg.frame.size.width, self.horizontalBg.frame.size.height);
        
        self.rightArrowImg.frame = CGRectMake(self.rightArrowImg.frame.origin.x, 15 - HORIZANTAL_HEIGHT, self.rightArrowImg.frame.size.width, self.rightArrowImg.frame.size.height);
        self.contentView.frame = CGRectMake(self.contentView.frame.origin.x, 0, self.contentView.frame.size.width, 480 -20 - 44  );
        
        [UIView commitAnimations];
        
        
    }
    
    self.topHidden = YES;
}

-(void) showCategory{
    
    if ( self.topHidden == YES)
    {
        [UIView beginAnimations:@"test" context:nil];
        [UIView setAnimationDuration:0.2];
        
        //     self.horizontalView.hidden = YES;
        
        
        self.horizontalView.frame = CGRectMake(self.horizontalView.frame.origin.x, 0, self.horizontalView.frame.size.width, self.horizontalView.frame.size.height );
        
        self.horizontalBg.frame = CGRectMake(self.horizontalBg.frame.origin.x, 0, self.horizontalBg.frame.size.width, self.horizontalBg.frame.size.height);
        
        self.rightArrowImg.frame = CGRectMake(self.rightArrowImg.frame.origin.x, 15, self.rightArrowImg.frame.size.width, self.rightArrowImg.frame.size.height);
        
        self.contentView.frame = CGRectMake(self.contentView.frame.origin.x, HORIZANTAL_HEIGHT, self.contentView.frame.size.width, self.contentView.frame.size.height );
        
        
        [UIView commitAnimations];
        
        self.contentView.frame = CGRectMake(self.contentView.frame.origin.x, self.contentView.frame.origin.y, self.contentView.frame.size.width, 480 -20 - 44 - HORIZANTAL_HEIGHT);
        
        
    }
    
    self.topHidden = NO;
}




@end

//
//  AMNewsDetailViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewsDetailViewController.h"
#import "AMNewsDetailRequest.h"
#import "AMNewsItem.h"
#import "ConstDef.h"
#import "AMNewsTitle.h"
#import "AMNewsTitleItem.h"

#import "NSAttributedString+HTML.h"

#import "AMToastView.h"
@interface AMNewsDetailViewController()

@property (retain,nonatomic) AMNewsDetailRequest*detailRequest;

- (void)loadObjectsFromRemote;
@end

@implementation AMNewsDetailViewController
@synthesize mainTitle=_mainTitle;
@synthesize subTitle=_subTitle;
@synthesize contentView=_contentView;
@synthesize categoryId=_categoryId;
@synthesize navigationTitle=_navigationTitle;
@synthesize parentTitle=_parentTitle;
@synthesize detailRequest=_detailRequest;
@synthesize hotNewsData=_hotNewsData;
@synthesize hotNewsIndex = _hotNewsIndex;
@synthesize line = _line;
@synthesize commonNewsData=_commonNewsData;
@synthesize commonNewsIndex=_commonNewsIndex;

-(AMNewsDetailRequest*)detailRequest
{
    if (_detailRequest==nil) {
        _detailRequest = [[AMNewsDetailRequest alloc] init];     
    }
    _detailRequest.cateId = self.categoryId;
    return _detailRequest;
}

-(NSMutableArray*)hotNewsData
{
    
    if (_hotNewsData==nil) {
        _hotNewsData = [[NSMutableArray alloc] init];
    }
    return _hotNewsData;
}

-(void)setHotNewsData:(NSMutableArray *)hotNewsData
{
    [self.hotNewsData addObjectsFromArray:hotNewsData];
}

-(NSMutableArray*)commonNewsData
{
    
    if (_commonNewsData==nil) {
        _commonNewsData = [[NSMutableArray alloc] init];
    }
    return _commonNewsData;
}

-(void)setCommonNewsData:(NSMutableArray *)commonNewsData
{
    [self.commonNewsData addObjectsFromArray:commonNewsData];
}

- (void)dealloc {
    [_mainTitle release];
    [_subTitle release];
    [_contentView release];
    [_categoryId release];
    [_navigationTitle release];
    [_parentTitle release];
    [_detailRequest release];
    [_hotNewsData release];
    [_commonNewsData release];

    [_line release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setMainTitle:nil];
    [self setSubTitle:nil];
    [self setContentView:nil];
    //_categoryId=nil;
    //_navigationTitle=nil;
    //_parentTitle=nil;
    [_detailRequest release];
    _detailRequest=nil;
    [_hotNewsData release];
    _hotNewsData = nil;
    [_commonNewsData release];
    _commonNewsData = nil;
    [self setLine:nil];
    [super viewDidUnload];
}
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
-(NSString*)commonTableViewOptionButtonTitle
{
    
    if ([self.hotNewsData count]>0) {
        if ([self.hotNewsData count]>self.hotNewsIndex+1) {
            return @"下一篇";
        }   
    }
    else if([self.commonNewsData count]>0){
        if ([self.commonNewsData count]>self.commonNewsIndex+1) {
            return @"下一篇";
        } 
    }
    
    return nil;
    
}
- (void) commonTableViewOptionButtonClick
{
    if ([self.hotNewsData count]>0) {
        
        if ([self.hotNewsData count]>self.hotNewsIndex+1) {
            [AMLogUtils appendLog: APP_NEWS_ONE]; 
            self.hotNewsIndex++;
            
            AMNewsTitle *news = (AMNewsTitle*)[self.hotNewsData objectAtIndex:self.hotNewsIndex] ;
            NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
            [f setNumberStyle:NSNumberFormatterDecimalStyle];
            
            self.categoryId=[f numberFromString:news.newsTitleItem.identifier];
            self.navigationTitle=news.newsTitleItem.title;    
            [f release];
            [self loadObjectsFromRemote];
            if ([self.hotNewsData count]==self.hotNewsIndex+1)
            {
                self.navigationItem.rightBarButtonItem=nil;
            }
        }   
    }
    else if([self.commonNewsData count]>0)
    {
        if ([self.commonNewsData count]>self.commonNewsIndex+1) {
            [AMLogUtils appendLog: APP_NEWS_ONE]; 
            self.commonNewsIndex++;
            
            AMNewsItem *cate = (AMNewsItem*)[self.commonNewsData objectAtIndex:self.commonNewsIndex] ;
            
            self.categoryId=cate.identifier;
            self.navigationTitle=cate.title;   
               
            [self loadObjectsFromRemote];
            if ([self.commonNewsData count]==self.commonNewsIndex+1)
            {
                self.navigationItem.rightBarButtonItem=nil;
            }
        }   

    }

}

-(void)viewDidLoad
{
    [self loadObjectsFromRemote];
    [super viewDidLoad];
}
-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"资讯详情";
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
    [super loadObjectsFromRemote];
}

#pragma mark RKObjectLoaderDelegate methods

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	

    AMNewsItem * item = (AMNewsItem*)[objects objectAtIndex:0];
    NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[item.title dataUsingEncoding:NSUTF8StringEncoding]documentAttributes:NULL];
    self.mainTitle.text = attributedText.plainTextString;
    //self.mainTitle.text = item.title;
    CGSize size = [item.title sizeWithFont:self.mainTitle.font];
    if (size.width>self.mainTitle.frame.size.width) {
        self.mainTitle.frame = CGRectMake(20.0, 13.0, 280.0, 42.0);
        self.mainTitle.numberOfLines=2;
    }
    else {
        self.mainTitle.frame = CGRectMake(20.0, 13.0, 280.0, 21.0);
        self.mainTitle.numberOfLines=1;
    }
    self.subTitle.frame = CGRectMake(20.0, self.mainTitle.frame.origin.y + self.mainTitle.frame.size.height, 280.0,21.0);
    CGFloat startY = self.subTitle.frame.origin.y + self.subTitle.frame.size.height;
    self.line.frame = CGRectMake(0.0, startY, 320 ,1);
    self.contentView.frame = CGRectMake(0.0, startY+1, 320 ,416 - startY-1);
    
    if (item.agencyName!=nil&&item.agencyName.length!=0) {
        self.subTitle.text = [NSString stringWithFormat:@"%@  来源：%@",item.publishDate,item.agencyName];
    }
    else
    {
        self.subTitle.text = item.publishDate;
    }
    
    [self.contentView loadHTMLString: [NSString stringWithFormat:@"<body style=\"background:#f5f5f5;font-size:16px;line-height:24px;padding:10px 5px 10px\">%@</body>", item.content ] baseURL:nil];
    [super objectLoader:objectLoader didLoadObjects: objects];
    //如果是最后一篇则提示 add by christ.yuj
    if (nil==[self commonTableViewOptionButtonTitle]) {
        [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAIL info:@"这是最后一篇了^_^"] show];

    }
}




@end

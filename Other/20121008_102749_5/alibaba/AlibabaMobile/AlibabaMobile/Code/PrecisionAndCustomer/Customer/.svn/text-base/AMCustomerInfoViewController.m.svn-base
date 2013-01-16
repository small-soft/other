//
//  AMCustomerInfoViewController.m
//  AlibabaMobile
//
//  Created lei.jul on 12-6-13.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferDetailViewController.h"
#import <QuartzCore/QuartzCore.h>
#import "AMOfferDetail.h"
#import "StringUtils.h"
#import "AMOfferRate.h"
#import "AMDataDictConstants.h"
#import "AMTradeInfo.h"
#import "OHAttributedLabel.h"
#import "UIHelp.h"
#import "AMOfferGalleryViewController.h"
#import "AliPriceRangeView.h"
#import "KeyValueObject.h"
#import "AliKeyValueMapView.h"
#import "AliImageControlFactory.h"
#import "AliImageButton.h"
#import "AliSatisfyRateView.h"
#import "AliSmallRemoteImageGallery.h"
#import "AMCreditBase.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

#import "AMCustomerInfoViewController.h"
#import "AMCustomerInfoRequest.h"
#import "AMCustomerInfoResult.h"
#import "AMContactView.h"
#import "AMEnqueryView.h"

#import "AMEnqueryItem.h"

#import "AliToastView.h"
#import "NoticationItem.h"

#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AMIMTalkViewController.h"
#import "LoginToken.h"

@implementation AMCustomerInfoViewController

@synthesize mContentScrollView;

@synthesize request = _request;
@synthesize objects = _objects;

@synthesize mButton;
@synthesize buyerId = _buyerId;

//@synthesize mLoadingView = _mLoadingView;

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [mContentScrollView release];
    
    [_buyerId release];
    [_request release];
    [_objects release];
    [mButton release];
    [super dealloc];
}

//-(UIView*)mLoadingView {
//    if (!_mLoadingView) {
//        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
//        for (id oneObject in nib) {
//            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
//                _mLoadingView = (AliLoadingDataView *)oneObject;            
//        }
//        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
//        _mLoadingView.noDataView.backgroundColor =[UIHelp colorWithHexString:@"0x0f0f0f"];
//        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
//        [self.view addSubview:_mLoadingView];
//        [_mLoadingView setHidden:NO];
//    }
//    
//    return _mLoadingView;
//}

- (void) showLoadingView {
    [self.mLoadingView setHidden:NO];
    [self.mButton setHidden:YES];
}
//去除加载进度
-(void) endLoadingView {
    [self.mLoadingView setHidden:YES];
    [self.mButton setHidden:NO];
}

- (id)initWithBuyerId:(NSString *)buyerId  
{
    self = [super init];
    if (self) {
        self.buyerId = buyerId;
    }
    return self;
}

-(NSString*)commonTableViewNavigationTitle
{
    return @"客户资料";
}

-(NSString*)commonTableViewBackButtonTitle
{
    return @"询盘管理";
}

- (NSString *) getNoNilString:(NSString *) str
{
    return str != nil? str:@"";
}
            
- (NSString *) getAddressString:(AMAddress *)address
{
    if(address != nil){
        NSString * provinceName = [self getNoNilString:[address provinceName]];
        NSString * areaName = [self getNoNilString:[address areaName]];
//        NSString * streetName = [self getNoNilString:[address streetAddress]];
        if([StringUtils getIndexOf:provinceName inFather:areaName] >=0){
//            return [areaName stringByAppendingString:streetName];
            return areaName;
        }else{
//            return [[provinceName stringByAppendingString:areaName] stringByAppendingString:streetName];
             return [provinceName stringByAppendingString:areaName];
        }
    }else{
        return nil;
    }
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [AMLogUtils appendLog:APP_PRD_DETAL_FOUR];
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self loadRequest];
    
    isTalkAfterWwLogin = NO;
}
-(void) viewDidUnload
{
//    _mLoadingView = nil;
    mContentScrollView = nil;
    self.request = nil;
    self.objects = nil;
    [super viewDidUnload];
}

-(void)loadRequest
{
//    isLoading = YES;
    self.request = [[AMCustomerInfoRequest alloc] init];
    self.request.buyerId = self.buyerId;
    
    [self loadObjectsFromRemote];
} 

- (void)loadObjectsFromRemote {

    [self showLoadingView];
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMCustomerInfoResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CUSTOMER_USERINFO usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCustomerInfoResult  class]];
            loader.objectMapping = [AMCustomerInfoResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
//    [super loadObjectsFromRemote];
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {  
    
    [self endLoadingView];
    
    id object = [objects objectAtIndex:0];
    if(object != nil){
        
        AMCustomerInfoResult * result = object;
        //        NSArray * array = offer.offerList;
//        NSArray * array = result.returnObject;
        
//        [self performSelectorOnMainThread:@selector(setData:) withObject:result waitUntilDone:YES];
        
        self.objects = result;
//        EnqueryItem *item =(EnqueryItem*) [result.enquriesList objectAtIndex:0];
//        
//        NSLog(@"%@", item.enquiriesSource);
        
        [self draw ];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
//    isLoading = NO;
//    [super objectLoader:objectLoader didLoadObjects:objects];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    
}

-(void)draw{
    //视觉稿顶部高度
    int tempY = 10;
    
    UIColor * bgColor = [UIHelp colorWithHexString:@"0xf5f5f5"];
    UIColor * viewColor = [UIHelp colorWithHexString:@"0xffffff"];
    self.mContentScrollView.backgroundColor = bgColor;
    
    //询盘人
    UILabel *subjectLabel =  [[self getSubjectLabel:self.objects.returnObject.buyerName] retain];
    subjectLabel.frame = CGRectMake(0, 0, 180, [self.objects.returnObject.buyerName sizeWithFont:subjectLabel.font constrainedToSize:CGSizeMake(290, MAXFLOAT)].height);
    
    subjectLabel.frame = CGRectMake(15, tempY, subjectLabel.frame.size.width, subjectLabel.frame.size.height);
    
    NSLog(@"the height of show name is %f" , subjectLabel.frame.size.height);
    
    [self.mContentScrollView addSubview:subjectLabel];
    
    //showName和jobTitle之间间距5
    tempY += (subjectLabel.frame.size.height );
    [subjectLabel release];
    
    
    
    //询盘人职务
    UILabel *jobTitle =  [[self getSubjectLabel:self.objects.returnObject.jobTitle] retain];
    
    jobTitle.font = [UIFont boldSystemFontOfSize:12.0f];
    jobTitle.textColor = [UIHelp colorWithHexString:@"0x666666"];
    jobTitle.frame = CGRectMake(0, 0, 290, [self.objects.returnObject.jobTitle sizeWithFont:jobTitle.font constrainedToSize:CGSizeMake(290, MAXFLOAT)].height);
    jobTitle.frame = CGRectMake(15, tempY, jobTitle.frame.size.width, jobTitle.frame.size.height);
    [self.mContentScrollView addSubview:jobTitle];
    
    tempY += (jobTitle.frame.size.height );
    [jobTitle release];
    
    NSLog(@"the tempY is %d", tempY);
    
    tempY = 55;
    
    UILabel * basicInfo = [[UILabel alloc]init];
    
    [[basicInfo layer] setCornerRadius:10.0];
    [basicInfo setClipsToBounds:YES];
    [[basicInfo layer] setBorderColor:[[UIColor lightGrayColor ] CGColor]];
    //    [[basicInfo layer] setBorderColor:[[UIColor clearColor] CGColor]];
    [[basicInfo layer] setBorderWidth:1.0];
    
    basicInfo.frame = CGRectMake(10, tempY , 300, 106);
    //    basicInfo.backgroundColor = [UIColor clearColor] ;
    basicInfo.backgroundColor = viewColor;
    
    int innerY = 10; 
   
    UILabel * label1 = [[UILabel alloc]init];
    label1.frame = CGRectMake(10, innerY , 70, 14);
    label1.text = @"分       组:" ;
    label1.textColor = [UIHelp colorWithHexString:@"0x666666"];
    label1.font = [UIFont  systemFontOfSize:14.0f];
    label1.backgroundColor = viewColor;
    [basicInfo addSubview:label1];
    
    NSLog(@"the height of label1 is %f", label1.frame.size.height);
    
    UILabel * contentLabel1 = [[UILabel alloc]init];
    contentLabel1.frame = CGRectMake(80, 10 , 210, 14);
    contentLabel1.text = @"";
    if (self.objects.returnObject.groupName != nil) {
        contentLabel1.text = [contentLabel1.text stringByAppendingString:self.objects.returnObject.groupName];
    }else {
        contentLabel1.text = [contentLabel1.text stringByAppendingString:@"无"];
    }
    contentLabel1.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel1.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel1.backgroundColor = viewColor;
    [basicInfo addSubview:contentLabel1];
    
    innerY += label1.frame.size.height + 10;
    [label1 release];
    [contentLabel1 release];
    
    UILabel * label2 = [[UILabel alloc]init];
    label2.frame = CGRectMake(10, innerY , 70, 14);
    label2.text = @"公司名称:";
    label2.textColor = [UIHelp colorWithHexString:@"0x666666"];
    label2.font = [UIFont  systemFontOfSize:14.0f];
    label2.backgroundColor = viewColor;
    [basicInfo addSubview:label2];
    
    UILabel * contentLabel2 = [[UILabel alloc]init];
    contentLabel2.frame = CGRectMake(80, innerY , 210, 14);
    contentLabel2.text = @"";
    if (self.objects.returnObject.corpName != nil) {
        contentLabel2.text = [contentLabel2.text stringByAppendingString:self.objects.returnObject.corpName];
    }else {
        contentLabel2.text = [contentLabel2.text stringByAppendingString:@"无"];
    }
    
    contentLabel2.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel2.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel2.backgroundColor = viewColor;
    [basicInfo addSubview:contentLabel2];
    
    innerY += label2.frame.size.height + 10;
    [label2 release];
    [contentLabel2 release];
    
    UILabel * label3 = [[UILabel alloc]init];
    label3.frame = CGRectMake(10, innerY , 70, 14);
    label3.text = @"地       区:";
    label3.textColor = [UIHelp colorWithHexString:@"0x666666"];
    label3.font = [UIFont  systemFontOfSize:14.0f];
    label3.backgroundColor = viewColor;
    [basicInfo addSubview:label3];
    
    UILabel * contentLabel3 = [[UILabel alloc]init];
    contentLabel3.frame = CGRectMake(80, innerY, 210, 14);
    contentLabel3.text = @"";
    if (self.objects.returnObject.country != nil) {
        contentLabel3.text = [contentLabel3.text stringByAppendingString:self.objects.returnObject.country];
    }else {
        contentLabel3.text = [contentLabel3.text stringByAppendingString:@"无"];
    }
    
    contentLabel3.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel3.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel3.backgroundColor = viewColor;
    [basicInfo addSubview:contentLabel3];
    
    innerY += label3.frame.size.height + 10;
    [label3 release];
    [contentLabel3 release];
    
    UILabel * label4 = [[UILabel alloc]init];
    label4.frame = CGRectMake(10, innerY , 70, 14);;
    label4.text = @"主       营:";
    label4.textColor = [UIHelp colorWithHexString:@"0x666666"];
    
    label4.font = [UIFont  systemFontOfSize:14.0f];
    label4.backgroundColor = viewColor;
    [basicInfo addSubview:label4];
    
    
    UILabel * contentLabel4 = [[UILabel alloc]init];
    contentLabel4.frame = CGRectMake(80, innerY, 210, 14);
    contentLabel4.text = @"";
    contentLabel4.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel4.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel4.backgroundColor = viewColor;
    contentLabel4.lineBreakMode = UILineBreakModeWordWrap;
    contentLabel4.numberOfLines = 0;
    if ( self.objects.returnObject.saleKeywords != nil )
    {
        NSString * areas = self.objects.returnObject.saleKeywords;
        contentLabel4.text = [contentLabel4.text stringByAppendingString:areas];
    }else {
        contentLabel4.text = [contentLabel4.text stringByAppendingString:@"无"];
    }    
    
    CGSize size = [contentLabel4.text sizeWithFont:contentLabel4.font constrainedToSize:CGSizeMake(210, MAXFLOAT)];
    contentLabel4.frame = CGRectMake(80, innerY, 210, size.height);
    [basicInfo addSubview:contentLabel4];
    
    innerY += size.height + 10;
    [label4 release];
    [contentLabel4 release];
    
    basicInfo.frame = CGRectMake(10, tempY , 300, innerY);
    
    [self.mContentScrollView addSubview:basicInfo];
    
    tempY += basicInfo.frame.size.height  ;
    [basicInfo release];
    
    //基本联系方式table
    NSMutableArray * keyValueArray = [[NSMutableArray alloc] init ];
    
    if(self.objects != nil){
        
        AMContactView * contactView = [[AMContactView alloc] init];
        [contactView setNavigationController:self.navigationController];
        
        [contactView setContactInfo:self.objects.returnObject ];
        [contactView reloadData];
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = ITEM_STYLE_CUSTOME;
        obj.key = @"";
        obj.value = contactView;
        
        [keyValueArray addObject:obj];
        [obj release];
        
        [contactView release];
    }
    
    AliKeyValueMapView * mappingView = [[AliKeyValueMapView alloc] init];
    mappingView.paddingTop = 0;
    [mappingView setContentArray:keyValueArray maxKeyLabelString:@"五个汉子宽"];
    mappingView.frame = CGRectMake(0, tempY, 320, mappingView.frame.size.height);
    
    [self.mContentScrollView addSubview:mappingView];
    tempY += mappingView.frame.size.height;
    [mappingView release];
    [keyValueArray release];
    
    tempY -=30;
    
    //询盘内容table
    AMEnqueryView * enqueryView = [[AMEnqueryView alloc] init];
    [enqueryView setNavigationController:self.navigationController];
    enqueryView.enqueryCount = self.objects.enquiryTotalTimes;
    [enqueryView.enqueryArray addObjectsFromArray:self.objects.enquriesList];
    
    NSLog(@"array count : %d",self.objects.enquriesList.count);
    NSLog(@"array count : %d",enqueryView.enqueryArray.count);
    
    [enqueryView reloadData];
    
//    enqueryView.frame = CGRectMake(0, tempY , 320, self.objects.enquiryTotalTimes.intValue * 80 + 60);
    enqueryView.frame = CGRectMake(0, tempY , 320, self.objects.enquriesList.count * 80 + 60);//不能用enquiryTotalTimes，因为询盘次数可能超过10条，但是服务器提供记录最多10条
    enqueryView.enqueryCount = self.objects.enquiryTotalTimes;

    tempY += enqueryView.frame.size.height;
    
    [self.mContentScrollView addSubview:enqueryView];
    [enqueryView release];
    
    self.mContentScrollView.contentSize = CGSizeMake(320, tempY );
    
    [self setupTalkBtnImage];
}

-(void)setupTalkBtnImage
{
    [self.mButton setImage:[UIImage imageNamed:@"icon_ww.png"] forState:UIControlStateNormal];
    [self.mButton setImageEdgeInsets:UIEdgeInsetsMake(0, -10, 0, 0)];
}

- (IBAction)actionGotoTalk:(id)sender {
    [AMLogUtils appendLog:CUSTOMERMANAGER_CUSTOMERINFO_ONE];
    
    if (_objects == nil || _objects.returnObject == nil || _objects.returnObject.memberId == nil) 
    {
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:NSLocalizedString(@"TALK_ERROR_NOT_REG_MEMBER", @"")] show];
    } 
    else 
    {
        if([LoginToken isWangWangLogined]) 
        {
            [self enterTalk];
        }
        else 
        {
            isTalkAfterWwLogin = YES;
            [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
        }
    }
}

-(void)onWwLoginSucc {
    if (isTalkAfterWwLogin) 
    {
        [self enterTalk];
        isTalkAfterWwLogin = false;
    }
}

-(void) enterTalk {
    if (_objects == nil || _objects.returnObject == nil || _objects.returnObject.memberId == nil) {
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:NSLocalizedString(@"TALK_ERROR_NOT_REG_MEMBER", @"")] show];
    } else {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:_objects.returnObject.memberId : _objects.returnObject.buyerName];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.navigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

-(UILabel *) getSubjectLabel:(NSString *)subject
{
    UILabel * subjectLabel = [[[UILabel alloc] init]autorelease];
    subjectLabel.backgroundColor = [UIColor clearColor];
    subjectLabel.textColor = [UIHelp colorWithHexString:@"0x000000"];
    subjectLabel.textAlignment = UITextAlignmentLeft;
    subjectLabel.font = [UIFont boldSystemFontOfSize:16.0f];
//    subjectLabel.lineBreakMode = UILineBreakModeWordWrap;
    subjectLabel.numberOfLines = 0;
    subjectLabel.text = subject;
    
    subjectLabel.frame = CGRectMake(0, 0, 180, [UIHelp getLabelSizeWithFont:subjectLabel.font labelString:subjectLabel.text labelWidth:290].height);
    
    return subjectLabel;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end

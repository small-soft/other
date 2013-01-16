//
//  AMPrecisionDetailViewController.m
//  AlibabaMobile
//
//  Created lei.jul on 12-6-29.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "StringUtils.h"
#import "UIHelp.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

#import "AMPrecisionDetailViewController.h"
#import "AMCustomerInfoRequest.h"
#import "AMCustomerInfoResult.h"
#import "AMContactView.h"
#import "AMEnqueryView.h"

#import "AMEnqueryItem.h"
#import "AMAddress.h"

#import "LoginToken.h"
#import "AMPrecisionVisitorAccessLog.h"
#import "AMPrecisionVisitorAccessLogDetail.h"
#import "UserDataUtils.h"
#import "NoticationItem.h"
#import "AMPrecisionSaveFreeUserResResult.h"
#import "AMPrecisionTalkPermissionResult.h"
#import "AMPrecisionContactView.h"

#import "AMAccessLogView.h"
#import "AMAccessLogFullView.h"

#import "UIHelp.h"
#import "AMIMTalkViewController.h"

#define DEFAULT_LENGTH_PERROW 20

@implementation AMPrecisionDetailViewController

@synthesize mContentScrollView;

@synthesize request = _request;
@synthesize objects = _objects;
@synthesize mButton;

@synthesize detailRequest = _detailRequest;
@synthesize detailObjects = _detailObjects;

@synthesize saveFreeUserResRequest = _saveFreeUserResRequest;
@synthesize talkPermissionRequest = _talkPermissionRequest;
@synthesize sellerMemberId = _sellerMemberId;
@synthesize siteId = _siteId;
@synthesize visitorId = _visitorId;
@synthesize wwId = _wwId;
@synthesize hasTalkPermision = _hasTalkPermision;

@synthesize precisionView;
@synthesize precisionFullView;
@synthesize partHeight=_partHeight;

//@synthesize mLoadingView = _mLoadingView;

-(void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [mContentScrollView release];
    
    [_request release];
    [_objects release];

    [mButton release];
    
    [_detailRequest release];
    [_detailObjects release];
    [_sellerMemberId release];
    [_saveFreeUserResRequest release];
    [_talkPermissionRequest request];
    [_siteId release];
    [_visitorId release];
    [_wwId release];
    [mCurVisitorId release];
    
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

- (id)initWithVisitorId:(NSString *)visitorId {
    self = [super init];
    return self;
}

-(NSString*)commonTableViewNavigationTitle {
    return NSLocalizedString(@"PMVisitorDetail", @"");
}

-(NSString*)commonTableViewBackButtonTitle {
    return NSLocalizedString(@"Precision", @"");
}

- (NSString *) getNoNilString:(NSString *) str {
    return str != nil? str:@"";
}
            
- (NSString *) getAddressString:(AMAddress *)address {
    if(address != nil){
        NSString * provinceName = [self getNoNilString:[address provinceName]];
        NSString * areaName = [self getNoNilString:[address areaName]];
        
        if([StringUtils getIndexOf:provinceName inFather:areaName] >=0){
            return areaName;
        }else{
             return [provinceName stringByAppendingString:areaName];
        }
    }else{
        return nil;
    }
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    mSaveFreeUserResWhenLogined = NO;
    isTalkAfterWwLogin = NO;
    
    [self loadGetUserInfoRequest];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(showFullList) name:NOTIFICATION_PRECISION_VIEW_SHOW object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(hideFullList) name:NOTIFICATION_PRECISION_VIEW_HIDE object:nil];
}

- (void)viewDidUnload {
//    _mLoadingView = nil;
    self.detailRequest = nil;
    self.detailObjects = nil;
    self.saveFreeUserResRequest = nil;
    self.talkPermissionRequest = nil;
    self.mContentScrollView = nil;
    self.precisionView = nil;
    self.precisionFullView = nil;

    [super viewDidUnload];
}


-(void)loadGetUserInfoRequest {
//    [LoginToken checkAccessTokenExpired];
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if ([loginUserName length] > 3) {
        if (nil == self.detailRequest) {
            self.detailRequest = [[AMPrecisionVisitorDetailRequest alloc] init]; 
        }
        self.detailRequest.requestURL = OCEAN_API_URL_PRECISION_VISITOR_DETAIL;  
        self.detailRequest.sellerMemberId = _sellerMemberId;
        self.detailRequest.visitorId = _visitorId;
        self.detailRequest.siteId = _siteId;
        self.detailRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_VISITOR_DETAIL;
        [self loadObjectsFromRemote];
    }
}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    [self showLoadingView];;
    
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* resultMapping = [AMPrecisionVisitorDetailResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_VISITOR_DETAIL usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionVisitorDetailResult class]];
            loader.objectMapping = [AMPrecisionVisitorDetailResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.detailRequest;
    }];
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {  
    
    [self endLoadingView];
    
    if (objects == nil || !([objectLoader.params respondsToSelector:@selector(transactionType)])) {
      //  return ;
    }
    
    NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
    if (transactionType == AMTRANSACTION_TYPE_PRECISION_VISITOR_DETAIL) {
        
        AMPrecisionVisitorDetailResult * result = (AMPrecisionVisitorDetailResult *)[objects objectAtIndex:0];
        if (result == nil) {
            [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
            return ;
        }
        
        //NSLog(@"%@", result);
        NSLog(@"Visitor Detail: showName = %@", result.showName);
        //[UIHelp showAlertDialogWithTitle:result.showName andMsg:result.position];
        NSLog(@"position = %@", result.position);
        NSLog(@"mainBiz = %@", result.mainBiz);
        NSLog(@"mainProduct = %@", result.mainProduct);
        NSLog(@"mobilephone = %@", result.mobilephone);
        NSLog(@"corpName = %@", result.corpName);
        NSLog(@"fixedPhone = %@", result.fixedPhone);
        if (result.handShake != nil) {
            NSLog(@"handShake = %d", [result.handShake boolValue]);
        }

        NSLog(@"email = %@", result.email);

        int cnt = result.accessLog.count;
        NSLog(@"Access log count = %d", cnt);
        for(int i = 0; i < cnt; i++) {
            AMPrecisionVisitorAccessLog *log = (AMPrecisionVisitorAccessLog*)[result.accessLog objectAtIndex:i];
            NSLog(@"log.time = %@", log.time);
            int detailCnt = log.logList.count;
            NSLog(@"log.detailCnt = %d", detailCnt);
 
            for (int j = 0; j < detailCnt; j++) {
                AMPrecisionVisitorAccessLogDetail *detail = (AMPrecisionVisitorAccessLogDetail*)[log.logList objectAtIndex:j];
                //[UIHelp showAlertDialogWithTitle:@"t" andMsg:detail.stayTime];
                NSLog(@"detail.title = %@", detail.title);
                NSLog(@"detail.browseCount = %d", [detail.browseCount intValue]);
                NSLog(@"detail.stayTime = %@", detail.stayTime);
                NSLog(@"detail.openTime = %@", detail.openTime);
                NSLog(@"detail.isPageClose = %@", detail.isPageClose);
                NSLog(@"detail.url = %@", detail.url);
                NSLog(@"detail.stayMilliSeconds = %ld", [detail.stayMilliSeconds longValue]);
            }
        }
        
        if (result.buyDemandAreaPreferences != nil) {
            cnt = result.buyDemandAreaPreferences.count;
            for (int i = 0; i < cnt; i++) {
                NSString * buy1 = (NSString *)[result.buyDemandAreaPreferences objectAtIndex:i];
                NSLog(@"buyDemandAreaPreferences = %@", buy1);
                //[UIHelp showAlertDialogWithTitle:@"t" andMsg:buy1];
            }
        }
    
        if (result.buyDemandCategoryPreferences != nil) {
            cnt = result.buyDemandCategoryPreferences.count;
            for (int i = 0; i < cnt; i++) {
                NSString * buy1 = (NSString *)[result.buyDemandCategoryPreferences objectAtIndex:i];
                NSLog(@"buyDemandCategoryPreferences = %@", buy1);
                //[UIHelp showAlertDialogWithTitle:@"t" andMsg:buy1];
            }
        }

        if (result.buyDemandKeywordPreferences != nil) {
            cnt = result.buyDemandKeywordPreferences.count;
            for (int i = 0; i < cnt; i++) {
                NSString * buy1 = (NSString *)[result.buyDemandKeywordPreferences objectAtIndex:i];
                NSLog(@"buyDemandKeywordPreferences = %@", buy1);
                //[UIHelp showAlertDialogWithTitle:@"t" andMsg:buy1];
            }
        }
       
        self.detailObjects = result;
        [self draw];
    } else if (transactionType == AMTRANSACTION_TYPE_PRECISION_SAVE_FREE_USER_RES) {
        AMPrecisionSaveFreeUserResResult * result = (AMPrecisionSaveFreeUserResResult *)[objects objectAtIndex:0];
        if (result == nil || result.rspResult == nil) {
            return ;
        }
        NSLog(@"SaveFreeUserResResult = %d", [[result rspResult] boolValue]);
    } else if(transactionType == AMTRANSACTION_TYPE_PRECISION_TALK_PERMISSION){
        AMPrecisionTalkPermissionResult * result = (AMPrecisionTalkPermissionResult *)[objects objectAtIndex:0];
        if (result == nil || result.hasPermissionUsed == nil || result.talked == nil) {
            return ;
        }
        
        BOOL canTalk = [[result hasPermissionUsed] boolValue];
        BOOL isTalked = [[result talked] boolValue];
        
        NSLog(@"visitor status canTalk = %d", canTalk);
        NSLog(@"visitor status isTalked = %d", isTalked);
        
        if (isTalked) {
            [self gotoWwTalk: _wwId: [_detailObjects.handShake boolValue]: _visitorId: _detailObjects.showName];
        } else {
            if (canTalk) {
                UIAlertView *alert = [[UIAlertView alloc] 
                                      initWithTitle:NSLocalizedString(@"Notice", nil) 
                                      message:NSLocalizedString(@"PM_Use_Talk_Confirm", nil) 
                                      delegate:self 
                                      cancelButtonTitle:NSLocalizedString(@"Cancel", nil) 
                                      otherButtonTitles:NSLocalizedString(@"OK", nil),
                                      nil];
                [alert setTag:0];
                [alert show];
                [alert release];
            } else {
                UIAlertView *alert = [[UIAlertView alloc] 
                                      initWithTitle:NSLocalizedString(@"Notice", nil) 
                                      message:NSLocalizedString(@"PM_Cannot_Talk", nil) 
                                      delegate:self 
                                      cancelButtonTitle:NSLocalizedString(@"OK", nil)
                                      otherButtonTitles:nil,
                                      nil];
                [alert setTag:1];
                [alert show];
                [alert release];
            }
        }
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    NSLog(@"alertView click tag = %d, index = %d", alertView.tag, buttonIndex);
    switch (alertView.tag) {
        case 0:
            if (buttonIndex == 1) {
                [self gotoWwTalk: _wwId: [_detailObjects.handShake boolValue]: _visitorId: _detailObjects.showName];
            }
            break;
        default:
            break;
    }
}

-(void)draw {
    
    if (self.detailObjects == nil) {
        return ;
    }
    
    UIColor * viewColor = [UIHelp colorWithHexString:@"0xffffff"];
    UIColor * bgColor = [UIHelp colorWithHexString:@"0xf5f5f5"];
    
    self.mContentScrollView.backgroundColor = bgColor;
    
    //视觉稿顶部高度
    int tempY = 10;
    
    int tempX = 15;
    
    //握手成功标志
    if(_detailObjects != nil && [_detailObjects.handShake boolValue]){
        UIImageView * hasTalked = [[UIImageView alloc]init];
        hasTalked.frame = CGRectMake( 15 , 10 , 30 ,30);
        hasTalked.image = [UIImage imageNamed:@"icon_wscg"];
        [self.mContentScrollView addSubview:hasTalked];
        tempX = 15 + hasTalked.frame.size.width + 5;
    }

    
    //询盘人
    //    UILabel *subjectLabel =  [[self getSubjectLabel:@"test12345678901234567890"] retain];
    
    UILabel *subjectLabel =  [[self getSubjectLabel:self.detailObjects.showName] retain];
    subjectLabel.frame = CGRectMake(0, 0, 290, [self.detailObjects.showName sizeWithFont:subjectLabel.font constrainedToSize:CGSizeMake(290, MAXFLOAT)].height);
    subjectLabel.frame = CGRectMake(tempX, tempY, subjectLabel.frame.size.width, subjectLabel.frame.size.height);
    
    CGSize size = [subjectLabel.text sizeWithFont:subjectLabel.font constrainedToSize:CGSizeMake(MAXFLOAT,30)];
    
    CGFloat widthOfSub = size.width;
    if ( size.width > 135 )
    {
        widthOfSub = 135;
    }
    
    subjectLabel.frame = CGRectMake(tempX, tempY, widthOfSub, subjectLabel.frame.size.height);
    
    //    subjectLabel.layer.borderWidth =1;
//    subjectLabel.layer.borderColor = [[UIColor blackColor] CGColor];
    
//    NSLog(@"the border of subject is %f", subjectLabel.layer.);
    
    NSLog(@"the height of show name is %f" , subjectLabel.frame.size.height);
    
    [self.mContentScrollView addSubview:subjectLabel];
    
    //showName和jobTitle之间间距5
    tempY += (subjectLabel.frame.size.height );
    
    //询盘人职务
    UILabel *jobTitle =  [[self getSubjectLabel:self.detailObjects.position] retain];
    
    jobTitle.font = [UIFont boldSystemFontOfSize:12.0f];
    jobTitle.textColor = [UIHelp colorWithHexString:@"0x666666"];
    jobTitle.frame = CGRectMake(0, 0, 290, [self.detailObjects.position sizeWithFont:jobTitle.font constrainedToSize:CGSizeMake(290, MAXFLOAT)].height);
    jobTitle.frame = CGRectMake(tempX, tempY, jobTitle.frame.size.width, jobTitle.frame.size.height);
    [self.mContentScrollView addSubview:jobTitle];
    
    tempY += (jobTitle.frame.size.height );
    
    NSLog(@"the height of jobTitle  is %f" , jobTitle.frame.size.height);
    
    
    
    NSLog(@"the tempY is %d", tempY);

//    jobTitle.layer.borderWidth =1;
//    jobTitle.layer.borderColor = [[UIColor blackColor] CGColor];
//    
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
    label1.text = @"所在地区：" ;
    label1.textColor = [UIHelp colorWithHexString:@"0x666666"];
    label1.font = [UIFont  systemFontOfSize:14.0f];
    label1.backgroundColor = viewColor;
    [basicInfo addSubview:label1];
    
    NSLog(@"the height of label1 is %f", label1.frame.size.height);
    
    UILabel * contentLabel1 = [[UILabel alloc]init];
    contentLabel1.frame = CGRectMake(80, 10 , 210, 14);
    contentLabel1.text = @"";
    if (self.detailObjects.area != nil && ![self.detailObjects.area isEqualToString:@""]) {
        contentLabel1.text = [contentLabel1.text stringByAppendingString:self.detailObjects.area];
    }else {
        contentLabel1.text = [contentLabel1.text stringByAppendingString:@"无"];
    }
    contentLabel1.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel1.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel1.backgroundColor = viewColor;
    [basicInfo addSubview:contentLabel1];

    innerY += label1.frame.size.height + 10;
    
    UILabel * label2 = [[UILabel alloc]init];
    label2.frame = CGRectMake(10, innerY , 70, 14);
    label2.text = @"关注类目：";
    label2.textColor = [UIHelp colorWithHexString:@"0x666666"];
    label2.font = [UIFont  systemFontOfSize:14.0f];
    label2.backgroundColor = viewColor;
    [basicInfo addSubview:label2];
    
    UILabel * contentLabel2 = [[UILabel alloc]init];
    contentLabel2.frame = CGRectMake(80, innerY , 210, 14);
    contentLabel2.text = @"";
    contentLabel2.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel2.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel2.backgroundColor = viewColor; 
    contentLabel2.lineBreakMode = UILineBreakModeWordWrap;
    contentLabel2.numberOfLines = 0;
    
    if ( self.detailObjects.buyDemandCategoryPreferences.count > 0 )
    {
        
        NSString * categories = [self.detailObjects.buyDemandCategoryPreferences objectAtIndex:0];
        for ( int i = 1 ; i < self.detailObjects.buyDemandCategoryPreferences.count ; i ++ )
        {
            if(i<3){
              categories = [categories stringByAppendingFormat:@" %@", [self.detailObjects.buyDemandCategoryPreferences objectAtIndex: i ]];  
            }
            
        }
        
        contentLabel2.text = [contentLabel2.text stringByAppendingString:categories];
                

    }else {
        contentLabel2.text = [contentLabel2.text stringByAppendingString:@"无"];
    }
 
    CGSize heightSize = [ contentLabel2.text sizeWithFont:contentLabel2.font constrainedToSize:CGSizeMake(210, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
    
    contentLabel2.frame= CGRectMake(80, innerY , 210, heightSize.height);
    [basicInfo addSubview:contentLabel2];
    innerY += heightSize.height + 10 ;
    
    UILabel * label3 = [[UILabel alloc]init];
    label3.frame = CGRectMake(10, innerY , 70, 14);
    label3.text = @"搜索信息：";
    label3.textColor = [UIHelp colorWithHexString:@"0x666666"];
    label3.font = [UIFont  systemFontOfSize:14.0f];
    label3.backgroundColor = viewColor;
    [basicInfo addSubview:label3];
    
    UILabel * contentLabel3 = [[UILabel alloc]init];
    contentLabel3.frame = CGRectMake(80, innerY, 210, 14);
    contentLabel3.text = @"";
    contentLabel3.textColor = [UIHelp colorWithHexString:@"0x333333"];
    contentLabel3.font = [UIFont  systemFontOfSize:14.0f];
    contentLabel3.backgroundColor = viewColor;
    contentLabel3.lineBreakMode = UILineBreakModeWordWrap;
    contentLabel3.numberOfLines = 0;
    
    if ( self.detailObjects.buyDemandKeywordPreferences.count > 0 )
    {
        NSString * keywords = [self.detailObjects.buyDemandKeywordPreferences objectAtIndex:0];
        for ( int i = 1 ; i < self.detailObjects.buyDemandKeywordPreferences.count ; i ++ )
        {
            keywords = [keywords stringByAppendingFormat:@" %@", [self.detailObjects.buyDemandKeywordPreferences objectAtIndex: i ]];
        }
        
        contentLabel3.text = [contentLabel3.text stringByAppendingString:keywords];
         
    }else {
        contentLabel3.text = [contentLabel3.text stringByAppendingString:@"无"];
    }
    
    heightSize = [ contentLabel3.text sizeWithFont:contentLabel3.font constrainedToSize:CGSizeMake(contentLabel3.frame.size.width, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
    
    contentLabel3.frame= CGRectMake(80, innerY , 210, heightSize.height );
   
    [basicInfo addSubview:contentLabel3];
    innerY += heightSize.height + 10 ;
    

    
    NSLog(@"innerY before label4 is %d", innerY);
    
    UILabel * label4 = [[UILabel alloc]init];
    label4.frame = CGRectMake(10, innerY , 70, 14);;
    label4.text = @"意向地区：";
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
    
    if ( self.detailObjects.buyDemandAreaPreferences.count > 0 )
    {
        NSString * areas = [self.detailObjects.buyDemandAreaPreferences objectAtIndex:0];
        for ( int i = 1 ; i < self.detailObjects.buyDemandAreaPreferences.count ; i ++ )
        {
            areas = [areas stringByAppendingFormat:@" %@", [self.detailObjects.buyDemandAreaPreferences objectAtIndex: i ]];
        }
        
        contentLabel4.text = [contentLabel4.text stringByAppendingString:areas];
       
    }else {
        contentLabel4.text = [contentLabel4.text stringByAppendingString:@"无"];
    }  
    
    heightSize = [ contentLabel4.text sizeWithFont:contentLabel4.font constrainedToSize:CGSizeMake(contentLabel4.frame.size.width, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
    
    contentLabel4.frame= CGRectMake(80, innerY , 210, heightSize.height );
    [basicInfo addSubview:contentLabel4];
    innerY += heightSize.height + 10;
   
    
    
//    innerY += label4.frame.size.height + 10;
    NSLog(@"innerY after  label4 is %d", innerY);
    basicInfo.frame = CGRectMake(10, tempY , 300, innerY);

    [self.mContentScrollView addSubview:basicInfo];
    
    tempY += basicInfo.frame.size.height  ;
    
    if ( self.hasTalkPermision && _detailObjects != nil && [_detailObjects.handShake boolValue]) {
        //基本联系方式table
        if(self.detailObjects != nil){
            
            AMPrecisionContactView * contactView = [[AMPrecisionContactView alloc] init];
            [contactView setNavigationController:self.navigationController];
            
            [contactView setContactInfo:self.detailObjects ];
            [contactView reloadData];
            
                      
            
            contactView.frame = CGRectMake(0, tempY, contactView.frame.size.width, contactView.frame.size.height);
            [self.mContentScrollView addSubview:contactView];
            tempY += contactView.frame.size.height;

            
            [contactView release];
        }
        
        tempY -= 10;
    }else {
        tempY +=  10;
        
        UIButton * contactHidden = [[UIButton alloc]init];
        
        [[contactHidden layer] setCornerRadius:10.0];
        [contactHidden setClipsToBounds:YES];
        [[contactHidden layer] setBorderColor:[[UIColor lightGrayColor ] CGColor]];
        //    [[basicInfo layer] setBorderColor:[[UIColor clearColor] CGColor]];
        [[contactHidden layer] setBorderWidth:1.0];
        contactHidden.frame = CGRectMake(10, tempY , 300, 44);
        //    basicInfo.backgroundColor = [UIColor clearColor] ;
        contactHidden.backgroundColor = viewColor;
        
        UILabel * hiddenTip = [[UILabel alloc]init];
        hiddenTip.frame = CGRectMake(10, 12 , 300, 20);
        hiddenTip.text = @"洽谈成功后可获取联系方式";
        hiddenTip.textColor = [UIHelp colorWithHexString:@"0x333333"];
        hiddenTip.font = [UIFont  systemFontOfSize:14.0f];
        hiddenTip.backgroundColor = viewColor;

        [contactHidden addSubview:hiddenTip];
        [hiddenTip release];
        
        
        UIImageView * hiddenImg = [[UIImageView alloc ]init];
        hiddenImg.frame = CGRectMake(260, 12 , 20, 20);
        hiddenImg.image = [UIImage imageNamed:@"icon_lock"];
        [contactHidden addSubview:hiddenImg];
        [hiddenImg release];
        
        [contactHidden addTarget:self action:@selector(contactGotoTalk:) forControlEvents:UIControlEventTouchUpInside];
        
        
        [self.mContentScrollView addSubview:contactHidden];
        
        tempY += 44;
    }
        
    self.partHeight=tempY;
    
    AMAccessLogView * logView = [[AMAccessLogView alloc]init];
    
    [logView.accessArray addObjectsFromArray:self.detailObjects.accessLog];
    logView.accessCount = [NSNumber numberWithInt: self.detailObjects.accessLog.count];
    [logView calculateHeight];
    logView.frame = CGRectMake(0, tempY, 320, logView.frame.size.height );
    [self.mContentScrollView addSubview:logView];
    
    AMAccessLogFullView * logFullView = [[AMAccessLogFullView alloc]init];
    [logFullView.accessArray addObjectsFromArray:self.detailObjects.accessLog];
    logFullView.accessCount = [NSNumber numberWithInt: self.detailObjects.accessLog.count];
    [logFullView calculateHeight];
    logFullView.frame = CGRectMake(0, tempY, 320, logFullView.frame.size.height);

//    [self.mContentScrollView addSubview:logFullView];

    self.precisionView = logView;
    self.precisionFullView = logFullView;

    self.mContentScrollView.contentSize = CGSizeMake(320, tempY + logView.frame.size.height);
    
    [self setupTalkBtnImage];
    
//    self.mButton.titleLabel.text = @"洽谈？";
}

-(void)setupTalkBtnImage
{
    [self.mButton setImage:[UIImage imageNamed:@"icon_ww.png"] forState:UIControlStateNormal];
    [self.mButton setImageEdgeInsets:UIEdgeInsetsMake(0, -10, 0, 0)];
}

-(UILabel *) getSubjectLabel:(NSString *)subject {
    UILabel * subjectLabel = [[[UILabel alloc] init]autorelease];
    subjectLabel.backgroundColor = [UIColor clearColor];
    subjectLabel.textColor = [UIHelp colorWithHexString:@"0x000000"];
    subjectLabel.textAlignment = UITextAlignmentLeft;
    subjectLabel.font = [UIFont boldSystemFontOfSize:16.0f];
//    subjectLabel.lineBreakMode = UILineBreakModeWordWrap;
    subjectLabel.numberOfLines = 0;
    subjectLabel.text = subject;
    
    subjectLabel.frame = CGRectMake(0, 0, 290, [UIHelp getLabelSizeWithFont:subjectLabel.font labelString:subjectLabel.text labelWidth:290].height);
    
    CGSize size = [subjectLabel.text sizeWithFont:subjectLabel.font constrainedToSize:CGSizeMake(MAXFLOAT,30)];
    
    NSLog(@"the width should be %f", size.width);
    
    return subjectLabel;
}

- (IBAction)actionGotoTalk:(id)sender {
    [AMLogUtils appendLog: PRECISION_VISITOR_DETAIL_ONE];
    [self startChat];
}

- (void)contactGotoTalk:(id)sender{
    [AMLogUtils appendLog: PRECISION_VISITOR_DETAIL_TWO];
    [self startChat];
}

- (void) startChat {
    if ([UserDataUtils isPmFreeUser]) {
        [self loadTalkPermissionRequest:_visitorId];
    } else {
        [self gotoWwTalk: _wwId: [_detailObjects.handShake boolValue]: _visitorId: _detailObjects.showName];
    }
}

-(void) gotoWwTalk:(NSString *) wwId:(BOOL)isHandShake:(NSString *)visitorId:(NSString *)showName {
    NSString *loginUserName = nil;
    loginUserName = [LoginToken getLoginUserName];
    
    if([LoginToken isWangWangLogined]) 
    {
        [self loadSaveFreeUserResRequest:visitorId];
        [self enterTalk];
    } 
    else 
    {
        mSaveFreeUserResWhenLogined = YES;
        
        isTalkAfterWwLogin = YES;
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
    }
    
    if (isHandShake) {
        mCurVisitorId = wwId;
    } else {
        mCurVisitorId = visitorId;
    }
}

- (void) onWwLoginSucc {
    if (mSaveFreeUserResWhenLogined) {
        [self loadSaveFreeUserResRequest:mCurVisitorId];
        mSaveFreeUserResWhenLogined = NO;
    }
    
    if (isTalkAfterWwLogin) {
        [self enterTalk];
        isTalkAfterWwLogin = NO;
    }
}

-(void) enterTalk {
    if (_detailObjects) 
    {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam : YES : [_detailObjects.handShake boolValue] : _visitorId : _wwId : _detailObjects.showName];
        
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.navigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

-(void)loadTalkPermissionRequest:(NSString *)visitorId {
//    [LoginToken checkAccessTokenExpired];

    if (nil == self.talkPermissionRequest) {
        self.talkPermissionRequest = [[AMPrecisionTalkPermissionRequest alloc] init]; 
    }
        
    self.talkPermissionRequest.requestURL = OCEAN_API_URL_PRECISION_TALK_PERMISSION;  
    self.talkPermissionRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_TALK_PERMISSION;
    self.talkPermissionRequest.siteId = [UserDataUtils getPmSiteId];
    self.talkPermissionRequest.visitorId = visitorId;
    [self loadObjectsFromRemoteTalkPermission];
}

-(void)loadSaveFreeUserResRequest:(NSString *)visitorId {
    if (nil == self.saveFreeUserResRequest) {
        self.saveFreeUserResRequest = [[AMPrecisionSaveFreeUserResRequest alloc] init]; 
    }
        
    self.saveFreeUserResRequest.requestURL = OCEAN_API_URL_PRECISION_SAVE_FREE_USER_RES;  
    self.saveFreeUserResRequest.transactionType = AMTRANSACTION_TYPE_PRECISION_SAVE_FREE_USER_RES;
    self.saveFreeUserResRequest.siteId = [UserDataUtils getPmSiteId];
    self.saveFreeUserResRequest.visitorId = visitorId;
    [self loadObjectsFromRemoteSaveFreeUserRes];
}

- (void)loadObjectsFromRemoteTalkPermission {
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* resultMapping = [AMPrecisionTalkPermissionResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_TALK_PERMISSION usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionTalkPermissionResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.talkPermissionRequest;
    }];
}

- (void)loadObjectsFromRemoteSaveFreeUserRes {
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* resultMapping = [AMPrecisionSaveFreeUserResResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRECISION_SAVE_FREE_USER_RES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPrecisionSaveFreeUserResResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.saveFreeUserResRequest;
    }];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)showFullList
{
    [AMLogUtils appendLog: PRECISION_VISITOR_DETAIL_SIX];
    [self.precisionView removeFromSuperview];
    
    [self.mContentScrollView addSubview:self.precisionFullView];
    self.mContentScrollView.contentSize = CGSizeMake(320, self.partHeight + self.precisionFullView.frame.size.height);
    
}

- (void)hideFullList
{
    [AMLogUtils appendLog: PRECISION_VISITOR_DETAIL_SEVEN];
    [self.precisionFullView removeFromSuperview];
   
    [self.mContentScrollView addSubview:self.precisionView];
    
    self.mContentScrollView.contentSize = CGSizeMake(320, self.partHeight + self.precisionView.frame.size.height);
}





@end
//
//  AMCompanyTabViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCompanyTabViewController.h"
#import "ConstDef.h"
#import "StringUtils.h"
#import "AMCompanyDetail.h"
#import "AMCompanyDetailRequest.h"
#import "AMCreditResult.h"
#import "AMCreditResultRequest.h"
#import "AMCreditSummary.h"
#import "AMCreditGuarantee.h"
#import "AMCreditRealAuth.h"
#import "UIHelp.h"
#import "AMCompanyDetailViewController.h"
#import "AMCompanyCreditViewController.h"
#import "AMCompanyMapViewController.h"
#import "AMCompanyOfferListViewController.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliNavigationBackButton.h"
#import "AliImageButton.h"
#import "AliImageControlFactory.h"

#import "LoginToken.h"
#import "AMIMViewController.h"
#import "AMCUDResult.h"
#import "AliToastView.h"
#import "AMFavoriteBaseItem.h"

const NSString * TAB_VIEW_COMPANY_DETAIL = @"tab_view_company_detail";
const NSString * TAB_VIEW_COMPANY_CREDIT = @"tab_view_company_credit";
const NSString * TAB_VIEW_MEMBER_ID = @"tab_view_member_id";

@implementation AMCompanyTabViewController

@synthesize  mMemberId;
@synthesize mCompanyName;
@synthesize addFavoriteRequset = _addFavoriteRequset;
@synthesize delFavoriteRequset = _delFavoriteRequset;

-(AMFavoriteRequest*)addFavoriteRequset
{
    if (_addFavoriteRequset==nil) {
        _addFavoriteRequset = [[AMFavoriteRequest alloc] init];
        _addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD;
    }
    return _addFavoriteRequset;
}

-(AMFavoriteRequest*)delFavoriteRequset
{
    if (_delFavoriteRequset==nil) {
        _delFavoriteRequset = [[AMFavoriteRequest alloc] init];
        _delFavoriteRequset.transactionType =AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST_DELETE;
    }
    return _delFavoriteRequset;
}

- (void) dealloc
{
    [mMemberId release];
    [mCompanyName release];
    
    [mCompanyDetail release];
    [mCreditResult release];
    [self.addFavoriteRequset release];
    [super dealloc];
}

- (void) initContentViews
{
    [super addTabPage:@"基本信息" viewControllerName:@"AMCompanyDetailViewController"];
    [super addTabPage:@"诚信档案" viewControllerName:@"AMCompanyCreditViewController"];
    [super addTabPage:@"公司地图" viewControllerName:@"AMCompanyMapViewController"];
    [super addTabPage:@"产品列表" viewControllerName:@"AMCompanyOfferListViewController"];
    
    [super switchContentView:0];
    //[self endLoadingView];
}

- (void)addCompanyFavorite {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* cudResultMapping = [AMCUDResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: cudResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_COMPANY_FAV_ADD usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCUDResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.addFavoriteRequset;
    }];
}

-(void) addFavCompany {
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:nextController animated:YES];
        [nextController release];
        
    }else{
        self.addFavoriteRequset.requestURL=OCEAN_API_URL_COMPANY_FAV_ADD;
        self.addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD;
        if (mCompanyDetail==nil) {
            mCompanyDetail = [[AMCompanyDetail alloc] init];        
        }
        mCompanyDetail = [self.dataDict objectForKey:TAB_VIEW_COMPANY_DETAIL];        
        if (mCompanyDetail) {
            self.addFavoriteRequset.memberid = mMemberId;   //? mCompanyDetail.memberId
            self.addFavoriteRequset.companyid = mCompanyDetail.identifier;
            
            [self addCompanyFavorite];
        }else{
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"收藏失败，请检查网络设置"] show];
        }


    }
}

/*
- (void)deleteFavoriteRecord:(NSString *)OceanApiUrl {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* cudResultMapping = [AMCUDResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: cudResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OceanApiUrl usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCUDResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.delFavoriteRequset;
    }];
}

-(void) delFavCompany {
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        //[AliToast showWithText:@"请登录！" duration:1]; 
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:nextController animated:YES];
        
    }else{
        self.delFavoriteRequset.requestURL=OCEAN_API_URL_COMPANY_FAV_DEL;
        self.delFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST_DELETE;
        self.delFavoriteRequset.memberid =mMemberId;
        self.delFavoriteRequset.companyids = [NSArray arrayWithObjects:mCompanyDetail.identifier, nil];
        [self deleteFavoriteRecord:OCEAN_API_URL_COMPANY_FAV_DEL];
    
    }
}
*/

- (void) setupTitleBarFAV
{
    //custome title label
    [self setTitle:@"公司详情"];
    
    //add favorite button
    [self initFavBtn];
}

- (void) initFavBtn {
    AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_SUCCESS_EXTEND_BTN];
    [favBtn setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [favBtn setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    
    [favBtn addTarget:self action:@selector(addFavCompany) forControlEvents:UIControlEventTouchUpInside];
    [super setNavigationRightItem:favBtn];
    favBtn.frame = CGRectMake(0, 0, 44, 30);
}

- (void) setupTitleBar
{
    //custome title label
    [self setTitle:@"公司详情"];
    
    //add favorite button
//    AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_NAV_BTN];
    
    btnBackImg = [UIImage imageNamed:@"btn_tb_normal"];
    btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
    btnBackImgPressed = [UIImage imageNamed:@"btn_tb_v"];
    btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
    
    UIButton *favBtn = [[UIButton alloc] init];
    [favBtn setContentHorizontalAlignment:UIControlContentHorizontalAlignmentCenter];
    [favBtn setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [favBtn setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [favBtn setImage:[UIImage imageNamed:@"icon_aliww_fav_01"] forState:UIControlStateNormal];
    favBtn.frame = CGRectMake(0, 0, 44, 30);
    

    
    [favBtn addTarget:self action:@selector(addFavCompany) forControlEvents:UIControlEventTouchUpInside];
    [super setNavigationRightItem:favBtn];
    [favBtn release];
}



- (id)initWithMemberId:(NSString *)memberId companyName:(NSString *)companyName preViewName: (NSString *)preViewName
{
    self = [super init];
    if(self){         
        
        self.mMemberId = memberId;
        self.mCompanyName = companyName;
      
        if ([preViewName isEqualToString:@"AMFavoritesViewController"]) {
            [self setupTitleBarFAV];
        }else{
            [self setupTitleBar];
        }
        
        [self.dataDict setObject:self.mMemberId forKey:TAB_VIEW_MEMBER_ID];
        [self loadRequest];
    }
    return self;
}

-(void)loadRequest
{
    _companyDetailRequest = [[AMCompanyDetailRequest alloc] init];
    _companyDetailRequest.memberId = self.mMemberId;  
    
    _creditResultRequest = [[AMCreditResultRequest alloc] init];
    _creditResultRequest.memberId = self.mMemberId;
    
    dataLoadedTime = 0;
    
    [self.mLoadingView showLoadingView];
    [self loadObjectsFromRemote];
    
} 

- (void)loadObjectsFromRemote {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* companyDetailMapping = [AMCompanyDetail sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: companyDetailMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_COMPANY_DETAIL_REQUEST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCompanyDetail  class]];
            loader.objectMapping = [AMCompanyDetail sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _companyDetailRequest;
    }];
//    
//    // Register our mappings with the provider
//    RKObjectMapping* creditResultMapping = [AMCreditResult  sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: creditResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CREDIT_RESULT usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCreditResult   class]];
            loader.objectMapping = [AMCreditResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _creditResultRequest;
    }];
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
    dataLoadedTime++;
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
    //	NSLog(@"Loaded objects: %@", objects);   
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if (transactionType == AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD) {
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // add favorite successfully 
//                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FROM_DETAIL object:self];

                [self initFavBtn];
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavSucc", @"")] show];
                
            } else {
                if (result.resultCode != nil && [result.resultCode isEqualToString:FAVORITE_ADD_CONTENT_HAS_EXISTED]) {
                    [self initFavBtn];
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavCompany", @"")] show];
                }else if(result.resultCode != nil && [result.resultCode isEqualToString:FAVORITE_ADD_STORAGE_HAS_FULL]){
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedCompany", @"")] show];
                }else {
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                }
            }
        }/* else if (transactionType == AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST_DELETE) {
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // del favorite successfully
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FROM_DETAIL object:self];
                AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_NAV_BTN];
                [favBtn addTarget:self action:@selector(addFavCompany) forControlEvents:UIControlEventTouchUpInside];
                
                [super setNavigationRightItem:favBtn]; 
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏成功"] show];               
                
            } else {
                // failed to del
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏失败"] show];
            }
        }
          */
        
    } else{
        [_objects release];
        
        id object = [objects objectAtIndex:0];
        if(object != nil){
            if([object class] == [AMCompanyDetail class]){
                AMCompanyDetail  *result = (AMCompanyDetail*)object;
                mCompanyDetail = result;
                NSLog(@"AMCompanyDetail %@", result.name);
                [self.dataDict setObject:result forKey:TAB_VIEW_COMPANY_DETAIL];
                [self initContentViews];
            }else if([object class] == [AMCreditResult class]){
                AMCreditResult *result = (AMCreditResult *)object;
                mCreditResult = result;
                NSLog(@"AMCreditResult tplogo %@", result.summary.tpLogo);   
                [self.dataDict setObject:result forKey:TAB_VIEW_COMPANY_CREDIT];
            }
            
            dataLoadedTime++;
            if(dataLoadedTime >= 3){
                //[self initContentViews];
                [self endLoadingView];
             }
        }else{
              [self endLoadingView];
            [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
        }

        
    }  
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    [self endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        
        if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
            NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
            
            if (transactionType == AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD) {
                
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"收藏失败，请检查网络设置"] show];
            } 
            
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        
    }
}

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    [self endLoadingView];
    [self navigationBack];
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    

}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
}



@end

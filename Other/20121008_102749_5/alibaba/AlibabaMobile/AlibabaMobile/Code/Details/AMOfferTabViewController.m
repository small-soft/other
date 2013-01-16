//
//  AMOfferTabViewController.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferTabViewController.h"
#import "AMOfferDetailViewController.h"
#import "AMOfferPropertiesViewController.h"
//#import "AMOfferCompanyViewController.h"
#import "StringUtils.h"
#import "ConstDef.h"
#import "AMOfferDetail.h"
#import "UIHelp.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliImageButton.h"
#import "AliImageControlFactory.h"
#import "AMOfferWebDetailViewController.h"
#import "AliTabViewController.h"

#import "LoginToken.h"
#import "AMIMViewController.h"
#import "AMCUDResult.h"
#import "AliToastView.h"
#import "AMFavoritesViewController.h"
#import "AMFavoriteBaseItem.h"

//content view id
static const int OFFER_TAB_VIEW_DETAIL = 0;
static const int OFFER_TAB_VIEW_PROPERTIES = 1;
static const int OFFER_TAB_VIEW_COMPANY = 2;
static const int OFFER_TAB_VIEW_WEB = 3;

NSString * TAB_VIEW_DATA_OFFER_DETAIL = @"offer_detail_tab_data_offer_detail";

@implementation AMOfferTabViewController


//other properties
@synthesize mOfferId;
@synthesize mOfferName;
@synthesize addFavoriteRequset = _addFavoriteRequset;
@synthesize delFavoriteRequset = _delFavoriteRequset;

-(AMFavoriteRequest*)addFavoriteRequset
{
    if (_addFavoriteRequset==nil) {
        _addFavoriteRequset = [[AMFavoriteRequest alloc] init];
        _addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD;
    }
    return _addFavoriteRequset;
}

-(AMFavoriteRequest*)delFavoriteRequset
{
    if (_delFavoriteRequset==nil) {
        _delFavoriteRequset = [[AMFavoriteRequest alloc] init];
        _delFavoriteRequset.transactionType =AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST_DELETE;
    }
    return _delFavoriteRequset;
}

- (void)loadObjectsFromRemote {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* offerDetailMapping = [AMOfferDetail sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: offerDetailMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRODUCT_DETAIL usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMOfferDetail class]];
            loader.objectMapping = [AMOfferDetail sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _request;
    }];
}

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
    
	if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if (transactionType == AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD) {
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // add favorite successfully
//                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FROM_DETAIL object:self];                 

                [self initFavBtn];
                
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavSucc", @"")] show];
            } else {
                if (result.resultCode != nil && [result.resultCode isEqualToString:FAVORITE_ADD_CONTENT_HAS_EXISTED]) {
                    [self initFavBtn];
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavOffer", @"")] show];
                }else if(result.resultCode != nil && [result.resultCode isEqualToString:FAVORITE_ADD_STORAGE_HAS_FULL]){
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedOffer", @"")] show];
                }else {
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                }
            }
        } /* else if (transactionType == AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST_DELETE) {
            AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
            if (result.success) {
                // del favorite successfully  
                [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_FROM_DETAIL object:self];
                AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_NAV_BTN];
                [favBtn addTarget:self action:@selector(addFavOffer) forControlEvents:UIControlEventTouchUpInside];
                
                [super setNavigationRightItem:favBtn]; 
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏成功"] show];                    
                
            } else {
                // failed to del
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏失败"] show];
            }
        } */
        
    } else{
        
        [_objects release];
        
        AMOfferDetail *result = (AMOfferDetail*)[objects objectAtIndex:0];
        if(result != nil){
            [self.dataDict setObject:result forKey:TAB_VIEW_DATA_OFFER_DETAIL];
            [self initContentViews];
        }else{
              [self endLoadingView];
            [UIHelp showAlertDialogWithTitle:@"错误" andMsg:[NSString stringWithFormat:@"获取信息失败！offerid:%@", self.mOfferId ]];
        }
        
    }  

}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    [self endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
        
        if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
            NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
            
            if (transactionType == AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD) {
                
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


-(void)loadRequest
{
    _request = [[AMOfferDetailRequest alloc] init];

    _request.imageSizeType =_imageSizeType;
    _request.disableLink =_disableLink;
    _request.offerId =_offerId;
      
    [self loadObjectsFromRemote];
    [self.mLoadingView showLoadingView];
    
} 

- (void) initContentViews
{
    [super addTabPage:@"产品简介" viewControllerName:@"AMOfferDetailViewController"];
    [super addTabPage:@"产品属性" viewControllerName:@"AMOfferPropertiesViewController"];
//    [super addTabPage:@"联系方式" viewControllerName:@"AMOfferCompanyViewController"];
    [super addTabPage:@"图文详情" viewControllerName:@"AMOfferWebDetailViewController"];
    
    [super switchContentView:0];
    [self endLoadingView];
}

- (void)addOfferFavorite {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* cudResultMapping = [AMCUDResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: cudResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_OFFER_FAV_ADD usingBlock:^(RKObjectLoader* loader) {
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

-(void) addFavOffer {
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        //[AliToast showWithText:@"请登录！" duration:1]; 
        UIViewController *nextController;
        nextController = [[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil];
        nextController.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:nextController animated:YES];
        [nextController release];

    }else{
        self.addFavoriteRequset.requestURL=OCEAN_API_URL_OFFER_FAV_ADD;
        self.addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD;
       
        AMOfferDetail * detail = [self.dataDict objectForKey:TAB_VIEW_DATA_OFFER_DETAIL];
        if(detail){
            self.addFavoriteRequset.offerid = detail.offerId;
            self.addFavoriteRequset.memberid =detail.memberId;
        
            [self addOfferFavorite];
        }else{
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"收藏失败，请检查网络设置"] show];
        }
        
    }
}

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
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCUDResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.delFavoriteRequset;
    }];
}

/*
-(void) delFavOffer {
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        //[AliToast showWithText:@"请登录！" duration:1]; 
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:nextController animated:YES];
        
    }else{
          
        AMOfferDetail * detail = [self.dataDict objectForKey:TAB_VIEW_DATA_OFFER_DETAIL];
        if(detail){
            self.delFavoriteRequset.requestURL=OCEAN_API_URL_OFFER_FAV_DEL;
            self.delFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST_DELETE;
            self.delFavoriteRequset.memberid =detail.memberId;
            self.delFavoriteRequset.offerids = [NSArray arrayWithObjects:detail.offerId, nil];
            
            [self deleteFavoriteRecord:OCEAN_API_URL_OFFER_FAV_DEL];
            
        }else{
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"删除收藏失败"] show];
        }
        
    }
}
*/


- (void) setupTitleBarFav
{
    //custome title label
    [self setTitle:@"产品详情"];
    
    //add favorite button
    [self initFavBtn];
}

- (void) initFavBtn {
    AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_SUCCESS_EXTEND_BTN];
    [favBtn setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [favBtn setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    favBtn.frame = CGRectMake(0, 0, 44, 30);
    
    [favBtn addTarget:self action:@selector(addFavOffer) forControlEvents:UIControlEventTouchUpInside];
    
    [super setNavigationRightItem:favBtn]; 
}

- (void) setupTitleBar
{
    //custome title label
    [self setTitle:@"产品详情"];
    
    //add favorite button
//    AliImageButton * favBtn = [[AliImageControlFactory sharedInstance] getImageButtonWithType:FAV_NAV_BTN];
    
//    UIImage * btnBackImg = [UIImage imageNamed:@"btn_tb_normal"];
    btnBackImg = [UIImage imageNamed:@"btn_tb_normal"];
    btnBackImg = [btnBackImg stretchableImageWithLeftCapWidth:btnBackImg.size.width/2 topCapHeight:btnBackImg.size.height/2];
//    UIImage * btnBackImgPressed = [UIImage imageNamed:@"btn_tb_v"];
    btnBackImgPressed = [UIImage imageNamed:@"btn_tb_v"];
    btnBackImgPressed = [btnBackImgPressed stretchableImageWithLeftCapWidth:btnBackImgPressed.size.width/2 topCapHeight:btnBackImgPressed.size.height/2];
    
    UIButton *favBtn = [[UIButton alloc] init];
    [favBtn setBackgroundImage:btnBackImg forState:UIControlStateNormal];
    [favBtn setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [favBtn setImage:[UIImage imageNamed:@"icon_aliww_fav_01"] forState:UIControlStateNormal];
    favBtn.frame = CGRectMake(0, 0, 44, 30);
    
    [favBtn addTarget:self action:@selector(addFavOffer) forControlEvents:UIControlEventTouchUpInside];
    [super setNavigationRightItem:favBtn];
    [favBtn release];
   
}

- (id)initWithOfferId:(NSString *)offerId offerName:(NSString *)offerName preViewName: (NSString *)preViewName
{
    [super init];
    
    if(self){
        self.view.backgroundColor = [UIHelp colorWithHexString:@"0xF5F5F5"];

        self.mOfferId = offerId;
        self.mOfferName = offerName;
        if ([preViewName isEqualToString:@"AMFavoritesViewController"]) {
            [self setupTitleBarFav];
        }else{
            [self setupTitleBar];
        }
        
        
        _offerId = self.mOfferId;
        _imageSizeType =[NSNumber numberWithInt: 5];
        _disableLink =[NSNumber numberWithBool: YES];
        
       
        [self loadRequest];
    }
    
    
    return self;
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

-(void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];
    self.navigationController.navigationBar.hidden = NO;
}


-(void) dealloc
{
    [self.mOfferId release];
    [self.mOfferName release];
    [self.addFavoriteRequset release];
    [super dealloc];
}


@end

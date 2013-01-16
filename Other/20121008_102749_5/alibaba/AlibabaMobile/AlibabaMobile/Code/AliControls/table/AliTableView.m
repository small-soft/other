//
//  AliTableView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableView.h"
#import "AMIMViewController.h"
#import "LoginToken.h"
#import "AMFavoriteRequest.h"
#import "ConstDef.h"
#import "AMCUDResult.h"
#import <objc/runtime.h>
#import "AliToastView.h"
#import "AMPriceBaseItem.h"
#import "AMFavoriteBaseItem.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

@interface AliTableView()
@property (nonatomic,retain) UISwipeGestureRecognizer *swipeGesture;
@property (nonatomic,readonly,retain)UINavigationController*navigationController;
@property (nonatomic, retain) AMFavoriteRequest *addFavoriteRequset;
@property (nonatomic,retain)NSIndexPath *swipedIndexPath;
@end
@implementation AliTableView
@synthesize swipeGesture=_swipeGesture;
@synthesize favDelegate = _favDelegate;
@synthesize navigationController=_navigationController;
@synthesize addFavoriteRequset=_addFavoriteRequset;
@synthesize swipedIndexPath = _swipedIndexPath;
-(void)dealloc
{
    //[self removeGestureRecognizer:_swipeGesture];
    [_swipeGesture release];
    [_favDelegate release];
    [_navigationController release];
    [_addFavoriteRequset release];
    [_swipedIndexPath release];
    NSLog(@"swipeGesture: %d, favDelegate: %d, navigationController: %d, addFavoriteRequset: %d, swipedIndexPath: %d",[_swipeGesture retainCount],[_favDelegate retainCount],[_navigationController retainCount],[_addFavoriteRequset retainCount],[_swipedIndexPath retainCount]);
    //[self removeGestureRecognizer:_swipeGesture];
    //AM_RELEASE_SAFELY(_swipeGesture)
    
    // NSLog(@"swipeGesture: %d",[_swipeGesture retainCount]);
    [super dealloc];
}

-(UISwipeGestureRecognizer*)swipeGesture
{
    if (!_swipeGesture) {
#warning 修改人孟希羲
        _swipeGesture = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipe:)];
        [_swipeGesture setDirection:(UISwipeGestureRecognizerDirectionRight | UISwipeGestureRecognizerDirectionLeft)];
    }
    return _swipeGesture;
}


-(UINavigationController*)navigationController
{
    
    Ivar ivar = class_getInstanceVariable([UIView class], "_viewDelegate");
    UIViewController *controller = object_getIvar(self, ivar);
    if (!controller) {
        controller = object_getIvar(self.superview, ivar);
    }
    return controller.navigationController;
}
-(AMFavoriteRequest*)addFavoriteRequset
{
    if (_addFavoriteRequset==nil) {
        _addFavoriteRequset = [[AMFavoriteRequest alloc] init];
    }
    return _addFavoriteRequset;
}
-(void)doFav
{
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:nextController animated:YES];
    }else{
        NSString *msg = [[NSString alloc]initWithFormat:@"加入收藏夹？"];
        UIAlertView *alert = [[UIAlertView alloc] 
                              initWithTitle:@"" 
                              message:msg 
                              delegate:self    
                              cancelButtonTitle:@"取消"                          otherButtonTitles:@"确定" ,
                              nil]; 
        [alert show]; 
        [alert release];
        [msg release];
    }

}


- (void)addPriceFavorite {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* cudResultMapping = [AMCUDResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: cudResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRICE_FAV_ADD usingBlock:^(RKObjectLoader* loader) {
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

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {  
      //  [self.swipedIndexPath release];
        self.swipedIndexPath = nil;
        NSLog(@"取消收藏");
    }
    else {    
        NSLog(@"收藏");
      //  CGPoint swipeLocation = [self.swipeGesture locationInView:self];
      //  NSIndexPath *swipedIndexPath = [self indexPathForRowAtPoint:swipeLocation];
        if ([self.favDelegate respondsToSelector:@selector(AliTableView:addPriceToFav:)]) {
            AMPriceItem*data = [self.favDelegate AliTableView:self addPriceToFav:self.swipedIndexPath];
            if (data) {
                self.addFavoriteRequset.requestURL=OCEAN_API_URL_PRICE_FAV_ADD;
                self.addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD;
                
                self.addFavoriteRequset.themeId =data.themeId;
                self.addFavoriteRequset.sourceFromId = data.sourceFromId;
                self.addFavoriteRequset.area = data.areaId;
                self.addFavoriteRequset.memberId=[LoginToken getLoginUserName];
                
                [self addPriceFavorite];
              //  [self.swipedIndexPath release];
                self.swipedIndexPath = nil;
                return;
            }
        }
        
        if ([self.favDelegate respondsToSelector:@selector(AliTableView:addOfferToFav:)]) {
            AMOffer*data = [self.favDelegate AliTableView:self addOfferToFav:self.swipedIndexPath];
            if (data) {
                self.addFavoriteRequset.requestURL=OCEAN_API_URL_OFFER_FAV_ADD;
                self.addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD;
                self.addFavoriteRequset.offerid = data.offerId;
                self.addFavoriteRequset.memberid = data.memberId;
                [self addOfferFavorite];
                //[self.swipedIndexPath release];
                self.swipedIndexPath=nil;
                return;
            }
        }
        
        if ([self.favDelegate respondsToSelector:@selector(AliTableView:addCompanyToFav:)]) {
            AMCompany*data = [self.favDelegate AliTableView:self addCompanyToFav:self.swipedIndexPath];
            if (data) {
                self.addFavoriteRequset.requestURL=OCEAN_API_URL_COMPANY_FAV_ADD;
                self.addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD;
                self.addFavoriteRequset.memberid = data.memberId;
                self.addFavoriteRequset.companyid = data.identifier;   
                [self addCompanyFavorite];
               // [self.swipedIndexPath release];
                self.swipedIndexPath = nil;
                return;
            }
        }


    }
}

- (void)didSwipe:(UISwipeGestureRecognizer *)gestureRecognizer {
    if (self.favDelegate) {
        if (gestureRecognizer.state == UIGestureRecognizerStateEnded) {
            
            CGPoint swipeLocation = [gestureRecognizer locationInView:self];
            self.swipedIndexPath = [self indexPathForRowAtPoint:swipeLocation];
            if ([self.favDelegate respondsToSelector:@selector(AliTableView:addPriceToFav:)]) {
                AMPriceItem*data = [self.favDelegate AliTableView:self addPriceToFav:self.swipedIndexPath];
                if (data) {
                    [self doFav];
                    return;
                }
            }
            if ([self.favDelegate respondsToSelector:@selector(AliTableView:addOfferToFav:)]) {
                AMOffer*data = [self.favDelegate AliTableView:self addOfferToFav:self.swipedIndexPath];
                if (data) {
                    [self doFav];
                    return;
                }
            }
            if ([self.favDelegate respondsToSelector:@selector(AliTableView:addCompanyToFav:)]) {
                AMCompany*data = [self.favDelegate AliTableView:self addCompanyToFav:self.swipedIndexPath];
                if (data) {
                    [self doFav];
                    return;
                }
            }


        }

    }
}
-(void)setupView
{
    self.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    self.separatorColor = RGB(0xe0,0xe0,0xe0);
    self.backgroundColor = RGB(0xF0,0xf0,0xf0);
           
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [self addGestureRecognizer:self.swipeGesture];
    [self setupView];
}


-(void)scrollViewDidScroll:(UIScrollView *)scrollView callback:(void(^)(void))loadNewObjects
{
    NSInteger currentOffset = scrollView.contentOffset.y;
    NSInteger maximumOffset = scrollView.contentSize.height - scrollView.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 30.0) {
        loadNewObjects();
      }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    if (![objectLoader.params respondsToSelector:@selector(transactionType)]) {
        return;
    }
    
    AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
    if (result.success) {
        // add favorite successfully
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavSucc", @"")] show];
    } else {

        if (result.resultCode == nil) {
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
            return ;
        }
        
        if ([self.favDelegate respondsToSelector:@selector(AliTableView:addCompanyToFav:)]) {
            // Company
            if ([result.resultCode isEqualToString:FAVORITE_ADD_CONTENT_HAS_EXISTED]) {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavCompany", @"")] show];
            }else if([result.resultCode isEqualToString:FAVORITE_ADD_STORAGE_HAS_FULL]){
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedCompany", @"")] show];
            }else {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
            }
        }
        else if ([self.favDelegate respondsToSelector:@selector(AliTableView:addOfferToFav:)]) {
            // Offer
            if ([result.resultCode isEqualToString:FAVORITE_ADD_CONTENT_HAS_EXISTED]) {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavOffer", @"")] show];
            }else if([result.resultCode isEqualToString:FAVORITE_ADD_STORAGE_HAS_FULL]){
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedOffer", @"")] show];
            }else {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
            }
        }
        else if ([self.favDelegate respondsToSelector:@selector(AliTableView:addPriceToFav:)]) {
            // Price
            if ([result.resultCode isEqualToString:FAVORITE_ADD_PRICE_EXISTS]) {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavPrice", @"")] show];
            }else if([result.resultCode isEqualToString:FAVORITE_ADD_PRICE_OVER_MAXLIMITED]) {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedPrice", @"")] show];
            }else {
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
            }
        }
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] == NSURLErrorConnectionToBeOffline) {    
        [[AliToastView MakeToastWithType:TOAST_STYLE_FAV info:@"收藏失败，请检查网络设置"] show];
    }
}

@end

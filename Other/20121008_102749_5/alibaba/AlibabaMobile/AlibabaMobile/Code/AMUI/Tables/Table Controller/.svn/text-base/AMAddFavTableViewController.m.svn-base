//
//  AMAddFavTableViewController.m
//  AlibabaMobile
//
//  Created by  on 12-7-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAddFavTableViewController.h"
#import "LoginToken.h"
#import "AMCUDResult.h"
#import "AMToastView.h"
#import "AMFavoriteBaseItem.h"
#import "AMPriceBaseItem.h"
#import "AMRequestDelegate.h"
#import "ConstDef.h"

@implementation AMAddFavTableViewController

- (void)viewDidLoad
{
     _addFavoriteRequset = [[AMFavoriteRequest alloc]init];
    [super viewDidLoad];
	// Do any additional setup after loading the view.
   
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

-(void)addOfferToFav:(AMOffer *)data{
    _addFavoriteRequset.requestURL=OCEAN_API_URL_OFFER_FAV_ADD;
    _addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD;
    _addFavoriteRequset.offerid = data.offerId;
    _addFavoriteRequset.memberid = data.memberId;
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
        loader.params = _addFavoriteRequset;
    }];

}

-(void)addPriceToFav:(AMPriceItem *)data{
    _addFavoriteRequset.requestURL=OCEAN_API_URL_PRICE_FAV_ADD;
    _addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD;
    
    _addFavoriteRequset.themeId =data.themeId;
    _addFavoriteRequset.sourceFromId = data.sourceFromId;
    _addFavoriteRequset.area = data.areaId;
    _addFavoriteRequset.memberId=[LoginToken getLoginUserName];
    
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
        loader.params = _addFavoriteRequset;
    }];
}

-(void)addCompanyToFav:(AMCompany *)data{
    _addFavoriteRequset.requestURL=OCEAN_API_URL_COMPANY_FAV_ADD;
    _addFavoriteRequset.transactionType = AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD;
    _addFavoriteRequset.memberid = data.memberId;
    _addFavoriteRequset.companyid = data.identifier;   
    
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
        loader.params = _addFavoriteRequset;
    }];

}


-(void)scrollViewDidScroll:(UIScrollView *)scrollView callback:(void (^)(void))loadNewObjects
{
    NSInteger currentOffset = scrollView.contentOffset.y;
    NSInteger maximumOffset = scrollView.contentSize.height - scrollView.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 30.0) {
        loadNewObjects();
    }
}




-(void)objectLoader:(RKObjectLoader *)objectLoader didLoadObjects:(NSArray *)objects
{
    
    [super objectLoader:objectLoader didLoadObjects:objects];
    
    if (![objectLoader.params respondsToSelector:@selector(transactionType)]) {
        return;
    }
    
    NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
    
    if(transactionType==AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD||transactionType==AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD||transactionType==AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD){
        AMCUDResult *result = (AMCUDResult*)[objects objectAtIndex:0];
        if (result.success) {
            // add favorite successfully
            [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavSucc", @"")] show];
        } else {
            
            if (result.resultCode == nil) {
                [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                return ;
            }
            
            if (transactionType==AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD) {
                // Company
                if ([result.resultCode isEqualToString:FAVORITE_ADD_CONTENT_HAS_EXISTED]) {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavCompany", @"")] show];
                }else if([result.resultCode isEqualToString:FAVORITE_ADD_STORAGE_HAS_FULL]){
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedCompany", @"")] show];
                }else {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                }
            }
            else if (transactionType==AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD) {
                // Offer
                if ([result.resultCode isEqualToString:FAVORITE_ADD_CONTENT_HAS_EXISTED]) {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavOffer", @"")] show];
                }else if([result.resultCode isEqualToString:FAVORITE_ADD_STORAGE_HAS_FULL]){
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedOffer", @"")] show];
                }else {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                }
            }
            else if (transactionType==AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD) {
                // Price
                if ([result.resultCode isEqualToString:FAVORITE_ADD_PRICE_EXISTS]) {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AlreadyAddFavPrice", @"")] show];
                }else if([result.resultCode isEqualToString:FAVORITE_ADD_PRICE_OVER_MAXLIMITED]) {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavExceedPrice", @"")] show];
                }else {
                    [[AMToastView MakeToastWithType:AMTOAST_STYLE_FAV info:NSLocalizedString(@"AddFavFail", @"")] show];
                }
            }
        }
    }
    
}

-(void)objectLoader:(RKObjectLoader *)objectLoader didFailWithError:(NSError *)error
{

}



-(void)dealloc
{
    AM_RELEASE_SAFELY(_addFavoriteRequset);
    [super dealloc];
}
@end

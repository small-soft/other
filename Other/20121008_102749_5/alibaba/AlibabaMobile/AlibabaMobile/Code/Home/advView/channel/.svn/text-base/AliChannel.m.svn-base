//
//  AliChannel.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliChannel.h"
#import "AMContentRequest.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "AMHomeContent.h"
#import "AMMarketpriceViewController.h"
#import "AMNewsViewController.h"
#import "ImageMagazineCategoryViewController.h"
#import "AMCategoryViewController.h"
#import "AMBannerContentDetailViewController.h"
#import "AMGuessListViewController.h"
#import "AMIndustrySelectHomeViewController.h"
@interface AliChannel ()
@property (nonatomic,retain) AMContentRequest *dataRequest;
@property (nonatomic,retain) NSArray *sourceData;

@end
@implementation AliChannel

@synthesize dataRequest=_dataRequest;
@synthesize contentData=_contentData;
@synthesize delegate=_delegate;
@synthesize sourceData=_sourceData;
@synthesize coltrollerDelegate=_coltrollerDelegate;
-(void)dealloc
{
    [_dataRequest release];
    [_contentData release];
    [_delegate release];
    [_sourceData release];
    [_coltrollerDelegate release];
    [super dealloc];
}

-(void)entryImageMagazine
{
    // Pictorials
    ImageMagazineCategoryViewController *imageMagazineCategoryViewController = [[ImageMagazineCategoryViewController alloc] init];
    imageMagazineCategoryViewController.parentTitle = [self.coltrollerDelegate superControllerName];
    [[self.coltrollerDelegate superController].navigationController pushViewController:imageMagazineCategoryViewController animated:YES];
    [imageMagazineCategoryViewController release];
    
}
-(void)entryPrice
{
    AMMarketpriceViewController *marketpriceListController  = [[AMMarketpriceViewController alloc] initWithNibName:@"AMMarketpriceViewController" bundle:nil];
    marketpriceListController.parentTitle = [self.coltrollerDelegate superControllerName];
    [[self.coltrollerDelegate superController].navigationController pushViewController:marketpriceListController animated:YES];
    [marketpriceListController release];
    
    
}
-(void)entryNews
{
    AMNewsViewController *newsListController  = [[AMNewsViewController alloc] initWithNibName:@"AMNewsViewController" bundle:nil];
    newsListController.parentTitle = [self.coltrollerDelegate superControllerName];
     
    [[self.coltrollerDelegate superController].navigationController pushViewController:newsListController animated:YES];
#warning xiugairen megnxixi
    [newsListController release];
    
    
}


-(void)entryCategory
{
    AMCategoryViewController *categoryListController  = [[AMCategoryViewController alloc] initWithNibName:@"AMCategoryViewController" bundle:nil];
    categoryListController.parentTitle = [self.coltrollerDelegate superControllerName];
    [[self.coltrollerDelegate superController].navigationController pushViewController:categoryListController animated:YES];
    [categoryListController release];
    
}

//增加猜你喜欢和论坛两个运营位相关

-(void)entryBBS
{
    AMBannerContentDetailViewController *viewController = [[AMBannerContentDetailViewController alloc] initWithNibName:@"AMBannerContentDetailViewController" bundle:nil];
    
    viewController.showToolBar=YES;
    viewController.parentTitle = @"首页";
    viewController.hidesBottomBarWhenPushed=YES;
    [[self.coltrollerDelegate superController].navigationController pushViewController:viewController animated:YES];
    [viewController release];
}

-(void)entryGuess
{
//    AMGuessListViewController *guessListController  = [[AMGuessListViewController alloc] initWithNibName:@"AMGuessListViewController" bundle:nil];
//    guessListController.parentTitle = @"首页";
//    [[self.coltrollerDelegate superController].navigationController pushViewController:guessListController animated:YES];
//#warning 修改人孟希羲
//    [guessListController release];
    AMIndustrySelectHomeViewController *industrySelectController = [[AMIndustrySelectHomeViewController alloc] initWithNibName:@"AMIndustrySelectHomeViewController" bundle:nil ];
    [[self.coltrollerDelegate superController].navigationController pushViewController:industrySelectController animated:YES];
//    UIViewController *controller = [self.delegate superController];
//    [controller.navigationController pushViewController:industrySelectController animated:YES];
    [industrySelectController release];
    
}

-(NSArray*)sourceData
{
    if (!_sourceData) {
        _sourceData = [[NSArray alloc]initWithObjects:
        
        [NSDictionary dictionaryWithObjectsAndKeys:@"精准营销", @"title",@"channel_precision_marketing", @"type", nil,@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"最新资讯", @"title",@"channel_news_info", @"type", @"entryNews",@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"价格行情", @"title",@"channel_price_quotation", @"type",@"entryPrice",@"selector", nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"类目浏览", @"title",@"channel_brower_category", @"type", @"entryCategory",@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"生意经", @"title",@"channel_business_doc", @"type", nil,@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"热门画报", @"title",@"channel_image_magazine", @"type", @"entryImageMagazine",@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"猜您喜欢", @"title",@"channel_guess_you_like", @"type",@"entryGuess",@"selector", nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"论       坛", @"title",@"channel_forum", @"type", @"entryBBS",@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"收藏夹", @"title",@"channel_favorite", @"type",nil,@"selector", nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"订单管理", @"title",@"channel_trade", @"type", nil,@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"物流", @"title",@"channel_logistics", @"type", nil,@"selector",nil],
        [NSDictionary dictionaryWithObjectsAndKeys:@"采购管理", @"title",@"channel_purchase_match", @"type", nil,@"selector",nil],
        nil ];
    }
    return _sourceData;
}
-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc]init];
        for (NSDictionary*data in self.sourceData) {
            if ([data objectForKey:@"selector"]) {
                [_contentData addObject:data];
            }
        }
    }
    return _contentData;
}
-(AMContentRequest*)dataRequest
{
    if (!_dataRequest) {
        _dataRequest = [[AMContentRequest alloc]init];
        _dataRequest.name = @"channel_ios";
    }
    return _dataRequest;
}
-(NSString*)getTitle:(NSUInteger)index
{
    NSDictionary*data = [self.contentData objectAtIndex:index];
    return [data objectForKey:@"title"];
}

-(void)doSelector:(NSUInteger)index
{
    NSDictionary*data = [self.contentData objectAtIndex:index];
    NSString *selectorName = [data objectForKey:@"selector"];
    if([selectorName isEqualToString:@"entryNews"]){
        [AMLogUtils appendLog: APP_HOME_PAGE_SEVEN];
    }else if([selectorName isEqualToString:@"entryPrice"]){
        [AMLogUtils appendLog: APP_HOME_PAGE_EIGHT];
    }else if([selectorName isEqualToString:@"entryImageMagazine"]){
        [AMLogUtils appendLog: APP_HOME_PAGE_TEN];
    }else if([selectorName isEqualToString:@"entryCategory"]){
        [AMLogUtils appendLog: APP_HOME_PAGE_NINE];
    }else if([selectorName isEqualToString:@"entryGuess"]){
        [AMLogUtils appendLog: APP_HOME_PAGE_THIRTEEN];
    }
    
    [self performSelector:NSSelectorFromString([data objectForKey:@"selector"])];
}
extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        
        gLastDisplayErrorTimeInterval = currentTime;
    }
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);   
    [self.contentData removeAllObjects];
    for (AMHomeContent*content in objects) {
       
        for (NSDictionary*data in self.sourceData) {
            
            NSString *type = [data objectForKey:@"type"];
            
            if ([type isEqualToString:content.appPath.busiType]) {
                if ([data objectForKey:@"selector"]) {
                    [_contentData addObject:data];
                }
                break;
            }
        }

    }
  
   // [self.contentData addObjectsFromArray:objects];
    if ([self.delegate respondsToSelector:@selector(AliChannelReloadData)]) {
        [self.delegate AliChannelReloadData];
    }
  
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
    
    // Convert body to real JSON NSString
    NSRange range = {1, [[response bodyAsString] length] - 2};
    NSString *trimmedJson1 = [[[response bodyAsString] substringWithRange: range] stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
    NSString *trimmedJson2 = [trimmedJson1 stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSString *trimmedJson = [trimmedJson2 stringByReplacingOccurrencesOfString:@"\\" withString:@""];
    
    NSLog(@"Trimmed payload: %@", trimmedJson);
    
    [(NSMutableData*)[response body] setData: [trimmedJson dataUsingEncoding: NSUTF8StringEncoding]];
}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* contentMapping = [AMHomeContent sharedObjectMapping];
    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CONTENTS usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        loader.method = RKRequestMethodPOST;
        loader.params = self.dataRequest;
    }];
}
@end

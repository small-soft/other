//
//  AMRecommendBrandsDataLoader.m
//  AlibabaMobile
//
//  Created by 佳 刘 on 12-9-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMRecommendBrandsDataLoader.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "ImageMagazineCategoryViewController.h"
#import "AMMenuItemView.h"
#import "AliToastView.h"
#import "AMHomepageDressRequest.h"
#import "AMRecommendBrandsResult.h"
#import "AMMenuView.h"

@interface AMRecommendBrandsDataLoader ()
@property (nonatomic,retain) NSMutableArray *menuViewData;
@property (nonatomic,retain) HJObjManager *objMan;
@end
@implementation AMRecommendBrandsDataLoader
@synthesize request=_request;
@synthesize contentData=_contentData;
@synthesize delegate=_delegate;
@synthesize md5Checksum = _md5Checksum;
@synthesize menuViewData = _menuViewData;
@synthesize objMan =_objMan;
@synthesize imgUrl = _imgUrl;
@synthesize menuView = _menuView;

-(void)dealloc
{
    [_request release];
    [_contentData release];
    [_md5Checksum release];
    [_menuViewData release];
    [_objMan release];
    [_imgUrl release];
    [super dealloc];
}
-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc]init];
        /*for (NSDictionary*data in self.sourceData) {
         if ([data objectForKey:@"selector"]) {
         [_contentData addObject:data];
         }
         }*/
    }
    return _contentData;
}
-(AMHomepageDressRequest*)request
{
    if (!_request) {
        _request = [[AMHomepageDressRequest alloc]init];
        _request.industryId = @"gongyepin";
        _request.summary = @"";
        _request.configName = @"brandsios";
    }
    return _request;
}
-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:20 memCacheSize:50];
        
        NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
        HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
        _objMan.fileCache = fileCache;
        // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
        fileCache.fileCountLimit = 100;
        fileCache.fileAgeLimit = 60*60*24*7; //1 week
        [fileCache trimCacheUsingBackgroundThread];
        
    }
    return _objMan;
    
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
//        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show]; 
        
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];  
//        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show]; 
        
        gLastDisplayErrorTimeInterval = currentTime;
    }
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    NSLog(@"loade data error:%@",error);
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    NSLog(@"Loaded objects: %@", objects);   
//    [objectLoader.params ]
    if (objects == nil || [objects count] == 0) {
        return;
    }
    AMRecommendBrandsResult *result = (AMRecommendBrandsResult*)[objects objectAtIndex:0];
    
    if (result.brandsios.hasChild && [result.brandsios.type isEqualToString:@"brands"]) {
        self.md5Checksum = result.brandsios.md5Checksum;
        self.imgUrl = result.brandsios.imageUrl;
        
        NSUInteger childenCount = [result.brandsios.children count];
        if (childenCount > 0) {
            [self.contentData removeAllObjects];
            //[self.contentData addObjectsFromArray:result.categories.children];
            for (AMRecommendBrandsItem *item in result.brandsios.children) 
            {
                AMMenuItemView *menuItemViewTmp = [[AMMenuItemView alloc] initWithStyle:AMMenuItemViewStyleImageOnly];
//                menuItemViewTmp.label.text = @"";
                menuItemViewTmp.imageView.url = [NSURL URLWithString:item.imageUrl];
                //menuItemViewTmp.imageView.mode = UIViewContentModeScaleToFill;
                [self.objMan manage:menuItemViewTmp.imageView];
                //[menuItemViewTmp manage];
                NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:item.name, @"name",item.brandId, @"ID",menuItemViewTmp,@"view",item.imageUrl,@"imageUrl",nil];
                
                [self.contentData addObject:data];
                [menuItemViewTmp release];
            }
            [self.menuView reloadData];
        }
        else {
            [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"对不起，没有数据请稍后再试！"] show]; 
        }
    }
    else {
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"申请数据失败请稍后再试！"] show]; 
    }
    
    if ([self.delegate respondsToSelector:@selector(AliChannelReloadData)]) {
        [self.delegate AliChannelReloadData];
    }
    
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
    
    // Convert body to real JSON NSString
    /*NSRange range = {1, [[response bodyAsString] length] - 2};
     NSString *trimmedJson1 = [[[response bodyAsString] substringWithRange: range] stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
     NSString *trimmedJson2 = [trimmedJson1 stringByReplacingOccurrencesOfString:@" " withString:@""];
     NSString *trimmedJson = [trimmedJson2 stringByReplacingOccurrencesOfString:@"\\" withString:@""];
     
     NSLog(@"Trimmed payload: %@", trimmedJson);
     
     [(NSMutableData*)[response body] setData: [trimmedJson dataUsingEncoding: NSUTF8StringEncoding]];*/
}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
//	RKObjectMapping* contentMapping = [AMRecommendBrandsResult sharedObjectMapping];
//    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_INDUSTRY_CONTENTS usingBlock:^(RKObjectLoader* loader) {

        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [AMRecommendBrandsResult sharedObjectMapping];
        }
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
}
@end

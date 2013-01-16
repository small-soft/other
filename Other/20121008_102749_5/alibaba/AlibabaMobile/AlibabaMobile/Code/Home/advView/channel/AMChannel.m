//
//  AMChannel.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMChannel.h"
#import "AMHomepageDressCategoriesResult.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "ImageMagazineCategoryViewController.h"
#import "AMMenuItemView.h"
#import "AliToastView.h"

@interface AMChannel ()
@property (nonatomic,retain) NSMutableArray *menuViewData;
@property (nonatomic,retain) HJObjManager *objMan;

@end
@implementation AMChannel
@synthesize request=_request;
@synthesize contentData=_contentData;
@synthesize delegate=_delegate;
@synthesize md5Checksum = _md5Checksum;
@synthesize menuViewData = _menuViewData;
@synthesize objMan =_objMan;

-(void)dealloc
{
    [_request release];
    [_contentData release];
    [_md5Checksum release];
    [_menuViewData release];
    [_objMan release];
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
        _request.industryId = @"fuzhuangfushi";
        _request.summary = @"";
        _request.configName = @"categories";
    }
    return _request;
}
-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:10 memCacheSize:40];
        
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
    AMHomepageDressCategoriesResult *result = (AMHomepageDressCategoriesResult*)[objects objectAtIndex:0];
    
    if (result.categories.hasChild && [result.categories.type isEqualToString:@"categories"]) {
        self.md5Checksum = result.categories.md5Checksum;
        NSUInteger childenCount = [result.categories.children count];
        if (childenCount > 0) {
            [self.contentData removeAllObjects];
            //[self.contentData addObjectsFromArray:result.categories.children];
            for (AMHomepageDressChilden *homepageDressChilden in result.categories.children) 
            {
                AMMenuItemView *menuItemViewTmp = [[AMMenuItemView alloc] init];
                menuItemViewTmp.label.text = homepageDressChilden.name;
                [menuItemViewTmp.imageView clear];
                [menuItemViewTmp.imageView showLoadingWheel];
                menuItemViewTmp.imageView.url = [NSURL URLWithString:homepageDressChilden.imageUrl];
                //menuItemViewTmp.imageView.mode = UIViewContentModeScaleToFill;
                [self.objMan manage:menuItemViewTmp.imageView];
                //[menuItemViewTmp manage];
                NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:homepageDressChilden.name, @"name",homepageDressChilden.ID, @"ID",menuItemViewTmp,@"view",homepageDressChilden.imageUrl,@"imageUrl",nil];
                
                [self.contentData addObject:data];
                [menuItemViewTmp release];
            }

        }
        else {
//            [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"对不起，没有数据请稍后再试！"] show]; 
        }
    }
    else {
//        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"申请数据失败请稍后再试！"] show]; 
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
    
//    // Register our mappings with the provider
//	RKObjectMapping* contentMapping = [AMHomepageDressCategoriesResult sharedObjectMapping];
//    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_INDUSTRY_CONTENTS usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMHomepageDressCategoriesResult class]];
            loader.objectMapping = [AMHomepageDressCategoriesResult sharedObjectMapping];
        }
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
}
@end


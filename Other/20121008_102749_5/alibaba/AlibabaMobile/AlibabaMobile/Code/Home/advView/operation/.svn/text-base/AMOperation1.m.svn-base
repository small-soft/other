//
//  AMOperation1.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-27.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

//
//  AliOperation1.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOperation1.h"
#import "AMContentRequest.h"
#import "AMHomepageDressRequest.h"
#import "AMHomepageDressEvent2Result.h"
#import "ConstDef.h"
#import "HJObjManager.h"
#import "UIHelp.h"
#import "AMHomeContent.h"
#import "AMHotRankViewController.h"
#import "HJManagedImageV.h"
@interface AMOperation1 ()
@property (nonatomic,retain) AMHomepageDressRequest *request;
@property (nonatomic,retain) HJManagedImageV *opertationView;
@property (nonatomic,retain) UIImageView *defaultImage;
@property (nonatomic,retain) HJObjManager *objMan;

@end
@implementation AMOperation1
@synthesize request=_request;
@synthesize delegate=_delegate;
@synthesize opertationView=_opertationView;
@synthesize objMan=_objMan;
@synthesize contentData=_contentData;
@synthesize defaultImage=_defaultImage;
@synthesize md5Checksum = _md5Checksum;

-(void)dealloc
{
    [_request release];
    [_delegate release];
    [_opertationView release];
    [_objMan release];
    [_contentData release];
    [_defaultImage release];
    [_md5Checksum release];
    [super dealloc];
}
-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc]init];
    }
    return _contentData;
}
-(HJObjManager*)objMan
{
    if (_objMan==nil) 
    {
        _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
        
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

-(HJManagedImageV*)opertationView
{
    if (!_opertationView) {
        _opertationView = [[HJManagedImageV alloc]init];
        _opertationView.backgroundColor = [UIColor clearColor];
    }
    return _opertationView;
}
-(AMHomepageDressRequest*)request
{
    if (!_request) {
        _request = [[AMHomepageDressRequest alloc]init];
        _request.industryId = @"fuzhuangfushi";
        _request.summary = @"";
        _request.configName = @"event2";
    }
    return _request;
}
-(UIImageView*)defaultImage
{
    if (!_defaultImage) {
        UIImage *image = [UIImage imageNamed:@"new.jpg"];
        _defaultImage = [[UIImageView alloc]initWithImage:image];
    }
    return _defaultImage;
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupViews];
    [self loadObjectsFromRemote];
}
-(void)setupViews
{
    self.defaultImage.frame = CGRectMake(0.0, 0.0, self.frame.size.width, self.frame.size.height);
    [self addSubview:self.defaultImage];
    self.opertationView.frame = CGRectMake(0.0, 0.0, self.frame.size.width, self.frame.size.height);
    [self addSubview:self.opertationView];
    
    
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
-(void)setParams:(AMHomepageDressEvent1 *)params
{
    self.opertationView.url = [NSURL URLWithString:params.imageUrl];
    self.opertationView.mode = UIViewContentModeScaleToFill;
    [self.objMan manage:self.opertationView];
}
-(void)resetData
{
    if ([self.contentData count] > 0) {
        AMHomepageDressEvent1 *homepageDressEvent1 = [self.contentData objectAtIndex:0];
        [self setParams:homepageDressEvent1];
    }
}
extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        
        gLastDisplayErrorTimeInterval = currentTime;
    }
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);   
    AMHomepageDressEvent2Result *result = (AMHomepageDressEvent2Result*)[objects objectAtIndex:0];
    
    if ([result.event2.type isEqualToString:@"event2"]) {
        self.md5Checksum = result.event2.md5Checksum;
        [self.contentData removeAllObjects];
        [self.contentData addObject:result.event2];
        [self resetData];
        
    }
    else {
        
    }
}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* contentMapping = [AMHomepageDressEvent2Result sharedObjectMapping];
    [objectManager.mappingProvider setMapping: contentMapping forKeyPath:@"data"];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_INDUSTRY_CONTENTS usingBlock:^(RKObjectLoader* loader) {
        // Change Method to POST
        loader.delegate = self;
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMHomepageDressEvent2Result class]];
        }
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
}

@end

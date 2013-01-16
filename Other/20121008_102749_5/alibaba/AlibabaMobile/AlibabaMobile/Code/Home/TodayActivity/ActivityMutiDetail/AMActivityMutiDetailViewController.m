//
//  AMActivityDetailViewController.m
//  AlibabaMobile
//
//  Created by alimobile on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMActivityMutiDetailViewController.h"

#import "AMActivityDetailCell.h"
#import "AMTodayActivityBlockBoxCell.h"
#import "AMTodayActivityBoxView.h"
#import "AliToastView.h"
#import "HJObjManager.h"


#define DATD_KEYWORD_TITLE  (@"title")
#define DATD_KEYWORD_IMAGE  (@"image")
#define DATD_KEYWORD_FOCUSIMAGE  (@"focusImage")
#define DATD_KEYWORD_SELECTOR  (@"selector")


@interface AMActivityMutiDetailViewController ()

@property (nonatomic,retain) NSArray *sourceData;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) AMSpecialPriceOfferRequest *specialPriceRequest;
@property (nonatomic, retain) NSMutableArray * objects;

@end

@implementation AMActivityMutiDetailViewController

@synthesize sourceData = _sourceData;
@synthesize objMan = _objMan;
@synthesize specialPriceRequest = _specialPriceRequest;
@synthesize objects = _objects;
@synthesize mTableView = _mTableView;

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/activityimgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	_objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

-(void) dealloc{
    
    [_mTableView release];
    [_sourceData release];
    [_objMan release];
    
    [super dealloc];
}

- (void)viewDidUnload
{
    [_sourceData release];
    _sourceData = nil;
    self.objMan = nil;
    self.mTableView = nil;
    [super viewDidUnload];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(NSArray*)sourceData
{
    if (!_sourceData) {
        _sourceData = [[NSArray alloc]initWithObjects:
                       [NSDictionary dictionaryWithObjectsAndKeys:@"097卡洛芙五角星欧美破洞仿弹力仿牛仔 薄款超级无敌好卖", @"subject",@"todayevent_1.jpg", @"eventProductImage",@"22.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"098【戈德堡正品折扣】衬衫HMHD3H221 两面穿纯棉男士休闲长袖衬衣", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"108.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"099【VIP批发】森马男士韩版修身直筒牛仔裤 男 牛仔裤批发308 310", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"153.00", @"leaveFactoryPriceAmount",@"条", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"100卡洛芙五角星欧美破洞仿弹力仿牛仔 薄款超级无敌好卖", @"subject",@"todayevent_1.jpg", @"eventProductImage",@"22.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"101【戈德堡正品折扣】衬衫HMHD3H221 两面穿纯棉男士休闲长袖衬衣", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"108.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"102【VIP批发】森马男士韩版修身直筒牛仔裤 男 牛仔裤批发308 310", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"153.00", @"leaveFactoryPriceAmount",@"条", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"103卡洛芙五角星欧美破洞仿弹力仿牛仔 薄款超级无敌好卖", @"subject",@"todayevent_1.jpg", @"eventProductImage",@"22.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"104【戈德堡正品折扣】衬衫HMHD3H221 两面穿纯棉男士休闲长袖衬衣", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"108.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"105【VIP批发】森马男士韩版修身直筒牛仔裤 男 牛仔裤批发308 310", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"153.00", @"leaveFactoryPriceAmount",@"条", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"106卡洛芙五角星欧美破洞仿弹力仿牛仔 薄款超级无敌好卖", @"subject",@"todayevent_1.jpg", @"eventProductImage",@"22.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"107【戈德堡正品折扣】衬衫HMHD3H221 两面穿纯棉男士休闲长袖衬衣", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"108.00", @"leaveFactoryPriceAmount",@"件", @"unit",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"108【VIP批发】森马男士韩版修身直筒牛仔裤 男 牛仔裤批发308 310", @"subject",@"todayevent_2.jpg", @"eventProductImage",@"153.00", @"leaveFactoryPriceAmount",@"条", @"unit",nil],
                       nil ];
        
    }
    return _sourceData;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self objManInit];
    
//    NSIndexPath *idxPath = [NSIndexPath indexPathForRow:5 inSection:0];
//    [self.mTableView scrollToRowAtIndexPath:idxPath 
//                          atScrollPosition:UITableViewScrollPositionMiddle 
//                                  animated:NO];
    
    [self.mTableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:3 inSection:0] animated:NO   
                          scrollPosition:UITableViewScrollPositionMiddle]; 
    
    
//    [self.navigationController setNavigationBarHidden:YES animated:NO];

}

- (void)viewWillAppear:(BOOL)animated{
    
//为了便于调试，navi暂时设置为可见
//    [self.navigationController setNavigationBarHidden:YES animated:NO];
//    [super viewWillAppear:animated];
    
//    NSIndexPath *idxPath = [NSIndexPath indexPathForRow:3 inSection:0];
//    [self.mTableView scrollToRowAtIndexPath:idxPath 
//                           atScrollPosition:UITableViewScrollPositionMiddle 
//                                   animated:NO];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{

//    return [self.sourceData count];
    
    int num= [self.sourceData count]/[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
    
    if ([self.sourceData count]%[AMTodayActivityBlockBoxCell cellBoxViewArrayCount]) {
        num++;
    }
    return num;
    
}

- (void) setLeaveFactoryAndUnitProperty:(NSString *)countValue unit:(NSString *)unitValue box:(AMTodayActivityBoxView *) boxValue{
    
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    boxValue.leaveFactoryPrice.text = [NSString stringWithFormat:@"%@/",countValue];
    
    CGSize labelSizeEnd = [unitValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    
    boxValue.unit.frame = CGRectMake(52+labelSize.width, 173, labelSizeEnd.width, labelSizeEnd.height);
    boxValue.unit.text = unitValue;
}


- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AMTodayActivityBlockBoxCell *cell = (AMTodayActivityBlockBoxCell *)[tableView dequeueReusableCellWithIdentifier: [AMTodayActivityBlockBoxCell cellIdentifer]];
    if (cell == nil)  
    {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMTodayActivityBlockBoxCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMTodayActivityBlockBoxCell class]])
                cell = (AMTodayActivityBlockBoxCell *)oneObject;
    }
    NSUInteger index = [indexPath row] *[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
    
    for (AMTodayActivityBoxView *box in cell.cellBoxViewArray) {
        if (index>=[self.sourceData count]) {
            break;
        }
        box.tag = index;
        NSDictionary *data = [self.sourceData objectAtIndex:index++]; 
        box.leaveFactoryImage.image = [UIImage imageNamed:[data objectForKey:@"eventProductImage"]];
        
        box.subject.text = [data objectForKey:@"subject"];
        [self setLeaveFactoryAndUnitProperty:[data objectForKey:@"leaveFactoryPriceAmount"] unit:[data objectForKey:@"unit"] box:box];

//        box.leaveFactoryPrice.text = [NSString stringWithFormat:@"%@/",[data objectForKey:@"leaveFactoryPriceAmount"]];
//        box.unit.text = [data objectForKey:@"unit"];
        [box addTarget:self action:@selector(boxUpAction:)  forControlEvents:UIControlEventTouchUpInside];    
//        [box addTarget:self action:@selector(boxDownAction:) forControlEvents:UIControlEventTouchDown];   
//        [box addTarget:self action:@selector(boxUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside]; 
    }
    return cell;
}

-(void)boxDownAction:(AMTodayActivityBoxView*)sender
{
    sender.leaveFactoryImageFocusIcon.frame = CGRectMake(0,10, 130,190);
    sender.leaveFactoryImageFocusIcon.image = [UIImage imageNamed:@"App_icon_press"]; 
    
}
-(void)boxUpAction:(AMTodayActivityBoxView*)sender
{
    NSDictionary *data = [self.sourceData objectAtIndex:sender.tag]; 
//    [self performSelector:NSSelectorFromString([data objectForKey:DATD_KEYWORD_SELECTOR])]
    
    NSString *leaveFactoryPriceAmount2 = [data objectForKey:@"leaveFactoryPriceAmount"];
    NSString *toastContent = [NSString stringWithFormat:@"您点击了出厂价为%@的Item",leaveFactoryPriceAmount2];
    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:toastContent] show];
    
    sender.leaveFactoryImageFocusIcon.image = nil; 

    
}

-(void)boxUpOutsideAction:(AMTodayActivityBoxView*)sender
{
    sender.leaveFactoryImageFocusIcon.image = nil; 
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    return [AMTodayActivityBlockBoxCell cellHeight];
}


-(void)loadRequest
{
    isLoading = YES;
    self.specialPriceRequest = [[AMSpecialPriceOfferRequest alloc] init];
    [self loadObjectsFromRemote];
    
} 

- (void)loadObjectsFromRemote {
    
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMSpecialPriceOfferResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SPECIAL_PRICE_OFFER_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMSpecialPriceOfferResult  class]];
             loader.objectMapping = [AMSpecialPriceOfferResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.specialPriceRequest;
    }];
    [super loadObjectsFromRemote];
    
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
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


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {  
    
    id object = [objects objectAtIndex:0];
    if(object != nil){
        
        AMSpecialPriceOfferResult * specialPriceOffer = object;
        NSArray * array = specialPriceOffer.resultList;
        
        
        [self performSelectorOnMainThread:@selector(setTableDate:) withObject:array waitUntilDone:YES];
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
    isLoading = NO;
    [super objectLoader:objectLoader didLoadObjects:objects];
}

- (void) setTableDate:(NSMutableArray *)date
{
    
    [self.objects addObjectsFromArray:date];
    [self.mTableView reloadData];
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
}



@end

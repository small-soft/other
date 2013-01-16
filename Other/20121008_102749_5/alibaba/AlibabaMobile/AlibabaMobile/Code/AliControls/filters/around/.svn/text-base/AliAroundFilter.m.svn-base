//
//  AliAroundFilter.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliAroundFilter.h"
#import "AliTableViewCellCategory.h"
#import "AMGeoGraphicInfoRequest.h"
#import "ConstDef.h"
#import "AMGeographicResult.h"
@interface AliAroundFilter ()

@property (retain,nonatomic)CLLocationManager *locationManager;
@property (retain,nonatomic)CLLocation *startingPoint;
@property (nonatomic)BOOL isLoading;
@property (nonatomic,retain)NSMutableArray*regionData;
@property (nonatomic,retain)UIView*headerView;
@property (nonatomic, retain) AMGeoGraphicInfoRequest *geoRequset;
@end

@implementation AliAroundFilter
@synthesize locationManager=_locationManager;
@synthesize isLoading=_isLoading;
@synthesize startingPoint=_startingPoint;
@synthesize delegate=_delegate;
@synthesize contentTable = _contentTable;
@synthesize resultView = _resultView;
@synthesize resultPreTitle = _resultPreTitle;
@synthesize resultTitle = _resultTitle;
@synthesize selectedItem=_selectedItem;
@synthesize regionData=_regionData;
@synthesize parentTitle=_parentTitle;
@synthesize headerView=_headerView;
@synthesize geoRequset=_geoRequset;

-(void)dealloc
{
    [_locationManager release];
    [_startingPoint release];
    [_delegate release];
    [_contentTable release];
    [_regionData release];
    [_parentTitle release];
    [_headerView release];
    [_resultView release];
    [_resultPreTitle release];
    [_resultTitle release];
    [_geoRequset release];
    [super dealloc];
}
-(AMGeoGraphicInfoRequest*)geoRequset
{
    if (!_geoRequset) {
        _geoRequset = [[AMGeoGraphicInfoRequest alloc]init];
    }
    return _geoRequset;
}
-(CLLocationManager*)locationManager
{
    if (_locationManager==nil) {
        _locationManager =[[CLLocationManager alloc]init];
        _locationManager.delegate=self;
        _locationManager.desiredAccuracy=kCLLocationAccuracyBest;
        _locationManager.distanceFilter = 1000.0;  
        
    }
    return _locationManager;
    
}
-(NSMutableArray*)regionData
{
    if (!_regionData) {
        _regionData = [[NSArray arrayWithObjects:
                        [NSDictionary dictionaryWithObjectsAndKeys:@"不限距离", @"title",nil],
                        [NSDictionary dictionaryWithObjectsAndKeys:@"20Km以内", @"title",@"20",@"value",nil],
                        [NSDictionary dictionaryWithObjectsAndKeys:@"50Km以内", @"title",@"50",@"value",nil],
                        [NSDictionary dictionaryWithObjectsAndKeys:@"100Km以内", @"title",@"100",@"value",nil],
                        [NSDictionary dictionaryWithObjectsAndKeys:@"300Km以内", @"title",@"300",@"value",nil],
                        nil] retain];
    }
    return _regionData;
}
-(UIView*)headerView
{
    if (!_headerView) {
        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 20.0)];
        _headerView.backgroundColor = RGB(0xF0,0xf0,0xf0);
         UIImageView *bg = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"bg_subtitle"]];
        bg.frame = CGRectMake(0.0, 0.0, 320.0, 20.0);
        [_headerView addSubview:bg];
        [bg release];
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(10.0, 0.0, 310.0, 20.0)];
        label.backgroundColor = [UIColor clearColor];
        label.text = @"筛选范围：";
        label.textColor = RGB(0x66,0x66,0x66);
        label.highlightedTextColor = RGB(0x66,0x66,0x66);
        label.font = [UIFont systemFontOfSize:14.0];
       

        [_headerView addSubview:label];
        [label release];
    }
    return _headerView;
}
-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;    
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"周边";
}

-(void)updataLocation
{
    self.isLoading=YES;
    [self.locationManager startUpdatingLocation];
}
-(void)setupResultView
{
    self.resultView.backgroundColor =  RGB(0xF0,0xf0,0xf0);
    self.resultPreTitle.fontSize = 14.0;
    self.resultPreTitle.r = 0x66;
    self.resultPreTitle.g = 0x66;
    self.resultPreTitle.b = 0x66;
    self.resultPreTitle.verticalAlignment = VerticalAlignmentTop;
    [self.resultPreTitle setupView];
    
    self.resultPreTitle.text=@"您的当前位置：";
    CGSize labelSize = [self.resultPreTitle.text sizeWithFont:self.resultPreTitle.font];
    self.resultPreTitle.frame = CGRectMake(10.0, 15.0 , labelSize.width, self.resultPreTitle.fontSize);
    
    
    self.resultTitle.fontSize = 14.0;
    self.resultTitle.r = 0x33;
    self.resultTitle.g = 0x33;
    self.resultTitle.b = 0x33;
   self.resultTitle.numberOfLines = 2;
    self.resultTitle.verticalAlignment = VerticalAlignmentTop;
    [self.resultTitle setupView];
 
    
    self.resultTitle.text = @"正在获取...\n   ";
    self.resultTitle.frame = CGRectMake(self.resultPreTitle.frame.origin.x+self.resultPreTitle.frame.size.width, 15.0 , (320.0 -15.0)-self.resultPreTitle.frame.origin.x-self.resultPreTitle.frame.size.width, self.resultTitle.fontSize*2+4);
    
    self.resultView.frame = CGRectMake(0.0, 0.0,320.0,self.resultTitle.frame.size.height+30.0);
    self.contentTable.frame = CGRectMake(0.0, self.resultView.frame.size.height,320.0,480.0-self.resultView.frame.size.height);

}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    /*!
     Map to a target object class -- just as you would for a non-persistent class. The entity is resolved
     for you using the Active Record pattern where the class name corresponds to the entity name within Core Data.
     */
//    RKObjectMapping* categoryMapping = [AMGeographicResult sharedObjectMapping];
//
//    
//    // Register our mappings with the provider
//    [objectManager.mappingProvider addObjectMapping: categoryMapping];
//    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_GEO usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMGeographicResult class]];
            loader.objectMapping = [AMGeographicResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.geoRequset;
    }];
    [super loadObjectsFromRemote];
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupResultView];
    [self updataLocation];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [self setContentTable:nil];
    [self setResultView:nil];
    [self setResultPreTitle:nil];
    [self setResultTitle:nil];
    [_regionData release];
    _regionData = nil;
    [_geoRequset release];
    _geoRequset = nil;
    self.locationManager = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

-(void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    self.isLoading=NO;
   
    self.startingPoint = newLocation;
    [manager stopUpdatingLocation];

    self.geoRequset.latitude = [NSString stringWithFormat:@"%f", newLocation.coordinate.latitude];
    
    self.geoRequset.longitude = [NSString stringWithFormat:@"%f" , newLocation.coordinate.longitude];
    
    [self loadObjectsFromRemote];
  
}
-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    if (!self.isLoading) 
    {
        return;
    }
    if ( [error code] == kCLErrorDenied ) {  
        [manager stopUpdatingHeading];  
    } else if ([error code] == kCLErrorHeadingFailure) {  
        
    }  
    self.isLoading=NO;
    self.resultTitle.text=@"无法获取位置信息\n   ";
}
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 20.0;
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellCategory cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    
    return [self.regionData count];
}
- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    return self.headerView;
}
- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];
        
    }
    
    
    NSUInteger row = [indexPath row];
    NSDictionary *data = [self.regionData objectAtIndex:row]; 
    cell.title.text = [data valueForKey:@"title"];
    if (row==self.selectedItem)
    {
        cell.identifyImage.image = [UIImage imageNamed:@"icon_list_Checkmark"]; 
    }
    else {
        cell.identifyImage.image = nil;
    }
    return cell;
}
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if ([self.delegate respondsToSelector:@selector(AliAroundFilter:distance:selectedItem:)]) 
    {
        NSUInteger row = [indexPath row];
        NSDictionary *data = [self.regionData objectAtIndex:row]; 
        [self.delegate AliAroundFilter:self.startingPoint distance:[data valueForKey:@"value"] selectedItem:row];
    }
    [self.navigationController popViewControllerAnimated:YES];
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	
    if ([objects count]>0) {
        AMGeographicResult *data = (AMGeographicResult *)[objects objectAtIndex:0];
        NSString *text = [NSString stringWithFormat:@"%@ %@%@%@%@",data.province,data.city,data.town, data.street,data.location];
        
        CGSize labelSize = [text sizeWithFont:self.resultTitle.font];
        if (labelSize.width<self.resultTitle.frame.size.width) {
            self.resultTitle.text = [text stringByAppendingString:@"\n  "];
        }
        else {
            self.resultTitle.text = text;
        }

    }
    [super objectLoader:objectLoader didLoadObjects:objects];
 
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline) {
//        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        self.isLoading=NO;
        self.resultTitle.text=@"无法获取位置信息\n   ";
    }
}
@end

//
//  AliRegionFilter.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliRegionFilter.h"
#import "AMHotAreaRequest.h"
#import "AMHotAreaResult.h"
#import "ConstDef.h"
#import "AliTableViewCellCategory.h"
#import "AMHotArea.h"
@interface AliRegionFilter ()
@property (retain,nonatomic) AMHotAreaRequest*request;
@property (retain,nonatomic) AMHotAreaResult*result;
@property (nonatomic)int segmentSelected;

@property (nonatomic, readonly) NSArray* segmentTitle;

@property (nonatomic) BOOL isLoading;
@property (nonatomic) BOOL isReseting;
@end

@implementation AliRegionFilter
@synthesize contentTable=_contentTable;
@synthesize segmentTitle=_segmentTitle;
@synthesize segmentSelected=_segmentSelected;
@synthesize request=_request;
@synthesize isLoading=_isLoading;
@synthesize result=_result;
@synthesize isReseting=_isReseting;
@synthesize selectedItem=_selectedItem;
@synthesize parentTitle=_parentTitle;
@synthesize delegate=_delegate;
@synthesize lastSegmentSelected=_lastSegmentSelected;
- (void)dealloc {
    [_contentTable release];
    [_segmentTitle release];
    [_result release];
    [_request release];
    [_parentTitle release];
    [_delegate release];
    [super dealloc];
}

-(AMHotAreaRequest*)request
{
    if (!_request) {
        _request = [[AMHotAreaRequest alloc]init];
    }
    return _request;
}

-(NSArray*)segmentTitle
{
    if (!_segmentTitle) {
        _segmentTitle = [[NSArray alloc]initWithObjects:@"地区",@"省份",@"城市",nil];
    }
    return _segmentTitle;
}

-(NSArray*)commonTableViewSegmentTitle
{
    return self.segmentTitle;
}
-(void)setSegmentSelected:(int)segmentSelected
{
    _segmentSelected = segmentSelected;
    [self.contentTable reloadData];
}

- (void) segmentValueChanged:(int)nowIndex
{
    self.segmentSelected = nowIndex;
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;    
}

-(NSString*)commonTableViewNavigationTitle
{
    return @"地区选择";
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.segmentSelected = self.lastSegmentSelected;
    [self changeSegmentIndex:(int)self.lastSegmentSelected];
    [self loadObjectsFromRemote];
}

- (void)viewDidUnload
{
    [self setContentTable:nil];
    [_segmentTitle release];
    _segmentTitle = nil;
    [_result release];
    _result = nil;
    [_request release];
    _request = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}
- (void)loadObjectsFromRemote {
  self.isLoading = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* offerResultMapping = [AMHotAreaResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: offerResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_HOT_AREA usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMHotAreaResult class]];
            loader.objectMapping = [AMHotAreaResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
    [super loadObjectsFromRemote];
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	
    self.result = (AMHotAreaResult*)[objects objectAtIndex:0];
    [self.contentTable reloadData];
    [super objectLoader:objectLoader didLoadObjects:objects];
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellCategory cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    if (self.result==nil||self.isReseting) {
        return 0;
    }
    if (self.segmentSelected==0) {
        return [self.result.hotAreaList count]+1;
    }
    else if(self.segmentSelected==1)
    {
        return [self.result.hotProvinceList count]+1;
    }
    else
    {
        return [self.result.hotCityList count]+1;
    }
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];
        
    }
    
    
    NSUInteger row = [indexPath row];
    if (row==0) {
        cell.title.text = @"所有地区";
    }
    else
    {
        if (self.segmentSelected==0) {
            
            AMHotArea * data = [self.result.hotAreaList objectAtIndex:row-1];
            cell.title.text = data.showTitle;
            
        }
        else if(self.segmentSelected==1)
        {
            AMHotArea * data = [self.result.hotProvinceList objectAtIndex:row-1];
            cell.title.text = data.showTitle;
        }
        else
        {
            AMHotArea * data = [self.result.hotCityList objectAtIndex:row-1];
            cell.title.text = data.showTitle;
        }
        
    }
    if ((self.segmentSelected==self.lastSegmentSelected&&row==self.selectedItem)||(self.selectedItem == 0&&row == 0))
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
    
      if ([self.delegate respondsToSelector:@selector(AliRegionFilter:segment:selectedItem:)]) 
      {
          NSUInteger row = [indexPath row];
          AMHotArea * data =nil;
          if (row==0) {
          }
          else {
              if (self.segmentSelected==0) {
                  data = [self.result.hotAreaList objectAtIndex:row-1];
              }
              else if(self.segmentSelected==1)
              {
                  data = [self.result.hotProvinceList objectAtIndex:row-1];   
              }
              else
              {
                  data = [self.result.hotCityList objectAtIndex:row-1];
                  
              }      
          }
          [self.delegate AliRegionFilter:data segment:self.segmentSelected selectedItem:row];
    }
    [self.navigationController popViewControllerAnimated:YES]; 
    
   
    
}
@end

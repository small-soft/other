//
//  AMMarketpriceViewController.m
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMMarketpriceViewController.h"
#import "AMPriceCategoriesRequest.h"
#import "AMPriceCategory.h"
#import "ConstDef.h"
#import "AMMarketPriceSubCategoryViewController.h"
#import "AliTableViewCellCategory.h"
@interface AMMarketpriceViewController()
@property (nonatomic, retain) NSMutableArray* categoriesData;
@property (nonatomic,retain)AMPriceCategoriesRequest *categoriesRequset;
- (void)loadObjectsFromRemote ;
@end

@implementation AMMarketpriceViewController

#pragma synthesize start
@synthesize contentTable=_contentTable;
@synthesize categoriesRequset = _categoriesRequset;
@synthesize categoriesData=_categoriesData;
@synthesize parentTitle=_parentTitle;
-(AMPriceCategoriesRequest*)categoriesRequset
{
    if (_categoriesRequset==nil) {
        _categoriesRequset = [[AMPriceCategoriesRequest alloc] init];
    }
    return _categoriesRequset;
}

-(NSMutableArray*)categoriesData
{
    
    if (_categoriesData==nil) {
        _categoriesData = [[NSMutableArray alloc] init];
    }
    return _categoriesData;
}
#pragma synthesize end



- (void)dealloc {
    [_categoriesRequset release];
    [_contentTable release];
    [_categoriesData release];
    [_parentTitle release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setContentTable:nil];
    [_categoriesRequset release];
    _categoriesRequset=nil;
    [_categoriesData release];
    _categoriesData =nil;
    [super viewDidUnload];
}
-(void) viewDidLoad
{
    [super viewDidLoad];
}
-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if ([[self categoriesData ] count] <= 0) {
        [self loadObjectsFromRemote];
    }
}
-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"价格类目";
}
- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* categoryMapping = [AMPriceCategory sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: categoryMapping];
    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRICE_CATEGORIES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPriceCategory class]];
            loader.objectMapping = [AMPriceCategory sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.categoriesRequset;
    }];
    [super loadObjectsFromRemote];
}
#pragma mark RKObjectLoaderDelegate methods



- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {

   	[self.categoriesData addObjectsFromArray:objects];
    
	[self.contentTable reloadData] ;
    [super objectLoader:objectLoader didLoadObjects:objects];

}


#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    return [AliTableViewCellCategory cellHeight];
}

- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    return [self.categoriesData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];
    }

    NSUInteger row = [indexPath row];
    cell.title.text = [[self.categoriesData objectAtIndex:row] name];
    
    return cell;
}
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
     [AMLogUtils appendLog: APP_PRICE_PAGE_THREE]; 
    NSUInteger row = [indexPath row];
    AMPriceCategory *data = (AMPriceCategory*)[self.categoriesData objectAtIndex:row];
    
    AMMarketPriceSubCategoryViewController *second = [[AMMarketPriceSubCategoryViewController alloc] initWithNibName:@"AMMarketPriceSubCategoryViewController" bundle:nil];
    
    second.categoryId=[NSNumber numberWithInt:[data.identifier intValue]];
    second.navigationTitle = data.name;
    second.parentTitle = [self commonTableViewNavigationTitle];
    second.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:second animated:YES];
    [second release];
     [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
}




@end

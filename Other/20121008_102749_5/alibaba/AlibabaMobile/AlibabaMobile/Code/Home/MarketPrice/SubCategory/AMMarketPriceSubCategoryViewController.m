//
//  AMMarketPriceSubCategoryViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMarketPriceSubCategoryViewController.h"
#import "AMPriceSubCategoryRequest.h"
#import "AMSearchPriceViewController.h"
#import "AMPriceCategory.h"
#import "ConstDef.h"
#import "AliTableViewCellCategory.h"
@interface AMMarketPriceSubCategoryViewController()

@property (nonatomic,retain) AMPriceSubCategoryRequest *categoriesRequset;
@property (nonatomic, retain) NSMutableArray* categoryData;

- (void)loadCategoryDataFromRemote;
@end


  
@implementation AMMarketPriceSubCategoryViewController

#pragma synthesize start
@synthesize contentTable=_contentTable;
@synthesize categoriesRequset=_categoriesRequset;
@synthesize categoryId=_categoryId;
@synthesize navigationTitle=_navigationTitle;
@synthesize categoryData=_categoryData;
@synthesize parentTitle=_parentTitle;

-(AMPriceSubCategoryRequest*)categoriesRequset
{
    if (_categoriesRequset==nil) {
        _categoriesRequset=[[AMPriceSubCategoryRequest alloc] init];
        _categoriesRequset.categoryId =self.categoryId;
    }
    return _categoriesRequset;
}
-(NSMutableArray*)categoryData
{
    
    if (_categoryData==nil) {
        _categoryData = [[NSMutableArray alloc] init];
    }
    return _categoryData;
}
#pragma synthesize end


- (void)dealloc {
    [_contentTable release];
    [_categoriesRequset release];
    [_categoryId release];
    [_navigationTitle release];
    [_categoryData release];
    [_parentTitle release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setContentTable:nil];
    [_categoriesRequset release];
    _categoriesRequset = nil;
    [_categoryData release];
    _categoryData = nil;
    /*
     self.categoryId = nil;
     _navigationTitle=nil;
    _parentTitle = nil;
     */
    
    [super viewDidUnload];
}
-(void)viewDidLoad
{
    [super viewDidLoad];
}
-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if ([[self categoryData ] count] <= 0) {
        [self loadCategoryDataFromRemote];
    }
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return self.navigationTitle;
}
- (void)loadCategoryDataFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* categoryMapping = [AMPriceCategory sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: categoryMapping];
    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_PRICE_SUB_CATEGORIES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMPriceCategory class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.categoriesRequset;
    }];
    [super loadObjectsFromRemote];
}

#pragma mark RKObjectLoaderDelegate methods


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {

    [self.categoryData addObjectsFromArray:objects]; 
	[self.contentTable reloadData] ;
    [super objectLoader:objectLoader didLoadObjects: objects];
}


#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    return [AliTableViewCellCategory cellHeight];
}


- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
   return [self.categoryData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];
    }
    NSUInteger row = [indexPath row];
 
    cell.title.text = [[self.categoryData objectAtIndex:row] name];
    
    return cell;
}

#pragma mark -
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger row = [indexPath row];
    AMPriceCategory *data = (AMPriceCategory*)[self.categoryData objectAtIndex:row];

    
    if (data.leaf) {
        [AMLogUtils appendLog: APP_PRICE_PAGE_FOUR]; 
        
        
        AMSearchPriceViewController *controller = [[AMSearchPriceViewController alloc] initWithNibName:@"AMSearchPriceViewController" bundle:nil];
        
        NSNumberFormatter * f = [[NSNumberFormatter alloc] init];
        [f setNumberStyle:NSNumberFormatterDecimalStyle];
        
        controller.catId = [f numberFromString:data.identifier];
        
        controller.catName = data.name;
        controller.parentTitle = self.navigationTitle;
        
        [f release];
        controller.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:controller animated:YES];
        [controller release];
        [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];

    }
    else {
        [AMLogUtils appendLog: APP_PRICE_PAGE_THREE]; 

        
        AMMarketPriceSubCategoryViewController *second = [[AMMarketPriceSubCategoryViewController alloc] initWithNibName:@"AMMarketPriceSubCategoryViewController" bundle:nil];
        
        second.categoryId=[NSNumber numberWithInt:[data.identifier intValue]];
        second.navigationTitle = data.name;
        second.parentTitle = self.navigationTitle;
        second.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:second animated:YES];
        [second release];
        [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];

    }
     
}
@end

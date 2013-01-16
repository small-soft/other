//
//  AMSubCategoryViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubCategoryViewController.h"
#import "AMOfferListViewController.h"
#import "AMCategorySub.h"
#import "ConstDef.h"
#import "AMCategorySubRequest.h"
#import "AliTableViewCellCategory.h"
@interface AMSubCategoryViewController()
@property (nonatomic, retain) AMCategorySubRequest *categoriesRequset;
@property (nonatomic, retain) NSMutableArray* categoriesData;
- (void)loadObjectsFromRemote ;
@end


@implementation AMSubCategoryViewController

#pragma synthesize start
@synthesize contentTable=_contentTable;
@synthesize categoryId=_categoryId;
@synthesize navigationTitle=_navigationTitle;
@synthesize parentTitle=_parentTitle;
@synthesize categoriesRequset=_categoriesRequset;
@synthesize categoriesData=_categoriesData;



-(AMCategorySubRequest*)categoriesRequset
{
    if (_categoriesRequset==nil) {
        _categoriesRequset = [[AMCategorySubRequest alloc] init];

    }
    _categoriesRequset.categoryId =self.categoryId;
    NSLog(@"AMCategorySubRequest %@",_categoriesRequset.categoryId);
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
    [_contentTable release];
    [_categoryId release];
    [_navigationTitle release];
    [_parentTitle release];
    [_categoriesRequset release];
    [_categoriesData release];
    
    [super dealloc];
}
- (void)viewDidUnload {
    [self setContentTable:nil];
    //_categoryId = nil;
    //_navigationTitle=nil;
    //_parentTitle =nil;
    [_categoriesRequset release];
    _categoriesRequset = nil;
    [_categoriesData release];
    _categoriesData =nil;
    [super viewDidUnload];
}
-(void)viewDidLoad
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
    return self.navigationTitle;

}


- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    /*!
     Map to a target object class -- just as you would for a non-persistent class. The entity is resolved
     for you using the Active Record pattern where the class name corresponds to the entity name within Core Data.
     */
    RKObjectMapping* categoryMapping = [RKObjectMapping mappingForClass:[AMCategorySub class]];
    [categoryMapping mapKeyPath:@"id" toAttribute:@"identifier"];
    [categoryMapping mapKeyPath:@"name" toAttribute:@"name"];
    [categoryMapping mapKeyPath:@"leaf" toAttribute:@"leaf"];
    
    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: categoryMapping];
    
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CATEGORIES_SUB usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCategorySub class]];
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
      return [self.categoriesData count]+1;
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
        cell.title.text = [NSString stringWithFormat:@"所有%@",self.navigationTitle];
    }
    else
    {
        cell.title.text = [[self.categoriesData objectAtIndex:row-1] name];
    }
    
    return cell;
}

#pragma mark -
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger row = [indexPath row];
    
    if (row==0) {
        [AMLogUtils appendLog: APP_CATEGORY_BROWSER_THREE]; 
        AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
        
        controller.catId = self.categoryId;
        controller.catName = self.navigationTitle;
        controller.parentTitle = self.parentTitle;
        
        controller.parentTitle = self.navigationTitle;
        controller.parentCatId=self.categoryId;
        controller.categoryFilterSelectedItem = row;
        
        controller.hidesBottomBarWhenPushed=NO;
        [self.navigationController pushViewController:controller animated:YES];
        [controller release];

    }
    else
    {
        AMCategorySub *data = (AMCategorySub*)[self.categoriesData objectAtIndex:row-1];
        if (data.leaf) {
         [AMLogUtils appendLog: APP_CATEGORY_BROWSER_FOUR]; 
                       
            AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
            controller.catId = data.identifier;
            controller.catName = data.name;
            controller.parentTitle = self.navigationTitle;
            controller.parentCatId=self.categoryId;
            controller.categoryFilterSelectedItem = row;
            controller.hidesBottomBarWhenPushed=YES;
            [self.navigationController pushViewController:controller animated:YES];
            [controller release];
        }
        else
        {
            [AMLogUtils appendLog: APP_CATEGORY_BROWSER_TWO]; 
            AMSubCategoryViewController *sub = [[AMSubCategoryViewController alloc] initWithNibName:@"AMSubCategoryViewController" bundle:nil];
            sub.categoryId=data.identifier;
            sub.navigationTitle = data.name;
            sub.parentTitle = self.navigationItem.title;
            sub.hidesBottomBarWhenPushed=YES;
            [self.navigationController pushViewController:sub animated:YES];
            [sub release];
        }
    }
     [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
}

@end

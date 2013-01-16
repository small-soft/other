//
//  AMCategoryViewController.m
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMCategoryViewController.h"
#import "AMCategory.h"
#import "ConstDef.h"
#import "AMSubCategoryViewController.h"
#import "AMCategoryRequest.h"
#import "AliTableViewCellCategory.h"
@interface AMCategoryViewController()
@property (nonatomic, retain) AMCategoryRequest *categoriesRequset;
@property (nonatomic, retain) NSMutableArray* categoriesData;
- (void)loadObjectsFromRemote ;
@end

@implementation AMCategoryViewController

#pragma synthesize start
@synthesize contentTable=_contentTable;
@synthesize categoriesRequset=_categoriesRequset;
@synthesize categoriesData=_categoriesData;
@synthesize parentTitle=_parentTitle;

-(AMCategoryRequest*)categoriesRequset
{
    if (_categoriesRequset==nil) {
        _categoriesRequset = [[AMCategoryRequest alloc] init];
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
    [_contentTable release];
    [_categoriesRequset release];
    [_categoriesData release];
    [_parentTitle release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setContentTable:nil];
    [_categoriesRequset release];
    _categoriesRequset = nil;
    [_categoriesData release];
    _categoriesData = nil;
    //_parentTitle = nil;
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
    return @"类目浏览";
}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: [AMCategory sharedObjectMapping]];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CATEGORIES usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCategory class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.categoriesRequset;
    }];
    [super loadObjectsFromRemote];
}



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

#pragma mark -
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    [AMLogUtils appendLog: APP_CATEGORY_BROWSER_TWO]; 
    NSUInteger row = [indexPath row];
    AMCategory *data = (AMCategory*)[self.categoriesData objectAtIndex:row];
    AMSubCategoryViewController *sub = [[AMSubCategoryViewController alloc] initWithNibName:@"AMSubCategoryViewController" bundle:nil];

    sub.categoryId=data.identifier;
    sub.navigationTitle = data.name;
    sub.parentTitle = self.navigationItem.title;
    sub.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:sub animated:YES];
    [sub release];
    [self.contentTable deselectRowAtIndexPath:indexPath animated:NO];
}
@end

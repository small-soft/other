//
//  AliCategoryFilter.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCategoryFilter.h"
#import "AMSmartNavigationRequest.h"
#import "AMCategorySubRequest.h"
#import "AMSmartNavigationResult.h"
#import "AliTableViewCellCategory.h"
#import "AMOfferListViewController.h"
#import "ConstDef.h"
#import "AMCategorySub.h"
@interface AliCategoryFilter ()

@property (nonatomic, retain) AMSmartNavigationRequest *requset;
@property (nonatomic, retain) AMCategorySubRequest *categoriesRequset;
@property (nonatomic, retain) NSMutableArray* resultData;
@property (nonatomic) BOOL isLoading;
@end

@implementation AliCategoryFilter
@synthesize parentTitle=_parentTitle;
@synthesize contentTable=_contentTable;
@synthesize resultData=_resultData;
@synthesize requset=_requset;
@synthesize isLoading = _isLoading;
@synthesize keyWords=_keyWords;
@synthesize catId=_catId;
@synthesize catName=_catName;
@synthesize selectedItem=_selectedItem;
@synthesize categoriesRequset=_categoriesRequset;
@synthesize delegate=_delegate;
- (void)dealloc {
    [_contentTable release];
    [_resultData release];
    [_requset release];
    [_parentTitle release];
    [_keyWords release];
    [_catName release];
    [_catId release];
    [_delegate release];
    [_categoriesRequset release];
    [super dealloc];
}
-(AMCategorySubRequest*)categoriesRequset
{
    if (_categoriesRequset==nil) {
        _categoriesRequset = [[AMCategorySubRequest alloc] init];
        
    }
    _categoriesRequset.categoryId =self.catId;
    return _categoriesRequset;
}


-(AMSmartNavigationRequest*)requset
{
    if (_requset==nil) {
        _requset = [[AMSmartNavigationRequest alloc] init];
        
    }
    _requset.keywords =self.keyWords;
   
    return _requset;
}

-(NSMutableArray*)resultData
{
    
    if (_resultData==nil) {
        _resultData = [[NSMutableArray alloc] init];
    }
    return _resultData;
}
-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;    
}

-(NSString*)commonTableViewNavigationTitle
{
    return @"类目选择";
}
- (void)loadObjectsFromRemoteByKeywords {
    self.isLoading = YES;
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
//    // Register our mappings with the provider
//	RKObjectMapping* offerResultMapping = [AMSmartNavigationResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: offerResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_NAVIGATION usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMSmartNavigationResult class]];
            loader.objectMapping = [AMSmartNavigationResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.requset;
    }];
    [super loadObjectsFromRemote];
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


- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    if (self.keyWords) {
        [self loadObjectsFromRemoteByKeywords];
    }
    else {
        [self loadObjectsFromRemote];
    }
    
}

- (void)viewDidUnload
{
    [_requset release];
    _requset = nil;
    [_categoriesRequset release];
    _categoriesRequset = nil;
    [_resultData release];
    _resultData = nil;
    [self setContentTable:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}



- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);  
    if (self.keyWords) {
        AMSmartNavigationResult *result =(AMSmartNavigationResult*)[objects objectAtIndex:0];
        [self.resultData addObjectsFromArray:result.categories];
    }
    else {
        [self.resultData addObjectsFromArray:objects]; 
    }
    [self.contentTable reloadData];
    [super objectLoader:objectLoader didLoadObjects: objects];
}



#pragma mark UITableViewDataSource methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellCategory cellHeight];
}
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section {
    
    return [self.resultData count] +1 ;
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
        cell.title.text = @"所有类目";
        if (self.catName) {
            cell.title.text = [NSString stringWithFormat:@"所有%@",self.catName];;
        }
        
    }
    else
    {
        cell.title.text = [[self.resultData objectAtIndex:row-1] name];
    }
    if (row==self.selectedItem) {
        cell.identifyImage.image = [UIImage imageNamed:@"icon_list_Checkmark"]; 
    }
    else {
        cell.identifyImage.image = nil;
    }
    
    return cell;
}
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if ([self.delegate respondsToSelector:@selector(AliCategoryFilter:catName:selectedItem:)]) 
    {
        NSUInteger row = [indexPath row];
        if (row==0) {
            [self.delegate AliCategoryFilter:_catId catName:nil selectedItem:0];
        }
        else {
             AMCategorySub *data = [self.resultData objectAtIndex:row-1] ;
            [self.delegate AliCategoryFilter:data.identifier catName:data.name selectedItem:row];
        }

    }
    [self.navigationController popViewControllerAnimated:YES];
}
@end

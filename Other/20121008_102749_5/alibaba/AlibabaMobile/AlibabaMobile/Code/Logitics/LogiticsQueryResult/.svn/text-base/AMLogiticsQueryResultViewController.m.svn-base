//
//  AMLogiticsQueryResultViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMLogiticsQueryResultViewController.h"
#import "AMLogisTraceStep.h"
#import "AMLogisSimpleOrder.h"
#import "ConstDef.h"
#import "AMLogiticsData.h"
#import "AMExpressDetailGroup.h"
#import "AMLogisticsQueryRequest.h"
#import "AMExpressDetailTitle.h"
#import "AliToastView.h"
#import "AliTitleCellView.h"
#import "StringUtils.h"
#import "AliTableViewCellSubTitle.h"
#import "AliToastView.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AMLogiticsQueryResultViewController() 
@property (readonly,nonatomic) AMExpressDetailGroup    * groupName;
@property (readonly,nonatomic) AMExpressDetailGroup    * groupNumber;
@property (readonly,nonatomic) AMExpressDetailGroup    * groupState;
@property (readonly,nonatomic) AMLogisticsQueryRequest * queryRequest;
@property (readonly,nonatomic) AMLogisticsQueryRequest * queryByLogisticsRequest;

@property (nonatomic, retain) NSMutableArray* resultData;
@end


@implementation AMLogiticsQueryResultViewController
@synthesize contentGroupTable=_contentGroupTable;
@synthesize contenDetailTable=_contenDetailTable;
@synthesize groupName=_groupName;
@synthesize groupNumber = _groupNumber;
@synthesize groupState = _groupState;
@synthesize company=_company;
@synthesize number=_number;
@synthesize logisticsID = _logisticsID;
@synthesize queryRequest=_queryRequest;
@synthesize queryByLogisticsRequest = _queryByLogisticsRequest;
@synthesize resultData=_resultData;
@synthesize  noInfoView = _noInfoView;
@synthesize parentTitle=_parentTitle;
-(AMExpressDetailGroup*)groupName
{
    if (_groupName==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMExpressDetailGroup" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMExpressDetailGroup class]])
                _groupName = (AMExpressDetailGroup *)oneObject;
        }
    
    _groupName.contentTitle.text=@"物流公司：";
    _groupName.contentValue.text = self.company.name;
    
    return _groupName;
}
-(AMExpressDetailGroup*)groupNumber
{
    if (_groupNumber==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMExpressDetailGroup" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMExpressDetailGroup class]])
                _groupNumber = (AMExpressDetailGroup *)oneObject;
    }
    
    _groupNumber.contentTitle.text=@"运单号码：";
    _groupNumber.contentValue.text = self.number;
    
    return _groupNumber;
}
-(AMExpressDetailGroup*)groupState
{
    if (_groupState==nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMExpressDetailGroup" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AMExpressDetailGroup class]])
                _groupState = (AMExpressDetailGroup *)oneObject;
        _groupState.contentTitle.text=@"最新状态：";
        _groupState.contentValue.text=@"无";
        _groupState.contentValue.textColor= RGB(0xff,0x66,0) ;
    }
    return _groupState;
}
-(AMLogisticsQueryRequest*)queryRequest
{
    if (_queryRequest==nil) {
        _queryRequest = [[AMLogisticsQueryRequest alloc] init];
    }
    _queryRequest.transactionType = AMTRANSACTION_TYPE_FAVORITE_LOGISTICS_TRACESTEP;
    _queryRequest.companyId = self.company.code;
    _queryRequest.deliveryId = self.number;
    return _queryRequest;
}

-(AMLogisticsQueryRequest*)queryByLogisticsRequest
{
    if (_queryByLogisticsRequest==nil) {
        _queryByLogisticsRequest = [[AMLogisticsQueryRequest alloc] init];
    }
    _queryByLogisticsRequest.transactionType = AMTRANSACTION_TYPE_QUERY_LOGIS_SIMPLE_ORDER;
    _queryByLogisticsRequest.logisticsId = self.logisticsID;
    return _queryByLogisticsRequest;
}

-(NSMutableArray*)resultData
{
    
    if (_resultData==nil) {
        _resultData = [[NSMutableArray alloc] init];
    }
    return _resultData;
}
- (void)dealloc {
    [_contentGroupTable release];
    [_contenDetailTable release];
    [_groupName release];
    [_groupNumber release];
    [_groupState release];
    [_company release];
    [_number release];
    [_logisticsID release];
    [_queryRequest release];
    [_queryByLogisticsRequest release];
    [_resultData release];
    [_noInfoView release];
    [_parentTitle release];
    
    [super dealloc];
}
- (void)viewDidUnload {
    [self setContentGroupTable:nil];
    [self setContenDetailTable:nil];
    _groupName = nil;
    _groupNumber = nil;
    _groupState = nil;
    _company = nil;
    _number = nil;
    _queryRequest=nil;
    _resultData=nil;
    
    [super viewDidUnload];
}
-(void) viewDidLoad
{
    [self.contenDetailTable setHidden:YES];
    self.contenDetailTable.bounces = NO;
    self.contenDetailTable.showsVerticalScrollIndicator = NO;
    self.noInfoView.alpha = 0.0f;
    
    if ([self logisticsID] != nil) {
        [self loadObjectsFromRemoteByLogisticsID];
    } else {
        [self loadObjectsFromRemote];
    }
    
    [super viewDidLoad];
}
-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}
-(NSString*)commonTableViewNavigationTitle
{
    return @"物流详情";
}
- (void)loadObjectsFromRemote {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
	objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL4PARAM];
    
    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: [AMLogisTraceStep sharedObjectMapping]];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_LOGISTICS_QUERY usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMLogisTraceStep class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.queryRequest;
    }];
    
    [super loadObjectsFromRemote];
}

- (void)loadObjectsFromRemoteByLogisticsID {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
	objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL4PARAM];
    
    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: [AMLogisSimpleOrder sharedObjectMapping]];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_ORDER_LOGISTICS_QUERY usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMLogisSimpleOrder class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.queryByLogisticsRequest;
    }];
    
    [super loadObjectsFromRemote];
}


#pragma mark RKObjectLoaderDelegate methods


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);    
    
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if ( transactionType == AMTRANSACTION_TYPE_FAVORITE_LOGISTICS_TRACESTEP ) {
            if (objects!=nil&&[objects count]>0) {
                
                self.noInfoView.alpha = 0.0f;
                [self.resultData addObjectsFromArray:objects];
                [self.contenDetailTable setHidden:NO];
                [self.contenDetailTable reloadData] ;
                
                AMLogisTraceStep *step = (AMLogisTraceStep*)[self.resultData objectAtIndex:[self.resultData count]-1];
                self.groupState.contentValue.text=step.remark;
                
            }else{
                self.noInfoView.alpha = 1.0f;
                [self.contenDetailTable setHidden:YES];
                [self.contenDetailTable reloadData] ;
            }

        } else if ( transactionType == AMTRANSACTION_TYPE_QUERY_LOGIS_SIMPLE_ORDER ) {
            if (objects!=nil&&[objects count]>0) {
                
                AMLogisSimpleOrder *logisSimpleOrder = [objects objectAtIndex:0];
                
                AMCorporation * company = [[AMCorporation alloc] init];
                company.name = logisSimpleOrder.logisticsCorpName;
                company.code = logisSimpleOrder.logisticsCompanyid;
                self.company = company;
                self.number = logisSimpleOrder.mailNo;
                [company release];
                
                self.noInfoView.alpha = 0.0f;
                //[self.resultData addObjectsFromArray:logisSimpleOrder.];
                [self.contenDetailTable setHidden:NO];
                //[self.contenDetailTable reloadData] ;
                
                AMLogisTraceStep *step = logisSimpleOrder.newestTraceStep;
                self.groupState.contentValue.text=step.remark;
                [self.contentGroupTable reloadData];
                
                self.logisticsID = nil;
                if (self.company != nil && self.company.code != nil && self.number != nil) {
                    [self loadObjectsFromRemote];
                } else {
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:NSLocalizedString(@"NO_MAIL_INFO", nil)] show];
                }
            }else{
                self.noInfoView.alpha = 1.0f;
                [self.contenDetailTable setHidden:YES];
                [self.contenDetailTable reloadData] ;
            }

        }
    }
    
    [super objectLoader:objectLoader didLoadObjects:objects];
}


#pragma mark Table View Data Source Methods
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView==self.contenDetailTable) {
        return 51.0;
    }
    return 44;
}

- (NSInteger)tableView:(UITableView *)tableView 
 numberOfRowsInSection:(NSInteger)section
{
    if (tableView==self.contentGroupTable)
    {
        return 3;
    }
    else
    {
        return [self.resultData count];
    }
}
- (UITableViewCell *)tableView:(UITableView *)tableView 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
    if (tableView==self.contentGroupTable)
    {
        NSUInteger row = [indexPath row];
        AMExpressDetailGroup *cell = (AMExpressDetailGroup *)[tableView 
                                                              dequeueReusableCellWithIdentifier: [AMExpressDetailGroup cellIdentifer]];
        if (row==0) {
            
            if (cell == nil)  
            {
                cell = self.groupName;
            } 
            
            cell.contentTitle.text=@"物流公司：";
            cell.contentValue.text = self.company.name;
              
        }
        else if (row==1)
        {
            if (cell == nil)  
            {
                cell = self.groupNumber;
            } 
           
            cell.contentTitle.text=@"运单号码：";
            cell.contentValue.text = self.number;
        }
        else
        {
            if (cell == nil)  
            {
                cell = self.groupState;
            } 
            
        }
        return cell;      
        
    }
    else
    {
        NSUInteger row = [indexPath row];
        
        AliTableViewCellSubTitle *cell = (AliTableViewCellSubTitle *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellSubTitle cellIdentifer]];
        if (cell == nil)  
        {
            cell = [AliTableViewCellSubTitle createCell];
            cell.frame = CGRectMake(0.0, 0.0, 320.0, 51.0);
            cell.title.fontSize = 12.0;
            [cell.title setupView];
            cell.subTitle.fontSize = 12.0;
            [cell.subTitle setupView];
            cell.hideIdentifyIMage = YES;
            cell.userInteractionEnabled = NO;
        }
        
        
        AMLogisTraceStep *step = (AMLogisTraceStep*)[self.resultData objectAtIndex:row];
        

        cell.title.text=step.remark;
        cell.subTitle.text =[StringUtils getDateStrLong:step.acceptTime.doubleValue/1000];
        return cell;
    }
}


- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if(tableView == self.contenDetailTable){
        [self.contenDetailTable deselectRowAtIndexPath:indexPath animated:YES];
    }
}
@end

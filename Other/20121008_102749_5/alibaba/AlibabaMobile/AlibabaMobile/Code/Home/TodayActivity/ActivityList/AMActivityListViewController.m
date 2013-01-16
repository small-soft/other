#import "AMActivityListViewController.h"

#import "AMActivityListRequest.h"
#import "AMActivityListResult.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "HJObjManager.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "NSAttributedString+HTML.h"
#import "AMActivityListCell.h"
#import "AMActivityDetailViewController.h"
#import "UIView+UIViewUtil.h"
#import "Utils.h"

@implementation AMActivityListViewController

@synthesize mTableView, mOfferResult,objMan;
@synthesize request = _requset;
@synthesize objects = _objects;
@synthesize parentTitle = _parentTitle;
@synthesize industryId = _industryId;
//@synthesize mLoadingView = _mLoadingView;

#pragma - mark
#pragma mark vc lifecycle

- (void) dealloc
{
    [mTableView release];
    [mOfferResult release];
    [_requset release];
    [_objects release];
    [objMan release];
    [_industryId release];
//    [_mLoadingView release];
    
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // 去掉分割线
    self.mTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    // 设置背景
    self.mTableView.backgroundColor = RGB(0xdb, 0xdb, 0xdb);
    
    [self objManInit];
    [self loadRequest];
}
- (void)viewDidUnload {
//    _mLoadingView = nil;
    self.objMan = nil;
    self.request = nil;
    [self.objects removeAllObjects];
    self.mTableView = nil;
    self.mOfferResult = nil;
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        isLoading = NO;
        
        self.objects = [[NSMutableArray alloc] init];
    }
    return self;
}

#pragma - mark
#pragma mark method of AliTable
-(NSString*)commonTableViewNavigationTitle
{
    return @"今日活动";
}

-(NSString*)commonTableViewBackButtonTitle
{
    return self.parentTitle;
}

#pragma - mark
#pragma mark table view & dataSource delegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    if(row == self.objects.count){
        return 45;
    }else{
        return [AMActivityListCell cellHeight];
        
    }
    
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{    
    if(self.objects.count <= 0){
        return 0;
    }else{
        return self.objects.count;
    }
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    NSUInteger row = [indexPath row];
    AMActivity *activity = (AMActivity*)[_objects objectAtIndex:row] ;
    AMActivityDetailViewController * detailView = [[AMActivityDetailViewController alloc] initWithNibName:@"AMActivityDetailViewController" bundle:nil];
    detailView.activityId = activity.activityId;
//    detailView.activityTitle = [NSString stringWithFormat:@"%@活动专场",activity.market];
    detailView.activityTitle = [NSString stringWithFormat:@"%@活动专场",@""];
    if([self.industryId isEqualToString:ACTIVITY_INDUSTRY_ID_OF_HOME]){
        //如果是家具百货的今日活动
        // 打点
        [AMLogUtils appendLog: TODAY_ACTITY_LIST_OF_CLOTH];
      detailView.businessType = AM_ACTIVITY_PRICE_TYPE_ACTIVITY_HOME;  
    }else{
        //如果是服装服饰的今日活动
        // 打点
        [AMLogUtils appendLog: TODAY_ACTITY_LIST_OF_HOME];
      detailView.businessType = AM_ACTIVITY_PRICE_TYPE_ACTIVITY;  
    }
    [self.navigationController pushViewController:detailView animated:YES];
    [self.mTableView deselectRowAtIndexPath:indexPath animated:NO];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    
    AMActivityListCell *cell = (AMActivityListCell *)[tableView dequeueReusableCellWithIdentifier: [AMActivityListCell cellIdentifer]];
    
    if (cell == nil){
        cell = [AMActivityListCell createCell];    
    }
    
    AMActivity *activity = (AMActivity*)[_objects objectAtIndex:row] ;
    [cell cellSetData:cell withActivity:activity];
    [self.objMan manage:cell.icon];
    return cell;
}

#pragma - mark
#pragma mark restkit delegate
-(void)loadRequest
{
    isLoading = YES;
    self.request = [[AMActivityListRequest alloc] init];
    self.request.industryId = self.industryId;
    
    [self loadObjectsFromRemote];
    
} 

- (void)loadObjectsFromRemote {
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_ACTIVITY usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [AMActivityListResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
        
    }];
    
    [super loadObjectsFromRemote];
    
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {  

    id object = [objects objectAtIndex:0];
    if(object != nil){
        
        AMActivityListResult * activity = object;
//        NSArray * array = [self filterExperied:activity.topicList];
        NSArray * array = activity.topicList;
        
        if (array == nil || [array count] == 0) {
            [self.mLoadingView showNodataMessage];
        } else {
            [self performSelectorOnMainThread:@selector(setTableData:) withObject:array waitUntilDone:YES];
            
            [super objectLoader:objectLoader didLoadObjects:objects];
        }
        
    }else{
        [UIHelp showAlertDialogWithTitle:@"错误" andMsg:@"获取信息失败！"];
    }
    
    isLoading = NO;
//    [self.mLoadingView showNodataMessage];
}

//- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
//	NSLog(@"Hit error: %@", error);
//}

#pragma - mark
#pragma mark setter & getter
-(void)objManInit
{
    if (objMan==nil) 
    {
        objMan = [Utils createObjManagerDefault];
        
    }
}

#pragma - mark
#pragma mark loading view methods
//-(UIView*)mLoadingView
//{
//    if (!_mLoadingView) {
//        
//        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
//        for (id oneObject in nib)
//            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
//                _mLoadingView = (AliLoadingDataView *)oneObject;
//        _mLoadingView.frame= CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
//        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
//        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
//        [self.view addSubview:_mLoadingView];
//        [_mLoadingView setHidden:NO];
//    }else {
//        [self.view bringSubviewToFront:_mLoadingView];
//    }
//    
//    return _mLoadingView;
//}


#pragma - mark
#pragma mark private method
- (void) setTableData:(NSMutableArray *)data
{
    
    [self.objects addObjectsFromArray:data];
    [self.mTableView reloadData];
}

-(NSArray *) filterExperied:(NSArray *)activities {
    if (activities == nil) {
        return nil;
    }
    
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:[activities count]];
    for (AMActivity *activity in activities) {
        if ([activity.expired isEqualToString:@"true"]) {
            continue;
        }
        
        [result addObject:activity];
    }
    
    return result;
}
@end
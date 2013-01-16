//
//  AMSubpageCommonViewController.m
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageCommonViewController.h"
#import "UIHelp.h"
#import "ConstDef.h"
#import "AMSubpageResult.h"
#import "AMSubpageRequest.h"
#import "ConstDef.h"
#import "AMMenuItemView.h"
#import "AMGroupCell.h"
#import "AMToastView.h"
#import "AliNavigationBackButton.h"
#import "AMAppDelegate.h"
#import "LoginToken.h"
#import "AMOfferListViewController.h"

@interface AMSubpageCommonViewController ()
@property (nonatomic, retain) AliNavigationBackButton * backButton;

@end
@implementation AMSubpageCommonViewController

@synthesize subpageRequest = _subpageRequest;

@synthesize subpageChildrenData = _subpageChildrenData;

@synthesize backButton = _backButton;

@synthesize mLoadingView = _mLoadingView;

@synthesize categoryName = _categoryName;
-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.backgroundColor = [UIColor colorWithRed:0xf0/255.0 green:0xf0/255.0 blue:0xf0/255.0 alpha:1.0];
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
//        _mLoadingView.delegate = self;
    }
    
    return _mLoadingView;
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}
-(AliNavigationBackButton*)backButton
{
    if (!_backButton) 
    {
        NSString * title = nil;
        
        title = @"首页";
        
        _backButton = [[AliNavigationBackButton alloc] initWithTitle:title];
        _backButton.navigationBackDelegate = self;
        
    }
    return _backButton;
}


-(AMSubpageRequest *)subpageRequest{
    if(!_subpageRequest){
        _subpageRequest =  [[AMSubpageRequest alloc] init];
        AMAppDelegate *appDelegate = (AMAppDelegate *)[[UIApplication sharedApplication] delegate];
        //注意。。这俩字段不太一样啊！不要看错。。
        _subpageRequest.terminalId = appDelegate.terminateId;
        NSString *loginUserName=nil;
        loginUserName=[LoginToken getLoginUserName];
        if([loginUserName length] > 3){
            _subpageRequest.loginId = loginUserName;
        }else {
            _subpageRequest.loginId = nil;
        }
        _subpageRequest.transactionType = AMTRANSACTION_TYPE_SUBPAGE_REQUEST;
        NSDictionary *dataRequestTree = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:@"tree",@"", nil] forKeys:[NSArray arrayWithObjects:@"configName",@"summary", nil]];
        NSDictionary *dataRequestRecommand = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:@"recommend",@"", nil] forKeys:[NSArray arrayWithObjects:@"configName",@"summary", nil]];
        NSDictionary *dataRequestHistory = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:@"history",@"", nil] forKeys:[NSArray arrayWithObjects:@"configName",@"summary", nil]];
        _subpageRequest.dataRequests = [NSArray arrayWithObjects:dataRequestTree,dataRequestRecommand,dataRequestHistory, nil];

    }
    return _subpageRequest;
}

-(NSMutableArray *)subpageChildrenData{
    if (!_subpageChildrenData) {
        _subpageChildrenData = [[NSMutableArray alloc] init];
    }
    return _subpageChildrenData;
}


#pragma mark RKObjectLoader

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response{
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
}


//extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error{
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
//    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
//    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
//        
//        gLastDisplayErrorTimeInterval = currentTime;
//    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
//        
//        gLastDisplayErrorTimeInterval = currentTime;
//    }
//    if ([error code] == RKRequestBaseURLOfflineError) {
//        [self.mLoadingView showLoadFailedMessageForRequest:request];
//    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error
{
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline)  {
        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
    }
}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects 
{
    NSLog(@"Loaded objects: %@", objects);
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if(transactionType == AMTRANSACTION_TYPE_SUBPAGE_REQUEST){
            AMSubpageResult * result = (AMSubpageResult*) [objects objectAtIndex:0];
            if (result.tree.hasChild) {
                [self.subpageChildrenData removeAllObjects];
                [self.subpageChildrenData addObjectsFromArray:result.tree.children];
                [self.tableView reloadData];
                
            }
        }
        
    }
    if ([self.subpageChildrenData count]>0) {
        [self.mLoadingView endLoadingView];
    }else {
        [self.mLoadingView showNodataMessage];
    }
}

#pragma mark view life cycle 

-(void)viewDidLoad{
    [super viewDidLoad];
    self.navigationItem.leftBarButtonItem = self.backButton;
    [self loadSubPageChildrenFromRemote];
//    [self loadHomePageCategoriesFromRemote];
}

-(void)viewDidUnload{
    [super viewDidUnload];
    self.backButton = nil;
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    self.subpageChildrenData = nil;
}
-(void)dealloc{

    AM_RELEASE_SAFELY(_subpageChildrenData);
    AM_RELEASE_SAFELY(_subpageRequest);
    AM_RELEASE_SAFELY(_backButton);
//    AM_RELEASE_SAFELY(_mLoadingView);
    self.mLoadingView = nil;
    AM_RELEASE_SAFELY(_categoryName);
    [super dealloc];
}


- (void)loadSubPageChildrenFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_INDUSTRY_SUBPAGE usingBlock:^(RKObjectLoader* loader) 
     {
         // Change Method to POST
         loader.delegate = self;
         if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
             
             loader.objectMapping = [AMSubpageResult sharedObjectMapping];
         }
         loader.method = RKRequestMethodPOST;
         
         loader.params = self.subpageRequest;
         
     }];
    [self.mLoadingView showLoadingView];
}

//-(void) rotateExpandBtn:(BOOL)isExpand withIndexPath:(NSIndexPath*)indexPath{
//    AMGroupCell * cell = (AMGroupCell*)[self.tableView cellForRowAtIndexPath:indexPath];
//    if (isExpand) {
//        [UIView beginAnimations:@"rotateDisclosureButt" context:nil];
//        [UIView setAnimationDuration:0.2];
//        cell.expandBtn.transform = CGAffineTransformMakeRotation(M_PI);
//        [UIView commitAnimations];
//    }else {
//        [UIView beginAnimations:@"rotateDisclosureButt" context:nil];
//        [UIView setAnimationDuration:0.2];
//        cell.expandBtn.transform = CGAffineTransformMakeRotation(2*M_PI);
//        [UIView commitAnimations];
//    }
//}

#pragma mark - 主table的事件 请实现
- (NSInteger) mainTable:(UITableView *)mainTable numberOfItemsInSection:(NSInteger)section{
    return [self.subpageChildrenData count];
}

//- (void) mainTable:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
//    
//    NSIndexPath * preIndexPath = self.expandedIndexPath.copy; 
//    
////    [self.tableView beginUpdates];
//
//    if ([indexPath isEqual: self.expandedIndexPath]) {
//        self.expandedIndexPath = nil;
////        [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
//    }else {
//        if (self.expandedIndexPath) {
//            self.expandedIndexPath = indexPath;
////            [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObjects:indexPath,preIndexPath,nil] withRowAnimation:UITableViewRowAnimationNone];
//        }else {
//            self.expandedIndexPath = indexPath;
////            [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
//        }
//    }
////    [UIView beginAnimations:@"expandtablerow" context:nil];
////    [UIView setAnimationDuration:0.8];
//    [self.tableView reloadData];
//    CATransition *animation = [CATransition animation];
//    [animation setType:kCATransitionPush];
//    [animation setSubtype:kCATransitionFromBottom];
//    [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear]];
//    [animation setFillMode:kCAFillModeBoth];
//    [animation setDuration:0.8];
//    [[((AMGroupCell*)[self.tableView cellForRowAtIndexPath:indexPath]).menuView layer] addAnimation:animation forKey:@"UITableViewReloadDataAnimationKey"];
////    [UIView commitAnimations];
////    [self.tableView endUpdates];
//    
////    AMGroupCell *cell = (AMGroupCell*)[tableView cellForRowAtIndexPath:indexPath];
////    cell.expandBtn.highlighted = NO;
//    if ([indexPath isEqual:preIndexPath]) {
//        [self rotateExpandBtn:NO withIndexPath:indexPath];
//    }else {
//        if (preIndexPath) {
//            [self rotateExpandBtn:NO withIndexPath:preIndexPath];
//            [self rotateExpandBtn:YES withIndexPath:indexPath];
//        }else {
//            [self rotateExpandBtn:YES withIndexPath:indexPath];
//        }
//    }
//    
//    
//}

//GroupCell的BackGroundView的宽度。
- (CGFloat) tableView:(UITableView *)tableView heightForGroupCellBackGroundViewAtIndexPath:(NSIndexPath *)indexPath{
    return 50.0;
}

#pragma mark - 下拉的menuView的方法 请实现
- (NSInteger) mainTable:(UITableView *)mainTable numberOfSubItemsforItemAtIndexPath:(NSIndexPath *)indexPath{
    AMSubpageTreeChildren* subpageTreeChildren = (AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex: [indexPath row]];
    if (subpageTreeChildren.hasChild) {
        return [subpageTreeChildren.children count];
    }else {
        return 0;
    }
}

- (void)groupCellIndexPath:(NSIndexPath*)groupCellIndexPath didSelectSubItem:(AMMenuItemView *)subItem withIndex:(NSInteger)index{
    AMSubpageTreeChildren* subpageTreeChildren = (AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex: [groupCellIndexPath row]];
    
    AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
    if ([((AMSubpageTreeChildren*)[subpageTreeChildren.children objectAtIndex:index]).type isEqualToString:@"keyword"]) {
        controller.keyWords = ((AMSubpageTreeChildren*)[subpageTreeChildren.children objectAtIndex:index]).name;
    }
    controller.catId = ((AMSubpageTreeChildren*)[subpageTreeChildren.children objectAtIndex:index]).ID
    ;
    controller.catName = ((AMSubpageTreeChildren*)[subpageTreeChildren.children objectAtIndex:index]).name;
    controller.parentTitle = self.navigationItem.title;
    controller.parentCatId=((AMSubpageTreeChildren*)[subpageTreeChildren.children objectAtIndex:index]).ID;


    if ([self.subpageRequest.categoryId isEqualToString:@"fuzhuangfushi"])
    {
        [AMLogUtils appendLog:APP_DRESSCATEGORY_BROWSER_TWO];
        controller.navigationCategoryId = subpageTreeChildren.ID;
    }else {
        [AMLogUtils appendLog:APP_OTHERINDUSTRY_BROWSER_FOUR];
        controller.navigationCategoryId = self.subpageRequest.categoryId;
    }
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES];
    [controller release];
//    NSLog(@"yujia %d", [groupCellIndexPath row]);
}

- (void) collapsableButtonTapped: (UIControl *) button withEvent: (UIEvent *) event{
    UITableView *tableView = self.tableView;
    NSIndexPath * indexPath = [tableView indexPathForRowAtPoint: [[[event touchesForView: button] anyObject] locationInView: tableView]];
    if ( indexPath == nil )
        return;
    [self mainTable:self.tableView didSelectRowAtIndexPath:indexPath];
//    NSIndexPath * preIndexPath = self.expandedIndexPath.copy; 
//    
////    [self.tableView beginUpdates];
//    if ([indexPath isEqual: self.expandedIndexPath]) {
//        self.expandedIndexPath = nil;
//        [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
//    }else {
//        if (self.expandedIndexPath) {
//            self.expandedIndexPath = indexPath;
//            [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObjects:indexPath,preIndexPath,nil] withRowAnimation:UITableViewRowAnimationAutomatic];
//        }else {
//            self.expandedIndexPath = indexPath;
//            [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
//        }
//    }
////    [self.tableView endUpdates];
//    
//    if ([indexPath isEqual:preIndexPath]) {
//        [self rotateExpandBtn:NO withIndexPath:indexPath];
//    }else {
//        if (preIndexPath) {
//            [self rotateExpandBtn:NO withIndexPath:preIndexPath];
//            [self rotateExpandBtn:YES withIndexPath:indexPath];
//        }else {
//            [self rotateExpandBtn:YES withIndexPath:indexPath];
//        }
//    }
}
//aliloadingdataview delegate
//-(void)reloadLoadingData{
//    [self loadSubPageChildrenFromRemote];
//}

@end


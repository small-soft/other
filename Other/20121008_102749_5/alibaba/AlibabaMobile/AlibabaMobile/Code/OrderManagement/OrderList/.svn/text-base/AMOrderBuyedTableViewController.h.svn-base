//
//  AMOrderBuyedTableViewController.h
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-8-26.
//
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import <QuartzCore/QuartzCore.h>
#import "AliTabContentViewController.h"
#import "AMOrderBuyedTableViewCell.h"

#import "AMCommonTableForOceanClientViewController.h"
#import "AliTableView.h"
#import "OceanClientViewController.h"

@class AMOrderBuyedRequest;
@class AMOrderBuyedResult;
@class HJObjManager;

//@interface AMOrderBuyedTableViewController: AMCommonTableForOceanClientViewController <AliTableViewDelegate,UITableViewDelegate, UITableViewDataSource>
@interface AMOrderBuyedTableViewController: AMCommonTableForOceanClientViewController <AliTableViewDelegate,UITableViewDelegate, UITableViewDataSource>
{
    AMOrderBuyedRequest *_request;
    NSMutableArray * _objects;
    bool isLoading;
    int currentIndex;
    NSDictionary * _orderStateDict;
    int _currentPage;
    int _totalCount;
    BOOL isFirstReceiveNotify;
    BOOL isPullViewLoad;
//    BOOL isReceiveOrderStateNotify;
    
}

@property (nonatomic, retain) IBOutlet UITableView * m2TableView;
@property (nonatomic, retain) AMOrderBuyedResult * mOfferResult;
@property (nonatomic, retain) AMOrderBuyedRequest * request;
@property (nonatomic, retain) NSMutableArray * objects;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) NSString *parentTitle;
@property (nonatomic, retain) UINavigationController * mNavigationController;
@property (nonatomic, retain) NSDictionary * orderStateDict;
@property (readwrite) int totalCount;
@property (readwrite) int currentPage;
@property (readwrite) BOOL isReceiveOrderStateNotify;
@property (nonatomic, retain) AliLoadingDataView * mLoadingView;
@property (nonatomic,assign) NSInteger tempCurrentPage;

- (void)loadObjectsFromRemote;
- (id)initWithNavigation:(UINavigationController *)navigation;

@end


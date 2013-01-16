//
//  AMOrderSelledTableViewController.h
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-9-14.
//
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import <QuartzCore/QuartzCore.h>
#import "AliTabContentViewController.h"
#import "AMOrderBuyedTableViewCell.h"

#import "AMCommonTableForOceanClientViewController.h"
#import "AliTableView.h"
#import "AliLoadingDataView.h"
#import "OceanClientViewController.h"

@class AMOrderSelledRequest;
@class AMOrderBuyedResult;
@class HJObjManager;

@interface AMOrderSelledTableViewController: AMCommonTableForOceanClientViewController <AliTableViewDelegate,UITableViewDelegate, UITableViewDataSource>
{
    AMOrderSelledRequest *_request;
    NSMutableArray * _objects;
    bool isLoading;
    int currentIndex;
    NSDictionary * _orderStateDict;
    int _currentPage;
    int _totalCount;
    BOOL isPullViewLoad;
//    BOOL isReceiveOrderStateNotify;
}

@property (nonatomic, retain) IBOutlet UITableView * m2TableView;
@property (nonatomic, retain) AMOrderBuyedResult * mOfferResult;
@property (nonatomic, retain) AMOrderSelledRequest * request;
@property (nonatomic, retain) NSMutableArray * objects;
@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic, retain) NSString *parentTitle;
@property (nonatomic, retain) UINavigationController * mNavigationController;
@property (nonatomic, retain) NSDictionary * orderStateDict;
@property (readwrite) int totalCount;
@property (readwrite) int currentPage;
@property (nonatomic, retain) UIView *headerView;
@property (nonatomic, retain) UIButton *pickerButton;
@property (readwrite) BOOL isReceiveOrderStateNotify;
@property (nonatomic, retain) AliLoadingDataView * mLoadingView;
@property (nonatomic,assign) NSInteger tempCurrentPage;

- (void)loadObjectsFromRemote;
- (id)initWithNavigation:(UINavigationController *)navigation;

@end


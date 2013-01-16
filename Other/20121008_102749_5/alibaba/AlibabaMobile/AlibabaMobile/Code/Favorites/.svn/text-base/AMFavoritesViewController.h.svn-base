//
//  AMFavoritesViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <RestKit/RestKit.h>
#import "AMFavoriteRequest.h"
#import "HJObjManager.h"
#import "AliSegmentedControl.h"
#import "AMSegmentedCtlWithButton.h"
#import "AMFavoriteRequest.h"
#import "AliLoadingDataView.h"
#import "OceanClientViewController.h"
@interface AMFavoritesViewController : OceanClientViewController <UITabBarDelegate,UITableViewDelegate, UITableViewDataSource,AMSegmentedDelegate> {
    
    NSInteger  selectItem;
    
    int productTotalCount;
    int companyTotalCount;
    int priceTotalCount;
    
    int currentProPage;
    int currentComPage;
    int currentPriPage;
    
    BOOL isLoading;
    BOOL isSegmentChanged;
    BOOL isFavCallLogin;
    int forceLoginCount;
    //由于在每次viewwillappear的时候都会去更新list 而push进入detail的时候再返回是不需要更新的，因此做了一个判断 这个isFromDetail原来不是这么用的 但是我发现原来的功能已经没有用了 那个notification也没有用 注释掉后使用良好 
    //add by christ.yuj
    BOOL isFromDetail;
    //    AliSegmentedControl  * mSegmentedControl;
    
}

@property (nonatomic,retain) NSMutableArray *controllers;
@property (nonatomic,retain) IBOutlet UITabBar *favorites;
@property (nonatomic,retain) IBOutlet UIView *favoritesView;
@property (nonatomic,retain) IBOutlet UITableView *offerTableView;
@property (nonatomic,retain) IBOutlet UITableView *companyTableView;
@property (nonatomic,retain) IBOutlet UITableView *priceTableView;
@property (nonatomic, retain) NSMutableArray* _proObjects;
@property (nonatomic, retain) NSMutableArray* _comObjects;
@property (nonatomic, retain) NSMutableArray* _priObjects;
@property (nonatomic, retain) AMFavoriteRequest *favOfferRequest;
@property (nonatomic, retain) AMFavoriteRequest *favComanyRequest;
@property (nonatomic, retain) AMFavoriteRequest *favPriceRequest;
@property (nonatomic,retain) HJObjManager *objMan;
@property (nonatomic, retain) AMFavoriteRequest *delFavOfferRequset;
@property (nonatomic, retain) AMFavoriteRequest *delFavComanyRequest;
@property (nonatomic, retain) AMFavoriteRequest *delFavPriceRequest;
@property (readwrite) NSUInteger rowToDel;
@property (nonatomic, retain) AliLoadingDataView *mLoadingView;
@property (nonatomic,retain) AMSegmentedCtlWithButton *mSegmentedControl;

- (void)loadObjectsFromRemoteProduct;
- (void)loadObjectsFromRemoteCompany;
- (void)loadObjectsFromRemotePrice;
- (void) customTabbarArea;
-(void)loginEvent:(id)sender;
-(void) setSelectedSegmentIndex:(NSUInteger)index;
@end

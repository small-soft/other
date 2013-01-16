//
//  AMPriceGraphViewController.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "S7GraphView.h"
#import "GraphNodeList.h"
#import "AliBaseViewController.h"
#import "AMBaseViewController.h"
#import "AMGraphPickView.h"


@interface AMPriceGraphViewController : AMBaseViewController<S7GraphViewDataSource,RKObjectLoaderDelegate,AMPickViewDataSource>
{
    
	S7GraphView *graphView;
    GraphNodeList *graphNodeList;
    AMGraphPickView *mPickView;
    UINavigationBar *myNavigationBar;
    UINavigationItem *myNavigationItem;
    UIBarButtonItem *myRightNavigationItem;
    UIView *myView;
    
    IBOutlet UIScrollView *scrollView;
    UILabel *lableInfo;
    
    NSString *sourceAddressName;
    //从服务器获取的数据信息
    NSString *sourceFromName;
    NSNumber *themeId;
    NSString *themeName;
    NSNumber *categroyId;
    NSMutableArray *lists;
    NSMutableArray *gNodelists;
    //request data
    NSNumber *themeRequstId; 
    NSNumber *areaRequstId;
    NSNumber *sourceFomeRequstId;
    
    UIImage * btnBackImg;
    UIImage * btnBackImgPressed;
    
    BOOL isPriceFavorited;
    NSString *navigateTitleName;

    
}

@property (nonatomic, retain) S7GraphView *graphView;
@property (nonatomic, retain) IBOutlet UILabel *lableInfo;
@property (nonatomic, retain) GraphNodeList *graphNodeList;
@property (nonatomic, retain) AMGraphPickView *mPickView;
@property (nonatomic, retain) IBOutlet UINavigationBar *myNavigationBar;
@property (nonatomic, retain) UINavigationItem *myNavigationItem;
@property (nonatomic, retain) UIBarButtonItem *myRightNavigationItem;
@property (nonatomic, retain) UIView *myView;

@property (nonatomic, retain) NSString *sourceFromName;
@property (nonatomic, retain) NSNumber *themeId;
@property (nonatomic, retain) NSString *themeName;
@property (nonatomic, retain) NSNumber *categroyId;
@property (nonatomic, retain) NSMutableArray *lists;
@property (nonatomic, retain) NSMutableArray *gNodelists;

@property (nonatomic, retain) NSNumber *themeRequstId;
@property (nonatomic, retain) NSNumber *areaRequstId;
@property (nonatomic, retain) NSNumber *sourceFomeRequstId;
@property (nonatomic, retain) NSString *sourceAddressName;

@property (nonatomic, assign) BOOL isPriceFavorited;
@property (nonatomic, retain) NSString *navigateTitleName;

@end

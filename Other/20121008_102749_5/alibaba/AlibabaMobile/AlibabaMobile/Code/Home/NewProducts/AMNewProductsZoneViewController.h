//
//  AMNewProductsZoneViewController.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>



#import "AMBrandsCategoryRequest.h"
#import "AMBrandsCategoryResult.h"

#import "AMNewProductsCategoryRequest.h"
#import "AMNewProductsListRequest.h"
#import "ConstDef.h"
#import "AMHotRankResult.h"
#import "AMNewProductsListResult.h"
#import "UIHelp.h"
#import "AMNewProductsListItem.h"
#import "AMNewProductsItem.h"
#import "ImageMagazineDetailViewController.h"
#import "AMOfferTabViewController.h"

#import "AMTodayActivityBlockBoxCell.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"

#import "AMLogUtils.h"

#define HORIZANTAL_HEIGHT 40

@interface AMNewProductsZoneViewController : AliBaseViewController<UIScrollViewDelegate, RKObjectLoaderDelegate,UITableViewDelegate,UITableViewDataSource>

@property (nonatomic,retain) IBOutlet UIImageView * horizontalBg;
@property (nonatomic,retain) IBOutlet UIImageView * rightArrowImg;


@property (nonatomic,retain) IBOutlet UIScrollView * horizontalView;
@property (nonatomic,retain) IBOutlet UITableView * contentView;


@property (nonatomic) BOOL isLoadCategory;


@property (nonatomic,retain) AMBrandsCategoryRequest * cateRequest;
@property (nonatomic,retain) AMNewProductsCategoryRequest * categoryRequest;
@property (nonatomic,retain) AMNewProductsListRequest * productRequest;

@property (nonatomic,retain) NSMutableArray * originCategoryList;
@property (nonatomic,retain) NSMutableArray * categoryList;


@property (nonatomic) NSInteger sum;
@property (nonatomic) NSInteger currentRequestPage;
@property (nonatomic) NSInteger currentNum;

@property (nonatomic, retain) NSMutableArray * productsList;
@property (nonatomic, retain) HJObjManager *objMan;

@property (nonatomic) NSInteger currentCateId;

@property (nonatomic) BOOL isCateSwitch;

@property (nonatomic) BOOL isLoading;

@property (nonatomic) NSInteger currentOffsetY;
@property (nonatomic) BOOL topHidden;

@property (nonatomic) BOOL isFirstLoad;



@end

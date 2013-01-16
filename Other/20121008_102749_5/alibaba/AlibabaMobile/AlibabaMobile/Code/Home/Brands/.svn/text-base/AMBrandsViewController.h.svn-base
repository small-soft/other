//
//  AMBrandsViewController.h
//  AlibabaMobile
//
//  Created by alimobile on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliCommonTableView.h"
#import "AMBrandsCategoryRequest.h"
#import "AMBrandsRequest.h"
#import "HJObjManager.h"

#import "AliLoadingDataView.h"

@interface AMBrandsViewController : AliCommonTableView<UITableViewDelegate,UITableViewDataSource,RKObjectLoaderDelegate>

@property (nonatomic,retain) IBOutlet UIScrollView * horizontalView;
@property (nonatomic,retain) IBOutlet UITableView * verticalView;
@property (nonatomic,retain) IBOutlet UIImageView * arrowImageView;
@property (nonatomic,retain) IBOutlet UIImageView * horizontalViewBackgroundImageView;
@property (nonatomic,retain) NSMutableArray* blockBoxData;
@property (nonatomic,retain) NSMutableArray* categoryData;
@property ( nonatomic ) BOOL isCateResponse;

@property (nonatomic,retain) AMBrandsCategoryRequest * cateRequest;
@property (nonatomic,retain) AMBrandsRequest * brandsRequest;

@property (nonatomic)        NSInteger  currentCateId;
@property (nonatomic,retain) NSString * currentCateName;

@property (nonatomic) CGFloat originalY;
@property (nonatomic) NSInteger defaultCate;

@property (nonatomic) BOOL horizontalViewHidden;

@property (nonatomic, retain) HJObjManager *objMan;
@property (nonatomic) BOOL isFirstLoad;
@property (nonatomic) NSInteger lastMenuOffset;
@property (nonatomic) CGFloat currentOffset;


//@property (nonatomic,retain) AliLoadingDataView * mLoadingView;


@end

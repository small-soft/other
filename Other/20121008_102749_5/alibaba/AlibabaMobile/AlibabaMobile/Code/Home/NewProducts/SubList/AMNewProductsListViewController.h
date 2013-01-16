//
//  ImageMagazineListViewController.h
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "HJObjManager.h"
#import "ConstDef.h"
#import "AliBaseViewController.h"
#import "AliSegmentedControl.h"

@interface AMNewProductsListViewController : AliBaseViewController<AliNavigationBackDelegate,  RKObjectLoaderDelegate, UIScrollViewDelegate,AliSegmentedDelegate>

- (id)initWithSecondcate:(NSString *)secondcate title:(NSString *)title pageId:(NSString *)pageId;

@end

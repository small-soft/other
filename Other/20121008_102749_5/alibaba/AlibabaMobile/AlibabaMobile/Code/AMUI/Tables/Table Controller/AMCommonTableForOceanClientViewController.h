//
//  AMCommonTableForOceanClientViewController.h
//  AlibabaMobile
//
//  Created by  on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliCommonTableView.h"
#import <RestKit/RestKit.h>
#import "LoginTokenHelper.h"
@interface AMCommonTableForOceanClientViewController : AliCommonTableView<RKOceanClientDelegate,LoginTokenHelperDelegate>
@property (nonatomic,retain) RKOceanClient *oceanClient;
@end

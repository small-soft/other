//
//  OceanClientViewController.h
//  AlibabaMobile
//
//  Created by  on 12-9-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "LoginTokenHelper.h"
@interface OceanClientViewController : UIViewController<RKOceanClientDelegate,LoginTokenHelperDelegate>
@property (nonatomic,retain) RKOceanClient *oceanClient;
@end

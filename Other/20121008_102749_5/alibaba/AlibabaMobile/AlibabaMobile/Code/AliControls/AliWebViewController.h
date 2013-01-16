//
//  AliWebViewController.h
//  AlibabaMobile
//
//  Created by zzh on 12-3-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliNavigationBackButton.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
@interface AliWebViewController : UIViewController <UIWebViewDelegate,AliNavigationBackDelegate>

-(BOOL)needReloadView;

- (void) showLoadingView;
-(void) endLoadingView;
@end

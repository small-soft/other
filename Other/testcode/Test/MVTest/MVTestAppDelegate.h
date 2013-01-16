//
//  MVTestAppDelegate.h
//  MVTest
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MVTestViewController.h"

@interface MVTestAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) IBOutlet UIWindow *window;
@property (strong, nonatomic) IBOutlet MVTestViewController *mvTestViewController;

+ (MVTestAppDelegate *)app;

@end

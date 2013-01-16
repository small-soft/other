//
//  PKAppDelegate.h
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PKViewController;

@interface PKAppDelegate : UIResponder <UIApplicationDelegate> {
    UIWindow *_window;
    UITabBarController *_rootController;
}

@property (strong, nonatomic) IBOutlet UIWindow *window;

@property (strong, nonatomic) PKViewController *viewController;

@property (strong, nonatomic) IBOutlet UITabBarController *rootController; 

@end

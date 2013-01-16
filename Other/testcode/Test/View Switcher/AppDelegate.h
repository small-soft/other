//
//  AppDelegate.h
//  View Switcher
//
//  Created by 佳 刘 on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class MainViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    UIWindow *window;
    MainViewController *mainViewController;
}

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic,retain) IBOutlet MainViewController *mainViewController;

@end

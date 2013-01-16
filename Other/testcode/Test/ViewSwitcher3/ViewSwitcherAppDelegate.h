//
//  ViewSwitcherAppDelegate.h
//  ViewSwitcher3
//
//  Created by 佳 刘 on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class SwitchViewController;

@interface ViewSwitcherAppDelegate : UIResponder <UIApplicationDelegate> {
    UIWindow *window;
    SwitchViewController *switchViewController;
}

@property (strong, nonatomic) UIWindow *window;
@property (retain,nonatomic) IBOutlet SwitchViewController *switchViewController;

@end

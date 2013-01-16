//
//  SWHAppDelegate.h
//  SWH
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class SWHViewController;

@interface SWHAppDelegate : UIResponder <UIApplicationDelegate> {
    UIWindow *window;
    SWHViewController *swhViewController;
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) IBOutlet SWHViewController *swhViewController;

@end

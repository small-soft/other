//
//  SWH3AppDelegate.h
//  SWH3
//
//  Created by 佳 刘 on 12-8-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class SWH3ViewController;

@interface SWH3AppDelegate : UIResponder <UIApplicationDelegate> {
    UIWindow *window;
    SWH3ViewController *swhViewController;
}

@property (strong, nonatomic) IBOutlet UIWindow *window;
@property (strong, nonatomic) IBOutlet SWH3ViewController *swhViewController;

@end

//
//  iphone_scanbarAppDelegate.h
//  iphone.scanbar
//
//  Created by wangjun on 10-12-26.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@class iphone_scanbarViewController;

@interface iphone_scanbarAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    iphone_scanbarViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet iphone_scanbarViewController *viewController;

@end


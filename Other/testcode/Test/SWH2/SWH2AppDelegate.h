//
//  SWH2AppDelegate.h
//  SWH2
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class SWH2ViewController;

@interface SWH2AppDelegate : UIResponder <UIApplicationDelegate> {
    UIWindow *window;
    SWH2ViewController *swh2ViewController;
}

@property (strong, nonatomic) IBOutlet UIWindow *window;
@property (retain, nonatomic) IBOutlet SWH2ViewController *swh2ViewController;

@end

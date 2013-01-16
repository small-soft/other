//
//  MobWinSampleAppDelegate.h
//  MobWinSample
//
//  Created by Guo Zhao on 11-12-26.
//  Copyright 2011 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MobWinSampleAppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    UINavigationController *navigationController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

@end


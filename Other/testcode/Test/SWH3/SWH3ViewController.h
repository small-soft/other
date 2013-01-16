//
//  SWH3ViewController.h
//  Test
//
//  Created by 佳 刘 on 12-8-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class Blue3ViewController;
@class Yellow3ViewController;

@interface SWH3ViewController : UIViewController {
    Blue3ViewController *blueViewController;
    Yellow3ViewController *yellowViewController;
}

@property (nonatomic,retain) Blue3ViewController *blueViewController;
@property (nonatomic,retain) Yellow3ViewController *yellowViewController;

- (void)initView;
- (void)showBlueView;
- (void)showYellowView;
- (void)removeAllView;
- (IBAction)swhNextViews:(id)sender;

@end

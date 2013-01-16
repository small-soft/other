//
//  SwitchViewController.h
//  Test
//
//  Created by 佳 刘 on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BlueViewController;
@class YellowViewController;

@interface SwitchViewController : UIViewController {
    YellowViewController *yellowViewController;
    BlueViewController *blueViewController;
}

@property (retain,nonatomic) YellowViewController *yellowViewController;
@property (retain,nonatomic) BlueViewController *blueViewController;

-(IBAction)switchViews3:(id)sender;

@end

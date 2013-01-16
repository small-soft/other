//
//  SWHViewController.h
//  SWH
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BlueViewController;
@class YellowViewController;

@interface SWHViewController : UIViewController {
    YellowViewController *yellowViewController;
    BlueViewController *blueViewController;
}

@property (strong, nonatomic) YellowViewController *yellowViewController;
@property (strong, nonatomic) BlueViewController *blueViewController;

- (IBAction)swhViews:(id)sender;
- (void)initview;

@end

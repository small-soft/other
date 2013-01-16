//
//  MainViewController.h
//  View Switcher
//
//  Created by 佳 刘 on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "FlipsideViewController.h"
@class ABCViewController;
@class BCDViewController;

@interface MainViewController : UIViewController <FlipsideViewControllerDelegate, UIPopoverControllerDelegate> {
    
    ABCViewController *abcViewController;
    BCDViewController *bcdViewController;
}

@property (strong, nonatomic) UIPopoverController *flipsidePopoverController;
@property (retain, nonatomic) ABCViewController *abcViewController;
@property (retain, nonatomic) BCDViewController *bcdViewController;

-(IBAction)mySwitch:(id)sender;

@end

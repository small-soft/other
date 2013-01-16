//
//  QFViewController.h
//  QuartzFun
//
//  Created by 佳 刘 on 12-10-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface QFViewController : UIViewController {
    UISegmentedControl *colorControl;
}

@property (nonatomic,retain) IBOutlet UISegmentedControl *colorControl;

- (IBAction)changeColor:(id)sender;
- (IBAction)changeShape:(id)sender;

@end

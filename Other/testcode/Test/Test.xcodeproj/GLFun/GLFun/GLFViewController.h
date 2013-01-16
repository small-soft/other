//
//  GLFViewController.h
//  GLFun
//
//  Created by 佳 刘 on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GLFViewController : UIViewController {
    UISegmentedControl *colorControl;
}

@property (nonatomic,retain) IBOutlet UISegmentedControl *colorControl;
- (IBAction)changeColor:(id)sender;
- (IBAction)changeShape:(id)sender;

@end

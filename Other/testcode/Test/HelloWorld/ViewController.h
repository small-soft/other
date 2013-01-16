//
//  ViewController.h
//  HelloWorld
//
//  Created by 佳 刘 on 12-7-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController{
    UILabel *statusText;
}

@property (nonatomic,retain) IBOutlet UILabel *statusText;
- (IBAction)buttonPressed:(id)sender;

@end

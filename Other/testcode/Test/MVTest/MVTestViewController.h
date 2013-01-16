//
//  MVTestViewController.h
//  Test
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class FirstViewController;
@class SecondViewController;

@interface MVTestViewController : UIViewController {
    FirstViewController *firstViewController;
    SecondViewController *secondViewController;
}

@property (nonatomic,retain) FirstViewController *firstViewController;
@property (nonatomic,retain) SecondViewController *secondViewController;

- (void)initView;
- (void)showFirstView;
- (void)showSecondView;
- (void)removeAllView;

@end

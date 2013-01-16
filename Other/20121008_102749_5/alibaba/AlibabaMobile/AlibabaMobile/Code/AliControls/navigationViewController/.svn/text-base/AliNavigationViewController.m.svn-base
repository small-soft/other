//
//  AliNavigationViewController.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliNavigationViewController.h"

@implementation AliNavigationViewController

-(void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_HIDETABBAR object:self];
    [super pushViewController:viewController animated:animated];
    
}

-(UIViewController*)popViewControllerAnimated:(BOOL)animated
{
    if (self.topViewController == [self.viewControllers objectAtIndex:1]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_UNHIDETABBAR object:self];
    }

    UIViewController *viewController = [super popViewControllerAnimated:animated];

       
    return   viewController;
}


- (NSArray *)popToViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    if (self.topViewController == [self.viewControllers objectAtIndex:0]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_UNHIDETABBAR object:self];
    }
    return [super popToViewController:viewController animated:animated];
}

- (NSArray *)popToRootViewControllerAnimated:(BOOL)animated
{
    return [super popToRootViewControllerAnimated:animated];
}
/*-----------------------*/
/*
 修复在ios4.3.2版本中viewWillAppear没有被调用到的情况
 */
- (void)navigationController:(UINavigationController *)navigationController 
willShowViewController:(UIViewController *)viewController animated:(BOOL
                                                                    )animated 
{
    [viewController viewWillAppear:animated];
}

- (void)navigationController:(UINavigationController *)navigationController 
didShowViewController:(UIViewController *)viewController animated:(BOOL
                                                                   )animated 
{
    [viewController viewDidAppear:animated];
}
/*-----------------------*/

@end

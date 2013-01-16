//
//  SWH3ViewController.m
//  Test
//
//  Created by 佳 刘 on 12-8-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SWH3ViewController.h"
#import "Blue3ViewController.h"
#import "Yellow3ViewController.h"

@interface SWH3ViewController ()

@end

@implementation SWH3ViewController
@synthesize blueViewController;
@synthesize yellowViewController;

- (void)initView {
    NSLog(@"init view ....");
    if (self.blueViewController == nil) {
        self.blueViewController = [[Blue3ViewController alloc] initWithNibName:@"BlueView" bundle:nil];
        
    }
    
    [self removeAllView];
    [self.view insertSubview:self.blueViewController.view atIndex:0];
    
}

- (void)showBlueView {
    
}

- (void)showYellowView {
    
}

- (void)removeAllView {
    
}

- (IBAction)swhNextViews:(id)sender {
    [UIView beginAnimations:@"View Flip" context:nil];
    [UIView setAnimationDuration:1.25];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    
    // 如果viewController存在，但其父视图为空，说明其没有显示
    if(self.blueViewController.view.superview == nil) {
        
        if (self.blueViewController == nil) {
            self.blueViewController = [[Blue3ViewController alloc] initWithNibName:@"BlueView" bundle:nil];
        }
        
        [UIView setAnimationTransition:UIViewAnimationTransitionFlipFromRight forView:self.view cache:YES];
        
        [yellowViewController viewWillAppear:YES];
        [blueViewController viewWillDisappear:YES];
        
        [yellowViewController.view removeFromSuperview];
        [self.view insertSubview:self.blueViewController.view atIndex:0];
        
        [blueViewController viewDidDisappear:YES];
        [yellowViewController viewDidAppear:YES];
        
    } else {
        if (self.yellowViewController == nil) {
            self.yellowViewController = [[Yellow3ViewController alloc] initWithNibName:@"YellowView" bundle:nil];
        }
        
        [UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:self.view cache:YES];
        
        [blueViewController viewWillAppear:YES];
        [yellowViewController viewWillDisappear:YES];
        
        [blueViewController.view removeFromSuperview];
        [self.view insertSubview:self.yellowViewController.view atIndex:0];
        
        [yellowViewController viewDidDisappear:YES];
        [blueViewController viewDidAppear:YES];
    }
    
    [UIView commitAnimations];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end

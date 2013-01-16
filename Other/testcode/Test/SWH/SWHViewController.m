//
//  SWHViewController.m
//  SWH
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SWHViewController.h"
#import "BlueViewController.h"
#import "YellowViewController.h"

@interface SWHViewController ()

@end

@implementation SWHViewController
@synthesize yellowViewController;
@synthesize blueViewController;

- (void)initview {
    NSLog(@"ttt");
    if (self.blueViewController == nil) {
        self.blueViewController = [[BlueViewController alloc] initWithNibName:@"Blue view" bundle:nil];
    }
    
self.view = [[UIView alloc]init];

    [self.view insertSubview:self.blueViewController.view atIndex:0];
}

- (void)viewDidLoad
{
    BlueViewController *blueController = [[BlueViewController alloc] initWithNibName:@"BlueView" bundle:nil];
    self.blueViewController = blueController;
//    [self.view insertSubview:blueController.view atIndex:0];
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (IBAction)swhViews:(id)sender {
    
}

@end

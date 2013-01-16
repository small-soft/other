//
//  MVTestViewController.m
//  Test
//
//  Created by 佳 刘 on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MVTestViewController.h"
#import "FirstViewController.h"
#import "SecondViewController.h"

@interface MVTestViewController ()

@end

@implementation MVTestViewController
@synthesize firstViewController;
@synthesize secondViewController;

- (void)initView {
    NSLog(@"ttt");
    if (self.firstViewController == nil) {
        self.firstViewController = [[FirstViewController alloc] initWithNibName:@"FirstView" bundle:nil];
        
    }
    
    [self removeAllView];
    
    [self.view insertSubview:self.firstViewController.view atIndex:0];
}

- (void)showFirstView {
    [self initView];
}

- (void)showSecondView {
    if (self.secondViewController == nil) {
        self.secondViewController = [[SecondViewController alloc] initWithNibName:@"SecondView" bundle:nil];
        
    }
    
    [self removeAllView];
    
    [self.view insertSubview:self.secondViewController.view atIndex:0];
}

- (void)removeAllView {
    for (NSInteger i = 0; i<[self.view.subviews count]; i++) {
        [[self.view.subviews objectAtIndex:i] removeFromSuperview];
    }
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

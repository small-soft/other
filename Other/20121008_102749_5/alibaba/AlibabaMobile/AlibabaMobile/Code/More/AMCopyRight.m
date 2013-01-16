//
//  AMCopyRight.m
//  AlibabaMobile
//
//  Created by lih on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCopyRight.h"

@implementation AMCopyRight

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.title = NSLocalizedString(@"版权信息", @"");
    }
    return self;
}


- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)setBackButton
{    
    AliNavigationBackButton * backButton = [[AliNavigationBackButton alloc] initWithTitle:@"更多" ];
    backButton.navigationBackDelegate=self;
    self.navigationItem.leftBarButtonItem = backButton;
    [backButton release];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self setBackButton];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {   
    [super dealloc];
}

@end

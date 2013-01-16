//
//  AliTabContentViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTabContentViewController.h"

@interface AliTabContentViewController()


@end

@implementation AliTabContentViewController

@synthesize dataDict = _dataDict;
@synthesize navigationController = _navigationController;


- (id)initWithData:(NSMutableDictionary *)data navigationController:(UINavigationController *) navigationController
{
    self = [super init];
    if (self) {
        self.dataDict = data;
        self.navigationController = navigationController;
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void) dealloc
{
    [_dataDict release];
    [_navigationController release];
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
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

@end

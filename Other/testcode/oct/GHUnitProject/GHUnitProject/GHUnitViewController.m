//
//  ViewController.m
//  GHUnitProject
//
//  Created by mardin partytime on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GHUnitViewController.h"


@implementation GHUnitViewController
@synthesize number = _number;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    _number.text = @"0";
    NSLog(@"number is %@",_number.text);
}

- (void)viewDidUnload
{
    [_number release];
    _number = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

- (void)dealloc {
    [_number release];
    [super dealloc];
}
- (IBAction)addOne:(UIButton *)sender {
    int i = [[[NSNumberFormatter alloc]numberFromString:self.number.text]autorelease].intValue + 1;
    self.number.text = [NSString stringWithFormat:@"%d",i];
}
@end

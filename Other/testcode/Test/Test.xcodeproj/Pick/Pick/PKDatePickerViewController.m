//
//  PKDatePickerViewController.m
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PKDatePickerViewController.h"

@interface PKDatePickerViewController ()

@end

@implementation PKDatePickerViewController
@synthesize datePicker = _datePicker;

#pragma -mark
#pragma mark vc lifecycle
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
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [_datePicker release];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma -mark
#pragma mark action

- (void)buttonPressed {
//    NSTimeZone *tzGMT = [NSTimeZone systemTimeZone]; 
//    [NSTimeZone setDefaultTimeZone:tzGMT];

    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd_HH:mm:ss"];
    NSString *na =[dateFormatter stringFromDate:_datePicker.date];

    
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"date" message:na delegate:nil cancelButtonTitle:@"cancel" otherButtonTitles:nil]autorelease];
    
    [alert show];
}

@end

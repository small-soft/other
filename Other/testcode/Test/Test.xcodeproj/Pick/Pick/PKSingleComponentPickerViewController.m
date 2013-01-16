//
//  PKSingleComponentPickerViewController.m
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PKSingleComponentPickerViewController.h"

@interface PKSingleComponentPickerViewController ()

@end

@implementation PKSingleComponentPickerViewController
@synthesize pickerData = _pickerData;
@synthesize singlePicker = _singlePicker;

#pragma - mark
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
    
    NSArray *array = [NSArray arrayWithObjects:@"a",@"b",@"c",@"d",@"e",@"f",@"g",@"h", nil];
    
    self.pickerData = array;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma - mark
#pragma mark vc action
- (void)buttonPressed {
    NSInteger row = [self.singlePicker selectedRowInComponent:0];
    NSString *selected = [self.pickerData objectAtIndex:row];
    NSString *title = [NSString stringWithFormat:@"You selected %@!",selected];
    
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:title message:@"thanks for choosing" delegate:nil cancelButtonTitle:@"cancel" otherButtonTitles: nil]autorelease];
    
    [alert show];
                        
}


#pragma - mark
#pragma mark for UIPickerViewDataSource
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
    
}

-(NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return [self.pickerData count];
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    return [self.pickerData objectAtIndex:row];
}

@end

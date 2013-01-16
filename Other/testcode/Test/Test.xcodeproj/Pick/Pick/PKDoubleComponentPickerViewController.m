//
//  PKDoubleComponentPickerViewController.m
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PKDoubleComponentPickerViewController.h"

@interface PKDoubleComponentPickerViewController ()

@end

@implementation PKDoubleComponentPickerViewController
@synthesize doublePicker  = _doublePiker;
@synthesize fillingTypes = _fillingTypes;
@synthesize breadTypes = _breadTypes;


#pragma - mark
#pragma mark vc lifeCycle
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
    
    self.breadTypes = [NSArray arrayWithObjects:@"White",@"Whole Wheat",@"Rye",@"Sourdough",@"Seven Grain", nil];
    self.fillingTypes = [NSArray arrayWithObjects:@"Ham",@"Turkey",@"Peanut Butter",@"Tuna Salad",@"Chicken Salad",@"Roast Reef",@"Vegemite", nil];
    
    NSLog(@"=====%@",_fillingTypes);
    NSLog(@"=====%@",self.fillingTypes);
    
}

- (void)viewDidUnload
{
    [_fillingTypes release];
    [_breadTypes release];
    [_doublePiker release];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma - mark
#pragma mark action
- (void)buttonPressed {
    NSInteger breadRow = [_doublePiker selectedRowInComponent:kBreadComponent];
    NSInteger fillingRow = [_doublePiker selectedRowInComponent:kFillingComponent];
    
    NSString *bread = [_breadTypes objectAtIndex:breadRow];
    NSString *filling = [_fillingTypes objectAtIndex:fillingRow];
    
    NSString *title = [NSString stringWithFormat:@"Your %@ on %@ bread will be right up.",filling,bread];
    
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:title message:@"thanks for order" delegate:nil cancelButtonTitle:@"great" otherButtonTitles: nil]autorelease];
    
    [alert show];
}

#pragma - mark
#pragma mark for UIPickerViewDataSource
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 2;
}

-(NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    NSLog(@"=======%@",self.fillingTypes);
    NSLog(@"=======%@",_fillingTypes);
    switch (component) {
        case kBreadComponent:
            return [_breadTypes count];
            break;  
            
        default:
            return [self.fillingTypes count];
            break;
    }
}

#pragma - mark
#pragma mark for picker delegate
-(NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    switch (component) {
        case kBreadComponent:
            return [_breadTypes objectAtIndex:row];
            break;
            
        default:
            return [_fillingTypes objectAtIndex:row];
            break;
    }
}

@end

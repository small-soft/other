//
//  PKDependentComponentPickerViewController.m
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PKDependentComponentPickerViewController.h"

@interface PKDependentComponentPickerViewController ()

@end

@implementation PKDependentComponentPickerViewController
@synthesize picker = _picker;
@synthesize states = _states;
@synthesize stateZips = _stateZips;
@synthesize zips = _zips;


#pragma - mark
#pragma mark vc lifecycele
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
    
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *plishPath = [bundle pathForResource:@"statedictionary" ofType:@"plist"];
    
    self.stateZips = [NSDictionary dictionaryWithContentsOfFile:plishPath];
    
    self.states = [[self.stateZips allKeys] sortedArrayUsingSelector:@selector(compare:)];
    
    self.zips = [self.stateZips objectForKey:[self.states objectAtIndex:0]];
}

- (void)viewDidUnload
{
    self.picker = nil;
    self.stateZips = nil;
    self.zips = nil;
    self.states = nil;
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
    NSInteger stateRow = [self.picker selectedRowInComponent:kStateComponent];
    NSInteger zipRow = [self.picker selectedRowInComponent:kZipComponent];
    
    NSString *state = [self.states objectAtIndex:stateRow];
    NSString *zip = [self.zips objectAtIndex:zipRow];
    
    NSString *title = [NSString stringWithFormat:@"You selected zip cod %@",zip];
    NSString *message = [NSString stringWithFormat:@"%@ is in %@",zip,state];
    
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:title message:message delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil]autorelease];
    
    [alert show];
}

#pragma - mark
#pragma mark picker data source method
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 2;
    
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return (component == kStateComponent)?[self.states count]:[self.zips count];
}

#pragma - mark
#pragma mark picker delegate method
- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    
    return (component == kStateComponent)?[self.states objectAtIndex:row]:[self.zips objectAtIndex:row];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    if (component == kStateComponent) {
        NSString *selectedState = [self.states objectAtIndex:row];
        self.zips = [self.stateZips objectForKey:selectedState];
        
        [self.picker selectRow:0 inComponent:kZipComponent animated:YES];
        [self.picker reloadComponent:kZipComponent];
    }
}

// 设置每列的宽度
- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component {
    return component == kZipComponent ? 90:200;
}
            
            

@end

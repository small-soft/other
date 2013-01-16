//
//  QFViewController.m
//  QuartzFun
//
//  Created by 佳 刘 on 12-10-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "QFViewController.h"
#import "QFQuartzFunView.h"
#import "Constants.h"

@interface QFViewController ()

@end

@implementation QFViewController
@synthesize colorControl;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [colorControl release];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

#pragma mark -
#pragma mark actions
- (void)changeColor:(id)sender {
    UISegmentedControl *control = sender;
    NSInteger index = control.selectedSegmentIndex;
    
    QFQuartzFunView *view = (QFQuartzFunView *)self.view;
    
    switch (index) {
        case kRedColorTab:
            view.currentColor = [UIColor redColor];
            view.useRandomColor = NO;
            break;
        case kBlueColorTab:
            view.currentColor = [UIColor blueColor];
            view.useRandomColor = NO;
            break;
        case kYellowColorTab:
            view.currentColor = [UIColor yellowColor];
            view.useRandomColor = NO;
            break;
        case kGreenColorTab:
            view.currentColor = [UIColor greenColor];
            view.useRandomColor = NO;
            break;
        case kRandomColorTab:
            view.useRandomColor = YES;
            break;
        default:
            break;
    }
}

-(void)changeShape:(id)sender {
    UISegmentedControl *cotrol = sender;
    [(QFQuartzFunView *)self.view setShapeType:[cotrol selectedSegmentIndex]];
    
    if (cotrol.selectedSegmentIndex == kImageShape) {
        colorControl.hidden = YES;
    }else {
        colorControl.hidden = NO;
    }
    
}

@end

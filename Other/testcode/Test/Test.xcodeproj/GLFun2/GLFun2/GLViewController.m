//
//  GLViewController.m
//  GLFun2
//
//  Created by 佳 刘 on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GLViewController.h"
#import "QFGLFunView.h"

@interface GLViewController ()

@end

@implementation GLViewController

@synthesize colorControl;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    self.colorControl = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}


#pragma mark -
#pragma mark actions
-(void)changeColor:(id)sender {
    UISegmentedControl *control = sender;
    NSInteger index = control.selectedSegmentIndex;
    
    QFGLFunView *glView = (QFGLFunView *)self.view;
    
    switch (index) {
        case kRedColorTab:
            glView.currentColor = [UIColor redColor];
            glView.useRandomColor = NO;
            break;
        case kBlueColorTab:
            glView.currentColor = [UIColor blueColor];
            glView.useRandomColor = NO;
            break;
        case kYellowColorTab:
            glView.currentColor = [UIColor yellowColor];
            glView.useRandomColor = NO;
            break;
        case kGreenColorTab:
            glView.currentColor = [UIColor greenColor];
            glView.useRandomColor = NO;
            break;
        case kRandomColorTab:
            glView.useRandomColor = YES;
            break;
        default:
            break;
    }
    
}

-(void)changeShape:(id)sender {
    UISegmentedControl *control = sender;
    [(QFGLFunView *)self.view setShapeType:control.selectedSegmentIndex];
    
    if ([control selectedSegmentIndex] == kImageShape) {
        colorControl.hidden = YES;
    }else {
        colorControl.hidden = NO;
    }
}

@end

//
//  CPViewController.m
//  CheckPlease
//
//  Created by 佳 刘 on 12-10-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CPViewController.h"
#import "CGPointUtils.h"

@interface CPViewController ()

@end

@implementation CPViewController
@synthesize label;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    self.label = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

#pragma mark -
#pragma mark actions
-(void)eraseLabel {
    label.text = @"";
}

#pragma mark -
#pragma mark touch event
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self.view];
    lastPrePoint = point;
    lastCurrentPoint = point;
    lineLengthSoFar = 0.f;
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint prePoint = [touch previousLocationInView:self.view];
    CGPoint currentPoint = [touch locationInView:self.view];
    CGFloat angle = angleBetweenLines(lastPrePoint, lastCurrentPoint, prePoint, currentPoint);
    
    if (angle >= kMinCheckMarkAngle && angle <=kMaxCheckMarkAngle && lineLengthSoFar > kMinCheckMarkLength) {
        label.text = @"Checkmark";
        [self performSelector:@selector(eraseLabel) withObject:nil afterDelay:1.6];
    }
    
    lineLengthSoFar += distanceBetweenPoints(prePoint, currentPoint);
    lastPrePoint = prePoint;
    lastCurrentPoint = currentPoint;
}
@end

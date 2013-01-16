//
//  SViewController.m
//  Swipes
//
//  Created by 佳 刘 on 12-10-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SViewController.h"

@interface SViewController ()

@end

@implementation SViewController
@synthesize label;
@synthesize gestureStartPoint;

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
- (void)eraseText {
    label.text = @"";
}

#pragma mark -
#pragma mark touch event
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    gestureStartPoint = [touch locationInView:self.view];
}

//- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
//    UITouch *touch = [touches anyObject];
//    CGPoint currentPosition = [touch locationInView:self.view];
//    
//    CGFloat deltaX = fabsf(gestureStartPoint.x - currentPosition.x);
//    CGFloat deltaY = fabsf(gestureStartPoint.y - currentPosition.y);
//    
//    if (deltaX >= kMinGestureLength && deltaY <= kMaxVariance) {
//        label.text = @"horizontal swipe detected";
//        [self performSelector:@selector(eraseText) withObject:nil afterDelay:2];
//    }else if (deltaY >= kMinGestureLength && deltaX <= kMaxVariance) {
//        label.text = @"vertical swipe detected";
//        [self performSelector:@selector(eraseText) withObject:nil afterDelay:2];
//    }
//}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    SwipeType swipeType = kNoSwipe;
    for (UITouch *touch in touches) {
        CGPoint currentPosition = [touch locationInView:self.view];
        
        CGFloat deltaX = fabsf(currentPosition.x - gestureStartPoint.x);
        CGFloat deltaY = fabsf(currentPosition.y - gestureStartPoint.y);
        
        if (deltaX >= kMinGestureLength && deltaY <= kMaxVariance) {
            swipeType = kHorizontalSwipe;
        } else if (deltaY >= kMinGestureLength && deltaX <= kMinGestureLength) {
            swipeType = kVerticalSwipe;
        }
    }
    
    BOOL allFingersFarEnoughAway = YES;
    if (swipeType != kNoSwipe) {
        for(UITouch *touch in touches) {
            CGPoint currentPosition = [touch locationInView:self.view];
            
            CGFloat distance;
            
            if(swipeType == kHorizontalSwipe) {
                distance = fabsf(currentPosition.x - gestureStartPoint.x);
            }else {
                distance = fabsf(currentPosition.y - gestureStartPoint.y);
            }
            
            if(distance <= kMinGestureLength) {
                allFingersFarEnoughAway = NO;
            }
        }
        
    }
    
    if(allFingersFarEnoughAway && swipeType!=kNoSwipe) {
        NSString *swipeCountString = nil;
        if([touches count]==2){
            swipeCountString = @"Double";
        }else if([touches count]==3){
            swipeCountString = @"tiple";
        }else if([touches count]==4){
            swipeCountString = @"quadruple";
        }else if([touches count]==5){
            swipeCountString = @"quintuple";
        }else {
            swipeCountString = @"";
        }
        
        NSString *swipeTypeString = (swipeType == kHorizontalSwipe)?@"Horizontal":@"Vertical";
        
        label.text = [NSString stringWithFormat:@"%@ %@ swipe detected.",swipeCountString,swipeTypeString];
        
        [self performSelector:@selector(eraseText) withObject:nil afterDelay:2];
    }
}

@end

//
//  FaceKeyboardView.m
//  FaceKeyboard
//
//  Created by chen littlejie on 10-6-26.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FaceKeyboardView.h"


@implementation FaceKeyboardView

#define sceneW					320
#define sceneH					480

#define scaleBigSize			1.5f
#define scaleSize				1.2f

@synthesize kDelegate,kDataSources;

- (id) init{
	
	keyBoardWidth = 320;
	keyBoardHeight = 215;
	
	self = [super initWithFrame:CGRectMake(0, 0, keyBoardWidth, keyBoardHeight)];

	if (self != nil) {
		faceView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, keyBoardWidth, keyBoardHeight)];
		NSArray* nibViews =  [[NSBundle mainBundle] loadNibNamed:@"FaceKeyboardView" owner:self options:nil];
		maxViews = [nibViews count];
			
		for (int i = 0; i < maxViews; i++) {
			FaceItemView *subView = [nibViews objectAtIndex:i];
			subView.center = CGPointMake(keyBoardWidth*i + keyBoardWidth/2, keyBoardHeight/2);
			[faceView addSubview:subView];
		}
		///config scroll view
		faceView.contentSize = CGSizeMake(keyBoardWidth*maxViews, keyBoardHeight);
		faceView.pagingEnabled = YES;
		faceView.showsHorizontalScrollIndicator = NO;
		faceView.showsVerticalScrollIndicator = NO;
		faceView.scrollsToTop = NO;
		
		faceView.alwaysBounceVertical = YES;
		faceView.alwaysBounceHorizontal = YES;
		faceView.bounces = NO;
        
        
        
		
		keyboard_icon = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"facekeyboard_icon.png"]];
		[keyboard_icon setHidden:YES];
		
        faceView.delegate = self;
		[self addSubview:faceView];
	
        
        pageControl = [[AliPageControl alloc] init];
        pageControl.frame = CGRectMake(0, 181, 320, 36);
        pageControl.backgroundColor = [UIColor clearColor];
        pageControl.userInteractionEnabled = NO;
        pageControl.currentPage = 0;
        pageControl.numberOfPages = maxViews;

        [self addSubview:pageControl];
	}
	return self;
}



- (void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView  
{  
    int index = fabs(scrollView.contentOffset.x)/self.frame.size.width;  
    pageControl.currentPage = index;  
}  

- (void) showKeyBoard:(UITextField *)_textField{
    [self scrollViewDidEndDecelerating:faceView];
		
	[_textField becomeFirstResponder];
	
	///插入至键盘前
	NSArray *windows = [[UIApplication sharedApplication] windows];
	if (windows == nil) {
		return;
	}
	if ([windows count] < 2) {
		return;
	}
	UIWindow* tempWindow = [windows objectAtIndex:1];
	NSArray *ary = tempWindow.subviews;
	if (ary == nil) {
		return;
	}
	if ([ary count] <= 0) {
		return;
	}
	///插入前先删除
	[self removeFromSuperview];
	[tempWindow addSubview:self];
	
	[keyboard_icon removeFromSuperview];
	[tempWindow addSubview:keyboard_icon];
	
	myBoardView = [ary objectAtIndex:0];
	
	self.center = CGPointMake(sceneW/2 , sceneH);
//	myBoardView.center = CGPointMake(sceneW/2, sceneH - self.bounds.size.height/2);
	///动画显示
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.2f];
	self.center = CGPointMake(sceneW/2, sceneH - self.bounds.size.height/2);
//	myBoardView.center = CGPointMake(-sceneW/2, sceneH - self.bounds.size.height/2);
	[UIView commitAnimations];
	[self setNeedsDisplay];
}

- (void) reKeyBoard{
    
    
 //   myBoardView.center = CGPointMake(sceneW/2, sceneH - self.bounds.size.height/2);
	///动画显示
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.2f];
	self.center = CGPointMake(sceneW/2, sceneH +self.bounds.size.height/2);
	//myBoardView.center = CGPointMake(sceneW/2, sceneH - self.bounds.size.height/2);
	[UIView commitAnimations];
    
    [self setNeedsDisplay];
}

- (void) hideKeyBoard{
//	self.center = CGPointMake(self.center.x, sceneH - self.bounds.size.height/2);
//	myBoardView.center = CGPointMake(sceneW/2, sceneH - self.bounds.size.height/2);
//	[UIView beginAnimations:nil context:nil];
//	[UIView setAnimationDuration:0.3f];
	self.center = CGPointMake(self.center.x, sceneH + self.bounds.size.height/2);
//	myBoardView.center = CGPointMake(myBoardView.center.x, sceneH + self.bounds.size.height/2);
//	[UIView commitAnimations];
}


- (void)dealloc {
    [pageControl release];
    
	[myBoardView release];
	[faceView release];
	[keyboard_icon release];
//	[keyboard_icon_image release];
    [super dealloc];
}

#pragma mark -
#pragma mark delegate
- (void) onRelease:(id)_sender{
	NSMutableDictionary *data = (NSMutableDictionary *)_sender;
	UITouch *touch = [data objectForKey:@"touch"];
	FaceItemButton *button = [data objectForKey:@"button"];
    CGPoint currentTouchPosition = [touch locationInView:touch.window];
	keyboard_icon.center = CGPointMake(currentTouchPosition.x,currentTouchPosition.y - button.bounds.size.height);

	keyboard_icon.alpha = 1.f;
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.35f];
	keyboard_icon.alpha = 0.f;
	keyboard_icon.center = CGPointMake(currentTouchPosition.x,currentTouchPosition.y - button.bounds.size.height*2);
	[UIView commitAnimations];
	
	[keyboard_icon setHidden:YES];
	[kDelegate onReturnKeyboardInput:button.titleLabel.text];
}

- (void) onPresses:(id)_sender{
	
	NSMutableDictionary *data = (NSMutableDictionary *)_sender;
	UITouch *touch = [data objectForKey:@"touch"];
	FaceItemButton *button = [data objectForKey:@"button"];
    CGPoint currentTouchPosition = [touch locationInView:touch.window];
	
	[keyboard_icon setHidden:NO];
	
	keyboard_icon.alpha = 1.f;
	keyboard_icon.center = CGPointMake(currentTouchPosition.x,currentTouchPosition.y - button.bounds.size.height);
//	if (keyboard_icon_image != nil) {
//		[keyboard_icon_image removeFromSuperview];
//		[keyboard_icon_image release];
//	}
	
	UIImageView *keyboard_icon_image = [[UIImageView alloc] initWithImage:button.imageView.image];
	[keyboard_icon addSubview:keyboard_icon_image];
	
	
	kRectIcon = keyboard_icon.bounds;
	kRectImage = keyboard_icon_image.bounds;
	
	keyboard_icon_image.bounds = CGRectMake(0, 0, 10, 10);
	keyboard_icon_image.center = CGPointMake(kRectIcon.size.width/2 - 2, kRectIcon.size.height/2 - 2);
	
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.2f];
//	[UIView setAnimationDelegate:self];
//	[UIView setAnimationDidStopSelector:@selector(scaleKeyboardIcon:)];
	keyboard_icon_image.bounds = CGRectMake(0, 0, kRectImage.size.width*scaleBigSize, kRectImage.size.height*scaleBigSize);
	[UIView commitAnimations];
	
	[keyboard_icon_image release];
}


//- (void) scaleKeyboardIcon:(id)_sender{
//	if (keyboard_icon_image != nil) {
//		[UIView beginAnimations:nil context:nil];
//		[UIView setAnimationDuration:0.2f];
//		keyboard_icon_image.bounds = CGRectMake(0, 0, kRectImage.size.width*scaleSize, kRectImage.size.height*scaleSize);
//		[UIView commitAnimations];
//	}
//}

- (void) onDrag:(id)_sender{
	NSMutableDictionary *data = (NSMutableDictionary *)_sender;
	UITouch *touch = [data objectForKey:@"touch"];
	FaceItemButton *button = [data objectForKey:@"button"];
    CGPoint currentTouchPosition = [touch locationInView:touch.window];
	keyboard_icon.center = CGPointMake(currentTouchPosition.x,currentTouchPosition.y - button.bounds.size.height);

}

- (void) onReleaseOutSide:(id)_sender{
	[keyboard_icon setHidden:YES];
}

- (void) onReturnKeyboardInput:(NSString *)_str{
	
}

@end

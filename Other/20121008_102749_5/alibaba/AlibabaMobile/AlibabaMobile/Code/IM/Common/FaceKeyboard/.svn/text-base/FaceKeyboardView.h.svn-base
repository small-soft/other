//
//  FaceKeyboardView.h
//  FaceKeyboard
//
//  Created by chen littlejie on 10-6-26.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "FaceItemView.h"

#import "FaceKeyboardDelegate.h"
#import "AliPageControl.h"


@interface FaceKeyboardView : UIView <FaceKeyboardDelegate, UIScrollViewDelegate>{
	
	id <FaceKeyboardDelegate> kDelegate;
	id <FaceKeyboardDataSources> kDataSources;
	
	UIView *myBoardView;
    AliPageControl * pageControl;
    UIScrollView *faceView;
	
//	UIScrollView *faceView;
//	UIImageView *keyboard_icon, *keyboard_icon_image;
	UIImageView *keyboard_icon;
	int maxViews;
	
	CGRect kRectIcon,kRectImage;
	
	float keyBoardWidth,keyBoardHeight,buttonBarHight;

}

@property (nonatomic,assign) id <FaceKeyboardDelegate> kDelegate;
@property (nonatomic,assign) id <FaceKeyboardDataSources> kDataSources;

- (void) showKeyBoard:(UITextField *)_textField;
- (void) reKeyBoard;
- (void) hideKeyBoard;


//- (void) scaleKeyboardIcon:(id)_sender;

@end

//
//  FaceItemButton.h
//  FaceKeyboard
//
//  Created by chen littlejie on 10-6-28.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FaceKeyboardDelegate.h"

@interface FaceItemButton : UIButton{
	id <FaceItemButtonDelegate> delegate;
}

@property (nonatomic,assign) id <FaceItemButtonDelegate> delegate;

- (void) selfOnPress:(id)_sender;
- (void) selfOnDrag:(id)_sender;
- (void) selfOnRelease:(id)_sender;
- (void) selfOnReleaseOutSide:(id)_sender;

@end

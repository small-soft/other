//
//  FaceItemView.h
//  FaceKeyboard
//
//  Created by chen littlejie on 10-6-28.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FaceItemButton.h"

@interface FaceItemView : UIView <FaceItemButtonDelegate>{
	IBOutlet UIImageView *bgImageView;
	IBOutlet UIView *faceItemsView;
	
	id <FaceItemButtonDelegate> delegate;
}

@property (nonatomic,retain) IBOutlet UIImageView *bgImageView;
@property (nonatomic,retain) IBOutlet UIView *faceItemsView;
@property (nonatomic,assign) id <FaceItemButtonDelegate> delegate;

@end

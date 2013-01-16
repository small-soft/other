//
//  FaceItemView.m
//  FaceKeyboard
//
//  Created by chen littlejie on 10-6-28.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FaceItemView.h"


@implementation FaceItemView

@synthesize bgImageView,faceItemsView,delegate;


- (void)awakeFromNib
{
	NSArray *views = [faceItemsView subviews];
	int viewsMax = [views count];
	for (int i = 0; i < viewsMax; i ++) {
		FaceItemButton *itemButton = [views objectAtIndex:i];
		itemButton.delegate = self;
	}
}

- (void)dealloc {
	[faceItemsView release];
	[bgImageView release];
    [super dealloc];
}


#pragma mark -
#pragma mark delegate

- (void) onRelease:(id)_sender{
	[delegate onRelease:_sender];
}

- (void) onPresses:(id)_sender{
	[delegate onPresses:_sender];
}

- (void) onDrag:(id)_sender{
	[delegate onDrag:_sender];
}

- (void) onReleaseOutSide:(id)_sender{
	[delegate onReleaseOutSide:_sender];
}

@end

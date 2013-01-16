//
//  FaceItemButton.m
//  FaceKeyboard
//
//  Created by chen littlejie on 10-6-28.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FaceItemButton.h"


@implementation FaceItemButton

@synthesize delegate;

//- (void)awakeFromNib
//{
//	[self addTarget:self action:@selector(selfOnPress:) forControlEvents:UIControlEventTouchDown];
//	[self addTarget:self action:@selector(selfOnDrag:) forControlEvents:UIControlEventTouchDragEnter];
//	[self addTarget:self action:@selector(selfOnRelease:) forControlEvents:UIControlEventTouchUpInside];
//	[self addTarget:self action:@selector(selfOnReleaseOutSide:) forControlEvents:UIControlEventTouchUpOutside];
//}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
	UITouch *touch = touches.anyObject;
	NSMutableDictionary *data = [[[NSMutableDictionary alloc] init] autorelease];
	[data setObject:touch forKey:@"touch"];
	[data setObject:self forKey:@"button"];
	[delegate onPresses:data];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
	UITouch *touch = touches.anyObject;
	NSMutableDictionary *data = [[[NSMutableDictionary alloc] init] autorelease];
	[data setObject:touch forKey:@"touch"];
	[data setObject:self forKey:@"button"];
	[delegate onRelease:data];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
	UITouch *touch = touches.anyObject;
	NSMutableDictionary *data = [[[NSMutableDictionary alloc] init] autorelease];
	[data setObject:touch forKey:@"touch"];
	[data setObject:self forKey:@"button"];
	[delegate onDrag:data];
}

#pragma mark -
#pragma mark delegate

- (void) selfOnPress:(id)_sender{
	[delegate onPresses:self];
}

- (void) selfOnDrag:(id)_sender{
	[delegate onDrag:self];
}

- (void) selfOnRelease:(id)_sender{
	[delegate onRelease:self];
}

- (void) selfOnReleaseOutSide:(id)_sender{
	[delegate onReleaseOutSide:self];
}

@end

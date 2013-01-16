//
//  InternetDataTool.m
//  WangWang
//
//  Created by littlejie chan on 10-5-31.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "InternetDataTool.h"


@implementation InternetDataTool

@synthesize operationQueue,facesCharArray;

static InternetDataTool *interfaceObject;

#pragma mark -
#pragma mark init and destory
+ (InternetDataTool *)create{
	if (interfaceObject == nil) {
		interfaceObject = [[InternetDataTool alloc] init];
	}
	return interfaceObject;
}

+ (void)destoryObject{
	if (interfaceObject != nil) {
		[interfaceObject release];
	}
}

- (id) init
{
	self = [super init];
	if (self != nil) {
		operationQueue = [[NSOperationQueue alloc] init];
		[operationQueue setMaxConcurrentOperationCount:1];
		facesCharArray = [[NSMutableArray alloc] init];
		
		NSArray* nibViews =  [[NSBundle mainBundle] loadNibNamed:@"FaceKeyboardView" owner:self options:nil];
		int maxViews = [nibViews count];
		for (int i = 0; i < maxViews; i++) {
			FaceItemView *subView = [nibViews objectAtIndex:i];
			NSArray *subItems = [subView.faceItemsView subviews];
			int subItemsMax = [subItems count];
			for (int j = 0; j < subItemsMax; j ++) {
				FaceItemButton *tmpButton = [subItems objectAtIndex:j];
				NSRange r = {0,1};
                
                NSString * imagePath =tmpButton.titleLabel.text;
                TextViewExItem *item = [[[TextViewExItem alloc] init:imagePath range:r] autorelease];
                
				NSString *tmpImgPath = [NSString stringWithFormat:@"000%d.png",tmpButton.tag];
				NSRange range;
				range.length = 7;
				range.location = [tmpImgPath length] - range.length;
				
				item.iconPath = [tmpImgPath substringWithRange:range];
				[facesCharArray addObject:item];
			}
		}
		
	}
	return self;
}

- (void) dealloc {
	[operationQueue release];
	[facesCharArray release];
	[super dealloc];
}
@end

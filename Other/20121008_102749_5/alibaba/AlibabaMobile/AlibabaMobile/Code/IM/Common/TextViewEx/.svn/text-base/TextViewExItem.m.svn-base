//
//  TextViewExItem.m
//  WangWang
//
//  Created by JerryChan on 10-6-30.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "TextViewExItem.h"


@implementation TextViewExItem

@synthesize imagePath,range,iconPath;

- (id) init:(NSString *)_imagePath range:(NSRange)_range{
    if ((self = [super init])) {
		imagePath = [[NSString alloc] initWithString:_imagePath];
		range = _range;
    }
    return self;
}

- (void)dealloc {
	[iconPath release];
	[imagePath release];
    [super dealloc];
}


@end

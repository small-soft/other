//
//  NoticationItem.m
//  WangWang
//
//  Created by littlejie chan on 10-6-4.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "NoticationItem.h"


@implementation NoticationItem

@synthesize errorCode,data,name;

- (id) init
{
	self = [super init];
	if (self != nil) {
		data = [[NSMutableDictionary alloc] init];
	}
	return self;
}


- (void) dealloc
{
	if (data != nil) {
		[data release];
	}
	
	if (name != nil) {
		[name release];
	}
	
	[super dealloc];
}


@end

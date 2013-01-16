//
//  NetworkNotReachException.m
//  myCuisine
//
//  Created by John Chen on 09-10-9.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "InterfaceCommandException.h"


@implementation InterfaceCommandException

-(id)initWithReason:(NSString *)reason userInfo:(NSDictionary *)userInfo{
	
	self = [super initWithName:@"NetworkNotReachException" reason:reason userInfo:userInfo];
	return self;
}

+(InterfaceCommandException *)exceptionWithReason:(NSString *)reason userInfo:(NSDictionary *)userInfo{
	
	InterfaceCommandException *e = [[InterfaceCommandException alloc] initWithReason:reason userInfo:userInfo];
	return [e autorelease];
}

@end

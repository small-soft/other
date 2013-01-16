//
//  AMPrecisionVisitorAccessLogDetail.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitorAccessLogDetail.h"

@implementation AMPrecisionVisitorAccessLogDetail

@synthesize title = _title;
@synthesize browseCount = _browseCount; //int
@synthesize stayTime = _stayTime;
@synthesize openTime = _openTime;
@synthesize isPageClose = _isPageClose;
@synthesize url = _url;
@synthesize stayMilliSeconds = _stayMilliSeconds; //long

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionVisitorAccessLogDetail class]] retain];

            [sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];
            [sharedObjectMapping mapKeyPath:@"browseCount" toAttribute:@"browseCount"];
            [sharedObjectMapping mapKeyPath:@"stayTime" toAttribute:@"stayTime"];
            [sharedObjectMapping mapKeyPath:@"openTime" toAttribute:@"openTime"];
            [sharedObjectMapping mapKeyPath:@"isPageClose" toAttribute:@"isPageClose"];
            [sharedObjectMapping mapKeyPath:@"url" toAttribute:@"url"];
            [sharedObjectMapping mapKeyPath:@"stayMilliSeconds" toAttribute:@"stayMilliSeconds"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_title release];
    [_browseCount release];
    [_stayTime release];
    [_openTime release];
    [_isPageClose release];
    [_url release];
    [_stayMilliSeconds release];
    [super dealloc];
}

@end
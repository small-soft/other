//
//  AMImage.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//询盘管理-推荐客户列表的图片
#import "AMCustomerImage.h"
#import <RestKit/RestKit.h>

@implementation AMCustomerImage

@synthesize mobileImageURI = _mobileImageURI;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCustomerImage class]] retain];
            [sharedObjectMapping mapKeyPath:@"mobileImageURI" toAttribute:@"mobileImageURI"];
        }
    }
    return sharedObjectMapping;
}

- (void) dealloc {
    [_mobileImageURI release];
    [super dealloc];
}

@end

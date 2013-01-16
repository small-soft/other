//
//  AMHomepageDressEvent1.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMHomepageDressEvent1.h"

@implementation AMHomepageDressEvent1
@synthesize md5Checksum = _md5Checksum;
@synthesize type = _type;
@synthesize updated = _updated;
@synthesize imageUrl = _imageUrl;
@synthesize hasChild= _hasChild;
@synthesize description = _description;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHomepageDressEvent1 class]] retain];
			[sharedObjectMapping mapKeyPath:@"md5Checksum" toAttribute:@"md5Checksum"];
            [sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
            [sharedObjectMapping mapKeyPath:@"updated" toAttribute:@"updated"];
            [sharedObjectMapping mapKeyPath:@"hasChild" toAttribute:@"hasChild"];
            [sharedObjectMapping mapKeyPath:@"imageUrl" toAttribute:@"imageUrl"];
            [sharedObjectMapping mapKeyPath:@"description" toAttribute:@"description"];
            
                
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_md5Checksum release];
    [_type release];
    [_imageUrl release];
    [_description release];
    
    [super dealloc];
}
@end



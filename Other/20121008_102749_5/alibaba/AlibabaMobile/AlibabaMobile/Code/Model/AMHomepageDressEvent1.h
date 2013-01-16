//
//  AMHomepageDressEvent1.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMHomepageDressEvent1 : NSObject<AMObjectMappingDelegate> 
{
    
}

@property(nonatomic, retain) NSString *md5Checksum;
@property(nonatomic, retain) NSString *type;
@property(nonatomic, retain) NSString *imageUrl;
@property(nonatomic, assign) BOOL updated;
@property(nonatomic, assign) BOOL hasChild;
@property(nonatomic, retain) NSString *description;


@end
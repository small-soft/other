//
//  AMHomepageDressBanner.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMHomepageDressBanner : NSObject<AMObjectMappingDelegate> 
{
    
}

@property(nonatomic, retain) NSString *md5Checksum;
@property(nonatomic, retain) NSString *type;
@property(nonatomic, assign) BOOL updated;
@property(nonatomic, assign) BOOL hasChild;
@property(nonatomic, retain) NSArray *children;

@end

@class AMHomepageDressChildenJumpPath;
@interface AMHomepageDressChilden : NSObject<AMObjectMappingDelegate> 
{
    
}

@property(nonatomic, retain) AMHomepageDressChildenJumpPath *jumpPath;
@property(nonatomic, retain) NSString *imageUrl;
@property(nonatomic, retain) NSString *ID;
@property(nonatomic, retain) NSString *type;
@property(nonatomic, retain) NSString *name;
@property(nonatomic, assign) BOOL hasChild;
@property(nonatomic, retain) NSString *clickId;

@end
@class AMHomepageDressChildenParams;
@interface AMHomepageDressChildenJumpPath : NSObject<AMObjectMappingDelegate> 
{
    
}

@property(nonatomic, retain) NSString *busiType;
@property(nonatomic, retain) NSString *pageId;
@property(nonatomic, retain) NSString *type;
@property(nonatomic, retain) AMHomepageDressChildenParams *params;

@end

@interface AMHomepageDressChildenParams : NSObject<AMObjectMappingDelegate> 
{
    
}

@property(nonatomic, retain) NSString *entry_url;
@property(nonatomic, retain) NSString *pictureNewsId;


@end


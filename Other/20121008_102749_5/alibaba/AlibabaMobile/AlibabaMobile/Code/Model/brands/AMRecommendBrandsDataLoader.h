//
//  AMRecommendBrandsDataLoader.h
//  AlibabaMobile
//
//  Created by 佳 刘 on 12-9-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import "AliChannel.h"

@class AMHomepageDressRequest;
@class AMMenuView;

@interface AMRecommendBrandsDataLoader : NSObject<RKObjectLoaderDelegate>
@property (nonatomic,assign) id <AliChannelDelegate> delegate;
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) NSString *md5Checksum;
@property (nonatomic,retain) AMHomepageDressRequest *request;
@property (nonatomic,retain) NSString *imgUrl;
@property (nonatomic,retain) AMMenuView *menuView;

- (void)loadObjectsFromRemote;
@end
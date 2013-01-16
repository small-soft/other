//
//  AMChannel.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import "AliAdvView.h"
#import "AliChannel.h"
#import "AMHomepageDressRequest.h"

@class AMChannel;

@interface AMChannel : NSObject<RKObjectLoaderDelegate>
@property (nonatomic,assign) id <AliChannelDelegate> delegate;
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) NSString *md5Checksum;
@property (nonatomic,retain) AMHomepageDressRequest *request;

- (void)loadObjectsFromRemote;
@end

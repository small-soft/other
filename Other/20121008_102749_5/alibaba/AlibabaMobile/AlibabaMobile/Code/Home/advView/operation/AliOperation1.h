//
//  AliOperation1.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <RestKit/RestKit.h>
#import "AliAdvView.h"
#import "AMHomepageDressRequest.h"

@interface AliOperation1 : UIControl<RKObjectLoaderDelegate>
@property (nonatomic,assign) id <AliAdvViewDelegate> delegate;
@property (nonatomic,retain) NSString *md5Checksum;
@property (nonatomic,retain) AMHomepageDressRequest *request;
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) UIImageView *defaultImage;
@property (nonatomic,retain) UIImageView *maskImage;

- (void)loadObjectsFromRemote;
- (void)setHideImageUrl:(BOOL)hideImageUrl;

@end


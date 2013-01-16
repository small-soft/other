//
//  AMAdvView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliGallaryView.h"
#import "AliAdvView.h"
#import "AMHomepageDressRequest.h"

@interface AMAdvView : UIControl<RKObjectLoaderDelegate,AliGallaryViewDelegate>
@property (nonatomic,retain) NSMutableArray *bannerData;
@property (nonatomic,retain) NSObject <AliAdvViewDelegate> *delegate;
@property (nonatomic,retain) NSString *md5Checksum;
@property (nonatomic,retain) AMHomepageDressRequest *request;
@property (nonatomic,retain) UIView *blackView;
- (void)loadObjectsFromRemote;

@end

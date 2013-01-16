//
//  AMOperationView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliAdvView.h"
#import "AMHomepageDressRequest.h"
#import "HJManagedImageV.h"

@interface AMOperationView : UIControl<RKObjectLoaderDelegate>
{
}
@property (nonatomic,retain) HJManagedImageV *opertationView;
@property (nonatomic,assign) id <AliAdvViewDelegate> delegate;
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) NSString *md5Checksum;
@property (nonatomic,retain) AMHomepageDressRequest *request;
@property (nonatomic,retain) UIImageView *defaultImage;
@property (nonatomic,retain) UIImageView *maskImage;

- (void)loadObjectsFromRemote;
- (void)setHideImageUrl:(BOOL)hideImageUrl;

@end

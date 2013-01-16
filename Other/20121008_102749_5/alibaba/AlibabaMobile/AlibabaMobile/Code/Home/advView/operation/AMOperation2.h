//
//  AMOperation2.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-27.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <RestKit/RestKit.h>
#import "AliAdvView.h"

@interface AMOperation2 : UIControl<RKObjectLoaderDelegate>
@property (nonatomic,retain) NSObject <AliAdvViewDelegate> *delegate;
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) NSString *md5Checksum;
- (void)loadObjectsFromRemote;
@end

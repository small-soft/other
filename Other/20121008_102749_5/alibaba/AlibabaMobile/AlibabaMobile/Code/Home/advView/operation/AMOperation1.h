//
//  AMOperation1.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-27.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import "AliAdvView.h"


@interface AMOperation1 : UIControl<RKObjectLoaderDelegate>
@property (nonatomic,retain) NSObject <AliAdvViewDelegate> *delegate;
@property (nonatomic,retain) NSString *md5Checksum;
- (void)loadObjectsFromRemote;
@property (nonatomic,retain) NSMutableArray *contentData;
@end

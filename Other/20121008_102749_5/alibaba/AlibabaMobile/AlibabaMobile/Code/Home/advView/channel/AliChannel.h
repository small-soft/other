//
//  AliChannel.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import <RestKit/RestKit.h>
#import "AliAdvView.h"
@class AliChannel;
@protocol AliChannelDelegate <NSObject>
-(void)AliChannelReloadData;
@end

@interface AliChannel : NSObject<RKObjectLoaderDelegate>
@property (nonatomic,retain) NSObject <AliChannelDelegate> *delegate;
@property (nonatomic,retain) NSObject <AliAdvViewDelegate> *coltrollerDelegate;
@property (nonatomic,retain) NSMutableArray *contentData;
-(NSString*)getTitle:(NSUInteger)index;
-(void)doSelector:(NSUInteger)index;
- (void)loadObjectsFromRemote;
@end

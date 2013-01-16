//
//  WwStatePickView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WangWangNetLib/CommonDefs.h>

@protocol WwStatePickDelegate <NSObject>

- (void) statePicked:(int) state;

@end

@interface WwStatePickView : UIView

@property (nonatomic, retain) id<WwStatePickDelegate> delegate;
- (id) initWithState:(int)status;

@end

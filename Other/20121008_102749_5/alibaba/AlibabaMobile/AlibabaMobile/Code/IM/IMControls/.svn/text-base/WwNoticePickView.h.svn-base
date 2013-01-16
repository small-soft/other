//
//  WwNoticePickView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-4-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol WwNoticePickDelegate <NSObject>

- (void) noticePickedMusic:(bool)music shake:(bool)shake;

@end

@interface WwNoticePickView : UIView

@property (nonatomic, retain) id<WwNoticePickDelegate> delegate;

- (id) initWithMusic:(bool)music shake:(bool)shake;

@end

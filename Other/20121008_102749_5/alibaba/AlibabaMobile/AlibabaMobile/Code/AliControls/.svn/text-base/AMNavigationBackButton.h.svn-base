//
//  AMNavigationBackButton.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-25.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliNavigationBackButton.h"

//navigationbackbutton 回调函数
//navigationbackbutton 回调函数
@protocol AMNavigationBackDelegate <NSObject>

@required
- (void) navigationBack;

@end
@interface AMNavigationBackButton : UIBarButtonItem
{
}

@property (nonatomic, assign) id<AMNavigationBackDelegate> navigationBackDelegate;

- (id) initWithTitle:(NSString *)title;


@end
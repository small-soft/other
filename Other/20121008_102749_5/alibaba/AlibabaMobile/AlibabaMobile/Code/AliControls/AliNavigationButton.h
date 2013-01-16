//
//  BackButton.h
//  AlibabaMobile
//
//  Created by  xiejin on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

extern const int NAV_BTN_STYLE_COMMON;
extern const int NAV_BTN_STYLE_MAIN;

//navigationbackbutton 回调函数
@protocol AliNavigationButtonDelegate <NSObject>

@required
- (void) navigationButtonClick;

@end

@interface AliNavigationButton : UIBarButtonItem
{
}

@property (nonatomic, retain) id<AliNavigationButtonDelegate> navigationButtonDelegate;

- (id) initWithTitle:(NSString *)title style:(int)style;

@end


//
//  BackButton.h
//  AlibabaMobile
//
//  Created by  xiejin on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

//navigationbackbutton 回调函数
@protocol AliNavigationBackDelegate <NSObject>

@required
- (void) navigationBack;

@end

@interface AliNavigationBackButton : UIBarButtonItem
{
}

@property (nonatomic, retain) id<AliNavigationBackDelegate> navigationBackDelegate;

- (id) initWithTitle:(NSString *)title;


@end


//
//  AliButton.h
//  AlibabaMobile
//
//  Created by  on 12-2-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliNavigationButton.h"

@interface AliButton : UIButton
{
    id<AliNavigationButtonDelegate> _navigationBackDelegate;
}

@property (nonatomic, retain) id<AliNavigationButtonDelegate> navigationButtonDelegate;

- (id) initWithTitle:(NSString *)title;
- (IBAction) navigationBack;
- (void) setButtonImageNormal:(NSString *)normal pressed:(NSString *)pressed;
-(void) setTitle:(NSString *)title;

@end
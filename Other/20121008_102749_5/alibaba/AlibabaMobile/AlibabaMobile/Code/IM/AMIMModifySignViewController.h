//
//  AMIMModifySignViewController.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-14.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliBaseViewController.h"
#import "AliNavigationButton.h"
#import "AMIMUserModel.h"

@interface AMIMModifySignViewController : AliBaseViewController <AliNavigationButtonDelegate, UITextViewDelegate>

- (id)initWithUser:(NSString *)user;

@end

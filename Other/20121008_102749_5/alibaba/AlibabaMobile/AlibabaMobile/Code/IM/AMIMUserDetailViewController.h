//
//  AMIMUserDetailViewController.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-14.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliBaseViewController.h"
#import "AMIMUserModel.h"


const int USER_RELATION_SEFL = 0;
const int USER_RELATION_FRIEND = 1;
const int USER_RELATION_STRANGER = 2;
    


@class AMIMUser;

@interface AMIMUserDetailViewController : AliBaseViewController
- (id)initWithUser:(NSString *)userId relation:(int)relation;

@end

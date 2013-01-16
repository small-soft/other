//
//  AMCompanyDetailViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTabContentViewController.h"
#import "AMCompanyTabViewController.h"
#import "AliMemberContactView.h"


@class AMCompanyDetail;

@interface AMCompanyDetailViewController : AliTabContentViewController  < MemberContactDelegate>
{
    AMCompanyDetail * mCompanyDetail;
    BOOL isTalkAfterWwLogin;
}

@property (nonatomic, retain) IBOutlet UIScrollView * mMainScrollView;


- (void) initContentDataEx;
- (NSString *) getBizType:(NSString *) typeCode;

@end

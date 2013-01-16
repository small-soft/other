//
//  AMAbout.h
//  AlibabaMobile
//
//  Created by lih on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import <Foundation/Foundation.h>
#import "AliNavigationBackButton.h"

@interface AMAbout: UIViewController<AliNavigationBackDelegate>{
    BOOL updateAlertFirst ;
}

@property (retain, nonatomic) IBOutlet UIButton *updateButton;

@end
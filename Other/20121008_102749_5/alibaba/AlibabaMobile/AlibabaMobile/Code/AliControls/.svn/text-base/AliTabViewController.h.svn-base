//
//  AliTabViewController.h
//  AlibabaMobile
//
//  Created by  on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliNavigationBackButton.h"
#import "AliSegmentedControl.h"
#import "AliTabContentViewController.h"
#import "AliBaseViewController.h"

@class AliNavigationTitleLabel;


@interface AliTabViewController : AliBaseViewController <AliNavigationBackDelegate, AliSegmentedDelegate>
{

}

@property (nonatomic, retain) NSMutableDictionary * dataDict;

//添加内容tab
-(void) addTabPage:(NSString *)tabTitle viewControllerName:(NSString *)viewControllerName;
//切换内容
- (void) switchContentView:(int)tabIndex;


@end

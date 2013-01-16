//
//  MyUITabBarController.h
//  AlibabaMobile
//
//  Created by mardin partytime on 2/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliCustomTabBar.h"

#import "AliLoadingDataView.h"

@interface MyUITabBarController : UIViewController <CustomTabBarDelegate,UIAlertViewDelegate,UITabBarControllerDelegate,UINavigationControllerDelegate>
{
}

@property (retain, nonatomic) IBOutlet AliCustomTabBar *aliTabBar;

@property(nonatomic,retain) NSMutableArray *tabBarItemArray;
@property (retain, nonatomic) IBOutlet UIView *contentView;

@property (nonatomic,retain) AliLoadingDataView * mLoadingView;

-(void)entryTabBarItem:(NSString*)name;
-(void)entryMsgCenter;


@end

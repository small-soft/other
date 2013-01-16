//
//  AliCustomTabBar.h
//  tabBarTest
//
//  Created by alimobile on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AliCustomTabBar;

@protocol CustomTabBarDelegate

- (NSUInteger)tabBarItemCount:(AliCustomTabBar*)tabBar;
- (UIControl*)tabBarItemView:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex;
@optional
- (UIImage*) tabBarSelectedItemImage:(AliCustomTabBar*)tabBar;
- (UIImage*) tabBarBackgroundImage:(AliCustomTabBar*)tabBar;
-(void)tabBarItemViewHighlighted:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex;
-(void)tabBarItemViewUnHighlighted:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex;
-(void)tabBarItemViewDidSelected:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex;
-(BOOL)tabBarItemViewShouldDidSelected:(AliCustomTabBar*)tabBar atIndex:(NSUInteger)itemIndex;
@end

@interface AliCustomTabBar : UIView
-(void)setNewSelectedItem:(NSInteger)itemIdx;

@property (nonatomic,assign) NSObject <CustomTabBarDelegate> *delegate;
@property(nonatomic) NSInteger selectedItem;
@property(nonatomic) BOOL reload;
@property(nonatomic) BOOL reloadItemContent;

@end

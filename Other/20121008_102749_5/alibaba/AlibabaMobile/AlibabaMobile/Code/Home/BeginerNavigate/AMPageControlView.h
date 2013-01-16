//
//  AMPageControlView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-3.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliPageControl.h"
#import "AliGallaryView.h"
@class AMPageControlView;

@protocol AMPageControlViewDelegate <NSObject>

- (NSUInteger)numberOfSectionsInGallaryView:(UIView*)gallaryView;
- (UIControl*)AliGallaryView:(UIView*)gallaryView atIndex:(NSUInteger)itemIndex;
@optional
-(void)AliGallaryView:(UIView*)gallaryView didAtIndex:(NSUInteger)itemIndex;
@end

@interface AMPageControlView : UIView<UIScrollViewDelegate>
@property (retain, nonatomic)AliPageControl *pageControl;
@property (nonatomic,assign) id <AMPageControlViewDelegate> delegate;
@property (nonatomic)BOOL showPageControl;
@property (nonatomic)BOOL autoScroll;
-(void)reloadData;


@end

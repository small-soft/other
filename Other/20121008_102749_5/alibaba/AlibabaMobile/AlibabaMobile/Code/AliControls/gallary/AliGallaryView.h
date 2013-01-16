//
//  AliGallaryView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AliGallaryView;

@protocol AliGallaryViewDelegate <NSObject>

- (NSUInteger)numberOfSectionsInGallaryView:(AliGallaryView*)gallaryView;
- (UIControl*)AliGallaryView:(AliGallaryView*)gallaryView atIndex:(NSUInteger)itemIndex;
@optional
-(void)AliGallaryView:(AliGallaryView*)gallaryView didAtIndex:(NSUInteger)itemIndex;
@optional

@end
@interface AliGallaryView : UIView<UIScrollViewDelegate>

@property (nonatomic,retain) NSObject <AliGallaryViewDelegate> *delegate;
@property (nonatomic)BOOL showPageControl;
@property (nonatomic)BOOL autoScroll;
-(void)stopScroll;
-(void)reloadData;
@end

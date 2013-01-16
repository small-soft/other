//
//  AMSegmentedCtlWithButton.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-18.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMFavSegmentedControl.h"
#import "AliBackButton.h"

typedef enum {
    UIAMFavSegmentedControlHidden = 0,
    UISegmentedControlHidden  = 1,
    UIButtonHidden = 2,
} SegmentedControlHidden;


@interface AMSegmentedCtlWithButton : UIControl

@property (nonatomic,retain) IBOutlet AMFavSegmentedControl *mSegmentedControl;
@property (nonatomic,retain) IBOutlet UISegmentedControl    *segmentedControl;
@property (nonatomic,retain) IBOutlet UIButton              *button;
@property (nonatomic,retain) IBOutlet AliBackButton *backButton;
@property (nonatomic,assign) BOOL isMSegmentedControl;

- (void)ChangeSegmentFont:(UIView *)aView;
- (void)setItemsHidden:(NSUInteger)segmentedControlHidden Hidden:(BOOL)hidden;
- (void) setBgImage:(NSString *)imageName WithIndex:(int)index WithState:(int) state ;
- (void) setLableTitle:(NSString *)imageName WithIndex:(int)index Visable:(BOOL)visable ;
- (void) addItem:(NSString *)name;
- (void) setSelectedIndex:(int)index;
- (void) setDelegate:(id)delegate;
- (void) insertSegmentWithTitle:(NSString *)title atIndex:(NSUInteger)index animated:(BOOL)animated;
@end

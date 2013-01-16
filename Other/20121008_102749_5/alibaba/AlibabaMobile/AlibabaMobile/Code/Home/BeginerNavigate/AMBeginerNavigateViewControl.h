//
//  AMBeginerNavigateViewControl.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-3.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMPageControlView.h"
#define BEGINER_NAVIGATE_IMAGEVIEW_COUNT 1

@interface AMBeginerNavigateViewControl : UIViewController<AMPageControlViewDelegate>
@property (nonatomic,retain) UIButton *quitButton;
@property (nonatomic,retain) IBOutlet AMPageControlView *gallaryView;
-(void) quitAction: (id)sender;
@end
